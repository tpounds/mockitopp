#ifndef __MOCKITOPP_DYNAMIC_OBJECT_HPP__
#define __MOCKITOPP_DYNAMIC_OBJECT_HPP__

#include <mockitopp/exceptions.hpp>
#include <mockitopp/detail/stubbing/dynamic_vfunction.hpp>
#include <mockitopp/detail/stubbing/proxy_vfunction.hpp>
#include <mockitopp/detail/util/remove_member_function_pointer_cv.hpp>

namespace mockitopp
{
   namespace detail
   {
      /**
       * helper class to find the vtable offset given a member function pointer
       */
      struct vtable_offset_helper
      {
         template <typename T>
         static int get(T ptr2member)
         {
            vtable_offset_helper f;
            return (f.*reinterpret_cast<int (vtable_offset_helper::*)()>(ptr2member))();
         }

include(`mockitopp/detail/m4/REPEAT.m4')dnl
define(`DEFINE_VTABLE_OFFSET_HELPER_FUNCTION', `        virtual int offset$1() { return $1; }
')dnl
M4_REPEAT(MOCKITOPP_MAX_VIRTUAL_FUNCTIONS, `DEFINE_VTABLE_OFFSET_HELPER_FUNCTION')dnl

         virtual ~vtable_offset_helper() {}
      };

      /**
       * implementation class for pseduo-dynamically defining an interface
       */
      struct dynamic_object
      {
         struct vtable { void* __vtable[MOCKITOPP_MAX_VIRTUAL_FUNCTIONS]; };

         vtable* __vptr;
         void*   __spys[MOCKITOPP_MAX_VIRTUAL_FUNCTIONS];

         dynamic_object()
            : __vptr(new vtable)
         {
            for(int i = 0; i < MOCKITOPP_MAX_VIRTUAL_FUNCTIONS; i++)
            {
               __vptr->__vtable[i] = horrible_cast<void*>(&dynamic_object::missing_vfunction);
               __spys[i] = 0;
            }
         }

         ~dynamic_object()
         {
            // delete __vptr->__vtable[i] not necessary, entries point to statically defined functions
            delete __vptr;
            for(int i = 0; i < MOCKITOPP_MAX_VIRTUAL_FUNCTIONS; i++)
            {
               if(__spys[i] != 0)
                  { delete reinterpret_cast<dynamic_vfunction_base*>(__spys[i]); }
            }
         }

         template <typename M>
         dynamic_vfunction<typename remove_member_function_pointer_cv<M>::type>& define_function(M ptr2member)
         {
            int offset = vtable_offset_helper::get(ptr2member);
            if(__spys[offset] == 0)
            {
               __vptr->__vtable[offset] = proxy_vfunction_factory<M>::get(ptr2member);
               __spys[offset] = new dynamic_vfunction<typename remove_member_function_pointer_cv<M>::type>();
            }
            return *reinterpret_cast<dynamic_vfunction<typename remove_member_function_pointer_cv<M>::type>*>(__spys[offset]);
         }

         void missing_vfunction()
            { throw missing_implementation_exception(); }
      };
   } // namespace detail
} // namespace mockitopp

#endif //__MOCKITOPP_DYNAMIC_OBJECT_HPP__
