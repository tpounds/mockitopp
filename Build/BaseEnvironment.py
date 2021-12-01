from SCons.Script.SConscript import SConsEnvironment
import os
import subprocess

def Test(target, source, env):
   print "YYY: " + str(source[0])
   print "YYY: " + str(source[0].abspath)
   print "YYY: " + os.path.normpath(str(source[0]))
   print "YYY: " + os.path.abspath(str(source[0]))
   print "YYY: " + os.path.abspath('.')

   print "ZZZ: " + os.getcwd()
   print "ZZZ: " + os.path.abspath(os.getcwd())
   print "ZZZ: " + " ".join(os.listdir('.'))
   print "ZZZ: " + " ".join(os.listdir('test'))
   print "ZZZ: " + " ".join(os.listdir('test\build'))

   proc = subprocess.Popen(source[0].abspath)
   proc.wait()
   print "\n============================="
   if proc.returncode:
      print "Result - FAILED!\n" \
            "============================="
      return 1
   print "Result - PASSED!\n" \
         "============================="
   return 0

def TestString(target, source, env):
   return "=============================\n" \
          "= Unit Test(s) - " + source[0].name + "\n" \
          "=============================\n"

class Environment(SConsEnvironment):
   def __init__(self, **kw):
      apply(SConsEnvironment.__init__, (self,), kw)
      self['CXX'] = os.getenv('CXX', self['CXX'])
      self['CXXFLAGS'] = os.getenv('CXXFLAGS', self['CXXFLAGS'])
      self['LINKFLAGS'] = os.getenv('LDFLAGS', self['LINKFLAGS'])
      self['BUILDERS']['Test'] = self.Builder(action = self.Action(Test, TestString),
                                              suffix = '.dummy',
                                              src_suffix = self['PROGSUFFIX'])
