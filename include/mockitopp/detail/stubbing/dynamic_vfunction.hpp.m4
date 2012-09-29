#ifndef __MOCKITOPP_DYNAMIC_VFUNCTION_HPP__
#define __MOCKITOPP_DYNAMIC_VFUNCTION_HPP__

#include <algorithm>
#include <list>
#include <utility>

#include <mockitopp/exceptions.hpp>
#include <mockitopp/detail/stubbing/action.hpp>
#include <mockitopp/detail/util/pointers.hpp>
#include <mockitopp/detail/util/tr1_tuple.hpp>
#include <mockitopp/matchers/Matcher.hpp>

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
      struct dynamic_vfunction_base
      {
         int calls;

         dynamic_vfunction_base()
            : calls(0)
            {}

         // allow polymorphic desctruction with unknown subtype
         virtual ~dynamic_vfunction_base() {}

         /**
          * verify method is called within a specified range
          *
          * @param min minimum times method should be called
          * @param max maximum times method should be called
          */
         bool between(int min, int max) const
         {
            if(calls >= min && calls <= max)
               { return true; }
            return false;
         }

         /**
          * verify method is called at least (n) times
          *
          * @param times minimum number of times method should be called
          */
         bool atLeast(int times) const
            { return calls >= times; }

         /**
          * verify method is called at most (n) times
          *
          * @param times maximum number of times method should be called
          */
         bool atMost(int times) const
            { return calls <= times; }

         /**
          * verify method is called exactly (n) times
          *
          * @param times exact number of times method should be called
          */
         bool exactly(int times) const
            { return calls == times; }

         /**
          * verify method is never called
          */
         bool never() const
            { return calls == 0; }
      };

      template <typename R>
      struct dynamic_vfunction_action
      {
         typedef shared_ptr<action<R> > action_type;
         typedef std::list<action_type> action_queue_type;

         action_queue_type* transient_stubbing;

         dynamic_vfunction_action& thenReturn(R value)
         {
            transient_stubbing->push_back(action_type(new returnable_action<R>(value)));
            return *this;
         }

         template <typename T>
         dynamic_vfunction_action& thenThrow(T throwable)
         {
            transient_stubbing->push_back(action_type(new throwable_action<R, T>(throwable)));
            return *this;
         }
      };

      template <>
      struct dynamic_vfunction_action<void>
      {
         typedef shared_ptr<action<void> > action_type;
         typedef std::list<action_type>    action_queue_type;

         action_queue_type* transient_stubbing;

         dynamic_vfunction_action& thenReturn()
         {
            transient_stubbing->push_back(action_type(new returnable_action<void>()));
            return *this;
         }

         template <typename T>
         dynamic_vfunction_action& thenThrow(T throwable)
         {
            transient_stubbing->push_back(action_type(new throwable_action<void, T>(throwable)));
            return *this;
         }
      };

      template <typename K, typename V>
      struct key_comparable_pair : public std::pair<K, V>
      {
         key_comparable_pair(const K& key, const V& pair)
            : std::pair<K, V>(key, pair)
            {}

         template <typename KRHS, typename VRHS>
         bool operator== (const key_comparable_pair<KRHS, VRHS>& rhs) const
            { return this->first == rhs.first; }

         template <typename RHS>
         bool operator== (const RHS& rhs) const
            { return this->first == rhs; }
      };

      template <typename T>
      struct matcher_element
      {
         matcher::Matcher<T>* matcher;
  
         matcher_element(const matcher::Matcher<T>& _matcher)
            : matcher(_matcher.clone())
            {}

         matcher_element(const matcher_element& rhs)
            : matcher(rhs.matcher->clone())
            {}

         ~matcher_element()
            { delete matcher; }

         bool operator== (typename tr1::add_reference<typename tr1::add_const<T>::type>::type rhs) const
            { return (*matcher == rhs); }

         bool operator== (const matcher_element& rhs) const
            { return (matcher == rhs.matcher); }
      };

      template <typename T> struct dynamic_vfunction;

      // TODO: clean up impl
      // TODO: add sequence matcher

      // TODO: clean up typedef nomenclature
define(`DEFINE_DYNAMIC_VFUNCTION', `
      // $1 arity template
      template <typename R, typename C`'M4_ENUM_TRAILING_PARAMS($1, typename A)>
      struct dynamic_vfunction<R (C::*)(M4_ENUM_PARAMS($1, A))>
         : private dynamic_vfunction_action<R>
         , public  dynamic_vfunction_base
      {
         typedef tr1::tuple<M4_ENUM_PARAMS($1, A)> raw_tuple_type;
         typedef tr1::tuple<M4_ENUM_BINARY_PARAMS($1, matcher_element<A, >, M4_INTERCEPT) > matcher_tuple_type;

         typedef typename dynamic_vfunction_action<R>::action_type       action_type;
         typedef typename dynamic_vfunction_action<R>::action_queue_type action_queue_type;

         std::list<key_comparable_pair<raw_tuple_type, action_queue_type> >     raw_actions_map;
         std::list<key_comparable_pair<matcher_tuple_type, action_queue_type> > matcher_actions_map;

         dynamic_vfunction()
            : dynamic_vfunction_action<R>()
            , dynamic_vfunction_base()
            , raw_actions_map()
            , matcher_actions_map()
            {}

         M4_IF($1, `dynamic_vfunction_action<R>& when(M4_ENUM_BINARY_PARAMS($1, const matcher::Matcher<A, >& a))
         {
            matcher_tuple_type args = matcher_tuple_type(M4_ENUM_PARAMS($1, a));
            typename std::list<key_comparable_pair<matcher_tuple_type, action_queue_type> >::iterator pair_it;
            pair_it = std::find(matcher_actions_map.begin(), matcher_actions_map.end(), args);
            if(pair_it == matcher_actions_map.end())
            {
               matcher_actions_map.push_back(key_comparable_pair<matcher_tuple_type, action_queue_type>(args, action_queue_type()));
               pair_it = --matcher_actions_map.end();
            }
            this->transient_stubbing = &(pair_it->second);
            return *this;
         }',)

         dynamic_vfunction_action<R>& when(M4_ENUM_BINARY_PARAMS($1, A, a))
         {
            raw_tuple_type args = raw_tuple_type(M4_ENUM_PARAMS($1, a));
            typename std::list<key_comparable_pair<raw_tuple_type, action_queue_type> >::iterator pair_it;
            pair_it = std::find(raw_actions_map.begin(), raw_actions_map.end(), args);
            if(pair_it == raw_actions_map.end())
            {
               raw_actions_map.push_back(key_comparable_pair<raw_tuple_type, action_queue_type>(args, action_queue_type()));
               pair_it = --raw_actions_map.end();
            }
            this->transient_stubbing = &(pair_it->second);
            return *this;
         }

         R invoke(M4_ENUM_BINARY_PARAMS($1, A, a))
         {
            this->calls++;
            raw_tuple_type     args    = raw_tuple_type(M4_ENUM_PARAMS($1, a));
            action_queue_type* actions = 0;
            typename std::list<key_comparable_pair<raw_tuple_type, action_queue_type> >::iterator raw_actions_it =
               std::find(raw_actions_map.begin(), raw_actions_map.end(), args);
            if(raw_actions_it != raw_actions_map.end())
               { actions = &(raw_actions_it->second); }
            if(actions == 0)
            {
               typename std::list<key_comparable_pair<matcher_tuple_type, action_queue_type> >::iterator pair_it;
               pair_it = std::find(matcher_actions_map.begin(), matcher_actions_map.end(), args);
               if(pair_it == matcher_actions_map.end())
                  { throw partial_implementation_exception(); }
               actions = &(pair_it->second);
            }
            action_type action = actions->front();
            if(actions->size() > 1)
               { actions->pop_front(); }
            return action->invoke();
         }
      };
')dnl
dnl add one to max arity so we generate 0 argument case
M4_REPEAT(eval(MOCKITOPP_MAX_VIRTUAL_FUNCTION_ARITY + 1), `DEFINE_DYNAMIC_VFUNCTION')dnl
   } // namespace detail
} // namespace mockitopp

#endif //__MOCKITOPP_DYNAMIC_VFUNCTION_HPP__