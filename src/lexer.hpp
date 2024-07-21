#ifndef LEXER_HPP
#define LEXER_HPP

// The lexer assumes that the program is in a binary intermediate 
// representation, and generates tokens according to the binary IR.

#include <vector>
#include <cstdint>

#include "tokens.hpp"

namespace Awax86{

class Lexer{
  public:
    // lifetime
    Lexer();
    Lexer(std::vector<std::uint8_t>&& input);

  public:
    // operational
    std::uint8_t ReadByte();
    void AnalyseBinaryIR();
    void DestructiveWriteBinaryInputIR(std::vector<std::uint8_t>&& binary){
      m_binary = std::move(binary);
    }
    std::vector<Tokens>&& DestructiveReadTokens(){ return std::move(m_tokens); }

  private:
    std::size_t m_cursor;
    std::vector<std::uint8_t> m_binary; // the binary ir
    std::vector<Tokens> m_tokens;    // used as output
};

}

#endif
