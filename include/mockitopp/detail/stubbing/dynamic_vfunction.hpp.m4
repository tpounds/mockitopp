#ifndef __MOCKITOPP_DYNAMIC_VFUNCTION_HPP__
#define __MOCKITOPP_DYNAMIC_VFUNCTION_HPP__

#include <algorithm>
#include <list>
#include <map>
#include <utility>

#include <mockitopp/exceptions.hpp>
#include <mockitopp/detail/stubbing/action.hpp>
#include <mockitopp/detail/stubbing/MatcherContainer.hpp>
#include <mockitopp/detail/stubbing/Verifier.hpp>
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
      struct dynamic_vfunction_base : dynamic_vfunction_polymorphic_destructor
      {
         typedef action<R>*             action_type;
         typedef std::list<action_type> action_queue_type;

         action_queue_type* ongoingMatch;

         dynamic_vfunction_base& thenReturn(R value)
         {
            ongoingMatch->push_back(new returnable_action<R>(value));
            return *this;
         }

         template <typename T>
         dynamic_vfunction_base& thenThrow(T throwable)
         {
            ongoingMatch->push_back(new throwable_action<R, T>(throwable));
            return *this;
         }
      };

      template <>
      struct dynamic_vfunction_base<void> : dynamic_vfunction_polymorphic_destructor
      {
         typedef action<void>*          action_type;
         typedef std::list<action_type> action_queue_type;

         action_queue_type* ongoingMatch;

         dynamic_vfunction_base& thenReturn()
         {
            ongoingMatch->push_back(new returnable_action<void>());
            return *this;
         }

         template <typename T>
         dynamic_vfunction_base& thenThrow(T throwable)
         {
            ongoingMatch->push_back(new throwable_action<void, T>(throwable));
            return *this;
         }
      };

      template <typename K, typename V>
      struct key_comparable_pair : public std::pair<K, V>
      {
         key_comparable_pair(const K& key, const V& pair)
            : std::pair<K, V>(key, pair)
            {}
      };

      template <typename K1, typename V1, typename K2, typename V2>
      bool operator== (const key_comparable_pair<K1, V1>& lhs, key_comparable_pair<K2, V2> rhs)
         { return lhs.first == rhs.first; }

      template <typename K1, typename V1, typename K2>
      bool operator== (const key_comparable_pair<K1, V1>& lhs, const K2& rhs)
         { return lhs.first == rhs; }

      template <typename T> struct dynamic_vfunction;

      // TODO: clean up impl
      // TODO: add sequence matcher

      //TODO: clean up typedef nomenclature
define(`DEFINE_DYNAMIC_VFUNCTION', `
      // $1 arity template
      template <typename R, typename C`'M4_ENUM_TRAILING_PARAMS($1, typename A)>
      struct dynamic_vfunction<R (C::*)(M4_ENUM_PARAMS($1, A))> : public dynamic_vfunction_base<R>, public Verifier
      {
         typedef tr1::tuple<M4_ENUM_BINARY_PARAMS($1,
            typename tr1::remove_const<typename tr1::remove_reference<A, >::type>::type,
               M4_INTERCEPT)> raw_tuple_type;
         typedef tr1::tuple<M4_ENUM_BINARY_PARAMS($1,
            MatcherContainer<typename tr1::remove_const<typename tr1::remove_reference<A, >::type>::type> ,
               M4_INTERCEPT)> matcher_tuple_type;

         typedef typename dynamic_vfunction_base<R>::action_type       action_type;
         typedef typename dynamic_vfunction_base<R>::action_queue_type action_queue_type;

         std::map<raw_tuple_type, action_queue_type>                raw_actions_map;
         std::list<key_comparable_pair<matcher_tuple_type, action_queue_type> > matcher_actions_map;

         dynamic_vfunction()
            : dynamic_vfunction_base<R>()
            , Verifier()
            , raw_actions_map()
            , matcher_actions_map()
            {}

         M4_IF($1, `dynamic_vfunction& when(M4_ENUM_BINARY_PARAMS($1, const matcher::Matcher<typename tr1::remove_const<typename tr1::remove_reference<A, >::type>::type>& a))
         {
            matcher_tuple_type args = matcher_tuple_type(M4_ENUM_PARAMS($1, a));
            typename std::list<key_comparable_pair<matcher_tuple_type, action_queue_type> >::iterator pair_it;
            pair_it = std::find(matcher_actions_map.begin(), matcher_actions_map.end(), args);
            if(pair_it == matcher_actions_map.end())
            {
               matcher_actions_map.push_back(key_comparable_pair<matcher_tuple_type, action_queue_type>(args, action_queue_type()));
               pair_it = --matcher_actions_map.end();
            }
            this->ongoingMatch = &(pair_it->second);
            return *this;
         }',)

         dynamic_vfunction& when(M4_ENUM_BINARY_PARAMS($1, A, a))
         {
            this->ongoingMatch = &(raw_actions_map[raw_tuple_type(M4_ENUM_PARAMS($1, a))]);
            return *this;
         }

         R invoke(M4_ENUM_BINARY_PARAMS($1, A, a))
         {
            this->calls++;
            raw_tuple_type     args    = raw_tuple_type(M4_ENUM_PARAMS($1, a));
            action_queue_type& actions = raw_actions_map[args];
            if(actions.empty())
            {
               typename std::list<key_comparable_pair<matcher_tuple_type, action_queue_type> >::iterator pair_it;
               pair_it = std::find(matcher_actions_map.begin(), matcher_actions_map.end(), args);
               if(pair_it == matcher_actions_map.end())
                  { throw partial_implementation_exception(); }
               actions = pair_it->second;
            }
            action_type action = actions.front();
            if(actions.size() > 1)
               { actions.pop_front(); }
            return action->invoke();
         }
      };
')dnl
dnl add one to max arity so we generate 0 argument case
M4_REPEAT(eval(MOCKITOPP_MAX_VIRTUAL_FUNCTION_ARITY + 1), `DEFINE_DYNAMIC_VFUNCTION')dnl
   } // namespace detail
} // namespace mockitopp

#endif //__MOCKITOPP_DYNAMIC_VFUNCTION_HPP__
