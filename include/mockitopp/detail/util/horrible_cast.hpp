#ifndef __MOCKITOPP_HORRIBLE_CAST_HPP__
#define __MOCKITOPP_HORRIBLE_CAST_HPP__

#include <mockitopp/detail/util/cxx0x_static_assert.hpp>

namespace mockitopp
{
   namespace detail
   {
      /**
       * A potentially unsafe cast using a union of two possibly
       * incompatible data types that can be used to completely
       * subvert the compiler's cast system...USE WITH CAUTION!
       *
       * @author Trevor Pounds
       */
      template <typename T, typename F>
      T horrible_cast(F from)
      {
         /**
          * Abort compilation to avoid casting potentially
          * incompatible types due obvious differences in size.
          */
         //mockitopp_static_assert(sizeof(T) == sizeof(F));

         union
         {
            F from;
            T to;
         } u;
         u.from = from;
         return u.to;
      }
   } // namespace detail
} // namespace mockitopp

#endif //__MOCKITOPP_HORRIBLE_CAST_HPP__
