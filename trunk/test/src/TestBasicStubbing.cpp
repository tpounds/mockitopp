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
   mock(&VoidVoidInterface::foo).when().thenReturn();
   mock(&VoidVoidInterface::foo).when().thenThrow(std::string("Hypothetical Error!"));
   VoidVoidInterface& i = mock.getInstance();

   i.foo();
   ASSERT_TRUE(mock.verify(&VoidVoidInterface::foo).exactly(1));

   ASSERT_THROW(i.foo(), std::string);
}

struct CharVoidInterface
{
   virtual char foo() = 0;
};
TEST(TestBasicStubbing, CharVoid)
{
   MockObject<CharVoidInterface> mock;
   mock(&CharVoidInterface::foo).when().thenReturn('A');
   mock(&CharVoidInterface::foo).when().thenThrow(std::string("Hypothetical Error!"));
   CharVoidInterface& i = mock.getInstance();

   ASSERT_EQ('A', i.foo());
   ASSERT_TRUE(mock.verify(&CharVoidInterface::foo).exactly(1));

   ASSERT_THROW(i.foo(), std::string);
}

struct VoidStringRefInterface
{
   virtual void foo(const std::string& ref) = 0;
};
TEST(TestBasicStubbing, VoidStringRef)
{
   MockObject<VoidStringRefInterface> mock;
   mock(&VoidStringRefInterface::foo).when("bar").thenReturn();
   VoidStringRefInterface& i = mock.getInstance();

   i.foo("bar");
   ASSERT_TRUE(mock.verify(&VoidStringRefInterface::foo).exactly(1));
}
