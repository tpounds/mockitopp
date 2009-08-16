#ifndef __MOCKITOPP_DYNAMIC_VFUNCTION_HPP__
#define __MOCKITOPP_DYNAMIC_VFUNCTION_HPP__

#include <algorithm>
#include <list>
#include <map>

#include <mockitopp/exceptions.hpp>
#include <mockitopp/detail/stubbing/action.hpp>
#include <mockitopp/detail/stubbing/MatcherContainer.hpp>
#include <mockitopp/detail/stubbing/Verifier.hpp>
#include <mockitopp/detail/util/KeyPair.hpp>
#include <mockitopp/detail/util/tr1_tuple.hpp>
#include <mockitopp/detail/util/tr1_type_traits.hpp>

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
      // simple base class to allow polymorphic desctruction with unknown subtype
      struct dynamic_vfunction_polymorphic_destructor { virtual ~dynamic_vfunction_polymorphic_destructor() {} };

      template <typename R>
      struct OngoingStubbingBase : dynamic_vfunction_polymorphic_destructor
      {
         typedef action<R>*             action_type;
         typedef std::list<action_type> queue_type;

         queue_type* ongoingMatch;

         OngoingStubbingBase& thenReturn(R value)
         {
            ongoingMatch->push_back(new returnable_action<R>(value));
            return *this;
         }

         template <typename T>
         OngoingStubbingBase& thenThrow(T throwable)
         {
            ongoingMatch->push_back(new throwable_action<R, T>(throwable));
            return *this;
         }
      };

      template <>
      struct OngoingStubbingBase<void> : dynamic_vfunction_polymorphic_destructor
      {
         typedef action<void>*          action_type;
         typedef std::list<action_type> queue_type;

         queue_type* ongoingMatch;

         OngoingStubbingBase& thenReturn()
         {
            ongoingMatch->push_back(new returnable_action<void>());
            return *this;
         }

         template <typename T>
         OngoingStubbingBase& thenThrow(T throwable)
         {
            ongoingMatch->push_back(new throwable_action<void, T>(throwable));
            return *this;
         }
      };

      template <typename T> struct OngoingStubbing;

      // TODO: clean up impl
      // TODO: add sequence matcher

      //TODO: clean up typedef nomenclature
define(`DEFINE_ONGOING_STUBBING', `
      template <typename R, typename C`'M4_ENUM_TRAILING_PARAMS($1, typename A)>
      struct OngoingStubbing<R (C::*)(M4_ENUM_PARAMS($1, A))> : public OngoingStubbingBase<R>, public Verifier
      {
         typedef tr1::tuple<M4_ENUM_BINARY_PARAMS($1,
            typename tr1::remove_const<typename tr1::remove_reference<A, >::type>::type,
               M4_INTERCEPT)> tuple_type;
         typedef tr1::tuple<M4_ENUM_BINARY_PARAMS($1,
            MatcherContainer<typename tr1::remove_const<typename tr1::remove_reference<A, >::type>::type> ,
               M4_INTERCEPT)> matcher_tuple_type;

         typedef typename OngoingStubbingBase<R>::action_type action_type;
         typedef typename OngoingStubbingBase<R>::queue_type  queue_type;

         //TODO: rename argument lists
         std::map<tuple_type, queue_type> actionMap;
         std::list<KeyPair<matcher_tuple_type, queue_type> > actionList;

         OngoingStubbing()
            : OngoingStubbingBase<R>()
            , Verifier()
            , actionMap()
            , actionList()
            {}

         M4_IF($1, `OngoingStubbing& when(M4_ENUM_BINARY_PARAMS($1, const matcher::Matcher<typename tr1::remove_const<typename tr1::remove_reference<A, >::type>::type>& a))
         {
            matcher_tuple_type arguments = matcher_tuple_type(M4_ENUM_PARAMS($1, a));
            typename std::list<KeyPair<matcher_tuple_type, queue_type> >::iterator pair_it;
            pair_it = std::find(actionList.begin(), actionList.end(), arguments);
            if(pair_it == actionList.end())
            {
               actionList.push_back(KeyPair<matcher_tuple_type, queue_type>(arguments, queue_type()));
               pair_it = --actionList.end();
            }
            this->ongoingMatch = &(pair_it->value);
            return *this;
         }',)

         OngoingStubbing& when(M4_ENUM_BINARY_PARAMS($1, A, a))
         {
            this->ongoingMatch = &(actionMap[tuple_type(M4_ENUM_PARAMS($1, a))]);
            return *this;
         }

         R invoke(M4_ENUM_BINARY_PARAMS($1, A, a))
         {
            this->calls++;
            tuple_type  args    = tuple_type(M4_ENUM_PARAMS($1, a));
            queue_type& actions = actionMap[args];
            if(actions.empty())
            {
               typename std::list<KeyPair<matcher_tuple_type, queue_type> >::iterator pair_it;
               pair_it = std::find(actionList.begin(), actionList.end(), args);
               if(pair_it == actionList.end())
                  { throw partial_implementation_exception(); }
               actions = pair_it->value;
            }
            action_type action = actions.front();
            if(actions.size() > 1)
               { actions.pop_front(); }
            return action->invoke();
         }
      };
')dnl
dnl add one to max arity so we generate 0 argument case
M4_REPEAT(eval(MOCKITOPP_MAX_VIRTUAL_FUNCTION_ARITY + 1), `DEFINE_ONGOING_STUBBING')dnl
   } // namespace detail
} // namespace mockitopp

#endif //__MOCKITOPP_DYNAMIC_VFUNCTION_HPP__
