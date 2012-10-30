#include "tpunit++.hpp"
#include <mockitopp/mockitopp.hpp>

struct PlainOleDataTypesTest : tpunit::TestFixture
{
   PlainOleDataTypesTest() : tpunit::TestFixture
      (TEST(PlainOleDataTypesTest::test))
      {}

   struct PlainOleDataTypes
   {
      virtual int  __int(int) = 0;
      virtual bool __bool(bool) = 0;
      virtual char __char(char) = 0;
   };

   void test()
   {
      mockitopp::mock_object<PlainOleDataTypes> m;
      m(&PlainOleDataTypes::__int).when(0).thenReturn(2);
      m(&PlainOleDataTypes::__int).when(100).thenReturn(8);
      m(&PlainOleDataTypes::__bool).when(true).thenReturn(false);
      m(&PlainOleDataTypes::__bool).when(false).thenReturn(true);
      m(&PlainOleDataTypes::__char).when('A').thenReturn('Z');
      m(&PlainOleDataTypes::__char).when('Z').thenReturn('0');
      PlainOleDataTypes& i = m.getInstance();

      ASSERT_EQUAL(2, i.__int(0));
      ASSERT_EQUAL(8, i.__int(100));
      ASSERT_EQUAL(8, i.__int(100));
      ASSERT_EQUAL(8, i.__int(100));
      ASSERT_EQUAL(8, i.__int(100));
      ASSERT_EQUAL(2, i.__int(0));
      ASSERT_EQUAL(2, i.__int(0));
      ASSERT_EQUAL(2, i.__int(0));
      ASSERT_EQUAL(2, i.__int(0));
      ASSERT_THROW(i.__int(999), mockitopp::partial_implementation_exception);
      ASSERT_TRUE(m(&PlainOleDataTypes::__int).when(0).exactly(5));
      ASSERT_TRUE(m(&PlainOleDataTypes::__int).when(100).exactly(4));
      ASSERT_TRUE(m(&PlainOleDataTypes::__int).when(999).exactly(1));

      ASSERT_EQUAL(false, i.__bool(true));
      ASSERT_EQUAL(true, i.__bool(false));
      ASSERT_TRUE(m(&PlainOleDataTypes::__bool).when(true).exactly(1));
      ASSERT_TRUE(m(&PlainOleDataTypes::__bool).when(false).exactly(1));

      ASSERT_EQUAL('Z', i.__char('A'));
      ASSERT_EQUAL('0', i.__char('Z'));
      ASSERT_THROW(i.__char('B'), mockitopp::partial_implementation_exception);
      ASSERT_TRUE(m(&PlainOleDataTypes::__char).when('A').exactly(1));
      ASSERT_TRUE(m(&PlainOleDataTypes::__char).when('B').exactly(1));
      ASSERT_TRUE(m(&PlainOleDataTypes::__char).when('Z').exactly(1));
   }
} __PlainOleDataTypesTest;
