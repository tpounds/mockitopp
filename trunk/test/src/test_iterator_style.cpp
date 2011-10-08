#include "tpunit++.hpp"
#include <mockitopp/mockitopp.hpp>

struct test_iterator_style : tpunit::TestFixture
{
   test_iterator_style() : tpunit::TestFixture
   (
      TEST(test_iterator_style::next),
      TEST(test_iterator_style::hasMore),
      TEST(test_iterator_style::typical_use_case)
   )
   {}

   struct __iterator
   {
      virtual bool hasMore() = 0;
      virtual int next() = 0;
   };

   void next()
   {
      mockitopp::mock_object<__iterator> mock;
      mock(&__iterator::hasMore).when().thenReturn(true);
      mock(&__iterator::next).when().thenReturn(0)
                                    .thenReturn(1)
                                    .thenReturn(2)
                                    .thenReturn(3)
                                    .thenReturn(4);
      __iterator& obj = mock.getInstance();

      ASSERT_EQUAL(0, obj.next());
      ASSERT_EQUAL(1, obj.next());
      ASSERT_EQUAL(2, obj.next());
      ASSERT_EQUAL(3, obj.next());
      ASSERT_EQUAL(4, obj.next());
      ASSERT_EQUAL(4, obj.next());
      ASSERT_EQUAL(4, obj.next());
   }

   void hasMore()
   {
      mockitopp::mock_object<__iterator> mock;
      mock(&__iterator::hasMore).when().thenReturn(true)
                                       .thenReturn(true)
                                       .thenReturn(true)
                                       .thenReturn(false);
      __iterator& obj = mock.getInstance();

      int loop = 0;
      while(obj.hasMore())
         { loop++; }
      ASSERT_EQUAL(loop, 3);
   }

   void typical_use_case()
   {
      mockitopp::mock_object<__iterator> mock;
      mock(&__iterator::hasMore).when().thenReturn(true)
                                       .thenReturn(true)
                                       .thenReturn(true)
                                       .thenReturn(true)
                                       .thenReturn(false);
      mock(&__iterator::next).when().thenReturn(0)
                                    .thenReturn(1)
                                    .thenReturn(2)
                                    .thenReturn(3)
                                    .thenReturn(4);
      __iterator& obj = mock.getInstance();

      int loop = 0;
      while(obj.hasMore())
      {
         ASSERT_EQUAL(loop, obj.next());
         loop++;
      }
      ASSERT_EQUAL(loop, 4);
   }
} __test_iterator_style;
