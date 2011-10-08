#include "tpunit++.hpp"
#include <mockitopp/mockitopp.hpp>

using mockitopp::mock_object;
using mockitopp::matcher::equal;

struct test_equal : tpunit::TestFixture
{
   test_equal() : tpunit::TestFixture
   (
      TEST(test_equal::equal_void_ptr),
      TEST(test_equal::equal_prim_char),
      TEST(test_equal::equal_std_string)
   )
   {}

   struct equal_test_interface
   {
      virtual int prim_void_ptr(void*) = 0;
      virtual int prim_char(char) = 0;
   //   virtual int prim_float(std::string) = 0;
      virtual int std_string(std::string) = 0;
   };

   void equal_void_ptr()
   {
      mock_object<equal_test_interface> mock;
      mock(&equal_test_interface::prim_void_ptr).when(equal<void*>(0)).thenReturn(0);
      void* void_ptr = new int;
      mock(&equal_test_interface::prim_void_ptr).when(equal<void*>(void_ptr)).thenReturn(1);
      equal_test_interface& obj = mock.getInstance();

      ASSERT_EQUAL(0, obj.prim_void_ptr(0));
      ASSERT_EQUAL(1, obj.prim_void_ptr(void_ptr));
      ASSERT_THROW(obj.prim_void_ptr(new int), mockitopp::partial_implementation_exception);
   }

   void equal_prim_char()
   {
      mock_object<equal_test_interface> mock;
      mock(&equal_test_interface::prim_char).when(equal<char>(' ')).thenReturn(32);
      mock(&equal_test_interface::prim_char).when(equal<char>('0')).thenReturn(48);
      mock(&equal_test_interface::prim_char).when(equal<char>('A')).thenReturn(65);
      equal_test_interface& obj = mock.getInstance();

      ASSERT_EQUAL(32, obj.prim_char(' '));
      ASSERT_EQUAL(48, obj.prim_char('0'));
      ASSERT_EQUAL(65, obj.prim_char('A'));
      ASSERT_THROW(obj.prim_char('@'), mockitopp::partial_implementation_exception);
      ASSERT_THROW(obj.prim_char('9'), mockitopp::partial_implementation_exception);
      ASSERT_THROW(obj.prim_char('Z'), mockitopp::partial_implementation_exception);
   }

   void equal_std_string()
   {
      mock_object<equal_test_interface> mock;
      mock(&equal_test_interface::std_string).when(equal("foo")).thenReturn(0);
      mock(&equal_test_interface::std_string).when(equal("w00t")).thenReturn(1);
      mock(&equal_test_interface::std_string).when(equal("hello")).thenReturn(2);
      equal_test_interface& obj = mock.getInstance();

      ASSERT_EQUAL(0, obj.std_string("foo"));
      ASSERT_EQUAL(1, obj.std_string("w00t"));
      ASSERT_EQUAL(2, obj.std_string("hello"));
      ASSERT_THROW(obj.std_string("ABCDEFXYZ"), mockitopp::partial_implementation_exception);
      ASSERT_THROW(obj.std_string("124356789"), mockitopp::partial_implementation_exception);
      ASSERT_THROW(obj.std_string("!@#$%^&*("), mockitopp::partial_implementation_exception);
   }
} __test_equal;
