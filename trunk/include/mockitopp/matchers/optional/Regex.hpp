#ifndef __MOCKITOPP_MATCHER_TR1_REGEX_HPP__
#define __MOCKITOPP_MATCHER_TR1_REGEX_HPP__

#include <mockitopp/matchers/Matcher.hpp>

namespace mockitopp
{
   namespace matcher
   {
      #if defined(BOOST_RE_REGEX_HPP)
         #define TR1_REGEX_NAMESPACE boost
      #elif defined(_GLIBCXX_TR1_REGEX) || defined(_REGEX_)
         #define TR1_REGEX_NAMESPACE std::tr1
      #else
         #error compatible tr1 regex header not found!
      #endif

      template <typename T>
      struct RegexT : public Matcher<T>
      {
         RegexT(const T& expr)
            : expr(expr)
            {}

         virtual Matcher<T>* clone() const
            { return new RegexT(expr); }

         virtual bool operator== (const T& rhs) const
            { return TR1_REGEX_NAMESPACE::regex_match(rhs, expr); }

         private:

            TR1_REGEX_NAMESPACE::regex expr;

            RegexT(const TR1_REGEX_NAMESPACE::regex& expr)
               : expr(expr)
               {}
      };

      inline RegexT<std::string> regex(const std::string& expr)
         { return RegexT<std::string>(expr); }

      inline RegexT<const char*> regex(const char* expr)
         { return RegexT<const char*>(expr); }
   } // namespace matcher
} // namespace mockitopp

#undef TR1_REGEX_NAMESPACE

#endif //__MOCKITOPP_MATCHER_TR1_REGEX_HPP__
