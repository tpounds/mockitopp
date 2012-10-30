#include "tpunit++.hpp"
#include <mockitopp/mockitopp.hpp>

struct TestBasicStubbing : tpunit::TestFixture
{
   TestBasicStubbing() : tpunit::TestFixture
   (
      TEST(TestBasicStubbing::VoidVoid),
      TEST(TestBasicStubbing::CharVoid),
      TEST(TestBasicStubbing::VoidStringRef)
   )
   {}
   
   struct VoidVoidInterface { virtual void foo() = 0; };
   void VoidVoid()
   {
      mockitopp::mock_object<VoidVoidInterface> mock;
      mock(&VoidVoidInterface::foo).when().thenReturn();
      mock(&VoidVoidInterface::foo).when().thenThrow(std::string("Hypothetical Error!"));
      VoidVoidInterface& i = mock.getInstance();

      i.foo();
      ASSERT_TRUE(mock(&VoidVoidInterface::foo).when().exactly(1));

      ASSERT_THROW(i.foo(), std::string);
   }

   struct CharVoidInterface { virtual char foo() = 0; };
   void CharVoid()
   {
      mockitopp::mock_object<CharVoidInterface> mock;
      mock(&CharVoidInterface::foo).when().thenReturn('A');
      mock(&CharVoidInterface::foo).when().thenThrow(std::string("Hypothetical Error!"));
      CharVoidInterface& i = mock.getInstance();

      ASSERT_EQUAL('A', i.foo());
      ASSERT_TRUE(mock(&CharVoidInterface::foo).when().exactly(1));

      ASSERT_THROW(i.foo(), std::string);
   }

   struct VoidStringRefInterface { virtual void foo(const std::string& ref) = 0; };
   void VoidStringRef()
   {
      mockitopp::mock_object<VoidStringRefInterface> mock;
      std::string bar("bar");
      mock(&VoidStringRefInterface::foo).when(bar).thenReturn();
      VoidStringRefInterface& i = mock.getInstance();

      i.foo("bar");
      ASSERT_TRUE(mock(&VoidStringRefInterface::foo).when("bar").exactly(1));
   }
} __TestBasicStubbing;
