#include "shpp.hxx"
#include "help.hxx"
using namespace std;
extern "C" {
#include "getopt.h"
};
#include <boost/filesystem.hpp> 


#define INPUT_OPTIONS "hf:o:"
#define DEFAULT_OUTPUT STDOUT


int main(int argc, char *argv[])
{
  int input_character;
  int digit_optind = 0;
  int aopt=0, bopt=0;
  string mode;
  int mode_int;
  char *copt=0, *dopt = 0;
  static struct option long_options[] {
    { "help", 0, 0, 'h' },
    { "mode", 1, 0, 'm'}
  };
  int optind = 0;
  int option_index = 0;



  string inputfile_raw;
  string outputfile_raw;
  while (
	 (input_character = getopt_long(argc, argv, INPUT_OPTIONS, long_options, &option_index)) != -1)
    {
      int this_option_optind = optind ? optind: 1;
      switch (input_character)
        {
        case 'h':
	  display_help();
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
	  cerr << "-h for help" << endl;
	  return 1;
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
      cerr << "warning no output file using stdout as default" << endl;
      // FIXME: need portable way to write to STDOUT
      outputfile_raw = "/dev/stdout";
    }

  return parser(inputfile_raw, outputfile_raw, mode_int);
}
