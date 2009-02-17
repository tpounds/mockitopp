#ifndef __MOCKITOPP_MATCHER_NULL_HPP__
#define __MOCKITOPP_MATCHER_NULL_HPP__

#include <mockitopp/matchers/Matcher.hpp>

namespace mockitopp
{
   template <typename T>
   struct NullT : public Matcher<T>
   {
      NullT()
         {}

      virtual Matcher<T>* clone() const
         { return new NullT(); }

      virtual bool operator== (const T& rhs) const
         { return rhs == 0; }
   };

   template <typename T>
   NullT<T> null()
      { return NullT<T>(); }
} // namespace mockitopp

#endif //__MOCKITOPP_MATCHER_NULL_HPP__
