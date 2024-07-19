#include "awassembler.hpp"
#include <stdexcept>

namespace Awax86{

Awassembler::Awassembler(std::string&& filename)
  : m_filename{std::move(filename)},
    m_cursor{0},
    m_wslut{{' ', '\n', '\r'}},
    m_numbers{{'-', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'}}
{
  m_binary.reserve(50);
  LoadFile();
}


Awassembler::Awassembler(std::vector<char>&& input)
  : m_inputBuffer{std::move(input)},
    m_cursor{0},
    m_wslut{{' ', '\n', '\r'}},
    m_numbers{{'-', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'}}
{
  m_binary.reserve(50);
}

//---------------------------------------------------------------//
// operational
//---------------------------------------------------------------//

void Awassembler::Match(char ch){
  if(m_inputBuffer[m_cursor] == ch){
    //std::cout << "matched " << ch << '\n';
    m_cursor++;
  }
  else{
    throw std::runtime_error{"Syntax Error;"};
  }
}

void Awassembler::MatchWhitespace(){
  bool isWhitespace = m_wslut.find(m_inputBuffer[m_cursor]) != 
    m_wslut.end();
  if(isWhitespace){
    //std::cout << "matched isWhitespace" << '\n';
    m_cursor++;
  }
  else{
    throw std::runtime_error{"Syntax Error; Whitespace is not matched"};
  }
}

char Awassembler::GetNextCharacter(){
  if(m_cursor == 0){
    return m_inputBuffer[m_cursor];
  }
  if(m_cursor < m_inputBuffer.size()){
    m_cursor++;
    return m_inputBuffer[m_cursor];
  }
}

void Awassembler::ParseUntilWhitespace(){
  // useful for dealing with new lines
  while(m_wslut.find(m_inputBuffer[m_cursor]) != m_wslut.end()){
    m_cursor++;
  }
}

void Awassembler::SkipUntilNewLine(){
  while(m_inputBuffer[m_cursor] != '\n'){
    m_cursor++;
  }
}

std::string Awassembler::ReadDigitsUntilWhitespace(){
  // useful for some handlers like blow and submerge
  std::string value{};
  value.reserve(20);
  while(m_numbers.find(m_inputBuffer[m_cursor]) != m_numbers.end()){
    value.push_back(m_inputBuffer[m_cursor]);
    m_cursor++;
  }
  //std::cout << "digits: " << value << '\n';
  return value;
}

//---------------------------------------------------------------//
// printing 
//---------------------------------------------------------------//

void Awassembler::PrintCharacters(){
  for(std::size_t i = 0; i < m_inputBuffer.size(); i++){
    std::cout << m_inputBuffer[i] << ' ';
  }
  std::cout << '\n';
}

void Awassembler::PrintHexCharacters(){
  for(std::size_t i = 0; i < m_inputBuffer.size(); i++){
    std::cout << static_cast<unsigned>(m_inputBuffer[i] & 0xFF) << ' ';
  }
  std::cout << '\n';
}


//---------------------------------------------------------------//
// main driver procedure
//---------------------------------------------------------------//

void Awassembler::Convert(){
  while(m_cursor < m_inputBuffer.size() - 1){
    char ch = GetNextCharacter();
    switch(ch){
      // automaton starters
      case '4':
        Handle4();
        break;
      case 'b':
        HandleB();
        break;
      case 'c':
        HandleC();
        break;
      case 'd':
        HandleD();
        break;
      case 'e':
        HandleE();
        break;
      case 'g':
        HandleG();
        break;
      case 'j':
        HandleJ();
        break;
      case 'l':
        HandleL();
        break;
      case 'm':
        HandleM();
        break;
      case 'n':
        HandleN();
        break;
      case 'p':
        HandleP();
        break;
      case 'r':
        HandleR();
        break;
      case 's':
        HandleS();
        break;
      case 't':
        HandleT();
        break;
      // for comments in awassembly
      case '\\':
      case '/':
        SkipUntilNewLine();
        break;
      // on any whitespace we fall through until we hit the whitespace 
      // handler
      case '\r':
        [[fallthrough]];
      case '\n':
        [[fallthrough]];
      case ' ':
        [[fallthrough]];
      case '\t':
        ParseUntilWhitespace();
        m_cursor -= 1;
        break;
    }
  }
}

//---------------------------------------------------------------//
// automaton handlers
//---------------------------------------------------------------//

// automaton handler template:
//  we first see if the corresponding text matches
//  when we pass the matching tests, we produce the IR
//  (i still haven't decided to write the IR to a binary rep or
//   to write it directly to a lexical rep)
//  
//  on a fail, we throw a syntax error.

void Awassembler::Handle4(){
  Match('4');
  Match('d');
  Match('d');
  MatchWhitespace();
  // actual work
  Do4dd();
}

void Awassembler::HandleB(){
  Match('b');
  Match('l');
  Match('o');
  MatchWhitespace();
  std::uint8_t value = 
    Convert8BitSigned(ReadDigitsUntilWhitespace());
  DoBlo(value);
}

void Awassembler::HandleC(){
  Match('c');
  Match('n');
  Match('t');
  MatchWhitespace();
  // actual work
  DoCnt();
}

void Awassembler::HandleD(){
  // this requires a switch case
  Match('d');
  m_cursor--;
  char next = GetNextCharacter();
  switch(next){
    case 'i':
      Match('i');
      Match('v');
      MatchWhitespace();
      // actual work
      DoDiv();
      break;
    case 'p':
      Match('p');
      Match('l');
      MatchWhitespace();
      // actual work
      DoDpl();
      break;
    default:
      throw std::runtime_error{"syntax error, unrecoginsable chaarcter after d"};
  }
}

void Awassembler::HandleE(){
  Match('e');
  Match('q');
  Match('l');
  MatchWhitespace();
  DoEql();
}

void Awassembler::HandleG(){
  Match('g');
  Match('r');
  Match('8');
  MatchWhitespace();
  DoGr8();
}

void Awassembler::HandleJ(){
  Match('j');
  Match('m');
  Match('p');
  MatchWhitespace();
  std::uint8_t value = 
    Convert5BitUnsigned(ReadDigitsUntilWhitespace());
  DoJmp(value);
}

void Awassembler::HandleL(){
  Match('l');
  m_cursor--;
  char next = GetNextCharacter();
  switch(next){
    case 'b':
      {
        Match('b');
        Match('l');
        MatchWhitespace();
        std::uint8_t value = 
          Convert5BitUnsigned(ReadDigitsUntilWhitespace());
        DoLbl(value);
        break;
      }
    case 's':
      Match('s');
      Match('s');
      MatchWhitespace();
      DoLss();
      break;
  }
}

void Awassembler::HandleM(){
  Match('m');
  m_cursor--;
  char next = GetNextCharacter();
  switch(next){
    case 'r':
      Match('r');
      Match('g');
      MatchWhitespace();
      DoMrg();
      break;
    case 'u':
      Match('u');
      Match('l');
      MatchWhitespace();
      DoMul();
      break;
  }
}

void Awassembler::HandleN(){
  Match('n');
  Match('o');
  Match('p');
  MatchWhitespace();
  DoNop();
}

void Awassembler::HandleP(){
  Match('p');
  m_cursor--;
  char next = GetNextCharacter();
  switch(next){
    case 'o':
      Match('o');
      Match('p');
      MatchWhitespace();
      DoPop();
      break;
    case 'r':
      {
        Match('r');
        m_cursor--;
        char next = GetNextCharacter();
        switch(next){
          case '1':
            Match('1');
            MatchWhitespace();
            DoPr1();
            break;
          case 'n':
            Match('n');
            MatchWhitespace();
            DoPrn();
            break;
        }
      }
  }
}

void Awassembler::HandleR(){
  Match('r');
  m_cursor--;
  char next = GetNextCharacter();
  switch(next){
    case 'e':
      Match('e');
      Match('d');
      MatchWhitespace();
      DoRed();
      break;
    case '3':
      Match('3');
      Match('d');
      MatchWhitespace();
      DoR3d();
      break;
  }
}

void Awassembler::HandleS(){
  Match('s');
  m_cursor--;
  char next = GetNextCharacter();
  switch(next){
    case 'b':
      {
        Match('b');
        Match('m');
        MatchWhitespace();
        std::uint8_t value = Convert5BitUnsigned(ReadDigitsUntilWhitespace());
        DoSbm(value);
        break;
      }

    case 'r':
      {
        Match('r');
        Match('n');
        MatchWhitespace();
        std::uint8_t value = Convert5BitUnsigned(ReadDigitsUntilWhitespace());
        DoSrn(value);
        break;
      }
    case 'u':
        Match('u');
        Match('b');
        DoSub();
        break;
  }
}

void Awassembler::HandleT(){
  Match('t');
  Match('r');
  Match('m');
  MatchWhitespace();
  DoTrm();
}

//---------------------------------------------------------------//
// opcode implementations
//---------------------------------------------------------------//

void Awassembler::Do4dd(){
  m_binary.push_back(0x0b);
}

void Awassembler::DoBlo(std::int8_t s8){
  m_binary.push_back(0x5);
  m_binary.push_back(s8);  // i hope you push the bit pattern rep
}

void Awassembler::DoCnt(){
  m_binary.push_back(0x0F);
}

void Awassembler::DoDiv(){
  m_binary.push_back(0x0E);
}

void Awassembler::DoDpl(){
  m_binary.push_back(0x08);
}

void Awassembler::DoEql(){
  m_binary.push_back(0x12);
}

void Awassembler::DoGr8(){
  m_binary.push_back(0x14);
}

void Awassembler::DoJmp(std::uint8_t u5){
  try{
    Check5BitUnsigned(u5);
  }
  catch(std::runtime_error e){
    throw std::runtime_error{"Internal Error: DoJmp did not recieve a 5 bit unsigned"};
  }

  m_binary.push_back(0x14);
  m_binary.push_back(u5);
}

void Awassembler::DoLbl(std::uint8_t u5){

  m_binary.push_back(0x10);
  m_binary.push_back(u5);
}

void Awassembler::DoLss(){
  m_binary.push_back(0x13);
}

void Awassembler::DoMrg(){
  m_binary.push_back(0xa);
}

void Awassembler::DoMul(){
  m_binary.push_back(0xd);
}

void Awassembler::DoNop(){
  m_binary.push_back(0x0);
}

void Awassembler::DoPop(){
  m_binary.push_back(0x7);
}

void Awassembler::DoPr1(){
  m_binary.push_back(0x2);
}

void Awassembler::DoPrn(){
  m_binary.push_back(0x1);
}

void Awassembler::DoRed(){
  m_binary.push_back(0x3);
}

void Awassembler::DoR3d(){
  m_binary.push_back(0x4);
}

void Awassembler::DoSbm(std::uint8_t u5){
  try{
    Check5BitUnsigned(u5);
  }
  catch(std::runtime_error e){
    throw std::runtime_error{"Internal Error: DoSbm did not recieve a 5 bit unsigned"};
  }
  m_binary.push_back(0x6);
  m_binary.push_back(u5);
}

void Awassembler::DoSrn(std::uint8_t u5){
  try{
    Check5BitUnsigned(u5);
  }
  catch(std::runtime_error e){
    throw std::runtime_error{"Internal Error: DoSrn did not recieve a 5 bit unsigned"};
  }
  m_binary.push_back(0x9);
  m_binary.push_back(u5);
}

void Awassembler::DoSub(){
  m_binary.push_back(0xc);
}

void Awassembler::DoTrm(){
  m_binary.push_back(0x1f);
}

}
