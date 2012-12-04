
import mybuild_prot

class Package:
    def __init__(self, name, parent):
	self.name = name
	self.parent = parent

class Annotated():
    def __init__(self, obj, anns):
	self.obj = obj
	self.anns = anns

def annotated(obj, anns):
    if isinstance(obj, Annotated):
	obj.anns += anns
	return obj
    return Annotated(obj, anns)

def NoRuntime(obj):
    return annotated(obj, ['NoRuntime'])

def package(name):
    global __package_tree, __package
    last_pkg = None 
    for pkg in name.split('.'):
	if not __package_tree.has_key(pkg):
	    __package_tree[pkg] = Package(pkg, last_pkg)
	last_pkg = __package_tree[pkg]
    __package = last_pkg

def module(name, *args, **kargs):
    global __package
    __package.__dict__[name] = mybuild_prot.Module(name, *args, **kargs)

if __name__ == '__main__':
    global __package_tree
    __package_tree = {}

    import sys
    for arg in sys.argv[1:]:
	glob = globals()
	locl = {}
	execfile(arg, glob)
	#print glob
	#print locl


