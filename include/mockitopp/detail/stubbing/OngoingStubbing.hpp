#ifndef __MOCKITOPP_ONGOING_STUBBING_HPP__
#define __MOCKITOPP_ONGOING_STUBBING_HPP__

#include <map>
#include <queue>

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
#include <mockitopp/detail/stubbing/Returns.hpp>
#include <mockitopp/detail/stubbing/Throws.hpp>
#include <mockitopp/detail/stubbing/Verifier.hpp>

// TODO: add documentation
namespace mockitopp
{
   namespace detail
   {
      template <typename T, typename ENABLE = void> struct OngoingStubbing;

      // TODO: clean up impl
      // TODO: add sequence matcher

      #define DEFINE_ONGOING_STUBBING_COMMON(ZZZ, NNN, TTT, RRR) \
            typedef boost::tuple<BOOST_PP_ENUM_BINARY_PARAMS(NNN, typename boost::remove_const<typename boost::remove_reference<A, >::type >::type BOOST_PP_INTERCEPT)> tuple_type; \
            typedef Answer<RRR>*                               answer_type; \
            typedef std::queue<answer_type>                    queue_type; \
         \
            std::map<tuple_type, queue_type>  answerMap; \
            std::map<tuple_type, answer_type> lastAnswerMap; \
            tuple_type  ongoingMatch; \
            Verifier    verifier; \
         \
            OngoingStubbing() \
               : answerMap() \
               , ongoingMatch() \
               , verifier() \
               {} \
         \
            OngoingStubbing& operator() (BOOST_PP_ENUM_BINARY_PARAMS(NNN, A, a)) \
            { \
               ongoingMatch = tuple_type(BOOST_PP_ENUM_PARAMS(NNN, a)); \
               return *this; \
            } \
         \
            template <typename T> \
            OngoingStubbing& thenThrow(T throwable) \
            { \
               answerMap[ongoingMatch].push(new Throws<RRR, T>(throwable)); \
               return *this; \
            } \
         \
            RRR invoke(BOOST_PP_ENUM_BINARY_PARAMS(NNN, A, a)) \
            { \
               verifier.calls++; \
               tuple_type  args     = tuple_type(BOOST_PP_ENUM_PARAMS(NNN, a)); \
               queue_type& answers = answerMap[args]; \
               if(answers.empty() && lastAnswerMap.find(args) == lastAnswerMap.end()) \
                  { throw IncompleteImplementationException(); } \
               if(answers.size() > 0) \
               { \
                  lastAnswerMap[args] = answers.front(); \
                  answers.pop(); \
               } \
               return lastAnswerMap[args]->execute(); \
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
               answerMap[ongoingMatch].push(new Returns<void>()); \
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
               answerMap[ongoingMatch].push(new Returns<R>(value)); \
               return *this; \
            } \
         };

      BOOST_PP_REPEAT(MAX_VIRTUAL_FUNCTION_ARITY, DEFINE_ONGOING_STUBBING, ~)

      #undef DEFINE_ONGOING_STUBBING_COMMON
      #undef DEFINE_ONGOING_STUBBING

   } // namespace detail
} // namespace mockitopp

#endif //__MOCKITOPP_ONGOING_STUBBING_HPP__
