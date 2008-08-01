#ifndef __MOCKITOPP_CONFIGURATION_HPP__
#define __MOCKITOPP_CONFIGURATION_HPP__

// XXX: This is set arbitrarily high on purpose, in a good
//      design an interface should have this many functions.
#define MAX_VIRTUAL_FUNCTIONS 50

// XXX: boost::tuple only supports 0-10 elements, so we
//      can't have a value > 11 with this implementation.
//      Heopfully, no one needs a function with > 10
//      arguments; that would just be silly.
#define MAX_VIRTUAL_FUNCTION_ARITY 11

#endif //__MOCKITOPP_CONFIGURATION_HPP__
