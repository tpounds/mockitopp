#ifndef __MOCKITOPP_REMOVE_MEMBER_FUNCTION_POINTER_CV_HPP__
#define __MOCKITOPP_REMOVE_MEMBER_FUNCTION_POINTER_CV_HPP__

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

      // 0 argument MFP remove const template
      template <typename R, typename C>
      struct remove_member_function_pointer_cv<R (C::*)() const>
         { typedef R (C::*type)(); };

      // 0 argument MFP remove const volatile template
      template <typename R, typename C>
      struct remove_member_function_pointer_cv<R (C::*)() const volatile>
         { typedef R (C::*type)(); };

      // 1 argument MFP remove const template
      template <typename R, typename C, typename A0>
      struct remove_member_function_pointer_cv<R (C::*)(A0) const>
         { typedef R (C::*type)(A0); };

      // 1 argument MFP remove const volatile template
      template <typename R, typename C, typename A0>
      struct remove_member_function_pointer_cv<R (C::*)(A0) const volatile>
         { typedef R (C::*type)(A0); };

      // 2 argument MFP remove const template
      template <typename R, typename C, typename A0, typename A1>
      struct remove_member_function_pointer_cv<R (C::*)(A0, A1) const>
         { typedef R (C::*type)(A0, A1); };

      // 2 argument MFP remove const volatile template
      template <typename R, typename C, typename A0, typename A1>
      struct remove_member_function_pointer_cv<R (C::*)(A0, A1) const volatile>
         { typedef R (C::*type)(A0, A1); };

      // 3 argument MFP remove const template
      template <typename R, typename C, typename A0, typename A1, typename A2>
      struct remove_member_function_pointer_cv<R (C::*)(A0, A1, A2) const>
         { typedef R (C::*type)(A0, A1, A2); };

      // 3 argument MFP remove const volatile template
      template <typename R, typename C, typename A0, typename A1, typename A2>
      struct remove_member_function_pointer_cv<R (C::*)(A0, A1, A2) const volatile>
         { typedef R (C::*type)(A0, A1, A2); };

      // 4 argument MFP remove const template
      template <typename R, typename C, typename A0, typename A1, typename A2, typename A3>
      struct remove_member_function_pointer_cv<R (C::*)(A0, A1, A2, A3) const>
         { typedef R (C::*type)(A0, A1, A2, A3); };

      // 4 argument MFP remove const volatile template
      template <typename R, typename C, typename A0, typename A1, typename A2, typename A3>
      struct remove_member_function_pointer_cv<R (C::*)(A0, A1, A2, A3) const volatile>
         { typedef R (C::*type)(A0, A1, A2, A3); };

      // 5 argument MFP remove const template
      template <typename R, typename C, typename A0, typename A1, typename A2, typename A3, typename A4>
      struct remove_member_function_pointer_cv<R (C::*)(A0, A1, A2, A3, A4) const>
         { typedef R (C::*type)(A0, A1, A2, A3, A4); };

      // 5 argument MFP remove const volatile template
      template <typename R, typename C, typename A0, typename A1, typename A2, typename A3, typename A4>
      struct remove_member_function_pointer_cv<R (C::*)(A0, A1, A2, A3, A4) const volatile>
         { typedef R (C::*type)(A0, A1, A2, A3, A4); };

      // 6 argument MFP remove const template
      template <typename R, typename C, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5>
      struct remove_member_function_pointer_cv<R (C::*)(A0, A1, A2, A3, A4, A5) const>
         { typedef R (C::*type)(A0, A1, A2, A3, A4, A5); };

      // 6 argument MFP remove const volatile template
      template <typename R, typename C, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5>
      struct remove_member_function_pointer_cv<R (C::*)(A0, A1, A2, A3, A4, A5) const volatile>
         { typedef R (C::*type)(A0, A1, A2, A3, A4, A5); };

      // 7 argument MFP remove const template
      template <typename R, typename C, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
      struct remove_member_function_pointer_cv<R (C::*)(A0, A1, A2, A3, A4, A5, A6) const>
         { typedef R (C::*type)(A0, A1, A2, A3, A4, A5, A6); };

      // 7 argument MFP remove const volatile template
      template <typename R, typename C, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
      struct remove_member_function_pointer_cv<R (C::*)(A0, A1, A2, A3, A4, A5, A6) const volatile>
         { typedef R (C::*type)(A0, A1, A2, A3, A4, A5, A6); };

      // 8 argument MFP remove const template
      template <typename R, typename C, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7>
      struct remove_member_function_pointer_cv<R (C::*)(A0, A1, A2, A3, A4, A5, A6, A7) const>
         { typedef R (C::*type)(A0, A1, A2, A3, A4, A5, A6, A7); };

      // 8 argument MFP remove const volatile template
      template <typename R, typename C, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7>
      struct remove_member_function_pointer_cv<R (C::*)(A0, A1, A2, A3, A4, A5, A6, A7) const volatile>
         { typedef R (C::*type)(A0, A1, A2, A3, A4, A5, A6, A7); };

      // 9 argument MFP remove const template
      template <typename R, typename C, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8>
      struct remove_member_function_pointer_cv<R (C::*)(A0, A1, A2, A3, A4, A5, A6, A7, A8) const>
         { typedef R (C::*type)(A0, A1, A2, A3, A4, A5, A6, A7, A8); };

      // 9 argument MFP remove const volatile template
      template <typename R, typename C, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8>
      struct remove_member_function_pointer_cv<R (C::*)(A0, A1, A2, A3, A4, A5, A6, A7, A8) const volatile>
         { typedef R (C::*type)(A0, A1, A2, A3, A4, A5, A6, A7, A8); };

      // 10 argument MFP remove const template
      template <typename R, typename C, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9>
      struct remove_member_function_pointer_cv<R (C::*)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9) const>
         { typedef R (C::*type)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9); };

      // 10 argument MFP remove const volatile template
      template <typename R, typename C, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9>
      struct remove_member_function_pointer_cv<R (C::*)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9) const volatile>
         { typedef R (C::*type)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9); };

   } // namespace detail
} // namespace mockitopp

#endif //__MOCKITOPP_TR1_TYPE_TRAITS_HPP__
