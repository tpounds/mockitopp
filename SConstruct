import Build, os, sys

env = Build.Environment()
Export('env')

if 'm4' in COMMAND_LINE_TARGETS:
   env.AppendUnique(M4FLAGS = [
      '-I' + os.path.abspath(sys.path[0]) + '/include',
      # maximum supported virtual functions, increase for classes with large vtables
      '-DMOCKITOPP_MAX_VIRTUAL_FUNCTIONS=100',
      # maximum supported arity, increase for function signatures with more arguments
      '-DMOCKITOPP_MAX_VIRTUAL_FUNCTION_ARITY=20',
   ])
   Alias('m4', [
      env.M4('include/mockitopp/detail/stubbing/dynamic_object.hpp.m4'),
      env.M4('include/mockitopp/detail/stubbing/dynamic_vfunction.hpp.m4'),
      env.M4('include/mockitopp/detail/stubbing/proxy_vfunction.hpp.m4'),
      env.M4('include/mockitopp/detail/util/remove_member_function_pointer_cv.hpp.m4'),
      env.M4('include/mockitopp/detail/util/tr1_tuple.hpp.m4')
   ])

test = SConscript('test/SConscript', variant_dir='test/build', duplicate=0)
Clean('test', '#test/build')
