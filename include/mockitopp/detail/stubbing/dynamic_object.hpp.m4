#ifndef __MOCKITOPP_MOCK_OBJECT_IMPL_HPP__
#define __MOCKITOPP_MOCK_OBJECT_IMPL_HPP__

#include <mockitopp/detail/exception/NotImplementedException.hpp>
#include <mockitopp/detail/stubbing/OngoingStubbing.hpp>
#include <mockitopp/detail/stubbing/Stub.hpp>

// TODO: add documentation
namespace mockitopp
{
   namespace detail
   {
      struct vfunction_offset_helper
      {
         template <typename T>
         static int get(T ptr2member)
         {
            vfunction_offset_helper f;
            return (f.*reinterpret_cast<int (vfunction_offset_helper::*)()>(ptr2member))();
         }

include(`mockitopp/detail/m4/REPEAT.m4')dnl
define(`VFUNCTION_OFFSET_HELPER_METHOD', `        virtual int offset$1() { return $1; }
')dnl
M4_REPEAT(MOCKITOPP_MAX_VIRTUAL_FUNCTIONS, `VFUNCTION_OFFSET_HELPER_METHOD')dnl
      };

      struct dynamic_object
      {
         struct vtable
         {
            void* __vtable[MAX_VIRTUAL_FUNCTIONS];

            template <typename T>
            vtable(T function)
            {
               for(int i = 0; i < MAX_VIRTUAL_FUNCTIONS; i++)
                  { __vtable[i] = horrible_cast<void*>(function); }
            }
         };

         vtable* __vptr;
         void*   __spys[MAX_VIRTUAL_FUNCTIONS];

         dynamic_object()
            : __vptr(new vtable(&dynamic_object::NotImplemented))
            { memset(__spys, 0, MAX_VIRTUAL_FUNCTIONS); }

         ~dynamic_object()
         {
            delete __vptr;
//            for(int i = 0; i < MAX_VIRTUAL_FUNCTIONS; i++)
//               { delete __spys[i]; }
         }

         template <typename M>
         OngoingStubbing<M>& beginStubbing(M ptr2member)
         {
            int offset = vfunction_offset_helper::get(ptr2member);
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
