#ifndef __MOCKITOPP_MATCHER_ANY_HPP__
#define __MOCKITOPP_MATCHER_ANY_HPP__

#include <mockitopp/matchers/Matcher.hpp>

namespace mockitopp
{
   template <typename T>
   struct AnyT : public Matcher<T>
   {
      AnyT()
         {}

      virtual Matcher<T>* clone() const
         { return new AnyT(); }

      virtual bool operator== (const T& rhs) const
         { return true; }
   };

   template <typename T>
   AnyT<T> any()
      { return AnyT<T>(); }
} // namespace mockitopp

#endif //__MOCKITOPP_MATCHER_ANY_HPP__
