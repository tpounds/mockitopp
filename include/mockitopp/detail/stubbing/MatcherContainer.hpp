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
  
         MatcherContainer(const matcher::Matcher<T>& _matcher)
            : matcher(_matcher.clone())
            {}

         MatcherContainer(const MatcherContainer& rhs)
            : matcher(rhs.matcher->clone())
            {}

         virtual ~MatcherContainer()
            { delete matcher; }

         bool operator== (typename tr1::add_reference<typename tr1::add_const<T>::type>::type rhs) const
            { return (*matcher == rhs); }

         bool operator== (const MatcherContainer& rhs) const
            { return matcher == rhs.matcher; }
      };
   } // namespace detail
} // namespace mockitopp

#endif //__MOCKITOPP_MATCHER_CONTAINER_HPP__
