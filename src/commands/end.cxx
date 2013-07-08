#include "../shpp.hxx"
bool end(void)
{
  /* follow current command and see if father of it is if */
  if ( follow(self, "else", "if" ) )
    return false;
  else
    return true;
}

  
