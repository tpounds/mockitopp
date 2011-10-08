#include "tpunit++.hpp"
#include <mockitopp/mockitopp.hpp>

using mockitopp::mock_object;
using mockitopp::matcher::null;

struct test_null : tpunit::TestFixture
{
   test_null() : tpunit::TestFixture
   (
      TEST(test_null::prim_int_ptr),
      TEST(test_null::std_string_ptr),
      TEST(test_null::object_ptr)
   )
   {}

   struct null_test_object {};

   struct null_test_interface
   {
      virtual std::string prim_int_ptr(int*) = 0;
      virtual std::string std_string_ptr(std::string*) = 0;
      virtual std::string object_ptr(null_test_object*) = 0;
   };

   void prim_int_ptr()
   {
      mock_object<null_test_interface> mock;
      mock(&null_test_interface::prim_int_ptr).when(null<int*>()).thenReturn("int* == NULL");
      null_test_interface& obj = mock.getInstance();

      ASSERT_EQUAL("int* == NULL", obj.prim_int_ptr(0));
      ASSERT_THROW(obj.prim_int_ptr(new int), mockitopp::partial_implementation_exception);
   }

   void std_string_ptr()
   {
      mock_object<null_test_interface> mock;
      mock(&null_test_interface::std_string_ptr).when(null<std::string*>()).thenReturn("std::string* == NULL");
      null_test_interface& obj = mock.getInstance();

      ASSERT_EQUAL("std::string* == NULL", obj.std_string_ptr(0));
      ASSERT_THROW(obj.std_string_ptr(new std::string("foo")), mockitopp::partial_implementation_exception);
      ASSERT_THROW(obj.std_string_ptr(new std::string("bar")), mockitopp::partial_implementation_exception);
   }

   void object_ptr()
   {
      mock_object<null_test_interface> mock;
      mock(&null_test_interface::object_ptr).when(null<null_test_object*>()).thenReturn("null_test_obj* == NULL");
      null_test_interface& obj = mock.getInstance();

      ASSERT_EQUAL("null_test_obj* == NULL", obj.object_ptr(0));
      ASSERT_THROW(obj.object_ptr(new null_test_object), mockitopp::partial_implementation_exception);
   }
} __test_null;
