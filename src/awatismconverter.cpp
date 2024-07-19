#include "awatismconverter.hpp"

namespace Awax86{

AwatismConverter::AwatismConverter(std::string&& file_name): 
  m_cursor{0}, m_filename{std::move(file_name)}{
    LoadFile();
}

void AwatismConverter::ConvertAwatismToBinary(){
  while(m_cursor < filebuffer.size()){
    if(m_ib.index == 5){
      m_binary.push_back(m_ib.byte);
      switch(m_ib.byte){
        case Opcode::blow:
          m_binary.push_back(ReadNext8());
          break;
        case Opcode::sbm:   [[fallthrough]];
        case Opcode::srn:   [[fallthrough]];
        case Opcode::label: [[fallthrough]];
        case Opcode::jump:
          m_binary.push_back(ReadNext5());
          break;
      }
      m_ib.index = 0;
    }
    char ch = GetNextCharacter();
    switch(ch){
      case ' ':
        //std::cout << "space character matched" << '\n';
        Match('a'); 
        Match('w'); 
        Match('a'); 
        //std::cout << '0';
        m_binir.push_back(0);
        m_ib.byte <<= 1;
        m_ib.index += 1;
        break;
      case 'a':
        //std::cout << "a character matched" << '\n';
        Match('w'); 
        Match('a');
        break;
      case 'w':
        //std::cout << "w character matched" << '\n';
        Match('a'); 
        //std::cout << '1';
        m_binir.push_back(1);
        m_ib.byte <<= 1;
        m_ib.byte |= 1;
        m_ib.index += 1;
        break;
      default:
        //throw std::runtime_error{"ConvertAwatismToBinary :: Syntax error"};
        break;
    }
  }
}

void AwatismConverter::Match(char ch){
  // procedure which advances the cursor iff there is a match
  if(filebuffer[m_cursor] == ch) m_cursor++;
  //else throw std::runtime_error{"Match :: there is a syntax error here"};
}

char AwatismConverter::GetNextCharacter(){
  if(m_cursor < filebuffer.size()){
    return filebuffer[m_cursor++];
  }
  else{
    //throw std::runtime_error{"Error, our cursor reaches beyond the input file"};
  }
}

std::uint8_t AwatismConverter::ReadNext(std::uint8_t bits){
  // returns a bit packed byte
  std::size_t count = 0;
  std::uint8_t buffer = 0;
  if(bits > m_cursor + filebuffer.size()){
    // we error here
  }
  while(count < bits){
    char ch = GetNextCharacter();
    switch(ch){
      case ' ':
        Match('a'); 
        Match('w'); 
        Match('a'); 
        //std::cout << '0';
        buffer <<= 1;
        break;
      case 'w':
        Match('a'); 
        //std::cout << '1';
        buffer <<= 1;
        buffer |= 1;
        break;
      default:
        //throw std::runtime_error{"ConvertAwatismToBinary :: Syntax error"};
        break;
    }
    count += 1;
  }
  return buffer;
}

void AwatismConverter::PrintBuffer() const{
  for(int i = 0; i < filebuffer.size(); i++){
    std::cout << filebuffer[i];
  }
}

void AwatismConverter::PrintBinaryIR() const{
  for(auto k : m_binir){
    std::cout << static_cast<unsigned>(k);
  }
  std::cout << '\n';
}

}
