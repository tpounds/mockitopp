#ifndef __MOCKITOPP_EXCEPTIONS_HPP__
#define __MOCKITOPP_EXCEPTIONS_HPP__

#include <exception>

namespace mockitopp
{
   #define MOCKITO_EXCEPTION(EEE) struct EEE : public ::std::exception {};

   MOCKITO_EXCEPTION(partial_implementation_exception)
   MOCKITO_EXCEPTION(missing_implementation_exception)

   MOCKITO_EXCEPTION(less_invocations_expected)
   MOCKITO_EXCEPTION(more_invocations_expected)
   MOCKITO_EXCEPTION(zero_invocations_expected)

   #undef MOCKITO_EXCEPTION
} // namespace mockitopp

#endif //__MOCKITOPP_EXCEPTIONS_HPP__
