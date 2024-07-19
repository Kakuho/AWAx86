#include <stdexcept>
#include <string>
#include <cstring>

#include "awatismconverter.hpp"
#include "awassembler.hpp"
#include "x86codegen.hpp"
#include "pipeline.hpp"


void TestExample(){
  using namespace Awax86;
  Awax86::X86Generator codegen{std::vector<Awax86::Tokens>{
    Tokens{Opcode::blow, 10},
    Tokens{Opcode::blow, 4},
    Tokens{Opcode::mult, 0xFF},
  }};
  codegen.Generate();
}

void ExamplePipeline(){
  using namespace Awax86;
  Awax86::Pipeline pipeline{"./../programs/awaseembly/example.awasm"};
  pipeline.Run();

}

struct CliArgs{
  std::string input_name;
  std::string output_name;
};

int main(int argc, const char* argv[]){
  CliArgs argpack;
  if(argc != 4 && argc != 2){
    throw std::runtime_error{"format: input_file -o output_file"};
  }
  if(argc == 4){
    if(strcmp(argv[2], "-o") != 0){
      throw std::runtime_error{"format: input_file -o output_file"};
    }
    argpack.input_name = argv[1]; 
    argpack.output_name = argv[3];
  }
  else if(argc == 2){
    argpack.input_name = argv[1]; 
    argpack.output_name = "output.s";
  }
  Awax86::Pipeline pipeline{std::move(argpack.input_name), std::move(argpack.output_name)};
  pipeline.Run();
}
