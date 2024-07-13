#ifndef AWASSEMBLER_HPP
#define AWASSEMBLER_HPP

// converts the shorthand awatisms into the token intermediate representation

#include <vector>
#include <set>
#include <stdexcept>
#include <fstream>
#include <iostream>

#include "utils/utils.hpp"

namespace Awa4x86{

class Awassembler{
  public:
    // lifetime
    Awassembler(std::string&& filename);
  
  public:
    // operational
    // I assume this is going to be a bunch of DFAs reading input text
    void Convert();
    void Match(char ch);
    char GetNextCharacter();
  private:
    void ParseUntilWhitespace();
    std::string ReadUntilWhitespace();

  public:
    void PrintCharacters();
    void PrintHexCharacters();

  private:
    std::string m_filename;
    std::vector<char> m_inputBuffer;
    std::size_t m_cursor;
    std::vector<std::uint8_t> m_binary;   // the binary representation
    std::set<char> m_wslut;

  private:
      void LoadFile(){
      // procedure to load the ascii bytes to ram
      std::ifstream inputfile{m_filename, std::ios::in | std::ios::ate};
      if(!inputfile){
        throw std::runtime_error{"Input file error"};
      }
      std::size_t filesize = inputfile.tellg();
      // now we place all the bytes into ram
      m_inputBuffer.reserve(filesize);
      m_inputBuffer.resize(filesize);
      inputfile.seekg(0);
      if(!inputfile.read(&m_inputBuffer[0], filesize)){
        throw std::runtime_error{"error reading bytes into vector buffer"};
      }
    }
};

} // namespace Awa4x86

#endif
