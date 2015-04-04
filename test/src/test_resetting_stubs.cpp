#include "tpunit++.hpp"
#include <mockitopp/mockitopp.hpp>

struct test_resetting_stubs : tpunit::TestFixture
{
   test_resetting_stubs() : tpunit::TestFixture
   (
      TEST(test_resetting_stubs::reset_with_stubs),
      TEST(test_resetting_stubs::reset_with_no_stubs),
      TEST(test_resetting_stubs::add_stub_after_reset)
   )
   {}

   struct interface
   {
      virtual int foo() = 0;
   };

   void reset_with_stubs()
   {
      mockitopp::mock_object<interface> mock;
      mock(&interface::foo).when().thenReturn(0)
                                   .thenReturn(1)
                                   .thenReturn(2);
      mock.reset(&interface::foo);
      ASSERT_THROW(mock.getInstance().foo(), mockitopp::missing_implementation_exception);
   }

   void reset_with_no_stubs()
   {
      mockitopp::mock_object<interface> mock;
      mock.reset(&interface::foo);
      ASSERT_THROW(mock.getInstance().foo(), mockitopp::missing_implementation_exception);
   }

   void add_stub_after_reset()
   {
      mockitopp::mock_object<interface> mock;
      mock(&interface::foo).when().thenReturn(0);
      mock.reset(&interface::foo);
      mock(&interface::foo).when().thenReturn(1);
      ASSERT_EQUAL(1, mock.getInstance().foo());
   }

} __test_resetting_stubs;

struct test_resetting_stubs_with_args : tpunit::TestFixture
{
   test_resetting_stubs_with_args() : tpunit::TestFixture
   (
      TEST(test_resetting_stubs_with_args::reset_with_stubs),
      TEST(test_resetting_stubs_with_args::reset_with_no_stubs),
      TEST(test_resetting_stubs_with_args::add_stub_after_reset),
      TEST(test_resetting_stubs_with_args::add_stub_after_reset_iteratively)
   )
   {}

   struct interface
   {
      virtual int foo(int) = 0;
   };

   void reset_with_stubs()
   {
      mockitopp::mock_object<interface> mock;
      mock(&interface::foo).when(0).thenReturn(0)
                                   .thenReturn(1)
                                   .thenReturn(2);
      mock(&interface::foo).when(0).reset();
      ASSERT_THROW(mock.getInstance().foo(0), mockitopp::partial_implementation_exception);
   }

   void reset_with_other_arg_stubs()
   {
      mockitopp::mock_object<interface> mock;
      mock(&interface::foo).when(0).thenReturn(0);
      mock(&interface::foo).when(1).thenReturn(1);
      mock(&interface::foo).when(0).reset();
      ASSERT_EQUAL(1, mock.getInstance().foo(1));
   }

   void reset_with_no_stubs()
   {
      mockitopp::mock_object<interface> mock;
      mock(&interface::foo).when(0).reset();
      ASSERT_THROW(mock.getInstance().foo(0), mockitopp::partial_implementation_exception);
   }

   void add_stub_after_reset()
   {
      mockitopp::mock_object<interface> mock;
      mock(&interface::foo).when(0).thenReturn(0);
      mock(&interface::foo).when(0).reset();
      mock(&interface::foo).when(0).thenReturn(1);
      ASSERT_EQUAL(1, mock.getInstance().foo(0));
   }

   void add_stub_after_reset_iteratively()
   {
      mockitopp::mock_object<interface> mock;
      mock(&interface::foo).when(0).thenReturn(0)
                                   .reset()
                                   .thenReturn(1);
      ASSERT_EQUAL(1, mock.getInstance().foo(0));
   }

} __test_resetting_stubs_with_args;
