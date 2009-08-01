import Build.EnvironmentFactory, os, sys
env = Build.EnvironmentFactory.GetInstance()
Export('env')

if 'm4-generate' in COMMAND_LINE_TARGETS:
   env.AppendUnique(M4FLAGS = [
      '-I' + os.path.abspath(sys.path[0]) + '/include',
      # maximum supported virtual functions, increase for classes with large vtables
      '-DMOCKITOPP_MAX_VIRTUAL_FUNCTIONS=50',
      # maximum supported arity, increase for function signatures with larger number of arguments
      # boost::tuple supports 0-10 elements, so don't support arity > 11 with this implementation.
      '-DMOCKITOPP_MAX_VIRTUAL_FUNCTION_ARITY=11',
   ])
   Alias('m4-generate', [
      env.M4('include/mockitopp/detail/stubbing/OngoingStubbing.hpp.m4'),
      env.M4('include/mockitopp/detail/stubbing/Stub.hpp.m4'),
      env.M4('include/mockitopp/detail/utility/Function.hpp.m4')
   ])

test = SConscript('test/SConscript', build_dir='test/build', duplicate=0)
Clean('test', '#test/build')

thirdparty = SConscript('#3rdparty/SConscript', build_dir='3rdparty/build', duplicate=0)
Clean('3rdparty', '#3rdparty/build')

# vim:ft=python:
