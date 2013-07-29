#include "shpp.hxx"
#include <commands/core>

bool Else(void)
{
    /* follow current command and see if father of it is if */
    if (follow(self, "if", "if" ))
	return true;
    else
	return false;
}
