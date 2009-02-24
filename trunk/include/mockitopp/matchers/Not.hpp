#ifndef __MOCKITOPP_MATCHER_NOT_HPP__
#define __MOCKITOPP_MATCHER_NOT_HPP__

#include <mockitopp/matchers/Matcher.hpp>

namespace mockitopp
{
   namespace matcher
   {
      template <typename T>
      struct NotT : public Matcher<T>
      {
         NotT(const Matcher<T>& matcher)
            : matcher(matcher.clone())
            {}

         virtual ~NotT()
            { delete matcher; }

         virtual Matcher<T>* clone() const
            { return new NotT(*matcher); }

         virtual bool operator== (const T& rhs) const
            { return !(*matcher == rhs); }

         private:

            Matcher<T>* matcher;
      };

      template <typename T>
      NotT<T> not_(const Matcher<T>& matcher)
         { return NotT<T>(matcher); }
   } // namespace matcher
} // namespace mockitopp

#endif //__MOCKITOPP_MATCHER_EQ_HPP__
