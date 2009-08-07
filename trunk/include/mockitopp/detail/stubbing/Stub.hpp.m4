#ifndef __MOCKITOPP_STUB_HPP__
#define __MOCKITOPP_STUB_HPP__

#include <mockitopp/detail/stubbing/OngoingStubbing.hpp>
#include <mockitopp/detail/util/horrible_cast.hpp>

include(`mockitopp/detail/m4/ENUM_BINARY_PARAMS.m4')dnl
include(`mockitopp/detail/m4/ENUM_PARAMS.m4')dnl
include(`mockitopp/detail/m4/ENUM_TRAILING_PARAMS.m4')dnl
include(`mockitopp/detail/m4/REPEAT.m4')dnl
namespace mockitopp
{
   namespace detail
   {
      template <int OFFSET, typename T> struct StubImpl;

define(`DEFINE_STUB_IMPL',
`     template <int OFFSET, typename R, typename C M4_ENUM_TRAILING_PARAMS($1, typename A)>
      struct StubImpl<OFFSET, R (C::*)(M4_ENUM_PARAMS($1, A))>
      {
         void* __PAD_FOR_MOCK_vptr;
         OngoingStubbing<R (C::*)(M4_ENUM_PARAMS($1, A))>*
            __PAD_FOR_MOCK_spys[MOCKITOPP_MAX_VIRTUAL_FUNCTIONS];

         R invoke(M4_ENUM_BINARY_PARAMS($1, A, a))
            { return __PAD_FOR_MOCK_spys[OFFSET]->invoke(M4_ENUM_PARAMS($1, a)); }
      };

')dnl
dnl add one to max arity so we generate 0 argument case
M4_REPEAT(eval(MOCKITOPP_MAX_VIRTUAL_FUNCTION_ARITY + 1), `DEFINE_STUB_IMPL')dnl

      template <typename M>
      struct Stub
      {
         static void* getInstance(M ptr2member)
         {
            Stub s;
            return (s.*reinterpret_cast<void* (Stub::*)()>(ptr2member))();
         }

define(`DEFINE_DYNAMIC_INVOKE_PROXY', `        virtual void* invoke_proxy$1() { return horrible_cast<void*>(&StubImpl<$1, M>::invoke); }
')dnl
M4_REPEAT(MOCKITOPP_MAX_VIRTUAL_FUNCTIONS, `DEFINE_DYNAMIC_INVOKE_PROXY')dnl
      };
   } // namespace detail
} // namespace mockitopp

#endif //__MOCKITOPP_STUB_HPP__
