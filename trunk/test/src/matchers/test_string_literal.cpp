#include <gtest/gtest.h>
#include <mockitopp/MockObject.hpp>
#include <mockitopp/matchers/type/string_literal.hpp>

using mockitopp::MockObject;
using mockitopp::matcher::string_literal;

struct string_literal_test_interface
{
   virtual int char_ptr(char*) = 0;
   virtual int const_char_ptr(const char*) = 0;
};

TEST(test_string_literal, char_ptr)
{
   MockObject<string_literal_test_interface> mock;
   mock(&string_literal_test_interface::char_ptr).when(string_literal<char*>("FOO")).thenReturn(0);
   mock(&string_literal_test_interface::char_ptr).when(string_literal<char*>("BAR")).thenReturn(1);
   string_literal_test_interface& obj = mock.getInstance();

   ASSERT_EQ(0, obj.char_ptr("FOO"));
   ASSERT_EQ(1, obj.char_ptr("BAR"));
   ASSERT_THROW(obj.char_ptr("NO MATCH"), mockitopp::detail::IncompleteImplementationException);
}

TEST(test_string_literal, const_char_ptr)
{
   MockObject<string_literal_test_interface> mock;
   mock(&string_literal_test_interface::const_char_ptr).when(string_literal<const char*>("1234567890")).thenReturn(0);
   mock(&string_literal_test_interface::const_char_ptr).when(string_literal<const char*>("!@$#")).thenReturn(1);
   string_literal_test_interface& obj = mock.getInstance();

   ASSERT_EQ(0, obj.const_char_ptr("1234567890"));
   ASSERT_EQ(1, obj.const_char_ptr("!@$#"));
   ASSERT_THROW(obj.const_char_ptr("NO MATCH"), mockitopp::detail::IncompleteImplementationException);
}
