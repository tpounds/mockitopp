#ifndef __MOCKITOPP_MATCHER_CONTAINER_HPP__
#define __MOCKITOPP_MATCHER_CONTAINER_HPP__

#include <mockitopp/matchers/Matcher.hpp>

namespace mockitopp
{
   namespace detail
   {
      template <typename T>
      struct MatcherContainer
      {
         matcher::Matcher<T>* matcher;

         MatcherContainer()
            : matcher(0)
            {}
  
         MatcherContainer(const matcher::Matcher<T>& _matcher)
            : matcher(_matcher.clone())
            {}

         ~MatcherContainer()
         {
//            if(matcher != 0)
//               { delete matcher; }
         }

         bool operator== (const T& rhs) const
            { return (*matcher == rhs); }

         bool operator== (const MatcherContainer& rhs) const
            { return matcher == rhs.matcher; }
      };
   } // namespace detail
} // namespace mockitopp

#endif //__MOCKITOPP_MATCHER_CONTAINER_HPP__
