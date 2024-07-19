#include <catch2/catch_test_macros.hpp>
#include <string>
#include <cstdint>

#include "awassembler.hpp"
#include "tokens.hpp"
#include "cassert"

TEST_CASE( "awassembly", "[awasm]" ) {
  SECTION( "compiles normal" ) {
    using namespace Awax86;
    std::string input = R"-(
      4dd
      cnt
      div 
      div
      dpl
      eql
      gr8
    )-";
    Awassembler assembler{std::vector<char>(input.begin(), input.end())};
    assembler.Convert();
    std::vector<std::uint8_t> output = assembler.DestructiveGetBinaryIR();
    std::vector<std::uint8_t> requiredResult{
      Opcode::add,
      Opcode::count,
      Opcode::div,
      Opcode::div,
      Opcode::dupe,
      Opcode::equals,
      Opcode::greater
    };
    REQUIRE(output == requiredResult);
  }


  SECTION( "compiles dpl and div" ) {
    using namespace Awax86;
    std::string input = R"-(
      4dd
      div 
      div
      dpl
      dpl
    )-";
    Awassembler assembler{std::vector<char>(input.begin(), input.end())};
    assembler.Convert();
    std::vector<std::uint8_t> output = assembler.DestructiveGetBinaryIR();
    std::vector<std::uint8_t> requiredResult{
      Opcode::add,
      Opcode::div,
      Opcode::div,
      Opcode::dupe,
      Opcode::dupe,
    };
    REQUIRE(output == requiredResult);
  }

  SECTION( "compiles lbl and lss correctly" ) {
    using namespace Awax86;
    std::string input = R"-(
      lss
      lbl 1
      lss
      lbl 2
      lbl 3
      lss
    )-";
    Awassembler assembler{std::vector<char>(input.begin(), input.end())};
    assembler.Convert();
    std::vector<std::uint8_t> output = assembler.DestructiveGetBinaryIR();
    std::vector<std::uint8_t> requiredResult{
      Opcode::less,
      Opcode::label, 1,
      Opcode::less,
      Opcode::label, 2,
      Opcode::label, 3,
      Opcode::less
    };
    REQUIRE(output == requiredResult);
  }

  SECTION( "compiles mrg and mul correctly" ) {
    using namespace Awax86;
    std::string input = R"-(
      mrg
      mrg
      mul
      mul
      mrg
      mul
    )-";
    Awassembler assembler{std::vector<char>(input.begin(), input.end())};
    assembler.Convert();
    std::vector<std::uint8_t> output = assembler.DestructiveGetBinaryIR();
    std::vector<std::uint8_t> requiredResult{
      Opcode::merge,
      Opcode::merge,
      Opcode::mult,
      Opcode::mult,
      Opcode::merge,
      Opcode::mult
    };
    REQUIRE(output == requiredResult);
  }

  SECTION( "compiles pop, pr1 and prn correctly" ) {
    using namespace Awax86;
    std::string input = R"-(
      pop
      pop
      pr1
      pr1
      prn
      prn
      pop
      pr1
      prn
    )-";
    Awassembler assembler{std::vector<char>(input.begin(), input.end())};
    assembler.Convert();
    std::vector<std::uint8_t> output = assembler.DestructiveGetBinaryIR();
    std::vector<std::uint8_t> requiredResult{
      Opcode::pop,
      Opcode::pop,
      Opcode::pr1nt,
      Opcode::pr1nt,
      Opcode::print,
      Opcode::print,
      Opcode::pop,
      Opcode::pr1nt,
      Opcode::print,
    };
    REQUIRE(output == requiredResult);
  }

  SECTION( "compiles red and r3d correctly" ) {
    using namespace Awax86;
    std::string input = R"-(
      red
      red
      r3d
      r3d
      red
      r3d
    )-";
    Awassembler assembler{std::vector<char>(input.begin(), input.end())};
    assembler.Convert();
    std::vector<std::uint8_t> output = assembler.DestructiveGetBinaryIR();
    std::vector<std::uint8_t> requiredResult{
      Opcode::red,
      Opcode::red,
      Opcode::r3d,
      Opcode::r3d,
      Opcode::red,
      Opcode::r3d
    };
    REQUIRE(output == requiredResult);
  }

  SECTION( "compiles sbm u5, srn u5 and sub correctly" ) {
    using namespace Awax86;
    std::string input = R"-(
      sbm 1
      sbm 2
      srn 3
      srn 4
      sub
      sub
      sbm 5
      srn 6
      sub
    )-";
    Awassembler assembler{std::vector<char>(input.begin(), input.end())};
    assembler.Convert();
    std::vector<std::uint8_t> output = assembler.DestructiveGetBinaryIR();
    std::vector<std::uint8_t> requiredResult{
      Opcode::sbm, 1,
      Opcode::sbm, 2,
      Opcode::srn, 3,
      Opcode::srn, 4,
      Opcode::sub,
      Opcode::sub,
      Opcode::sbm, 5,
      Opcode::srn, 6,
      Opcode::sub
    };
    REQUIRE(output == requiredResult);
  }

  SECTION( "compiles the \"atomic\" tokens separately" ) {
    using namespace Awax86;
    std::string input = R"-(
      4dd
      4dd
      cnt
      cnt
      eql
      eql
      gr8
      gr8
      mrg
      mrg
      nop
      nop
      trm
      trm
    )-";
    Awassembler assembler{std::vector<char>(input.begin(), input.end())};
    assembler.Convert();
    std::vector<std::uint8_t> output = assembler.DestructiveGetBinaryIR();
    std::vector<std::uint8_t> requiredResult{
      Opcode::add,
      Opcode::add,
      Opcode::count,
      Opcode::count,
      Opcode::equals,
      Opcode::equals,
      Opcode::greater,
      Opcode::greater,
      Opcode::merge,
      Opcode::merge,
      Opcode::nop,
      Opcode::nop,
      Opcode::terminate,
      Opcode::terminate,
    };
    REQUIRE(output == requiredResult);
  }

  SECTION( "compiles the example" ) {
    using namespace Awax86;
    std::string input = R"-(
      blo 25 // ayo
      blo 4 // ayo
      mul
    )-";
    Awassembler assembler{std::vector<char>(input.begin(), input.end())};
    assembler.Convert();
    std::vector<std::uint8_t> output = assembler.DestructiveGetBinaryIR();
    std::vector<std::uint8_t> requiredResult{
      Opcode::blow, 25,
      Opcode::blow, 4,
      Opcode::mult
    };
    REQUIRE(output == requiredResult);
  }
}
