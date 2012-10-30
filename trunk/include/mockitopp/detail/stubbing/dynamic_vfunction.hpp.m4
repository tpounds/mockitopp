#ifndef __MOCKITOPP_DYNAMIC_VFUNCTION_HPP__
#define __MOCKITOPP_DYNAMIC_VFUNCTION_HPP__

#include <algorithm>
#include <list>

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
      struct dynamic_vfunction_progress : dynamic_vfunction_base
      {
         typedef shared_ptr<action<R> > action_type;
         typedef std::list<action_type> action_queue_type;

         action_queue_type* stubbing_progress;

         dynamic_vfunction_progress& thenReturn(R value)
         {
            stubbing_progress->push_back(action_type(new returnable_action<R>(value)));
            return *this;
         }

         template <typename T>
         dynamic_vfunction_progress& thenThrow(T throwable)
         {
            stubbing_progress->push_back(action_type(new throwable_action<R, T>(throwable)));
            return *this;
         }
      };

      template <>
      struct dynamic_vfunction_progress<void> : dynamic_vfunction_base
      {
         typedef shared_ptr<action<void> > action_type;
         typedef std::list<action_type>    action_queue_type;

         action_queue_type* stubbing_progress;

         dynamic_vfunction_progress& thenReturn()
         {
            stubbing_progress->push_back(action_type(new returnable_action<void>()));
            return *this;
         }

         template <typename T>
         dynamic_vfunction_progress& thenThrow(T throwable)
         {
            stubbing_progress->push_back(action_type(new throwable_action<void, T>(throwable)));
            return *this;
         }
      };

      template <typename K, typename V>
      struct map_entry
      {
         K key;
         V val;

         map_entry(const K& k, const V& v) : key(k), val(v) {}

         template <typename K2, typename V2>
            bool operator== (const map_entry<K2, V2>& rhs) const
            { return key == rhs.key; }

         template <typename T>
            bool operator== (const T& rhs) const
            { return key == rhs; }
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
      struct dynamic_vfunction<R (C::*)(M4_ENUM_PARAMS($1, A))> : private dynamic_vfunction_progress<R>
      {
         typedef tr1::tuple<M4_ENUM_PARAMS($1, A)> exact_tuple_type;
         typedef tr1::tuple<M4_ENUM_BINARY_PARAMS($1, matcher_element<A, >, M4_INTERCEPT) > fuzzy_tuple_type;

         typedef typename dynamic_vfunction_progress<R>::action_type       action_type;
         typedef typename dynamic_vfunction_progress<R>::action_queue_type action_queue_type;

         std::list<map_entry<exact_tuple_type, action_queue_type> > exact_matches;
         std::list<map_entry<fuzzy_tuple_type, action_queue_type> > fuzzy_matches;
         std::list<map_entry<exact_tuple_type, int> >               args_to_calls;

         dynamic_vfunction()
            : dynamic_vfunction_progress<R>()
            , exact_matches()
            , fuzzy_matches()
            {}

         template <typename T>
         int calculate_calls_for_arguments(const T args) {
            int calls = 0;
            typename std::list<map_entry<exact_tuple_type, int> >::iterator calls_it
               = args_to_calls.begin();
            for(; calls_it != args_to_calls.end(); calls_it++) {
               if(args == calls_it->key) {
                  calls += calls_it->val;
               }
            }
            return calls;
         }

         M4_IF($1, `dynamic_vfunction_progress<R>& when(M4_ENUM_BINARY_PARAMS($1, const matcher::Matcher<A, >& a))
         {
            const fuzzy_tuple_type args = fuzzy_tuple_type(M4_ENUM_PARAMS($1, a));
            typename std::list<map_entry<fuzzy_tuple_type, action_queue_type> >::iterator match
               = std::find(fuzzy_matches.begin(), fuzzy_matches.end(), args);
            if(match == fuzzy_matches.end())
            {
               fuzzy_matches.push_back(map_entry<fuzzy_tuple_type, action_queue_type>(args, action_queue_type()));
               match = --fuzzy_matches.end();
            }
            this->calls = calculate_calls_for_arguments(args);
            this->stubbing_progress = &(match->val);
            return *this;
         }',)

         dynamic_vfunction_progress<R>& when(M4_ENUM_BINARY_PARAMS($1, A, a))
         {
            const exact_tuple_type args = exact_tuple_type(M4_ENUM_PARAMS($1, a));
            typename std::list<map_entry<exact_tuple_type, action_queue_type> >::iterator match
               = std::find(exact_matches.begin(), exact_matches.end(), args);
            if(match == exact_matches.end())
            {
               exact_matches.push_back(map_entry<exact_tuple_type, action_queue_type>(args, action_queue_type()));
               match = --exact_matches.end();
            }
            this->calls = calculate_calls_for_arguments(args);
            this->stubbing_progress = &(match->val);
            return *this;
         }

         R invoke(M4_ENUM_BINARY_PARAMS($1, A, a))
         {
            const exact_tuple_type args = exact_tuple_type(M4_ENUM_PARAMS($1, a));

            typename std::list<map_entry<exact_tuple_type, int> >::iterator calls_it
               = std::find(args_to_calls.begin(), args_to_calls.end(), args);
            if(calls_it == args_to_calls.end()) {
               args_to_calls.push_back(map_entry<exact_tuple_type, int>(args, 1));
            } else {
               (calls_it->val)++;
            }

            action_queue_type* actions = 0;
            typename std::list<map_entry<exact_tuple_type, action_queue_type> >::iterator exact_match
               = std::find(exact_matches.begin(), exact_matches.end(), args);
            if(exact_match != exact_matches.end())
               { actions = &(exact_match->val); }
            if(!actions)
            {
               typename std::list<map_entry<fuzzy_tuple_type, action_queue_type> >::iterator fuzzy_match
                  = std::find(fuzzy_matches.begin(), fuzzy_matches.end(), args);
               if(fuzzy_match == fuzzy_matches.end())
                   { throw partial_implementation_exception(); }
               actions = &(fuzzy_match->val);
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
