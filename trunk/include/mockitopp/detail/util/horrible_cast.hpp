#ifndef __MOCKITOPP_HORRIBLE_CAST_HPP__
#define __MOCKITOPP_HORRIBLE_CAST_HPP__

namespace mockitopp
{
   namespace detail
   {
      /**
       * terrible cast using a union of two
       * possibly incompatible data types...USE WITH CAUTION!
       *
       * @author Trevor Pounds
       */
      template <typename T, typename F>
      T horrible_cast(F from)
      {
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
