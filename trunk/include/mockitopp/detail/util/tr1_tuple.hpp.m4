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

         // MOCKITOPP_MAX_VIRTUAL_FUNCTION_ARITY element template
         template <M4_ENUM_BINARY_PARAMS(MOCKITOPP_MAX_VIRTUAL_FUNCTION_ARITY, typename T, = tuple_null_type, M4_INTERCEPT)>
         struct tuple : tuple_cons<T0, tuple<M4_ENUM_SHIFTED_PARAMS(eval(MOCKITOPP_MAX_VIRTUAL_FUNCTION_ARITY), T), tuple_null_type> >
         {
            tuple(M4_ENUM_BINARY_PARAMS(MOCKITOPP_MAX_VIRTUAL_FUNCTION_ARITY, typename add_reference<typename add_const<T, >::type>::type t))
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
            tuple(M4_ENUM_BINARY_PARAMS($1, typename add_reference<typename add_const<T, >::type>::type t))
               : tuple_cons<T0, tuple<M4_ENUM_SHIFTED_PARAMS($1, T)> >
                  (t0, tuple<M4_ENUM_SHIFTED_PARAMS($1, T)>
                     (M4_ENUM_SHIFTED_PARAMS($1, t)))
               {}
         };

')dnl
M4_REPEAT_FROM_TO(2, eval(MOCKITOPP_MAX_VIRTUAL_FUNCTION_ARITY), `TUPLE_TEMPLATE')

         // 1 element template
         template <M4_ENUM_PARAMS(1, typename T)>
         struct tuple<M4_ENUM_PARAMS(1, T)M4_REPEAT(eval(MOCKITOPP_MAX_VIRTUAL_FUNCTION_ARITY - 1), `TUPLE_NULL_TYPE_TRAILING_PARAM')>
            : tuple_cons<T0, tuple_null_type>
         {
            tuple(M4_ENUM_BINARY_PARAMS(1, typename add_reference<typename add_const<T, >::type>::type t))
               : tuple_cons<T0, tuple_null_type>
                  (t0, tuple_null_type())
            {}
         };

         // 0 element template
define(`TUPLE_NULL_TYPE_PARAM', `tuple_null_type M4_COMMA_IF(eval(MOCKITOPP_MAX_VIRTUAL_FUNCTION_ARITY-1-$1))')dnl
         template <>
         struct tuple<M4_REPEAT(MOCKITOPP_MAX_VIRTUAL_FUNCTION_ARITY, `TUPLE_NULL_TYPE_PARAM')>
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
