#include <catch2/catch_test_macros.hpp>
#include <string>
#include <filesystem>
#include <cstdint>
#include <cassert>
#include <iostream>

#include "x86codegen.hpp"
#include "tokens.hpp"

TEST_CASE( "x86codegen blow", "[codegen_blow]" ){
  // PRELUDE:
  namespace fs = std::filesystem;
  // creates the directory of tests if they dont exist
  const fs::path tests_path = fs::path().string() + "./out_tests";
  if(!fs::exists(tests_path)){
    std::cout << "creating the tests directory\n";
    fs::create_directory(tests_path);
  }
  // creates the directory of controlflow if they dont exist
  const fs::path controlflow_path = tests_path.string() + "/blow";
  // first check if the test directory exists
  if(!fs::exists(controlflow_path)){
    std::cout << "creating the push directory\n";
    fs::create_directory(controlflow_path);
  }

  SECTION("compiler is able to clean up 4 blow"){
    using namespace Awax86;
    // example program:
    //  blo 0
    //  blo 10
    //  blo 30
    //  blo 46
    // essentially 
    std::vector<Tokens> input_tokens{
      Tokens{blow, 0},   
      Tokens{blow, 10},   
      Tokens{blow, 30},   
      Tokens{blow, 46}     
    };
    X86Generator codegen{
      std::move(input_tokens), 
      std::string{controlflow_path.string() + "/pop4.s"}
    };
    codegen.Run();
  }

  SECTION("compiler is able to clean up 15 blow"){
    using namespace Awax86;
    // example program:
    //  blo 0
    //  blo 10
    //  blo 30
    //  blo 46
    // essentially 
    std::vector<Tokens> input_tokens{
      Tokens{blow, 0},   
      Tokens{blow, 10},   
      Tokens{blow, 30},   
      Tokens{blow, 30},   
      Tokens{blow, 0},   
      Tokens{blow, 0},   
      Tokens{blow, 10},   
      Tokens{blow, 30},   
      Tokens{blow, 30},   
      Tokens{blow, 0},   
      Tokens{blow, 10},   
      Tokens{blow, 30},   
      Tokens{blow, 30},   
      Tokens{blow, 46},
      Tokens{blow, 46}     
    };
    X86Generator codegen{
      std::move(input_tokens), 
      std::string{controlflow_path.string() + "/pop15.s"}
    };
    codegen.Run();
  }
}
