import BaseEnvironment
import os

class Environment(BaseEnvironment.Environment):
   def __init__(self, **kw):
      apply(BaseEnvironment.Environment.__init__, (self,), kw)

      self.ConfigureCompiler()

   def ConfigureCompiler(self):
      cxx = self.WhereIs(self['CXX'])
      cxx_bin = os.path.basename(cxx).lower()
      cxx_dir = os.path.dirname(cxx)

      if cxx_bin.startswith("g++"):
         self.AppendUnique(CXXFLAGS=['-Wall'])
