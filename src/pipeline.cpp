#include "pipeline.hpp"

namespace Awax86{

Pipeline::Pipeline(std::string&& inputName, std::string&& outputName):
  m_awasm{std::move(inputName)},
  m_lexer{},
  m_codegen{std::move(outputName)}
{
  //m_awasm.PrintHexCharacters();
}

Pipeline::Pipeline(std::string&& inputname):
  m_awasm{std::move(inputname)},
  m_lexer{},
  m_codegen{"output.s"}
{
  //m_awasm.PrintHexCharacters();
}

void Pipeline::Run(){
  m_awasm.Convert();
  m_lexer.DestructiveWriteBinaryInputIR(m_awasm.DestructiveGetBinaryIR());
  m_lexer.AnalyseBinaryIR();
  m_codegen.DestructiveWriteTokenIR(m_lexer.DestructiveReadTokens());
  m_codegen.Generate();
}

} // namespace Awax86
