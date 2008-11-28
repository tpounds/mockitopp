#ifndef __MOCKITOPP_ONGOING_STUBBING_HPP__
#define __MOCKITOPP_ONGOING_STUBBING_HPP__

#include <map>
#include <queue>

#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_params.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>

#include <mockitopp/detail/exception/IncompleteImplementationException.hpp>
#include <mockitopp/detail/stubbing/Answer.hpp>
#include <mockitopp/detail/stubbing/Returns.hpp>
#include <mockitopp/detail/stubbing/Throws.hpp>
#include <mockitopp/detail/utility/Tuple.hpp>

// TODO: add documentation
namespace mockitopp
{
   namespace detail
   {
      template <typename T> struct OngoingStubbing;

      // TODO: clean up impl
      // TODO: add sequence matcher

      #define DEFINE_ARGUMENT_MATCHER_IMPL_VOID(ZZZ, NNN, TTT) \
         template <typename C BOOST_PP_ENUM_TRAILING_PARAMS(NNN, typename A)> \
         struct OngoingStubbing<void (C::*)(BOOST_PP_ENUM_PARAMS(NNN, A))> \
         { \
            DEFINE_ARGUMENT_MATCHER_IMPL_COMMON(ZZZ, NNN, TTT, void) \
         \
            OngoingStubbing& thenReturn() \
            { \
               answerMap[ongoingMatch].push(new Returns<void>()); \
               return *this; \
            } \
         };

      #define DEFINE_ARGUMENT_MATCHER_IMPL_NON_VOID(ZZZ, NNN, TTT) \
         template <typename R, typename C BOOST_PP_ENUM_TRAILING_PARAMS(NNN, typename A)> \
         struct OngoingStubbing<R (C::*)(BOOST_PP_ENUM_PARAMS(NNN, A))> \
         { \
            DEFINE_ARGUMENT_MATCHER_IMPL_COMMON(ZZZ, NNN, TTT, R) \
         \
            OngoingStubbing& thenReturn(R value) \
            { \
               answerMap[ongoingMatch].push(new Returns<R>(value)); \
               return *this; \
            } \
         };

      #define DEFINE_ARGUMENT_MATCHER_IMPL_COMMON(ZZZ, NNN, TTT, RRR) \
            typedef Tuple<BOOST_PP_ENUM_PARAMS(NNN, A)> args_type; \
            typedef Answer<RRR>*                               answer_type; \
            typedef std::queue<answer_type>                    queue_type; \
            typedef std::map<args_type, queue_type>            map_type; \
         \
            map_type    answerMap; \
            answer_type lastAnswer; \
            args_type   ongoingMatch; \
            int         calls; \
         \
            OngoingStubbing() \
               : answerMap() \
               , lastAnswer(NULL) \
               , ongoingMatch() \
               , calls(0) \
               {} \
         \
            OngoingStubbing& operator() (BOOST_PP_ENUM_BINARY_PARAMS(NNN, A, a)) \
            { \
               ongoingMatch = args_type(BOOST_PP_ENUM_PARAMS(NNN, a)); \
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
               calls++; \
               args_type   args     = args_type(BOOST_PP_ENUM_PARAMS(NNN, a)); \
               queue_type& answer_q = answerMap[args]; \
               if(!answer_q.empty()) \
               { \
                  lastAnswer = answer_q.front(); \
                  answer_q.pop(); \
               } \
               if(lastAnswer != NULL) \
                  { return lastAnswer->execute(); } \
               throw IncompleteImplementationException(); \
            } \
         \
            int getCalls() const \
               { return calls; }

      BOOST_PP_REPEAT(MAX_VIRTUAL_FUNCTION_ARITY, DEFINE_ARGUMENT_MATCHER_IMPL_VOID, ~)
      BOOST_PP_REPEAT(MAX_VIRTUAL_FUNCTION_ARITY, DEFINE_ARGUMENT_MATCHER_IMPL_NON_VOID, ~)

      #undef DEFINE_ARGUMENT_MATCHER_IMPL

   } // namespace detail
} // namespace mockitopp

#endif //__MOCKITOPP_ONGOING_STUBBING_HPP__
