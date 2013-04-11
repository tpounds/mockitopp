#ifndef __MOCKITOPP_TR1_TUPLE_HPP__
#define __MOCKITOPP_TR1_TUPLE_HPP__

#include <mockitopp/detail/util/tr1_type_traits.hpp>

/** 
 * partial implementation of tr1 <tuple>
 * for internal mockitopp use
 *
 * unsupported functionality:
 *
 *   get
 *   make_tuple
 *   tie
 *   tuple_element
 *   tuple_size
 */
namespace mockitopp
{
   namespace detail
   {
      namespace tr1
      {
         struct tuple_null_type {};

         template <typename H, typename T>
         struct tuple_cons
         {
            H head_;
            T tail_;

            tuple_cons(typename add_reference<typename add_const<H>::type>::type head,
                       typename add_reference<typename add_const<T>::type>::type tail)
               : head_(head)
               , tail_(tail)
               {}
         };

         // 10 element template
         template <typename T0 = tuple_null_type, typename T1 = tuple_null_type, typename T2 = tuple_null_type, typename T3 = tuple_null_type, typename T4 = tuple_null_type, typename T5 = tuple_null_type, typename T6 = tuple_null_type, typename T7 = tuple_null_type, typename T8 = tuple_null_type, typename T9 = tuple_null_type>
         struct tuple : tuple_cons<T0, tuple<T1, T2, T3, T4, T5, T6, T7, T8, T9, tuple_null_type> >
         {
            tuple(typename add_reference<typename add_const<T0 >::type>::type t0, typename add_reference<typename add_const<T1 >::type>::type t1, typename add_reference<typename add_const<T2 >::type>::type t2, typename add_reference<typename add_const<T3 >::type>::type t3, typename add_reference<typename add_const<T4 >::type>::type t4, typename add_reference<typename add_const<T5 >::type>::type t5, typename add_reference<typename add_const<T6 >::type>::type t6, typename add_reference<typename add_const<T7 >::type>::type t7, typename add_reference<typename add_const<T8 >::type>::type t8, typename add_reference<typename add_const<T9 >::type>::type t9)
               : tuple_cons<T0, tuple<T1, T2, T3, T4, T5, T6, T7, T8, T9, tuple_null_type> >
                  (t0, tuple<T1, T2, T3, T4, T5, T6, T7, T8, T9, tuple_null_type>
                     (t1, t2, t3, t4, t5, t6, t7, t8, t9))
               {}
         };

         // 2 element template
         template <typename T0, typename T1>
         struct tuple<T0, T1 , tuple_null_type , tuple_null_type , tuple_null_type , tuple_null_type , tuple_null_type , tuple_null_type , tuple_null_type , tuple_null_type>
            : tuple_cons<T0, tuple<T1> >
         {
            tuple(typename add_reference<typename add_const<T0 >::type>::type t0, typename add_reference<typename add_const<T1 >::type>::type t1)
               : tuple_cons<T0, tuple<T1> >
                  (t0, tuple<T1>
                     (t1))
               {}
         };

         // 3 element template
         template <typename T0, typename T1, typename T2>
         struct tuple<T0, T1, T2 , tuple_null_type , tuple_null_type , tuple_null_type , tuple_null_type , tuple_null_type , tuple_null_type , tuple_null_type>
            : tuple_cons<T0, tuple<T1, T2> >
         {
            tuple(typename add_reference<typename add_const<T0 >::type>::type t0, typename add_reference<typename add_const<T1 >::type>::type t1, typename add_reference<typename add_const<T2 >::type>::type t2)
               : tuple_cons<T0, tuple<T1, T2> >
                  (t0, tuple<T1, T2>
                     (t1, t2))
               {}
         };

         // 4 element template
         template <typename T0, typename T1, typename T2, typename T3>
         struct tuple<T0, T1, T2, T3 , tuple_null_type , tuple_null_type , tuple_null_type , tuple_null_type , tuple_null_type , tuple_null_type>
            : tuple_cons<T0, tuple<T1, T2, T3> >
         {
            tuple(typename add_reference<typename add_const<T0 >::type>::type t0, typename add_reference<typename add_const<T1 >::type>::type t1, typename add_reference<typename add_const<T2 >::type>::type t2, typename add_reference<typename add_const<T3 >::type>::type t3)
               : tuple_cons<T0, tuple<T1, T2, T3> >
                  (t0, tuple<T1, T2, T3>
                     (t1, t2, t3))
               {}
         };

