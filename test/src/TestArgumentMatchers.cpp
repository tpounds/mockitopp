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
   mock(&VoidPtrInterface::foo).when(Null<int*>()).thenReturn(200);
   mock(&VoidPtrInterface::foo).when(NotNull<int*>()).thenReturn(100);
   mock(&VoidPtrInterface::bar).when(NotNull<int*>(), NotEq<std::string>("bar")).thenReturn(1234);
   mock(&VoidPtrInterface::bar).when(Null<int*>(), Eq<std::string>("hello")).thenReturn(5678);
   VoidPtrInterface& i = mock.getInstance();

   ASSERT_EQ(200, i.foo(0));
   ASSERT_EQ(100, i.foo(new int));
   ASSERT_EQ(100, i.foo(new int));
   ASSERT_EQ(100, i.foo(new int));
   ASSERT_EQ(100, i.foo(new int));
   ASSERT_EQ(1234, i.bar(new int, "NOT-bar"));
   ASSERT_EQ(5678, i.bar(0, "hello"));
}

#include <matchers/hc_all_of.h>
#include <matchers/hc_any_of.h>
#include <matchers/hc_anything.h>
#include <matchers/hc_equal_to.h>
#include <matchers/hc_is.h>
#include <matchers/hc_is_not.h>
#include <matchers/hc_same_instance.h>
#include <matchers/hc_shortcut_combination.h>
#include <mockitopp/matchers/3rdparty/Hamcrest.hpp>

using namespace hamcrest;

struct HamcrestInterface
{
   virtual int foo(std::string) = 0;
};
TEST(TestArgumentMatchers, Hamcrest)
{
   MockObject<HamcrestInterface> mock;
   mock(&HamcrestInterface::foo).when(Hamcrest<std::string>(all_of(is_not(std::string("hello")),
                                                                   is_not(std::string("world")),
                                                                   is_not(std::string("foo"))))).thenReturn(1243);
   HamcrestInterface& hc = mock.getInstance();

   ASSERT_EQ(1243, hc.foo("NOT-foo"));
   ASSERT_EQ(1243, hc.foo("bar"));
}
