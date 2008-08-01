#include <mockitopp/MockObject.hpp>
#include <UnitTest++.h>

using mockitopp::MockObject;

struct VoidVoidInterface
{
   virtual void foo() = 0;
};
TEST(TestBasicStubbingVoidVoid)
{
   MockObject<VoidVoidInterface> mock;
   VoidVoidInterface& i = mock.getMock();

   // returnable call
   mock.stub(&VoidVoidInterface::foo).arguments().returns();
   i.foo();
   CHECK(mock.verifyExactly(&VoidVoidInterface::foo, 1));

   // throwable call
   mock.stub(&VoidVoidInterface::foo).arguments().throws(std::string("Hypothetical Error!"));
   try
   {
      i.foo();
      CHECK(false);
   }
   catch(...)
      { CHECK(true); }
}


struct CharVoidInterface
{
   virtual char foo() = 0;
};
TEST(TestBasicStubbingCharVoid)
{
   MockObject<CharVoidInterface> mock;
   CharVoidInterface& i = mock.getMock();

   // returnable call
   mock.stub(&CharVoidInterface::foo).arguments().returns('A');
   CHECK('A' == i.foo());
   CHECK(mock.verifyExactly(&CharVoidInterface::foo, 1));

   // throwable call
   mock.stub(&CharVoidInterface::foo).arguments().throws(std::string("Hypothetical Error!"));
   try
   {
      i.foo();
      CHECK(false);
   }
   catch(...)
      { CHECK(true); }
}
