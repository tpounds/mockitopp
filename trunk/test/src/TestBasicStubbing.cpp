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
   VoidVoidInterface& i = mock.getInstance();

   // returnable call
   mock.when(&VoidVoidInterface::foo)().thenReturn();
   i.foo();
   ASSERT_TRUE(mock.verify(&VoidVoidInterface::foo).exactly(1));

   // throwable call
   mock.when(&VoidVoidInterface::foo)().thenThrow(std::string("Hypothetical Error!"));
   ASSERT_THROW(i.foo(), std::string);
}

struct CharVoidInterface
{
   virtual char foo() = 0;
};
TEST(TestBasicStubbing, CharVoid)
{
   MockObject<CharVoidInterface> mock;
   CharVoidInterface& i = mock.getInstance();

   // returnable call
   mock.when(&CharVoidInterface::foo)().thenReturn('A');
   ASSERT_EQ('A', i.foo());
   ASSERT_TRUE(mock.verify(&CharVoidInterface::foo).exactly(1));

   // throwable call
   mock.when(&CharVoidInterface::foo)().thenThrow(std::string("Hypothetical Error!"));
   ASSERT_THROW(i.foo(), std::string);
}

struct VoidStringRefInterface
{
   virtual void foo(const std::string& ref) = 0;
};
TEST(TestBasicStubbing, VoidStringRef)
{
   MockObject<VoidStringRefInterface> mock;
   VoidStringRefInterface& i = mock.getInstance();

   // returnable call
   std::string bar = "bar";
   mock.when(&VoidStringRefInterface::foo)(bar).thenReturn();
   i.foo(bar);
   ASSERT_TRUE(mock.verify(&VoidStringRefInterface::foo).exactly(1));
}
