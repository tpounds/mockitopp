#ifndef __MOCKITOPP_MATCHER_EQ_HPP__
#define __MOCKITOPP_MATCHER_EQ_HPP__

#include <mockitopp/matchers/Matcher.hpp>

namespace mockitopp
{
   template <typename T>
   struct Eq : public Matcher<T>
   {
      Eq(const T& element)
         : element(element)
         {}

      virtual Matcher<T>* clone() const
         { return new Eq(element); }

      virtual bool operator== (const T& rhs) const
         { return element == rhs; }

      private:

         T element;

         Eq() {}
   };
} // namespace mockitopp

#endif //__MOCKITOPP_MATCHER_EQ_HPP__
