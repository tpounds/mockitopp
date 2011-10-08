#include "tpunit++.hpp"

struct compiler_pointer_size : tpunit::TestFixture
{
   compiler_pointer_size() : tpunit::TestFixture
   (
      TEST(compiler_pointer_size::data_code_pointer)
   )
   {}

   void data_code_pointer()
   {
      ASSERT_EQUAL(sizeof(void*), sizeof(void (*)()));
   }
} __compiler_pointer_size;
