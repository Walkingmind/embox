
__author__ = "Anton Kozlov"
__date__ = "2012-12-12"

from mybuild import module as mybuild_module, option
from mybuild.constraints import Constraints

import common.pkg

import types

def root_pkg():
    return types.ModuleType('root')

def package(name):
    import sys
    import config
   
    pkg = config.root

    for subpkg in name.split('.'):
	if not hasattr(pkg, name):
	    pkg.__dict__[name] = types.ModuleType(subpkg)
	pkg = getattr(pkg, name)

    global this_pkg
    this_pkg = pkg

def module(name, *args, **kargs):
    def mod_dec(name_overwrite):
	def f(fn):
	    fn.__name__ = name_overwrite
	    return mybuild_module(fn)

	return f

    @mod_dec(name)
    def new_mod(self):
	pass

    this_pkg.__dict__[name] = new_mod

def prepare_build(root):
    modlist = common.pkg.modlist(root, types.ModuleType, mybuild_module, lambda pkg: pkg.__dict__.items())
    print '\n'.join(modlist)
    return modlist
