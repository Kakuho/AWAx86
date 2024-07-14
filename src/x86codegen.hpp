#ifndef x86_CODEGEN_hpp
#define x86_CODEGEN_hpp

// hardware code gen layer for x86 architectures.
//
// The code generator assumes it is given tokens from the lexer, and produces x86 code 
// accordingly to the tokens given.

#include <fstream>

namespace Awa4x86{
  class X86Generator{
    public:
      // lifetimes
      X86Generator() = default;
      void WritePrelude();
      void WriteConclusion();

    public:
      // token handling functions

      inline void HandleNoOp(){
        return; // hope to god you dont do anything
      }

    private:
      std::ofstream m_outputfile;
  };
};

#endif
