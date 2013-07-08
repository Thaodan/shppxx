#include "shpp.hxx"
/* follow command until command->father is NULL */
bool follow(command *target, string want1, string want2)
{
    while ( target->father->args[0] == want1 || target->father->args[0] == want2
	    || target->father == NULL)
    {
	target=target->father;
    }
  
    if ( target->father == NULL )
	return false;
    else
	return true;
}
