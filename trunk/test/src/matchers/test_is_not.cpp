#include <gtest/gtest.h>
#include <mockitopp/MockObject.hpp>

using mockitopp::MockObject;
using mockitopp::matcher::equal;
using mockitopp::matcher::is_not;
using mockitopp::matcher::null;

struct is_not_test_interface
{
   virtual std::string prim_void_ptr(void*) = 0;
//   virtual std::string std_string(std::string) = 0;
};

TEST(test_is_not, is_not_null_ptr)
{
   MockObject<is_not_test_interface> mock;
   mock(&is_not_test_interface::prim_void_ptr).when(is_not(null<void*>())).thenReturn("void* != NULL");
   is_not_test_interface& obj = mock.getInstance();

   ASSERT_EQ("void* != NULL", obj.prim_void_ptr(new char));
   ASSERT_EQ("void* != NULL", obj.prim_void_ptr(new double));
   ASSERT_THROW(obj.prim_void_ptr(0), mockitopp::partial_implementation_exception);
}

TEST(test_is_not, is_not_is_not_equal_ptr)
{
   MockObject<is_not_test_interface> mock;
   void* void_ptr = new char;
   mock(&is_not_test_interface::prim_void_ptr).when(is_not(is_not(equal(void_ptr)))).thenReturn("void* == new char");
   is_not_test_interface& obj = mock.getInstance();

   ASSERT_EQ("void* == new char", obj.prim_void_ptr(void_ptr));
   ASSERT_THROW(obj.prim_void_ptr(0), mockitopp::partial_implementation_exception);
}
