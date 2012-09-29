from SCons.Script.SConscript import SConsEnvironment
import os
import subprocess

def Test(target, source, env):
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
