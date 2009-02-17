#include <gtest/gtest.h>
#include <mockitopp/MockObject.hpp>

using mockitopp::MockObject;

struct iterator_interface
{
   virtual bool hasMore() = 0;
   virtual int next() = 0;
};

TEST(test_iterator_style, next)
{
   MockObject<iterator_interface> mock;
   mock(&iterator_interface::hasMore).when().thenReturn(true);
   mock(&iterator_interface::next).when().thenReturn(0)
                                         .thenReturn(1)
                                         .thenReturn(2)
                                         .thenReturn(3)
                                         .thenReturn(4);
   iterator_interface& obj = mock.getInstance();

   ASSERT_EQ(0, obj.next());
   ASSERT_EQ(1, obj.next());
   ASSERT_EQ(2, obj.next());
   ASSERT_EQ(3, obj.next());
   ASSERT_EQ(4, obj.next());
   ASSERT_EQ(4, obj.next());
}

TEST(test_iterator_style, hasMore)
{
   MockObject<iterator_interface> mock;
   mock(&iterator_interface::hasMore).when().thenReturn(true)
                                            .thenReturn(true)
                                            .thenReturn(true)
                                            .thenReturn(false);
   iterator_interface& obj = mock.getInstance();

   int loop = 0;
   while(obj.hasMore())
      { loop++; }
   ASSERT_EQ(loop, 3);
}

TEST(test_iterator_style, typical_use_case)
{
   MockObject<iterator_interface> mock;
   mock(&iterator_interface::hasMore).when().thenReturn(true)
                                            .thenReturn(true)
                                            .thenReturn(true)
                                            .thenReturn(true)
                                            .thenReturn(false);
   mock(&iterator_interface::next).when().thenReturn(0)
                                         .thenReturn(1)
                                         .thenReturn(2)
                                         .thenReturn(3)
                                         .thenReturn(4);
   iterator_interface& obj = mock.getInstance();

   int loop = 0;
   while(obj.hasMore())
   {
      ASSERT_EQ(loop, obj.next());
      loop++;
   }
   ASSERT_EQ(loop, 4);
}
