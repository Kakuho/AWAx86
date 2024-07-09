#ifndef CODEGEN_HPP
#define CODEGEN_HPP
#include <vector>
#include "lexer.hpp"

// We need to define a model of computation which maps the bubble 
// model of AWA to x86 Register based model.
//
// I choose to do the following:
// Stack represents our abyss

namespace Awa4x86{
  class CodeGenerator{
    public:
      void HandleNop(){

      }

      void HandleBlow(){

      }
    private:
      std::vector<Tokens> m_input;
  };
}
#endif
