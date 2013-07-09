#ifndef SHPP_HXX
#define SHPP_HXX
#include <iostream>
#include <fstream>
#include <boost/tr1/regex.hpp>
#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>
using std::string;
using std::ifstream;
using std::ofstream;
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
    int line_ued;
    command *father=NULL;
    command **childs;
    std::vector<std::string> args;
};

/*
  contains just the commands of a file
*/
typedef struct {
    command *commands;
    int command_count;
} script;

typedef struct {
    int mode;
    int verbose;
} state_container;
/*
  parser does:
  open file
  calls script=parse(file);
  calls run(&script, &file);
*/
script parse(ifstream *scriptfile);
bool run(script *Script, ifstream *scriptfile, ofstream *outputfile);
bool parser(string scriptfile_raw, string outputfile_raw);
/*
  follows command until its NULL
*/
bool follow(command *target, string want1, string want2);

/*
  global link to the current command
*/
extern command *self;
extern state_container settings;
#endif
