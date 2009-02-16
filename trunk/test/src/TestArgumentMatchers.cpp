#include <gtest/gtest.h>
#include <mockitopp/MockObject.hpp>
#include <mockitopp/Matchers.hpp>

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
