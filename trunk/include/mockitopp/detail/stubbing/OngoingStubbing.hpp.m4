#ifndef __MOCKITOPP_ONGOING_STUBBING_HPP__
#define __MOCKITOPP_ONGOING_STUBBING_HPP__

#include <list>
#include <map>

#include <mockitopp/detail/exception/IncompleteImplementationException.hpp>
#include <mockitopp/detail/stubbing/Answer.hpp>
#include <mockitopp/detail/stubbing/MatcherContainer.hpp>
#include <mockitopp/detail/stubbing/Returns.hpp>
#include <mockitopp/detail/stubbing/Throws.hpp>
#include <mockitopp/detail/stubbing/Verifier.hpp>
#include <mockitopp/detail/utility/KeyPair.hpp>
#include <mockitopp/detail/utility/tr1_tuple.hpp>
#include <mockitopp/detail/utility/tr1_type_traits.hpp>

include(`mockitopp/detail/m4/ENUM_BINARY_PARAMS.m4')dnl
include(`mockitopp/detail/m4/ENUM_PARAMS.m4')dnl
include(`mockitopp/detail/m4/ENUM_TRAILING_PARAMS.m4')dnl
include(`mockitopp/detail/m4/IF.m4')dnl
include(`mockitopp/detail/m4/REPEAT.m4')dnl
// TODO: add documentation
namespace mockitopp
{
   namespace detail
   {
      template <typename R>
      struct OngoingStubbingBase
      {
         typedef Answer<R>*             answer_type;
         typedef std::list<answer_type> queue_type;

         queue_type* ongoingMatch;

         OngoingStubbingBase& thenReturn(R value)
         {
            ongoingMatch->push_back(new Returns<R>(value));
            return *this;
         }

         template <typename T>
         OngoingStubbingBase& thenThrow(T throwable)
         {
            ongoingMatch->push_back(new Throws<R, T>(throwable));
            return *this;
         }
      };

      template <>
      struct OngoingStubbingBase<void>
      {
         typedef Answer<void>*          answer_type;
         typedef std::list<answer_type> queue_type;

         queue_type* ongoingMatch;

         OngoingStubbingBase& thenReturn()
         {
            ongoingMatch->push_back(new Returns<void>());
            return *this;
         }

         template <typename T>
         OngoingStubbingBase& thenThrow(T throwable)
         {
            ongoingMatch->push_back(new Throws<void, T>(throwable));
            return *this;
         }
      };

      template <typename T> struct OngoingStubbing;

      // TODO: clean up impl
      // TODO: add sequence matcher

      //TODO: clean up typedef nomenclature
define(`DEFINE_ONGOING_STUBBING', `
      template <typename R, typename C`'M4_ENUM_TRAILING_PARAMS($1, typename A)>
      struct OngoingStubbing<R (C::*)(M4_ENUM_PARAMS($1, A))> : public OngoingStubbingBase<R>
      {
         typedef tr1::tuple<M4_ENUM_BINARY_PARAMS($1,
            typename tr1::remove_const<typename tr1::remove_reference<A, >::type>::type,
               M4_INTERCEPT)> tuple_type;
         typedef tr1::tuple<M4_ENUM_BINARY_PARAMS($1,
            MatcherContainer<typename tr1::remove_const<typename tr1::remove_reference<A, >::type>::type> ,
               M4_INTERCEPT)> matcher_tuple_type;

         typedef typename OngoingStubbingBase<R>::answer_type answer_type;
         typedef typename OngoingStubbingBase<R>::queue_type  queue_type;

         //TODO: rename argument lists
         std::map<tuple_type, queue_type> answerMap;
         std::list<KeyPair<matcher_tuple_type, queue_type> > answerList;

         Verifier   verifier;

         OngoingStubbing()
            : OngoingStubbingBase<R>()
            , answerMap()
            , answerList()
            , verifier()
            {}

         OngoingStubbing& M4_IF($1, when, __DISABLE_OVERLOAD__when)(M4_ENUM_BINARY_PARAMS($1, const matcher::Matcher<typename tr1::remove_const<typename tr1::remove_reference<A, >::type>::type>& a))
         {
            matcher_tuple_type arguments = matcher_tuple_type(M4_ENUM_PARAMS($1, a));
            typename std::list<KeyPair<matcher_tuple_type, queue_type> >::iterator pair_it;
            pair_it = find(answerList.begin(), answerList.end(), arguments);
            if(pair_it == answerList.end())
            {
               answerList.push_back(KeyPair<matcher_tuple_type, queue_type>(arguments, queue_type()));
               pair_it = --answerList.end();
            }
            this->ongoingMatch = &(pair_it->value);
            return *this;
         }

         OngoingStubbing& when(M4_ENUM_BINARY_PARAMS($1, A, a))
         {
            this->ongoingMatch = &(answerMap[tuple_type(M4_ENUM_PARAMS($1, a))]);
            return *this;
         }

         R invoke(M4_ENUM_BINARY_PARAMS($1, A, a))
         {
            verifier.calls++;
            tuple_type  args    = tuple_type(M4_ENUM_PARAMS($1, a));
            queue_type& answers = answerMap[args];
            if(answers.empty())
            {
               typename std::list<KeyPair<matcher_tuple_type, queue_type> >::iterator pair_it;
               pair_it = find(answerList.begin(), answerList.end(), args);
               if(pair_it == answerList.end())
                  { throw IncompleteImplementationException(); }
               answers = pair_it->value;
            }
            answer_type answer = answers.front();
            if(answers.size() > 1)
               { answers.pop_front(); }
            return answer->execute();
         }

         const Verifier& getVerifier() const
            { return verifier; }
      };
')
M4_REPEAT(11, `DEFINE_ONGOING_STUBBING')dnl
   } // namespace detail
} // namespace mockitopp

#endif //__MOCKITOPP_ONGOING_STUBBING_HPP__
