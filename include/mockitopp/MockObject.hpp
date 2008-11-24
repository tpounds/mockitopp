#ifndef __MOCKITOPP_MOCK_OBJECT_HPP__
#define __MOCKITOPP_MOCK_OBJECT_HPP__

// increase to support more virtual functions
#define MAX_VIRTUAL_FUNCTIONS 50
// boost::tuple supports 0-10 elements, so don't
// support arity > 11 with this implementation.
#define MAX_VIRTUAL_FUNCTION_ARITY 11

#include <mockitopp/detail/mock/MockObjectImpl.hpp>

namespace mockitopp
{
   /**
    * provides a base implementation of a mock object
    *
    * @author Trevor Pounds
    */
   template <typename T>
   struct MockObject : protected detail::MockObjectImpl
   {
      /**
       * returns a mock object of the given abstract base class/interface
       *
       * @return mock object
       */
      T& getMock()
        { return reinterpret_cast<T&>(*this); }

      /**
       * stub functionality for a given method
       *
       * @param ptr2member method to be stubbed
       */
      template <typename M>
      typename OngoingStubbing<M>::base_type& when(M ptr2member)
         { return doStub(ptr2member); }

      /**
       * verify method invocation occurs in a certain range
       *
       * @param ptr2member method to be verify
       * @param minTimes minimum number of times method can be called
       * @param maxTimes maximum number of times method can be called
       */
      template <typename M>
      bool verify(M ptr2member, int minTimes, int maxTimes)
         { return doVerify(ptr2member, minTimes, maxTimes); }

      /**
       * verify method invocation occurs at least (n) times
       *
       * @param ptr2member method to be verify
       * @param times minimum number of times method should be called
       */
      template <typename M>
      bool verifyAtLeast(M ptr2member, int times)
         { return verify(ptr2member, times, 0x7FFF); }

      /**
       * verify method invocation occurs at most (n) times
       *
       * @param ptr2member method to be verify
       * @param times maximum number of times method should be called
       */
      template <typename M>
      bool verifyAtMost(M ptr2member, int times)
         { return verify(ptr2member, 0, times); }

      /**
       * verify method invocation exactly (n) times
       *
       * @param ptr2member method to be verify
       * @param times exact number of times method should be called
       */
      template <typename M>
      bool verifyExactly(M ptr2member, int times)
         { return verify(ptr2member, times, times); }

      /**
       * verify method invocation is never called
       *
       * @param ptr2member method to be verify
       */
      template <typename M>
      bool verifyNever(M ptr2member)
         { return verify(ptr2member, 0, 0); }
   };
} // namespace mockitopp

#endif //__MOCKITOPP_MOCK_OBJECT_HPP__
