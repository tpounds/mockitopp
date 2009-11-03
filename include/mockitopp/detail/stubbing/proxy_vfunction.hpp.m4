#ifndef __MOCKITOPP_PROXY_VFUNCTION_HPP__
#define __MOCKITOPP_PROXY_VFUNCTION_HPP__

#include <mockitopp/detail/stubbing/dynamic_vfunction.hpp>
#include <mockitopp/detail/util/horrible_cast.hpp>
#include <mockitopp/detail/util/remove_member_function_pointer_cv.hpp>

include(`mockitopp/detail/m4/ENUM_BINARY_PARAMS.m4')dnl
include(`mockitopp/detail/m4/ENUM_PARAMS.m4')dnl
include(`mockitopp/detail/m4/ENUM_TRAILING_PARAMS.m4')dnl
include(`mockitopp/detail/m4/REPEAT.m4')dnl
namespace mockitopp
{
   namespace detail
   {
      template <int OFFSET, typename T> struct proxy_vfunction;

define(`DEFINE_PROXY_VFUNCTION',
`     template <int OFFSET, typename R, typename C M4_ENUM_TRAILING_PARAMS($1, typename A)>
      struct proxy_vfunction<OFFSET, R (C::*)(M4_ENUM_PARAMS($1, A))>
      {
         void* __PAD_FOR_MOCK_vptr;
         dynamic_vfunction<R (C::*)(M4_ENUM_PARAMS($1, A))>*
            __PAD_FOR_MOCK_spys[MOCKITOPP_MAX_VIRTUAL_FUNCTIONS];

         R invoke(M4_ENUM_BINARY_PARAMS($1, A, a))
            { return __PAD_FOR_MOCK_spys[OFFSET]->invoke(M4_ENUM_PARAMS($1, a)); }
      };

')dnl
dnl add one to max arity so we generate 0 argument case
M4_REPEAT(eval(MOCKITOPP_MAX_VIRTUAL_FUNCTION_ARITY + 1), `DEFINE_PROXY_VFUNCTION')dnl

      template <typename M>
      struct proxy_vfunction_factory
      {
         static void* get(M ptr2member)
         {
            proxy_vfunction_factory s;
            return (s.*reinterpret_cast<void* (proxy_vfunction_factory::*)()>(ptr2member))();
         }

define(`DEFINE_PROXY_VFUNCTION_FACTORY_OFFSET_FUNCTION', `        virtual void* offset$1() { return horrible_cast<void*>(&proxy_vfunction<$1, typename remove_member_function_pointer_cv<M>::type>::invoke); }
')dnl
M4_REPEAT(MOCKITOPP_MAX_VIRTUAL_FUNCTIONS, `DEFINE_PROXY_VFUNCTION_FACTORY_OFFSET_FUNCTION')dnl

         virtual ~proxy_vfunction_factory() {}
      };
   } // namespace detail
} // namespace mockitopp

#endif //__MOCKITOPP_PROXY_VFUNCTION_HPP__
