import BaseEnvironment
import re
from subprocess import Popen, PIPE, STDOUT

class Environment(BaseEnvironment.Environment):
   def __init__(self, **kw):
      apply(BaseEnvironment.Environment.__init__, (self,), kw)
      self.DetectEnvironment()

   def DetectEnvironment(self):
      # TODO: check Microsoft Platform SDK

      proc = Popen(self['CC'], stderr=STDOUT, stdout=PIPE)
      proc.wait()
      version = "".join(proc.stderr.readlines())

      # configure compiler version
      if re.compile("Version 13\.10").search(version):
         self.Configure_MSVC_7_1()
      elif re.compile("Version 14\.00").search(version):
         self.Configure_MSVC_8_0()
      elif re.compile("Version 15\.00").search(version):
         self.Configure_MSVC_9_0()
      # TODO: MINGW
      # TODO: raise error otherwise

      if re.compile("Microsoft").search(version):
         self.AppendUnique(CCFLAGS = "/EHsc")

   # Microsoft Visual C++ .NET 2003 (7.1)
   def Configure_MSVC_7_1(self):
      binpath = os.path.dirname(self['CXX'])
      self['LINK'] = binpath + "\link.exe"
      print "MSVC 7.1 Detected"

   # Microsoft Visual C++ 2005 (8.0)
   def Configure_MSVC_8_0(self):
      print "MSVC 8.0 Detected"

   # Microsoft Visual C++ 2008 (9.0)
   def Configure_MSVC_9_0(self):
      print "MSVC 9.0 Detected"
