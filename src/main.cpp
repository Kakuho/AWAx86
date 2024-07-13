#include "awatismconverter.hpp"
#include "awassembler.hpp"

int main(){
  Awa4x86::AwatismConverter conv{"./../programs/initial.awa"};
  conv.ConvertAwatismToBinary();
  conv.PrintBuffer();
  conv.PrintBinaryIR();

  Awa4x86::Awassembler awasm{"./../programs/awaseembly/noncomments.awsm"};
  awasm.PrintCharacters();
  awasm.PrintHexCharacters();
}
