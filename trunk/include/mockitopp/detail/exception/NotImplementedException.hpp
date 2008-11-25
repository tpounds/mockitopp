#ifndef __MOCKITOPP_NOT_IMPLEMENTED_EXCEPTION_HPP__
#define __MOCKITOPP_NOT_IMPLEMENTED_EXCEPTION_HPP__

#include <exception>

namespace mockitopp
{
   namespace detail
   {
      struct NotImplementedException : public std::exception
      {
         const char *what() const throw()
            { return "Called method not implemented!"; }
      };
   } // namespace detail
} // namespace mockitopp

#endif //__MOCKITOPP_NOT_IMPLEMENTED_EXCEPTION_HPP__
