import os
import NTEnvironment
import POSIXEnvironment

def GetInstance():
   if os.name == 'nt':
      return NTEnvironment.Environment()
   elif os.name == 'posix':
      return POSIXEnvironment.Environment()
   # TODO: raise error otherwise
