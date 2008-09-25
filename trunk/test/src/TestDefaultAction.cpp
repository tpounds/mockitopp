#include <gtest/gtest.h>
#include <mockitopp/MockObject.hpp>

// XXX: ASSERT_EQ(NULL, i.getXXX()) generates template warnings, using ASSERT_TRUE for those cases

using mockitopp::MockObject;

struct ReferenceInterface
{
   virtual ReferenceInterface& get() = 0;
};
TEST(TestDefaultAction, ReferenceInterface)
{
   MockObject<ReferenceInterface> mock;
   mock.stub(&ReferenceInterface::get);
   ReferenceInterface& i = mock.getMock();

   ReferenceInterface& ret = i.get();
   ASSERT_TRUE(mock.verifyExactly(&ReferenceInterface::get, 1));
}

struct PointerInterface
{
   virtual PointerInterface* get() = 0;
};
TEST(TestDefaultAction, PointerInterface)
{
   MockObject<PointerInterface> mock;
   mock.stub(&PointerInterface::get);
   PointerInterface& i = mock.getMock();

   ASSERT_TRUE(NULL == i.get());
   ASSERT_TRUE(mock.verifyExactly(&PointerInterface::get, 1));
}

struct VoidInterface
{
   virtual void get() = 0;
};
TEST(TestDefaultAction, VoidInterface)
{
   MockObject<VoidInterface> mock;
   mock.stub(&VoidInterface::get);
   VoidInterface& i = mock.getMock();

   i.get();
   ASSERT_TRUE(mock.verifyExactly(&VoidInterface::get, 1));
}

#include <string>
struct StringInterface
{
   virtual std::string get() = 0;
};
TEST(TestDefaultAction, StringInterface)
{
   MockObject<StringInterface> mock;
   mock.stub(&StringInterface::get);
   StringInterface& i = mock.getMock();

   ASSERT_EQ("", i.get());
   ASSERT_TRUE(mock.verifyExactly(&StringInterface::get, 1));
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
TEST(TestDefaultAction, PODInterface)
{
   MockObject<PODInterface> mock;
   mock.stub(&PODInterface::getChar);
   mock.stub(&PODInterface::getBool);
   mock.stub(&PODInterface::getInt);
   mock.stub(&PODInterface::getLong);
   mock.stub(&PODInterface::getFloat);
   mock.stub(&PODInterface::getDouble);
   PODInterface& i = mock.getMock();

   ASSERT_EQ(0, i.getChar());
   ASSERT_TRUE(mock.verifyExactly(&PODInterface::getChar, 1));

   ASSERT_EQ(false, i.getBool());
   ASSERT_TRUE(mock.verifyExactly(&PODInterface::getBool, 1));

   ASSERT_EQ(0, i.getInt());
   ASSERT_TRUE(mock.verifyExactly(&PODInterface::getInt, 1));

   ASSERT_EQ(0, i.getLong());
   ASSERT_TRUE(mock.verifyExactly(&PODInterface::getLong, 1));

   ASSERT_EQ(0.0, i.getFloat());
   ASSERT_TRUE(mock.verifyExactly(&PODInterface::getFloat, 1));

   ASSERT_EQ(0.0, i.getDouble());
   ASSERT_TRUE(mock.verifyExactly(&PODInterface::getDouble, 1));
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
TEST(TestDefaultAction, PODPointerInterface)
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

   ASSERT_TRUE(NULL == i.getVoidP());
   ASSERT_TRUE(mock.verifyExactly(&PODPointerInterface::getVoidP, 1));

   ASSERT_TRUE(NULL == i.getCharP());
   ASSERT_TRUE(mock.verifyExactly(&PODPointerInterface::getCharP, 1));

   ASSERT_TRUE(NULL == i.getBoolP());
   ASSERT_TRUE(mock.verifyExactly(&PODPointerInterface::getBoolP, 1));

   ASSERT_TRUE(NULL == i.getIntP());
   ASSERT_TRUE(mock.verifyExactly(&PODPointerInterface::getIntP, 1));

   ASSERT_TRUE(NULL == i.getLongP());
   ASSERT_TRUE(mock.verifyExactly(&PODPointerInterface::getLongP, 1));

   ASSERT_TRUE(NULL == i.getFloatP());
   ASSERT_TRUE(mock.verifyExactly(&PODPointerInterface::getFloatP, 1));

   ASSERT_TRUE(NULL == i.getDoubleP());
   ASSERT_TRUE(mock.verifyExactly(&PODPointerInterface::getDoubleP, 1));
}
