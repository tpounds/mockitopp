import BaseEnvironment
import os

class Environment(BaseEnvironment.Environment):
   def __init__(self, **kw):
      apply(BaseEnvironment.Environment.__init__, (self,), kw)

      self.ConfigureCompiler()

   def ConfigureCompiler(self):
      cxx = os.path.basename(self['CXX'])

      if cxx.startswith("clang") or cxx.startswith("g++"):
         self.AppendUnique(CXXFLAGS=['-Wall', '-pedantic', '-g'])
