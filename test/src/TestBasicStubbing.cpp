#include <gtest/gtest.h>
#include <mockitopp/MockObject.hpp>

using mockitopp::MockObject;

struct VoidVoidInterface
{
   virtual void foo() = 0;
};
TEST(TestBasicStubbing, VoidVoid)
{
   MockObject<VoidVoidInterface> mock;
   VoidVoidInterface& i = mock.getMock();

   // returnable call
   mock.stub(&VoidVoidInterface::foo).arguments().returns();
   i.foo();
   ASSERT_TRUE(mock.verifyExactly(&VoidVoidInterface::foo, 1));

   // throwable call
   mock.stub(&VoidVoidInterface::foo).arguments().throws(std::string("Hypothetical Error!"));
   ASSERT_THROW(i.foo(), std::string);
}

struct CharVoidInterface
{
   virtual char foo() = 0;
};
TEST(TestBasicStubbing, CharVoid)
{
   MockObject<CharVoidInterface> mock;
   CharVoidInterface& i = mock.getMock();

   // returnable call
   mock.stub(&CharVoidInterface::foo).arguments().returns('A');
   ASSERT_EQ('A', i.foo());
   ASSERT_TRUE(mock.verifyExactly(&CharVoidInterface::foo, 1));

   // throwable call
   mock.stub(&CharVoidInterface::foo).arguments().throws(std::string("Hypothetical Error!"));
   ASSERT_THROW(i.foo(), std::string);
}
