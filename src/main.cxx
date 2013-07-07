#include "shpp.hxx"
#include "help.hxx"
using namespace std;
extern "C" {
#include "getopt.h"
};

int main(int argc, char *argv[])
{
  int input_character;
  int digit_optind = 0;
  int aopt=0, bopt=0;
  char *copt=0, *dopt = 0;
  static struct option long_options[] {
    { "help", 0, 0, 'h' }
  };
  int optind = 0;
  int option_index = 0;
  while (
	 (input_character = getopt_long(argc, argv, "h", long_options, &option_index)) != -1)
    {
      int this_option_optind = optind ? optind: 1;
      switch (input_character)
        {
        case 'h':
	  display_help();
	  break;
        default:
	  cerr << "-h for help" << endl;
	  break;
        }
    }
    return 0;
}
