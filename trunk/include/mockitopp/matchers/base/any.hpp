#ifndef __MOCKITOPP_MATCHER_ANY_HPP__
#define __MOCKITOPP_MATCHER_ANY_HPP__

#include <mockitopp/matchers/Matcher.hpp>

namespace mockitopp
{
   namespace matcher
   {
      namespace detail
      {
         template <typename T>
         struct AnyT : public Matcher<T>
         {
            AnyT()
               {}

            virtual Matcher<T>* clone() const
               { return new AnyT(); }

            virtual bool operator== (typename mockitopp::detail::tr1::add_reference<typename mockitopp::detail::tr1::add_const<T>::type>::type rhs) const
            { 
               (void)rhs;
               return true; 
            }
         };
      } // namespace detail

      template <typename T>
      detail::AnyT<T> any()
         { return detail::AnyT<T>(); }
   } // namespace matcher
} // namespace mockitopp

#endif //__MOCKITOPP_MATCHER_ANY_HPP__
