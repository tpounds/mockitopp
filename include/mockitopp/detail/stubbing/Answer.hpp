#ifndef __MOCKITOPP_ANSWER_HPP__
#define __MOCKITOPP_ANSWER_HPP__

namespace mockitopp
{
   namespace detail
   {
      template <typename R>
      struct Answer
      {
         virtual R execute() = 0;

         virtual ~Answer() {}
      };
   } // namespace detail
} // namespace mockitopp

#endif //__MOCKITOPP_ANSWER_HPP__
