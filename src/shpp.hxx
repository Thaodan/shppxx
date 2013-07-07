#ifndef SHPP_HXX
#define SHPP_HXX
#include <iostream>
#include <fstream>
using std::string;
using std::ofstream;

void stub(void) {
  std::cout << "stub";
}

#define MAX_COMMAND_ARGS 9
/*
  this is our command type
  string is the raw command string
  childs contains all commands that are below command as pointer
  arg all args of command
  arg[0] is name of command
 */
typedef struct command commmand;
struct command{
  string raw_string;
  command *father=NULL;
  command **childs;
  string args[MAX_COMMAND_ARGS];
};

/*
  contains just the commands of a file
 */
typedef struct {
  command *commands;
} script;

namespace defines {
  string *stack;
}
/*
  parser does:
  open file
  calls script=parse(file);
  calls run(&script, &file);
 */
script parse(ofstream *script_file);
bool run(script *scriptfile, ofstream *scriptfile_raw);
bool parser(string script_file);
/*
follows command until its NULL
 */
bool follow(command *target, string want);

/*
  global link to the current command
 */
extern command *self;
#endif
