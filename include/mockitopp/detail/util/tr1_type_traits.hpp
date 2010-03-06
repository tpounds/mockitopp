#ifndef __MOCKITOPP_TR1_TYPE_TRAITS_HPP__
#define __MOCKITOPP_TR1_TYPE_TRAITS_HPP__

namespace mockitopp
{
   namespace detail
   {
      /** 
       * Simple subset adaptation of tr1 type_traits
       * for internal mockitopp use.
       *
       * @author Trevor Pounds
       * @see http://www.boost.org/doc/libs/release/libs/type_traits/
       */
      namespace tr1
      {
         #ifdef _MSC_VER
            // C4181: qualifier applied to reference type
            #pragma warning(disable:4181)
         #endif

         // std::tr1::add_const
         template <typename T> struct add_const { typedef const T type; };
         template <typename T> struct add_const<const T> { typedef const T type; };

         #ifdef _MSC_VER
            #pragma warning(default:4181)
         #endif

         // std::tr1::remove_const
         template <typename T> struct remove_const { typedef T type; };
         template <typename T> struct remove_const<const T> { typedef T type; };

         // std::tr1::add_reference
         template <typename T> struct add_reference { typedef T type; };
         template <typename T> struct add_reference<T&> { typedef T& type; };

         // std::tr1::remove_reference
         template <typename T> struct remove_reference { typedef T type; };
         template <typename T> struct remove_reference<T&> { typedef T type; };
      } // namespace tr1
   } // namespace detail
} // namespace mockitopp

#endif //__MOCKITOPP_TR1_TYPE_TRAITS_HPP__
