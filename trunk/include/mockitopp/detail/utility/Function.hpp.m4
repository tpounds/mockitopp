#ifndef __MOCKITOPP_FUNCTION_HPP__
#define __MOCKITOPP_FUNCTION_HPP__

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

include(`mockitopp/detail/m4/REPEAT.m4')dnl
define(`DEFINE_OFFSET_LOOKUP_FUNCTION', `        virtual int offset$1() { return $1; }
')dnl
M4_REPEAT(50, `DEFINE_OFFSET_LOOKUP_FUNCTION')dnl
      };

   } // namespace detail
} // namespace mockitopp

#endif //__MOCKITOPP_FUNCTION_HPP__
