#include "tpunit++.hpp"
#include <mockitopp/mockitopp.hpp>

using namespace mockitopp;
using namespace mockitopp::matcher;

namespace issue_7_ns
{
    struct iface1 {};

    struct iface2
    {
       virtual void func(iface1&) = 0;
    };

    bool operator==(issue_7_ns::iface1&, issue_7_ns::iface1&) { return true; }
}

bool eq(issue_7_ns::iface1& lhs, issue_7_ns::iface1& rhs) { return lhs == rhs; }

struct issue_7 : tpunit::TestFixture
{
   issue_7() : tpunit::TestFixture
   (
      TEST(issue_7::test_should_compile)
   )
   {}

   void test_should_compile()
   {
      mock_object<issue_7_ns::iface2> mock;
      mock(&issue_7_ns::iface2::func).when(any<issue_7_ns::iface1&>()).thenReturn();
      issue_7_ns::iface2& obj = mock.getInstance();

      issue_7_ns::iface1 arg;
      ASSERT_NO_THROW(obj.func(arg));
   }
} issue_7__;
