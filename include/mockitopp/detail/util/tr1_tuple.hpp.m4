#ifndef __MOCKITOPP_TR1_TUPLE_HPP__
#define __MOCKITOPP_TR1_TUPLE_HPP__

#include <mockitopp/detail/util/tr1_type_traits.hpp>

include(`mockitopp/detail/m4/ENUM_BINARY_PARAMS.m4')dnl
include(`mockitopp/detail/m4/ENUM_SHIFTED_PARAMS.m4')dnl
include(`mockitopp/detail/m4/ENUM_PARAMS.m4')dnl
include(`mockitopp/detail/m4/REPEAT.m4')dnl
include(`mockitopp/detail/m4/REPEAT_FROM_TO.m4')dnl
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

         // MOCKITOPP_MAX_VIRTUAL_FUNCTION_ARITY element template
         template <M4_ENUM_BINARY_PARAMS(MOCKITOPP_MAX_VIRTUAL_FUNCTION_ARITY, typename T, = tuple_null_type, M4_INTERCEPT)>
         struct tuple : tuple_cons<T0, tuple<M4_ENUM_SHIFTED_PARAMS(eval(MOCKITOPP_MAX_VIRTUAL_FUNCTION_ARITY), T), tuple_null_type> >
         {
            tuple(M4_ENUM_BINARY_PARAMS(MOCKITOPP_MAX_VIRTUAL_FUNCTION_ARITY, const T, & t))
               : tuple_cons<T0, tuple<M4_ENUM_SHIFTED_PARAMS(eval(MOCKITOPP_MAX_VIRTUAL_FUNCTION_ARITY), T), tuple_null_type> >
                  (t0, tuple<M4_ENUM_SHIFTED_PARAMS(eval(MOCKITOPP_MAX_VIRTUAL_FUNCTION_ARITY), T), tuple_null_type>
                     (M4_ENUM_SHIFTED_PARAMS(eval(MOCKITOPP_MAX_VIRTUAL_FUNCTION_ARITY), t)))
               {}
         };

define(`TUPLE_NULL_TYPE_TRAILING_PARAM', `, tuple_null_type')dnl
define(`TUPLE_TEMPLATE',
`        // $1 element template
         template <M4_ENUM_PARAMS($1, typename T)>
         struct tuple<M4_ENUM_PARAMS($1, T)M4_REPEAT(eval(MOCKITOPP_MAX_VIRTUAL_FUNCTION_ARITY-$1), `TUPLE_NULL_TYPE_TRAILING_PARAM')>
            : tuple_cons<T0, tuple<M4_ENUM_SHIFTED_PARAMS($1, T)> >
         {
            tuple(M4_ENUM_BINARY_PARAMS($1, const T, & t))
               : tuple_cons<T0, tuple<M4_ENUM_SHIFTED_PARAMS($1, T)> >
                  (t0, tuple<M4_ENUM_SHIFTED_PARAMS($1, T)>
                     (M4_ENUM_SHIFTED_PARAMS($1, t)))
               {}
         };

')dnl
M4_REPEAT_FROM_TO(1, eval(MOCKITOPP_MAX_VIRTUAL_FUNCTION_ARITY), `TUPLE_TEMPLATE')

         // 0 element template
define(`TUPLE_NULL_TYPE_PARAM', `tuple_null_type M4_COMMA_IF(eval(MOCKITOPP_MAX_VIRTUAL_FUNCTION_ARITY-1-$1))')dnl
         template <>
         struct tuple<M4_REPEAT(MOCKITOPP_MAX_VIRTUAL_FUNCTION_ARITY, `TUPLE_NULL_TYPE_PARAM')>
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
