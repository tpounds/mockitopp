## Argument Matching ##
Usually, test cases are required to cover a large permutation of user inputs. This can be troublesome in cases where the system under test has several underlying non-trivial dependencies. Non-trivial dependencies are those that are slow (network or disk I/O), flaky (connections to third-party services), or dependencies whose quality is volatile. All of these things are barriers to fast, dependable tests that whose legitimate failure are easy to diagnose.

Usually, when using a static mock framework to provide the dependencies for the system under test, each dependency will have to stubbed with 1:1 mappings of the user inputs. Overtime this makes test cases quite brittle and becomes a maintenance liability. To help reduce this overhead generic argument matchers are available (`<mockitopp/matchers>`) to use when stubbing method invocations. These matchers work with all primitive types, but do note that complex types (classes, etc) **must** implement operator==() correctly in order to be used. If your complex types do not implement operator==, you will get a somewhat messy compile error with lots of template expansion to sift through.

The best examples of how to use mockitopp are it's own test source code located in the test/ subdirectory. If you have problems using the examples below, study the test source code.

### Built-in ###
```
#include <mockitopp/mockitopp.hpp>

using mockitopp::matcher::null;
using mockitopp::matcher::any;
using mockitopp::matcher::equal;
using mockitopp::matcher::is_not;

// this is a micro-test framework, real projects should use 
// cgreen, Catch, Boost::Unit, gtest, or some other framework
#include <cassert>
#define ASSERT_TRUE(expr) assert( (expr) == true )
#define ASSERT_FALSE(expr) assert( (expr) == false )
#define ASSERT_THROW(expr, exception) do {                      \
        try {                                                   \
            expr;                                               \
            assert(! #expr " did not throw " #exception);       \
        } catch (exception& ex) {                               \
        } catch (exception* ex) {                               \
        } catch (...) {                                         \
            assert(! #expr " did throw unknown exception");     \
        }                                                       \
    } while(0)

struct interface
{
    virtual bool func1(int*) = 0;
    virtual bool func2(const std::string&) = 0;
    virtual bool func3(int) = 0;
};

int main()
{
    mockitopp::mock_object<interface> mock;

    // first expectation
    mock(&interface::func1)
        .when(null<int*>())
        .thenReturn(true);

    // second expectation
    mock(&interface::func1)
        .when(any<int*>())
        .thenReturn(false);

    // third expectation
    mock(&interface::func2)
        .when(is_not(equal<const std::string&>("foo")))
        .thenReturn(true);

    interface& obj = mock.getInstance();

    int value = 31337;
    ASSERT_TRUE(obj.func1(NULL));
    ASSERT_FALSE(obj.func1(&value));
    ASSERT_TRUE(obj.func2("hello world!"));
    ASSERT_TRUE(obj.func2("bar"));
    ASSERT_THROW(obj.func3(7), mockitopp::missing_implementation_exception);

    return 0;
}
```

The first expectation set is that our mocked instance of the `interface` type will have `func1(int*)` called with a `NULL`. If it gets called with something other than `NULL`, the mocked instance will throw an exception. This is fantastic for debugging when there are regressions in the way your code interacts with it's collaborators. When the expectation fails, the stack trace in the debugger tells you **exactly** where the incorrect input came from as it happened -- not with log messages are the fact. This makes not only for easy-to-read tests as documentation, but fast debugging cycles when your tests do fail.

The `null<T>` matcher is an interesting one, in that one typically will combine is with the `is_not()` modifier. This can be useful when the exact pointer value being passed in is not reasonably known to the test due to proper encapsulation -- it just needs to not be `NULL`.

The second expectation set on our mocked instance of the `interface` type uses the `any<T>` matcher. This is a way to say "we don't care what the value is". This can be useful for focusing the reader of the test on what is relevant to the given test. By over-specifying exact values for all parameters to mocked methods, we are may be over-communicating and making it harder to determine what's relevant to the exact scenario and action (GivenWhenThen) versus others in the suite. Also, over-specification in mocks can make them more brittle. When a regression occurs, more tests may fail at once, creating noise for the developer to sift through. In addition, over-specification can mean changes in the implementation that require more tests and mock expectations need to be updated. So, keeping tests and mock expectations focused on the "simplest thing that could possible work" to pin down relevant behavior and protect against regressions is highly recommended -- the `any<>` matcher is one of the great tools to accomplish that. Keep in mind that even with the any<> matcher, types need to implement `operator==()`; if they don't, you'll get a compile error.

The third expectation uses the `equal<>` matcher, combined with the `is_not()` modifier. Note that the template parameter, `const std::string&`, matches the `interface::func2` signature **exactly**. If there is even a slight mismatch -- a missing const, value instead of reference, etc -- then a compile error will occur. Also, if the type supplied in the `thenReturn()` clause does not match the mocked method signature, you will get a similar compile error.


### [TR1 &lt;regex&gt;](http://www.boost.org/doc/libs/1_36_0/libs/regex/doc/html/index.html) ###
```
#include <boost/regex.hpp> // or <regex>
#include <mockitopp/mockitopp.hpp>
#include <mockitopp/matchers/regex.hpp>

using mockitopp::matcher::regex;

#include <cassert>
#define ASSERT_TRUE(expr) assert( (expr) == true )
#define ASSERT_FALSE(expr) assert( (expr) == false )
#define ASSERT_THROW(expr, exception) do {                      \
        try {                                                   \
            expr;                                               \
            assert(! #expr " did not throw " #exception);       \
        } catch (exception& ex) {                               \
        } catch (exception* ex) {                               \
        } catch (...) {                                         \
            assert(! #expr " did throw unknown exception");     \
        }                                                       \
    } while(0)

struct interface
{
    virtual bool func(const char*) = 0;
};

int main()
{
    mockitopp::mock_object<interface> mock;
    // the following line incorrectly fails on GCC <= 4.8.1
    mock(&interface::func).when(regex("[0-9]*")).thenReturn(true);
    mock(&interface::func).when(regex("he.*ld")).thenReturn(true);
    interface& obj = mock.getInstance();

    ASSERT_TRUE(obj.func("1234567890"));
    ASSERT_TRUE(obj.func("hello world"));
    ASSERT_THROW(obj.func("foo"), mockitopp::partial_implementation_exception);

    return 0;
}
```

GNU g++ versions <= 4.8.1 do not have a fully functional regular expression library. Using the boost regular expression library may be preferred.