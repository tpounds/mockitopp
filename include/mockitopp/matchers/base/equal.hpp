#ifndef __MOCKITOPP_MATCHER_EQ_HPP__
#define __MOCKITOPP_MATCHER_EQ_HPP__

#include <mockitopp/matchers/Matcher.hpp>

namespace mockitopp
{
   namespace matcher
   {
      template <typename T>
      struct EqT : public Matcher<T>
      {
         EqT(const T& element)
            : element(element)
            {}

         virtual Matcher<T>* clone() const
            { return new EqT(element); }

         virtual bool operator== (const T& rhs) const
            { return element == rhs; }

         private:

            T element;
      };

      template <typename T>
      EqT<T> equal(const T& element)
         { return EqT<T>(element); }
   } // namespace matcher
} // namespace mockitopp

#endif //__MOCKITOPP_MATCHER_EQ_HPP__
