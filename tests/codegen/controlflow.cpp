#include <catch2/catch_test_macros.hpp>
#include <string>
#include <filesystem>
#include <cstdint>
#include <cassert>
#include <iostream>

#include "x86codegen.hpp"
#include "tokens.hpp"

TEST_CASE( "x86codegen control flow", "[codegen_controlflow]" ){
  // PRELUDE:
  namespace fs = std::filesystem;
  // creates the directory of tests if they dont exist
  const fs::path tests_path = fs::path().string() + "./out_tests";
  if(!fs::exists(tests_path)){
    std::cout << "creating the tests directory\n";
    fs::create_directory(tests_path);
  }
  // creates the directory of controlflow if they dont exist
  const fs::path controlflow_path = tests_path.string() + "/controlflow";
  // first check if the test directory exists
  if(!fs::exists(controlflow_path)){
    std::cout << "creating the control flow directory\n";
    fs::create_directory(controlflow_path);
  }

  SECTION("handles lbl and jumping to lbl"){
    using namespace Awax86;
    // example program:
    //  lbl 0
    //  push 10
    //  jmp 0
    //  basically fills the ram with the number 10
    std::vector<Tokens> input_tokens{
      Tokens{label, 0},   
      Tokens{blow, 10},   
      Tokens{jump, 0}     
    };
    X86Generator codegen{
      std::move(input_tokens), 
      std::string{controlflow_path.string() + "/lbl.s"}
    };
    codegen.Run();
  }

  SECTION("handles equal"){
    using namespace Awax86;
    // example program:
    //  push 10
    //  push 10
    //  if the last two values are equals:
    //    push 90
    //  else:
    //    push 30
    std::vector<Tokens> input_tokens{
      Tokens{blow, 10},   // blo 10
      Tokens{blow, 10},   // blo 10
      Tokens{equals, 0},  // eql 
      Tokens{blow, 30},   // blo 90
      Tokens{blow, 90},   // blo 30
      //Tokens{print, 0}    // prn  - should be 90
    };
    X86Generator codegen{
      std::move(input_tokens), 
      std::string{controlflow_path.string() + "/equal.s"}
    };
    codegen.Run();
  }
}