         // 5 element template
         template <typename T0, typename T1, typename T2, typename T3, typename T4>
         struct tuple<T0, T1, T2, T3, T4 , tuple_null_type , tuple_null_type , tuple_null_type , tuple_null_type , tuple_null_type>
            : tuple_cons<T0, tuple<T1, T2, T3, T4> >
         {
            tuple(typename add_reference<typename add_const<T0 >::type>::type t0, typename add_reference<typename add_const<T1 >::type>::type t1, typename add_reference<typename add_const<T2 >::type>::type t2, typename add_reference<typename add_const<T3 >::type>::type t3, typename add_reference<typename add_const<T4 >::type>::type t4)
               : tuple_cons<T0, tuple<T1, T2, T3, T4> >
                  (t0, tuple<T1, T2, T3, T4>
                     (t1, t2, t3, t4))
               {}
         };

         // 6 element template
         template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
         struct tuple<T0, T1, T2, T3, T4, T5 , tuple_null_type , tuple_null_type , tuple_null_type , tuple_null_type>
            : tuple_cons<T0, tuple<T1, T2, T3, T4, T5> >
         {
            tuple(typename add_reference<typename add_const<T0 >::type>::type t0, typename add_reference<typename add_const<T1 >::type>::type t1, typename add_reference<typename add_const<T2 >::type>::type t2, typename add_reference<typename add_const<T3 >::type>::type t3, typename add_reference<typename add_const<T4 >::type>::type t4, typename add_reference<typename add_const<T5 >::type>::type t5)
               : tuple_cons<T0, tuple<T1, T2, T3, T4, T5> >
                  (t0, tuple<T1, T2, T3, T4, T5>
                     (t1, t2, t3, t4, t5))
               {}
         };

         // 7 element template
         template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
         struct tuple<T0, T1, T2, T3, T4, T5, T6 , tuple_null_type , tuple_null_type , tuple_null_type>
            : tuple_cons<T0, tuple<T1, T2, T3, T4, T5, T6> >
         {
            tuple(typename add_reference<typename add_const<T0 >::type>::type t0, typename add_reference<typename add_const<T1 >::type>::type t1, typename add_reference<typename add_const<T2 >::type>::type t2, typename add_reference<typename add_const<T3 >::type>::type t3, typename add_reference<typename add_const<T4 >::type>::type t4, typename add_reference<typename add_const<T5 >::type>::type t5, typename add_reference<typename add_const<T6 >::type>::type t6)
               : tuple_cons<T0, tuple<T1, T2, T3, T4, T5, T6> >
                  (t0, tuple<T1, T2, T3, T4, T5, T6>
                     (t1, t2, t3, t4, t5, t6))
               {}
         };

         // 8 element template
         template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
         struct tuple<T0, T1, T2, T3, T4, T5, T6, T7 , tuple_null_type , tuple_null_type>
            : tuple_cons<T0, tuple<T1, T2, T3, T4, T5, T6, T7> >
         {
            tuple(typename add_reference<typename add_const<T0 >::type>::type t0, typename add_reference<typename add_const<T1 >::type>::type t1, typename add_reference<typename add_const<T2 >::type>::type t2, typename add_reference<typename add_const<T3 >::type>::type t3, typename add_reference<typename add_const<T4 >::type>::type t4, typename add_reference<typename add_const<T5 >::type>::type t5, typename add_reference<typename add_const<T6 >::type>::type t6, typename add_reference<typename add_const<T7 >::type>::type t7)
               : tuple_cons<T0, tuple<T1, T2, T3, T4, T5, T6, T7> >
                  (t0, tuple<T1, T2, T3, T4, T5, T6, T7>
                     (t1, t2, t3, t4, t5, t6, t7))
               {}
         };

         // 9 element template
         template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
         struct tuple<T0, T1, T2, T3, T4, T5, T6, T7, T8 , tuple_null_type>
            : tuple_cons<T0, tuple<T1, T2, T3, T4, T5, T6, T7, T8> >
         {
            tuple(typename add_reference<typename add_const<T0 >::type>::type t0, typename add_reference<typename add_const<T1 >::type>::type t1, typename add_reference<typename add_const<T2 >::type>::type t2, typename add_reference<typename add_const<T3 >::type>::type t3, typename add_reference<typename add_const<T4 >::type>::type t4, typename add_reference<typename add_const<T5 >::type>::type t5, typename add_reference<typename add_const<T6 >::type>::type t6, typename add_reference<typename add_const<T7 >::type>::type t7, typename add_reference<typename add_const<T8 >::type>::type t8)
               : tuple_cons<T0, tuple<T1, T2, T3, T4, T5, T6, T7, T8> >
                  (t0, tuple<T1, T2, T3, T4, T5, T6, T7, T8>
                     (t1, t2, t3, t4, t5, t6, t7, t8))
               {}
         };



