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
      T& getInstance()
        { return reinterpret_cast<T&>(*this); }

      /**
       * stub functionality for a given method
       *
       * @param ptr2member method to be stubbed
       */
      template <typename M>
      detail::OngoingStubbing<M>& operator() (M ptr2member)
         { return beginStubbing(ptr2member); }

      /**
       * verify method innvocation occurances
       *
       * @param ptr2member method to be verify
       */
      template <typename M>
      const detail::Verifier& verify(M ptr2member)
         { return doVerify(ptr2member); }
   };
} // namespace mockitopp

#endif //__MOCKITOPP_MOCK_OBJECT_HPP__
