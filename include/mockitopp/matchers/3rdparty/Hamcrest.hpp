#ifndef __MOCKITOPP_MATCHER_HAMCREST_HPP__
#define __MOCKITOPP_MATCHER_HAMCREST_HPP__

#ifndef HAMCREST_MATCHER_H
   #error Hamcrest matcher library not found!
#endif

#include <mockitopp/matchers/Matcher.hpp>

namespace mockitopp
{
   template <typename T>
   struct Hamcrest : public Matcher<T>
   {
      Hamcrest(const hamcrest::matcher<T>& matcher_impl)
         : matcher_impl(matcher_impl.copy())
         {}

      virtual Matcher<T>* clone() const
         { return new Hamcrest(matcher_impl); }

      virtual bool operator== (const T& rhs) const
         { return (*matcher_impl)(rhs); }

      private:

         hamcrest::matcher<T>* matcher_impl;

         Hamcrest() {}

         Hamcrest(hamcrest::matcher<T>* matcher_impl)
            : matcher_impl(matcher_impl)
         {}
   };
} // namespace mockitopp

#endif //__MOCKITOPP_MATCHER_HAMCREST_HPP__
