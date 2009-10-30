#include <gtest/gtest.h>
#include <mockitopp/mockitopp.hpp>

using mockitopp::mock_object;
using mockitopp::matcher::any;

struct any_test_interface
{
   virtual int prim_int_ptr(int*) = 0;
   virtual int prim_char(char) = 0;
   virtual int prim_float(float) = 0;
   virtual int std_string(std::string) = 0;
};

TEST(test_any, prim_int_ptr)
{
   mock_object<any_test_interface> mock;
   mock(&any_test_interface::prim_int_ptr).when(any<int*>()).thenReturn(1234);
   any_test_interface& obj = mock.getInstance();

   int* int_ptr = new int;
   ASSERT_EQ(1234, obj.prim_int_ptr(int_ptr));
   ASSERT_EQ(1234, obj.prim_int_ptr(new int));
   ASSERT_EQ(1234, obj.prim_int_ptr(new int));
}

TEST(test_any, prim_char)
{
   mock_object<any_test_interface> mock;
   mock(&any_test_interface::prim_char).when(any<char>()).thenReturn(1234);
   any_test_interface& obj = mock.getInstance();

   ASSERT_EQ(1234, obj.prim_char('A'));
   ASSERT_EQ(1234, obj.prim_char('Z'));
   ASSERT_EQ(1234, obj.prim_char('$'));
   ASSERT_EQ(1234, obj.prim_char(' '));
}

TEST(test_any, prim_float)
{
   mock_object<any_test_interface> mock;
   mock(&any_test_interface::prim_float).when(any<float>()).thenReturn(1234);
   any_test_interface& obj = mock.getInstance();

   ASSERT_EQ(1234, obj.prim_float(3.14));
   ASSERT_EQ(1234, obj.prim_float(1.00f));
   ASSERT_EQ(1234, obj.prim_float(5.0));
   ASSERT_EQ(1234, obj.prim_float(-0.1234));
}

TEST(test_any, std_string)
{
   mock_object<any_test_interface> mock;
   mock(&any_test_interface::std_string).when(any<std::string>()).thenReturn(1234);
   any_test_interface& obj = mock.getInstance();

   ASSERT_EQ(1234, obj.std_string("foo"));
   ASSERT_EQ(1234, obj.std_string("w00t"));
   ASSERT_EQ(1234, obj.std_string("hello"));
}
