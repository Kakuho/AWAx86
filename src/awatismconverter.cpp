#include "awatismconverter.hpp"

namespace Awa4x86{

AwatismConverter::AwatismConverter(std::string&& file_name): 
  m_cursor{0}, m_filename{std::move(file_name)}{
    LoadFile();
}

void AwatismConverter::ConvertAwatismToBinary(){
  while(m_cursor < filebuffer.size()){
    char ch = GetNextCharacter();
    switch(ch){
      case ' ':
        //std::cout << "space character matched" << '\n';
        Match('a'); 
        Match('w'); 
        Match('a'); 
        //std::cout << '0';
        m_binir.push_back(0);
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
