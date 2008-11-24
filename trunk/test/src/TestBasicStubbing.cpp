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
   mock.when(&VoidVoidInterface::foo)().toReturn();
   i.foo();
   ASSERT_TRUE(mock.verifyExactly(&VoidVoidInterface::foo, 1));

   // throwable call
   mock.when(&VoidVoidInterface::foo)().toThrow(std::string("Hypothetical Error!"));
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
   mock.when(&CharVoidInterface::foo)().toReturn('A');
   ASSERT_EQ('A', i.foo());
   ASSERT_TRUE(mock.verifyExactly(&CharVoidInterface::foo, 1));

   // throwable call
   mock.when(&CharVoidInterface::foo)().toThrow(std::string("Hypothetical Error!"));
   ASSERT_THROW(i.foo(), std::string);
}
