
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

    def __repr__(self):
	return "%s('%s')" % (self.__class__.__name__, self.obj)

def annotated(obj, annot):
    try:
	obj.annots += annot
    except Exception, ex:
	class AnnotHolder(obj.__class__):
	    pass
	new_obj = AnnotHolder(obj)
	new_obj.annots = annot
	return new_obj

class NoRuntimeAnnotation:
    def __init__(self):
	pass

def NoRuntime(obj, **kwargs):
    return annotated(obj, [NoRuntimeAnnotation(**kwargs)])

class Source:
    def __init__(self, dirname, filename):
	self.dirname = dirname
	self.filename = filename
    def __repr__(self):
	return "Source('%s/%s')" % (self.dirname, self.filename)

def package(name):
    global __package_tree, __package
    __package = __package_tree
    for pkg in name.split('.'):
	if not __package.has_key(pkg):
	    __package[pkg] = mybuild_prot.Package(pkg, __package)
	__package = __package[pkg]

def module(name, *args, **kargs):
    global __package
    global __dirname
    if kargs.has_key('sources'):
	kargs['sources'] = map (lambda s: Source(__dirname, s), kargs['sources'])
    mybuild_prot.module_package(__package, name, *args, **kargs)

if __name__ == '__main__':
    global __package_tree
    __package_tree = mybuild_prot.Package('root', None)

    import sys, os
    for arg in sys.argv[1:]:
	for dirpath, dirnames, filenames in os.walk(arg):
	    for file in filenames:
		if file.endswith('.py') or file == 'Pybuild':
		    glob = globals()
		    glob['__dirname'] = dirpath
		    locl = {}
		    execfile(os.path.join(dirpath, file), glob)
		    print glob['__package_tree']
		    #print locl


