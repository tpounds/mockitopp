#ifndef __MOCKITOPP_RETURNS_HPP__
#define __MOCKITOPP_RETURNS_HPP__

#include <mockitopp/detail/stubbing/Answer.hpp>

namespace mockitopp
{
   namespace detail
   {
      template <typename R>
      struct Returns : public Answer<R>
      {
         R _returnable;

         Returns(const R& returnable)
            : _returnable(returnable)
            {}

         R execute()
            { return _returnable; }
      };

      template <>
      struct Returns<void> : public Answer<void>
      {
         void execute()
            {}
      };
   } // namespace detail
} // namespace mockitopp

#endif //__MOCKITOPP_RETURNS_HPP__
