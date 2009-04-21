#ifndef __MOCKITOPP_MATCHER_HAMCREST_HPP__
#define __MOCKITOPP_MATCHER_HAMCREST_HPP__

#include <mockitopp/matchers/Matcher.hpp>

#ifndef HAMCREST_MATCHER_H
   #error compatible hamcrest matcher header not found!
#endif

namespace mockitopp
{
   namespace matcher
   {
      namespace detail
      {
         template <typename T>
         struct HamcrestT : public Matcher<T>
         {
            HamcrestT(const ::hamcrest::matcher<T>& hc_matcher)
               : hc_matcher(hc_matcher.copy())
               {}

            virtual ~HamcrestT()
               { delete hc_matcher; }

            virtual Matcher<T>* clone() const
               { return new HamcrestT(*hc_matcher); }

            virtual bool operator== (const T& rhs) const
               { return (*hc_matcher)(rhs); }

            private:

               ::hamcrest::matcher<T>* hc_matcher;
         };
      } // namespace detail
 
      template <typename T>
      detail::HamcrestT<T> hamcrest(const ::hamcrest::matcher<T>& hc_matcher)
         { return detail::HamcrestT<T>(hc_matcher); }

      template <typename T>
      detail::HamcrestT<T> hc(const ::hamcrest::matcher<T>& hc_matcher)
         { return detail::HamcrestT<T>(hc_matcher); }
   } // namespace matcher
} // namespace mockitopp

#endif //__MOCKITOPP_MATCHER_HAMCREST_HPP__
