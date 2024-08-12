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
#include <stdexcept>
#include <vector>
#include <utility>
#include <variant>
#include <format>

#include "tokens.hpp"

namespace Awax86{
  class X86Generator{
    enum class BubbleType: std::uint8_t{Single, Double};
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
      // bubble stack related
      [[nodiscard]] BubbleType TopBubble() const{
        // maybe include safety checks here?
        return m_bubbleStack[m_bubbleStack.size()-1];
      }
      [[nodiscard]] BubbleType GetBubble(std::size_t index) const{
        return m_bubbleStack[index];
      }
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
      void HandleMrg();
      void HandleAdd();
      void HandleSub();
      void HandleMul();

    private:
      //using StackEntry = std::pair<BubbleType, std::variant<>;
      std::string m_outputFilename;
      std::vector<Tokens> m_tokens;
      std::ofstream m_output;
      std::vector<BubbleType> m_bubbleStack;
      std::size_t m_stackSize;
  };
} // namespace Awax86

#endif
