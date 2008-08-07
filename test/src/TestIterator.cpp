#include <UnitTest++.h>

#include <mockitopp/MockObject.hpp>

using mockitopp::MockObject;

template <typename T>
struct Iterator
{
   virtual T next() = 0;
};
TEST(TestIterator)
{
   typedef Iterator<int> it_type;
   MockObject<it_type> mock;
   mock.stub(&it_type::next).arguments().returns(0)
                                        .returns(1)
                                        .returns(2)
                                        .returns(3)
                                        .returns(4);
   it_type& i = mock.getMock();

   CHECK(0 == i.next());
   CHECK(1 == i.next());
   CHECK(2 == i.next());
   CHECK(3 == i.next());
   CHECK(4 == i.next());
   CHECK(4 == i.next());
   CHECK(mock.verifyExactly(&it_type::next, 6));
}
