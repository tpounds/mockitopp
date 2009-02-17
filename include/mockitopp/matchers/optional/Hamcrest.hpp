#ifndef __MOCKITOPP_MATCHER_HAMCREST_HPP__
#define __MOCKITOPP_MATCHER_HAMCREST_HPP__

#include <mockitopp/matchers/Matcher.hpp>

namespace mockitopp
{
   #ifndef HAMCREST_MATCHER_H
      #error compatible hamcrest matcher header not found!
   #endif

   template <typename T>
   struct HamcrestT : public Matcher<T>
   {
      HamcrestT(const hamcrest::matcher<T>& hc_matcher)
         : hc_matcher(hc_matcher.copy())
         {}

      virtual Matcher<T>* clone() const
         { return new HamcrestT(hc_matcher); }

      virtual bool operator== (const T& rhs) const
         { return (*hc_matcher)(rhs); }

      private:

         hamcrest::matcher<T>* hc_matcher;

         HamcrestT(hamcrest::matcher<T>* hc_matcher)
            : hc_matcher(hc_matcher)
         {}
   };

   template <typename T>
   HamcrestT<T> hamcrest(const hamcrest::matcher<T>& hc_matcher)
      { return HamcrestT<T>(hc_matcher); }
} // namespace mockitopp

#endif //__MOCKITOPP_MATCHER_HAMCREST_HPP__
