#include "x86codegen.hpp"
#include <stdexcept>

namespace Awax86{

//---------------------------------------------------------------//
// Lifetime
//---------------------------------------------------------------//

X86Generator::X86Generator(std::string&& outputFileName):
  m_outputFilename{std::move(outputFileName)},
  m_output{m_outputFilename},
  m_stackSize{0}
{
  WritePrelude();
  InitialiseAwascii();
}

// ctor mostly for testing
X86Generator::X86Generator(std::vector<Tokens>&& tokens):
  m_tokens{std::move(tokens)},
  m_output{"./out/output.s"},
  m_stackSize{0}
{
  WritePrelude();
  InitialiseAwascii();
}

X86Generator::~X86Generator(){
  DestroyAwascii();
  WriteConclusion();
}

void X86Generator::WritePrelude(){
  m_output << ".section .data\n"
           << ".section .text\n"
           << ".globl main\n\n"
           << "main:\n"
           // start of the stack frame
           << "pushq   %rbp\n"
           << "movq    %rsp, %rbp\n"
           // I will use %rax as the current stackframe pointer
           << "movq    %rsp, %rax\n";
}

void X86Generator::InitialiseAwascii(){
  // we place the awascii table onto stack at start up
  m_output << ".initialiseAwascii:\n"
           << "subq $64, %rsp\n"
           // the elements of the hashing table itself
           << "movb $65, -1(%rbp)\n"    // A
           << "movb $87, -2(%rbp)\n"    // W
           << "movb $97, -3(%rbp)\n"    // a
           << "movb $119, -4(%rbp)\n"   // w
           << "movb $74, -5(%rbp)\n"    // J
           << "movb $69, -6(%rbp)\n"    // E
           << "movb $76, -7(%rbp)\n"    // L
           << "movb $89, -8(%rbp)\n"    // Y
           << "movb $72, -9(%rbp)\n"    // H
           << "movb $79, -10(%rbp)\n"   // O
           << "movb $83, -11(%rbp)\n"   // S
           << "movb $73, -12(%rbp)\n"   // I
           << "movb $85, -13(%rbp)\n"   // U
           << "movb $77, -14(%rbp)\n"   // M
           << "movb $106, -15(%rbp)\n"  // j
           << "movb $101, -16(%rbp)\n"  // e
           << "movb $108, -17(%rbp)\n"  // l
           << "movb $121, -18(%rbp)\n"  // y
           << "movb $104, -19(%rbp)\n"  // h
           << "movb $111, -20(%rbp)\n"  // o
           << "movb $115, -21(%rbp)\n"  // s
           << "movb $105, -22(%rbp)\n"  // i
//---------------------------------------------------------------//
           << "movb $117, -23(%rbp)\n"  // u
           << "movb $109, -24(%rbp)\n"  // m
           << "movb $80, -25(%rbp)\n"   // P
           << "movb $67, -26(%rbp)\n"   // C
           << "movb $78, -27(%rbp)\n"   // N
           << "movb $84, -28(%rbp)\n"   // T
           << "movb $112, -29(%rbp)\n"  // p
           << "movb $99, -30(%rbp)\n"   // c
           << "movb $110, -31(%rbp)\n"  // n
           << "movb $116, -32(%rbp)\n"  // t
           << "movb $66, -33(%rbp)\n"   // B
           << "movb $68, -34(%rbp)\n"   // D
           << "movb $70, -35(%rbp)\n"   // F
           << "movb $71, -36(%rbp)\n"   // G
           << "movb $82, -37(%rbp)\n"   // R
           << "movb $98, -38(%rbp)\n"   // b
           << "movb $100, -39(%rbp)\n"  // d
           << "movb $102, -40(%rbp)\n"  // f
           << "movb $103, -41(%rbp)\n"  // g
           << "movb $114, -42(%rbp)\n"  // r
           << "movb $48, -43(%rbp)\n"   // 0
           << "movb $49, -44(%rbp)\n"   // 1
//---------------------------------------------------------------//
           << "movb $50, -45(%rbp)\n"   // 2
           << "movb $51, -46(%rbp)\n"   // 3
           << "movb $52, -47(%rbp)\n"   // 4
           << "movb $53, -48(%rbp)\n"   // 5
           << "movb $54, -49(%rbp)\n"   // 6
           << "movb $55, -50(%rbp)\n"   // 7
           << "movb $56, -51(%rbp)\n"   // 8
           << "movb $57, -52(%rbp)\n"   // 9
           << "movb $32, -53(%rbp)\n"   // ' '
           << "movb $46, -54(%rbp)\n"   // .
           << "movb $44, -55(%rbp)\n"   // ,
           << "movb $33, -56(%rbp)\n"   // !
           << "movb $39, -57(%rbp)\n"   // '
           << "movb $40, -58(%rbp)\n"   // (
           << "movb $41, -59(%rbp)\n"   // )
           << "movb $126, -60(%rbp)\n"  // ~
           << "movb $95, -61(%rbp)\n"   // _
           << "movb $47, -62(%rbp)\n"   // /
           << "movb $58, -63(%rbp)\n"   // :
           << "movb $10, -64(%rbp)\n"   // '\n'
//---------------------------------------------------------------//
           << ".program_start:\n";

}

void X86Generator::DestroyAwascii(){
  // we place the awascii table onto stack at start up
  m_output << ".destroyAwascii:\n"
           << "addq $64, %rsp\n";
}

void X86Generator::WriteConclusion(){
  if(auto stackSize = m_bubbleStack.size(); stackSize > 0){
    m_output << "xorq %rax, %rax" << '\n'
             << "movq $" << static_cast<unsigned>(stackSize) << ", %rax" << '\n'
             << "movq $8, %rsi" << '\n'
             << "mulq %rsi"   << '\n'
             << "addq %rax, %rsp" << '\n';
  }
  /*
  while(m_stackSize > 0){
    // i shall use r15 as my dumpster shoot
    m_output << "pop %r15\n";
    DecreaseStackSize();
  }
  */
  m_output << "pop %rbp\n"
           << "ret\n";
}

//---------------------------------------------------------------//
// Operational
//---------------------------------------------------------------//

void X86Generator::Generate(){
  for(auto& token: m_tokens){
    Opcode opcode = token.m_token;
    switch(opcode){
      case nop:
        HandleNoOp();
        break;
      case print:
        HandlePrn();
        break;
      case blow:
        HandleBlo(token.value);
        break;
      /*
      case sbm:
        HandleSbm(token.value);
        break;
       */
      case pop:
        HandlePop();
        break;
      case dupe:
        HandleDpl();
        break;
      case mult:
        HandleMul();
        break;
      default:
        throw std::runtime_error{"Codegen error: Unknown Token"};
    }
  }
}

//---------------------------------------------------------------//
// Token Handlers
//---------------------------------------------------------------//

void X86Generator::HandleNoOp() const{
  // literally does nothing
  return;
}

void X86Generator::HandlePrn(){
  // pop the top most bubble and print it
  //  todo: handle double bubbles
  m_output << "popq %rsi" << '\n' 
           << "neg %rsi"  << '\n'
           << "subq $1, %rsi"  << '\n'
           << "movq (%rbp, %rsi), %rdi" << '\n'
           << "call putchar" << '\n';
  m_bubbleStack.pop_back();
}

void X86Generator::HandleBlo(std::uint8_t u5){
  // blow a bubble onto the bubble stack
  m_output << "pushq $" << static_cast<unsigned>(u5&0x1FF) << '\n';
  m_bubbleStack.push_back(BubbleType::Single);
  IncreaseStackSize();
}

/*
void X86Generator::HandleSbm(std::uint8_t u5){
  // submerge the top of the bubble stack down x positions, where
  // x is a unsigned 5 bit intger
  m_output << "pushq $" << static_cast<unsigned>(u5&0x1FF) << '\n';
  IncreaseStackSize();
}
*/

void X86Generator::HandlePop(){
  // pops the top most bubble
  auto toptype = TopBubble();
  if(toptype == BubbleType::Single){
    m_output << "popq %r15" << '\n';
  }
  else{
    //  todo: handle double bubbles
    //        we will need to deallacote ( call free() ) from the top most double bubble
    throw std::runtime_error{
      std::format("X86Generator::HandlePop()::Double bubble not implemented")
    };
  }
  m_bubbleStack.pop_back();
  DecreaseStackSize();
}

void X86Generator::HandleDpl(){
  // duplicate the top most bubble
  auto toptype = TopBubble();
  if(toptype == BubbleType::Single){
    m_output << "pushq (%rsp)" << '\n';
  }
  else{
    //  todo: handle double bubbles - implement deep copy 
    throw std::runtime_error{
      std::format("X86Generator::HandleDpl()::Double bubble not implemented")
    };
  }
  m_bubbleStack.push_back(toptype);
  IncreaseStackSize();
}

void X86Generator::HandleSrn(){
  // surrounds the top most x integers as a double bubble
  m_output << "pushq (%rsp)" << '\n';
  IncreaseStackSize();
}

void X86Generator::HandleMrg(){
  using enum BubbleType;
  BubbleType top = TopBubble();
  BubbleType second = GetBubble(m_bubbleStack.size() - 2);
  if((top == Single) && (second == Single)){
    // we essentially perform a surround but with two elements
    throw std::runtime_error{
      std::format("X86Generator::HandleMrg()::(Single, Single) bubble not implemented")
    };
  }
  else if(top == Double){
    // allocate a double bubble here
    throw std::runtime_error{
      std::format("X86Generator::HandleMrg()::(Single, Double) bubble not implemented")
    };
  }
  else if(second == Double){
    // allocate a double bubble here
    throw std::runtime_error{
      std::format("X86Generator::HandleMrg()::(Double, Single) bubble not implemented")
    };
  }
  else{
    throw std::runtime_error{
      std::format("X86Generator::HandleMrg()::(Double, Double) bubble not implemented")
    };
  }
}

void X86Generator::HandleAdd(){
  using enum BubbleType;
  BubbleType top = TopBubble();
  BubbleType second = GetBubble(m_bubbleStack.size() - 2);
  m_bubbleStack.pop_back();
  m_bubbleStack.pop_back();
  if((top == Single) && (second == Single)){
    // Single, Single
    m_output << "popq %rsi" << '\n' 
             << "popq %rax" << '\n'
             << "addq %rsi, %rax" << '\n'
             << "pushq %rax" << '\n';
    m_bubbleStack.push_back(Single);
  }
  else if(top == Double){
    // (Double, Single)
    throw std::runtime_error{
      std::format("X86Generator::HandleAdd()::(Double, Single) bubble not implemented")
    };
  }
  else if(second == Double){
    // (Single, Double)
    throw std::runtime_error{
      std::format("X86Generator::HandleAdd()::(Single, Double) bubble not implemented")
    };
  }
  else{
    // (Double, Double)
    // we need to figure out how long each of the double bubbles are
    throw std::runtime_error{
      std::format("X86Generator::HandleAdd()::(Double, Double) bubble not implemented")
    };
  }
}

void X86Generator::HandleSub(){
  using enum BubbleType;
  // prelude
  BubbleType top = TopBubble();
  BubbleType second = GetBubble(m_bubbleStack.size() - 2);
  m_bubbleStack.pop_back();
  m_bubbleStack.pop_back();
  // case analysis
  if((top == Single) && (second == Single)){
    // Single, Single
    m_output << "popq %rsi" << '\n' 
             << "popq %rax" << '\n'
             << "subq %rsi, %rax" << '\n'
             << "pushq %rax" << '\n';
    m_bubbleStack.push_back(Single);
  }
  else if(top == Double){
    // (Double, Single)
    throw std::runtime_error{
      std::format("X86Generator::HandleAdd()::(Double, Single) bubble not implemented")
    };
  }
  else if(second == Double){
    // (Single, Double)
    throw std::runtime_error{
      std::format("X86Generator::HandleAdd()::(Single, Double) bubble not implemented")
    };
  }
  else{
    // (Double, Double)
    // we need to figure out how long each of the double bubbles are
    throw std::runtime_error{
      std::format("X86Generator::HandleAdd()::(Double, Double) bubble not implemented")
    };
  }
}

void X86Generator::HandleMul(){
  // take the two top most registers, pop it off the bubble stack,
  // multiply, and store the result back onto the bubble stack
  using enum BubbleType;
  // prelude
  BubbleType top = TopBubble();
  BubbleType second = GetBubble(m_bubbleStack.size() - 2);
  m_bubbleStack.pop_back();
  m_bubbleStack.pop_back();
  // case analysis
  if((top == Single) && (second == Single)){
    // Single, Single
    m_output << "popq %rsi" << '\n'
             << "popq %rax" << '\n'
             << "mulq %rsi" << '\n'
             << "pushq %rax" << '\n';
    m_bubbleStack.push_back(Single);
    //DecreaseStackSize();
  }
  else if(top == Double){
    // (Double, Single)
    throw std::runtime_error{
      std::format("X86Generator::HandleMul()::(Double, Single) bubble not implemented")
    };
  }
  else if(second == Double){
    // (Single, Double)
    throw std::runtime_error{
      std::format("X86Generator::HandleMul()::(Single, Double) bubble not implemented")
    };
  }
  else{
    // (Double, Double)
    // we need to figure out how long each of the double bubbles are
    throw std::runtime_error{
      std::format("X86Generator::HandleMul()::(Double, Double) bubble not implemented")
    };
  }
}

} // namespace Awax86
