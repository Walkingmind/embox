"""
Python-like loader which is able to customize default global namespace.
"""

import sys

from . import mybuild_importer

from ..util.importlib.machinery import SourceFileLoader
from ..util.compat import *


FILENAME = 'Pybuild'

@mybuild_importer.loader_for(FILENAME)
class PybuildFileLoader(SourceFileLoader):
    """Loads Pybuild files and executes them as regular Python scripts.

    Upon creation of a new module initializes its namespace with defaults taken
    from the dictionary passed in __init__. Also adds a global variable
    pointing to a module corresponding to the namespace root.
    """

    def __init__(self, ctx, fullname, path):
        super(PybuildFileLoader, self).__init__(fullname, path)
        self._defaults = dict((key, value)
                              for key, value in iteritems(ctx.defaults)
                              if key[0] != '!')

    def is_package(self, fullname):
        return False

    def _init_module(self, module):
        fullname = module.__name__

        module.__dict__.update(self._defaults)

        namespace_root, dot, _ = fullname.partition('.')
        if dot:
            setattr(module, namespace_root, sys.modules[namespace_root])

        super(PybuildFileLoader, self)._init_module(module)

