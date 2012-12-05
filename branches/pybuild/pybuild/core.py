
import mybuild_prot
from mybuild_prot import one_or_many
from mybuild_prot import Integer, Boolean, String

class Annotation():
    def __init__(self, obj):
	self.obj = obj

    def get_obj(self):
	if isinstance(self.obj, Annotation):
	    return self.obj.get_obj()
	return self.obj

    def test(self, annot_class):
	if isinstance(self, annot_class):
	    return self
	elif isinstance(self.obj, Annotation):
	    return self.obj.test(annot_class)
	else:
	    return None

class NoRuntime(Annotation):
    pass

class Empty(Annotation):
    pass

def package(name):
    global __package_tree, __package
    __package = __package_tree
    for pkg in name.split('.'):
	if not __package.has_key(pkg):
	    __package[pkg] = mybuild_prot.Package(pkg, __package)
	__package = __package[pkg]

def module(name, *args, **kargs):
    global __package
    mybuild_prot.module_package(__package, name, *args, **kargs)

if __name__ == '__main__':
    global __package_tree
    __package_tree = mybuild_prot.Package('root', None)

    import sys
    for arg in sys.argv[1:]:
	glob = globals()
	locl = {}
	execfile(arg, glob)
	print glob['__package_tree']
	#print locl


