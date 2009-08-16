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
 
      template <typename R, typename C>
      struct OngoingStubbing<R (C::*)()> : public OngoingStubbingBase<R>, public Verifier
      {
         typedef tr1::tuple<> tuple_type;
         typedef tr1::tuple<> matcher_tuple_type;

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

         

         OngoingStubbing& when()
         {
            this->ongoingMatch = &(actionMap[tuple_type()]);
            return *this;
         }

         R invoke()
         {
            this->calls++;
            tuple_type  args    = tuple_type();
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
 
      template <typename R, typename C, typename A0>
      struct OngoingStubbing<R (C::*)(A0)> : public OngoingStubbingBase<R>, public Verifier
      {
         typedef tr1::tuple<typename tr1::remove_const<typename tr1::remove_reference<A0 >::type>::type> tuple_type;
         typedef tr1::tuple<MatcherContainer<typename tr1::remove_const<typename tr1::remove_reference<A0 >::type>::type> > matcher_tuple_type;

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

         OngoingStubbing& when(const matcher::Matcher<typename tr1::remove_const<typename tr1::remove_reference<A0 >::type>::type>& a0)
         {
            matcher_tuple_type arguments = matcher_tuple_type(a0);
            typename std::list<KeyPair<matcher_tuple_type, queue_type> >::iterator pair_it;
            pair_it = std::find(actionList.begin(), actionList.end(), arguments);
            if(pair_it == actionList.end())
            {
               actionList.push_back(KeyPair<matcher_tuple_type, queue_type>(arguments, queue_type()));
               pair_it = --actionList.end();
            }
            this->ongoingMatch = &(pair_it->value);
            return *this;
         }

         OngoingStubbing& when(A0 a0)
         {
            this->ongoingMatch = &(actionMap[tuple_type(a0)]);
            return *this;
         }

         R invoke(A0 a0)
         {
            this->calls++;
            tuple_type  args    = tuple_type(a0);
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
 
      template <typename R, typename C, typename A0, typename A1>
      struct OngoingStubbing<R (C::*)(A0, A1)> : public OngoingStubbingBase<R>, public Verifier
      {
         typedef tr1::tuple<typename tr1::remove_const<typename tr1::remove_reference<A0 >::type>::type, typename tr1::remove_const<typename tr1::remove_reference<A1 >::type>::type> tuple_type;
         typedef tr1::tuple<MatcherContainer<typename tr1::remove_const<typename tr1::remove_reference<A0 >::type>::type> , MatcherContainer<typename tr1::remove_const<typename tr1::remove_reference<A1 >::type>::type> > matcher_tuple_type;

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

         OngoingStubbing& when(const matcher::Matcher<typename tr1::remove_const<typename tr1::remove_reference<A0 >::type>::type>& a0, const matcher::Matcher<typename tr1::remove_const<typename tr1::remove_reference<A1 >::type>::type>& a1)
         {
            matcher_tuple_type arguments = matcher_tuple_type(a0, a1);
            typename std::list<KeyPair<matcher_tuple_type, queue_type> >::iterator pair_it;
            pair_it = std::find(actionList.begin(), actionList.end(), arguments);
            if(pair_it == actionList.end())
            {
               actionList.push_back(KeyPair<matcher_tuple_type, queue_type>(arguments, queue_type()));
               pair_it = --actionList.end();
            }
            this->ongoingMatch = &(pair_it->value);
            return *this;
         }

         OngoingStubbing& when(A0 a0, A1 a1)
         {
            this->ongoingMatch = &(actionMap[tuple_type(a0, a1)]);
            return *this;
         }

         R invoke(A0 a0, A1 a1)
         {
            this->calls++;
            tuple_type  args    = tuple_type(a0, a1);
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
 
      template <typename R, typename C, typename A0, typename A1, typename A2>
      struct OngoingStubbing<R (C::*)(A0, A1, A2)> : public OngoingStubbingBase<R>, public Verifier
      {
         typedef tr1::tuple<typename tr1::remove_const<typename tr1::remove_reference<A0 >::type>::type, typename tr1::remove_const<typename tr1::remove_reference<A1 >::type>::type, typename tr1::remove_const<typename tr1::remove_reference<A2 >::type>::type> tuple_type;
         typedef tr1::tuple<MatcherContainer<typename tr1::remove_const<typename tr1::remove_reference<A0 >::type>::type> , MatcherContainer<typename tr1::remove_const<typename tr1::remove_reference<A1 >::type>::type> , MatcherContainer<typename tr1::remove_const<typename tr1::remove_reference<A2 >::type>::type> > matcher_tuple_type;

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

         OngoingStubbing& when(const matcher::Matcher<typename tr1::remove_const<typename tr1::remove_reference<A0 >::type>::type>& a0, const matcher::Matcher<typename tr1::remove_const<typename tr1::remove_reference<A1 >::type>::type>& a1, const matcher::Matcher<typename tr1::remove_const<typename tr1::remove_reference<A2 >::type>::type>& a2)
         {
            matcher_tuple_type arguments = matcher_tuple_type(a0, a1, a2);
            typename std::list<KeyPair<matcher_tuple_type, queue_type> >::iterator pair_it;
            pair_it = std::find(actionList.begin(), actionList.end(), arguments);
            if(pair_it == actionList.end())
            {
               actionList.push_back(KeyPair<matcher_tuple_type, queue_type>(arguments, queue_type()));
               pair_it = --actionList.end();
            }
            this->ongoingMatch = &(pair_it->value);
            return *this;
         }

         OngoingStubbing& when(A0 a0, A1 a1, A2 a2)
         {
            this->ongoingMatch = &(actionMap[tuple_type(a0, a1, a2)]);
            return *this;
         }

         R invoke(A0 a0, A1 a1, A2 a2)
         {
            this->calls++;
            tuple_type  args    = tuple_type(a0, a1, a2);
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
 
      template <typename R, typename C, typename A0, typename A1, typename A2, typename A3>
      struct OngoingStubbing<R (C::*)(A0, A1, A2, A3)> : public OngoingStubbingBase<R>, public Verifier
      {
         typedef tr1::tuple<typename tr1::remove_const<typename tr1::remove_reference<A0 >::type>::type, typename tr1::remove_const<typename tr1::remove_reference<A1 >::type>::type, typename tr1::remove_const<typename tr1::remove_reference<A2 >::type>::type, typename tr1::remove_const<typename tr1::remove_reference<A3 >::type>::type> tuple_type;
         typedef tr1::tuple<MatcherContainer<typename tr1::remove_const<typename tr1::remove_reference<A0 >::type>::type> , MatcherContainer<typename tr1::remove_const<typename tr1::remove_reference<A1 >::type>::type> , MatcherContainer<typename tr1::remove_const<typename tr1::remove_reference<A2 >::type>::type> , MatcherContainer<typename tr1::remove_const<typename tr1::remove_reference<A3 >::type>::type> > matcher_tuple_type;

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

         OngoingStubbing& when(const matcher::Matcher<typename tr1::remove_const<typename tr1::remove_reference<A0 >::type>::type>& a0, const matcher::Matcher<typename tr1::remove_const<typename tr1::remove_reference<A1 >::type>::type>& a1, const matcher::Matcher<typename tr1::remove_const<typename tr1::remove_reference<A2 >::type>::type>& a2, const matcher::Matcher<typename tr1::remove_const<typename tr1::remove_reference<A3 >::type>::type>& a3)
         {
            matcher_tuple_type arguments = matcher_tuple_type(a0, a1, a2, a3);
            typename std::list<KeyPair<matcher_tuple_type, queue_type> >::iterator pair_it;
            pair_it = std::find(actionList.begin(), actionList.end(), arguments);
            if(pair_it == actionList.end())
            {
               actionList.push_back(KeyPair<matcher_tuple_type, queue_type>(arguments, queue_type()));
               pair_it = --actionList.end();
            }
            this->ongoingMatch = &(pair_it->value);
            return *this;
         }

         OngoingStubbing& when(A0 a0, A1 a1, A2 a2, A3 a3)
         {
            this->ongoingMatch = &(actionMap[tuple_type(a0, a1, a2, a3)]);
            return *this;
         }

         R invoke(A0 a0, A1 a1, A2 a2, A3 a3)
         {
            this->calls++;
            tuple_type  args    = tuple_type(a0, a1, a2, a3);
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
 
      template <typename R, typename C, typename A0, typename A1, typename A2, typename A3, typename A4>
      struct OngoingStubbing<R (C::*)(A0, A1, A2, A3, A4)> : public OngoingStubbingBase<R>, public Verifier
      {
         typedef tr1::tuple<typename tr1::remove_const<typename tr1::remove_reference<A0 >::type>::type, typename tr1::remove_const<typename tr1::remove_reference<A1 >::type>::type, typename tr1::remove_const<typename tr1::remove_reference<A2 >::type>::type, typename tr1::remove_const<typename tr1::remove_reference<A3 >::type>::type, typename tr1::remove_const<typename tr1::remove_reference<A4 >::type>::type> tuple_type;
         typedef tr1::tuple<MatcherContainer<typename tr1::remove_const<typename tr1::remove_reference<A0 >::type>::type> , MatcherContainer<typename tr1::remove_const<typename tr1::remove_reference<A1 >::type>::type> , MatcherContainer<typename tr1::remove_const<typename tr1::remove_reference<A2 >::type>::type> , MatcherContainer<typename tr1::remove_const<typename tr1::remove_reference<A3 >::type>::type> , MatcherContainer<typename tr1::remove_const<typename tr1::remove_reference<A4 >::type>::type> > matcher_tuple_type;

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

         OngoingStubbing& when(const matcher::Matcher<typename tr1::remove_const<typename tr1::remove_reference<A0 >::type>::type>& a0, const matcher::Matcher<typename tr1::remove_const<typename tr1::remove_reference<A1 >::type>::type>& a1, const matcher::Matcher<typename tr1::remove_const<typename tr1::remove_reference<A2 >::type>::type>& a2, const matcher::Matcher<typename tr1::remove_const<typename tr1::remove_reference<A3 >::type>::type>& a3, const matcher::Matcher<typename tr1::remove_const<typename tr1::remove_reference<A4 >::type>::type>& a4)
         {
            matcher_tuple_type arguments = matcher_tuple_type(a0, a1, a2, a3, a4);
            typename std::list<KeyPair<matcher_tuple_type, queue_type> >::iterator pair_it;
            pair_it = std::find(actionList.begin(), actionList.end(), arguments);
            if(pair_it == actionList.end())
            {
               actionList.push_back(KeyPair<matcher_tuple_type, queue_type>(arguments, queue_type()));
               pair_it = --actionList.end();
            }
            this->ongoingMatch = &(pair_it->value);
            return *this;
         }

         OngoingStubbing& when(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4)
         {
            this->ongoingMatch = &(actionMap[tuple_type(a0, a1, a2, a3, a4)]);
            return *this;
         }

         R invoke(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4)
         {
            this->calls++;
            tuple_type  args    = tuple_type(a0, a1, a2, a3, a4);
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
 
      template <typename R, typename C, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5>
      struct OngoingStubbing<R (C::*)(A0, A1, A2, A3, A4, A5)> : public OngoingStubbingBase<R>, public Verifier
      {
         typedef tr1::tuple<typename tr1::remove_const<typename tr1::remove_reference<A0 >::type>::type, typename tr1::remove_const<typename tr1::remove_reference<A1 >::type>::type, typename tr1::remove_const<typename tr1::remove_reference<A2 >::type>::type, typename tr1::remove_const<typename tr1::remove_reference<A3 >::type>::type, typename tr1::remove_const<typename tr1::remove_reference<A4 >::type>::type, typename tr1::remove_const<typename tr1::remove_reference<A5 >::type>::type> tuple_type;
         typedef tr1::tuple<MatcherContainer<typename tr1::remove_const<typename tr1::remove_reference<A0 >::type>::type> , MatcherContainer<typename tr1::remove_const<typename tr1::remove_reference<A1 >::type>::type> , MatcherContainer<typename tr1::remove_const<typename tr1::remove_reference<A2 >::type>::type> , MatcherContainer<typename tr1::remove_const<typename tr1::remove_reference<A3 >::type>::type> , MatcherContainer<typename tr1::remove_const<typename tr1::remove_reference<A4 >::type>::type> , MatcherContainer<typename tr1::remove_const<typename tr1::remove_reference<A5 >::type>::type> > matcher_tuple_type;

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

         OngoingStubbing& when(const matcher::Matcher<typename tr1::remove_const<typename tr1::remove_reference<A0 >::type>::type>& a0, const matcher::Matcher<typename tr1::remove_const<typename tr1::remove_reference<A1 >::type>::type>& a1, const matcher::Matcher<typename tr1::remove_const<typename tr1::remove_reference<A2 >::type>::type>& a2, const matcher::Matcher<typename tr1::remove_const<typename tr1::remove_reference<A3 >::type>::type>& a3, const matcher::Matcher<typename tr1::remove_const<typename tr1::remove_reference<A4 >::type>::type>& a4, const matcher::Matcher<typename tr1::remove_const<typename tr1::remove_reference<A5 >::type>::type>& a5)
         {
            matcher_tuple_type arguments = matcher_tuple_type(a0, a1, a2, a3, a4, a5);
            typename std::list<KeyPair<matcher_tuple_type, queue_type> >::iterator pair_it;
            pair_it = std::find(actionList.begin(), actionList.end(), arguments);
            if(pair_it == actionList.end())
            {
               actionList.push_back(KeyPair<matcher_tuple_type, queue_type>(arguments, queue_type()));
               pair_it = --actionList.end();
            }
            this->ongoingMatch = &(pair_it->value);
            return *this;
         }

         OngoingStubbing& when(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5)
         {
            this->ongoingMatch = &(actionMap[tuple_type(a0, a1, a2, a3, a4, a5)]);
            return *this;
         }

         R invoke(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5)
         {
            this->calls++;
            tuple_type  args    = tuple_type(a0, a1, a2, a3, a4, a5);
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
 
      template <typename R, typename C, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
      struct OngoingStubbing<R (C::*)(A0, A1, A2, A3, A4, A5, A6)> : public OngoingStubbingBase<R>, public Verifier
      {
         typedef tr1::tuple<typename tr1::remove_const<typename tr1::remove_reference<A0 >::type>::type, typename tr1::remove_const<typename tr1::remove_reference<A1 >::type>::type, typename tr1::remove_const<typename tr1::remove_reference<A2 >::type>::type, typename tr1::remove_const<typename tr1::remove_reference<A3 >::type>::type, typename tr1::remove_const<typename tr1::remove_reference<A4 >::type>::type, typename tr1::remove_const<typename tr1::remove_reference<A5 >::type>::type, typename tr1::remove_const<typename tr1::remove_reference<A6 >::type>::type> tuple_type;
         typedef tr1::tuple<MatcherContainer<typename tr1::remove_const<typename tr1::remove_reference<A0 >::type>::type> , MatcherContainer<typename tr1::remove_const<typename tr1::remove_reference<A1 >::type>::type> , MatcherContainer<typename tr1::remove_const<typename tr1::remove_reference<A2 >::type>::type> , MatcherContainer<typename tr1::remove_const<typename tr1::remove_reference<A3 >::type>::type> , MatcherContainer<typename tr1::remove_const<typename tr1::remove_reference<A4 >::type>::type> , MatcherContainer<typename tr1::remove_const<typename tr1::remove_reference<A5 >::type>::type> , MatcherContainer<typename tr1::remove_const<typename tr1::remove_reference<A6 >::type>::type> > matcher_tuple_type;

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

         OngoingStubbing& when(const matcher::Matcher<typename tr1::remove_const<typename tr1::remove_reference<A0 >::type>::type>& a0, const matcher::Matcher<typename tr1::remove_const<typename tr1::remove_reference<A1 >::type>::type>& a1, const matcher::Matcher<typename tr1::remove_const<typename tr1::remove_reference<A2 >::type>::type>& a2, const matcher::Matcher<typename tr1::remove_const<typename tr1::remove_reference<A3 >::type>::type>& a3, const matcher::Matcher<typename tr1::remove_const<typename tr1::remove_reference<A4 >::type>::type>& a4, const matcher::Matcher<typename tr1::remove_const<typename tr1::remove_reference<A5 >::type>::type>& a5, const matcher::Matcher<typename tr1::remove_const<typename tr1::remove_reference<A6 >::type>::type>& a6)
         {
            matcher_tuple_type arguments = matcher_tuple_type(a0, a1, a2, a3, a4, a5, a6);
            typename std::list<KeyPair<matcher_tuple_type, queue_type> >::iterator pair_it;
            pair_it = std::find(actionList.begin(), actionList.end(), arguments);
            if(pair_it == actionList.end())
            {
               actionList.push_back(KeyPair<matcher_tuple_type, queue_type>(arguments, queue_type()));
               pair_it = --actionList.end();
            }
            this->ongoingMatch = &(pair_it->value);
            return *this;
         }

         OngoingStubbing& when(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6)
         {
            this->ongoingMatch = &(actionMap[tuple_type(a0, a1, a2, a3, a4, a5, a6)]);
            return *this;
         }

         R invoke(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6)
         {
            this->calls++;
            tuple_type  args    = tuple_type(a0, a1, a2, a3, a4, a5, a6);
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
 
      template <typename R, typename C, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7>
      struct OngoingStubbing<R (C::*)(A0, A1, A2, A3, A4, A5, A6, A7)> : public OngoingStubbingBase<R>, public Verifier
      {
         typedef tr1::tuple<typename tr1::remove_const<typename tr1::remove_reference<A0 >::type>::type, typename tr1::remove_const<typename tr1::remove_reference<A1 >::type>::type, typename tr1::remove_const<typename tr1::remove_reference<A2 >::type>::type, typename tr1::remove_const<typename tr1::remove_reference<A3 >::type>::type, typename tr1::remove_const<typename tr1::remove_reference<A4 >::type>::type, typename tr1::remove_const<typename tr1::remove_reference<A5 >::type>::type, typename tr1::remove_const<typename tr1::remove_reference<A6 >::type>::type, typename tr1::remove_const<typename tr1::remove_reference<A7 >::type>::type> tuple_type;
         typedef tr1::tuple<MatcherContainer<typename tr1::remove_const<typename tr1::remove_reference<A0 >::type>::type> , MatcherContainer<typename tr1::remove_const<typename tr1::remove_reference<A1 >::type>::type> , MatcherContainer<typename tr1::remove_const<typename tr1::remove_reference<A2 >::type>::type> , MatcherContainer<typename tr1::remove_const<typename tr1::remove_reference<A3 >::type>::type> , MatcherContainer<typename tr1::remove_const<typename tr1::remove_reference<A4 >::type>::type> , MatcherContainer<typename tr1::remove_const<typename tr1::remove_reference<A5 >::type>::type> , MatcherContainer<typename tr1::remove_const<typename tr1::remove_reference<A6 >::type>::type> , MatcherContainer<typename tr1::remove_const<typename tr1::remove_reference<A7 >::type>::type> > matcher_tuple_type;

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

         OngoingStubbing& when(const matcher::Matcher<typename tr1::remove_const<typename tr1::remove_reference<A0 >::type>::type>& a0, const matcher::Matcher<typename tr1::remove_const<typename tr1::remove_reference<A1 >::type>::type>& a1, const matcher::Matcher<typename tr1::remove_const<typename tr1::remove_reference<A2 >::type>::type>& a2, const matcher::Matcher<typename tr1::remove_const<typename tr1::remove_reference<A3 >::type>::type>& a3, const matcher::Matcher<typename tr1::remove_const<typename tr1::remove_reference<A4 >::type>::type>& a4, const matcher::Matcher<typename tr1::remove_const<typename tr1::remove_reference<A5 >::type>::type>& a5, const matcher::Matcher<typename tr1::remove_const<typename tr1::remove_reference<A6 >::type>::type>& a6, const matcher::Matcher<typename tr1::remove_const<typename tr1::remove_reference<A7 >::type>::type>& a7)
         {
            matcher_tuple_type arguments = matcher_tuple_type(a0, a1, a2, a3, a4, a5, a6, a7);
            typename std::list<KeyPair<matcher_tuple_type, queue_type> >::iterator pair_it;
            pair_it = std::find(actionList.begin(), actionList.end(), arguments);
            if(pair_it == actionList.end())
            {
               actionList.push_back(KeyPair<matcher_tuple_type, queue_type>(arguments, queue_type()));
               pair_it = --actionList.end();
            }
            this->ongoingMatch = &(pair_it->value);
            return *this;
         }

         OngoingStubbing& when(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7)
         {
            this->ongoingMatch = &(actionMap[tuple_type(a0, a1, a2, a3, a4, a5, a6, a7)]);
            return *this;
         }

         R invoke(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7)
         {
            this->calls++;
            tuple_type  args    = tuple_type(a0, a1, a2, a3, a4, a5, a6, a7);
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
 
      template <typename R, typename C, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8>
      struct OngoingStubbing<R (C::*)(A0, A1, A2, A3, A4, A5, A6, A7, A8)> : public OngoingStubbingBase<R>, public Verifier
      {
         typedef tr1::tuple<typename tr1::remove_const<typename tr1::remove_reference<A0 >::type>::type, typename tr1::remove_const<typename tr1::remove_reference<A1 >::type>::type, typename tr1::remove_const<typename tr1::remove_reference<A2 >::type>::type, typename tr1::remove_const<typename tr1::remove_reference<A3 >::type>::type, typename tr1::remove_const<typename tr1::remove_reference<A4 >::type>::type, typename tr1::remove_const<typename tr1::remove_reference<A5 >::type>::type, typename tr1::remove_const<typename tr1::remove_reference<A6 >::type>::type, typename tr1::remove_const<typename tr1::remove_reference<A7 >::type>::type, typename tr1::remove_const<typename tr1::remove_reference<A8 >::type>::type> tuple_type;
         typedef tr1::tuple<MatcherContainer<typename tr1::remove_const<typename tr1::remove_reference<A0 >::type>::type> , MatcherContainer<typename tr1::remove_const<typename tr1::remove_reference<A1 >::type>::type> , MatcherContainer<typename tr1::remove_const<typename tr1::remove_reference<A2 >::type>::type> , MatcherContainer<typename tr1::remove_const<typename tr1::remove_reference<A3 >::type>::type> , MatcherContainer<typename tr1::remove_const<typename tr1::remove_reference<A4 >::type>::type> , MatcherContainer<typename tr1::remove_const<typename tr1::remove_reference<A5 >::type>::type> , MatcherContainer<typename tr1::remove_const<typename tr1::remove_reference<A6 >::type>::type> , MatcherContainer<typename tr1::remove_const<typename tr1::remove_reference<A7 >::type>::type> , MatcherContainer<typename tr1::remove_const<typename tr1::remove_reference<A8 >::type>::type> > matcher_tuple_type;

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

         OngoingStubbing& when(const matcher::Matcher<typename tr1::remove_const<typename tr1::remove_reference<A0 >::type>::type>& a0, const matcher::Matcher<typename tr1::remove_const<typename tr1::remove_reference<A1 >::type>::type>& a1, const matcher::Matcher<typename tr1::remove_const<typename tr1::remove_reference<A2 >::type>::type>& a2, const matcher::Matcher<typename tr1::remove_const<typename tr1::remove_reference<A3 >::type>::type>& a3, const matcher::Matcher<typename tr1::remove_const<typename tr1::remove_reference<A4 >::type>::type>& a4, const matcher::Matcher<typename tr1::remove_const<typename tr1::remove_reference<A5 >::type>::type>& a5, const matcher::Matcher<typename tr1::remove_const<typename tr1::remove_reference<A6 >::type>::type>& a6, const matcher::Matcher<typename tr1::remove_const<typename tr1::remove_reference<A7 >::type>::type>& a7, const matcher::Matcher<typename tr1::remove_const<typename tr1::remove_reference<A8 >::type>::type>& a8)
         {
            matcher_tuple_type arguments = matcher_tuple_type(a0, a1, a2, a3, a4, a5, a6, a7, a8);
            typename std::list<KeyPair<matcher_tuple_type, queue_type> >::iterator pair_it;
            pair_it = std::find(actionList.begin(), actionList.end(), arguments);
            if(pair_it == actionList.end())
            {
               actionList.push_back(KeyPair<matcher_tuple_type, queue_type>(arguments, queue_type()));
               pair_it = --actionList.end();
            }
            this->ongoingMatch = &(pair_it->value);
            return *this;
         }

         OngoingStubbing& when(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8)
         {
            this->ongoingMatch = &(actionMap[tuple_type(a0, a1, a2, a3, a4, a5, a6, a7, a8)]);
            return *this;
         }

         R invoke(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8)
         {
            this->calls++;
            tuple_type  args    = tuple_type(a0, a1, a2, a3, a4, a5, a6, a7, a8);
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
 
      template <typename R, typename C, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9>
      struct OngoingStubbing<R (C::*)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9)> : public OngoingStubbingBase<R>, public Verifier
      {
         typedef tr1::tuple<typename tr1::remove_const<typename tr1::remove_reference<A0 >::type>::type, typename tr1::remove_const<typename tr1::remove_reference<A1 >::type>::type, typename tr1::remove_const<typename tr1::remove_reference<A2 >::type>::type, typename tr1::remove_const<typename tr1::remove_reference<A3 >::type>::type, typename tr1::remove_const<typename tr1::remove_reference<A4 >::type>::type, typename tr1::remove_const<typename tr1::remove_reference<A5 >::type>::type, typename tr1::remove_const<typename tr1::remove_reference<A6 >::type>::type, typename tr1::remove_const<typename tr1::remove_reference<A7 >::type>::type, typename tr1::remove_const<typename tr1::remove_reference<A8 >::type>::type, typename tr1::remove_const<typename tr1::remove_reference<A9 >::type>::type> tuple_type;
         typedef tr1::tuple<MatcherContainer<typename tr1::remove_const<typename tr1::remove_reference<A0 >::type>::type> , MatcherContainer<typename tr1::remove_const<typename tr1::remove_reference<A1 >::type>::type> , MatcherContainer<typename tr1::remove_const<typename tr1::remove_reference<A2 >::type>::type> , MatcherContainer<typename tr1::remove_const<typename tr1::remove_reference<A3 >::type>::type> , MatcherContainer<typename tr1::remove_const<typename tr1::remove_reference<A4 >::type>::type> , MatcherContainer<typename tr1::remove_const<typename tr1::remove_reference<A5 >::type>::type> , MatcherContainer<typename tr1::remove_const<typename tr1::remove_reference<A6 >::type>::type> , MatcherContainer<typename tr1::remove_const<typename tr1::remove_reference<A7 >::type>::type> , MatcherContainer<typename tr1::remove_const<typename tr1::remove_reference<A8 >::type>::type> , MatcherContainer<typename tr1::remove_const<typename tr1::remove_reference<A9 >::type>::type> > matcher_tuple_type;

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

         OngoingStubbing& when(const matcher::Matcher<typename tr1::remove_const<typename tr1::remove_reference<A0 >::type>::type>& a0, const matcher::Matcher<typename tr1::remove_const<typename tr1::remove_reference<A1 >::type>::type>& a1, const matcher::Matcher<typename tr1::remove_const<typename tr1::remove_reference<A2 >::type>::type>& a2, const matcher::Matcher<typename tr1::remove_const<typename tr1::remove_reference<A3 >::type>::type>& a3, const matcher::Matcher<typename tr1::remove_const<typename tr1::remove_reference<A4 >::type>::type>& a4, const matcher::Matcher<typename tr1::remove_const<typename tr1::remove_reference<A5 >::type>::type>& a5, const matcher::Matcher<typename tr1::remove_const<typename tr1::remove_reference<A6 >::type>::type>& a6, const matcher::Matcher<typename tr1::remove_const<typename tr1::remove_reference<A7 >::type>::type>& a7, const matcher::Matcher<typename tr1::remove_const<typename tr1::remove_reference<A8 >::type>::type>& a8, const matcher::Matcher<typename tr1::remove_const<typename tr1::remove_reference<A9 >::type>::type>& a9)
         {
            matcher_tuple_type arguments = matcher_tuple_type(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9);
            typename std::list<KeyPair<matcher_tuple_type, queue_type> >::iterator pair_it;
            pair_it = std::find(actionList.begin(), actionList.end(), arguments);
            if(pair_it == actionList.end())
            {
               actionList.push_back(KeyPair<matcher_tuple_type, queue_type>(arguments, queue_type()));
               pair_it = --actionList.end();
            }
            this->ongoingMatch = &(pair_it->value);
            return *this;
         }

         OngoingStubbing& when(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9)
         {
            this->ongoingMatch = &(actionMap[tuple_type(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9)]);
            return *this;
         }

         R invoke(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9)
         {
            this->calls++;
            tuple_type  args    = tuple_type(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9);
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
   } // namespace detail
} // namespace mockitopp

#endif //__MOCKITOPP_DYNAMIC_VFUNCTION_HPP__
