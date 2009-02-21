#ifndef __MOCKITOPP_TR1_TUPLE_HPP__
#define __MOCKITOPP_TR1_TUPLE_HPP__

// TODO: develop independent impl of tr1 tuple...too lazy for now
#include <boost/tuple/tuple.hpp>
#include <boost/tuple/tuple_comparison.hpp>

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
         using boost::tuple;
//         #define boost::tuple tuple
      } // namespace tr1
   } // namespace detail
} // namespace mockitopp

#endif //__MOCKITOPP_TR1_TUPLE_HPP__
