#include "shpp.hxx"
/* follow command until command->father is NULL */
bool follow(command *target, string want[2])
{
  while ( target->father->arg[0] == want[0] || target->father->arg[0] == want[1] || target->father == NULL)
    {
      target=target->father;
    }
  
  if ( target->father == NULL )
    return false;
  else
    return true;
}
