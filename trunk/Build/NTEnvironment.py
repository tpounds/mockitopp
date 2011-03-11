import BaseEnvironment
import re
import os
from subprocess import Popen, PIPE, STDOUT

class Environment(BaseEnvironment.Environment):
   def __init__(self, **kw):
      apply(BaseEnvironment.Environment.__init__, (self,), kw)

      self.ConfigureCompiler()

      self['ENV']['INCLUDE'] = self['CPPPATH']
      self['ENV']['LIB'] = self['LIBPATH']
      self['ENV']['PATH'] = os.environ['PATH']

   def ConfigureCompiler(self):
      cxx = self.WhereIs(self['CXX'])
      cxx_bin = os.path.basename(cxx).lower()
      cxx_dir = os.path.dirname(cxx)

      if cxx_bin.startswith("cl"):
         common = cxx_dir + "\..\.."
         if os.path.exists(common + "\Common\IDE"):
           os.environ['PATH'] = common + "\Common\IDE" + ";" + cxx_dir
         elif os.path.exists(common + "\Common7\IDE"):
           os.environ['PATH'] = common + "\Common7\IDE" + ";" + cxx_dir

         proc = Popen(cxx_bin, stderr=STDOUT, stdout=PIPE)
         proc.wait()
         version = "".join(proc.stdout.readlines())

         if re.search("Version 12\.00", version):
            raise EnvironmentError("Microsoft Visual C++ (6.0) Unsupported!")
         elif re.search("Version 13\.00", version):
            print "Microsoft Visual C++ .NET 2002 (7.0) Detected"
         elif re.search("Version 13\.10", version):
            print "Microsoft Visual C++ .NET 2003 (7.1) Detected"
         elif re.search("Version 14\.00", version):
            print "Microsoft Visual C++ 2005 (8.0) Detected"
         elif re.search("Version 15\.00", version):
            print "Microsoft Visual C++ 2008 (9.0) Detected"
         elif re.search("Version 16\.00", version):
            print "Microsoft Visual C++ 2010 (10.0) Detected"
         else:
            raise EnvironmentError("Unknown Microsoft Visual C++ Detected!")

         # XXX: BOOST_ALL_NO_LIB prevents MSVC from auto-linking a non-existent library
         self.AppendUnique(CXXFLAGS = ['/EHsc', '/GR', '/DBOOST_ALL_NO_LIB'])
         self['CXX'] = cxx_bin
#         self['LINK'] = "link.exe"
         self['CPPPATH'] = os.path.abspath(cxx_dir + "\..\include")
         self['LIBPATH'] = os.path.abspath(cxx_dir + "\..\lib")

         sdk_dir = ""
         if os.getenv('MicrosoftPlatformSDK', None) != None:
            sdk_dir = os.environ['MicrosoftPlatformSDK']
         # standard MSVC++ relative install
         elif os.path.exists(cxx_dir + "\..\PlatformSDK"):
            sdk_dir = cxx_dir + "\..\PlatformSDK"
         #TODO: handle directory not found

         if os.path.exists(sdk_dir + "\include\windows.h"):
            self.AppendUnique(CPPPATH=[sdk_dir + "\include"])
            self.AppendUnique(LIBPATH=[sdk_dir + "\lib"])
         #TODO: handle windows.h not found

      elif cxx_bin.startswith("g++"):
         os.environ['PATH'] = cxx_dir
         proc = Popen(cxx_bin + " --version", stderr=STDOUT, stdout=PIPE)
         proc.wait()
         version = "".join(proc.stdout.readlines())

         match = re.search("\(GCC\) (\d.\d.\d)", version)
         if match:
            print "MinGW " + match.group(1) + " Detected"
         # TODO: handle unsupported mingw version

         self.Tool('mingw')
         if '/nologo' in self['CCFLAGS']:
            self['CCFLAGS'].remove('/nologo')

         self.AppendUnique(CXXFLAGS=['-Wall'])
         self.AppendUnique(CPPPATH=[os.path.abspath(cxx_dir + "\..\include")])
         self.AppendUnique(LIBPATH=[os.path.abspath(cxx_dir + "\..\lib")])
