
import sys
import os

sys.path.append(os.getcwd())

import mybuild_prot
from mybuild_prot import one_or_many
from mybuild_prot import Integer, Boolean, String

class Annotation():
    def __init__(self):
	pass

def annotated(obj, annot):
    try:
	obj.annots += annot
    except Exception, ex:
	class AnnotHolder(obj.__class__):
	    pass
	new_obj = AnnotHolder(obj)
	new_obj.annots = annot
	return new_obj

class NoRuntimeAnnotation(Annotation):
    pass

class SourceAnnotation(Annotation):
    pass

class LDScriptAnnotation(SourceAnnotation):
    def build(self, bld, source):
	bld(
	    features = 'includes',
	    source = source.fullpath(),
	    includes = bld.env.includes,
	)

def NoRuntime(obj):
    return annotated(obj, [NoRuntimeAnnotation()])

def LDScript(obj):
    return annotated(obj, [LDScriptAnnotation()])

class Source:
    def __init__(self, dirname, filename):
	self.dirname = dirname
	self.filename = filename

    def __repr__(self):
	return "Source('%s/%s')" % (self.dirname, self.filename)

    def fullpath(self):
	return os.path.join(self.dirname, self.filename)

    def annotations(self):
	return getattr(self.filename, 'annots', [])

    def build(self, bld):
	for ann in self.annotations():
	    ann.build(bld, self)
	    break
	else:
	    bld(features = 'c', 
		source = self.fullpath(),
		defines = ['__EMBUILD_MOD__'],
		includes = bld.env.includes)


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
from waflib import TaskGen, Task

@TaskGen.extension('.lds.S')
def lds_s_hook(self, node):
    tgtnode = node.change_ext('.lds', '.lds.S')
    return self.create_task('lds_s', node, tgtnode)

class lds_s(Task.Task):
    run_str = '${CC} ${ARCH_ST:ARCH} ${CFLAGS} ${CPPFLAGS} ${FRAMEWORKPATH_ST:FRAMEWORKPATH} ${CPPPATH_ST:INCPATHS} ${DEFINES_ST:DEFINES} ${CC_SRC_F}${SRC} -E -P -o ${TGT}'
    ext_out = ['.lds'] # set the build order easily by using ext_out=['.h']

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

def waf_layer(bld):

    final = mybuild_main(['src'])   

    srcs = []

    for opt, dom in final.items():
	if isinstance(opt, mybuild_prot.Module) and dom == mybuild_prot.Domain([True]):
	    bld(features = 'module_header',
		target = 'include/module/%s.h' % (opt.qualified_name().replace('.','/'),),
		mod = opt,
		scope = final)

	    for src in opt.sources:
		src.build(bld)
    bld(
	features = 'c cprogram',
	source = srcs,
	target = bld.env.target,
	includes = bld.env.includes,
	linkflags = bld.env.LDFLAGS,
    )

if __name__ == '__main__':
    import sys
    mybuild_main(sys.argv[1:])
