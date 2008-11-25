#ifndef __MOCKITOPP_STUB_IMPL_HPP__
#define __MOCKITOPP_STUB_IMPL_HPP__

#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>

#include <mockitopp/detail/stubbing/OngoingStubbing.hpp>

namespace mockitopp
{
   namespace detail
   {
      template <int OFFSET, typename T> struct StubImpl;

      #define DEFINE_STUB_IMPL(ZZZ, NNN, TTT) \
         template <int OFFSET, typename R, typename C BOOST_PP_COMMA_IF(NNN) BOOST_PP_ENUM_PARAMS(NNN, typename A)> \
         struct StubImpl<OFFSET, R (C::*)(BOOST_PP_ENUM_PARAMS(NNN, A))> \
         { \
            void* __PAD_FOR_MOCK_vptr; \
            OngoingStubbing<R (C::*)(BOOST_PP_ENUM_PARAMS(NNN, A))>* \
               __PAD_FOR_MOCK_spys[MAX_VIRTUAL_FUNCTIONS]; \
         \
            R invoke(BOOST_PP_ENUM_BINARY_PARAMS(NNN, A, a)) \
               { return __PAD_FOR_MOCK_spys[OFFSET]->invoke(BOOST_PP_ENUM_PARAMS(NNN, a)); } \
         };

      BOOST_PP_REPEAT(MAX_VIRTUAL_FUNCTION_ARITY, DEFINE_STUB_IMPL, ~)

      #undef DEFINE_STUB_IMPL

   } // namespace detail
} // namespace mockitopp

#endif //__MOCKITOPP_STUB_IMPL_HPP__
