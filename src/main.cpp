#include "awatismconverter.hpp"

int main(){
  Awa4x86::AwatismConverter conv{"./../awa.txt"};
  conv.ConvertAwatismToBinary();
  conv.PrintBuffer();
  conv.PrintBinaryIR();
}
