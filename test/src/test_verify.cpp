#include "tpunit++.hpp"
#include <mockitopp/mockitopp.hpp>

struct test_verify : tpunit::TestFixture
{
   test_verify() : tpunit::TestFixture
   (
      TEST(test_verify::atLeast),
      TEST(test_verify::atMost),
      TEST(test_verify::between),
      TEST(test_verify::exactly),
      TEST(test_verify::never)
   )
   {}

   struct verify_interface
   {
      virtual void func() = 0;
   };

   #define VERIFY_MOCK_DEFINITION \
      mockitopp::mock_object<verify_interface> mock; \
      mock(&verify_interface::func).when().thenReturn(); \
      verify_interface& obj = mock.getInstance(); \
   \
      obj.func(); \
      obj.func(); \
      obj.func();

   void atLeast()
   {
      VERIFY_MOCK_DEFINITION

      ASSERT_TRUE(mock(&verify_interface::func).when().atLeast(1));
      ASSERT_TRUE(mock(&verify_interface::func).when().atLeast(2));
      ASSERT_TRUE(mock(&verify_interface::func).when().atLeast(3));
      ASSERT_FALSE(mock(&verify_interface::func).when().atLeast(4));
   }

   void atMost()
   {
      VERIFY_MOCK_DEFINITION

      ASSERT_FALSE(mock(&verify_interface::func).when().atMost(1));
      ASSERT_FALSE(mock(&verify_interface::func).when().atMost(2));
      ASSERT_TRUE(mock(&verify_interface::func).when().atMost(3));
      ASSERT_TRUE(mock(&verify_interface::func).when().atMost(4));
   }

   void between()
   {
      VERIFY_MOCK_DEFINITION

      ASSERT_FALSE(mock(&verify_interface::func).when().between(0, 2));
      ASSERT_FALSE(mock(&verify_interface::func).when().between(4, 9));
      ASSERT_TRUE(mock(&verify_interface::func).when().between(1, 5));
      ASSERT_TRUE(mock(&verify_interface::func).when().between(3, 3));
   }

   void exactly()
   {
      VERIFY_MOCK_DEFINITION

      ASSERT_FALSE(mock(&verify_interface::func).when().exactly(1));
      ASSERT_FALSE(mock(&verify_interface::func).when().exactly(2));
      ASSERT_TRUE(mock(&verify_interface::func).when().exactly(3));
      ASSERT_FALSE(mock(&verify_interface::func).when().exactly(4));
   }

   void never()
   {
      VERIFY_MOCK_DEFINITION

      ASSERT_FALSE(mock(&verify_interface::func).when().never());
   }
} __test_verify;
