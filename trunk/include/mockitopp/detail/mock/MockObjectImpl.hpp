#ifndef __MOCKITOPP_MOCK_OBJECT_IMPL_HPP__
#define __MOCKITOPP_MOCK_OBJECT_IMPL_HPP__

#include <mockitopp/detail/mock/VirtualTable.hpp>
#include <mockitopp/detail/stubbing/OngoingStubbing.hpp>
#include <mockitopp/detail/stubbing/Stub.hpp>
#include <mockitopp/detail/stubbing/Verifier.hpp>
#include <mockitopp/detail/utility/Function.hpp>

// TODO: add documentation
namespace mockitopp
{
   namespace detail
   {
      struct MockObjectImpl
      {
         VirtualTable* __vptr;
         void*         __spys[MAX_VIRTUAL_FUNCTIONS];
         Verifier      __verifier;

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
         OngoingStubbing<M>& doWhen(M ptr2member)
         {
            int offset = Function::getOffset(ptr2member);
            if(__spys[offset] == NULL)
            {
               __vptr->__vtable[offset] = Stub<M>::getInstance(ptr2member);
               __spys[offset] = new OngoingStubbing<M>();
            }
            return *reinterpret_cast<OngoingStubbing<M>*>(__spys[offset]);
         }

         template <typename M>
         const Verifier& doVerify(M ptr2member)
         {
            __verifier.calls = reinterpret_cast<OngoingStubbing<M>*>(__spys[Function::getOffset(ptr2member)])->getCalls();
            return __verifier;
         }
      };
   } // namespace detail
} // namespace mockitopp

#endif //__MOCKITOPP_MOCK_OBJECT_IMPL_HPP__
