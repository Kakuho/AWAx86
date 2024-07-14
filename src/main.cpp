#include "awatismconverter.hpp"
#include "awassembler.hpp"

void TestAwasm(std::string inputString){
  Awa4x86::Awassembler awasm2{std::vector<char>(inputString.begin(), inputString.end())};
  awasm2.PrintCharacters();
  awasm2.PrintHexCharacters();
  awasm2.Convert();
}

int main(){
  /*
  Awa4x86::AwatismConverter conv{"./../programs/initial.awa"};
  conv.ConvertAwatismToBinary();
  conv.PrintBuffer();
  conv.PrintBinaryIR();

  Awa4x86::Awassembler awasm{"./../programs/awaseembly/noncomments.awsm"};
  awasm.PrintCharacters();
  awasm.PrintHexCharacters();
  */

  std::string example = R"-(
  blo 25
  blo 4 
  mul   
  prn   
  )-";

  std::string numerics = R"-(
  blo 25
  blo 31
  blo 0
  blo -22
  )-";

  std::string comments = R"-(
  blo 25    \\ here's a comment for you
  blo 31
  )-";

  std::string runningexample = R"-(
  4dd
  cnt
  div div 
  dpl
  eql
  gr8
  )-";

  TestAwasm(runningexample);
}
