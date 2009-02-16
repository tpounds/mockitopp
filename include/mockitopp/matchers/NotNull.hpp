#ifndef __MOCKITOPP_MATCHER_NOT_NULL_HPP__
#define __MOCKITOPP_MATCHER_NOT_NULL_HPP__

#include <mockitopp/matchers/Matcher.hpp>

namespace mockitopp
{
   template <typename T>
   struct NotNull : public Matcher<T>
   {
      NotNull()
         {}

      virtual Matcher<T>* clone() const
         { return new NotNull(); }

      virtual bool operator== (const T& rhs) const
         { return rhs != 0; }
   };
} // namespace mockitopp

#endif //__MOCKITOPP_MATCHER_NOT_NULL_HPP__
