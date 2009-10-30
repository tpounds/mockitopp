#include <gtest/gtest.h>
#include <mockitopp/mockitopp.hpp>

using mockitopp::mock_object;

struct cv_interface
{
   virtual int __no_cv();
   virtual int __has_c() const;
   virtual int __has_cv() const volatile;
};

TEST(test_mfp_cv, compile)
{
   mock_object<cv_interface> mock;
   mock(&cv_interface::__no_cv).when().thenReturn(0);
   mock(&cv_interface::__has_c).when().thenReturn(0);
   mock(&cv_interface::__has_cv).when().thenReturn(0);
   cv_interface& obj = mock.getInstance();

   ASSERT_EQ(0, obj.__no_cv());
   ASSERT_EQ(0, obj.__has_c());
   ASSERT_EQ(0, obj.__has_cv());
}
