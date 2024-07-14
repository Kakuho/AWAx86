#ifndef LEXER_HPP
#define LEXER_HPP

// The lexer assumes that the program is in a binary intermediate 
// representation, and generates tokens according to the binary IR.

#include <vector>
#include <cstdint>

#include "tokens.hpp"

namespace Awa4x86{

class Lexer{
  public:
    // lifetime
    Lexer();

  public:
    // operational
    std::uint8_t ReadByte();
    void AnalyseBinaryIR();
    std::vector<Tokens>&& DestructiveReadTokens(){ return std::move(m_tokens); }

  private:
    std::size_t m_cursor;
    std::vector<std::uint8_t> m_binary; // the binary ir
    std::vector<Tokens> m_tokens;    // used as output
};

}

#endif
