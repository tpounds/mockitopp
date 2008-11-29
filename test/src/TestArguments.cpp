#include <gtest/gtest.h>
#include <mockitopp/MockObject.hpp>

using mockitopp::MockObject;

struct PlainOleDataTypes
{
   virtual int  __int(int) = 0;
   virtual bool __bool(bool) = 0;
   virtual char __char(char) = 0;
};
TEST(TestArguments, PlainOleDataTypes)
{
   MockObject<PlainOleDataTypes> m;
   m.when(&PlainOleDataTypes::__int)(0).thenReturn(2);
   m.when(&PlainOleDataTypes::__int)(100).thenReturn(8);
   m.when(&PlainOleDataTypes::__bool)(true).thenReturn(false);
   m.when(&PlainOleDataTypes::__bool)(false).thenReturn(true);
   m.when(&PlainOleDataTypes::__char)('A').thenReturn('Z');
   m.when(&PlainOleDataTypes::__char)('Z').thenReturn('0');
   PlainOleDataTypes& i = m.getInstance();

   ASSERT_EQ(2, i.__int(0));
   ASSERT_EQ(8, i.__int(100));
   ASSERT_EQ(8, i.__int(100));
   ASSERT_EQ(8, i.__int(100));
   ASSERT_EQ(8, i.__int(100));
   ASSERT_EQ(2, i.__int(0));
   ASSERT_EQ(2, i.__int(0));
   ASSERT_EQ(2, i.__int(0));
   ASSERT_EQ(2, i.__int(0));
   ASSERT_THROW(i.__int(999), mockitopp::detail::IncompleteImplementationException);
   ASSERT_TRUE(m.verify(&PlainOleDataTypes::__int).exactly(10));

   ASSERT_EQ(false, i.__bool(true));
   ASSERT_EQ(true, i.__bool(false));
   ASSERT_TRUE(m.verify(&PlainOleDataTypes::__bool).exactly(2));

   ASSERT_EQ('Z', i.__char('A'));
   ASSERT_EQ('0', i.__char('Z'));
   ASSERT_THROW(i.__char('B'), mockitopp::detail::IncompleteImplementationException);
   ASSERT_TRUE(m.verify(&PlainOleDataTypes::__char).exactly(3));
}
