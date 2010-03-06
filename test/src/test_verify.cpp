#include <gtest/gtest.h>
#include <mockitopp/mockitopp.hpp>

using mockitopp::mock_object;

struct verify_interface
{
   virtual void func() = 0;
};

#define VERIFY_MOCK_DEFINITION \
   mock_object<verify_interface> mock; \
   mock(&verify_interface::func).when().thenReturn(); \
   verify_interface& obj = mock.getInstance(); \
\
   obj.func(); \
   obj.func(); \
   obj.func();

TEST(test_verify, atLeast)
{
   VERIFY_MOCK_DEFINITION

   ASSERT_TRUE(mock(&verify_interface::func).atLeast(1));
   ASSERT_TRUE(mock(&verify_interface::func).atLeast(2));
   ASSERT_TRUE(mock(&verify_interface::func).atLeast(3));
   ASSERT_FALSE(mock(&verify_interface::func).atLeast(4));
}

TEST(test_verify, atMost)
{
   VERIFY_MOCK_DEFINITION

   ASSERT_FALSE(mock(&verify_interface::func).atMost(1));
   ASSERT_FALSE(mock(&verify_interface::func).atMost(2));
   ASSERT_TRUE(mock(&verify_interface::func).atMost(3));
   ASSERT_TRUE(mock(&verify_interface::func).atMost(4));
}

TEST(test_verify, between)
{
   VERIFY_MOCK_DEFINITION

   ASSERT_FALSE(mock(&verify_interface::func).between(0, 2));
   ASSERT_FALSE(mock(&verify_interface::func).between(4, 9));
   ASSERT_TRUE(mock(&verify_interface::func).between(1, 5));
   ASSERT_TRUE(mock(&verify_interface::func).between(3, 3));
}

TEST(test_verify, exactly)
{
   VERIFY_MOCK_DEFINITION

   ASSERT_FALSE(mock(&verify_interface::func).exactly(1));
   ASSERT_FALSE(mock(&verify_interface::func).exactly(2));
   ASSERT_TRUE(mock(&verify_interface::func).exactly(3));
   ASSERT_FALSE(mock(&verify_interface::func).exactly(4));
}

TEST(test_verify, never)
{
   VERIFY_MOCK_DEFINITION

   ASSERT_FALSE(mock(&verify_interface::func).never());
}