#if defined(MOCKITOPP_STD_REGEX)
   #include <regex>
#elif defined(MOCKITOPP_STD_TR1_REGEX)
   #include <tr1/regex>
#elif defined(MOCKITOPP_BOOST_REGEX)
   #include <boost/regex.hpp>
#endif

#if defined(MOCKITOPP_STD_REGEX) || defined(MOCKITOPP_STD_TR1_REGEX) || defined(MOCKITOPP_BOOST_REGEX)

/* gcc versions <= 4.8 do not fully support ECMAScript regular expressions */

#include "tpunit++.hpp"
#include <mockitopp/mockitopp.hpp>
#include <mockitopp/matchers/regex.hpp>

using mockitopp::mock_object;
using mockitopp::matcher::regex;

struct test_regex : tpunit::TestFixture
{
   test_regex() : tpunit::TestFixture
   (
      TEST(test_regex::const_char),
      TEST(test_regex::std_string),
      TEST(test_regex::composite)
   )
   {}

   struct regex_interface
   {
      virtual std::string const_char_s(const char*) = 0;
      virtual std::string std_string(const std::string&) = 0;
      virtual std::string composite(const char*, const std::string&) = 0;
   };

   void const_char()
   {
      mock_object<regex_interface> mock;
      mock(&regex_interface::const_char_s).when(regex(".*foo.*")).thenReturn("matches__.*foo.*");
      mock(&regex_interface::const_char_s).when(regex(".*bar.*")).thenReturn("matches__.*bar.*");
#if ! (defined(_GLIBCXX_TR1_REGEX) || defined(_GLIBCXX_REGEX))
      mock(&regex_interface::const_char_s).when(regex("[A-Z]*")).thenReturn("matches__[A-Z]*");
#endif
      regex_interface& obj = mock.getInstance();

      ASSERT_EQUAL("matches__.*foo.*", obj.const_char_s("foo"));
      ASSERT_EQUAL("matches__.*bar.*", obj.const_char_s("bar"));
#if ! (defined(_GLIBCXX_TR1_REGEX) || defined(_GLIBCXX_REGEX))
      ASSERT_EQUAL("matches__[A-Z]*",  obj.const_char_s("ABCDEFGHIKLMNOPQRSTUVWXYZ"));
#endif
      ASSERT_THROW(obj.const_char_s("FOO-BAR"),    mockitopp::partial_implementation_exception);
      ASSERT_THROW(obj.const_char_s("1234567890"), mockitopp::partial_implementation_exception);
   }

   void std_string()
   {
      mock_object<regex_interface> mock;
      mock(&regex_interface::std_string).when(regex<const std::string&>(".*foo.*")).thenReturn("matches__.*foo.*");
      mock(&regex_interface::std_string).when(regex<const std::string&>(".*bar.*")).thenReturn("matches__.*bar.*");
#if ! (defined(_GLIBCXX_TR1_REGEX) || defined(_GLIBCXX_REGEX))
      mock(&regex_interface::std_string).when(regex<const std::string&>("[A-Z]*")).thenReturn("matches__[A-Z]*");
#endif
      regex_interface& obj = mock.getInstance();

      ASSERT_EQUAL("matches__.*foo.*", obj.std_string("foo"));
      ASSERT_EQUAL("matches__.*bar.*", obj.std_string("bar"));
#if ! (defined(_GLIBCXX_TR1_REGEX) || defined(_GLIBCXX_REGEX))
      ASSERT_EQUAL("matches__[A-Z]*",  obj.std_string("ABCDEFGHIKLMNOPQRSTUVWXYZ"));
#endif
      ASSERT_THROW(obj.std_string("FOO-BAR"),    mockitopp::partial_implementation_exception);
      ASSERT_THROW(obj.std_string("1234567890"), mockitopp::partial_implementation_exception);
   }

   void composite()
   {
      mock_object<regex_interface> mock;
      mock(&regex_interface::composite).when(regex(".*foo.*"), regex<const std::string&>(".*bar.*")).thenReturn("matches__.*foo.*__.*bar.*");
      mock(&regex_interface::composite).when(regex(".*FOO.*"), regex<const std::string&>(".*BAR.*")).thenReturn("matches__.*FOO.*__.*BAR.*");
#if ! (defined(_GLIBCXX_TR1_REGEX) || defined(_GLIBCXX_REGEX))
      mock(&regex_interface::composite).when(regex("[a-z]*"),  regex<const std::string&>("[A-Z]*")).thenReturn("matches__[a-z]*__[A-Z]*");
#endif
      regex_interface& obj = mock.getInstance();

      ASSERT_EQUAL("matches__.*foo.*__.*bar.*", obj.composite("foo", "bar"));
      ASSERT_EQUAL("matches__.*foo.*__.*bar.*", obj.composite("abc-foo-xyz", "123-bar-890"));
      ASSERT_EQUAL("matches__.*FOO.*__.*BAR.*", obj.composite("FOO", "BAR"));
      ASSERT_EQUAL("matches__.*FOO.*__.*BAR.*", obj.composite("FOOTLONG SANDWICH", "BARLEY SOUP"));
#if ! (defined(_GLIBCXX_TR1_REGEX) || defined(_GLIBCXX_REGEX))
      ASSERT_EQUAL("matches__[a-z]*__[A-Z]*",   obj.composite("abcdefghijklmnopqrstuvwxyz", "ABCDEFGHIKLMNOPQRSTUVWXYZ"));
#endif
      ASSERT_THROW(obj.composite("foo", "abcdefghij"), mockitopp::partial_implementation_exception);
      ASSERT_THROW(obj.composite("1234567890", "bar"), mockitopp::partial_implementation_exception);
   }
} __test_regex;
#endif // MOCKITOPP_REGEX_HEADER
