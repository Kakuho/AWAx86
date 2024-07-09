#ifndef SEMANTIC_ANALYSER_HPP
#define SEMANTIC_ANALYSER_HPP

/* 
 * Semantic Analyser checks for errors such as popping when there is no bubble at the top of the stack.
 * Goal of the Semantic Analyser is to rewrite the input code for correctness before code gen occurs.
 *
 * Reminder of Lexer Tokens:
 *
 * enum class Tokens : std::uint8_t {
 *  // system 
 *  nop = 0x00, 
 *  print = 0x01, 
 *  pr1nt = 0x02, 
 *  red = 0x03, 
 *  r3d = 0x04, 
 *  terminate = 0x1f,
 *  // bubble pile manip
 *  blow = 0x05, 
 *  sbm = 0x06, 
 *  pop = 0x07, 
 *  dupe = 0x08,
 *  srn = 0x09, 
 *  merge = 0x0a, 
 *  // arithemtic
 *  add = 0x0b, 
 *  sub = 0x0c,
 *  mult = 0x0d,
 *  div = 0x0e,
 *  count = 0x0f,
 *  // program flow
 *  label = 0x10,
 *  jump = 0x11,
 *  equals = 0x12,
 *  less = 0x13,
 *  greater = 0x14,
 *};
 */

#include <vector>
#include <cstdint>

namespace Awa4x86{

class SemanticAnalyser{
  public:
    SemanticAnalyser() = default;

  private:
    std::size_t m_cursor;
    std::vector<Tokens> m_tokens;    // input
};

}

#endif
