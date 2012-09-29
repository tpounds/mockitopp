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
 
      // 0 arity template
      template <typename R, typename C>
      struct dynamic_vfunction<R (C::*)()>
         : private dynamic_vfunction_action<R>
         , public  dynamic_vfunction_base
      {
         typedef tr1::tuple<> raw_tuple_type;
         typedef tr1::tuple< > matcher_tuple_type;

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

         

         dynamic_vfunction_action<R>& when()
         {
            raw_tuple_type args = raw_tuple_type();
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

         R invoke()
         {
            this->calls++;
            raw_tuple_type     args    = raw_tuple_type();
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
 
      // 1 arity template
      template <typename R, typename C, typename A0>
      struct dynamic_vfunction<R (C::*)(A0)>
         : private dynamic_vfunction_action<R>
         , public  dynamic_vfunction_base
      {
         typedef tr1::tuple<A0> raw_tuple_type;
         typedef tr1::tuple<matcher_element<A0 > > matcher_tuple_type;

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

         dynamic_vfunction_action<R>& when(const matcher::Matcher<A0 >& a0)
         {
            matcher_tuple_type args = matcher_tuple_type(a0);
            typename std::list<key_comparable_pair<matcher_tuple_type, action_queue_type> >::iterator pair_it;
            pair_it = std::find(matcher_actions_map.begin(), matcher_actions_map.end(), args);
            if(pair_it == matcher_actions_map.end())
            {
               matcher_actions_map.push_back(key_comparable_pair<matcher_tuple_type, action_queue_type>(args, action_queue_type()));
               pair_it = --matcher_actions_map.end();
            }
            this->transient_stubbing = &(pair_it->second);
            return *this;
         }

         dynamic_vfunction_action<R>& when(A0 a0)
         {
            raw_tuple_type args = raw_tuple_type(a0);
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

         R invoke(A0 a0)
         {
            this->calls++;
            raw_tuple_type     args    = raw_tuple_type(a0);
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
 
      // 2 arity template
      template <typename R, typename C, typename A0, typename A1>
      struct dynamic_vfunction<R (C::*)(A0, A1)>
         : private dynamic_vfunction_action<R>
         , public  dynamic_vfunction_base
      {
         typedef tr1::tuple<A0, A1> raw_tuple_type;
         typedef tr1::tuple<matcher_element<A0 >, matcher_element<A1 > > matcher_tuple_type;

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

         dynamic_vfunction_action<R>& when(const matcher::Matcher<A0 >& a0, const matcher::Matcher<A1 >& a1)
         {
            matcher_tuple_type args = matcher_tuple_type(a0, a1);
            typename std::list<key_comparable_pair<matcher_tuple_type, action_queue_type> >::iterator pair_it;
            pair_it = std::find(matcher_actions_map.begin(), matcher_actions_map.end(), args);
            if(pair_it == matcher_actions_map.end())
            {
               matcher_actions_map.push_back(key_comparable_pair<matcher_tuple_type, action_queue_type>(args, action_queue_type()));
               pair_it = --matcher_actions_map.end();
            }
            this->transient_stubbing = &(pair_it->second);
            return *this;
         }

         dynamic_vfunction_action<R>& when(A0 a0, A1 a1)
         {
            raw_tuple_type args = raw_tuple_type(a0, a1);
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

         R invoke(A0 a0, A1 a1)
         {
            this->calls++;
            raw_tuple_type     args    = raw_tuple_type(a0, a1);
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
 
      // 3 arity template
      template <typename R, typename C, typename A0, typename A1, typename A2>
      struct dynamic_vfunction<R (C::*)(A0, A1, A2)>
         : private dynamic_vfunction_action<R>
         , public  dynamic_vfunction_base
      {
         typedef tr1::tuple<A0, A1, A2> raw_tuple_type;
         typedef tr1::tuple<matcher_element<A0 >, matcher_element<A1 >, matcher_element<A2 > > matcher_tuple_type;

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

         dynamic_vfunction_action<R>& when(const matcher::Matcher<A0 >& a0, const matcher::Matcher<A1 >& a1, const matcher::Matcher<A2 >& a2)
         {
            matcher_tuple_type args = matcher_tuple_type(a0, a1, a2);
            typename std::list<key_comparable_pair<matcher_tuple_type, action_queue_type> >::iterator pair_it;
            pair_it = std::find(matcher_actions_map.begin(), matcher_actions_map.end(), args);
            if(pair_it == matcher_actions_map.end())
            {
               matcher_actions_map.push_back(key_comparable_pair<matcher_tuple_type, action_queue_type>(args, action_queue_type()));
               pair_it = --matcher_actions_map.end();
            }
            this->transient_stubbing = &(pair_it->second);
            return *this;
         }

         dynamic_vfunction_action<R>& when(A0 a0, A1 a1, A2 a2)
         {
            raw_tuple_type args = raw_tuple_type(a0, a1, a2);
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

         R invoke(A0 a0, A1 a1, A2 a2)
         {
            this->calls++;
            raw_tuple_type     args    = raw_tuple_type(a0, a1, a2);
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
 
      // 4 arity template
      template <typename R, typename C, typename A0, typename A1, typename A2, typename A3>
      struct dynamic_vfunction<R (C::*)(A0, A1, A2, A3)>
         : private dynamic_vfunction_action<R>
         , public  dynamic_vfunction_base
      {
         typedef tr1::tuple<A0, A1, A2, A3> raw_tuple_type;
         typedef tr1::tuple<matcher_element<A0 >, matcher_element<A1 >, matcher_element<A2 >, matcher_element<A3 > > matcher_tuple_type;

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

         dynamic_vfunction_action<R>& when(const matcher::Matcher<A0 >& a0, const matcher::Matcher<A1 >& a1, const matcher::Matcher<A2 >& a2, const matcher::Matcher<A3 >& a3)
         {
            matcher_tuple_type args = matcher_tuple_type(a0, a1, a2, a3);
            typename std::list<key_comparable_pair<matcher_tuple_type, action_queue_type> >::iterator pair_it;
            pair_it = std::find(matcher_actions_map.begin(), matcher_actions_map.end(), args);
            if(pair_it == matcher_actions_map.end())
            {
               matcher_actions_map.push_back(key_comparable_pair<matcher_tuple_type, action_queue_type>(args, action_queue_type()));
               pair_it = --matcher_actions_map.end();
            }
            this->transient_stubbing = &(pair_it->second);
            return *this;
         }

         dynamic_vfunction_action<R>& when(A0 a0, A1 a1, A2 a2, A3 a3)
         {
            raw_tuple_type args = raw_tuple_type(a0, a1, a2, a3);
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

         R invoke(A0 a0, A1 a1, A2 a2, A3 a3)
         {
            this->calls++;
            raw_tuple_type     args    = raw_tuple_type(a0, a1, a2, a3);
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
 
      // 5 arity template
      template <typename R, typename C, typename A0, typename A1, typename A2, typename A3, typename A4>
      struct dynamic_vfunction<R (C::*)(A0, A1, A2, A3, A4)>
         : private dynamic_vfunction_action<R>
         , public  dynamic_vfunction_base
      {
         typedef tr1::tuple<A0, A1, A2, A3, A4> raw_tuple_type;
         typedef tr1::tuple<matcher_element<A0 >, matcher_element<A1 >, matcher_element<A2 >, matcher_element<A3 >, matcher_element<A4 > > matcher_tuple_type;

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

         dynamic_vfunction_action<R>& when(const matcher::Matcher<A0 >& a0, const matcher::Matcher<A1 >& a1, const matcher::Matcher<A2 >& a2, const matcher::Matcher<A3 >& a3, const matcher::Matcher<A4 >& a4)
         {
            matcher_tuple_type args = matcher_tuple_type(a0, a1, a2, a3, a4);
            typename std::list<key_comparable_pair<matcher_tuple_type, action_queue_type> >::iterator pair_it;
            pair_it = std::find(matcher_actions_map.begin(), matcher_actions_map.end(), args);
            if(pair_it == matcher_actions_map.end())
            {
               matcher_actions_map.push_back(key_comparable_pair<matcher_tuple_type, action_queue_type>(args, action_queue_type()));
               pair_it = --matcher_actions_map.end();
            }
            this->transient_stubbing = &(pair_it->second);
            return *this;
         }

         dynamic_vfunction_action<R>& when(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4)
         {
            raw_tuple_type args = raw_tuple_type(a0, a1, a2, a3, a4);
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

         R invoke(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4)
         {
            this->calls++;
            raw_tuple_type     args    = raw_tuple_type(a0, a1, a2, a3, a4);
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
 
      // 6 arity template
      template <typename R, typename C, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5>
      struct dynamic_vfunction<R (C::*)(A0, A1, A2, A3, A4, A5)>
         : private dynamic_vfunction_action<R>
         , public  dynamic_vfunction_base
      {
         typedef tr1::tuple<A0, A1, A2, A3, A4, A5> raw_tuple_type;
         typedef tr1::tuple<matcher_element<A0 >, matcher_element<A1 >, matcher_element<A2 >, matcher_element<A3 >, matcher_element<A4 >, matcher_element<A5 > > matcher_tuple_type;

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

         dynamic_vfunction_action<R>& when(const matcher::Matcher<A0 >& a0, const matcher::Matcher<A1 >& a1, const matcher::Matcher<A2 >& a2, const matcher::Matcher<A3 >& a3, const matcher::Matcher<A4 >& a4, const matcher::Matcher<A5 >& a5)
         {
            matcher_tuple_type args = matcher_tuple_type(a0, a1, a2, a3, a4, a5);
            typename std::list<key_comparable_pair<matcher_tuple_type, action_queue_type> >::iterator pair_it;
            pair_it = std::find(matcher_actions_map.begin(), matcher_actions_map.end(), args);
            if(pair_it == matcher_actions_map.end())
            {
               matcher_actions_map.push_back(key_comparable_pair<matcher_tuple_type, action_queue_type>(args, action_queue_type()));
               pair_it = --matcher_actions_map.end();
            }
            this->transient_stubbing = &(pair_it->second);
            return *this;
         }

         dynamic_vfunction_action<R>& when(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5)
         {
            raw_tuple_type args = raw_tuple_type(a0, a1, a2, a3, a4, a5);
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

         R invoke(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5)
         {
            this->calls++;
            raw_tuple_type     args    = raw_tuple_type(a0, a1, a2, a3, a4, a5);
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
 
      // 7 arity template
      template <typename R, typename C, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
      struct dynamic_vfunction<R (C::*)(A0, A1, A2, A3, A4, A5, A6)>
         : private dynamic_vfunction_action<R>
         , public  dynamic_vfunction_base
      {
         typedef tr1::tuple<A0, A1, A2, A3, A4, A5, A6> raw_tuple_type;
         typedef tr1::tuple<matcher_element<A0 >, matcher_element<A1 >, matcher_element<A2 >, matcher_element<A3 >, matcher_element<A4 >, matcher_element<A5 >, matcher_element<A6 > > matcher_tuple_type;

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

         dynamic_vfunction_action<R>& when(const matcher::Matcher<A0 >& a0, const matcher::Matcher<A1 >& a1, const matcher::Matcher<A2 >& a2, const matcher::Matcher<A3 >& a3, const matcher::Matcher<A4 >& a4, const matcher::Matcher<A5 >& a5, const matcher::Matcher<A6 >& a6)
         {
            matcher_tuple_type args = matcher_tuple_type(a0, a1, a2, a3, a4, a5, a6);
            typename std::list<key_comparable_pair<matcher_tuple_type, action_queue_type> >::iterator pair_it;
            pair_it = std::find(matcher_actions_map.begin(), matcher_actions_map.end(), args);
            if(pair_it == matcher_actions_map.end())
            {
               matcher_actions_map.push_back(key_comparable_pair<matcher_tuple_type, action_queue_type>(args, action_queue_type()));
               pair_it = --matcher_actions_map.end();
            }
            this->transient_stubbing = &(pair_it->second);
            return *this;
         }

         dynamic_vfunction_action<R>& when(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6)
         {
            raw_tuple_type args = raw_tuple_type(a0, a1, a2, a3, a4, a5, a6);
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

         R invoke(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6)
         {
            this->calls++;
            raw_tuple_type     args    = raw_tuple_type(a0, a1, a2, a3, a4, a5, a6);
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
 
      // 8 arity template
      template <typename R, typename C, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7>
      struct dynamic_vfunction<R (C::*)(A0, A1, A2, A3, A4, A5, A6, A7)>
         : private dynamic_vfunction_action<R>
         , public  dynamic_vfunction_base
      {
         typedef tr1::tuple<A0, A1, A2, A3, A4, A5, A6, A7> raw_tuple_type;
         typedef tr1::tuple<matcher_element<A0 >, matcher_element<A1 >, matcher_element<A2 >, matcher_element<A3 >, matcher_element<A4 >, matcher_element<A5 >, matcher_element<A6 >, matcher_element<A7 > > matcher_tuple_type;

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

         dynamic_vfunction_action<R>& when(const matcher::Matcher<A0 >& a0, const matcher::Matcher<A1 >& a1, const matcher::Matcher<A2 >& a2, const matcher::Matcher<A3 >& a3, const matcher::Matcher<A4 >& a4, const matcher::Matcher<A5 >& a5, const matcher::Matcher<A6 >& a6, const matcher::Matcher<A7 >& a7)
         {
            matcher_tuple_type args = matcher_tuple_type(a0, a1, a2, a3, a4, a5, a6, a7);
            typename std::list<key_comparable_pair<matcher_tuple_type, action_queue_type> >::iterator pair_it;
            pair_it = std::find(matcher_actions_map.begin(), matcher_actions_map.end(), args);
            if(pair_it == matcher_actions_map.end())
            {
               matcher_actions_map.push_back(key_comparable_pair<matcher_tuple_type, action_queue_type>(args, action_queue_type()));
               pair_it = --matcher_actions_map.end();
            }
            this->transient_stubbing = &(pair_it->second);
            return *this;
         }

         dynamic_vfunction_action<R>& when(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7)
         {
            raw_tuple_type args = raw_tuple_type(a0, a1, a2, a3, a4, a5, a6, a7);
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

         R invoke(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7)
         {
            this->calls++;
            raw_tuple_type     args    = raw_tuple_type(a0, a1, a2, a3, a4, a5, a6, a7);
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
 
      // 9 arity template
      template <typename R, typename C, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8>
      struct dynamic_vfunction<R (C::*)(A0, A1, A2, A3, A4, A5, A6, A7, A8)>
         : private dynamic_vfunction_action<R>
         , public  dynamic_vfunction_base
      {
         typedef tr1::tuple<A0, A1, A2, A3, A4, A5, A6, A7, A8> raw_tuple_type;
         typedef tr1::tuple<matcher_element<A0 >, matcher_element<A1 >, matcher_element<A2 >, matcher_element<A3 >, matcher_element<A4 >, matcher_element<A5 >, matcher_element<A6 >, matcher_element<A7 >, matcher_element<A8 > > matcher_tuple_type;

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

         dynamic_vfunction_action<R>& when(const matcher::Matcher<A0 >& a0, const matcher::Matcher<A1 >& a1, const matcher::Matcher<A2 >& a2, const matcher::Matcher<A3 >& a3, const matcher::Matcher<A4 >& a4, const matcher::Matcher<A5 >& a5, const matcher::Matcher<A6 >& a6, const matcher::Matcher<A7 >& a7, const matcher::Matcher<A8 >& a8)
         {
            matcher_tuple_type args = matcher_tuple_type(a0, a1, a2, a3, a4, a5, a6, a7, a8);
            typename std::list<key_comparable_pair<matcher_tuple_type, action_queue_type> >::iterator pair_it;
            pair_it = std::find(matcher_actions_map.begin(), matcher_actions_map.end(), args);
            if(pair_it == matcher_actions_map.end())
            {
               matcher_actions_map.push_back(key_comparable_pair<matcher_tuple_type, action_queue_type>(args, action_queue_type()));
               pair_it = --matcher_actions_map.end();
            }
            this->transient_stubbing = &(pair_it->second);
            return *this;
         }

         dynamic_vfunction_action<R>& when(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8)
         {
            raw_tuple_type args = raw_tuple_type(a0, a1, a2, a3, a4, a5, a6, a7, a8);
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

         R invoke(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8)
         {
            this->calls++;
            raw_tuple_type     args    = raw_tuple_type(a0, a1, a2, a3, a4, a5, a6, a7, a8);
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
 
      // 10 arity template
      template <typename R, typename C, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9>
      struct dynamic_vfunction<R (C::*)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9)>
         : private dynamic_vfunction_action<R>
         , public  dynamic_vfunction_base
      {
         typedef tr1::tuple<A0, A1, A2, A3, A4, A5, A6, A7, A8, A9> raw_tuple_type;
         typedef tr1::tuple<matcher_element<A0 >, matcher_element<A1 >, matcher_element<A2 >, matcher_element<A3 >, matcher_element<A4 >, matcher_element<A5 >, matcher_element<A6 >, matcher_element<A7 >, matcher_element<A8 >, matcher_element<A9 > > matcher_tuple_type;

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

         dynamic_vfunction_action<R>& when(const matcher::Matcher<A0 >& a0, const matcher::Matcher<A1 >& a1, const matcher::Matcher<A2 >& a2, const matcher::Matcher<A3 >& a3, const matcher::Matcher<A4 >& a4, const matcher::Matcher<A5 >& a5, const matcher::Matcher<A6 >& a6, const matcher::Matcher<A7 >& a7, const matcher::Matcher<A8 >& a8, const matcher::Matcher<A9 >& a9)
         {
            matcher_tuple_type args = matcher_tuple_type(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9);
            typename std::list<key_comparable_pair<matcher_tuple_type, action_queue_type> >::iterator pair_it;
            pair_it = std::find(matcher_actions_map.begin(), matcher_actions_map.end(), args);
            if(pair_it == matcher_actions_map.end())
            {
               matcher_actions_map.push_back(key_comparable_pair<matcher_tuple_type, action_queue_type>(args, action_queue_type()));
               pair_it = --matcher_actions_map.end();
            }
            this->transient_stubbing = &(pair_it->second);
            return *this;
         }

         dynamic_vfunction_action<R>& when(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9)
         {
            raw_tuple_type args = raw_tuple_type(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9);
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

         R invoke(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9)
         {
            this->calls++;
            raw_tuple_type     args    = raw_tuple_type(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9);
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
   } // namespace detail
} // namespace mockitopp

#endif //__MOCKITOPP_DYNAMIC_VFUNCTION_HPP__
