#include "tpunit++.hpp"
#include <mockitopp/mockitopp.hpp>

using mockitopp::mock_object;
using mockitopp::matcher::string_literal;

struct test_string_literal : tpunit::TestFixture
{
   test_string_literal() : tpunit::TestFixture
   (
      TEST(test_string_literal::char_ptr),
      TEST(test_string_literal::const_char_ptr)
   )
   {}

   struct string_literal_test_interface
   {
      virtual int char_ptr(char*) = 0;
      virtual int const_char_ptr(const char*) = 0;
   };

   void char_ptr()
   {
      mock_object<string_literal_test_interface> mock;
      mock(&string_literal_test_interface::char_ptr).when(string_literal<char*>(const_cast<char*>("FOO"))).thenReturn(0);
      mock(&string_literal_test_interface::char_ptr).when(string_literal<char*>(const_cast<char*>("BAR"))).thenReturn(1);
      string_literal_test_interface& obj = mock.getInstance();

      ASSERT_EQUAL(0, obj.char_ptr(const_cast<char*>("FOO")));
      ASSERT_EQUAL(1, obj.char_ptr(const_cast<char*>("BAR")));
      ASSERT_THROW(obj.char_ptr(const_cast<char*>("NO MATCH")), mockitopp::partial_implementation_exception);
   }

   void const_char_ptr()
   {
      mock_object<string_literal_test_interface> mock;
      mock(&string_literal_test_interface::const_char_ptr).when(string_literal<const char*>("1234567890")).thenReturn(0);
      mock(&string_literal_test_interface::const_char_ptr).when(string_literal<const char*>("!@$#")).thenReturn(1);
      string_literal_test_interface& obj = mock.getInstance();

      ASSERT_EQUAL(0, obj.const_char_ptr("1234567890"));
      ASSERT_EQUAL(1, obj.const_char_ptr("!@$#"));
      ASSERT_THROW(obj.const_char_ptr("NO MATCH"), mockitopp::partial_implementation_exception);
   }
} __test_string_literal;
