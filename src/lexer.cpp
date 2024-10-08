#include "lexer.hpp"
#include <vector>

namespace Awax86{

//---------------------------------------------------------------//
// Lifteime
//---------------------------------------------------------------//

Lexer::Lexer()
  : m_cursor{0}
{

}

Lexer::Lexer(std::vector<std::uint8_t>&& input): 
  m_cursor{0},
  m_binary{std::move(input)}
{

}

//---------------------------------------------------------------//
// Operational
//---------------------------------------------------------------//

std::uint8_t Lexer::ReadByte(){
  return m_binary[m_cursor++];
}

void Lexer::AnalyseBinaryIR(){
  while(m_cursor < m_binary.size()){
    Opcode opcode = static_cast<Opcode>(ReadByte());
    switch(opcode){
      // system
      case Opcode::nop:
        m_tokens.push_back(Tokens{.m_token = Opcode::nop});
        break;
      case Opcode::print:
        m_tokens.push_back(Tokens{.m_token = Opcode::print});
        break;
      case Opcode::pr1nt:
        m_tokens.push_back(Tokens{.m_token = Opcode::pr1nt});
        break;
      case Opcode::red:
        m_tokens.push_back(Tokens{.m_token = Opcode::red});
        break;
      case Opcode::r3d:
        m_tokens.push_back(Tokens{.m_token = Opcode::r3d});
        break;
      case Opcode::terminate:
        m_tokens.push_back(Tokens{.m_token = Opcode::terminate});
        break;
      // pile manipulation
      case Opcode::blow:
        m_tokens.push_back(Tokens{.m_token = Opcode::blow, .value = ReadByte()});
        break;
      case Opcode::sbm:
        m_tokens.push_back(Tokens{.m_token = Opcode::sbm, .value = ReadByte()});
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
        m_tokens.push_back(Tokens{.m_token = Opcode::label, .value = ReadByte()});
        break;
      case Opcode::jump:
        m_tokens.push_back(Tokens{.m_token = Opcode::jump, .value = ReadByte()});
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

} // namespace Awa4x86
