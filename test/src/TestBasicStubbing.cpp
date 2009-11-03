#include <gtest/gtest.h>
#include <mockitopp/mockitopp.hpp>

using mockitopp::mock_object;

struct VoidVoidInterface
{
   virtual void foo() = 0;
};
TEST(TestBasicStubbing, VoidVoid)
{
   mock_object<VoidVoidInterface> mock;
   mock(&VoidVoidInterface::foo).when().thenReturn();
   mock(&VoidVoidInterface::foo).when().thenThrow(std::string("Hypothetical Error!"));
   VoidVoidInterface& i = mock.getInstance();

   i.foo();
   ASSERT_TRUE(mock(&VoidVoidInterface::foo).exactly(1));

   ASSERT_THROW(i.foo(), std::string);
}

struct CharVoidInterface
{
   virtual char foo() = 0;
};
TEST(TestBasicStubbing, CharVoid)
{
   mock_object<CharVoidInterface> mock;
   mock(&CharVoidInterface::foo).when().thenReturn('A');
   mock(&CharVoidInterface::foo).when().thenThrow(std::string("Hypothetical Error!"));
   CharVoidInterface& i = mock.getInstance();

   ASSERT_EQ('A', i.foo());
   ASSERT_TRUE(mock(&CharVoidInterface::foo).exactly(1));

   ASSERT_THROW(i.foo(), std::string);
}

struct VoidStringRefInterface
{
   virtual void foo(const std::string& ref) = 0;
};
TEST(TestBasicStubbing, VoidStringRef)
{
   mock_object<VoidStringRefInterface> mock;
   std::string bar("bar");
   mock(&VoidStringRefInterface::foo).when(bar).thenReturn();
   VoidStringRefInterface& i = mock.getInstance();

   i.foo("bar");
   ASSERT_TRUE(mock(&VoidStringRefInterface::foo).exactly(1));
}
