#ifndef __MOCKITOPP_MOCK_OBJECT_IMPL_HPP__
#define __MOCKITOPP_MOCK_OBJECT_IMPL_HPP__

#include <mockitopp/detail/exception/NotImplementedException.hpp>
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

         MockObjectImpl()
            : __vptr(new VirtualTable(&MockObjectImpl::NotImplemented))
            { memset(__spys, 0, MAX_VIRTUAL_FUNCTIONS); }

         ~MockObjectImpl()
         {
            delete __vptr;
//            for(int i = 0; i < MAX_VIRTUAL_FUNCTIONS; i++)
//               { delete __spys[i]; }
         }

         template <typename M>
         OngoingStubbing<M>& beginStubbing(M ptr2member)
         {
            int offset = Function::getOffset(ptr2member);
            if(__spys[offset] == NULL)
            {
               __vptr->__vtable[offset] = Stub<M>::getInstance(ptr2member);
               __spys[offset] = new OngoingStubbing<M>();
            }
            return *reinterpret_cast<OngoingStubbing<M>*>(__spys[offset]);
         }

         void NotImplemented()
            { throw NotImplementedException(); }
      };
   } // namespace detail
} // namespace mockitopp

#endif //__MOCKITOPP_MOCK_OBJECT_IMPL_HPP__
