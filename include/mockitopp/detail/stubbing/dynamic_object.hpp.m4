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
         struct vtable {
            void* vbase_offset;
            void* vcall_offset;
            void* offset_to_top;
            void* type_info;
            void* functions[MOCKITOPP_MAX_VIRTUAL_FUNCTIONS];
         };

         void*   vtable_object_ptr;
         void*   vtable_mocks[MOCKITOPP_MAX_VIRTUAL_FUNCTIONS];
         vtable* vtable_actual_ptr;

         dynamic_object()
            : vtable_actual_ptr(new vtable)
         {
            vtable_actual_ptr->vbase_offset  = 0;
            vtable_actual_ptr->vcall_offset  = 0;
            vtable_actual_ptr->offset_to_top = 0;
            vtable_actual_ptr->type_info     = 0;
            for(int i = 0; i < MOCKITOPP_MAX_VIRTUAL_FUNCTIONS; i++)
            {
               vtable_actual_ptr->functions[i] = horrible_cast<void*>(&dynamic_object::missing_vfunction);
               vtable_mocks[i] = 0;
            }
            vtable_object_ptr = vtable_actual_ptr->functions;
         }

         ~dynamic_object()
         {
            for(int i = 0; i < MOCKITOPP_MAX_VIRTUAL_FUNCTIONS; i++)
            {
               if(vtable_mocks[i] != 0)
                  { delete reinterpret_cast<dynamic_vfunction_base*>(vtable_mocks[i]); }
            }
            delete vtable_actual_ptr;
         }

         template <typename M>
         dynamic_vfunction<typename remove_member_function_pointer_cv<M>::type>& define_function(M ptr2member)
         {
            int offset = vtable_offset_helper::get(ptr2member);
            if(vtable_mocks[offset] == 0)
            {
               vtable_actual_ptr->functions[offset] = proxy_vfunction_factory<M>::get(ptr2member);
               vtable_mocks[offset] = new dynamic_vfunction<typename remove_member_function_pointer_cv<M>::type>();
            }
            return *reinterpret_cast<dynamic_vfunction<typename remove_member_function_pointer_cv<M>::type>*>(vtable_mocks[offset]);
         }

         void missing_vfunction()
            { throw missing_implementation_exception(); }
      };
   } // namespace detail
} // namespace mockitopp

#endif //__MOCKITOPP_DYNAMIC_OBJECT_HPP__
