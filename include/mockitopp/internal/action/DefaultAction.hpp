#ifndef __MOCKITOPP_DEFAULT_ACTION_HPP__
#define __MOCKITOPP_DEFAULT_ACTION_HPP__

#include  <boost/type_traits/is_reference.hpp>
#include  <boost/utility/enable_if.hpp>

#include <mockitopp/internal/action/Action.hpp>

namespace mockitopp
{
   namespace detail
   {
      template <typename R, typename ENABLE = void> struct DefaultAction;

      template <typename R>
      struct DefaultAction<R, typename boost::disable_if<boost::is_reference<R> >::type> : public Action<R>
      {
         R _returnable;

         DefaultAction()
            : _returnable(*(new R()))
            {}

         ~DefaultAction()
            { delete &_returnable; }

         R execute()
            { return _returnable; }
      };

      template <typename R>
      struct DefaultAction<R, typename boost::enable_if<boost::is_reference<R> >::type> : public Action<R>
      {
         R _returnable;

         DefaultAction()
            // XXX: this is kind of hacky but works as needed
            : _returnable(reinterpret_cast<R>(*(new char())))
            {}

         ~DefaultAction()
            { delete &_returnable; }

         R execute()
            { return _returnable; }
      };

      template <>
      struct DefaultAction<void> : public Action<void>
      {
         void execute()
            {}
      };
   } // namespace detail
} // namespace mockitopp

#endif //__MOCKITOPP_DEFAULT_ACTION_HPP__
