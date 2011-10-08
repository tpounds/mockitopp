#include "tpunit++.hpp"
#include <mockitopp/mockitopp.hpp>

struct test_cref : tpunit::TestFixture
{
   test_cref() : tpunit::TestFixture
   (
      TEST(test_cref::derived_type),
      TEST(test_cref::interface_type)
   )
   {}

   struct test_cref_base
   {
      virtual int do_it() = 0;

      bool operator<(const test_cref_base&) const
         { return false; }

      bool operator==(const test_cref_base&) const
         { return true; }
   };

   struct test_cref_derived : public test_cref_base
   {
      virtual int do_it()
         { return 100; }
   };

   struct test_cref_interface
   {
      virtual int wrap_base(const test_cref_base&) = 0;
   };

   void derived_type()
   {
      mockitopp::mock_object<test_cref_interface> mock;
      test_cref_derived d;
      mock(&test_cref_interface::wrap_base).when(d).thenReturn(100);
      test_cref_interface& obj = mock.getInstance();

      ASSERT_EQUAL(100, obj.wrap_base(test_cref_derived()));
   }

   void interface_type()
   {
      mockitopp::mock_object<test_cref_interface> mock;
      const test_cref_base& i = test_cref_derived();
      mock(&test_cref_interface::wrap_base).when(i).thenReturn(100);
      test_cref_interface& obj = mock.getInstance();

      ASSERT_EQUAL(100, obj.wrap_base(test_cref_derived()));
   }
} __test_cref;
