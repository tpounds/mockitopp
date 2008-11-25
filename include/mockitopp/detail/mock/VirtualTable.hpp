#ifndef __MOCKITOPP_VIRTUAL_TABLE_HPP__
#define __MOCKITOPP_VIRTUAL_TABLE_HPP__

#include <mockitopp/detail/utility/HorribleCast.hpp>

namespace mockitopp
{
   namespace detail
   {
      /**
       * simple virtual table implementation
       *
       * @author Trevor Pounds
       */
      struct VirtualTable
      {
         void* __vtable[MAX_VIRTUAL_FUNCTIONS];

         template <typename T>
         VirtualTable(T function)
         {
            for(int i = 0; i < MAX_VIRTUAL_FUNCTIONS; i++)
               { __vtable[i] = horrible_cast<void*>(function); }
         }
      };
   } // namespace detail
} // namespace mockitopp

#endif //__MOCKITOPP_VIRTUAL_TABLE_HPP__
