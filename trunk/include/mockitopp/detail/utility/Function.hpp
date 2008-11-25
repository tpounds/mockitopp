#ifndef __MOCKITOPP_FUNCTION_HPP__
#define __MOCKITOPP_FUNCTION_HPP__

#include <boost/preprocessor/repetition/repeat.hpp>

namespace mockitopp
{
   namespace detail
   {
      /**
       * @author Trevor Pounds
       */
      struct Function
      {
         template <typename T>
         static int getOffset(T ptr2member)
         {
            Function f;
            return (f.*reinterpret_cast<int (Function::*)()>(ptr2member))();
         }

         #define DEFINE_OFFSET_LOOKUP_FUNCTION(ZZZ, NNN, TTT) \
            virtual int offset##NNN() { return NNN; }

         BOOST_PP_REPEAT(MAX_VIRTUAL_FUNCTIONS, DEFINE_OFFSET_LOOKUP_FUNCTION, ~)

         #undef DEFINE_OFFSET_LOOKUP_FUNCTION
      };

   } // namespace detail
} // namespace mockitopp

#endif //__MOCKITOPP_FUNCTION_HPP__
