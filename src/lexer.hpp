#ifndef LEXER_HPP
#define LEXER_HPP

#include <vector>
#include <cstdint>

namespace Awa4x86{

// lexer tokens
enum class Opcode : std::uint8_t {
  // system 
  nop = 0x00, 
  print = 0x01, 
  pr1nt = 0x02, 
  red = 0x03, 
  r3d = 0x04, 
  terminate = 0x1f,
  // bubble pile manip
  blow = 0x05, 
  sbm = 0x06, 
  pop = 0x07, 
  dupe = 0x08,
  srn = 0x09, 
  merge = 0x0a, 
  // arithemtic
  add = 0x0b, 
  sub = 0x0c,
  mult = 0x0d,
  div = 0x0e,
  count = 0x0f,
  // program flow
  label = 0x10,
  jump = 0x11,
  equals = 0x12,
  less = 0x13,
  greater = 0x14,
};

struct Tokens{
  Opcode m_token;         // each opcode define a token type
  std::uint8_t value;     // value is defined only when the token type expects a parameter,
                          //    otherwise the value is undefined
};

class Lexer{
  public:
    Lexer() = default;

    void AnalyseBinaryIR(){
      while(m_cursor < m_bir.size()){
        Opcode opcode = ReadOpCode(m_cursor);
        switch(opcode){
          // system
          case Opcode::nop:
            m_tokens.push_back(Tokens{.m_token = Opcode::nop});
          // pile manipulation
          case Opcode::blow:
            m_tokens.push_back(Tokens{.m_token = Opcode::blow, .value = ReadBits(m_cursor, 8)});
            break;
          case Opcode::sbm:
            m_tokens.push_back(Tokens{.m_token = Opcode::sbm, .value = ReadBits(m_cursor, 5)});
            break;
          case Opcode::pop:
            m_tokens.push_back(Tokens{.m_token = Opcode::pop});
            break;
          case Opcode::dupe:
            m_tokens.push_back(Tokens{.m_token = Opcode::dupe});
            break;
          case Opcode::srn:
            m_tokens.push_back(Tokens{.m_token = Opcode::srn});
            break;
          case Opcode::merge:
            m_tokens.push_back(Tokens{.m_token = Opcode::merge});
            break;
          // arithmetric
          case Opcode::add:
            m_tokens.push_back(Tokens{.m_token = Opcode::add});
            break;
          case Opcode::sub:
            m_tokens.push_back(Tokens{.m_token = Opcode::sub});
            break;
          case Opcode::mult:
            m_tokens.push_back(Tokens{.m_token = Opcode::mult});
            break;
          case Opcode::div:
            m_tokens.push_back(Tokens{.m_token = Opcode::div});
            break;
          case Opcode::count:
            m_tokens.push_back(Tokens{.m_token = Opcode::count});
            break;
          // program flow
          case Opcode::label:
            m_tokens.push_back(Tokens{.m_token = Opcode::label, .value =ReadBits(m_cursor, 5)});
            break;
          case Opcode::jump:
            m_tokens.push_back(Tokens{.m_token = Opcode::jump, .value = ReadBits(m_cursor, 5)});
            break;
          case Opcode::equals:
            m_tokens.push_back(Tokens{.m_token = Opcode::equals});
            break;
          case Opcode::less:
            m_tokens.push_back(Tokens{.m_token = Opcode::less});
            break;
          case Opcode::greater:
            m_tokens.push_back(Tokens{.m_token = Opcode::greater});
            break;
        }
      }
    }

    Opcode ReadOpCode(std::size_t start){
      // read the initial 5 bit opcode for the instruction and increase cursor position
      std::uint8_t value = 0;
      std::size_t end = start + 5;
      for(std::size_t i = start; i < end; i++){
        value |= m_bir[i];
        value <<= 1;
      }
      m_cursor += 5;
      return static_cast<Opcode>(value);
    }

    std::uint8_t ReadBits(std::size_t start, std::uint8_t bits){
      // read the initial 5 bit opcode for the instruction
      std::uint8_t value = 0;
      std::size_t end = start + bits;
      for(std::size_t i = start; i < end; i++){
        value |= m_bir[i];
        value <<= 1;
      }
      m_cursor += bits;
      return value;
    }

  private:
    std::size_t m_cursor;
    std::vector<std::uint8_t> m_bir; // used as input
    std::vector<Tokens> m_tokens;    // used as output
};

}

#endif
