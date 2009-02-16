#ifndef __MOCKITOPP_MATCHER_NULL_HPP__
#define __MOCKITOPP_MATCHER_NULL_HPP__

#include <mockitopp/matchers/Matcher.hpp>

namespace mockitopp
{
   template <typename T>
   struct Null : public Matcher<T>
   {
      Null()
         {}

      virtual Matcher<T>* clone() const
         { return new Null(); }

      virtual bool operator== (const T& rhs) const
         { return rhs == 0; }
   };
} // namespace mockitopp

#endif //__MOCKITOPP_MATCHER_NULL_HPP__
