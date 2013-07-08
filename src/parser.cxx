#include "shpp.hxx"
#include "commands/commands.hxx"
#include <boost/tr1/regex.hpp>

void stub(void) {
    std::cout << "stub";
}
bool parser(string scriptfile_raw, string outputfile_raw, int mode)
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
    Script = parse(&scriptfile, mode);
    part_state = run(&Script, &scriptfile, &outputfile);
    scriptfile.close();
    outputfile.close();
    return part_state;
}

#define REGEX_MODE std::tr1::regex::egrep
command *self;
script parse(ifstream *scriptfile, int mode)
{
    string line;
    script Script;
    int line_index=0;
    int command_index=0;
  
    int command_counter=0;
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
	if ( std::tr1::regex_search(line.c_str(),  modes[mode]) )
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
	if ( std::tr1::regex_search(line.c_str(),  modes[mode]) )
	{
	    if ( command_index < command_counter )
	    {
		(command_stack+command_index)->raw_string=line;
		//std::cerr << (command_stack+command_index)->raw_string << std::endl;
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
	*outputfile << Script->commands[command_index].raw_string << std::endl;
	command_index++;
    }
    return false;
}
