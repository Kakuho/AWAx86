#include <catch2/catch_test_macros.hpp>
#include <string>
#include <filesystem>
#include <cstdint>
#include <cassert>
#include <iostream>

#include "x86codegen.hpp"
#include "tokens.hpp"

TEST_CASE( "x86codegen pop", "[codegen_dpl]" ){
  // PRELUDE:
  namespace fs = std::filesystem;
  // creates the directory of tests if they dont exist
  const fs::path tests_path = fs::path().string() + "./out_tests";
  if(!fs::exists(tests_path)){
    std::cout << "creating the tests directory\n";
    fs::create_directory(tests_path);
  }
  // creates the directory of controlflow if they dont exist
  const fs::path controlflow_path = tests_path.string() + "/duplicate";
  // first check if the test directory exists
  if(!fs::exists(controlflow_path)){
    std::cout << "creating the push directory\n";
    fs::create_directory(controlflow_path);
  }

  SECTION("compiler is able to handle duplication"){
    using namespace Awax86;
    // example program:
    //  blo 0
    //  blo 10
    //  dpl
    //  stack = [0, 10, 10]
    // essentially 
    std::vector<Tokens> input_tokens{
      Tokens{blow, 0},   
      Tokens{blow, 10},   
      Tokens{dupe, 0},
    };
    X86Generator codegen{
      std::move(input_tokens), 
      std::string{controlflow_path.string() + "/dpl1.s"}
    };
    codegen.Run();
  }

  SECTION("mixing blo, pop and dpl"){
    using namespace Awax86;
    // compiler needs to clean up 5
    std::vector<Tokens> input_tokens{
      Tokens{blow, 0},   
      Tokens{blow, 10},   
      Tokens{blow, 39},   
      Tokens{dupe, 0},
      Tokens{dupe, 0},
      Tokens{blow, 10},   
      Tokens{pop, 10}
    };
    X86Generator codegen{
      std::move(input_tokens), 
      std::string{controlflow_path.string() + "/dpl_5.s"}
    };
    codegen.Run();
  }
}
