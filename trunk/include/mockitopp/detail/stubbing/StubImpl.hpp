#ifndef __MOCKITOPP_STUB_IMPL_HPP__
#define __MOCKITOPP_STUB_IMPL_HPP__

#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>

#include <mockitopp/Configuration.hpp>
#include <mockitopp/detail/stubbing/StubImplData.hpp>

namespace mockitopp
{
   namespace detail
   {
      template <size_t O, typename T> struct StubImpl;

      #define DEFINE_STUB_IMPL(ZZZ, NNN, TTT) \
         template <size_t OFFSET, typename R, typename C BOOST_PP_COMMA_IF(NNN) BOOST_PP_ENUM_PARAMS(NNN, typename A)> \
         struct StubImpl<OFFSET, R (C::*)(BOOST_PP_ENUM_PARAMS(NNN, A))> \
         { \
            typedef R (C::*sig_type)(BOOST_PP_ENUM_PARAMS(NNN, A)); \
            typedef StubImplData<sig_type> stub_data_type; \
         \
            void*           __PAD_FOR_MOCK_vptr; \
            stub_data_type* __PAD_FOR_MOCK_stubs[MAX_VIRTUAL_FUNCTIONS]; \
         \
            R invoke(BOOST_PP_ENUM_BINARY_PARAMS(NNN, A, a)) \
            { \
               stub_data_type* stub = __PAD_FOR_MOCK_stubs[OFFSET]; \
               stub->getCalls()++; \
               return stub->getMatcher().invoke(BOOST_PP_ENUM_PARAMS(NNN, a)); \
            } \
         };

      BOOST_PP_REPEAT(MAX_VIRTUAL_FUNCTION_ARITY, DEFINE_STUB_IMPL, ~)

      #undef DEFINE_STUB_IMPL

   } // namespace detail
} // namespace mockitopp

#endif //__MOCKITOPP_STUB_IMPL_HPP__
