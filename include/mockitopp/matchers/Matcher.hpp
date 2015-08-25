#ifndef __MOCKITOPP_MATCHER_HPP__
#define __MOCKITOPP_MATCHER_HPP__

#include <mockitopp/detail/util/tr1_type_traits.hpp>

namespace mockitopp
{
   namespace matcher
   {
      template <typename T>
      struct Matcher
      {
         virtual ~Matcher() {}

         virtual Matcher* clone() const = 0;

         virtual bool operator== (typename mockitopp::detail::tr1::add_reference<typename mockitopp::detail::tr1::add_const<T>::type>::type rhs) const = 0;
      };
   } // namespace matcher
} // namespace mockitopp

#endif //__MOCKITOPP_MATCHER_HPP__
