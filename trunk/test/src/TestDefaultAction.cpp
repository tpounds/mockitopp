#include "tpunit++.hpp"
#include <mockitopp/mockitopp.hpp>

#include <string>

// XXX: ASSERT_EQ(NULL, i.getXXX()) generates template warnings, using ASSERT_TRUE for those cases

struct TestDefaultAction : tpunit::TestFixture
{
   TestDefaultAction() : tpunit::TestFixture
   (
      TEST(TestDefaultAction::ReferenceInterface),
      TEST(TestDefaultAction::PointerInterface),
      TEST(TestDefaultAction::VoidInterface),
      TEST(TestDefaultAction::PODInterface),
      TEST(TestDefaultAction::PODPointerInterface)
   )
   {}

   struct ReferenceInterface__ { virtual ReferenceInterface__& get() = 0; };
   void ReferenceInterface()
   {
      mockitopp::mock_object<ReferenceInterface__> mock;
      mock(&ReferenceInterface__::get);
      ReferenceInterface__& i = mock.getInstance();

      ReferenceInterface__& ret = i.get();
      ASSERT_TRUE(mock(&ReferenceInterface__::get).exactly(1));
   }

   struct PointerInterface__ { virtual PointerInterface__* get() = 0; };
   void PointerInterface()
   {
      mockitopp::mock_object<PointerInterface__> mock;
      mock(&PointerInterface__::get);
      PointerInterface__& i = mock.getInstance();

      ASSERT_TRUE(NULL == i.get());
      ASSERT_TRUE(mock(&PointerInterface__::get).exactly(1));
   }

   struct VoidInterface__ { virtual void get() = 0; };
   void VoidInterface()
   {
      mockitopp::mock_object<VoidInterface__> mock;
      mock(&VoidInterface__::get);
      VoidInterface__& i = mock.getInstance();

      i.get();
      ASSERT_TRUE(mock(&VoidInterface__::get).exactly(1));
   }

   struct StringInterface__ { virtual std::string get() = 0; };
   void StringInterface()
   {
      mockitopp::mock_object<StringInterface__> mock;
      mock(&StringInterface__::get);
      StringInterface__& i = mock.getInstance();

      ASSERT_EQUAL("", i.get());
      ASSERT_TRUE(mock(&StringInterface__::get).exactly(1));
   }

   struct PODInterface__
   {
      virtual char   getChar()   = 0;
      virtual bool   getBool()   = 0;
      virtual int    getInt()    = 0;
      virtual long   getLong()   = 0;
      virtual float  getFloat()  = 0;
      virtual double getDouble() = 0;
   };
   void PODInterface()
   {
      mockitopp::mock_object<PODInterface__> mock;
      mock(&PODInterface__::getChar);
      mock(&PODInterface__::getBool);
      mock(&PODInterface__::getInt);
      mock(&PODInterface__::getLong);
      mock(&PODInterface__::getFloat);
      mock(&PODInterface__::getDouble);
      PODInterface__& i = mock.getInstance();

      ASSERT_EQUAL(0, i.getChar());
      ASSERT_TRUE(mock(&PODInterface__::getChar).exactly(1));

      ASSERT_EQUAL(false, i.getBool());
      ASSERT_TRUE(mock(&PODInterface__::getBool).exactly(1));

      ASSERT_EQUAL(0, i.getInt());
      ASSERT_TRUE(mock(&PODInterface__::getInt).exactly(1));

      ASSERT_EQUAL(0, i.getLong());
      ASSERT_TRUE(mock(&PODInterface__::getLong).exactly(1));

      ASSERT_EQUAL(0.0, i.getFloat());
      ASSERT_TRUE(mock(&PODInterface__::getFloat).exactly(1));

      ASSERT_EQUAL(0.0, i.getDouble());
      ASSERT_TRUE(mock(&PODInterface__::getDouble).exactly(1));
   }

   struct __PODPointerInterface
   {
      virtual void*   getVoidP()   = 0;
      virtual char*   getCharP()   = 0;
      virtual bool*   getBoolP()   = 0;
      virtual int*    getIntP()    = 0;
      virtual long*   getLongP()   = 0;
      virtual float*  getFloatP()  = 0;
      virtual double* getDoubleP() = 0;
   };
   void PODPointerInterface()
   {
      mockitopp::mock_object<__PODPointerInterface> mock;
      mock(&__PODPointerInterface::getVoidP);
      mock(&__PODPointerInterface::getCharP);
      mock(&__PODPointerInterface::getBoolP);
      mock(&__PODPointerInterface::getIntP);
      mock(&__PODPointerInterface::getLongP);
      mock(&__PODPointerInterface::getFloatP);
      mock(&__PODPointerInterface::getDoubleP);
      __PODPointerInterface& i = mock.getInstance();

      ASSERT_EQUAL(NULL, i.getVoidP());
      ASSERT_TRUE(mock(&__PODPointerInterface::getVoidP).exactly(1));

      ASSERT_TRUE(NULL == i.getCharP());
      ASSERT_TRUE(mock(&__PODPointerInterface::getCharP).exactly(1));

      ASSERT_TRUE(NULL == i.getBoolP());
      ASSERT_TRUE(mock(&__PODPointerInterface::getBoolP).exactly(1));

      ASSERT_TRUE(NULL == i.getIntP());
      ASSERT_TRUE(mock(&__PODPointerInterface::getIntP).exactly(1));

      ASSERT_TRUE(NULL == i.getLongP());
      ASSERT_TRUE(mock(&__PODPointerInterface::getLongP).exactly(1));

      ASSERT_TRUE(NULL == i.getFloatP());
      ASSERT_TRUE(mock(&__PODPointerInterface::getFloatP).exactly(1));

      ASSERT_TRUE(NULL == i.getDoubleP());
      ASSERT_TRUE(mock(&__PODPointerInterface::getDoubleP).exactly(1));
   }
} __TestDefaultAction;
