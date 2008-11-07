#ifndef __MOCKITOPP_STUB_HPP__
#define __MOCKITOPP_STUB_HPP__

#include <boost/preprocessor/repetition/repeat.hpp>

#include <mockitopp/Configuration.hpp>
#include <mockitopp/detail/stubbing/StubImpl.hpp>
#include <mockitopp/detail/utility/FunctionAddress.hpp>

// TODO: add documentation
namespace mockitopp
{
   namespace detail
   {
      /**
       * @author Trevor Pounds
       */
      struct Stub
      {
         template <typename M>
         static void* getInstance(M ptr2member)
         {
            void* stubImplTable[MAX_VIRTUAL_FUNCTIONS];

            #define ASSIGN_STUB_IMPL_TO_TABLE(ZZZ, NNN, TTT) \
               stubImplTable[NNN] = FunctionAddress::unsafe_cast(&StubImpl<NNN, M>::invoke);

            BOOST_PP_REPEAT(MAX_VIRTUAL_FUNCTIONS, ASSIGN_STUB_IMPL_TO_TABLE, ~)

            #undef ASSIGN_STUB_IMPL_TO_TABLE

            return stubImplTable[FunctionAddress::offset(ptr2member)];
         }
      };
   } // namespace detail
} // namespace mockitopp

#endif //__MOCKITOPP_STUB_HPP__
