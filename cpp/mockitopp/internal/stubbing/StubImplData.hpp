#ifndef __MOCKITOPP_STUB_IMPL_DATA_HPP__
#define __MOCKITOPP_STUB_IMPL_DATA_HPP__

#include <stdint.h>

#include <mockitopp/internal/matcher/ArgumentMatcher.hpp>

namespace mockitopp
{
   namespace detail
   {
      template <typename T>
      class StubImplData
      {
         public:

            typedef ArgumentMatcher<T> matcher_type;

         private:

            uint32_t     __calls;
            matcher_type __matcher;

         public:

            StubImplData()
               : __calls(0)
               , __matcher()
            {}

            uint32_t& getCalls()
               { return __calls; }

            matcher_type& getMatcher()
               { return __matcher; }
      };

   } // namespace detail
} // namespace mockitopp

#endif //__MOCKITOPP_STUB_IMPL_DATA_HPP__
