#include <gtest/gtest.h>
#include <mockitopp/MockObject.hpp>

using mockitopp::MockObject;

template <typename T>
struct IteratorInterface
{
   virtual T next() = 0;
};
TEST(TestIterator, IteratorInterface)
{
   typedef IteratorInterface<int> it_type;
   MockObject<it_type> mock;
   mock.when(&it_type::next)().thenReturn(0)
                              .thenReturn(1)
                              .thenReturn(2)
                              .thenReturn(3)
                              .thenReturn(4);
   it_type& i = mock.getMock();

   ASSERT_EQ(0, i.next());
   ASSERT_EQ(1, i.next());
   ASSERT_EQ(2, i.next());
   ASSERT_EQ(3, i.next());
   ASSERT_EQ(4, i.next());
   ASSERT_EQ(4, i.next());
   ASSERT_TRUE(mock.verifyExactly(&it_type::next, 6));
}
