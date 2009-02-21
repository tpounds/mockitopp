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
         // tr1:remove_const
         template <typename T> struct remove_const { typedef T type; };
         template <typename T> struct remove_const<const T> { typedef T type; };

         // tr1:remove_refernce
         template <typename T> struct remove_reference { typedef T type; };
         template <typename T> struct remove_reference<T&> { typedef T type; };
      } // namespace tr1
   } // namespace detail
} // namespace mockitopp

#endif //__MOCKITOPP_TR1_TYPE_TRAITS_HPP__
