#ifndef __MOCKITOPP_INCOMPLETE_IMPLEMENTATION_EXCEPTION_HPP__
#define __MOCKITOPP_INCOMPLETE_IMPLEMENTATION_EXCEPTION_HPP__

#include <exception>

namespace mockitopp
{
   namespace detail
   {
      struct IncompleteImplementationException : public std::exception
      {
         const char *what() const throw()
            { return "Called method has incomplete implementation!"; }
      };
   } // namespace detail
} // namespace mockitopp

#endif //__MOCKITOPP_INCOMPLETE_IMPLEMENTATION_EXCEPTION_HPP__
