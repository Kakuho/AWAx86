#ifndef x86_CODEGEN_hpp
#define x86_CODEGEN_hpp

// hardware code gen layer for x86 architectures.
//
// The code generator assumes it is given tokens from the lexer, and produces x86 code 
// accordingly to the tokens given.
//
// Register Model:
//    R8 = base of the awascii table

#include <fstream>
#include <vector>
#include "tokens.hpp"

namespace Awax86{
  class X86Generator{
    public:
      // lifetimes
      X86Generator(std::string&& outputFileName);
      X86Generator(std::vector<Tokens>&& tokens);
      ~X86Generator();
      void WritePrelude();
      void InitialiseAwascii();
      void DestroyAwascii();
      void WriteConclusion();

    public:
      void IncreaseStackSize(){m_stackSize++;}
      void DecreaseStackSize(){m_stackSize--;}

    public:
      // operational
      void Generate(); // the main boy
      void DestructiveWriteTokenIR(std::vector<Tokens>&& tokens){
        m_tokens = std::move(tokens);
      }

    public:
      // Token handlers
      inline void HandleNoOp() const;
      void HandlePrn();
      void HandleBlo(std::uint8_t u5);
      //void HandleSbm(std::uint8_t u5);  // gotta loop through assembly
      void HandlePop();
      void HandleDpl();
      void HandleSrn();
      void HandleMul();

    private:
      std::string m_outputFilename;
      std::vector<Tokens> m_tokens;
      std::ofstream m_output;
      std::size_t m_stackSize;
  };
} // namespace Awax86

#endif
