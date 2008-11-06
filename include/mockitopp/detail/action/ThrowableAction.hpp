#ifndef __MOCKITOPP_THROWABLE_ACTION_HPP__
#define __MOCKITOPP_THROWABLE_ACTION_HPP__

#include <mockitopp/detail/action/Action.hpp>

namespace mockitopp
{
   namespace detail
   {
      template <typename R, typename T>
      struct ThrowableAction : public Action<R>
      {
         T _throwable;

         ThrowableAction(const T& throwable)
            : _throwable(throwable)
            {}

         R execute()
            { throw _throwable; }
      };
   } // namespace detail
} // namespace mockitopp

#endif //__MOCKITOPP_THROWABLE_ACTION_HPP__
