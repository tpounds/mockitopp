#ifndef __MOCKITOPP_MATCHER_STRING_LITERAL_HPP__
#define __MOCKITOPP_MATCHER_STRING_LITERAL_HPP__

#include <mockitopp/matchers/Matcher.hpp>
#include <string>

namespace mockitopp
{
   namespace matcher
   {
      namespace detail
      {
         template <typename T> struct is_string_literal {};
         template <> struct is_string_literal<char*> { typedef char* type; };
         template <> struct is_string_literal<const char*> { typedef const char* type; };

         template <typename T>
         struct StringLiteralT : public Matcher<T>
         {
            StringLiteralT(const T& string_lit)
               : internal_string(string_lit)
               {}

            virtual Matcher<T>* clone() const
               { return new StringLiteralT(const_cast<T>(internal_string.c_str())); }

            virtual bool operator== (typename mockitopp::detail::tr1::add_reference<typename mockitopp::detail::tr1::add_const<T>::type>::type rhs) const
               { return internal_string == rhs; }

            private:

               std::string internal_string;
         };
      } // namespace detail

      template <typename T>
      detail::StringLiteralT<T> string_literal(typename detail::is_string_literal<T>::type string_lit)
         { return detail::StringLiteralT<T>(string_lit); }
   } // namespace matcher
} // namespace mockitopp

#endif //__MOCKITOPP_MATCHER_STRING_LITERAL_HPP__
