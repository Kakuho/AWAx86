#ifndef UTIL_HPP
#define UTIL_HPP

#include <stdexcept>
#include <string>
#include <cstdint>
#include <cctype>
#include <exception>

// just general utilities

namespace Awa4x86{
  inline bool IsNumeric(std::string& s){
    // the beginning may only start with a '-', or is a digit
    if(! (std::isdigit(static_cast<unsigned char>(s[0])) || s[0] == '-')){
      return false;
    }
    // check the inner part
    for(std::size_t i = 1; i < s.size(); i++){
      if(!std::isdigit(static_cast<unsigned char>(s[i]))){
        return false;
      }
    }
    return true;
  }

  inline std::uint8_t Convert5BitUnsigned(std::string s){
    bool isNegative = s[0] == '-';
    if(!IsNumeric(s) || isNegative){
      throw std::runtime_error{"input string s is either not a numeric, or is negative and not unsigned"};
    }
    // all validity checks passed, we convert the string to an unsigned integer
    auto input = std::stoul(s);
    if(input > 0x1F){
      throw std::runtime_error{"input string s is greater than maximum allowed in a 5bit unsignwed"};
    }
    return input;
  }

  inline std::int8_t Convert8BitSigned(std::string s){
    if(!IsNumeric(s)){
      throw std::runtime_error{"input string s is either not a numeric, or is negative and not unsigned"};
    }
    // all validity checks passed, we convert the string to an signed integer
    auto input = std::stol(s);
    bool isOverflow = (input > 127) || (input < -127);
    if(isOverflow){
      throw std::runtime_error{"input string s does not fit within 8 bit integer"};
    }
    return input;
  }
} // namespace Awa4x86

#endif
