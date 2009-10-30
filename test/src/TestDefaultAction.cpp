#include <gtest/gtest.h>
#include <mockitopp/mockitopp.hpp>

// XXX: ASSERT_EQ(NULL, i.getXXX()) generates template warnings, using ASSERT_TRUE for those cases

using mockitopp::mock_object;

struct ReferenceInterface
{
   virtual ReferenceInterface& get() = 0;
};
TEST(TestDefaultAction, ReferenceInterface)
{
   mock_object<ReferenceInterface> mock;
   mock(&ReferenceInterface::get);
   ReferenceInterface& i = mock.getInstance();

   ReferenceInterface& ret = i.get();
   ASSERT_TRUE(mock(&ReferenceInterface::get).exactly(1));
}

struct PointerInterface
{
   virtual PointerInterface* get() = 0;
};
TEST(TestDefaultAction, PointerInterface)
{
   mock_object<PointerInterface> mock;
   mock(&PointerInterface::get);
   PointerInterface& i = mock.getInstance();

   ASSERT_TRUE(NULL == i.get());
   ASSERT_TRUE(mock(&PointerInterface::get).exactly(1));
}

struct VoidInterface
{
   virtual void get() = 0;
};
TEST(TestDefaultAction, VoidInterface)
{
   mock_object<VoidInterface> mock;
   mock(&VoidInterface::get);
   VoidInterface& i = mock.getInstance();

   i.get();
   ASSERT_TRUE(mock(&VoidInterface::get).exactly(1));
}

#include <string>
struct StringInterface
{
   virtual std::string get() = 0;
};
TEST(TestDefaultAction, StringInterface)
{
   mock_object<StringInterface> mock;
   mock(&StringInterface::get);
   StringInterface& i = mock.getInstance();

   ASSERT_EQ("", i.get());
   ASSERT_TRUE(mock(&StringInterface::get).exactly(1));
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
   mock_object<PODInterface> mock;
   mock(&PODInterface::getChar);
   mock(&PODInterface::getBool);
   mock(&PODInterface::getInt);
   mock(&PODInterface::getLong);
   mock(&PODInterface::getFloat);
   mock(&PODInterface::getDouble);
   PODInterface& i = mock.getInstance();

   ASSERT_EQ(0, i.getChar());
   ASSERT_TRUE(mock(&PODInterface::getChar).exactly(1));

   ASSERT_EQ(false, i.getBool());
   ASSERT_TRUE(mock(&PODInterface::getBool).exactly(1));

   ASSERT_EQ(0, i.getInt());
   ASSERT_TRUE(mock(&PODInterface::getInt).exactly(1));

   ASSERT_EQ(0, i.getLong());
   ASSERT_TRUE(mock(&PODInterface::getLong).exactly(1));

   ASSERT_EQ(0.0, i.getFloat());
   ASSERT_TRUE(mock(&PODInterface::getFloat).exactly(1));

   ASSERT_EQ(0.0, i.getDouble());
   ASSERT_TRUE(mock(&PODInterface::getDouble).exactly(1));
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
   mock_object<PODPointerInterface> mock;
   mock(&PODPointerInterface::getVoidP);
   mock(&PODPointerInterface::getCharP);
   mock(&PODPointerInterface::getBoolP);
   mock(&PODPointerInterface::getIntP);
   mock(&PODPointerInterface::getLongP);
   mock(&PODPointerInterface::getFloatP);
   mock(&PODPointerInterface::getDoubleP);
   PODPointerInterface& i = mock.getInstance();

   ASSERT_TRUE(NULL == i.getVoidP());
   ASSERT_TRUE(mock(&PODPointerInterface::getVoidP).exactly(1));

   ASSERT_TRUE(NULL == i.getCharP());
   ASSERT_TRUE(mock(&PODPointerInterface::getCharP).exactly(1));

   ASSERT_TRUE(NULL == i.getBoolP());
   ASSERT_TRUE(mock(&PODPointerInterface::getBoolP).exactly(1));

   ASSERT_TRUE(NULL == i.getIntP());
   ASSERT_TRUE(mock(&PODPointerInterface::getIntP).exactly(1));

   ASSERT_TRUE(NULL == i.getLongP());
   ASSERT_TRUE(mock(&PODPointerInterface::getLongP).exactly(1));

   ASSERT_TRUE(NULL == i.getFloatP());
   ASSERT_TRUE(mock(&PODPointerInterface::getFloatP).exactly(1));

   ASSERT_TRUE(NULL == i.getDoubleP());
   ASSERT_TRUE(mock(&PODPointerInterface::getDoubleP).exactly(1));
}
