import os
env = Environment(CXX=os.getenv('CXX', Environment()['CXX']),
                  CPPPATH=['#cpp', '#3rdparty/boost_headers_1_35_0','#3rdparty/UnitTest++/src'],
                  LIBPATH=['#3rdparty/build'])
Export('env')

test = env.SConscript('test/SConscript', build_dir='test/build', duplicate=0)
Clean('test', '#test/build')

thirdparty = env.SConscript('#3rdparty/SConscript', build_dir='3rdparty/build', duplicate=0)
Clean('3rdparty', '#3rdparty/build')

# vim:ft=python:
