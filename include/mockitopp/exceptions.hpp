#ifndef __MOCKITOPP_EXCEPTIONS_HPP__
#define __MOCKITOPP_EXCEPTIONS_HPP__

#include <exception>

namespace mockitopp
{
   struct partial_implementation_exception : public ::std::exception
   {
      const char *what() const throw()
         { return "function has partial implementation!"; }
   };

   struct missing_implementation_exception : public ::std::exception
   {
      const char *what() const throw()
         { return "function has no implementation!"; }
   };
} // namespace mockitopp

#endif //__MOCKITOPP_EXCEPTIONS_HPP__
