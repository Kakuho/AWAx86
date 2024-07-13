#include "awassembler.hpp"

namespace Awa4x86{

Awassembler::Awassembler(std::string&& filename)
  : m_filename{std::move(filename)},
    m_wslut{{' ', '\n', '\r'}}
{
  LoadFile();
}

void Awassembler::Convert(){
  char ch = GetNextCharacter();
  switch(ch){
    case 'j':
      Match('m');
      Match('p');
      Match(' ');
      std::uint8_t value = Convert5BitUnsigned(ReadUntilWhitespace());
      break;
  }
}

void Awassembler::Match(char ch){
  if(m_inputBuffer[m_cursor] == ch){
    m_cursor++;
  }
  else{
    throw std::runtime_error{"Syntax Error;"};
  }
}

char Awassembler::GetNextCharacter(){
  if(m_cursor < m_inputBuffer.size()){
    m_cursor++;
    return m_inputBuffer[m_cursor];
  }
}

void Awassembler::ParseUntilWhitespace(){
  // useful for dealing with new lines
  while(m_wslut.find(m_inputBuffer[m_cursor]) != m_wslut.end()){
    m_cursor++;
  }
}

std::string Awassembler::ReadUntilWhitespace(){
  // useful for some handlers like blow and submerge
  std::string value{};
  value.reserve(20);
  while(m_wslut.find(m_inputBuffer[m_cursor]) != m_wslut.end()){
    m_cursor++;
    value.push_back(m_inputBuffer[m_cursor]);
  }
  return value;
}

// printing 
void Awassembler::PrintCharacters(){
  for(std::size_t i = 0; i < m_inputBuffer.size(); i++){
    std::cout << m_inputBuffer[i] << ' ';
  }
  std::cout << '\n';
}

void Awassembler::PrintHexCharacters(){
  for(std::size_t i = 0; i < m_inputBuffer.size(); i++){
    std::cout << static_cast<unsigned>(m_inputBuffer[i] & 0xFF) << ' ';
  }
  std::cout << '\n';
}

}
