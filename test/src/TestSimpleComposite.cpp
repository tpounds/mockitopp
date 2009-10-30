#include <gtest/gtest.h>
#include <mockitopp/mockitopp.hpp>

using mockitopp::mock_object;

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

TEST(TestSimpleComposite, Add)
{
   mock_object<Interface1> mock1;
   mock1(&Interface1::foo).when().thenReturn(2);
   Interface1& i1 = mock1.getInstance();

   mock_object<Interface2> mock2;
   mock2(&Interface2::bar).when().thenReturn(10);
   Interface2& i2 = mock2.getInstance();

   SimpleComposite c = SimpleComposite(i1, i2);

   ASSERT_EQ(12, c.simpleAdd());
   ASSERT_TRUE(mock1(&Interface1::foo).exactly(1));
   ASSERT_TRUE(mock2(&Interface2::bar).exactly(1));
}

TEST(TestSimpleComposite, Multiply)
{
   mock_object<Interface1> mock1;
   mock1(&Interface1::foo).when().thenReturn(10);
   Interface1& i1 = mock1.getInstance();

   mock_object<Interface2> mock2;
   mock2(&Interface2::bar).when().thenReturn(10);
   Interface2& i2 = mock2.getInstance();

   SimpleComposite c = SimpleComposite(i1, i2);

   ASSERT_EQ(100, c.simpleMultiply());
   ASSERT_TRUE(mock1(&Interface1::foo).exactly(1));
   ASSERT_TRUE(mock2(&Interface2::bar).exactly(1));
}

TEST(TestSimpleComposite, Add_and_Multiply)
{
   mock_object<Interface1> mock1;
   mock1(&Interface1::foo).when().thenReturn(10);
   Interface1& i1 = mock1.getInstance();

   mock_object<Interface2> mock2;
   mock2(&Interface2::bar).when().thenReturn(10);
   Interface2& i2 = mock2.getInstance();

   SimpleComposite c = SimpleComposite(i1, i2);

   ASSERT_EQ(20,  c.simpleAdd());
   ASSERT_EQ(100, c.simpleMultiply());
   ASSERT_TRUE(mock1(&Interface1::foo).exactly(2));
   ASSERT_TRUE(mock2(&Interface2::bar).exactly(2));
}
