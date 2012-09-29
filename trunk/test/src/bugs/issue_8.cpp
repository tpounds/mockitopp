#include "tpunit++.hpp"
#include <mockitopp/mockitopp.hpp>

struct issue_8 : tpunit::TestFixture
{
   issue_8() : tpunit::TestFixture
   (
      TEST(issue_8::test_no_crash)
   )
   {}

   struct vbase
   {
      virtual void func() = 0;
   };

   struct vderived : virtual vbase { };

   void test_no_crash()
   {
      mockitopp::mock_object<vderived> mock;
      mock(&vderived::func).when().thenReturn();
      ASSERT_NO_THROW(mock.getInstance().func());
   }
} issue_8__;
