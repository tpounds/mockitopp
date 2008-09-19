import Build.EnvironmentFactory
env = Build.EnvironmentFactory.GetInstance()
Export('env')

test = SConscript('test/SConscript', build_dir='test/build', duplicate=0)
Clean('test', '#test/build')

thirdparty = SConscript('#3rdparty/SConscript', build_dir='3rdparty/build', duplicate=0)
Clean('3rdparty', '#3rdparty/build')

# vim:ft=python:
