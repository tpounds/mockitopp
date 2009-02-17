#include <gtest/gtest.h>
#include <mockitopp/MockObject.hpp>

using namespace mockitopp;

struct VoidPtrInterface
{
   virtual int foo(int*) = 0;
   virtual int bar(int*, std::string) = 0;
};
TEST(TestArgumentMatchers, VoidPtr)
{
   MockObject<VoidPtrInterface> mock;
   mock(&VoidPtrInterface::foo).when(null<int*>()).thenReturn(200);
   mock(&VoidPtrInterface::foo).when(not_(null<int*>())).thenReturn(100);
   mock(&VoidPtrInterface::bar).when(not_(null<int*>()), not_(eq(std::string("bar")))).thenReturn(1234);
   mock(&VoidPtrInterface::bar).when(null<int*>(), eq(std::string("hello"))).thenReturn(5678);
   mock(&VoidPtrInterface::bar).when(any<int*>(), any<std::string>()).thenReturn(9999);
   VoidPtrInterface& i = mock.getInstance();

   ASSERT_EQ(200, i.foo(0));
   ASSERT_EQ(100, i.foo(new int));
   ASSERT_EQ(100, i.foo(new int));
   ASSERT_EQ(100, i.foo(new int));
   ASSERT_EQ(100, i.foo(new int));
   ASSERT_EQ(1234, i.bar(new int, "NOT-bar"));
   ASSERT_EQ(5678, i.bar(0, "hello"));
   ASSERT_EQ(9999, i.bar(new int, "bar"));
}

#include <matchers/hc_all_of.h>
#include <matchers/hc_any_of.h>
#include <matchers/hc_anything.h>
#include <matchers/hc_equal_to.h>
#include <matchers/hc_is.h>
#include <matchers/hc_is_not.h>
#include <matchers/hc_same_instance.h>
#include <matchers/hc_shortcut_combination.h>
#include <mockitopp/matchers/optional/Hamcrest.hpp>

using hamcrest::all_of;
using hamcrest::any_of;
using hamcrest::anything;
using hamcrest::equal_to;
using hamcrest::is;
using hamcrest::is_not;
using hamcrest::same_instance;
using hamcrest::shortcut_combination;

struct HamcrestInterface
{
   virtual int foo(std::string) = 0;
};
TEST(TestArgumentMatchers, Hamcrest)
{
   MockObject<HamcrestInterface> mock;
   mock(&HamcrestInterface::foo).when(mockitopp::hamcrest(all_of(is_not(std::string("hello")),
                                                                 is_not(std::string("world")),
                                                                 is_not(std::string("foo"))))).thenReturn(1243);
   HamcrestInterface& hc = mock.getInstance();

   ASSERT_EQ(1243, hc.foo("NOT-foo"));
   ASSERT_EQ(1243, hc.foo("bar"));
}

#include <boost/regex.hpp> 
#include <mockitopp/matchers/optional/Regex.hpp>

struct RegexInterface
{
   virtual int foo(std::string) = 0;
   virtual int bar(const char*) = 0;
};
TEST(TestArgumentMatchers, TR1_Regex)
{
   MockObject<RegexInterface> mock;
   mock(&RegexInterface::foo).when(regex(std::string("foo.*"))).thenReturn(1234);
   mock(&RegexInterface::foo).when(regex(std::string(".*bar.*"))).thenReturn(5678);
   mock(&RegexInterface::bar).when(regex(".*beef.*")).thenReturn(5678);
   RegexInterface& rx = mock.getInstance();

   ASSERT_EQ(1234, rx.foo("foo"));
   ASSERT_EQ(1234, rx.foo("foot"));
   ASSERT_EQ(1234, rx.foo("football"));
   ASSERT_THROW(rx.foo("FOO"), mockitopp::detail::IncompleteImplementationException);
   ASSERT_EQ(5678, rx.foo("bar"));
   ASSERT_EQ(5678, rx.foo("barley"));
   ASSERT_EQ(5678, rx.foo("bartend"));
   ASSERT_THROW(rx.foo("BAR"), mockitopp::detail::IncompleteImplementationException);
   ASSERT_EQ(5678, rx.bar("beefy"));
}
