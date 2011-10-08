#include "tpunit++.hpp"
#include <mockitopp/mockitopp.hpp>

struct test_mfp_cv : tpunit::TestFixture
{
   test_mfp_cv() : tpunit::TestFixture
   (
      TEST(test_mfp_cv::compile)
   )
   {}

   struct cv_interface
   {
      virtual int __no_cv();
      virtual int __has_c() const;
      virtual int __has_cv() const volatile;
   };

   void compile()
   {
      mockitopp::mock_object<cv_interface> mock;
      mock(&cv_interface::__no_cv).when().thenReturn(0);
      mock(&cv_interface::__has_c).when().thenReturn(0);
      mock(&cv_interface::__has_cv).when().thenReturn(0);
      cv_interface& obj = mock.getInstance();

      ASSERT_EQUAL(0, obj.__no_cv());
      ASSERT_EQUAL(0, obj.__has_c());
      ASSERT_EQUAL(0, obj.__has_cv());
   }
} __test_mfp_cv;
