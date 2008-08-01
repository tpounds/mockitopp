#include <UnitTest++.h>

#include <mockitopp/MockObject.hpp>

using mockitopp::MockObject;

class SimpleInterface
{
   public: virtual void foo() = 0;
};

TEST(TestVerifyAtLeast)
{
   MockObject<SimpleInterface> mock;
   mock.stub(&SimpleInterface::foo).arguments().returns();
   SimpleInterface& si = mock.getMock();

   si.foo();
   si.foo();
   si.foo();

   CHECK(mock.verifyAtLeast(&SimpleInterface::foo, 1));
   CHECK(mock.verifyAtLeast(&SimpleInterface::foo, 2));
   CHECK(mock.verifyAtLeast(&SimpleInterface::foo, 3));
   CHECK(!mock.verifyAtLeast(&SimpleInterface::foo, 4));
}

TEST(TestVerifyAtMost)
{
   MockObject<SimpleInterface> mock;
   mock.stub(&SimpleInterface::foo).arguments().returns();
   SimpleInterface& si = mock.getMock();

   si.foo();
   si.foo();
   si.foo();
   si.foo();

   CHECK(!mock.verifyAtMost(&SimpleInterface::foo, 1));
   CHECK(!mock.verifyAtMost(&SimpleInterface::foo, 2));
   CHECK(!mock.verifyAtMost(&SimpleInterface::foo, 3));
   CHECK(mock.verifyAtMost(&SimpleInterface::foo, 4));
   CHECK(mock.verifyAtMost(&SimpleInterface::foo, 5));
}

TEST(TestVerifyExactly)
{
   MockObject<SimpleInterface> mock;
   mock.stub(&SimpleInterface::foo).arguments().returns();
   SimpleInterface& si = mock.getMock();

   si.foo();
   si.foo();

   CHECK(!mock.verifyExactly(&SimpleInterface::foo, 0));
   CHECK(!mock.verifyExactly(&SimpleInterface::foo, 1));
   CHECK(mock.verifyExactly(&SimpleInterface::foo, 2));
   CHECK(!mock.verifyExactly(&SimpleInterface::foo, 3));
   CHECK(!mock.verifyExactly(&SimpleInterface::foo, 4));
}

TEST(TestVerifyNever)
{
   MockObject<SimpleInterface> mock;
   mock.stub(&SimpleInterface::foo).arguments().returns();
   SimpleInterface& si = mock.getMock();

   CHECK(mock.verifyNever(&SimpleInterface::foo));
   si.foo();
   CHECK(!mock.verifyNever(&SimpleInterface::foo));
}
