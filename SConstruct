env = Environment(CPPPATH=['#cpp', '#3rdparty/UnitTest++/src'],
                  LIBPATH=['#3rdparty/UnitTest++', '#cpp/build'])
Export('env')

cpp = env.SConscript('cpp/SConscript',  build_dir='cpp/build', duplicate=0)
Clean('cpp', '#cpp/build')

test = env.SConscript('test/SConscript', build_dir='test/build', duplicate=0)
Clean('test', '#test/build')

# vim:ft=python:
