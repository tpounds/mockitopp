#include <gtest/gtest.h>

TEST(compiler_alignment, struct_types)
{
   struct __bool_char_got { bool b; char c; };
   struct __bool_char_exp { char c[2]; };
   ASSERT_EQ(sizeof(__bool_char_exp), sizeof(__bool_char_got));

   struct __bool_int_got { bool b; int i; };
   struct __bool_int_exp { int i[2]; };
   ASSERT_EQ(sizeof(__bool_int_exp), sizeof(__bool_int_got));

   struct __bool_long_got { bool b; long l; };
   struct __bool_long_exp { long l[2]; };
   ASSERT_EQ(sizeof(__bool_long_exp), sizeof(__bool_long_got));

   struct __bool_dataptr_got { bool b; void* v; };
   struct __bool_dataptr_exp { void* v[2]; };
   ASSERT_EQ(sizeof(__bool_dataptr_exp), sizeof(__bool_dataptr_got));
}

TEST(compiler_alignment, vtable)
{
   struct vtable0 { virtual ~vtable0() = 0; };
   struct vtable1 { virtual ~vtable1() = 0; };
   struct vtable2 { virtual ~vtable2() = 0; };
   struct vtable3 { virtual ~vtable3() = 0; };

   struct __vtable1_got : vtable0 {};
   struct __vtable1_exp { void* v[1]; };
   ASSERT_EQ(sizeof(__vtable1_exp), sizeof(__vtable1_got));

   struct __vtable2_got : vtable0, vtable1 {};
   struct __vtable2_exp { void* v[2]; };
   ASSERT_EQ(sizeof(__vtable2_exp), sizeof(__vtable2_got));

   struct __vtable3_got : vtable0, vtable1, vtable2 {};
   struct __vtable3_exp { void* v[3]; };
   ASSERT_EQ(sizeof(__vtable3_exp), sizeof(__vtable3_got));

   struct __vtable4_got : vtable0, vtable1, vtable2, vtable3 {};
   struct __vtable4_exp { void* v[4]; };
   ASSERT_EQ(sizeof(__vtable4_exp), sizeof(__vtable4_got));
}
