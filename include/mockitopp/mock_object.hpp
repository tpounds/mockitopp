#ifndef __MOCKITOPP_MOCK_OBJECT_HPP__
#define __MOCKITOPP_MOCK_OBJECT_HPP__

#include <mockitopp/detail/stubbing/dynamic_object.hpp>

namespace mockitopp
{
   /**
    * provides a base implementation of a mock object
    *
    * @author Trevor Pounds
    */
   template <typename T>
   struct mock_object : protected detail::dynamic_object
   {
      /**
       * returns a mock object of the given abstract base class/interface
       *
       * @return mock object
       */
      T& getInstance()
        { return reinterpret_cast<T&>(*this); }

      /**
       * stub functionality for a given method
       *
       * @param ptr2member method to be stubbed
       */
      template <typename M>
      detail::dynamic_vfunction<typename detail::remove_member_function_pointer_cv<M>::type>& operator() (M ptr2member)
         { return define_function(ptr2member); }
   };
} // namespace mockitopp

#endif //__MOCKITOPP_MOCK_OBJECT_HPP__
