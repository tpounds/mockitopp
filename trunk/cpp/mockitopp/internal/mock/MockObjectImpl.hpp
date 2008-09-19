#ifndef __MOCKITOPP_MOCK_OBJECT_IMPL_HPP__
#define __MOCKITOPP_MOCK_OBJECT_IMPL_HPP__

#include <mockitopp/Configuration.hpp>
#include <mockitopp/internal/matcher/ArgumentMatcher.hpp>
#include <mockitopp/internal/mock/VirtualTable.hpp>

// TODO: add documentation
namespace mockitopp
{
   namespace detail
   {
      struct MockObjectImpl
      {
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

         template <typename M> void stubImpl(M ptr2member);

         template <typename M> ArgumentMatcher<M>& getMatcher(M ptr2member);

         template <typename M> int getCalls(M ptr2member);
      };
   } // namespace detail
}

#include <mockitopp/internal/mock/MockObjectImpl.tcpp>

#endif //__MOCKITOPP_MOCK_OBJECT_IMPL_HPP__
