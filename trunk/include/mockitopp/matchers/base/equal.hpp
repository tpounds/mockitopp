#ifndef __MOCKITOPP_MATCHER_EQ_HPP__
#define __MOCKITOPP_MATCHER_EQ_HPP__

#include <mockitopp/matchers/Matcher.hpp>
#include <string>

namespace mockitopp
{
   namespace matcher
   {
      namespace detail
      {
         template <typename T>
         struct EqualT : public Matcher<T>
         {
            EqualT(typename mockitopp::detail::tr1::add_reference<
                     typename mockitopp::detail::tr1::add_const<T>::type>::type element)
               : element_(element)
               {}

            virtual Matcher<T>* clone() const
               { return new EqualT(element_); }

            virtual bool operator== (typename mockitopp::detail::tr1::add_reference<
                                       typename mockitopp::detail::tr1::add_const<T>::type>::type rhs) const
               { return element_ == rhs; }

            private:

               T element_;
         };
      } // namespace detail

      template <typename T>
      detail::EqualT<T> equal(typename mockitopp::detail::tr1::add_reference<
                                 typename mockitopp::detail::tr1::add_const<T>::type>::type element)
         { return detail::EqualT<T>(element); }

      inline detail::EqualT<std::string> equal(const char* element)
         { return detail::EqualT<std::string>(element); }
   } // namespace matcher
} // namespace mockitopp

#endif //__MOCKITOPP_MATCHER_EQ_HPP__
