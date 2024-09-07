#ifndef AWA_EXCEPTIONS_HPP
#define AWA_EXCEPTIONS_HPP

// custom exceptions with semantic names

#include <exception>
#include <format>
#include <string>

namespace Awax86{

  class NotimplementedException: public std::exception{
  };

  class UnspecifiedException: public std::exception{
  };

}

#endif
