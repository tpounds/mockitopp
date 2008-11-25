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
   mock.when(&ReferenceInterface::get);
   ReferenceInterface& i = mock.getInstance();

   ReferenceInterface& ret = i.get();
   ASSERT_TRUE(mock.verify(&ReferenceInterface::get).exactly(1));
}

struct PointerInterface
{
   virtual PointerInterface* get() = 0;
};
TEST(TestDefaultAction, PointerInterface)
{
   MockObject<PointerInterface> mock;
   mock.when(&PointerInterface::get);
   PointerInterface& i = mock.getInstance();

   ASSERT_TRUE(NULL == i.get());
   ASSERT_TRUE(mock.verify(&PointerInterface::get).exactly(1));
}

struct VoidInterface
{
   virtual void get() = 0;
};
TEST(TestDefaultAction, VoidInterface)
{
   MockObject<VoidInterface> mock;
   mock.when(&VoidInterface::get);
   VoidInterface& i = mock.getInstance();

   i.get();
   ASSERT_TRUE(mock.verify(&VoidInterface::get).exactly(1));
}

#include <string>
struct StringInterface
{
   virtual std::string get() = 0;
};
TEST(TestDefaultAction, StringInterface)
{
   MockObject<StringInterface> mock;
   mock.when(&StringInterface::get);
   StringInterface& i = mock.getInstance();

   ASSERT_EQ("", i.get());
   ASSERT_TRUE(mock.verify(&StringInterface::get).exactly(1));
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
   mock.when(&PODInterface::getChar);
   mock.when(&PODInterface::getBool);
   mock.when(&PODInterface::getInt);
   mock.when(&PODInterface::getLong);
   mock.when(&PODInterface::getFloat);
   mock.when(&PODInterface::getDouble);
   PODInterface& i = mock.getInstance();

   ASSERT_EQ(0, i.getChar());
   ASSERT_TRUE(mock.verify(&PODInterface::getChar).exactly(1));

   ASSERT_EQ(false, i.getBool());
   ASSERT_TRUE(mock.verify(&PODInterface::getBool).exactly(1));

   ASSERT_EQ(0, i.getInt());
   ASSERT_TRUE(mock.verify(&PODInterface::getInt).exactly(1));

   ASSERT_EQ(0, i.getLong());
   ASSERT_TRUE(mock.verify(&PODInterface::getLong).exactly(1));

   ASSERT_EQ(0.0, i.getFloat());
   ASSERT_TRUE(mock.verify(&PODInterface::getFloat).exactly(1));

   ASSERT_EQ(0.0, i.getDouble());
   ASSERT_TRUE(mock.verify(&PODInterface::getDouble).exactly(1));
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
   mock.when(&PODPointerInterface::getVoidP);
   mock.when(&PODPointerInterface::getCharP);
   mock.when(&PODPointerInterface::getBoolP);
   mock.when(&PODPointerInterface::getIntP);
   mock.when(&PODPointerInterface::getLongP);
   mock.when(&PODPointerInterface::getFloatP);
   mock.when(&PODPointerInterface::getDoubleP);
   PODPointerInterface& i = mock.getInstance();

   ASSERT_TRUE(NULL == i.getVoidP());
   ASSERT_TRUE(mock.verify(&PODPointerInterface::getVoidP).exactly(1));

   ASSERT_TRUE(NULL == i.getCharP());
   ASSERT_TRUE(mock.verify(&PODPointerInterface::getCharP).exactly(1));

   ASSERT_TRUE(NULL == i.getBoolP());
   ASSERT_TRUE(mock.verify(&PODPointerInterface::getBoolP).exactly(1));

   ASSERT_TRUE(NULL == i.getIntP());
   ASSERT_TRUE(mock.verify(&PODPointerInterface::getIntP).exactly(1));

   ASSERT_TRUE(NULL == i.getLongP());
   ASSERT_TRUE(mock.verify(&PODPointerInterface::getLongP).exactly(1));

   ASSERT_TRUE(NULL == i.getFloatP());
   ASSERT_TRUE(mock.verify(&PODPointerInterface::getFloatP).exactly(1));

   ASSERT_TRUE(NULL == i.getDoubleP());
   ASSERT_TRUE(mock.verify(&PODPointerInterface::getDoubleP).exactly(1));
}
