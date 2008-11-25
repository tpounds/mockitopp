#include <gtest/gtest.h>
#include <mockitopp/MockObject.hpp>
#include <string>

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
   m.when(&PlainOleDataTypes::__bool)('Z').thenReturn('0');
   PlainOleDataTypes& i = m.getInstance();

   ASSERT_EQ(2, i.__int(0));
   ASSERT_EQ(8, i.__int(100));
   ASSERT_TRUE(m.verify(&PlainOleDataTypes::__int).exactly(2));
}
