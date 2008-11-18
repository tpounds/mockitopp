#ifndef __MOCKITOPP_FUNCTION_ADDRESS_HPP__
#define __MOCKITOPP_FUNCTION_ADDRESS_HPP__

#include <stddef.h>

#include <boost/preprocessor/repetition/repeat.hpp>

// TODO: add documentation
namespace mockitopp
{
   namespace detail
   {
      /**
       * @author Trevor Pounds
       */
      class FunctionAddress
      {
         private:

            union UnsafeUnion
            {
               void* ptr2void;
               void (UnsafeUnion::*ptr2member)();
            };

         public:

            template <typename T>
            static void* unsafe_cast(T ptr2member)
            {
               UnsafeUnion u;
               u.ptr2member = reinterpret_cast<void (UnsafeUnion::*)()>(ptr2member);
               return u.ptr2void;
            }

            template <typename T>
            static T unsafe_cast(void* ptr2void)
            {
               UnsafeUnion u;
               u.ptr2void = ptr2void;
               return reinterpret_cast<T>(u.ptr2member);
            }

            template <typename T>
            static size_t offset(T ptr2member)
            {
               FunctionAddress fa;
               return (fa.*reinterpret_cast<size_t (FunctionAddress::*)()>(ptr2member))();
            }

            #define DEFINE_OFFSET_HELPER_VIRTUAL_FUNCTION(ZZZ, NNN, TTT) \
               virtual size_t offset##NNN() { return NNN; }

            BOOST_PP_REPEAT(MAX_VIRTUAL_FUNCTIONS, DEFINE_OFFSET_HELPER_VIRTUAL_FUNCTION, ~)

            #undef DEFINE_OFFSET_HELPER_VIRTUAL_FUNCTION
      };

   } // namespace detail
} // namespace mockitopp

#endif //__MOCKITOPP_FUNCTION_ADDRESS_HPP__
