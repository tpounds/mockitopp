#include "tpunit++.hpp"
#include <mockitopp/mockitopp.hpp>

struct test_multiple_inheritance : tpunit::TestFixture
{
   test_multiple_inheritance() : tpunit::TestFixture
   (
      TEST(test_multiple_inheritance::unsupported_interface)
   )
   {}

   struct interface1 { virtual bool foo1(int) = 0; };
   struct interface2 { virtual bool foo2(int) = 0; };
   struct interface3 { virtual bool foo3(int) = 0; };

   // XXX: multiple inheritance is unsupported due to the use of multiple
   //      vtables i.e. sizeof(unsupported_interface) == 3 * sizeof(void*)
   struct __unsupported_interface : public interface1, public interface2, public interface3 {};

   void unsupported_interface()
   {
      mockitopp::mock_object<__unsupported_interface> mock;
      mock(&__unsupported_interface::foo1).when(1234).thenReturn(true);
      mock(&__unsupported_interface::foo1).when(5678).thenReturn(false);
      mock(&__unsupported_interface::foo2).when(1234).thenReturn(true);
      mock(&__unsupported_interface::foo2).when(5678).thenReturn(false);
      mock(&__unsupported_interface::foo3).when(1234).thenReturn(true);
      mock(&__unsupported_interface::foo3).when(5678).thenReturn(false);
      __unsupported_interface& obj = mock.getInstance();

      ASSERT_EQUAL(true, obj.foo1(1234));
      ASSERT_EQUAL(false, obj.foo1(5678));
      // XXX: assert segmentation faults
//      ASSERT_DEATH(obj.foo2(1234), "");
//      ASSERT_DEATH(obj.foo2(5678), "");
//      ASSERT_DEATH(obj.foo3(1234), "");
//      ASSERT_DEATH(obj.foo3(5678), "");
   }
} __test_multiple_inheritance;
