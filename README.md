## Mockitopp [![Build Status](https://travis-ci.org/tpounds/mockitopp.svg?branch=master)](https://travis-ci.org/tpounds/mockitopp)
A C++ mocking framework inspired by the ideas developed for [Mockito](https://github.com/mockito/mockito) written by [Szczepan Faber, et al](http://monkeyisland.pl/). The purpose is to provide similar construction semantics for creating mock objects leading to smaller, more readable test cases. It is designed to be a lightweight framework allowing you to mock dependencies for a system under test using a simple descriptive domain specific language. The goal is to help create simpler, less brittle test cases; ultimately, leading to less maintenance overhead in the future.

## Documentation
Basic usage examples and other information can be found in the [wiki](../../wiki) documentation.

1. [Stubbing](../../wiki/Stubbing)
1. [Behavior Verification](../../wiki/BehaviorVerification)
1. [Argument Matching](../../wiki/ArgumentMatching)
1. [Common Issues](../../wiki/CommonIssues)
1. [Supported Compilers](../../wiki/SupportedCompilers)

## How does it work?
MockitoPP uses ABI and template techniques to create mock delegate classes that intercept calls intended for any abstract base class you care to model. The techniques used to construct the mock objects are similar to the techniques used by [Automatic Mock Object for C++ (amop)](http://code.google.com/p/amop/), [Hippo Mocks](http://www.assembla.com/wiki/show/hippomocks), and [Member Function Pointers and the Fastest Possible C++ Delegates](http://www.codeproject.com/KB/cpp/FastDelegate.aspx). By exploiting the compiler's ABI class layout we can dynamically construct a mock delegate class to provide minimal stubbed functionality used during unit testing.

## Limitations
This framework really only supports pure virtual abstract base classes (i.e. interface). The mocking construction only works for virtual functions declared in the target class to mock. You cannot use it to stub calls to non-virtual functions. In some cases it may be possible to mock a class that is not a pure abstract base class (i.e. hybrid class containing both virtual and non-virtual functions), but you may encounter unexpected results if other objects are expecting the mock object to operate under normal circumstances (i.e. maintain state) or have internal wired dependencies that operate on the object's state.
