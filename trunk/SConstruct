import Build.EnvironmentFactory
env = Build.EnvironmentFactory.GetInstance()
Export('env')

if 'm4-generate' in COMMAND_LINE_TARGETS:
   env.AppendUnique(M4FLAGS = ['-I/home/tlbs/src/mockitopp/include'])
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
