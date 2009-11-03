#include <gtest/gtest.h>
#include <mockitopp/mockitopp.hpp>

using mockitopp::mock_object;

struct overloaded_interface
{
   virtual int foo() = 0;
   virtual int foo(bool) = 0;
   virtual int foo(char) = 0;
   virtual int foo(const std::string&) = 0;
};

TEST(test_overloaded_functions, foo)
{
   mock_object<overloaded_interface> mock;
   mock(static_cast<int (overloaded_interface::*)()>(&overloaded_interface::foo)).when().thenReturn(0);
   mock(static_cast<int (overloaded_interface::*)(bool)>(&overloaded_interface::foo)).when(true).thenReturn(0);
   mock(static_cast<int (overloaded_interface::*)(char)>(&overloaded_interface::foo)).when('A').thenReturn(0);
   mock(static_cast<int (overloaded_interface::*)(char)>(&overloaded_interface::foo)).when('%').thenReturn(1);
   std::string bar("bar");
   mock(static_cast<int (overloaded_interface::*)(const std::string&)>(&overloaded_interface::foo)).when(bar).thenReturn(50);
   std::string hello("hello");
   mock(static_cast<int (overloaded_interface::*)(const std::string&)>(&overloaded_interface::foo)).when(hello).thenReturn(10);
   overloaded_interface& obj = mock.getInstance();

   ASSERT_EQ(0, obj.foo(true));
   ASSERT_THROW(obj.foo(false), mockitopp::partial_implementation_exception);
   ASSERT_EQ(0, obj.foo('A'));
   ASSERT_EQ(1, obj.foo('%'));
   ASSERT_THROW(obj.foo('#'), mockitopp::partial_implementation_exception);
   // XXX: explicitly specify std::string because of implicit boolean conversion (i.e. ISO 14882 sec 4.12)
   ASSERT_EQ(50, obj.foo(std::string("bar")));
   ASSERT_EQ(10, obj.foo(std::string("hello")));
   ASSERT_THROW(obj.foo(std::string("!@#$%")), mockitopp::partial_implementation_exception);

   ASSERT_TRUE(mock(static_cast<int (overloaded_interface::*)(bool)>(&overloaded_interface::foo)).exactly(2));
   ASSERT_TRUE(mock(static_cast<int (overloaded_interface::*)(char)>(&overloaded_interface::foo)).exactly(3));
   ASSERT_TRUE(mock(static_cast<int (overloaded_interface::*)(const std::string&)>(&overloaded_interface::foo)).exactly(3));
}
