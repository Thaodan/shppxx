#ifndef COMMANDS_HXX
#define COMMANDS_HXX
/*
  commands
 */

bool define(int argc, char *argv[MAX_COMMAND_ARGS]);
bool IF(int argc, char *argv[MAX_COMMAND_ARGS]);
bool Else(void);
bool end(void);


/*
  msgs

 */
namespace msg {
    void msg(string message);
    void verbose(string message);
    bool error(string message);
}
#endif
