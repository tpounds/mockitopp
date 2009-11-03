#ifndef __MOCKITOPP_REMOVE_MEMBER_FUNCTION_POINTER_CV_HPP__
#define __MOCKITOPP_REMOVE_MEMBER_FUNCTION_POINTER_CV_HPP__

include(`mockitopp/detail/m4/ENUM_PARAMS.m4')dnl
include(`mockitopp/detail/m4/ENUM_TRAILING_PARAMS.m4')dnl
include(`mockitopp/detail/m4/REPEAT.m4')dnl
namespace mockitopp
{
   namespace detail
   {
      /** 
       * Simple meta-prorgramming template that removes
       * const/volatile from member function pointers
       * making them suitable for internal use.
       * 
       * @author Trevor Pounds
       */
      template <typename T>
      struct remove_member_function_pointer_cv
         { typedef T type; };

define(`REMOVE_MFP_CV_TEMPLATE',
`     // $1 argument MFP remove const template
      template <typename R, typename C`'M4_ENUM_TRAILING_PARAMS($1, typename A)>
      struct remove_member_function_pointer_cv<R (C::*)(M4_ENUM_PARAMS($1, A)) const>
         { typedef R (C::*type)(M4_ENUM_PARAMS($1, A)); };

      // $1 argument MFP remove const volatile template
      template <typename R, typename C`'M4_ENUM_TRAILING_PARAMS($1, typename A)>
      struct remove_member_function_pointer_cv<R (C::*)(M4_ENUM_PARAMS($1, A)) const volatile>
         { typedef R (C::*type)(M4_ENUM_PARAMS($1, A)); };

')dnl
M4_REPEAT(eval(MOCKITOPP_MAX_VIRTUAL_FUNCTION_ARITY + 1), `REMOVE_MFP_CV_TEMPLATE')dnl
   } // namespace detail
} // namespace mockitopp

#endif //__MOCKITOPP_TR1_TYPE_TRAITS_HPP__
