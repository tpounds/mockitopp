#ifndef __MOCKITOPP_ONGOING_STUBBING_HPP__
#define __MOCKITOPP_ONGOING_STUBBING_HPP__

#include <list>
#include <map>

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
 
      // void partial specialization for 0 arguments
      template <typename C>
      struct OngoingStubbing<void (C::*)()>
      {
         
         typedef boost::tuple<> tuple_type;
         typedef boost::tuple<> matcher_tuple_type;
         typedef Answer<void>*            answer_type;
         typedef std::list<answer_type> queue_type;

         //TODO: rename argument lists
         std::map<tuple_type, queue_type> answerMap;
         std::list<KeyPair<matcher_tuple_type, queue_type> > answerList;

         queue_type* ongoingMatch;
         Verifier   verifier;

         OngoingStubbing()
            : answerMap()
            , answerList()
            , ongoingMatch()
            , verifier()
            {}

         OngoingStubbing& __DISABLE_OVERLOAD__when()
         {
            matcher_tuple_type arguments = matcher_tuple_type();
            typename std::list<KeyPair<matcher_tuple_type, queue_type> >::iterator pair_it;
            pair_it = find(answerList.begin(), answerList.end(), arguments);
            if(pair_it == answerList.end())
            {
               answerList.push_back(KeyPair<matcher_tuple_type, queue_type>(arguments, queue_type()));
               pair_it = --answerList.end();
            }
            ongoingMatch = &(pair_it->value);
            return *this;
         }

         OngoingStubbing& when()
         {
            ongoingMatch = &(answerMap[tuple_type()]);
            return *this;
         }

         template <typename T>
         OngoingStubbing& thenThrow(T throwable)
         {
            ongoingMatch->push_back(new Throws<void, T>(throwable));
            return *this;
         }

         void invoke()
         {
            verifier.calls++;
            tuple_type  args    = tuple_type();
            queue_type& answers = answerMap[args];
            if(answers.empty())
            {
               typename std::list<KeyPair<matcher_tuple_type, queue_type> >::iterator pair_it;
               pair_it = find(answerList.begin(), answerList.end(), args);
               if(pair_it == answerList.end())
                  { throw IncompleteImplementationException(); }
               answers = pair_it->value;
            }
            answer_type answer = answers.front();
            if(answers.size() > 1)
               { answers.pop_front(); }
            return answer->execute();
         }

         const Verifier& getVerifier() const
            { return verifier; }

         OngoingStubbing& thenReturn()
         {
            ongoingMatch->push_back(new Returns<void>());
            return *this;
         }
      };

      // non-void partial specialization for 0 arguments
      template <typename R, typename C>
      struct OngoingStubbing<R (C::*)(), typename boost::disable_if<boost::is_void<R> >::type>
      {
         
         typedef boost::tuple<> tuple_type;
         typedef boost::tuple<> matcher_tuple_type;
         typedef Answer<R>*            answer_type;
         typedef std::list<answer_type> queue_type;

         //TODO: rename argument lists
         std::map<tuple_type, queue_type> answerMap;
         std::list<KeyPair<matcher_tuple_type, queue_type> > answerList;

         queue_type* ongoingMatch;
         Verifier   verifier;

         OngoingStubbing()
            : answerMap()
            , answerList()
            , ongoingMatch()
            , verifier()
            {}

         OngoingStubbing& __DISABLE_OVERLOAD__when()
         {
            matcher_tuple_type arguments = matcher_tuple_type();
            typename std::list<KeyPair<matcher_tuple_type, queue_type> >::iterator pair_it;
            pair_it = find(answerList.begin(), answerList.end(), arguments);
            if(pair_it == answerList.end())
            {
               answerList.push_back(KeyPair<matcher_tuple_type, queue_type>(arguments, queue_type()));
               pair_it = --answerList.end();
            }
            ongoingMatch = &(pair_it->value);
            return *this;
         }

         OngoingStubbing& when()
         {
            ongoingMatch = &(answerMap[tuple_type()]);
            return *this;
         }

         template <typename T>
         OngoingStubbing& thenThrow(T throwable)
         {
            ongoingMatch->push_back(new Throws<R, T>(throwable));
            return *this;
         }

         R invoke()
         {
            verifier.calls++;
            tuple_type  args    = tuple_type();
            queue_type& answers = answerMap[args];
            if(answers.empty())
            {
               typename std::list<KeyPair<matcher_tuple_type, queue_type> >::iterator pair_it;
               pair_it = find(answerList.begin(), answerList.end(), args);
               if(pair_it == answerList.end())
                  { throw IncompleteImplementationException(); }
               answers = pair_it->value;
            }
            answer_type answer = answers.front();
            if(answers.size() > 1)
               { answers.pop_front(); }
            return answer->execute();
         }

         const Verifier& getVerifier() const
            { return verifier; }

         OngoingStubbing& thenReturn(R value)
         {
            ongoingMatch->push_back(new Returns<R>(value));
            return *this;
         }
      };
 
      // void partial specialization for 1 arguments
      template <typename C, typename A0>
      struct OngoingStubbing<void (C::*)(A0)>
      {
         
         typedef boost::tuple<typename boost::remove_const<typename boost::remove_reference<A0 >::type>::type> tuple_type;
         typedef boost::tuple<MatcherContainer<typename boost::remove_const<typename boost::remove_reference<A0 >::type>::type> > matcher_tuple_type;
         typedef Answer<void>*            answer_type;
         typedef std::list<answer_type> queue_type;

         //TODO: rename argument lists
         std::map<tuple_type, queue_type> answerMap;
         std::list<KeyPair<matcher_tuple_type, queue_type> > answerList;

         queue_type* ongoingMatch;
         Verifier   verifier;

         OngoingStubbing()
            : answerMap()
            , answerList()
            , ongoingMatch()
            , verifier()
            {}

         OngoingStubbing& when(const matcher::Matcher<typename boost::remove_const<typename boost::remove_reference<A0 >::type>::type>& a0)
         {
            matcher_tuple_type arguments = matcher_tuple_type(a0);
            typename std::list<KeyPair<matcher_tuple_type, queue_type> >::iterator pair_it;
            pair_it = find(answerList.begin(), answerList.end(), arguments);
            if(pair_it == answerList.end())
            {
               answerList.push_back(KeyPair<matcher_tuple_type, queue_type>(arguments, queue_type()));
               pair_it = --answerList.end();
            }
            ongoingMatch = &(pair_it->value);
            return *this;
         }

         OngoingStubbing& when(A0 a0)
         {
            ongoingMatch = &(answerMap[tuple_type(a0)]);
            return *this;
         }

         template <typename T>
         OngoingStubbing& thenThrow(T throwable)
         {
            ongoingMatch->push_back(new Throws<void, T>(throwable));
            return *this;
         }

         void invoke(A0 a0)
         {
            verifier.calls++;
            tuple_type  args    = tuple_type(a0);
            queue_type& answers = answerMap[args];
            if(answers.empty())
            {
               typename std::list<KeyPair<matcher_tuple_type, queue_type> >::iterator pair_it;
               pair_it = find(answerList.begin(), answerList.end(), args);
               if(pair_it == answerList.end())
                  { throw IncompleteImplementationException(); }
               answers = pair_it->value;
            }
            answer_type answer = answers.front();
            if(answers.size() > 1)
               { answers.pop_front(); }
            return answer->execute();
         }

         const Verifier& getVerifier() const
            { return verifier; }

         OngoingStubbing& thenReturn()
         {
            ongoingMatch->push_back(new Returns<void>());
            return *this;
         }
      };

      // non-void partial specialization for 1 arguments
      template <typename R, typename C, typename A0>
      struct OngoingStubbing<R (C::*)(A0), typename boost::disable_if<boost::is_void<R> >::type>
      {
         
         typedef boost::tuple<typename boost::remove_const<typename boost::remove_reference<A0 >::type>::type> tuple_type;
         typedef boost::tuple<MatcherContainer<typename boost::remove_const<typename boost::remove_reference<A0 >::type>::type> > matcher_tuple_type;
         typedef Answer<R>*            answer_type;
         typedef std::list<answer_type> queue_type;

         //TODO: rename argument lists
         std::map<tuple_type, queue_type> answerMap;
         std::list<KeyPair<matcher_tuple_type, queue_type> > answerList;

         queue_type* ongoingMatch;
         Verifier   verifier;

         OngoingStubbing()
            : answerMap()
            , answerList()
            , ongoingMatch()
            , verifier()
            {}

         OngoingStubbing& when(const matcher::Matcher<typename boost::remove_const<typename boost::remove_reference<A0 >::type>::type>& a0)
         {
            matcher_tuple_type arguments = matcher_tuple_type(a0);
            typename std::list<KeyPair<matcher_tuple_type, queue_type> >::iterator pair_it;
            pair_it = find(answerList.begin(), answerList.end(), arguments);
            if(pair_it == answerList.end())
            {
               answerList.push_back(KeyPair<matcher_tuple_type, queue_type>(arguments, queue_type()));
               pair_it = --answerList.end();
            }
            ongoingMatch = &(pair_it->value);
            return *this;
         }

         OngoingStubbing& when(A0 a0)
         {
            ongoingMatch = &(answerMap[tuple_type(a0)]);
            return *this;
         }

         template <typename T>
         OngoingStubbing& thenThrow(T throwable)
         {
            ongoingMatch->push_back(new Throws<R, T>(throwable));
            return *this;
         }

         R invoke(A0 a0)
         {
            verifier.calls++;
            tuple_type  args    = tuple_type(a0);
            queue_type& answers = answerMap[args];
            if(answers.empty())
            {
               typename std::list<KeyPair<matcher_tuple_type, queue_type> >::iterator pair_it;
               pair_it = find(answerList.begin(), answerList.end(), args);
               if(pair_it == answerList.end())
                  { throw IncompleteImplementationException(); }
               answers = pair_it->value;
            }
            answer_type answer = answers.front();
            if(answers.size() > 1)
               { answers.pop_front(); }
            return answer->execute();
         }

         const Verifier& getVerifier() const
            { return verifier; }

         OngoingStubbing& thenReturn(R value)
         {
            ongoingMatch->push_back(new Returns<R>(value));
            return *this;
         }
      };
 
      // void partial specialization for 2 arguments
      template <typename C, typename A0, typename A1>
      struct OngoingStubbing<void (C::*)(A0, A1)>
      {
         
         typedef boost::tuple<typename boost::remove_const<typename boost::remove_reference<A0 >::type>::type, typename boost::remove_const<typename boost::remove_reference<A1 >::type>::type> tuple_type;
         typedef boost::tuple<MatcherContainer<typename boost::remove_const<typename boost::remove_reference<A0 >::type>::type> , MatcherContainer<typename boost::remove_const<typename boost::remove_reference<A1 >::type>::type> > matcher_tuple_type;
         typedef Answer<void>*            answer_type;
         typedef std::list<answer_type> queue_type;

         //TODO: rename argument lists
         std::map<tuple_type, queue_type> answerMap;
         std::list<KeyPair<matcher_tuple_type, queue_type> > answerList;

         queue_type* ongoingMatch;
         Verifier   verifier;

         OngoingStubbing()
            : answerMap()
            , answerList()
            , ongoingMatch()
            , verifier()
            {}

         OngoingStubbing& when(const matcher::Matcher<typename boost::remove_const<typename boost::remove_reference<A0 >::type>::type>& a0, const matcher::Matcher<typename boost::remove_const<typename boost::remove_reference<A1 >::type>::type>& a1)
         {
            matcher_tuple_type arguments = matcher_tuple_type(a0, a1);
            typename std::list<KeyPair<matcher_tuple_type, queue_type> >::iterator pair_it;
            pair_it = find(answerList.begin(), answerList.end(), arguments);
            if(pair_it == answerList.end())
            {
               answerList.push_back(KeyPair<matcher_tuple_type, queue_type>(arguments, queue_type()));
               pair_it = --answerList.end();
            }
            ongoingMatch = &(pair_it->value);
            return *this;
         }

         OngoingStubbing& when(A0 a0, A1 a1)
         {
            ongoingMatch = &(answerMap[tuple_type(a0, a1)]);
            return *this;
         }

         template <typename T>
         OngoingStubbing& thenThrow(T throwable)
         {
            ongoingMatch->push_back(new Throws<void, T>(throwable));
            return *this;
         }

         void invoke(A0 a0, A1 a1)
         {
            verifier.calls++;
            tuple_type  args    = tuple_type(a0, a1);
            queue_type& answers = answerMap[args];
            if(answers.empty())
            {
               typename std::list<KeyPair<matcher_tuple_type, queue_type> >::iterator pair_it;
               pair_it = find(answerList.begin(), answerList.end(), args);
               if(pair_it == answerList.end())
                  { throw IncompleteImplementationException(); }
               answers = pair_it->value;
            }
            answer_type answer = answers.front();
            if(answers.size() > 1)
               { answers.pop_front(); }
            return answer->execute();
         }

         const Verifier& getVerifier() const
            { return verifier; }

         OngoingStubbing& thenReturn()
         {
            ongoingMatch->push_back(new Returns<void>());
            return *this;
         }
      };

      // non-void partial specialization for 2 arguments
      template <typename R, typename C, typename A0, typename A1>
      struct OngoingStubbing<R (C::*)(A0, A1), typename boost::disable_if<boost::is_void<R> >::type>
      {
         
         typedef boost::tuple<typename boost::remove_const<typename boost::remove_reference<A0 >::type>::type, typename boost::remove_const<typename boost::remove_reference<A1 >::type>::type> tuple_type;
         typedef boost::tuple<MatcherContainer<typename boost::remove_const<typename boost::remove_reference<A0 >::type>::type> , MatcherContainer<typename boost::remove_const<typename boost::remove_reference<A1 >::type>::type> > matcher_tuple_type;
         typedef Answer<R>*            answer_type;
         typedef std::list<answer_type> queue_type;

         //TODO: rename argument lists
         std::map<tuple_type, queue_type> answerMap;
         std::list<KeyPair<matcher_tuple_type, queue_type> > answerList;

         queue_type* ongoingMatch;
         Verifier   verifier;

         OngoingStubbing()
            : answerMap()
            , answerList()
            , ongoingMatch()
            , verifier()
            {}

         OngoingStubbing& when(const matcher::Matcher<typename boost::remove_const<typename boost::remove_reference<A0 >::type>::type>& a0, const matcher::Matcher<typename boost::remove_const<typename boost::remove_reference<A1 >::type>::type>& a1)
         {
            matcher_tuple_type arguments = matcher_tuple_type(a0, a1);
            typename std::list<KeyPair<matcher_tuple_type, queue_type> >::iterator pair_it;
            pair_it = find(answerList.begin(), answerList.end(), arguments);
            if(pair_it == answerList.end())
            {
               answerList.push_back(KeyPair<matcher_tuple_type, queue_type>(arguments, queue_type()));
               pair_it = --answerList.end();
            }
            ongoingMatch = &(pair_it->value);
            return *this;
         }

         OngoingStubbing& when(A0 a0, A1 a1)
         {
            ongoingMatch = &(answerMap[tuple_type(a0, a1)]);
            return *this;
         }

         template <typename T>
         OngoingStubbing& thenThrow(T throwable)
         {
            ongoingMatch->push_back(new Throws<R, T>(throwable));
            return *this;
         }

         R invoke(A0 a0, A1 a1)
         {
            verifier.calls++;
            tuple_type  args    = tuple_type(a0, a1);
            queue_type& answers = answerMap[args];
            if(answers.empty())
            {
               typename std::list<KeyPair<matcher_tuple_type, queue_type> >::iterator pair_it;
               pair_it = find(answerList.begin(), answerList.end(), args);
               if(pair_it == answerList.end())
                  { throw IncompleteImplementationException(); }
               answers = pair_it->value;
            }
            answer_type answer = answers.front();
            if(answers.size() > 1)
               { answers.pop_front(); }
            return answer->execute();
         }

         const Verifier& getVerifier() const
            { return verifier; }

         OngoingStubbing& thenReturn(R value)
         {
            ongoingMatch->push_back(new Returns<R>(value));
            return *this;
         }
      };
 
      // void partial specialization for 3 arguments
      template <typename C, typename A0, typename A1, typename A2>
      struct OngoingStubbing<void (C::*)(A0, A1, A2)>
      {
         
         typedef boost::tuple<typename boost::remove_const<typename boost::remove_reference<A0 >::type>::type, typename boost::remove_const<typename boost::remove_reference<A1 >::type>::type, typename boost::remove_const<typename boost::remove_reference<A2 >::type>::type> tuple_type;
         typedef boost::tuple<MatcherContainer<typename boost::remove_const<typename boost::remove_reference<A0 >::type>::type> , MatcherContainer<typename boost::remove_const<typename boost::remove_reference<A1 >::type>::type> , MatcherContainer<typename boost::remove_const<typename boost::remove_reference<A2 >::type>::type> > matcher_tuple_type;
         typedef Answer<void>*            answer_type;
         typedef std::list<answer_type> queue_type;

         //TODO: rename argument lists
         std::map<tuple_type, queue_type> answerMap;
         std::list<KeyPair<matcher_tuple_type, queue_type> > answerList;

         queue_type* ongoingMatch;
         Verifier   verifier;

         OngoingStubbing()
            : answerMap()
            , answerList()
            , ongoingMatch()
            , verifier()
            {}

         OngoingStubbing& when(const matcher::Matcher<typename boost::remove_const<typename boost::remove_reference<A0 >::type>::type>& a0, const matcher::Matcher<typename boost::remove_const<typename boost::remove_reference<A1 >::type>::type>& a1, const matcher::Matcher<typename boost::remove_const<typename boost::remove_reference<A2 >::type>::type>& a2)
         {
            matcher_tuple_type arguments = matcher_tuple_type(a0, a1, a2);
            typename std::list<KeyPair<matcher_tuple_type, queue_type> >::iterator pair_it;
            pair_it = find(answerList.begin(), answerList.end(), arguments);
            if(pair_it == answerList.end())
            {
               answerList.push_back(KeyPair<matcher_tuple_type, queue_type>(arguments, queue_type()));
               pair_it = --answerList.end();
            }
            ongoingMatch = &(pair_it->value);
            return *this;
         }

         OngoingStubbing& when(A0 a0, A1 a1, A2 a2)
         {
            ongoingMatch = &(answerMap[tuple_type(a0, a1, a2)]);
            return *this;
         }

         template <typename T>
         OngoingStubbing& thenThrow(T throwable)
         {
            ongoingMatch->push_back(new Throws<void, T>(throwable));
            return *this;
         }

         void invoke(A0 a0, A1 a1, A2 a2)
         {
            verifier.calls++;
            tuple_type  args    = tuple_type(a0, a1, a2);
            queue_type& answers = answerMap[args];
            if(answers.empty())
            {
               typename std::list<KeyPair<matcher_tuple_type, queue_type> >::iterator pair_it;
               pair_it = find(answerList.begin(), answerList.end(), args);
               if(pair_it == answerList.end())
                  { throw IncompleteImplementationException(); }
               answers = pair_it->value;
            }
            answer_type answer = answers.front();
            if(answers.size() > 1)
               { answers.pop_front(); }
            return answer->execute();
         }

         const Verifier& getVerifier() const
            { return verifier; }

         OngoingStubbing& thenReturn()
         {
            ongoingMatch->push_back(new Returns<void>());
            return *this;
         }
      };

      // non-void partial specialization for 3 arguments
      template <typename R, typename C, typename A0, typename A1, typename A2>
      struct OngoingStubbing<R (C::*)(A0, A1, A2), typename boost::disable_if<boost::is_void<R> >::type>
      {
         
         typedef boost::tuple<typename boost::remove_const<typename boost::remove_reference<A0 >::type>::type, typename boost::remove_const<typename boost::remove_reference<A1 >::type>::type, typename boost::remove_const<typename boost::remove_reference<A2 >::type>::type> tuple_type;
         typedef boost::tuple<MatcherContainer<typename boost::remove_const<typename boost::remove_reference<A0 >::type>::type> , MatcherContainer<typename boost::remove_const<typename boost::remove_reference<A1 >::type>::type> , MatcherContainer<typename boost::remove_const<typename boost::remove_reference<A2 >::type>::type> > matcher_tuple_type;
         typedef Answer<R>*            answer_type;
         typedef std::list<answer_type> queue_type;

         //TODO: rename argument lists
         std::map<tuple_type, queue_type> answerMap;
         std::list<KeyPair<matcher_tuple_type, queue_type> > answerList;

         queue_type* ongoingMatch;
         Verifier   verifier;

         OngoingStubbing()
            : answerMap()
            , answerList()
            , ongoingMatch()
            , verifier()
            {}

         OngoingStubbing& when(const matcher::Matcher<typename boost::remove_const<typename boost::remove_reference<A0 >::type>::type>& a0, const matcher::Matcher<typename boost::remove_const<typename boost::remove_reference<A1 >::type>::type>& a1, const matcher::Matcher<typename boost::remove_const<typename boost::remove_reference<A2 >::type>::type>& a2)
         {
            matcher_tuple_type arguments = matcher_tuple_type(a0, a1, a2);
            typename std::list<KeyPair<matcher_tuple_type, queue_type> >::iterator pair_it;
            pair_it = find(answerList.begin(), answerList.end(), arguments);
            if(pair_it == answerList.end())
            {
               answerList.push_back(KeyPair<matcher_tuple_type, queue_type>(arguments, queue_type()));
               pair_it = --answerList.end();
            }
            ongoingMatch = &(pair_it->value);
            return *this;
         }

         OngoingStubbing& when(A0 a0, A1 a1, A2 a2)
         {
            ongoingMatch = &(answerMap[tuple_type(a0, a1, a2)]);
            return *this;
         }

         template <typename T>
         OngoingStubbing& thenThrow(T throwable)
         {
            ongoingMatch->push_back(new Throws<R, T>(throwable));
            return *this;
         }

         R invoke(A0 a0, A1 a1, A2 a2)
         {
            verifier.calls++;
            tuple_type  args    = tuple_type(a0, a1, a2);
            queue_type& answers = answerMap[args];
            if(answers.empty())
            {
               typename std::list<KeyPair<matcher_tuple_type, queue_type> >::iterator pair_it;
               pair_it = find(answerList.begin(), answerList.end(), args);
               if(pair_it == answerList.end())
                  { throw IncompleteImplementationException(); }
               answers = pair_it->value;
            }
            answer_type answer = answers.front();
            if(answers.size() > 1)
               { answers.pop_front(); }
            return answer->execute();
         }

         const Verifier& getVerifier() const
            { return verifier; }

         OngoingStubbing& thenReturn(R value)
         {
            ongoingMatch->push_back(new Returns<R>(value));
            return *this;
         }
      };
 
      // void partial specialization for 4 arguments
      template <typename C, typename A0, typename A1, typename A2, typename A3>
      struct OngoingStubbing<void (C::*)(A0, A1, A2, A3)>
      {
         
         typedef boost::tuple<typename boost::remove_const<typename boost::remove_reference<A0 >::type>::type, typename boost::remove_const<typename boost::remove_reference<A1 >::type>::type, typename boost::remove_const<typename boost::remove_reference<A2 >::type>::type, typename boost::remove_const<typename boost::remove_reference<A3 >::type>::type> tuple_type;
         typedef boost::tuple<MatcherContainer<typename boost::remove_const<typename boost::remove_reference<A0 >::type>::type> , MatcherContainer<typename boost::remove_const<typename boost::remove_reference<A1 >::type>::type> , MatcherContainer<typename boost::remove_const<typename boost::remove_reference<A2 >::type>::type> , MatcherContainer<typename boost::remove_const<typename boost::remove_reference<A3 >::type>::type> > matcher_tuple_type;
         typedef Answer<void>*            answer_type;
         typedef std::list<answer_type> queue_type;

         //TODO: rename argument lists
         std::map<tuple_type, queue_type> answerMap;
         std::list<KeyPair<matcher_tuple_type, queue_type> > answerList;

         queue_type* ongoingMatch;
         Verifier   verifier;

         OngoingStubbing()
            : answerMap()
            , answerList()
            , ongoingMatch()
            , verifier()
            {}

         OngoingStubbing& when(const matcher::Matcher<typename boost::remove_const<typename boost::remove_reference<A0 >::type>::type>& a0, const matcher::Matcher<typename boost::remove_const<typename boost::remove_reference<A1 >::type>::type>& a1, const matcher::Matcher<typename boost::remove_const<typename boost::remove_reference<A2 >::type>::type>& a2, const matcher::Matcher<typename boost::remove_const<typename boost::remove_reference<A3 >::type>::type>& a3)
         {
            matcher_tuple_type arguments = matcher_tuple_type(a0, a1, a2, a3);
            typename std::list<KeyPair<matcher_tuple_type, queue_type> >::iterator pair_it;
            pair_it = find(answerList.begin(), answerList.end(), arguments);
            if(pair_it == answerList.end())
            {
               answerList.push_back(KeyPair<matcher_tuple_type, queue_type>(arguments, queue_type()));
               pair_it = --answerList.end();
            }
            ongoingMatch = &(pair_it->value);
            return *this;
         }

         OngoingStubbing& when(A0 a0, A1 a1, A2 a2, A3 a3)
         {
            ongoingMatch = &(answerMap[tuple_type(a0, a1, a2, a3)]);
            return *this;
         }

         template <typename T>
         OngoingStubbing& thenThrow(T throwable)
         {
            ongoingMatch->push_back(new Throws<void, T>(throwable));
            return *this;
         }

         void invoke(A0 a0, A1 a1, A2 a2, A3 a3)
         {
            verifier.calls++;
            tuple_type  args    = tuple_type(a0, a1, a2, a3);
            queue_type& answers = answerMap[args];
            if(answers.empty())
            {
               typename std::list<KeyPair<matcher_tuple_type, queue_type> >::iterator pair_it;
               pair_it = find(answerList.begin(), answerList.end(), args);
               if(pair_it == answerList.end())
                  { throw IncompleteImplementationException(); }
               answers = pair_it->value;
            }
            answer_type answer = answers.front();
            if(answers.size() > 1)
               { answers.pop_front(); }
            return answer->execute();
         }

         const Verifier& getVerifier() const
            { return verifier; }

         OngoingStubbing& thenReturn()
         {
            ongoingMatch->push_back(new Returns<void>());
            return *this;
         }
      };

      // non-void partial specialization for 4 arguments
      template <typename R, typename C, typename A0, typename A1, typename A2, typename A3>
      struct OngoingStubbing<R (C::*)(A0, A1, A2, A3), typename boost::disable_if<boost::is_void<R> >::type>
      {
         
         typedef boost::tuple<typename boost::remove_const<typename boost::remove_reference<A0 >::type>::type, typename boost::remove_const<typename boost::remove_reference<A1 >::type>::type, typename boost::remove_const<typename boost::remove_reference<A2 >::type>::type, typename boost::remove_const<typename boost::remove_reference<A3 >::type>::type> tuple_type;
         typedef boost::tuple<MatcherContainer<typename boost::remove_const<typename boost::remove_reference<A0 >::type>::type> , MatcherContainer<typename boost::remove_const<typename boost::remove_reference<A1 >::type>::type> , MatcherContainer<typename boost::remove_const<typename boost::remove_reference<A2 >::type>::type> , MatcherContainer<typename boost::remove_const<typename boost::remove_reference<A3 >::type>::type> > matcher_tuple_type;
         typedef Answer<R>*            answer_type;
         typedef std::list<answer_type> queue_type;

         //TODO: rename argument lists
         std::map<tuple_type, queue_type> answerMap;
         std::list<KeyPair<matcher_tuple_type, queue_type> > answerList;

         queue_type* ongoingMatch;
         Verifier   verifier;

         OngoingStubbing()
            : answerMap()
            , answerList()
            , ongoingMatch()
            , verifier()
            {}

         OngoingStubbing& when(const matcher::Matcher<typename boost::remove_const<typename boost::remove_reference<A0 >::type>::type>& a0, const matcher::Matcher<typename boost::remove_const<typename boost::remove_reference<A1 >::type>::type>& a1, const matcher::Matcher<typename boost::remove_const<typename boost::remove_reference<A2 >::type>::type>& a2, const matcher::Matcher<typename boost::remove_const<typename boost::remove_reference<A3 >::type>::type>& a3)
         {
            matcher_tuple_type arguments = matcher_tuple_type(a0, a1, a2, a3);
            typename std::list<KeyPair<matcher_tuple_type, queue_type> >::iterator pair_it;
            pair_it = find(answerList.begin(), answerList.end(), arguments);
            if(pair_it == answerList.end())
            {
               answerList.push_back(KeyPair<matcher_tuple_type, queue_type>(arguments, queue_type()));
               pair_it = --answerList.end();
            }
            ongoingMatch = &(pair_it->value);
            return *this;
         }

         OngoingStubbing& when(A0 a0, A1 a1, A2 a2, A3 a3)
         {
            ongoingMatch = &(answerMap[tuple_type(a0, a1, a2, a3)]);
            return *this;
         }

         template <typename T>
         OngoingStubbing& thenThrow(T throwable)
         {
            ongoingMatch->push_back(new Throws<R, T>(throwable));
            return *this;
         }

         R invoke(A0 a0, A1 a1, A2 a2, A3 a3)
         {
            verifier.calls++;
            tuple_type  args    = tuple_type(a0, a1, a2, a3);
            queue_type& answers = answerMap[args];
            if(answers.empty())
            {
               typename std::list<KeyPair<matcher_tuple_type, queue_type> >::iterator pair_it;
               pair_it = find(answerList.begin(), answerList.end(), args);
               if(pair_it == answerList.end())
                  { throw IncompleteImplementationException(); }
               answers = pair_it->value;
            }
            answer_type answer = answers.front();
            if(answers.size() > 1)
               { answers.pop_front(); }
            return answer->execute();
         }

         const Verifier& getVerifier() const
            { return verifier; }

         OngoingStubbing& thenReturn(R value)
         {
            ongoingMatch->push_back(new Returns<R>(value));
            return *this;
         }
      };
 
      // void partial specialization for 5 arguments
      template <typename C, typename A0, typename A1, typename A2, typename A3, typename A4>
      struct OngoingStubbing<void (C::*)(A0, A1, A2, A3, A4)>
      {
         
         typedef boost::tuple<typename boost::remove_const<typename boost::remove_reference<A0 >::type>::type, typename boost::remove_const<typename boost::remove_reference<A1 >::type>::type, typename boost::remove_const<typename boost::remove_reference<A2 >::type>::type, typename boost::remove_const<typename boost::remove_reference<A3 >::type>::type, typename boost::remove_const<typename boost::remove_reference<A4 >::type>::type> tuple_type;
         typedef boost::tuple<MatcherContainer<typename boost::remove_const<typename boost::remove_reference<A0 >::type>::type> , MatcherContainer<typename boost::remove_const<typename boost::remove_reference<A1 >::type>::type> , MatcherContainer<typename boost::remove_const<typename boost::remove_reference<A2 >::type>::type> , MatcherContainer<typename boost::remove_const<typename boost::remove_reference<A3 >::type>::type> , MatcherContainer<typename boost::remove_const<typename boost::remove_reference<A4 >::type>::type> > matcher_tuple_type;
         typedef Answer<void>*            answer_type;
         typedef std::list<answer_type> queue_type;

         //TODO: rename argument lists
         std::map<tuple_type, queue_type> answerMap;
         std::list<KeyPair<matcher_tuple_type, queue_type> > answerList;

         queue_type* ongoingMatch;
         Verifier   verifier;

         OngoingStubbing()
            : answerMap()
            , answerList()
            , ongoingMatch()
            , verifier()
            {}

         OngoingStubbing& when(const matcher::Matcher<typename boost::remove_const<typename boost::remove_reference<A0 >::type>::type>& a0, const matcher::Matcher<typename boost::remove_const<typename boost::remove_reference<A1 >::type>::type>& a1, const matcher::Matcher<typename boost::remove_const<typename boost::remove_reference<A2 >::type>::type>& a2, const matcher::Matcher<typename boost::remove_const<typename boost::remove_reference<A3 >::type>::type>& a3, const matcher::Matcher<typename boost::remove_const<typename boost::remove_reference<A4 >::type>::type>& a4)
         {
            matcher_tuple_type arguments = matcher_tuple_type(a0, a1, a2, a3, a4);
            typename std::list<KeyPair<matcher_tuple_type, queue_type> >::iterator pair_it;
            pair_it = find(answerList.begin(), answerList.end(), arguments);
            if(pair_it == answerList.end())
            {
               answerList.push_back(KeyPair<matcher_tuple_type, queue_type>(arguments, queue_type()));
               pair_it = --answerList.end();
            }
            ongoingMatch = &(pair_it->value);
            return *this;
         }

         OngoingStubbing& when(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4)
         {
            ongoingMatch = &(answerMap[tuple_type(a0, a1, a2, a3, a4)]);
            return *this;
         }

         template <typename T>
         OngoingStubbing& thenThrow(T throwable)
         {
            ongoingMatch->push_back(new Throws<void, T>(throwable));
            return *this;
         }

         void invoke(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4)
         {
            verifier.calls++;
            tuple_type  args    = tuple_type(a0, a1, a2, a3, a4);
            queue_type& answers = answerMap[args];
            if(answers.empty())
            {
               typename std::list<KeyPair<matcher_tuple_type, queue_type> >::iterator pair_it;
               pair_it = find(answerList.begin(), answerList.end(), args);
               if(pair_it == answerList.end())
                  { throw IncompleteImplementationException(); }
               answers = pair_it->value;
            }
            answer_type answer = answers.front();
            if(answers.size() > 1)
               { answers.pop_front(); }
            return answer->execute();
         }

         const Verifier& getVerifier() const
            { return verifier; }

         OngoingStubbing& thenReturn()
         {
            ongoingMatch->push_back(new Returns<void>());
            return *this;
         }
      };

      // non-void partial specialization for 5 arguments
      template <typename R, typename C, typename A0, typename A1, typename A2, typename A3, typename A4>
      struct OngoingStubbing<R (C::*)(A0, A1, A2, A3, A4), typename boost::disable_if<boost::is_void<R> >::type>
      {
         
         typedef boost::tuple<typename boost::remove_const<typename boost::remove_reference<A0 >::type>::type, typename boost::remove_const<typename boost::remove_reference<A1 >::type>::type, typename boost::remove_const<typename boost::remove_reference<A2 >::type>::type, typename boost::remove_const<typename boost::remove_reference<A3 >::type>::type, typename boost::remove_const<typename boost::remove_reference<A4 >::type>::type> tuple_type;
         typedef boost::tuple<MatcherContainer<typename boost::remove_const<typename boost::remove_reference<A0 >::type>::type> , MatcherContainer<typename boost::remove_const<typename boost::remove_reference<A1 >::type>::type> , MatcherContainer<typename boost::remove_const<typename boost::remove_reference<A2 >::type>::type> , MatcherContainer<typename boost::remove_const<typename boost::remove_reference<A3 >::type>::type> , MatcherContainer<typename boost::remove_const<typename boost::remove_reference<A4 >::type>::type> > matcher_tuple_type;
         typedef Answer<R>*            answer_type;
         typedef std::list<answer_type> queue_type;

         //TODO: rename argument lists
         std::map<tuple_type, queue_type> answerMap;
         std::list<KeyPair<matcher_tuple_type, queue_type> > answerList;

         queue_type* ongoingMatch;
         Verifier   verifier;

         OngoingStubbing()
            : answerMap()
            , answerList()
            , ongoingMatch()
            , verifier()
            {}

         OngoingStubbing& when(const matcher::Matcher<typename boost::remove_const<typename boost::remove_reference<A0 >::type>::type>& a0, const matcher::Matcher<typename boost::remove_const<typename boost::remove_reference<A1 >::type>::type>& a1, const matcher::Matcher<typename boost::remove_const<typename boost::remove_reference<A2 >::type>::type>& a2, const matcher::Matcher<typename boost::remove_const<typename boost::remove_reference<A3 >::type>::type>& a3, const matcher::Matcher<typename boost::remove_const<typename boost::remove_reference<A4 >::type>::type>& a4)
         {
            matcher_tuple_type arguments = matcher_tuple_type(a0, a1, a2, a3, a4);
            typename std::list<KeyPair<matcher_tuple_type, queue_type> >::iterator pair_it;
            pair_it = find(answerList.begin(), answerList.end(), arguments);
            if(pair_it == answerList.end())
            {
               answerList.push_back(KeyPair<matcher_tuple_type, queue_type>(arguments, queue_type()));
               pair_it = --answerList.end();
            }
            ongoingMatch = &(pair_it->value);
            return *this;
         }

         OngoingStubbing& when(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4)
         {
            ongoingMatch = &(answerMap[tuple_type(a0, a1, a2, a3, a4)]);
            return *this;
         }

         template <typename T>
         OngoingStubbing& thenThrow(T throwable)
         {
            ongoingMatch->push_back(new Throws<R, T>(throwable));
            return *this;
         }

         R invoke(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4)
         {
            verifier.calls++;
            tuple_type  args    = tuple_type(a0, a1, a2, a3, a4);
            queue_type& answers = answerMap[args];
            if(answers.empty())
            {
               typename std::list<KeyPair<matcher_tuple_type, queue_type> >::iterator pair_it;
               pair_it = find(answerList.begin(), answerList.end(), args);
               if(pair_it == answerList.end())
                  { throw IncompleteImplementationException(); }
               answers = pair_it->value;
            }
            answer_type answer = answers.front();
            if(answers.size() > 1)
               { answers.pop_front(); }
            return answer->execute();
         }

         const Verifier& getVerifier() const
            { return verifier; }

         OngoingStubbing& thenReturn(R value)
         {
            ongoingMatch->push_back(new Returns<R>(value));
            return *this;
         }
      };
 
      // void partial specialization for 6 arguments
      template <typename C, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5>
      struct OngoingStubbing<void (C::*)(A0, A1, A2, A3, A4, A5)>
      {
         
         typedef boost::tuple<typename boost::remove_const<typename boost::remove_reference<A0 >::type>::type, typename boost::remove_const<typename boost::remove_reference<A1 >::type>::type, typename boost::remove_const<typename boost::remove_reference<A2 >::type>::type, typename boost::remove_const<typename boost::remove_reference<A3 >::type>::type, typename boost::remove_const<typename boost::remove_reference<A4 >::type>::type, typename boost::remove_const<typename boost::remove_reference<A5 >::type>::type> tuple_type;
         typedef boost::tuple<MatcherContainer<typename boost::remove_const<typename boost::remove_reference<A0 >::type>::type> , MatcherContainer<typename boost::remove_const<typename boost::remove_reference<A1 >::type>::type> , MatcherContainer<typename boost::remove_const<typename boost::remove_reference<A2 >::type>::type> , MatcherContainer<typename boost::remove_const<typename boost::remove_reference<A3 >::type>::type> , MatcherContainer<typename boost::remove_const<typename boost::remove_reference<A4 >::type>::type> , MatcherContainer<typename boost::remove_const<typename boost::remove_reference<A5 >::type>::type> > matcher_tuple_type;
         typedef Answer<void>*            answer_type;
         typedef std::list<answer_type> queue_type;

         //TODO: rename argument lists
         std::map<tuple_type, queue_type> answerMap;
         std::list<KeyPair<matcher_tuple_type, queue_type> > answerList;

         queue_type* ongoingMatch;
         Verifier   verifier;

         OngoingStubbing()
            : answerMap()
            , answerList()
            , ongoingMatch()
            , verifier()
            {}

         OngoingStubbing& when(const matcher::Matcher<typename boost::remove_const<typename boost::remove_reference<A0 >::type>::type>& a0, const matcher::Matcher<typename boost::remove_const<typename boost::remove_reference<A1 >::type>::type>& a1, const matcher::Matcher<typename boost::remove_const<typename boost::remove_reference<A2 >::type>::type>& a2, const matcher::Matcher<typename boost::remove_const<typename boost::remove_reference<A3 >::type>::type>& a3, const matcher::Matcher<typename boost::remove_const<typename boost::remove_reference<A4 >::type>::type>& a4, const matcher::Matcher<typename boost::remove_const<typename boost::remove_reference<A5 >::type>::type>& a5)
         {
            matcher_tuple_type arguments = matcher_tuple_type(a0, a1, a2, a3, a4, a5);
            typename std::list<KeyPair<matcher_tuple_type, queue_type> >::iterator pair_it;
            pair_it = find(answerList.begin(), answerList.end(), arguments);
            if(pair_it == answerList.end())
            {
               answerList.push_back(KeyPair<matcher_tuple_type, queue_type>(arguments, queue_type()));
               pair_it = --answerList.end();
            }
            ongoingMatch = &(pair_it->value);
            return *this;
         }

         OngoingStubbing& when(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5)
         {
            ongoingMatch = &(answerMap[tuple_type(a0, a1, a2, a3, a4, a5)]);
            return *this;
         }

         template <typename T>
         OngoingStubbing& thenThrow(T throwable)
         {
            ongoingMatch->push_back(new Throws<void, T>(throwable));
            return *this;
         }

         void invoke(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5)
         {
            verifier.calls++;
            tuple_type  args    = tuple_type(a0, a1, a2, a3, a4, a5);
            queue_type& answers = answerMap[args];
            if(answers.empty())
            {
               typename std::list<KeyPair<matcher_tuple_type, queue_type> >::iterator pair_it;
               pair_it = find(answerList.begin(), answerList.end(), args);
               if(pair_it == answerList.end())
                  { throw IncompleteImplementationException(); }
               answers = pair_it->value;
            }
            answer_type answer = answers.front();
            if(answers.size() > 1)
               { answers.pop_front(); }
            return answer->execute();
         }

         const Verifier& getVerifier() const
            { return verifier; }

         OngoingStubbing& thenReturn()
         {
            ongoingMatch->push_back(new Returns<void>());
            return *this;
         }
      };

      // non-void partial specialization for 6 arguments
      template <typename R, typename C, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5>
      struct OngoingStubbing<R (C::*)(A0, A1, A2, A3, A4, A5), typename boost::disable_if<boost::is_void<R> >::type>
      {
         
         typedef boost::tuple<typename boost::remove_const<typename boost::remove_reference<A0 >::type>::type, typename boost::remove_const<typename boost::remove_reference<A1 >::type>::type, typename boost::remove_const<typename boost::remove_reference<A2 >::type>::type, typename boost::remove_const<typename boost::remove_reference<A3 >::type>::type, typename boost::remove_const<typename boost::remove_reference<A4 >::type>::type, typename boost::remove_const<typename boost::remove_reference<A5 >::type>::type> tuple_type;
         typedef boost::tuple<MatcherContainer<typename boost::remove_const<typename boost::remove_reference<A0 >::type>::type> , MatcherContainer<typename boost::remove_const<typename boost::remove_reference<A1 >::type>::type> , MatcherContainer<typename boost::remove_const<typename boost::remove_reference<A2 >::type>::type> , MatcherContainer<typename boost::remove_const<typename boost::remove_reference<A3 >::type>::type> , MatcherContainer<typename boost::remove_const<typename boost::remove_reference<A4 >::type>::type> , MatcherContainer<typename boost::remove_const<typename boost::remove_reference<A5 >::type>::type> > matcher_tuple_type;
         typedef Answer<R>*            answer_type;
         typedef std::list<answer_type> queue_type;

         //TODO: rename argument lists
         std::map<tuple_type, queue_type> answerMap;
         std::list<KeyPair<matcher_tuple_type, queue_type> > answerList;

         queue_type* ongoingMatch;
         Verifier   verifier;

         OngoingStubbing()
            : answerMap()
            , answerList()
            , ongoingMatch()
            , verifier()
            {}

         OngoingStubbing& when(const matcher::Matcher<typename boost::remove_const<typename boost::remove_reference<A0 >::type>::type>& a0, const matcher::Matcher<typename boost::remove_const<typename boost::remove_reference<A1 >::type>::type>& a1, const matcher::Matcher<typename boost::remove_const<typename boost::remove_reference<A2 >::type>::type>& a2, const matcher::Matcher<typename boost::remove_const<typename boost::remove_reference<A3 >::type>::type>& a3, const matcher::Matcher<typename boost::remove_const<typename boost::remove_reference<A4 >::type>::type>& a4, const matcher::Matcher<typename boost::remove_const<typename boost::remove_reference<A5 >::type>::type>& a5)
         {
            matcher_tuple_type arguments = matcher_tuple_type(a0, a1, a2, a3, a4, a5);
            typename std::list<KeyPair<matcher_tuple_type, queue_type> >::iterator pair_it;
            pair_it = find(answerList.begin(), answerList.end(), arguments);
            if(pair_it == answerList.end())
            {
               answerList.push_back(KeyPair<matcher_tuple_type, queue_type>(arguments, queue_type()));
               pair_it = --answerList.end();
            }
            ongoingMatch = &(pair_it->value);
            return *this;
         }

         OngoingStubbing& when(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5)
         {
            ongoingMatch = &(answerMap[tuple_type(a0, a1, a2, a3, a4, a5)]);
            return *this;
         }

         template <typename T>
         OngoingStubbing& thenThrow(T throwable)
         {
            ongoingMatch->push_back(new Throws<R, T>(throwable));
            return *this;
         }

         R invoke(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5)
         {
            verifier.calls++;
            tuple_type  args    = tuple_type(a0, a1, a2, a3, a4, a5);
            queue_type& answers = answerMap[args];
            if(answers.empty())
            {
               typename std::list<KeyPair<matcher_tuple_type, queue_type> >::iterator pair_it;
               pair_it = find(answerList.begin(), answerList.end(), args);
               if(pair_it == answerList.end())
                  { throw IncompleteImplementationException(); }
               answers = pair_it->value;
            }
            answer_type answer = answers.front();
            if(answers.size() > 1)
               { answers.pop_front(); }
            return answer->execute();
         }

         const Verifier& getVerifier() const
            { return verifier; }

         OngoingStubbing& thenReturn(R value)
         {
            ongoingMatch->push_back(new Returns<R>(value));
            return *this;
         }
      };
 
      // void partial specialization for 7 arguments
      template <typename C, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
      struct OngoingStubbing<void (C::*)(A0, A1, A2, A3, A4, A5, A6)>
      {
         
         typedef boost::tuple<typename boost::remove_const<typename boost::remove_reference<A0 >::type>::type, typename boost::remove_const<typename boost::remove_reference<A1 >::type>::type, typename boost::remove_const<typename boost::remove_reference<A2 >::type>::type, typename boost::remove_const<typename boost::remove_reference<A3 >::type>::type, typename boost::remove_const<typename boost::remove_reference<A4 >::type>::type, typename boost::remove_const<typename boost::remove_reference<A5 >::type>::type, typename boost::remove_const<typename boost::remove_reference<A6 >::type>::type> tuple_type;
         typedef boost::tuple<MatcherContainer<typename boost::remove_const<typename boost::remove_reference<A0 >::type>::type> , MatcherContainer<typename boost::remove_const<typename boost::remove_reference<A1 >::type>::type> , MatcherContainer<typename boost::remove_const<typename boost::remove_reference<A2 >::type>::type> , MatcherContainer<typename boost::remove_const<typename boost::remove_reference<A3 >::type>::type> , MatcherContainer<typename boost::remove_const<typename boost::remove_reference<A4 >::type>::type> , MatcherContainer<typename boost::remove_const<typename boost::remove_reference<A5 >::type>::type> , MatcherContainer<typename boost::remove_const<typename boost::remove_reference<A6 >::type>::type> > matcher_tuple_type;
         typedef Answer<void>*            answer_type;
         typedef std::list<answer_type> queue_type;

         //TODO: rename argument lists
         std::map<tuple_type, queue_type> answerMap;
         std::list<KeyPair<matcher_tuple_type, queue_type> > answerList;

         queue_type* ongoingMatch;
         Verifier   verifier;

         OngoingStubbing()
            : answerMap()
            , answerList()
            , ongoingMatch()
            , verifier()
            {}

         OngoingStubbing& when(const matcher::Matcher<typename boost::remove_const<typename boost::remove_reference<A0 >::type>::type>& a0, const matcher::Matcher<typename boost::remove_const<typename boost::remove_reference<A1 >::type>::type>& a1, const matcher::Matcher<typename boost::remove_const<typename boost::remove_reference<A2 >::type>::type>& a2, const matcher::Matcher<typename boost::remove_const<typename boost::remove_reference<A3 >::type>::type>& a3, const matcher::Matcher<typename boost::remove_const<typename boost::remove_reference<A4 >::type>::type>& a4, const matcher::Matcher<typename boost::remove_const<typename boost::remove_reference<A5 >::type>::type>& a5, const matcher::Matcher<typename boost::remove_const<typename boost::remove_reference<A6 >::type>::type>& a6)
         {
            matcher_tuple_type arguments = matcher_tuple_type(a0, a1, a2, a3, a4, a5, a6);
            typename std::list<KeyPair<matcher_tuple_type, queue_type> >::iterator pair_it;
            pair_it = find(answerList.begin(), answerList.end(), arguments);
            if(pair_it == answerList.end())
            {
               answerList.push_back(KeyPair<matcher_tuple_type, queue_type>(arguments, queue_type()));
               pair_it = --answerList.end();
            }
            ongoingMatch = &(pair_it->value);
            return *this;
         }

         OngoingStubbing& when(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6)
         {
            ongoingMatch = &(answerMap[tuple_type(a0, a1, a2, a3, a4, a5, a6)]);
            return *this;
         }

         template <typename T>
         OngoingStubbing& thenThrow(T throwable)
         {
            ongoingMatch->push_back(new Throws<void, T>(throwable));
            return *this;
         }

         void invoke(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6)
         {
            verifier.calls++;
            tuple_type  args    = tuple_type(a0, a1, a2, a3, a4, a5, a6);
            queue_type& answers = answerMap[args];
            if(answers.empty())
            {
               typename std::list<KeyPair<matcher_tuple_type, queue_type> >::iterator pair_it;
               pair_it = find(answerList.begin(), answerList.end(), args);
               if(pair_it == answerList.end())
                  { throw IncompleteImplementationException(); }
               answers = pair_it->value;
            }
            answer_type answer = answers.front();
            if(answers.size() > 1)
               { answers.pop_front(); }
            return answer->execute();
         }

         const Verifier& getVerifier() const
            { return verifier; }

         OngoingStubbing& thenReturn()
         {
            ongoingMatch->push_back(new Returns<void>());
            return *this;
         }
      };

      // non-void partial specialization for 7 arguments
      template <typename R, typename C, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
      struct OngoingStubbing<R (C::*)(A0, A1, A2, A3, A4, A5, A6), typename boost::disable_if<boost::is_void<R> >::type>
      {
         
         typedef boost::tuple<typename boost::remove_const<typename boost::remove_reference<A0 >::type>::type, typename boost::remove_const<typename boost::remove_reference<A1 >::type>::type, typename boost::remove_const<typename boost::remove_reference<A2 >::type>::type, typename boost::remove_const<typename boost::remove_reference<A3 >::type>::type, typename boost::remove_const<typename boost::remove_reference<A4 >::type>::type, typename boost::remove_const<typename boost::remove_reference<A5 >::type>::type, typename boost::remove_const<typename boost::remove_reference<A6 >::type>::type> tuple_type;
         typedef boost::tuple<MatcherContainer<typename boost::remove_const<typename boost::remove_reference<A0 >::type>::type> , MatcherContainer<typename boost::remove_const<typename boost::remove_reference<A1 >::type>::type> , MatcherContainer<typename boost::remove_const<typename boost::remove_reference<A2 >::type>::type> , MatcherContainer<typename boost::remove_const<typename boost::remove_reference<A3 >::type>::type> , MatcherContainer<typename boost::remove_const<typename boost::remove_reference<A4 >::type>::type> , MatcherContainer<typename boost::remove_const<typename boost::remove_reference<A5 >::type>::type> , MatcherContainer<typename boost::remove_const<typename boost::remove_reference<A6 >::type>::type> > matcher_tuple_type;
         typedef Answer<R>*            answer_type;
         typedef std::list<answer_type> queue_type;

         //TODO: rename argument lists
         std::map<tuple_type, queue_type> answerMap;
         std::list<KeyPair<matcher_tuple_type, queue_type> > answerList;

         queue_type* ongoingMatch;
         Verifier   verifier;

         OngoingStubbing()
            : answerMap()
            , answerList()
            , ongoingMatch()
            , verifier()
            {}

         OngoingStubbing& when(const matcher::Matcher<typename boost::remove_const<typename boost::remove_reference<A0 >::type>::type>& a0, const matcher::Matcher<typename boost::remove_const<typename boost::remove_reference<A1 >::type>::type>& a1, const matcher::Matcher<typename boost::remove_const<typename boost::remove_reference<A2 >::type>::type>& a2, const matcher::Matcher<typename boost::remove_const<typename boost::remove_reference<A3 >::type>::type>& a3, const matcher::Matcher<typename boost::remove_const<typename boost::remove_reference<A4 >::type>::type>& a4, const matcher::Matcher<typename boost::remove_const<typename boost::remove_reference<A5 >::type>::type>& a5, const matcher::Matcher<typename boost::remove_const<typename boost::remove_reference<A6 >::type>::type>& a6)
         {
            matcher_tuple_type arguments = matcher_tuple_type(a0, a1, a2, a3, a4, a5, a6);
            typename std::list<KeyPair<matcher_tuple_type, queue_type> >::iterator pair_it;
            pair_it = find(answerList.begin(), answerList.end(), arguments);
            if(pair_it == answerList.end())
            {
               answerList.push_back(KeyPair<matcher_tuple_type, queue_type>(arguments, queue_type()));
               pair_it = --answerList.end();
            }
            ongoingMatch = &(pair_it->value);
            return *this;
         }

         OngoingStubbing& when(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6)
         {
            ongoingMatch = &(answerMap[tuple_type(a0, a1, a2, a3, a4, a5, a6)]);
            return *this;
         }

         template <typename T>
         OngoingStubbing& thenThrow(T throwable)
         {
            ongoingMatch->push_back(new Throws<R, T>(throwable));
            return *this;
         }

         R invoke(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6)
         {
            verifier.calls++;
            tuple_type  args    = tuple_type(a0, a1, a2, a3, a4, a5, a6);
            queue_type& answers = answerMap[args];
            if(answers.empty())
            {
               typename std::list<KeyPair<matcher_tuple_type, queue_type> >::iterator pair_it;
               pair_it = find(answerList.begin(), answerList.end(), args);
               if(pair_it == answerList.end())
                  { throw IncompleteImplementationException(); }
               answers = pair_it->value;
            }
            answer_type answer = answers.front();
            if(answers.size() > 1)
               { answers.pop_front(); }
            return answer->execute();
         }

         const Verifier& getVerifier() const
            { return verifier; }

         OngoingStubbing& thenReturn(R value)
         {
            ongoingMatch->push_back(new Returns<R>(value));
            return *this;
         }
      };
 
      // void partial specialization for 8 arguments
      template <typename C, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7>
      struct OngoingStubbing<void (C::*)(A0, A1, A2, A3, A4, A5, A6, A7)>
      {
         
         typedef boost::tuple<typename boost::remove_const<typename boost::remove_reference<A0 >::type>::type, typename boost::remove_const<typename boost::remove_reference<A1 >::type>::type, typename boost::remove_const<typename boost::remove_reference<A2 >::type>::type, typename boost::remove_const<typename boost::remove_reference<A3 >::type>::type, typename boost::remove_const<typename boost::remove_reference<A4 >::type>::type, typename boost::remove_const<typename boost::remove_reference<A5 >::type>::type, typename boost::remove_const<typename boost::remove_reference<A6 >::type>::type, typename boost::remove_const<typename boost::remove_reference<A7 >::type>::type> tuple_type;
         typedef boost::tuple<MatcherContainer<typename boost::remove_const<typename boost::remove_reference<A0 >::type>::type> , MatcherContainer<typename boost::remove_const<typename boost::remove_reference<A1 >::type>::type> , MatcherContainer<typename boost::remove_const<typename boost::remove_reference<A2 >::type>::type> , MatcherContainer<typename boost::remove_const<typename boost::remove_reference<A3 >::type>::type> , MatcherContainer<typename boost::remove_const<typename boost::remove_reference<A4 >::type>::type> , MatcherContainer<typename boost::remove_const<typename boost::remove_reference<A5 >::type>::type> , MatcherContainer<typename boost::remove_const<typename boost::remove_reference<A6 >::type>::type> , MatcherContainer<typename boost::remove_const<typename boost::remove_reference<A7 >::type>::type> > matcher_tuple_type;
         typedef Answer<void>*            answer_type;
         typedef std::list<answer_type> queue_type;

         //TODO: rename argument lists
         std::map<tuple_type, queue_type> answerMap;
         std::list<KeyPair<matcher_tuple_type, queue_type> > answerList;

         queue_type* ongoingMatch;
         Verifier   verifier;

         OngoingStubbing()
            : answerMap()
            , answerList()
            , ongoingMatch()
            , verifier()
            {}

         OngoingStubbing& when(const matcher::Matcher<typename boost::remove_const<typename boost::remove_reference<A0 >::type>::type>& a0, const matcher::Matcher<typename boost::remove_const<typename boost::remove_reference<A1 >::type>::type>& a1, const matcher::Matcher<typename boost::remove_const<typename boost::remove_reference<A2 >::type>::type>& a2, const matcher::Matcher<typename boost::remove_const<typename boost::remove_reference<A3 >::type>::type>& a3, const matcher::Matcher<typename boost::remove_const<typename boost::remove_reference<A4 >::type>::type>& a4, const matcher::Matcher<typename boost::remove_const<typename boost::remove_reference<A5 >::type>::type>& a5, const matcher::Matcher<typename boost::remove_const<typename boost::remove_reference<A6 >::type>::type>& a6, const matcher::Matcher<typename boost::remove_const<typename boost::remove_reference<A7 >::type>::type>& a7)
         {
            matcher_tuple_type arguments = matcher_tuple_type(a0, a1, a2, a3, a4, a5, a6, a7);
            typename std::list<KeyPair<matcher_tuple_type, queue_type> >::iterator pair_it;
            pair_it = find(answerList.begin(), answerList.end(), arguments);
            if(pair_it == answerList.end())
            {
               answerList.push_back(KeyPair<matcher_tuple_type, queue_type>(arguments, queue_type()));
               pair_it = --answerList.end();
            }
            ongoingMatch = &(pair_it->value);
            return *this;
         }

         OngoingStubbing& when(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7)
         {
            ongoingMatch = &(answerMap[tuple_type(a0, a1, a2, a3, a4, a5, a6, a7)]);
            return *this;
         }

         template <typename T>
         OngoingStubbing& thenThrow(T throwable)
         {
            ongoingMatch->push_back(new Throws<void, T>(throwable));
            return *this;
         }

         void invoke(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7)
         {
            verifier.calls++;
            tuple_type  args    = tuple_type(a0, a1, a2, a3, a4, a5, a6, a7);
            queue_type& answers = answerMap[args];
            if(answers.empty())
            {
               typename std::list<KeyPair<matcher_tuple_type, queue_type> >::iterator pair_it;
               pair_it = find(answerList.begin(), answerList.end(), args);
               if(pair_it == answerList.end())
                  { throw IncompleteImplementationException(); }
               answers = pair_it->value;
            }
            answer_type answer = answers.front();
            if(answers.size() > 1)
               { answers.pop_front(); }
            return answer->execute();
         }

         const Verifier& getVerifier() const
            { return verifier; }

         OngoingStubbing& thenReturn()
         {
            ongoingMatch->push_back(new Returns<void>());
            return *this;
         }
      };

      // non-void partial specialization for 8 arguments
      template <typename R, typename C, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7>
      struct OngoingStubbing<R (C::*)(A0, A1, A2, A3, A4, A5, A6, A7), typename boost::disable_if<boost::is_void<R> >::type>
      {
         
         typedef boost::tuple<typename boost::remove_const<typename boost::remove_reference<A0 >::type>::type, typename boost::remove_const<typename boost::remove_reference<A1 >::type>::type, typename boost::remove_const<typename boost::remove_reference<A2 >::type>::type, typename boost::remove_const<typename boost::remove_reference<A3 >::type>::type, typename boost::remove_const<typename boost::remove_reference<A4 >::type>::type, typename boost::remove_const<typename boost::remove_reference<A5 >::type>::type, typename boost::remove_const<typename boost::remove_reference<A6 >::type>::type, typename boost::remove_const<typename boost::remove_reference<A7 >::type>::type> tuple_type;
         typedef boost::tuple<MatcherContainer<typename boost::remove_const<typename boost::remove_reference<A0 >::type>::type> , MatcherContainer<typename boost::remove_const<typename boost::remove_reference<A1 >::type>::type> , MatcherContainer<typename boost::remove_const<typename boost::remove_reference<A2 >::type>::type> , MatcherContainer<typename boost::remove_const<typename boost::remove_reference<A3 >::type>::type> , MatcherContainer<typename boost::remove_const<typename boost::remove_reference<A4 >::type>::type> , MatcherContainer<typename boost::remove_const<typename boost::remove_reference<A5 >::type>::type> , MatcherContainer<typename boost::remove_const<typename boost::remove_reference<A6 >::type>::type> , MatcherContainer<typename boost::remove_const<typename boost::remove_reference<A7 >::type>::type> > matcher_tuple_type;
         typedef Answer<R>*            answer_type;
         typedef std::list<answer_type> queue_type;

         //TODO: rename argument lists
         std::map<tuple_type, queue_type> answerMap;
         std::list<KeyPair<matcher_tuple_type, queue_type> > answerList;

         queue_type* ongoingMatch;
         Verifier   verifier;

         OngoingStubbing()
            : answerMap()
            , answerList()
            , ongoingMatch()
            , verifier()
            {}

         OngoingStubbing& when(const matcher::Matcher<typename boost::remove_const<typename boost::remove_reference<A0 >::type>::type>& a0, const matcher::Matcher<typename boost::remove_const<typename boost::remove_reference<A1 >::type>::type>& a1, const matcher::Matcher<typename boost::remove_const<typename boost::remove_reference<A2 >::type>::type>& a2, const matcher::Matcher<typename boost::remove_const<typename boost::remove_reference<A3 >::type>::type>& a3, const matcher::Matcher<typename boost::remove_const<typename boost::remove_reference<A4 >::type>::type>& a4, const matcher::Matcher<typename boost::remove_const<typename boost::remove_reference<A5 >::type>::type>& a5, const matcher::Matcher<typename boost::remove_const<typename boost::remove_reference<A6 >::type>::type>& a6, const matcher::Matcher<typename boost::remove_const<typename boost::remove_reference<A7 >::type>::type>& a7)
         {
            matcher_tuple_type arguments = matcher_tuple_type(a0, a1, a2, a3, a4, a5, a6, a7);
            typename std::list<KeyPair<matcher_tuple_type, queue_type> >::iterator pair_it;
            pair_it = find(answerList.begin(), answerList.end(), arguments);
            if(pair_it == answerList.end())
            {
               answerList.push_back(KeyPair<matcher_tuple_type, queue_type>(arguments, queue_type()));
               pair_it = --answerList.end();
            }
            ongoingMatch = &(pair_it->value);
            return *this;
         }

         OngoingStubbing& when(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7)
         {
            ongoingMatch = &(answerMap[tuple_type(a0, a1, a2, a3, a4, a5, a6, a7)]);
            return *this;
         }

         template <typename T>
         OngoingStubbing& thenThrow(T throwable)
         {
            ongoingMatch->push_back(new Throws<R, T>(throwable));
            return *this;
         }

         R invoke(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7)
         {
            verifier.calls++;
            tuple_type  args    = tuple_type(a0, a1, a2, a3, a4, a5, a6, a7);
            queue_type& answers = answerMap[args];
            if(answers.empty())
            {
               typename std::list<KeyPair<matcher_tuple_type, queue_type> >::iterator pair_it;
               pair_it = find(answerList.begin(), answerList.end(), args);
               if(pair_it == answerList.end())
                  { throw IncompleteImplementationException(); }
               answers = pair_it->value;
            }
            answer_type answer = answers.front();
            if(answers.size() > 1)
               { answers.pop_front(); }
            return answer->execute();
         }

         const Verifier& getVerifier() const
            { return verifier; }

         OngoingStubbing& thenReturn(R value)
         {
            ongoingMatch->push_back(new Returns<R>(value));
            return *this;
         }
      };
 
      // void partial specialization for 9 arguments
      template <typename C, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8>
      struct OngoingStubbing<void (C::*)(A0, A1, A2, A3, A4, A5, A6, A7, A8)>
      {
         
         typedef boost::tuple<typename boost::remove_const<typename boost::remove_reference<A0 >::type>::type, typename boost::remove_const<typename boost::remove_reference<A1 >::type>::type, typename boost::remove_const<typename boost::remove_reference<A2 >::type>::type, typename boost::remove_const<typename boost::remove_reference<A3 >::type>::type, typename boost::remove_const<typename boost::remove_reference<A4 >::type>::type, typename boost::remove_const<typename boost::remove_reference<A5 >::type>::type, typename boost::remove_const<typename boost::remove_reference<A6 >::type>::type, typename boost::remove_const<typename boost::remove_reference<A7 >::type>::type, typename boost::remove_const<typename boost::remove_reference<A8 >::type>::type> tuple_type;
         typedef boost::tuple<MatcherContainer<typename boost::remove_const<typename boost::remove_reference<A0 >::type>::type> , MatcherContainer<typename boost::remove_const<typename boost::remove_reference<A1 >::type>::type> , MatcherContainer<typename boost::remove_const<typename boost::remove_reference<A2 >::type>::type> , MatcherContainer<typename boost::remove_const<typename boost::remove_reference<A3 >::type>::type> , MatcherContainer<typename boost::remove_const<typename boost::remove_reference<A4 >::type>::type> , MatcherContainer<typename boost::remove_const<typename boost::remove_reference<A5 >::type>::type> , MatcherContainer<typename boost::remove_const<typename boost::remove_reference<A6 >::type>::type> , MatcherContainer<typename boost::remove_const<typename boost::remove_reference<A7 >::type>::type> , MatcherContainer<typename boost::remove_const<typename boost::remove_reference<A8 >::type>::type> > matcher_tuple_type;
         typedef Answer<void>*            answer_type;
         typedef std::list<answer_type> queue_type;

         //TODO: rename argument lists
         std::map<tuple_type, queue_type> answerMap;
         std::list<KeyPair<matcher_tuple_type, queue_type> > answerList;

         queue_type* ongoingMatch;
         Verifier   verifier;

         OngoingStubbing()
            : answerMap()
            , answerList()
            , ongoingMatch()
            , verifier()
            {}

         OngoingStubbing& when(const matcher::Matcher<typename boost::remove_const<typename boost::remove_reference<A0 >::type>::type>& a0, const matcher::Matcher<typename boost::remove_const<typename boost::remove_reference<A1 >::type>::type>& a1, const matcher::Matcher<typename boost::remove_const<typename boost::remove_reference<A2 >::type>::type>& a2, const matcher::Matcher<typename boost::remove_const<typename boost::remove_reference<A3 >::type>::type>& a3, const matcher::Matcher<typename boost::remove_const<typename boost::remove_reference<A4 >::type>::type>& a4, const matcher::Matcher<typename boost::remove_const<typename boost::remove_reference<A5 >::type>::type>& a5, const matcher::Matcher<typename boost::remove_const<typename boost::remove_reference<A6 >::type>::type>& a6, const matcher::Matcher<typename boost::remove_const<typename boost::remove_reference<A7 >::type>::type>& a7, const matcher::Matcher<typename boost::remove_const<typename boost::remove_reference<A8 >::type>::type>& a8)
         {
            matcher_tuple_type arguments = matcher_tuple_type(a0, a1, a2, a3, a4, a5, a6, a7, a8);
            typename std::list<KeyPair<matcher_tuple_type, queue_type> >::iterator pair_it;
            pair_it = find(answerList.begin(), answerList.end(), arguments);
            if(pair_it == answerList.end())
            {
               answerList.push_back(KeyPair<matcher_tuple_type, queue_type>(arguments, queue_type()));
               pair_it = --answerList.end();
            }
            ongoingMatch = &(pair_it->value);
            return *this;
         }

         OngoingStubbing& when(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8)
         {
            ongoingMatch = &(answerMap[tuple_type(a0, a1, a2, a3, a4, a5, a6, a7, a8)]);
            return *this;
         }

         template <typename T>
         OngoingStubbing& thenThrow(T throwable)
         {
            ongoingMatch->push_back(new Throws<void, T>(throwable));
            return *this;
         }

         void invoke(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8)
         {
            verifier.calls++;
            tuple_type  args    = tuple_type(a0, a1, a2, a3, a4, a5, a6, a7, a8);
            queue_type& answers = answerMap[args];
            if(answers.empty())
            {
               typename std::list<KeyPair<matcher_tuple_type, queue_type> >::iterator pair_it;
               pair_it = find(answerList.begin(), answerList.end(), args);
               if(pair_it == answerList.end())
                  { throw IncompleteImplementationException(); }
               answers = pair_it->value;
            }
            answer_type answer = answers.front();
            if(answers.size() > 1)
               { answers.pop_front(); }
            return answer->execute();
         }

         const Verifier& getVerifier() const
            { return verifier; }

         OngoingStubbing& thenReturn()
         {
            ongoingMatch->push_back(new Returns<void>());
            return *this;
         }
      };

      // non-void partial specialization for 9 arguments
      template <typename R, typename C, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8>
      struct OngoingStubbing<R (C::*)(A0, A1, A2, A3, A4, A5, A6, A7, A8), typename boost::disable_if<boost::is_void<R> >::type>
      {
         
         typedef boost::tuple<typename boost::remove_const<typename boost::remove_reference<A0 >::type>::type, typename boost::remove_const<typename boost::remove_reference<A1 >::type>::type, typename boost::remove_const<typename boost::remove_reference<A2 >::type>::type, typename boost::remove_const<typename boost::remove_reference<A3 >::type>::type, typename boost::remove_const<typename boost::remove_reference<A4 >::type>::type, typename boost::remove_const<typename boost::remove_reference<A5 >::type>::type, typename boost::remove_const<typename boost::remove_reference<A6 >::type>::type, typename boost::remove_const<typename boost::remove_reference<A7 >::type>::type, typename boost::remove_const<typename boost::remove_reference<A8 >::type>::type> tuple_type;
         typedef boost::tuple<MatcherContainer<typename boost::remove_const<typename boost::remove_reference<A0 >::type>::type> , MatcherContainer<typename boost::remove_const<typename boost::remove_reference<A1 >::type>::type> , MatcherContainer<typename boost::remove_const<typename boost::remove_reference<A2 >::type>::type> , MatcherContainer<typename boost::remove_const<typename boost::remove_reference<A3 >::type>::type> , MatcherContainer<typename boost::remove_const<typename boost::remove_reference<A4 >::type>::type> , MatcherContainer<typename boost::remove_const<typename boost::remove_reference<A5 >::type>::type> , MatcherContainer<typename boost::remove_const<typename boost::remove_reference<A6 >::type>::type> , MatcherContainer<typename boost::remove_const<typename boost::remove_reference<A7 >::type>::type> , MatcherContainer<typename boost::remove_const<typename boost::remove_reference<A8 >::type>::type> > matcher_tuple_type;
         typedef Answer<R>*            answer_type;
         typedef std::list<answer_type> queue_type;

         //TODO: rename argument lists
         std::map<tuple_type, queue_type> answerMap;
         std::list<KeyPair<matcher_tuple_type, queue_type> > answerList;

         queue_type* ongoingMatch;
         Verifier   verifier;

         OngoingStubbing()
            : answerMap()
            , answerList()
            , ongoingMatch()
            , verifier()
            {}

         OngoingStubbing& when(const matcher::Matcher<typename boost::remove_const<typename boost::remove_reference<A0 >::type>::type>& a0, const matcher::Matcher<typename boost::remove_const<typename boost::remove_reference<A1 >::type>::type>& a1, const matcher::Matcher<typename boost::remove_const<typename boost::remove_reference<A2 >::type>::type>& a2, const matcher::Matcher<typename boost::remove_const<typename boost::remove_reference<A3 >::type>::type>& a3, const matcher::Matcher<typename boost::remove_const<typename boost::remove_reference<A4 >::type>::type>& a4, const matcher::Matcher<typename boost::remove_const<typename boost::remove_reference<A5 >::type>::type>& a5, const matcher::Matcher<typename boost::remove_const<typename boost::remove_reference<A6 >::type>::type>& a6, const matcher::Matcher<typename boost::remove_const<typename boost::remove_reference<A7 >::type>::type>& a7, const matcher::Matcher<typename boost::remove_const<typename boost::remove_reference<A8 >::type>::type>& a8)
         {
            matcher_tuple_type arguments = matcher_tuple_type(a0, a1, a2, a3, a4, a5, a6, a7, a8);
            typename std::list<KeyPair<matcher_tuple_type, queue_type> >::iterator pair_it;
            pair_it = find(answerList.begin(), answerList.end(), arguments);
            if(pair_it == answerList.end())
            {
               answerList.push_back(KeyPair<matcher_tuple_type, queue_type>(arguments, queue_type()));
               pair_it = --answerList.end();
            }
            ongoingMatch = &(pair_it->value);
            return *this;
         }

         OngoingStubbing& when(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8)
         {
            ongoingMatch = &(answerMap[tuple_type(a0, a1, a2, a3, a4, a5, a6, a7, a8)]);
            return *this;
         }

         template <typename T>
         OngoingStubbing& thenThrow(T throwable)
         {
            ongoingMatch->push_back(new Throws<R, T>(throwable));
            return *this;
         }

         R invoke(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8)
         {
            verifier.calls++;
            tuple_type  args    = tuple_type(a0, a1, a2, a3, a4, a5, a6, a7, a8);
            queue_type& answers = answerMap[args];
            if(answers.empty())
            {
               typename std::list<KeyPair<matcher_tuple_type, queue_type> >::iterator pair_it;
               pair_it = find(answerList.begin(), answerList.end(), args);
               if(pair_it == answerList.end())
                  { throw IncompleteImplementationException(); }
               answers = pair_it->value;
            }
            answer_type answer = answers.front();
            if(answers.size() > 1)
               { answers.pop_front(); }
            return answer->execute();
         }

         const Verifier& getVerifier() const
            { return verifier; }

         OngoingStubbing& thenReturn(R value)
         {
            ongoingMatch->push_back(new Returns<R>(value));
            return *this;
         }
      };
 
      // void partial specialization for 10 arguments
      template <typename C, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9>
      struct OngoingStubbing<void (C::*)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9)>
      {
         
         typedef boost::tuple<typename boost::remove_const<typename boost::remove_reference<A0 >::type>::type, typename boost::remove_const<typename boost::remove_reference<A1 >::type>::type, typename boost::remove_const<typename boost::remove_reference<A2 >::type>::type, typename boost::remove_const<typename boost::remove_reference<A3 >::type>::type, typename boost::remove_const<typename boost::remove_reference<A4 >::type>::type, typename boost::remove_const<typename boost::remove_reference<A5 >::type>::type, typename boost::remove_const<typename boost::remove_reference<A6 >::type>::type, typename boost::remove_const<typename boost::remove_reference<A7 >::type>::type, typename boost::remove_const<typename boost::remove_reference<A8 >::type>::type, typename boost::remove_const<typename boost::remove_reference<A9 >::type>::type> tuple_type;
         typedef boost::tuple<MatcherContainer<typename boost::remove_const<typename boost::remove_reference<A0 >::type>::type> , MatcherContainer<typename boost::remove_const<typename boost::remove_reference<A1 >::type>::type> , MatcherContainer<typename boost::remove_const<typename boost::remove_reference<A2 >::type>::type> , MatcherContainer<typename boost::remove_const<typename boost::remove_reference<A3 >::type>::type> , MatcherContainer<typename boost::remove_const<typename boost::remove_reference<A4 >::type>::type> , MatcherContainer<typename boost::remove_const<typename boost::remove_reference<A5 >::type>::type> , MatcherContainer<typename boost::remove_const<typename boost::remove_reference<A6 >::type>::type> , MatcherContainer<typename boost::remove_const<typename boost::remove_reference<A7 >::type>::type> , MatcherContainer<typename boost::remove_const<typename boost::remove_reference<A8 >::type>::type> , MatcherContainer<typename boost::remove_const<typename boost::remove_reference<A9 >::type>::type> > matcher_tuple_type;
         typedef Answer<void>*            answer_type;
         typedef std::list<answer_type> queue_type;

         //TODO: rename argument lists
         std::map<tuple_type, queue_type> answerMap;
         std::list<KeyPair<matcher_tuple_type, queue_type> > answerList;

         queue_type* ongoingMatch;
         Verifier   verifier;

         OngoingStubbing()
            : answerMap()
            , answerList()
            , ongoingMatch()
            , verifier()
            {}

         OngoingStubbing& when(const matcher::Matcher<typename boost::remove_const<typename boost::remove_reference<A0 >::type>::type>& a0, const matcher::Matcher<typename boost::remove_const<typename boost::remove_reference<A1 >::type>::type>& a1, const matcher::Matcher<typename boost::remove_const<typename boost::remove_reference<A2 >::type>::type>& a2, const matcher::Matcher<typename boost::remove_const<typename boost::remove_reference<A3 >::type>::type>& a3, const matcher::Matcher<typename boost::remove_const<typename boost::remove_reference<A4 >::type>::type>& a4, const matcher::Matcher<typename boost::remove_const<typename boost::remove_reference<A5 >::type>::type>& a5, const matcher::Matcher<typename boost::remove_const<typename boost::remove_reference<A6 >::type>::type>& a6, const matcher::Matcher<typename boost::remove_const<typename boost::remove_reference<A7 >::type>::type>& a7, const matcher::Matcher<typename boost::remove_const<typename boost::remove_reference<A8 >::type>::type>& a8, const matcher::Matcher<typename boost::remove_const<typename boost::remove_reference<A9 >::type>::type>& a9)
         {
            matcher_tuple_type arguments = matcher_tuple_type(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9);
            typename std::list<KeyPair<matcher_tuple_type, queue_type> >::iterator pair_it;
            pair_it = find(answerList.begin(), answerList.end(), arguments);
            if(pair_it == answerList.end())
            {
               answerList.push_back(KeyPair<matcher_tuple_type, queue_type>(arguments, queue_type()));
               pair_it = --answerList.end();
            }
            ongoingMatch = &(pair_it->value);
            return *this;
         }

         OngoingStubbing& when(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9)
         {
            ongoingMatch = &(answerMap[tuple_type(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9)]);
            return *this;
         }

         template <typename T>
         OngoingStubbing& thenThrow(T throwable)
         {
            ongoingMatch->push_back(new Throws<void, T>(throwable));
            return *this;
         }

         void invoke(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9)
         {
            verifier.calls++;
            tuple_type  args    = tuple_type(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9);
            queue_type& answers = answerMap[args];
            if(answers.empty())
            {
               typename std::list<KeyPair<matcher_tuple_type, queue_type> >::iterator pair_it;
               pair_it = find(answerList.begin(), answerList.end(), args);
               if(pair_it == answerList.end())
                  { throw IncompleteImplementationException(); }
               answers = pair_it->value;
            }
            answer_type answer = answers.front();
            if(answers.size() > 1)
               { answers.pop_front(); }
            return answer->execute();
         }

         const Verifier& getVerifier() const
            { return verifier; }

         OngoingStubbing& thenReturn()
         {
            ongoingMatch->push_back(new Returns<void>());
            return *this;
         }
      };

      // non-void partial specialization for 10 arguments
      template <typename R, typename C, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9>
      struct OngoingStubbing<R (C::*)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9), typename boost::disable_if<boost::is_void<R> >::type>
      {
         
         typedef boost::tuple<typename boost::remove_const<typename boost::remove_reference<A0 >::type>::type, typename boost::remove_const<typename boost::remove_reference<A1 >::type>::type, typename boost::remove_const<typename boost::remove_reference<A2 >::type>::type, typename boost::remove_const<typename boost::remove_reference<A3 >::type>::type, typename boost::remove_const<typename boost::remove_reference<A4 >::type>::type, typename boost::remove_const<typename boost::remove_reference<A5 >::type>::type, typename boost::remove_const<typename boost::remove_reference<A6 >::type>::type, typename boost::remove_const<typename boost::remove_reference<A7 >::type>::type, typename boost::remove_const<typename boost::remove_reference<A8 >::type>::type, typename boost::remove_const<typename boost::remove_reference<A9 >::type>::type> tuple_type;
         typedef boost::tuple<MatcherContainer<typename boost::remove_const<typename boost::remove_reference<A0 >::type>::type> , MatcherContainer<typename boost::remove_const<typename boost::remove_reference<A1 >::type>::type> , MatcherContainer<typename boost::remove_const<typename boost::remove_reference<A2 >::type>::type> , MatcherContainer<typename boost::remove_const<typename boost::remove_reference<A3 >::type>::type> , MatcherContainer<typename boost::remove_const<typename boost::remove_reference<A4 >::type>::type> , MatcherContainer<typename boost::remove_const<typename boost::remove_reference<A5 >::type>::type> , MatcherContainer<typename boost::remove_const<typename boost::remove_reference<A6 >::type>::type> , MatcherContainer<typename boost::remove_const<typename boost::remove_reference<A7 >::type>::type> , MatcherContainer<typename boost::remove_const<typename boost::remove_reference<A8 >::type>::type> , MatcherContainer<typename boost::remove_const<typename boost::remove_reference<A9 >::type>::type> > matcher_tuple_type;
         typedef Answer<R>*            answer_type;
         typedef std::list<answer_type> queue_type;

         //TODO: rename argument lists
         std::map<tuple_type, queue_type> answerMap;
         std::list<KeyPair<matcher_tuple_type, queue_type> > answerList;

         queue_type* ongoingMatch;
         Verifier   verifier;

         OngoingStubbing()
            : answerMap()
            , answerList()
            , ongoingMatch()
            , verifier()
            {}

         OngoingStubbing& when(const matcher::Matcher<typename boost::remove_const<typename boost::remove_reference<A0 >::type>::type>& a0, const matcher::Matcher<typename boost::remove_const<typename boost::remove_reference<A1 >::type>::type>& a1, const matcher::Matcher<typename boost::remove_const<typename boost::remove_reference<A2 >::type>::type>& a2, const matcher::Matcher<typename boost::remove_const<typename boost::remove_reference<A3 >::type>::type>& a3, const matcher::Matcher<typename boost::remove_const<typename boost::remove_reference<A4 >::type>::type>& a4, const matcher::Matcher<typename boost::remove_const<typename boost::remove_reference<A5 >::type>::type>& a5, const matcher::Matcher<typename boost::remove_const<typename boost::remove_reference<A6 >::type>::type>& a6, const matcher::Matcher<typename boost::remove_const<typename boost::remove_reference<A7 >::type>::type>& a7, const matcher::Matcher<typename boost::remove_const<typename boost::remove_reference<A8 >::type>::type>& a8, const matcher::Matcher<typename boost::remove_const<typename boost::remove_reference<A9 >::type>::type>& a9)
         {
            matcher_tuple_type arguments = matcher_tuple_type(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9);
            typename std::list<KeyPair<matcher_tuple_type, queue_type> >::iterator pair_it;
            pair_it = find(answerList.begin(), answerList.end(), arguments);
            if(pair_it == answerList.end())
            {
               answerList.push_back(KeyPair<matcher_tuple_type, queue_type>(arguments, queue_type()));
               pair_it = --answerList.end();
            }
            ongoingMatch = &(pair_it->value);
            return *this;
         }

         OngoingStubbing& when(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9)
         {
            ongoingMatch = &(answerMap[tuple_type(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9)]);
            return *this;
         }

         template <typename T>
         OngoingStubbing& thenThrow(T throwable)
         {
            ongoingMatch->push_back(new Throws<R, T>(throwable));
            return *this;
         }

         R invoke(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9)
         {
            verifier.calls++;
            tuple_type  args    = tuple_type(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9);
            queue_type& answers = answerMap[args];
            if(answers.empty())
            {
               typename std::list<KeyPair<matcher_tuple_type, queue_type> >::iterator pair_it;
               pair_it = find(answerList.begin(), answerList.end(), args);
               if(pair_it == answerList.end())
                  { throw IncompleteImplementationException(); }
               answers = pair_it->value;
            }
            answer_type answer = answers.front();
            if(answers.size() > 1)
               { answers.pop_front(); }
            return answer->execute();
         }

         const Verifier& getVerifier() const
            { return verifier; }

         OngoingStubbing& thenReturn(R value)
         {
            ongoingMatch->push_back(new Returns<R>(value));
            return *this;
         }
      };
   } // namespace detail
} // namespace mockitopp

#endif //__MOCKITOPP_ONGOING_STUBBING_HPP__
