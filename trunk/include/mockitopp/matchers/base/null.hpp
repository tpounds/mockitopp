#ifndef __MOCKITOPP_MATCHER_NULL_HPP__
#define __MOCKITOPP_MATCHER_NULL_HPP__

#include <mockitopp/matchers/Matcher.hpp>

namespace mockitopp
{
   namespace matcher
   {
      namespace detail
      {
         template <typename T>
         struct NullT : public Matcher<T>
         {
            NullT()
               {}

            virtual Matcher<T>* clone() const
               { return new NullT(); }

            virtual bool operator== (typename mockitopp::detail::tr1::add_reference<typename mockitopp::detail::tr1::add_const<T>::type>::type rhs) const
               { return rhs == 0; }
         };
      } // namespace detail

      template <typename T>
      detail::NullT<T> null()
         { return detail::NullT<T>(); }
   } // namespace matcher
} // namespace mockitopp

#endif //__MOCKITOPP_MATCHER_NULL_HPP__