         // 1 element template
         template <typename T0>
         struct tuple<T0 , tuple_null_type , tuple_null_type , tuple_null_type , tuple_null_type , tuple_null_type , tuple_null_type , tuple_null_type , tuple_null_type , tuple_null_type>
            : tuple_cons<T0, tuple_null_type>
         {
            tuple(typename add_reference<typename add_const<T0 >::type>::type t0)
               : tuple_cons<T0, tuple_null_type>
                  (t0, tuple_null_type())
            {}
         };

         // 0 element template
         template <>
         struct tuple< tuple_null_type ,  tuple_null_type ,  tuple_null_type ,  tuple_null_type ,  tuple_null_type ,  tuple_null_type ,  tuple_null_type ,  tuple_null_type ,  tuple_null_type ,  tuple_null_type >
            : tuple_cons<tuple_null_type, tuple_null_type>
         {
            tuple()
               : tuple_cons<tuple_null_type, tuple_null_type>
                  (tuple_null_type(), tuple_null_type())
            {}
         };
      } // namespace tr1
   } // namespace detail
} // namespace mockitopp

inline bool operator== (const mockitopp::detail::tr1::tuple_null_type&, const mockitopp::detail::tr1::tuple_null_type&) { return true;  }
inline bool operator!= (const mockitopp::detail::tr1::tuple_null_type&, const mockitopp::detail::tr1::tuple_null_type&) { return false; }
inline bool operator<  (const mockitopp::detail::tr1::tuple_null_type&, const mockitopp::detail::tr1::tuple_null_type&) { return false; }
inline bool operator<= (const mockitopp::detail::tr1::tuple_null_type&, const mockitopp::detail::tr1::tuple_null_type&) { return true;  }
inline bool operator>  (const mockitopp::detail::tr1::tuple_null_type&, const mockitopp::detail::tr1::tuple_null_type&) { return false; }
inline bool operator>= (const mockitopp::detail::tr1::tuple_null_type&, const mockitopp::detail::tr1::tuple_null_type&) { return true;  }

template <typename L0, typename L1, typename R0, typename R1>
inline bool operator== (const mockitopp::detail::tr1::tuple_cons<L0, L1>& lhs, const mockitopp::detail::tr1::tuple_cons<R0, R1>& rhs)
   { return (lhs.head_ == rhs.head_) && (lhs.tail_ == rhs.tail_); }

template <typename L0, typename L1, typename R0, typename R1>
inline bool operator!= (const mockitopp::detail::tr1::tuple_cons<L0, L1>& lhs, const mockitopp::detail::tr1::tuple_cons<R0, R1>& rhs)
   { return !(lhs == rhs); }

template <typename L0, typename L1, typename R0, typename R1>
inline bool operator< (const mockitopp::detail::tr1::tuple_cons<L0, L1>& lhs, const mockitopp::detail::tr1::tuple_cons<R0, R1>& rhs)
   { return (lhs.head_ < rhs.head_) || (lhs.tail_ < rhs.tail_); }

template <typename L0, typename L1, typename R0, typename R1>
inline bool operator<= (const mockitopp::detail::tr1::tuple_cons<L0, L1>& lhs, const mockitopp::detail::tr1::tuple_cons<R0, R1>& rhs)
   { return (lhs == rhs) || (lhs < rhs); }

template <typename L0, typename L1, typename R0, typename R1>
inline bool operator> (const mockitopp::detail::tr1::tuple_cons<L0, L1>& lhs, const mockitopp::detail::tr1::tuple_cons<R0, R1>& rhs)
   { return (lhs.head_ > rhs.head_) && (lhs.tail_ > rhs.tail_); }

template <typename L0, typename L1, typename R0, typename R1>
inline bool operator>= (const mockitopp::detail::tr1::tuple_cons<L0, L1>& lhs, const mockitopp::detail::tr1::tuple_cons<R0, R1>& rhs)
   { return (lhs == rhs) || (lhs > rhs); }

#endif //__MOCKITOPP_TR1_TUPLE_HPP__
