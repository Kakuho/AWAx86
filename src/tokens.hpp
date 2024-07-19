#ifndef TOKENS_HPP
#define TOKENS_HPP

#include <cstdint>

namespace Awax86{

// lexer tokens
//  purposefully enum and not enumclass, as it represents integral constants
enum Opcode : std::uint8_t {
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
  std::uint8_t value;     // value is defined only when the token type 
                          // expects a parameter, otherwise the value is 
                          // undefined
};

}

#endif 
