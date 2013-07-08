#include "shpp.hxx"
#include "help.hxx"
#include "config.hxx"
using namespace std;
extern "C" {
#include "getopt.h"
};
#include <boost/filesystem.hpp> 


#define DEFAULT_OUTPUT STDOUT


int main(int argc, char *argv[])
{
    float appver=APPVER;
    int mode_int, stdoutput=0;
#define INPUT_OPTIONS "hHVf:o:"
    static struct option long_options[] {
	{ "help", 0, 0, 'h' },
	{ "long-help",0 , 0,'H'},
	{"version",0, 0,'V'},
	{ "mode", 1, 0, 'm'},
	{"stdout", 0, &stdoutput, 1}
    };

    int input_character;
    int digit_optind = 0;
    int aopt=0, bopt=0;
    string mode;
    char *copt=0, *dopt = 0;
    int optind = 0;
    int option_index = 0;

    string inputfile_raw;
    string outputfile_raw;
    while (
	(input_character = getopt_long(argc, argv, INPUT_OPTIONS, long_options, &option_index)) != -1)
    {
	int this_option_optind = optind ? optind: 1;
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
	case 'V':
	    cout << appver << endl;
	    return 0;
	case 'f':
	    inputfile_raw = optarg;
	    break;
	case 'm':
	    mode = optarg;
	    break;
	case 'o':
	    outputfile_raw = optarg;
	    break;
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
    if ( mode == "c" )
	mode_int=1;
    else
	mode_int=0;

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

    return parser(inputfile_raw, outputfile_raw, mode_int);
}
