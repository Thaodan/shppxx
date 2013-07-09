#include "shpp.hxx"
#include "commands/commands.hxx"

void stub(void) {
    std::cout << "stub";
}
bool parser(string scriptfile_raw, string outputfile_raw)
{
    ifstream scriptfile;
    ofstream outputfile;
    script Script;
    bool part_state;
    scriptfile.open(scriptfile_raw.c_str());
    if ( ! scriptfile.is_open() )
    {
	std::cerr << "error while open input file" 
		  << scriptfile_raw << std::endl;
	return false;
    }
  
    outputfile.open(outputfile_raw.c_str(), ofstream::out);
    if ( ! outputfile.is_open() )
    {
	std::cerr << "error while open output file" 
		  << outputfile_raw << std::endl;
	return false;
    }
    Script = parse(&scriptfile);
    part_state = run(&Script, &scriptfile, &outputfile);
    scriptfile.close();
    outputfile.close();
    return part_state;
}

#define REGEX_MODE std::tr1::regex::egrep
command *self;
script parse(ifstream *scriptfile)
{
    string line;
    script Script;
    int line_index=0, command_index=0, command_counter=0;
    std::vector<std::string> args;
    /*
      parse modes:
      0: shpp : sh
      1: CPU  : c
    */
    std::tr1::regex modes[2] = {
	std::tr1::regex("^#\\\\", REGEX_MODE ),
	std::tr1::regex("^#")
    };
    std::tr1::regex end_line("\n");
    std::tr1::regex end_char(";");
    std::tr1::cmatch match;

    /*
      count how many commands we got to make commands
    */
    while ( getline(*scriptfile, line))
    {
	line_index++;
	if ( std::tr1::regex_search(line.c_str(),  modes[settings.mode]) )
	    command_counter++;
    }
    /* reset states*/
    line_index=0;
    /* reset state of scriptfile */
    scriptfile->clear();
    scriptfile->seekg(0, std::ios::beg);
    static command *command_stack = new command[command_counter];
       
    while ( getline(*scriptfile, line))
    {
	line_index++;
	if ( std::tr1::regex_search(line.c_str(),  modes[settings.mode]) )
	{
	    if ( command_index < command_counter )
	    {
		if ( settings.verbose )
		    (command_stack+command_index)->line_ued=line_index;
		(command_stack+command_index)->raw_string=std::tr1::regex_replace(line, modes[settings.mode], "");		//std::cerr << (command_stack+command_index)->raw_string << std::endl;
		boost::split((command_stack+command_index)->args,(command_stack+command_index)->raw_string, boost::is_any_of("\t "));
		command_index++;
	    }
	}
    }
  
    Script.commands=command_stack;
    Script.command_count=command_counter;
    return Script;
}

bool run(script *Script, ifstream *scriptfile, ofstream *outputfile)
{
    int command_index=0;
    while ( command_index < Script->command_count)
    {
	msg::verbose("L"+std::to_string(Script->commands[command_index].line_ued) + ": found XXX raw string is '"
		+ Script->commands[command_index].raw_string +"'" );
	*outputfile << Script->commands[command_index].raw_string << std::endl;
	command_index++;
    }
    return false;
}
