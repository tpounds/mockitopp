#include "tpunit++.hpp"
#include <mockitopp/mockitopp.hpp>

struct test_overloaded_functions : tpunit::TestFixture
{
   test_overloaded_functions() : tpunit::TestFixture
   (
      TEST(test_overloaded_functions::test_overloaded_interface)
   )
   {}

   struct overloaded_interface
   {
      virtual int foo() = 0;
      virtual int foo(bool) = 0;
      virtual int foo(char) = 0;
      virtual int foo(const std::string&) = 0;
   };
   void test_overloaded_interface()
   {
      mockitopp::mock_object<overloaded_interface> mock;
      mock(static_cast<int (overloaded_interface::*)()>(&overloaded_interface::foo)).when().thenReturn(0);
      mock(static_cast<int (overloaded_interface::*)(bool)>(&overloaded_interface::foo)).when(true).thenReturn(0);
      mock(static_cast<int (overloaded_interface::*)(char)>(&overloaded_interface::foo)).when('A').thenReturn(0);
      mock(static_cast<int (overloaded_interface::*)(char)>(&overloaded_interface::foo)).when('%').thenReturn(1);
      std::string bar("bar");
      mock(static_cast<int (overloaded_interface::*)(const std::string&)>(&overloaded_interface::foo)).when(bar).thenReturn(50);
      std::string hello("hello");
      mock(overloaded_method(int, overloaded_interface, foo, const std::string&)).when(hello).thenReturn(10);
      overloaded_interface& obj = mock.getInstance();

      ASSERT_EQUAL(0, obj.foo(true));
      ASSERT_THROW(obj.foo(false), mockitopp::partial_implementation_exception);
      ASSERT_EQUAL(0, obj.foo('A'));
      ASSERT_EQUAL(1, obj.foo('%'));
      ASSERT_THROW(obj.foo('#'), mockitopp::partial_implementation_exception);
      // XXX: explicitly specify std::string because of implicit boolean conversion (i.e. ISO 14882 sec 4.12)
      ASSERT_EQUAL(50, obj.foo(std::string("bar")));
      ASSERT_EQUAL(10, obj.foo(std::string("hello")));
      ASSERT_THROW(obj.foo(std::string("!@#$%")), mockitopp::partial_implementation_exception);

      ASSERT_TRUE(mock(static_cast<int (overloaded_interface::*)(bool)>(&overloaded_interface::foo)).when(true).exactly(1));
      ASSERT_TRUE(mock(static_cast<int (overloaded_interface::*)(char)>(&overloaded_interface::foo)).when('A').exactly(1));
      // ASSERT_TRUE(mock(static_cast<int (overloaded_interface::*)(const std::string&)>(&overloaded_interface::foo)).when(hello).exactly(1));
   }
} __test_overloaded_functions;
