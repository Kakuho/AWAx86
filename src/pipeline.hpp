#ifndef PIPELINE_HPP
#define PIPELINE_HPP

// Pipeline class represents the compiler pipeline, a sequence of passes where the output of one pass is used as the
// input to another pass.

#include "awassembler.hpp"
#include "lexer.hpp"
#include "x86codegen.hpp"

namespace Awax86{
  class Pipeline{
    public:
      Pipeline(std::string&& inputname, std::string&& outputName);
      Pipeline(std::string&& inputname);
      void Run();
    private:
      Awassembler m_awasm;
      Lexer m_lexer;
      X86Generator m_codegen;
      std::string m_inputName;
      std::string m_outputName;
  };
}

#endif
