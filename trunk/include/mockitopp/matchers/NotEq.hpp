#ifndef __MOCKITOPP_MATCHER_NOT_EQ_HPP__
#define __MOCKITOPP_MATCHER_NOT_EQ_HPP__

#include <mockitopp/matchers/Matcher.hpp>

namespace mockitopp
{
   template <typename T>
   struct NotEq : public Matcher<T>
   {
      NotEq(const T& element)
         : element(element)
         {}

      virtual Matcher<T>* clone() const
         { return new NotEq(element); }

      virtual bool operator== (const T& rhs) const
         { return element != rhs; }

      private:

         T element;

         NotEq() {}
   };
} // namespace mockitopp

#endif //__MOCKITOPP_MATCHER_NOT_EQ_HPP__
