#ifndef AWASSEMBLER_HPP
#define AWASSEMBLER_HPP

// converts the shorthand awatisms into the token intermediate 
// representation
//
// Note, this effectively acts as a second frontend for awa5.0 programs.

#include <cstdint>
#include <vector>
#include <set>
#include <stdexcept>
#include <cassert>
#include <fstream>
#include <iostream>

#include "utils/utils.hpp"

namespace Awa4x86{

class Awassembler{
  public:
    // lifetime
    Awassembler(std::string&& filename);
    Awassembler(std::vector<char>&& input);
  
  public:
    // operational
    void Match(char ch);
    void MatchWhitespace();
    char GetNextCharacter();
  private:
    void ParseUntilWhitespace();
    void SkipUntilNewLine();
    std::string ReadDigitsUntilWhitespace();

  public:
    // printing
    void PrintCharacters();
    void PrintHexCharacters();

  public:
    // main driver procedure
    void Convert();
    // after calling this, the class is non functional
    std::vector<std::uint8_t>&& DestructiveGetBinaryIR();

  private:
    // automaton handlers - modeled as DFAs
    //  the implementation of the handlers are listed on the right
    void Handle4(); void Do4dd();
    void HandleB(); void DoBlo(std::int8_t);  // bit pattern coercion?
    void HandleC(); void DoCnt();
    void HandleD(); void DoDiv(); void DoDpl();
    void HandleE(); void DoEql();
    void HandleG(); void DoGr8();
    void HandleJ(); void DoJmp(std::uint8_t);
    void HandleL(); void DoLbl(std::uint8_t); void DoLss();
    void HandleM(); void DoMrg(); void DoMul();
    void HandleN(); void DoNop();
    void HandleP(); void DoPop(); void DoPr1(); void DoPrn();
    void HandleR(); void DoRed(); void DoR3d();
    void HandleS(); void DoSbm(std::uint8_t); void DoSrn(std::uint8_t);
                    void DoSub();
    void HandleT(); void DoTrm();

  private:
    std::string m_filename;
    std::vector<char> m_inputBuffer;
    std::size_t m_cursor;
    std::set<char> m_wslut;
    std::set<char> m_numbers;
    std::vector<std::uint8_t> m_binary;   // the binary representation

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
