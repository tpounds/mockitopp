import os
import NTEnvironment
import POSIXEnvironment

def Environment():
   if os.name == 'nt':
      return NTEnvironment.Environment()
   elif os.name == 'posix':
      return POSIXEnvironment.Environment()
   else:
      raise EnvironmentError("Unsupported host environment: " + ", ".join(os.uname()))
