#include <UnitTest++.h>

#include <mockitopp/MockObject.hpp>

using mockitopp::MockObject;

struct ReferenceInterface
{
   virtual ReferenceInterface& get() = 0;
};
TEST(TestReferenceReturnable)
{
   MockObject<ReferenceInterface> mock;
   mock.stub(&ReferenceInterface::get);
   ReferenceInterface& i = mock.getMock();

   ReferenceInterface& ret = i.get();
   CHECK(mock.verifyExactly(&ReferenceInterface::get, 1));
}

struct PointerInterface
{
   virtual PointerInterface* get() = 0;
};
TEST(TestPointerReturnable)
{
   MockObject<PointerInterface> mock;
   mock.stub(&PointerInterface::get);
   PointerInterface& i = mock.getMock();

   CHECK(NULL == i.get());
   CHECK(mock.verifyExactly(&PointerInterface::get, 1));
}

struct VoidInterface
{
   virtual void get() = 0;
};
TEST(TestVoidReturnable)
{
   MockObject<VoidInterface> mock;
   mock.stub(&VoidInterface::get);
   VoidInterface& i = mock.getMock();

   i.get();
   CHECK(mock.verifyExactly(&VoidInterface::get, 1));
}

#include <string>
struct StringInterface
{
   virtual std::string get() = 0;
};
TEST(TestStringReturnable)
{
   MockObject<StringInterface> mock;
   mock.stub(&StringInterface::get);
   StringInterface& i = mock.getMock();

   CHECK("" == i.get());
   CHECK(mock.verifyExactly(&StringInterface::get, 1));
}

struct PODInterface
{
   virtual char   getChar()   = 0;
   virtual bool   getBool()   = 0;
   virtual int    getInt()    = 0;
   virtual long   getLong()   = 0;
   virtual float  getFloat()  = 0;
   virtual double getDouble() = 0;
};
TEST(TestPODReturnable)
{
   MockObject<PODInterface> mock;
   mock.stub(&PODInterface::getChar);
   mock.stub(&PODInterface::getBool);
   mock.stub(&PODInterface::getInt);
   mock.stub(&PODInterface::getLong);
   mock.stub(&PODInterface::getFloat);
   mock.stub(&PODInterface::getDouble);
   PODInterface& i = mock.getMock();

   CHECK(0 == i.getChar());
   CHECK(mock.verifyExactly(&PODInterface::getChar, 1));

   CHECK(false == i.getBool());
   CHECK(mock.verifyExactly(&PODInterface::getBool, 1));

   CHECK(0 == i.getInt());
   CHECK(mock.verifyExactly(&PODInterface::getInt, 1));

   CHECK(0 == i.getLong());
   CHECK(mock.verifyExactly(&PODInterface::getLong, 1));

   CHECK(0.0 == i.getFloat());
   CHECK(mock.verifyExactly(&PODInterface::getFloat, 1));

   CHECK(0.0 == i.getDouble());
   CHECK(mock.verifyExactly(&PODInterface::getDouble, 1));
}

struct PODPointerInterface
{
   virtual void*   getVoidP()   = 0;
   virtual char*   getCharP()   = 0;
   virtual bool*   getBoolP()   = 0;
   virtual int*    getIntP()    = 0;
   virtual long*   getLongP()   = 0;
   virtual float*  getFloatP()  = 0;
   virtual double* getDoubleP() = 0;
};
TEST(TestPODPointerReturnable)
{
   MockObject<PODPointerInterface> mock;
   mock.stub(&PODPointerInterface::getVoidP);
   mock.stub(&PODPointerInterface::getCharP);
   mock.stub(&PODPointerInterface::getBoolP);
   mock.stub(&PODPointerInterface::getIntP);
   mock.stub(&PODPointerInterface::getLongP);
   mock.stub(&PODPointerInterface::getFloatP);
   mock.stub(&PODPointerInterface::getDoubleP);
   PODPointerInterface& i = mock.getMock();

   CHECK(NULL == i.getVoidP());
   CHECK(mock.verifyExactly(&PODPointerInterface::getVoidP, 1));

   CHECK(NULL == i.getCharP());
   CHECK(mock.verifyExactly(&PODPointerInterface::getCharP, 1));

   CHECK(NULL == i.getBoolP());
   CHECK(mock.verifyExactly(&PODPointerInterface::getBoolP, 1));

   CHECK(NULL == i.getIntP());
   CHECK(mock.verifyExactly(&PODPointerInterface::getIntP, 1));

   CHECK(NULL == i.getLongP());
   CHECK(mock.verifyExactly(&PODPointerInterface::getLongP, 1));

   CHECK(NULL == i.getFloatP());
   CHECK(mock.verifyExactly(&PODPointerInterface::getFloatP, 1));

   CHECK(NULL == i.getDoubleP());
   CHECK(mock.verifyExactly(&PODPointerInterface::getDoubleP, 1));
}
