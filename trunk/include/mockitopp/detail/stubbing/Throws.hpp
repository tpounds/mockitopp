#ifndef __MOCKITOPP_THROWS_HPP__
#define __MOCKITOPP_THROWS_HPP__

#include <mockitopp/detail/stubbing/Answer.hpp>

namespace mockitopp
{
   namespace detail
   {
      template <typename R, typename T>
      struct Throws : public Answer<R>
      {
         T _throwable;

         Throws(const T& throwable)
            : _throwable(throwable)
            {}

         R execute()
            { throw _throwable; }
      };
   } // namespace detail
} // namespace mockitopp

#endif //__MOCKITOPP_THROWS_HPP__
