
import sys
import os

sys.path.append(os.getcwd())

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

    def fullpath(self):
	return os.path.join(self.dirname, self.filename)

def package(name):
    global __package_tree, __package
    __package = name

    __package_tree.built_subpack(name)

def module(name, *args, **kargs):
    global __package
    global __dirname
    global __modlist
    if kargs.has_key('sources'):
	kargs['sources'] = map (lambda s: Source(__dirname, s), kargs['sources'])
    __modlist.append('.'.join ((__package, name)))
    mybuild_prot.module_package(__package_tree[__package], name, *args, **kargs)


def include(name, opts={}):
    global __modconstr
    __modconstr.append((name, mybuild_prot.Domain([True])))
    for opt_name, value in opts.items():
	__modconstr.append(("%s.%s" % (name, opt_name), mybuild_prot.Domain([value])))

def exclude(name):
    pass

def mybuild_main(argv):
    import os
    rootpkg = mybuild_prot.Package('root', None)
    allmodlist = []
    scope = mybuild_prot.Scope()

    glob = globals()

    glob['__package_tree'] = rootpkg
    glob['__modlist'] = allmodlist

    for arg in argv:
	for dirpath, dirnames, filenames in os.walk(arg):
	    for file in filenames:
		if file.endswith('.py') or file == 'Pybuild':
		    glob['__dirname'] = dirpath
		    execfile(os.path.join(dirpath, file), glob)

    #print rootpkg
    #print
    #print glob['__modlist']

    conf = 'pyconf/conf.py'

    glob['__scope'] = scope

    modlst = map(lambda name: glob['__package_tree'][name], glob['__modlist'])
    #print 
    #print modlst
    mybuild_prot.add_many(scope, modlst)

    glob['__modconstr'] = []

    execfile(conf, glob)

    modconstr = map(lambda (name, dom): (rootpkg[name], dom), glob['__modconstr'])

    #print 
    #print modconstr

    cut_scope = mybuild_prot.cut_many(scope, modconstr)
    final = mybuild_prot.fixate(cut_scope)
    #print
    #print final

    return final

from waflib.TaskGen import feature

@feature('module_header')
def header_gen(self):
    header = '''
#ifndef {GUARD}
#define {GUARD}

{INCLUDES}

{OPTIONS}

#endif /* {GUARD} */
'''
    options = []
    for name, opt in self.mod.items():
	repr = ''
	if isinstance(opt, mybuild_prot.Integer):
	    repr = 'NUMBER'
	elif isinstance(opt, mybuild_prot.Boolean):
	    repr = 'BOOLEAN'
	elif isinstance(opt, mybuild_prot.String):
	    repr = 'STRING'
	else:
	   continue

	options.append('OPTION_%s_%s %s' % (repr, opt.qualified_name().replace('.', '__'),
	    self.scope[opt].value()))

    hdr = header.format(GUARD=self.mod.qualified_name().replace('.', '_').upper(),
	    OPTIONS=''.join(map(lambda str: '#define %s\n\n' %(str,), options)),
	    INCLUDES='')

    def rule_process(self):
	self.outputs[0].write(hdr)

    self.rule = rule_process

def waf_layer(bld, env):

    final = mybuild_main(['src'])   

    objs = []

    for opt, dom in final.items():
	if isinstance(opt, mybuild_prot.Module) and dom == mybuild_prot.Domain([True]):
	    bld(features = 'module_header',
		target = 'include/module/%s.h' % (opt.qualified_name().replace('.','/'),),
		mod = opt,
		scope = final)
	    for src in opt.sources:


		bld(features = 'c', 
		    source = src.fullpath(),
		    defines = ['__EMBUILD_MOD__'],
		    includes = env.includes)

		#objs.append(target)
    bld(
	features = 'c cprogram',
	target = env.target,
	use = objs,
	linkflags = bld.env.LDFLAGS,
    )
if __name__ == '__main__':
    import sys
    mybuild_main(sys.argv[1:])
