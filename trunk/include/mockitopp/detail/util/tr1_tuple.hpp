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
         struct tuple_null_type
         {
            bool operator== (const tuple_null_type&) const { return true; }
            bool operator!= (const tuple_null_type&) const { return false; }
            bool operator<  (const tuple_null_type&) const { return false; }
            bool operator<= (const tuple_null_type&) const { return true; }
            bool operator>  (const tuple_null_type&) const { return false; }
            bool operator>= (const tuple_null_type&) const { return true; }
         };

         template <typename H, typename T>
         struct tuple_cons
         {
            typename remove_const<typename remove_reference<H>::type>::type head;
            typename remove_const<typename remove_reference<T>::type>::type tail;

            tuple_cons(const H& head, const T& tail)
               : head(head)
               , tail(tail)
               {}
         };

         // TODO: fix comparison ops?

         template <typename L0, typename L1, typename R0, typename R1>
         bool operator== (const tuple_cons<L0, L1>& lhs, const tuple_cons<R0, R1>& rhs)
            { return (lhs.head == rhs.head) && (lhs.tail == rhs.tail); }

         template <typename L0, typename L1, typename R0, typename R1>
         bool operator!= (const tuple_cons<L0, L1>& lhs, const tuple_cons<R0, R1>& rhs)
            { return !(lhs == rhs); }

         template <typename L0, typename L1, typename R0, typename R1>
         bool operator< (const tuple_cons<L0, L1>& lhs, const tuple_cons<R0, R1>& rhs)
            { return (lhs.head < rhs.head) || (lhs.tail < rhs.tail); }

         template <typename L0, typename L1, typename R0, typename R1>
         bool operator<= (const tuple_cons<L0, L1>& lhs, const tuple_cons<R0, R1>& rhs)
            { return (lhs == rhs) || (lhs < rhs); }

         template <typename L0, typename L1, typename R0, typename R1>
         bool operator> (const tuple_cons<L0, L1>& lhs, const tuple_cons<R0, R1>& rhs)
            { return (lhs.head > rhs.head) && (lhs.tail > rhs.tail); }

         template <typename L0, typename L1, typename R0, typename R1>
         bool operator>= (const tuple_cons<L0, L1>& lhs, const tuple_cons<R0, R1>& rhs)
            { return (lhs == rhs) || (lhs > rhs); }

         // 10 element template
         template <typename T0 = tuple_null_type, typename T1 = tuple_null_type, typename T2 = tuple_null_type, typename T3 = tuple_null_type, typename T4 = tuple_null_type, typename T5 = tuple_null_type, typename T6 = tuple_null_type, typename T7 = tuple_null_type, typename T8 = tuple_null_type, typename T9 = tuple_null_type>
         struct tuple : tuple_cons<T0, tuple<T1, T2, T3, T4, T5, T6, T7, T8, T9, tuple_null_type> >
         {
            tuple(const T0 & t0, const T1 & t1, const T2 & t2, const T3 & t3, const T4 & t4, const T5 & t5, const T6 & t6, const T7 & t7, const T8 & t8, const T9 & t9)
               : tuple_cons<T0, tuple<T1, T2, T3, T4, T5, T6, T7, T8, T9, tuple_null_type> >
                  (t0, tuple<T1, T2, T3, T4, T5, T6, T7, T8, T9, tuple_null_type>
                     (t1, t2, t3, t4, t5, t6, t7, t8, t9))
               {}
         };

         // 1 element template
         template <typename T0>
         struct tuple<T0 , tuple_null_type , tuple_null_type , tuple_null_type , tuple_null_type , tuple_null_type , tuple_null_type , tuple_null_type , tuple_null_type , tuple_null_type>
            : tuple_cons<T0, tuple<> >
         {
            tuple(const T0 & t0)
               : tuple_cons<T0, tuple<> >
                  (t0, tuple<>
                     ())
               {}
         };

         // 2 element template
         template <typename T0, typename T1>
         struct tuple<T0, T1 , tuple_null_type , tuple_null_type , tuple_null_type , tuple_null_type , tuple_null_type , tuple_null_type , tuple_null_type , tuple_null_type>
            : tuple_cons<T0, tuple<T1> >
         {
            tuple(const T0 & t0, const T1 & t1)
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
            tuple(const T0 & t0, const T1 & t1, const T2 & t2)
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
            tuple(const T0 & t0, const T1 & t1, const T2 & t2, const T3 & t3)
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
            tuple(const T0 & t0, const T1 & t1, const T2 & t2, const T3 & t3, const T4 & t4)
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
            tuple(const T0 & t0, const T1 & t1, const T2 & t2, const T3 & t3, const T4 & t4, const T5 & t5)
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
            tuple(const T0 & t0, const T1 & t1, const T2 & t2, const T3 & t3, const T4 & t4, const T5 & t5, const T6 & t6)
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
            tuple(const T0 & t0, const T1 & t1, const T2 & t2, const T3 & t3, const T4 & t4, const T5 & t5, const T6 & t6, const T7 & t7)
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
            tuple(const T0 & t0, const T1 & t1, const T2 & t2, const T3 & t3, const T4 & t4, const T5 & t5, const T6 & t6, const T7 & t7, const T8 & t8)
               : tuple_cons<T0, tuple<T1, T2, T3, T4, T5, T6, T7, T8> >
                  (t0, tuple<T1, T2, T3, T4, T5, T6, T7, T8>
                     (t1, t2, t3, t4, t5, t6, t7, t8))
               {}
         };



         // 0 element template
         template <>
         struct tuple< tuple_null_type ,  tuple_null_type ,  tuple_null_type ,  tuple_null_type ,  tuple_null_type ,  tuple_null_type ,  tuple_null_type ,  tuple_null_type ,  tuple_null_type ,  tuple_null_type >
            : tuple_cons<tuple_null_type, tuple_cons<tuple_null_type, tuple_null_type> >
         {
            tuple()
               : tuple_cons<tuple_null_type, tuple_cons<tuple_null_type, tuple_null_type> >
                  (tuple_null_type(), tuple_cons<tuple_null_type, tuple_null_type>
                     (tuple_null_type(), tuple_null_type()))
            {}
         };
      } // namespace tr1
   } // namespace detail
} // namespace mockitopp

#endif //__MOCKITOPP_TR1_TUPLE_HPP__
