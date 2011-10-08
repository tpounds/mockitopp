#include "tpunit++.hpp"
#include <mockitopp/mockitopp.hpp>

using mockitopp::mock_object;
using mockitopp::matcher::any;

struct test_any : tpunit::TestFixture
{
   test_any() : tpunit::TestFixture
   (
      TEST(test_any::any_int_ptr),
      TEST(test_any::any_char),
      TEST(test_any::any_float),
      TEST(test_any::any_std_string)
   )
   {}

   struct any_test_interface
   {
      virtual int prim_int_ptr(int*) = 0;
      virtual int prim_char(char) = 0;
      virtual int prim_float(float) = 0;
      virtual int std_string(std::string) = 0;
   };

   void any_int_ptr()
   {
      mock_object<any_test_interface> mock;
      mock(&any_test_interface::prim_int_ptr).when(any<int*>()).thenReturn(1234);
      any_test_interface& obj = mock.getInstance();

     int* int_ptr = new int;
      ASSERT_EQUAL(1234, obj.prim_int_ptr(int_ptr));
      ASSERT_EQUAL(1234, obj.prim_int_ptr(new int));
      ASSERT_EQUAL(1234, obj.prim_int_ptr(new int));
   }

   void any_char()
   {
      mock_object<any_test_interface> mock;
      mock(&any_test_interface::prim_char).when(any<char>()).thenReturn(1234);
      any_test_interface& obj = mock.getInstance();

      ASSERT_EQUAL(1234, obj.prim_char('A'));
      ASSERT_EQUAL(1234, obj.prim_char('Z'));
      ASSERT_EQUAL(1234, obj.prim_char('$'));
      ASSERT_EQUAL(1234, obj.prim_char(' '));
   }

   void any_float()
   {
      mock_object<any_test_interface> mock;
      mock(&any_test_interface::prim_float).when(any<float>()).thenReturn(1234);
      any_test_interface& obj = mock.getInstance();

      ASSERT_EQUAL(1234, obj.prim_float(3.14));
      ASSERT_EQUAL(1234, obj.prim_float(1.00f));
      ASSERT_EQUAL(1234, obj.prim_float(5.0));
      ASSERT_EQUAL(1234, obj.prim_float(-0.1234));
   }

   void any_std_string()
   {
      mock_object<any_test_interface> mock;
      mock(&any_test_interface::std_string).when(any<std::string>()).thenReturn(1234);
      any_test_interface& obj = mock.getInstance();

      ASSERT_EQUAL(1234, obj.std_string("foo"));
      ASSERT_EQUAL(1234, obj.std_string("w00t"));
      ASSERT_EQUAL(1234, obj.std_string("hello"));
   }
} __test_any;
