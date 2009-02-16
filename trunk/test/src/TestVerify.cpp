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
   mock(&SimpleInterface::foo).when().thenReturn();
   SimpleInterface& si = mock.getInstance();

   si.foo();
   si.foo();
   si.foo();

   ASSERT_TRUE(mock.verify(&SimpleInterface::foo).atLeast(1));
   ASSERT_TRUE(mock.verify(&SimpleInterface::foo).atLeast(2));
   ASSERT_TRUE(mock.verify(&SimpleInterface::foo).atLeast(3));
   ASSERT_FALSE(mock.verify(&SimpleInterface::foo).atLeast(4));
}

TEST(TestVerify, AtMost)
{
   MockObject<SimpleInterface> mock;
   mock(&SimpleInterface::foo).when().thenReturn();
   SimpleInterface& si = mock.getInstance();

   si.foo();
   si.foo();
   si.foo();
   si.foo();

   ASSERT_FALSE(mock.verify(&SimpleInterface::foo).atMost(1));
   ASSERT_FALSE(mock.verify(&SimpleInterface::foo).atMost(2));
   ASSERT_FALSE(mock.verify(&SimpleInterface::foo).atMost(3));
   ASSERT_TRUE(mock.verify(&SimpleInterface::foo).atMost(4));
   ASSERT_TRUE(mock.verify(&SimpleInterface::foo).atMost(5));
}

TEST(TestVerify, Exactly)
{
   MockObject<SimpleInterface> mock;
   mock(&SimpleInterface::foo).when().thenReturn();
   SimpleInterface& si = mock.getInstance();

   si.foo();
   si.foo();

   ASSERT_FALSE(mock.verify(&SimpleInterface::foo).exactly(0));
   ASSERT_FALSE(mock.verify(&SimpleInterface::foo).exactly(1));
   ASSERT_TRUE(mock.verify(&SimpleInterface::foo).exactly(2));
   ASSERT_FALSE(mock.verify(&SimpleInterface::foo).exactly(3));
   ASSERT_FALSE(mock.verify(&SimpleInterface::foo).exactly(4));
}

TEST(TestVerify, Never)
{
   MockObject<SimpleInterface> mock;
   mock(&SimpleInterface::foo).when().thenReturn();
   SimpleInterface& si = mock.getInstance();

   ASSERT_TRUE(mock.verify(&SimpleInterface::foo).never());
   si.foo();
   ASSERT_FALSE(mock.verify(&SimpleInterface::foo).never());
}
