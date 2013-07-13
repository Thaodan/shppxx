#include "shpp.hxx"
#include "help.hxx"
#include "config.hxx"
using namespace std;
extern "C" {
#include "getopt.h"
};



#define DEFAULT_OUTPUT STDOUT
state_container settings;

int main(int argc, char *argv[])
{
    float appver=APPVER;
    int stdoutput=0;
#define INPUT_OPTIONS "hHVvf:o:"
    static struct option long_options[] {
	{ "help", 0, 0, 'h' },
	{ "long-help",0 , 0,'H'},
	{"version",0, 0,'V'},
	{ "mode", 1, 0, 'm'},
	{"stdout", 0, &stdoutput, 1},
	{"verbose", 0, 0, 'v'}
    };
    int input_character, this_option_optind;
    std::map< std::string, std::string> mode_strs;
    std::map<std::string, std::string>::iterator mode_str_it; 
    mode_strs["shpp"] = "#\\\\";
    mode_strs["cpp"] = "#";
    string mode_str;
    int optind = 0, option_index = 0;
    string inputfile_raw;
    string outputfile_raw;
    while ( (input_character = getopt_long(argc, argv, INPUT_OPTIONS, long_options, &option_index)) != -1 )
    {
	this_option_optind = optind ? optind: 1;
	if ( input_character == -1 )
	    break;

	switch (input_character)
        {
        case 'h':
	    display_help();
	    return 0;
	case 'H':
	    display_long_help();
	    return 0;
	case 'v':
	    settings.verbose=1;
	    break;
	case 'V':
	    cout << appver << endl;
	    return 0;
	case 'f':
	    inputfile_raw = optarg;
	    break;
	case 'm':
	    mode_str = optarg;
	    break;
	case 'o':
	    outputfile_raw = optarg;
	    break;
	case '?':
	    return 1;
        default:
	    break;
        }
    }

    if ( optind < argc && argc > 1)
    {
	/*
	  last should always be input file
	*/
	if (inputfile_raw == "" )
	    inputfile_raw = argv[argc-1];
      
	//for (index = optind; index < argc; index++)
	//switch(argv[index])
    }  

    else
    {
	cerr << "Need input file" << endl;
	return 1;
    }

    if ( ! boost::filesystem::exists( inputfile_raw ) )
    {
	cerr << inputfile_raw << " not found" << endl;
	return 1;
    }
#ifdef WOEXIST_ERR
    if ( boost::filesystem::exists(outputfile_raw) )
    {
	cerr << outputfile_raw << " exists already" << endl;
	return 1;
    }
#endif
    /*
      check if parse mode is cpp
    */
    mode_str_it = mode_strs.find(mode_str);
    if ( mode_str_it == mode_strs.end() )
    {
	cerr << "Unkown mode " << mode_str << endl;
	return 1;
    }
    settings.mode_str = mode_str_it->second;

    /*
      check if we got no output_file
    */
    if ( outputfile_raw == "" )
    {
	if ( ! stdoutput )
	    cerr << "warning no output file using stdout as default" << endl;
	// FIXME: need portable way to write to STDOUT
	outputfile_raw = "/dev/stdout";;
    }

    return parser(inputfile_raw, outputfile_raw);
}
