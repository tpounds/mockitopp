#include "tpunit++.hpp"
#include <mockitopp/mockitopp.hpp>

using mockitopp::mock_object;
using mockitopp::matcher::equal;
using mockitopp::matcher::is_not;
using mockitopp::matcher::null;

struct test_is_not : tpunit::TestFixture
{
   test_is_not() : tpunit::TestFixture
   (
      TEST(test_is_not::is_not_null_ptr),
      TEST(test_is_not::is_not_is_not_equal_ptr)
   )
   {}

   struct is_not_test_interface
   {
      virtual std::string prim_void_ptr(void*) = 0;
   //   virtual std::string std_string(std::string) = 0;
   };

   void is_not_null_ptr()
   {
      mock_object<is_not_test_interface> mock;
      mock(&is_not_test_interface::prim_void_ptr).when(is_not(null<void*>())).thenReturn("void* != NULL");
      is_not_test_interface& obj = mock.getInstance();

      ASSERT_EQUAL("void* != NULL", obj.prim_void_ptr(new char));
      ASSERT_EQUAL("void* != NULL", obj.prim_void_ptr(new double));
      ASSERT_THROW(obj.prim_void_ptr(0), mockitopp::partial_implementation_exception);
   }

   void is_not_is_not_equal_ptr()
   {
      mock_object<is_not_test_interface> mock;
      void* void_ptr = new char;
      mock(&is_not_test_interface::prim_void_ptr).when(is_not(is_not(equal<void*>(void_ptr)))).thenReturn("void* == new char");
      is_not_test_interface& obj = mock.getInstance();

      ASSERT_EQUAL("void* == new char", obj.prim_void_ptr(void_ptr));
      ASSERT_THROW(obj.prim_void_ptr(0), mockitopp::partial_implementation_exception);
   }
} __test_is_not;
