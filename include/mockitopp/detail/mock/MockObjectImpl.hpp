#ifndef __MOCKITOPP_MOCK_OBJECT_IMPL_HPP__
#define __MOCKITOPP_MOCK_OBJECT_IMPL_HPP__

#include <mockitopp/Configuration.hpp>
#include <mockitopp/detail/matcher/ArgumentMatcher.hpp>
#include <mockitopp/detail/mock/VirtualTable.hpp>
#include <mockitopp/detail/stubbing/Stub.hpp>
#include <mockitopp/detail/stubbing/StubImplData.hpp>
#include <mockitopp/detail/utility/FunctionAddress.hpp>

// TODO: add documentation
namespace mockitopp
{
   namespace detail
   {
      struct MockObjectImpl
      {
         template <typename T>
         struct OngoingStubbing
         {
            typedef ArgumentMatcher<T> base_type;
         };

         VirtualTable* __vptr;
         void*         __stubImpl[MAX_VIRTUAL_FUNCTIONS];

         MockObjectImpl()
            : __vptr(new VirtualTable())
            , __stubImpl()
         {}

         ~MockObjectImpl()
         {
            delete __vptr;
//            for(int i = 0; i < MAX_VIRTUAL_FUNCTIONS; i++)
//               { delete __stubImpl[i]; }
         }

         template <typename M>
         int getCalls(M ptr2member)
            { return reinterpret_cast<StubImplData<M>*>(__stubImpl[FunctionAddress::offset(ptr2member)])->getCalls(); }

         template <typename M>
         ArgumentMatcher<M>& doStub(M ptr2member)
         {
            size_t vtable_offset = FunctionAddress::offset(ptr2member);
            __vptr->__vtable[vtable_offset] = Stub::getInstance<M>(vtable_offset);
            __stubImpl[vtable_offset] = new StubImplData<M>();
            return reinterpret_cast<StubImplData<M>*>(__stubImpl[FunctionAddress::offset(ptr2member)])->getMatcher();
         }

         template <typename M>
         bool doVerify(M ptr2member, int minTimes, int maxTimes)
         {
            int calls = getCalls(ptr2member);
            if(calls >= minTimes && calls <= maxTimes)
               { return true; }
            return false;
         }
      };
   } // namespace detail
} // namespace mockitopp

#endif //__MOCKITOPP_MOCK_OBJECT_IMPL_HPP__
