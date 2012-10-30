#include "tpunit++.hpp"
#include <mockitopp/mockitopp.hpp>

struct TestSimpleComposite : tpunit::TestFixture
{
   TestSimpleComposite() : tpunit::TestFixture
   (
      TEST(TestSimpleComposite::Add),
      TEST(TestSimpleComposite::Multiply),
      TEST(TestSimpleComposite::Add_and_Multiply)
   )
   {}

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

   void Add()
   {
      mockitopp::mock_object<Interface1> mock1;
      mock1(&Interface1::foo).when().thenReturn(2);
      Interface1& i1 = mock1.getInstance();

      mockitopp::mock_object<Interface2> mock2;
      mock2(&Interface2::bar).when().thenReturn(10);
      Interface2& i2 = mock2.getInstance();

      SimpleComposite c = SimpleComposite(i1, i2);

      ASSERT_EQUAL(12, c.simpleAdd());
      ASSERT_TRUE(mock1(&Interface1::foo).when().exactly(1));
      ASSERT_TRUE(mock2(&Interface2::bar).when().exactly(1));
   }

   void Multiply()
   {
      mockitopp::mock_object<Interface1> mock1;
      mock1(&Interface1::foo).when().thenReturn(10);
      Interface1& i1 = mock1.getInstance();

      mockitopp::mock_object<Interface2> mock2;
      mock2(&Interface2::bar).when().thenReturn(10);
      Interface2& i2 = mock2.getInstance();

      SimpleComposite c = SimpleComposite(i1, i2);

      ASSERT_EQUAL(100, c.simpleMultiply());
      ASSERT_TRUE(mock1(&Interface1::foo).when().exactly(1));
      ASSERT_TRUE(mock2(&Interface2::bar).when().exactly(1));
   }

   void Add_and_Multiply()
   {
      mockitopp::mock_object<Interface1> mock1;
      mock1(&Interface1::foo).when().thenReturn(10);
      Interface1& i1 = mock1.getInstance();

      mockitopp::mock_object<Interface2> mock2;
      mock2(&Interface2::bar).when().thenReturn(10);
      Interface2& i2 = mock2.getInstance();

      SimpleComposite c = SimpleComposite(i1, i2);

      ASSERT_EQUAL(20,  c.simpleAdd());
      ASSERT_EQUAL(100, c.simpleMultiply());
      ASSERT_TRUE(mock1(&Interface1::foo).when().exactly(2));
      ASSERT_TRUE(mock2(&Interface2::bar).when().exactly(2));
   }
} __TestSimpleComposite;
