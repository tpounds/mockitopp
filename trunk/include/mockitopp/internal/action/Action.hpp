#ifndef __MOCKITOPP_ACTION_HPP__
#define __MOCKITOPP_ACTION_HPP__

namespace mockitopp
{
   namespace detail
   {
      template <typename R>
      struct Action
      {
         virtual R execute() = 0;
      };
   } // namespace detail
} // namespace mockitopp

#endif //__MOCKITOPP_ACTION_HPP__
