#include <catch2/catch_test_macros.hpp>
#include <string>
#include <cstdint>

#include "lexer.hpp"
#include "tokens.hpp"
#include "cassert"

TEST_CASE( "lexer", "[lexer]" ) {
  SECTION( "lexes instructions consisting of unsigned" ) {
    using namespace Awax86;
    std::vector<std::uint8_t> input{
      // submerge
      0x6, 0x4,
      0x6, 0x1F,
      0x6, 0x00,
      0x6, 0x2F,
    };
    Lexer lexer{std::move(input)};
    lexer.AnalyseBinaryIR();
    std::vector<Tokens> output = lexer.DestructiveReadTokens();
    std::vector<Tokens> requiredResult{
      Tokens{.m_token = Opcode::sbm, .value = 0x4},
      Tokens{.m_token = Opcode::sbm, .value = 0x1f},
      Tokens{.m_token = Opcode::sbm, .value = 0x00},
      Tokens{.m_token = Opcode::sbm, .value = 0x2f}
    };
    REQUIRE(output == requiredResult);
  }

  SECTION( "lexes system instructions" ) {
    using namespace Awax86;
    std::vector<std::uint8_t> input{
      0x00, // nop
      0x01, // prn
      0x02, // pr1
      0x03, // red
      0x04, // r3d
      0x1f, // trm
    };
    Lexer lexer{std::move(input)};
    lexer.AnalyseBinaryIR();
    std::vector<Tokens> output = lexer.DestructiveReadTokens();
    std::vector<Tokens> requiredResult{
      Tokens{.m_token = Opcode::nop},
      Tokens{.m_token = Opcode::print},
      Tokens{.m_token = Opcode::pr1nt},
      Tokens{.m_token = Opcode::red},
      Tokens{.m_token = Opcode::r3d},
      Tokens{.m_token = Opcode::terminate},
    };
    REQUIRE(output == requiredResult);
  }

  SECTION( "lexes pile instructions without operands" ) {
    using namespace Awax86;
    std::vector<std::uint8_t> input{
      0x07, // pop
      0x07, // pop
      0x08, // dpl
      0x08, // dpl
      0x0a, // merge
      0x0a, // merge
      0x07, // pop
      0x08, // dpl
      0x0a, // merge
    };
    Lexer lexer{std::move(input)};
    lexer.AnalyseBinaryIR();
    std::vector<Tokens> output = lexer.DestructiveReadTokens();
    std::vector<Tokens> requiredResult{
      Tokens{.m_token = Opcode::pop},
      Tokens{.m_token = Opcode::pop},
      Tokens{.m_token = Opcode::dupe},
      Tokens{.m_token = Opcode::dupe},
      Tokens{.m_token = Opcode::merge},
      Tokens{.m_token = Opcode::merge},
      Tokens{.m_token = Opcode::pop},
      Tokens{.m_token = Opcode::dupe},
      Tokens{.m_token = Opcode::merge},
    };
    REQUIRE(output == requiredResult);
  }

  SECTION( "lexes arithemtic instructions" ) {
    using namespace Awax86;
    std::vector<std::uint8_t> input{
      0x0b,   // add
      0x0b,   // add
      0x0b,   // add
      0x0c,   // sub
      0x0c,   // sub
      0x0c,   // sub
      0x0d,   // mul
      0x0d,   // mul
      0x0d,   // mul
      0x0e,   // div
      0x0e,   // div
      0x0e,   // div
      0x0f,   // cnt
      0x0f,   // cnt
      0x0f,   // cnt
      0x0e,   // div
      0x0d,   // mul
      0x0c,   // sub
      0x0b,   // add
    };
    Lexer lexer{std::move(input)};
    lexer.AnalyseBinaryIR();
    std::vector<Tokens> output = lexer.DestructiveReadTokens();
    std::vector<Tokens> requiredResult{
      Tokens{.m_token = Opcode::add},
      Tokens{.m_token = Opcode::add},
      Tokens{.m_token = Opcode::add},
      Tokens{.m_token = Opcode::sub},
      Tokens{.m_token = Opcode::sub},
      Tokens{.m_token = Opcode::sub},
      Tokens{.m_token = Opcode::mult},
      Tokens{.m_token = Opcode::mult},
      Tokens{.m_token = Opcode::mult},
      Tokens{.m_token = Opcode::div},
      Tokens{.m_token = Opcode::div},
      Tokens{.m_token = Opcode::div},
      Tokens{.m_token = Opcode::count},
      Tokens{.m_token = Opcode::count},
      Tokens{.m_token = Opcode::count},
      Tokens{.m_token = Opcode::div},
      Tokens{.m_token = Opcode::mult},
      Tokens{.m_token = Opcode::sub},
      Tokens{.m_token = Opcode::add},
    };
    REQUIRE(output == requiredResult);
  }

  SECTION( "lexes program flow instructions without operands" ) {
    using namespace Awax86;
    std::vector<std::uint8_t> input{
      0x12, // eql
      0x12, // eql
      0x12, // eql
      0x13, // lss
      0x13, // lss
      0x13, // lss
      0x14, // gr8
      0x14, // gr8
      0x14, // gr8
      0x12, // eql
      0x13, // lss
      0x14, // gr8
    };
    Lexer lexer{std::move(input)};
    lexer.AnalyseBinaryIR();
    std::vector<Tokens> output = lexer.DestructiveReadTokens();
    std::vector<Tokens> requiredResult{
      Tokens{.m_token = Opcode::equals},
      Tokens{.m_token = Opcode::equals},
      Tokens{.m_token = Opcode::equals},
      Tokens{.m_token = Opcode::less},
      Tokens{.m_token = Opcode::less},
      Tokens{.m_token = Opcode::less},
      Tokens{.m_token = Opcode::greater},
      Tokens{.m_token = Opcode::greater},
      Tokens{.m_token = Opcode::greater},
      Tokens{.m_token = Opcode::equals},
      Tokens{.m_token = Opcode::less},
      Tokens{.m_token = Opcode::greater},
    };
    REQUIRE(output == requiredResult);
  }

}
