#include <UnitTest++.h>

#include <mockitopp/MockObject.hpp>

using mockitopp::MockObject;

struct Interface1
{
   virtual int foo() = 0;
};

struct Interface2
{
   virtual int bar() = 0;
};

struct SimpleComposite
{
   Interface1& _i1;
   Interface2& _i2;

   SimpleComposite(Interface1& i1, Interface2& i2)
      : _i1(i1)
      , _i2(i2)
      {}

   int simpleAdd()
   {
      return _i1.foo() + _i2.bar();
   }

   int simpleMultiply()
   {
      return _i1.foo() * _i2.bar();
   }
};

TEST(TestSimpleCompositeAdd)
{
   MockObject<Interface1> mock1;
   mock1.stub(&Interface1::foo).arguments().returns(2);
   Interface1& i1 = mock1.getMock();

   MockObject<Interface2> mock2;
   mock2.stub(&Interface2::bar).arguments().returns(10);
   Interface2& i2 = mock2.getMock();

   SimpleComposite c = SimpleComposite(i1, i2);

   CHECK(12 == c.simpleAdd());
   CHECK(mock1.verifyExactly(&Interface1::foo, 1));
   CHECK(mock2.verifyExactly(&Interface2::bar, 1));
}

TEST(TestSimpleCompositeMultiply)
{
   MockObject<Interface1> mock1;
   mock1.stub(&Interface1::foo).arguments().returns(10);
   Interface1& i1 = mock1.getMock();

   MockObject<Interface2> mock2;
   mock2.stub(&Interface2::bar).arguments().returns(10);
   Interface2& i2 = mock2.getMock();

   SimpleComposite c = SimpleComposite(i1, i2);

   CHECK(100 == c.simpleMultiply());
   CHECK(mock1.verifyExactly(&Interface1::foo, 1));
   CHECK(mock2.verifyExactly(&Interface2::bar, 1));
}

TEST(TestSimpleCompositeAddandMultiply)
{
   MockObject<Interface1> mock1;
   mock1.stub(&Interface1::foo).arguments().returns(10);
   Interface1& i1 = mock1.getMock();

   MockObject<Interface2> mock2;
   mock2.stub(&Interface2::bar).arguments().returns(10);
   Interface2& i2 = mock2.getMock();

   SimpleComposite c = SimpleComposite(i1, i2);

   CHECK(20  == c.simpleAdd());
   CHECK(100 == c.simpleMultiply());
   CHECK(mock1.verifyExactly(&Interface1::foo, 2));
   CHECK(mock2.verifyExactly(&Interface2::bar, 2));
}
