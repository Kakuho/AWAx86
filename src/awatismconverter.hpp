#include <stdexcept>
#include <vector>
#include <cstdint>
#include <fstream>
#include <iostream>

namespace Awa4x86{

class InputBuffer{
  InputBuffer(std::string&& input): m_buffer{std::move(input)}
  {
  };
  std::string m_buffer;
};

class AwatismConverter{
  // class AwatismConverter is a helper class to convert awatisms 
  // to a binary intermediate representation. 
  //
  // this makes it easier for the lexer to perform token generation.
  public:
    AwatismConverter(std::string&& file_name): 
      m_cursor{0}, m_filename{std::move(file_name)}{
        LoadFile();
    }

    void ConvertAwatismToBinary(){
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

    void Match(char ch){
      // procedure which advances the cursor iff there is a match
      if(filebuffer[m_cursor] == ch) m_cursor++;
      //else throw std::runtime_error{"Match :: there is a syntax error here"};
    }

    char GetNextCharacter(){
      if(m_cursor < filebuffer.size()){
        return filebuffer[m_cursor++];
      }
      else{
        //throw std::runtime_error{"Error, our cursor reaches beyond the input file"};
      }
    }

    void PrintBuffer(){
      for(int i = 0; i < filebuffer.size(); i++){
        std::cout << filebuffer[i];
      }
    }

    void PrintBinaryIR(){
      for(auto k : m_binir){
        std::cout << static_cast<unsigned>(k);
      }
      std::cout << '\n';
    }

  private:
    std::string m_filename;
    std::vector<char> filebuffer;
    std::size_t m_cursor;
    std::vector<std::uint8_t> m_binir;

  private:
    void LoadFile(){
      std::ifstream inputfile{m_filename, std::ios::in | std::ios::ate};
      if(!inputfile){
        throw std::runtime_error{"Input file error"};
      }
      std::size_t filesize = inputfile.tellg();
      // now we place all the bytes into ram
      filebuffer.reserve(filesize);
      filebuffer.resize(filesize);
      inputfile.seekg(0);
      if(!inputfile.read(&filebuffer[0], filesize)){
        throw std::runtime_error{"error reading bytes into vector buffer"};
      }
    }
};

}
