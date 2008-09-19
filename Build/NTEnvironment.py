import BaseEnvironment

class Environment(BaseEnvironment.Environment):
   def __init__(self, **kw):
      apply(BaseEnvironment.Environment.__init__, (self,), kw)
