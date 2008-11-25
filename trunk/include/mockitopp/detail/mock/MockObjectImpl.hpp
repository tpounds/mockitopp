#ifndef __MOCKITOPP_MOCK_OBJECT_IMPL_HPP__
#define __MOCKITOPP_MOCK_OBJECT_IMPL_HPP__

#include <boost/preprocessor/repetition/repeat.hpp>

#include <mockitopp/detail/mock/VirtualTable.hpp>
#include <mockitopp/detail/stubbing/OngoingStubbing.hpp>
#include <mockitopp/detail/stubbing/StubImpl.hpp>
#include <mockitopp/detail/utility/FunctionAddress.hpp>

// TODO: add documentation
namespace mockitopp
{
   namespace detail
   {
      struct MockObjectImpl
      {
         VirtualTable* __vptr;
         void*         __spys[MAX_VIRTUAL_FUNCTIONS];

         MockObjectImpl()
            : __vptr(new VirtualTable())
            , __spys()
         {}

         ~MockObjectImpl()
         {
            delete __vptr;
//            for(int i = 0; i < MAX_VIRTUAL_FUNCTIONS; i++)
//               { delete __spys[i]; }
         }

         template <typename M>
         static void* createStub(M ptr2member)
         {
            void* stubs[MAX_VIRTUAL_FUNCTIONS];

            #define ASSIGN_STUB_TO_TABLE(ZZZ, NNN, TTT) \
               stubs[NNN] = FunctionAddress::unsafe_cast(&StubImpl<NNN, M>::invoke);

            BOOST_PP_REPEAT(MAX_VIRTUAL_FUNCTIONS, ASSIGN_STUB_TO_TABLE, ~)

            #undef ASSIGN_STUB_TO_TABLE

            return stubs[FunctionAddress::offset(ptr2member)];
         }

         template <typename M>
         OngoingStubbing<M>& doWhen(M ptr2member)
         {
            size_t vtable_offset = FunctionAddress::offset(ptr2member);
            if(__spys[vtable_offset] == NULL)
            {
               __vptr->__vtable[vtable_offset] = createStub(ptr2member);
               __spys[vtable_offset] = new OngoingStubbing<M>();
            }
            return *reinterpret_cast<OngoingStubbing<M>*>(__spys[vtable_offset]);
         }

         template <typename M>
         bool doVerify(M ptr2member, int minTimes, int maxTimes)
         {
            int calls = reinterpret_cast<OngoingStubbing<M>*>(__spys[FunctionAddress::offset(ptr2member)])->getCalls();
            if(calls >= minTimes && calls <= maxTimes)
               { return true; }
            return false;
         }
      };
   } // namespace detail
} // namespace mockitopp

#endif //__MOCKITOPP_MOCK_OBJECT_IMPL_HPP__
