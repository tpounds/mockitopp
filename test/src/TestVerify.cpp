#include <gtest/gtest.h>
#include <mockitopp/MockObject.hpp>

using mockitopp::MockObject;

class SimpleInterface
{
   public: virtual void foo() = 0;
};

TEST(TestVerify, AtLeast)
{
   MockObject<SimpleInterface> mock;
   mock.when(&SimpleInterface::foo)().thenReturn();
   SimpleInterface& si = mock.getMock();

   si.foo();
   si.foo();
   si.foo();

   ASSERT_TRUE(mock.verifyAtLeast(&SimpleInterface::foo, 1));
   ASSERT_TRUE(mock.verifyAtLeast(&SimpleInterface::foo, 2));
   ASSERT_TRUE(mock.verifyAtLeast(&SimpleInterface::foo, 3));
   ASSERT_FALSE(mock.verifyAtLeast(&SimpleInterface::foo, 4));
}

TEST(TestVerify, AtMost)
{
   MockObject<SimpleInterface> mock;
   mock.when(&SimpleInterface::foo)().thenReturn();
   SimpleInterface& si = mock.getMock();

   si.foo();
   si.foo();
   si.foo();
   si.foo();

   ASSERT_FALSE(mock.verifyAtMost(&SimpleInterface::foo, 1));
   ASSERT_FALSE(mock.verifyAtMost(&SimpleInterface::foo, 2));
   ASSERT_FALSE(mock.verifyAtMost(&SimpleInterface::foo, 3));
   ASSERT_TRUE(mock.verifyAtMost(&SimpleInterface::foo, 4));
   ASSERT_TRUE(mock.verifyAtMost(&SimpleInterface::foo, 5));
}

TEST(TestVerify, Exactly)
{
   MockObject<SimpleInterface> mock;
   mock.when(&SimpleInterface::foo)().thenReturn();
   SimpleInterface& si = mock.getMock();

   si.foo();
   si.foo();

   ASSERT_FALSE(mock.verifyExactly(&SimpleInterface::foo, 0));
   ASSERT_FALSE(mock.verifyExactly(&SimpleInterface::foo, 1));
   ASSERT_TRUE(mock.verifyExactly(&SimpleInterface::foo, 2));
   ASSERT_FALSE(mock.verifyExactly(&SimpleInterface::foo, 3));
   ASSERT_FALSE(mock.verifyExactly(&SimpleInterface::foo, 4));
}

TEST(TestVerify, Never)
{
   MockObject<SimpleInterface> mock;
   mock.when(&SimpleInterface::foo)().thenReturn();
   SimpleInterface& si = mock.getMock();

   ASSERT_TRUE(mock.verifyNever(&SimpleInterface::foo));
   si.foo();
   ASSERT_FALSE(mock.verifyNever(&SimpleInterface::foo));
}
