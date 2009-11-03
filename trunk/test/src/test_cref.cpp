#include <gtest/gtest.h>
#include <mockitopp/mockitopp.hpp>

using mockitopp::mock_object;

struct test_cref_base
{
   virtual int do_it() = 0;
};

struct test_cref_derived : public test_cref_base
{
   virtual int do_it()
      { return 100; }
};

bool operator<(const test_cref_base&, const test_cref_base&)
   { return false; }

bool operator==(const test_cref_base&, const test_cref_base&)
   { return true; }

struct test_cref_interface
{
   virtual int wrap_base(const test_cref_base&) = 0;
};

TEST(test_cref, derived_type)
{
   mock_object<test_cref_interface> mock;
   test_cref_derived d;
   mock(&test_cref_interface::wrap_base).when(d).thenReturn(100);
   test_cref_interface& obj = mock.getInstance();

   ASSERT_EQ(100, obj.wrap_base(test_cref_derived()));
}

TEST(test_cref, interface_type)
{
   mock_object<test_cref_interface> mock;
   const test_cref_base& i = test_cref_derived();
   mock(&test_cref_interface::wrap_base).when(i).thenReturn(100);
   test_cref_interface& obj = mock.getInstance();

   ASSERT_EQ(100, obj.wrap_base(test_cref_derived()));
}
