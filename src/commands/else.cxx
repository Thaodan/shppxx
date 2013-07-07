#include "../shpp.hxx"
#include "commands.hxx"

bool Else(void)
{
  /* follow current command and see if father of it is if */
  if ( follow(self) == "if" )
    return true;
  else
    return false;
}
