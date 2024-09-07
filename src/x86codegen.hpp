#ifndef x86_CODEGEN_hpp
#define x86_CODEGEN_hpp

//  hardware code gen layer for x86 architectures.
//
//  The code generator assumes it is given tokens from the lexer, and produces x86 code 
//  accordingly to the tokens given.
//
//  Register Model:
//    R8 = base of the awascii table
//
//  Some errors for internal state update when doing lbl and jmp instructions.
//  what if we put the number of elements on the stack in the runtime?

#include <cstdint>
#include <fstream>
#include <stdexcept>
#include <vector>
#include <optional>
#include <variant>
#include <filesystem>
#include <format>

#include "tokens.hpp"
#include "utils/bubblering.hpp"

namespace Awax86{
  class X86Generator{
    enum class BubbleType: std::uint8_t{Single, Double};
    using StackEntry = std::pair<BubbleType, std::uint8_t>;
    struct DoubleBubbleUnimplemented{};
    public:
      //---------------------------------------------------------------//
      // Lifetime:
      //    Conversion Constructors, and functions to start and end the
      //    generated assembly programs.
      //---------------------------------------------------------------//

      X86Generator(std::string&& outputFileName);
      X86Generator(std::vector<Tokens>&& tokens);
      X86Generator(std::vector<Tokens>&& tokens, std::string&& outputFileName);
      ~X86Generator();
      void WritePrelude();
      void WriteConclusion();
      void InitialiseAwascii();
      void DestroyAwascii();

      //---------------------------------------------------------------//
      // Bubblepile stack related:
      //    Functions to get the top bubbles and valuesfrom the bubble
      //    pile stack
      //---------------------------------------------------------------//

      [[nodiscard]] BubbleType TopBubble() const{
        // maybe include safety checks here?
        return m_bubbleStack[m_bubbleStack.size()-1];
      }

      [[nodiscard]] BubbleType GetBubble(std::size_t index) const{
        return m_bubbleStack[index];
      }

      [[nodiscard]] StackEntry TopBubbleSh() const{
        // maybe include safety checks here?
        return m_shadowStack[m_shadowStack.size()-1];
      }

      [[nodiscard]] StackEntry GetBubbleSh(std::size_t index) const{
        return m_shadowStack[index];
      }

      //---------------------------------------------------------------//
      // Operational related:
      //    Functions that faciliates performing internal state updates 
      //    and generating the x86 program. 
      //
      //    Contains functionalities that drives the whole generation process
      //    and stepping through to handle tokens writting and updating one by one.
      //---------------------------------------------------------------//


      [[deprecated]]
      void Generate();                          // the main driver
      [[deprecated]]
      void GenerateNext();

      void Run();                               // Main driver 2
      void WriteToken(std::size_t index);       // only writes
      void UpdateToken(std::size_t index);      // only updates
      void SetTokenIndex(std::size_t index)     {m_tokenIndex = index;}
      void DestructiveWriteTokenIR(std::vector<Tokens>&& tokens){
        m_tokens = std::move(tokens);
      }
      void SkipNextToken(){}

      //---------------------------------------------------------------//
      // Token handlers:
      //    The idea is to split functions for writting to file io and updating
      //    internal state, to allow more of a modular design.
      //    
      //    Update functions are fairly small, so I made them inline.
      //---------------------------------------------------------------//

      // System related
      //---------------------------------------------------------------//
      
      inline void HandleNoOp() const;
      // Prn
      void HandlePrn();
      void WritePrn(); 
      inline void UpdatePrn();  

      // Bubble Pile manipulation
      //---------------------------------------------------------------//

      // Blow
      [[deprecated]]
      void HandleBlo(std::uint8_t){};

      void WriteBlo(std::uint8_t u5); 
      inline void UpdateBlo(std::uint8_t u5);

      //void HandleSbm(std::uint8_t u5);  // gotta loop through assembly

      // Pop
      [[deprecated]]
      void HandlePop();
      void WritePop(); 
      inline void UpdatePop();

      // Dpl
      [[deprecated]]
      void HandleDpl();
      void WriteDpl(); 
      inline void UpdateDpl();

      //void HandleSrn();   // remove
      void HandleMrg();     // remove

      // Arithmetic
      //---------------------------------------------------------------//

      void HandleAdd(); // remove
      void HandleSub(); // remove
                        
      // Mul
      [[deprecated]]
      void HandleMul();
      void WriteMul(); 
      inline void UpdateMul();

      void HandleDiv(); // remove
      //void HandleCnt(); // remove
      
      // Control Flow
      //---------------------------------------------------------------//
      [[nodiscard]] bool IsControlflow(std::size_t index);

      void HandleLbl(std::uint8_t u5);    // remove
      void HandleJmp(std::uint8_t u5);    // remove
      // Equals
      void HandleEql();
      void WriteEql();
      void UpdateEql();

    private:
      std::string m_outputFilename;
      std::vector<Tokens> m_tokens;
      std::ofstream m_output;
      // i kinda want to maintain a single stack tho :/
      std::vector<BubbleType> m_bubbleStack;
      std::vector<std::pair<BubbleType, std::uint8_t>> m_shadowStack;
      std::size_t m_tokenIndex;
      BubbleRing<2> m_cache;  // a lru cache for the last two elements
      bool withinControlFlow = false;
      std::size_t labelIndex;
  };

} // namespace Awax86

#endif
