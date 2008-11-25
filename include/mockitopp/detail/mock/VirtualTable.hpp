#ifndef __MOCKITOPP_VIRTUAL_TABLE_HPP__
#define __MOCKITOPP_VIRTUAL_TABLE_HPP__

#include <exception>

#include <mockitopp/detail/utility/HorribleCast.hpp>

// TODO: add documentation
namespace mockitopp
{
   namespace detail
   {
      /**
       * @author Trevor Pounds
       */
      struct VirtualTable
      {
         void* __vtable[MAX_VIRTUAL_FUNCTIONS];

         VirtualTable()
         {
            for(int i = 0; i < MAX_VIRTUAL_FUNCTIONS; i++)
               { __vtable[i] = horrible_cast<void*>(&VirtualTable::virtualFunctionNotImplemented); }
         }

         struct NotImplementedException : public std::exception {};
         void virtualFunctionNotImplemented()
            { throw NotImplementedException(); }
      };

   } // namespace detail
} // namespace mockitopp

#endif //__MOCKITOPP_VIRTUAL_TABLE_HPP__
