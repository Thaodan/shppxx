#include "shpp.hxx"
#include "commands/commands.hxx"
void stub(void) {
  std::cout << "stub";
}
bool parser(string scriptfile)
{
  ofstream script_raw=open(scriptfile, ios::in );
  script Script=parse(&scriptfile);
  run(&script, &script_raw);
  return true;
}

script parse(ofstream *scriptfile)
{
  stub;
  return true;
}
