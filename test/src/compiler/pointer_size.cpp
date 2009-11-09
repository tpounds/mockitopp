#include <gtest/gtest.h>

TEST(compiler_pointer_size, data_code_pointer)
{
   ASSERT_EQ(sizeof(void*), sizeof(void (*)()));
}
