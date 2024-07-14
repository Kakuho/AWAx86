#ifndef AWATISM_CONVERTER_HPP
#define AWATISM_CONVERTER_HPP

// AwatismConverter is a helper class to convert awatalk
// to a binary intermediate representation.
//
// The aim is to make it easier for the lexer to perform token generation.

#include <stdexcept>
#include <vector>
#include <cstdint>
#include <fstream>
#include <iostream>

#include "tokens.hpp"

namespace Awa4x86{

struct IndexerByte{
  std::uint8_t byte{0};
  std::uint8_t index{0};
};

class AwatismConverter{
  public:
    AwatismConverter(std::string&& file_name);

  public:
    // operational functions
    void ConvertAwatismToBinary();
    void Match(char ch);
    char GetNextCharacter();
    std::uint8_t ReadNext(std::uint8_t bits);
    std::uint8_t ReadNext5(){return ReadNext(5);}
    std::uint8_t ReadNext8(){return ReadNext(8);}
    std::vector<std::uint8_t>&& DestructiveGetBinary(){return std::move(m_binary);}

  public:
    // Printing functions
    void PrintBuffer() const;
    void PrintBinaryIR() const;

  private:
    std::string m_filename;
    std::vector<char> filebuffer;
    std::size_t m_cursor;
    std::vector<std::uint8_t> m_binir;
    std::vector<std::uint8_t> m_binary;
    IndexerByte m_ib;

  private:
    void LoadFile(){
      // procedure to load the ascii bytes to ram
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

#endif
