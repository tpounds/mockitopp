#ifndef __MOCKITOPP_MATCHER_REGEX_HPP__
#define __MOCKITOPP_MATCHER_REGEX_HPP__

#include <mockitopp/matchers/Matcher.hpp>

namespace mockitopp
{
   namespace matcher
   {
      namespace detail
      {
         #if defined(BOOST_RE_REGEX_HPP)
            namespace __tr1 = ::boost;
         #elif defined(_GLIBCXX_TR1_REGEX) || defined(_REGEX_)
            namespace __tr1 = ::std::tr1;
         #else
            #error compatible tr1 regex header not found!
         #endif

         template <typename T>
         struct RegexT : public Matcher<T>
         {
            RegexT(typename mockitopp::detail::tr1::add_reference<typename mockitopp::detail::tr1::add_const<T>::type>::type expr)
               : expr(expr)
               {}

            virtual Matcher<T>* clone() const
               { return new RegexT(expr); }

            virtual bool operator== (typename mockitopp::detail::tr1::add_reference<typename mockitopp::detail::tr1::add_const<T>::type>::type rhs) const
               { return __tr1::regex_match(rhs, expr); }

            private:

               __tr1::regex expr;

               RegexT(const __tr1::regex& expr)
                  : expr(expr)
                  {}
         };
      } // namespace detail

      template <typename T>
      detail::RegexT<T> regex(T expr)
         { return detail::RegexT<T>(expr); }
   } // namespace matcher
} // namespace mockitopp

#endif //__MOCKITOPP_MATCHER_REGEX_HPP__
