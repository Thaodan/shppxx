#include <iostream>
#include "help.hxx"
#include "utils.hxx"
void display_help(void)
{
  static std::string help_msg = R"HELP_MSG(
* OPTIONS  
  - --help        -H -h ::              print this help
  - --version     -v    ::              print version
  - --color       -C    ::              enable colored output
  - --verbose     -v    ::              tell us what we do

  - --output        -o  _file_     ::   places output in file
  - --option        -O  _option_   ::   give shpp <option>
  - --stdout                       ::   output result goes to stdout
  - --stderr=<destination>         ::   stderr goes to destination
  - --critical-warning             ::   warnings are threated as errors
  -                 -Dvar=var      ::   define var
                                        ( same as '#\\\\ define var=var') 
  -                  -Ipath        ::   add path so search for includes
  -                  -Mpath        ::   same just for macros
  - --tmp=tmp_dir                  ::   set temp directory (use before *-D* or this has no effect)
  - --keep                         ::   don't delete tmp files after running
* COMMANDS
** define
   define  variable
*** SYNTAX
   *define* _foo=_bar_
   Or
   *define* _foo_ _bar_
** if 
   test if condition is true
*** SYNTAX
    *if*  _condition_

    _condition_  can be any condition like foo > bar or these symbols:
    
    - *defined* _var_  :: test if var is defined
    - !                :: negate condtion
    - ||               :: do condition after || if previus condition fails
    - &&               :: do condition after && if previus condition is succesfull

*** Aliases 
     - ifdef  :: = *if* *defined* 
     - ifndef :: = *if* ! *defined* 

** else
   Else statement if if(def) was unsuccesfull, will sent an error if no if(def) was found before or removes content till endif if ifdef was succesfull.

** endif
   Says shpp to stop after ifdef or else was found before, if no ifdef or else was found before shpp will send an error.

** include
  Includes File
*** SYNTAX 
    *include* [_options_] _file_

*** OPTIONS
    - noparse :: dont parse _file_
    - *parser=_parser* :: use _parser_ to parse file
    - *parser_args=options* :: set arguments for _parser_
** rem
   Inits a comment line that will be only the seen before that preprocessor was runned.
** macro
   Loads Macro file
*** SYNTAX
    *macro* _file_
)HELP_MSG";
  std::cout << help_msg << std::endl;
}
