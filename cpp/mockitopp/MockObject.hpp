#ifndef __MOCKITOPP_MOCK_OBJECT_HPP__
#define __MOCKITOPP_MOCK_OBJECT_HPP__

#include <mockitopp/internal/matcher/ArgumentMatcher.hpp>
#include <mockitopp/internal/mock/MockObjectImpl.hpp>

// TODO: add documentation
namespace mockitopp
{
   /**
    * @author Trevor Pounds
    */
   template <typename T>
   struct MockObject : protected detail::MockObjectImpl
   {
      typedef T interface_type;

      interface_type& getMock()
        { return reinterpret_cast<interface_type&>(*this); }

      template <typename M>
      detail::ArgumentMatcher<M>& stub(M ptr2member)
      {
         stubImpl(ptr2member);
         return getMatcher(ptr2member);
      }

      template <typename M>
      bool verify(M ptr2member, int minTimes, int maxTimes)
      {
         int calls = getCalls(ptr2member);
         if(calls >= minTimes && calls <= maxTimes)
            { return true; }
         return false;
      }

      template <typename M>
      bool verifyAtLeast(M ptr2member, int times)
         { return verify(ptr2member, times, 0x7FFF); }

      template <typename M>
      bool verifyAtMost(M ptr2member, int times)
         { return verify(ptr2member, 0, times); }

      template <typename M>
      bool verifyExactly(M ptr2member, int times)
         { return verify(ptr2member, times, times); }

      template <typename M>
      bool verifyNever(M ptr2member)
         { return verify(ptr2member, 0, 0); }
   };

} // namespace mockitopp

#endif //__MOCKITOPP_MOCK_OBJECT_HPP__
