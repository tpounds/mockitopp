from SCons.Script.SConscript import SConsEnvironment

def Test(target, source, env):
   import os
   from subprocess import Popen
   # TODO: fix LD_LIBRARY_PATH construction
   proc = Popen(source[0].abspath, env={'LD_LIBRARY_PATH': '3rdparty/build'})
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
      self['BUILDERS']['Test'] = self.Builder(action = self.Action(Test, TestString),
                                              suffix = '.dummy',
                                              src_suffix = self['PROGSUFFIX'])
