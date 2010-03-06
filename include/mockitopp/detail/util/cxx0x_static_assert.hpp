#ifndef __MOCKITOPP_CXX0X_STATIC_ASSERT_HPP__
#define __MOCKITOPP_CXX0X_STATIC_ASSERT_HPP__

namespace mockitopp
{
   namespace detail
   {
      /**
       * An emulation of the C++0x static_assert macro that can be
       * used to force a compile time error in older compilers.
       *
       * @author Trevor Pounds
       */
      template <bool E> struct static_assert_impl { typedef bool type; };
      template <> struct static_assert_impl<false> { };

      #define mockitopp_static_assert(constant_expression) \
         typedef typename ::mockitopp::detail::static_assert_impl<constant_expression>::type MOCKITOPP_STATIC_ASSERT_TYPE;
   } // namespace detail
} // namespace mockitopp

#endif //__MOCKITOPP_CXX0X_STATIC_ASSERT_HPP__
