#ifndef __MOCKITOPP_ONGOING_STUBBING_HPP__
#define __MOCKITOPP_ONGOING_STUBBING_HPP__

#include <list>
#include <map>

#include <boost/preprocessor/facilities/intercept.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_params.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/tuple/tuple_comparison.hpp>
#include <boost/type_traits/is_void.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/utility/enable_if.hpp>

#include <mockitopp/detail/exception/IncompleteImplementationException.hpp>
#include <mockitopp/detail/stubbing/Answer.hpp>
#include <mockitopp/detail/stubbing/MatcherContainer.hpp>
#include <mockitopp/detail/stubbing/Returns.hpp>
#include <mockitopp/detail/stubbing/Throws.hpp>
#include <mockitopp/detail/stubbing/Verifier.hpp>
#include <mockitopp/detail/utility/KeyPair.hpp>

// TODO: add documentation
namespace mockitopp
{
   namespace detail
   {
      template <typename T, typename ENABLE = void> struct OngoingStubbing;

      // TODO: clean up impl
      // TODO: add sequence matcher

      //TODO: clean up typedef nomenclature
      #define DEFINE_ONGOING_STUBBING_COMMON(ZZZ, NNN, TTT, RRR) \
            typedef boost::tuple<BOOST_PP_ENUM_BINARY_PARAMS(NNN, \
               typename boost::remove_const<typename boost::remove_reference<A, >::type >::type \
                  BOOST_PP_INTERCEPT)> tuple_type; \
            typedef boost::tuple<BOOST_PP_ENUM_BINARY_PARAMS(NNN, \
               MatcherContainer<typename boost::remove_const<typename boost::remove_reference<A, >::type >::type> \
                  BOOST_PP_INTERCEPT)> matcher_tuple_type; \
            typedef Answer<RRR>*            answer_type; \
            typedef std::list<answer_type> queue_type; \
         \
            /*TODO: rename argument lists*/ \
            std::map<tuple_type, queue_type> answerMap; \
            std::list<KeyPair<matcher_tuple_type, queue_type> > answerList; \
         \
            queue_type* ongoingMatch; \
            Verifier   verifier; \
         \
            OngoingStubbing() \
               : answerMap() \
               , answerList() \
               , ongoingMatch() \
               , verifier() \
               {} \
         \
            OngoingStubbing& BOOST_PP_IF(NNN, when, __DISABLED_when)(BOOST_PP_ENUM_BINARY_PARAMS(NNN, const Matcher<typename boost::remove_const<typename boost::remove_reference<A, >::type >::type>& a)) \
            { \
               matcher_tuple_type arguments = matcher_tuple_type(BOOST_PP_ENUM_PARAMS(NNN, a)); \
               typename std::list<KeyPair<matcher_tuple_type, queue_type> >::iterator pair_it; \
               pair_it = find(answerList.begin(), answerList.end(), arguments); \
               if(pair_it == answerList.end()) \
               { \
                  answerList.push_back(KeyPair<matcher_tuple_type, queue_type>(arguments, queue_type())); \
                  pair_it = --answerList.end(); \
               } \
               ongoingMatch = &(pair_it->value); \
               return *this; \
            } \
         \
            OngoingStubbing& when(BOOST_PP_ENUM_BINARY_PARAMS(NNN, A, a)) \
            { \
               ongoingMatch = &(answerMap[tuple_type(BOOST_PP_ENUM_PARAMS(NNN, a))]); \
               return *this; \
            } \
         \
            template <typename T> \
            OngoingStubbing& thenThrow(T throwable) \
            { \
               ongoingMatch->push_back(new Throws<RRR, T>(throwable)); \
               return *this; \
            } \
         \
            RRR invoke(BOOST_PP_ENUM_BINARY_PARAMS(NNN, A, a)) \
            { \
               verifier.calls++; \
               tuple_type  args    = tuple_type(BOOST_PP_ENUM_PARAMS(NNN, a)); \
               queue_type& answers = answerMap[args]; \
               if(answers.empty()) \
               { \
                  typename std::list<KeyPair<matcher_tuple_type, queue_type> >::iterator pair_it; \
                  pair_it = find(answerList.begin(), answerList.end(), args); \
                  if(pair_it == answerList.end()) \
                     { throw IncompleteImplementationException(); } \
                  answers = pair_it->value; \
               } \
               answer_type answer = answers.front(); \
               if(answers.size() > 1) \
                  { answers.pop_front(); } \
               return answer->execute(); \
            } \
         \
            const Verifier& getVerifier() const \
               { return verifier; }

      #define DEFINE_ONGOING_STUBBING(ZZZ, NNN, TTT) \
         template <typename C BOOST_PP_ENUM_TRAILING_PARAMS(NNN, typename A)> \
         struct OngoingStubbing<void (C::*)(BOOST_PP_ENUM_PARAMS(NNN, A))> \
         { \
            DEFINE_ONGOING_STUBBING_COMMON(ZZZ, NNN, TTT, void) \
         \
            OngoingStubbing& thenReturn() \
            { \
               ongoingMatch->push_back(new Returns<void>()); \
               return *this; \
            } \
         }; \
      \
         template <typename R, typename C BOOST_PP_ENUM_TRAILING_PARAMS(NNN, typename A)> \
         struct OngoingStubbing<R (C::*)(BOOST_PP_ENUM_PARAMS(NNN, A)), typename boost::disable_if<boost::is_void<R> >::type> \
         { \
            DEFINE_ONGOING_STUBBING_COMMON(ZZZ, NNN, TTT, R) \
         \
            OngoingStubbing& thenReturn(R value) \
            { \
               ongoingMatch->push_back(new Returns<R>(value)); \
               return *this; \
            } \
         };

      BOOST_PP_REPEAT(MAX_VIRTUAL_FUNCTION_ARITY, DEFINE_ONGOING_STUBBING, ~)

      #undef DEFINE_ONGOING_STUBBING_COMMON
      #undef DEFINE_ONGOING_STUBBING

   } // namespace detail
} // namespace mockitopp

#endif //__MOCKITOPP_ONGOING_STUBBING_HPP__
