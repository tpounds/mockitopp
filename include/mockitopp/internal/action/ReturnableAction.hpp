#ifndef __MOCKITOPP_RETURNABLE_ACTION_HPP__
#define __MOCKITOPP_RETURNABLE_ACTION_HPP__

#include <mockitopp/internal/action/Action.hpp>

namespace mockitopp
{
   namespace detail
   {
      template <typename R>
      struct ReturnableAction : public Action<R>
      {
         R _returnable;

         ReturnableAction(const R& returnable)
            : _returnable(returnable)
            {}

         R execute()
            { return _returnable; }
      };

      template <>
      struct ReturnableAction<void> : public Action<void>
      {
         void execute()
            {}
      };
   } // namespace detail
} // namespace mockitopp

#endif //__MOCKITOPP_RETURNABLE_ACTION_HPP__
