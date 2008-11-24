#ifndef __MOCKITOPP_ARGUMENT_MATCHER_HPP__
#define __MOCKITOPP_ARGUMENT_MATCHER_HPP__

#include <map>
#include <queue>

#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/tuple/tuple_comparison.hpp>

#include <mockitopp/detail/action/Action.hpp>
#include <mockitopp/detail/action/DefaultAction.hpp>
#include <mockitopp/detail/action/ReturnableAction.hpp>
#include <mockitopp/detail/action/ThrowableAction.hpp>

// TODO: add documentation
namespace mockitopp
{
   namespace detail
   {
      template <typename T, typename ENABLE = void> struct ArgumentMatcher;

      // TODO: clean up impl
      // TODO: add sequence matcher

      #define DEFINE_ARGUMENT_MATCHER_IMPL_VOID(ZZZ, NNN, TTT) \
         template <typename C BOOST_PP_COMMA_IF(NNN) BOOST_PP_ENUM_PARAMS(NNN, typename A)> \
         struct ArgumentMatcher<void (C::*)(BOOST_PP_ENUM_PARAMS(NNN, A))> \
         { \
            DEFINE_ARGUMENT_MATCHER_IMPL_COMMON(ZZZ, NNN, TTT, void) \
         \
            ArgumentMatcher& thenReturn() \
            { \
               actionMap[ongoingMatch].push(new ReturnableAction<void>()); \
               return *this; \
            } \
         };

      #define DEFINE_ARGUMENT_MATCHER_IMPL_NON_VOID(ZZZ, NNN, TTT) \
         template <typename R, typename C BOOST_PP_COMMA_IF(NNN) BOOST_PP_ENUM_PARAMS(NNN, typename A)> \
         struct ArgumentMatcher<R (C::*)(BOOST_PP_ENUM_PARAMS(NNN, A))> \
         { \
            DEFINE_ARGUMENT_MATCHER_IMPL_COMMON(ZZZ, NNN, TTT, R) \
         \
            ArgumentMatcher& thenReturn(R value) \
            { \
               actionMap[ongoingMatch].push(new ReturnableAction<R>(value)); \
               return *this; \
            } \
         };

      #define DEFINE_ARGUMENT_MATCHER_IMPL_COMMON(ZZZ, NNN, TTT, RRR) \
            typedef boost::tuple<BOOST_PP_ENUM_PARAMS(NNN, A)> args_type; \
            typedef Action<RRR>*                               action_type; \
            typedef std::queue<action_type>                    queue_type; \
            typedef std::map<args_type, queue_type>            map_type; \
         \
            map_type    actionMap; \
            action_type defaultAction; \
            args_type   ongoingMatch; \
         \
            ArgumentMatcher() \
               : actionMap() \
               , defaultAction(new DefaultAction<RRR>()) \
               , ongoingMatch() \
               {} \
         \
            ArgumentMatcher& operator() (BOOST_PP_ENUM_BINARY_PARAMS(NNN, A, a)) \
            { \
               ongoingMatch = args_type(BOOST_PP_ENUM_PARAMS(NNN, a)); \
               return *this; \
            } \
         \
            template <typename T> \
            ArgumentMatcher& thenThrow(T throwable) \
            { \
               actionMap[ongoingMatch].push(new ThrowableAction<RRR, T>(throwable)); \
               return *this; \
            } \
         \
            RRR invoke(BOOST_PP_ENUM_BINARY_PARAMS(NNN, A, a)) \
            { \
               args_type   args     = args_type(BOOST_PP_ENUM_PARAMS(NNN, a)); \
               queue_type& action_q = actionMap[args]; \
               if(action_q.empty()) \
                  { return defaultAction->execute(); } \
               else if(action_q.size() == 1) \
                  { return action_q.front()->execute(); } \
               action_type action = action_q.front(); \
               action_q.pop(); \
               return action->execute(); \
            }

      BOOST_PP_REPEAT(MAX_VIRTUAL_FUNCTION_ARITY, DEFINE_ARGUMENT_MATCHER_IMPL_VOID, ~)
      BOOST_PP_REPEAT(MAX_VIRTUAL_FUNCTION_ARITY, DEFINE_ARGUMENT_MATCHER_IMPL_NON_VOID, ~)

      #undef DEFINE_ARGUMENT_MATCHER_IMPL

   } // namespace detail
} // namespace mockitopp

#endif //__MOCKITOPP_ARGUMENT_MATCHER_HPP__
