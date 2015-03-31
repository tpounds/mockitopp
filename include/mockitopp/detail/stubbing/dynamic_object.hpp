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

         virtual int offset0() { return 0; }
         virtual int offset1() { return 1; }
         virtual int offset2() { return 2; }
         virtual int offset3() { return 3; }
         virtual int offset4() { return 4; }
         virtual int offset5() { return 5; }
         virtual int offset6() { return 6; }
         virtual int offset7() { return 7; }
         virtual int offset8() { return 8; }
         virtual int offset9() { return 9; }
         virtual int offset10() { return 10; }
         virtual int offset11() { return 11; }
         virtual int offset12() { return 12; }
         virtual int offset13() { return 13; }
         virtual int offset14() { return 14; }
         virtual int offset15() { return 15; }
         virtual int offset16() { return 16; }
         virtual int offset17() { return 17; }
         virtual int offset18() { return 18; }
         virtual int offset19() { return 19; }
         virtual int offset20() { return 20; }
         virtual int offset21() { return 21; }
         virtual int offset22() { return 22; }
         virtual int offset23() { return 23; }
         virtual int offset24() { return 24; }
         virtual int offset25() { return 25; }
         virtual int offset26() { return 26; }
         virtual int offset27() { return 27; }
         virtual int offset28() { return 28; }
         virtual int offset29() { return 29; }
         virtual int offset30() { return 30; }
         virtual int offset31() { return 31; }
         virtual int offset32() { return 32; }
         virtual int offset33() { return 33; }
         virtual int offset34() { return 34; }
         virtual int offset35() { return 35; }
         virtual int offset36() { return 36; }
         virtual int offset37() { return 37; }
         virtual int offset38() { return 38; }
         virtual int offset39() { return 39; }
         virtual int offset40() { return 40; }
         virtual int offset41() { return 41; }
         virtual int offset42() { return 42; }
         virtual int offset43() { return 43; }
         virtual int offset44() { return 44; }
         virtual int offset45() { return 45; }
         virtual int offset46() { return 46; }
         virtual int offset47() { return 47; }
         virtual int offset48() { return 48; }
         virtual int offset49() { return 49; }

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
            void* functions[50];
         };

         void*   vtable_object_ptr;
         void*   vtable_mocks[50];
         vtable* vtable_actual_ptr;

         dynamic_object()
            : vtable_actual_ptr(new vtable)
         {
            vtable_actual_ptr->vbase_offset  = 0;
            vtable_actual_ptr->vcall_offset  = 0;
            vtable_actual_ptr->offset_to_top = 0;
            vtable_actual_ptr->type_info     = 0;
            for(int i = 0; i < 50; i++)
            {
               vtable_actual_ptr->functions[i] = horrible_cast<void*>(&dynamic_object::missing_vfunction);
               vtable_mocks[i] = 0;
            }
            vtable_object_ptr = vtable_actual_ptr->functions;
         }

         ~dynamic_object()
         {
            for(int i = 0; i < 50; i++)
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

         template <typename M>
         void delete_function(M ptr2member)
         {
            int offset = vtable_offset_helper::get(ptr2member);
            if (vtable_mocks[offset] != 0) {
               delete reinterpret_cast<dynamic_vfunction_base*>(vtable_mocks[offset]);
               vtable_actual_ptr->functions[offset] = horrible_cast<void*>(&dynamic_object::missing_vfunction);
               vtable_mocks[offset] = 0;
            }
         }

         void missing_vfunction()
            { throw missing_implementation_exception(); }
      };
   } // namespace detail
} // namespace mockitopp

#endif //__MOCKITOPP_DYNAMIC_OBJECT_HPP__
