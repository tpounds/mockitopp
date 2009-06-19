#include <gtest/gtest.h>
#include <mockitopp/MockObject.hpp>

using mockitopp::MockObject;

// TODO: fix std::string impl

struct overloaded_interface
{
   virtual int foo() = 0;
   virtual int foo(bool) = 0;
   virtual int foo(char) = 0;
//   virtual int foo(const std::string&) = 0;
};

TEST(test_overloaded_functions, foo)
{
   MockObject<overloaded_interface> mock;
   mock(&overloaded_interface::foo).when().thenReturn(0);
   mock(static_cast<int (overloaded_interface::*)(bool)>(&overloaded_interface::foo)).when(true).thenReturn(0);
   mock(static_cast<int (overloaded_interface::*)(char)>(&overloaded_interface::foo)).when('A').thenReturn(0);
   mock(static_cast<int (overloaded_interface::*)(char)>(&overloaded_interface::foo)).when('%').thenReturn(1);
//   mock(static_cast<int (overloaded_interface::*)(const std::string&)>(&overloaded_interface::foo)).when("bar").thenReturn(50);
//   mock(static_cast<int (overloaded_interface::*)(const std::string&)>(&overloaded_interface::foo)).when("hello").thenReturn(10);
   overloaded_interface& obj = mock.getInstance();

   ASSERT_EQ(0, obj.foo(true));
   ASSERT_THROW(obj.foo(false), mockitopp::detail::IncompleteImplementationException);
   ASSERT_EQ(0, obj.foo('A'));
   ASSERT_EQ(1, obj.foo('%'));
   ASSERT_THROW(obj.foo('#'), mockitopp::detail::IncompleteImplementationException);
//   ASSERT_EQ(50, obj.foo("bar"));
//   ASSERT_EQ(10, obj.foo("hello"));
//   ASSERT_THROW(obj.foo("!@#$%"), mockitopp::detail::IncompleteImplementationException);

   ASSERT_TRUE(mock(static_cast<int (overloaded_interface::*)(bool)>(&overloaded_interface::foo)).exactly(2));
   ASSERT_TRUE(mock(static_cast<int (overloaded_interface::*)(char)>(&overloaded_interface::foo)).exactly(3));
//   ASSERT_TRUE(mock(static_cast<int (overloaded_interface::*)(std::string)>(&overloaded_interface::foo)).exactly(3));
}

