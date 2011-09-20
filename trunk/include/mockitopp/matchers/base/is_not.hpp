#ifndef __MOCKITOPP_MATCHER_NOT_HPP__
#define __MOCKITOPP_MATCHER_NOT_HPP__

#include <mockitopp/matchers/Matcher.hpp>

namespace mockitopp
{
   namespace matcher
   {
      namespace detail
      {
         template <typename T>
         struct NotT : public Matcher<T>
         {
            NotT(const Matcher<T>& matcher)
               : matcher_(matcher.clone())
               {}

            virtual ~NotT()
               { delete matcher_; }

            virtual Matcher<T>* clone() const
               { return new NotT(*matcher_); }

            virtual bool operator== (typename mockitopp::detail::tr1::add_reference<typename mockitopp::detail::tr1::add_const<T>::type>::type rhs) const
               { return !(*matcher_ == rhs); }

            private:

               Matcher<T>* matcher_;
         };
      } // namespace detail

      template <typename T>
      detail::NotT<T> is_not(const Matcher<T>& matcher)
         { return detail::NotT<T>(matcher); }
   } // namespace matcher
} // namespace mockitopp

#endif //__MOCKITOPP_MATCHER_EQ_HPP__
