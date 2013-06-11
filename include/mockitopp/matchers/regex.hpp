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
         #elif defined(_GLIBCXX_REGEX)
            namespace __tr1 = ::std;
         #else
            #error compatible tr1 regex header not found!
         #endif

         template <typename T>
         struct RegexT : public Matcher<T>
         {
            RegexT(typename mockitopp::detail::tr1::add_reference<typename mockitopp::detail::tr1::add_const<T>::type>::type expr)
               : expr_(expr)
               {}

            virtual Matcher<T>* clone() const
               { return new RegexT(expr_); }

            virtual bool operator== (typename mockitopp::detail::tr1::add_reference<typename mockitopp::detail::tr1::add_const<T>::type>::type rhs) const
               { return __tr1::regex_match(rhs, expr_); }

            private:

               __tr1::regex expr_;

               RegexT(const __tr1::regex& expr)
                  : expr_(expr)
                  {}
         };
      } // namespace detail

      template <typename T>
      detail::RegexT<T> regex(T expr)
         { return detail::RegexT<T>(expr); }
   } // namespace matcher
} // namespace mockitopp

#endif //__MOCKITOPP_MATCHER_REGEX_HPP__
