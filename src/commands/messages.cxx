#include "../shpp.hxx"
#include "commands.hxx"
namespace msg {
    void msg(string message)
    {
	std::cerr << message << std::endl;
    }
    
    void verbose(string message)
    {
	if (settings.verbose)
	    msg(message);
    }
    
    bool error(string message)
    {
	msg(message);
	return false;
    }
}
