#ifndef __MOCKITOPP_TR1_TYPE_TRAITS_HPP__
#define __MOCKITOPP_TR1_TYPE_TRAITS_HPP__

/** 
 * adaptation of tr1 <type_traits>
 * for internal mockitopp use
 */
namespace mockitopp
{
   namespace detail
   {
      namespace tr1
      {
         // std::tr1::add_const
         template <typename T> struct add_const { typedef const T type; };
         template <typename T> struct add_const<const T> { typedef const T type; };

         // std::tr1::remove_const
         template <typename T> struct remove_const { typedef T type; };
         template <typename T> struct remove_const<const T> { typedef T type; };

         // std::tr1::add_reference
         template <typename T> struct add_reference { typedef T& type; };
         template <typename T> struct add_reference<T&> { typedef T& type; };

         // std::tr1::remove_reference
         template <typename T> struct remove_reference { typedef T type; };
         template <typename T> struct remove_reference<T&> { typedef T type; };
      } // namespace tr1
   } // namespace detail
} // namespace mockitopp

#endif //__MOCKITOPP_TR1_TYPE_TRAITS_HPP__
