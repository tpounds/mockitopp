#include <gtest/gtest.h>
#include <matchers/hc_all_of.h>
#include <matchers/hc_any_of.h>
#include <matchers/hc_anything.h>
#include <matchers/hc_equal_to.h>
#include <matchers/hc_is.h>
#include <matchers/hc_is_not.h>
#include <matchers/hc_same_instance.h>
#include <matchers/hc_shortcut_combination.h>
#include <mockitopp/MockObject.hpp>
#include <mockitopp/matchers/optional/hamcrest.hpp>

using namespace hamcrest;
using mockitopp::MockObject;
using mockitopp::matcher::hc;

struct hc_interface
{
   virtual std::string hc_test(const char*) = 0;
};

TEST(test_hamcrest, all_of)
{
   MockObject<hc_interface> mock;
   mock(&hc_interface::hc_test).when(hc(all_of(is_not("foo"), is_not("bar"), is_not("abc")))).thenReturn("is_not_foo__is_not_bar__is_not_abc");
   mock(&hc_interface::hc_test).when(hc(all_of(is("foo"), is_not("bar")))).thenReturn("is_foo__is_not_bar");
   hc_interface& obj = mock.getInstance();

   ASSERT_EQ("is_not_foo__is_not_bar__is_not_abc", obj.hc_test("foobar"));
   ASSERT_EQ("is_not_foo__is_not_bar__is_not_abc", obj.hc_test("All work and no play makes Jack a dull boy."));
   ASSERT_EQ("is_not_foo__is_not_bar__is_not_abc", obj.hc_test("beef"));
   ASSERT_EQ("is_not_foo__is_not_bar__is_not_abc", obj.hc_test("Hello World!"));
   ASSERT_EQ("is_foo__is_not_bar", obj.hc_test("foo"));
   ASSERT_THROW(obj.hc_test("bar"), mockitopp::detail::IncompleteImplementationException);
   ASSERT_THROW(obj.hc_test("abc"), mockitopp::detail::IncompleteImplementationException);
}

TEST(test_hamcrest, any_of)
{
   MockObject<hc_interface> mock;
   mock(&hc_interface::hc_test).when(hc(any_of(is("foo"), is("bar"), is("abc")))).thenReturn("is_foo__is_bar__is_abc");
   mock(&hc_interface::hc_test).when(hc(any_of(is("123"), is_not("890")))).thenReturn("is_123__is_not_890");
   hc_interface& obj = mock.getInstance();

   ASSERT_EQ("is_foo__is_bar__is_abc", obj.hc_test("foo"));
   ASSERT_EQ("is_foo__is_bar__is_abc", obj.hc_test("bar"));
   ASSERT_EQ("is_foo__is_bar__is_abc", obj.hc_test("abc"));
   ASSERT_EQ("is_123__is_not_890", obj.hc_test("123"));
   ASSERT_EQ("is_123__is_not_890", obj.hc_test("456"));
   ASSERT_EQ("is_123__is_not_890", obj.hc_test("foobar"));
   ASSERT_EQ("is_123__is_not_890", obj.hc_test("abcdefghijklmnopqrstuvwxyz"));
   ASSERT_THROW(obj.hc_test("890"), mockitopp::detail::IncompleteImplementationException);
}

TEST(test_hamcrest, anything)
{
   MockObject<hc_interface> mock;
   mock(&hc_interface::hc_test).when(hc(anything<const char*>())).thenReturn("anything");
   hc_interface& obj = mock.getInstance();

   ASSERT_EQ("anything", obj.hc_test("foobar"));
   ASSERT_EQ("anything", obj.hc_test("All work and no play makes Jack a dull boy."));
   ASSERT_EQ("anything", obj.hc_test("beef"));
   ASSERT_EQ("anything", obj.hc_test("Hello World!"));
}

TEST(test_hamcrest, equal_to)
{
   MockObject<hc_interface> mock;
   mock(&hc_interface::hc_test).when(hc(equal_to("foo"))).thenReturn("equal_to_foo");
   hc_interface& obj = mock.getInstance();

   ASSERT_EQ("equal_to_foo", obj.hc_test("foo"));
   ASSERT_THROW(obj.hc_test("bar"), mockitopp::detail::IncompleteImplementationException);
}

TEST(test_hamcrest, is)
{
   MockObject<hc_interface> mock;
   mock(&hc_interface::hc_test).when(hc(is("foo"))).thenReturn("is_foo");
   hc_interface& obj = mock.getInstance();

   ASSERT_EQ("is_foo", obj.hc_test("foo"));
   ASSERT_THROW(obj.hc_test("abc"), mockitopp::detail::IncompleteImplementationException);
   ASSERT_THROW(obj.hc_test("bar"), mockitopp::detail::IncompleteImplementationException);
}

TEST(test_hamcrest, is_not)
{
   MockObject<hc_interface> mock;
   mock(&hc_interface::hc_test).when(hc(is_not("foo"))).thenReturn("is_not_foo");
   hc_interface& obj = mock.getInstance();

   ASSERT_EQ("is_not_foo", obj.hc_test("abc"));
   ASSERT_EQ("is_not_foo", obj.hc_test("bar"));
   ASSERT_THROW(obj.hc_test("foo"), mockitopp::detail::IncompleteImplementationException);
}

/* FIXME: broken?
TEST(test_hamcrest, same_instance)
{
   const char* argument = "foo";

   MockObject<hc_interface> mock;
   mock(&hc_interface::hc_test).when(hc(same_instance(argument))).thenReturn("same foo instance");
   hc_interface& obj = mock.getInstance();

   ASSERT_EQ("same foo instance", obj.hc_test(argument));
   ASSERT_THROW(obj.hc_test("foo"), mockitopp::detail::IncompleteImplementationException);
}*/

// TODO: shortcut combination
