
import re
import itertools

from exception import *

import option
import domain
import scope

from util import isvector

from ops  import *

from mybuild.common import repr as common_repr
from mybuild.build import inchdr

def trigger_handle(cont, scope, trig, *args, **kwargs):
    opt = None
    try:
	trig_ret = trig(scope, *args, **kwargs)

	if isinstance(trig_ret, Scope):
	    return cont(trig_ret)

	return cont(scope)
    except MultiValueException, excp:
	opt = excp.opt

    dom = scope[opt]

    if hasattr(opt, 'default') and opt.default in dom:
	dom = itertools.chain((opt.default,), dom)

    for value in dom:
	value_scope = cut(scope, opt, opt.domain_class([value]))

	try:
	    return trigger_handle(cont, value_scope, trig, *args, **kwargs)
	except CutConflictException or MultiValueException, excp:
	    pass

    raise CutConflictException(opt)

class Module(option.Boolean, scope.BaseScope):
    def __init__(self, name, pkg=None, sources=[], options=[], super=None, implements=(), depends=(), include_trigger=None):
	option.Boolean.__init__(self, name, pkg = pkg)
	self.parent = super
	self.name = name
	self.include_trigger = include_trigger
	self.sources = sources

	self.options = []
	self.options += options
	self.hash_value = hash(name + '.include_module')

	self.depends = []

	for d in depends:
	    if not isvector(d):
		self.depends.append((d, {}))
	    else:
		self.depends.append(d)

	self.implements = implements

	for o in self.options:
	    o.pkg = self
	    self[o.name] = o

    def add_trigger(self, scope):
	for impl in self.implements:
	    implmod = self.pkg.root().find_with_imports([self.pkg.qualified_name(), ''], impl)
	    scope[implmod] |= domain.ModDom([self])
	return scope

    def cut_trigger(self, cont, scope, old_domain):
	dom = scope[self]
	v = dom.value()
	if len(dom) > 1: 
	    return cont(scope)

	def find_fn(name):
	    return self.pkg.root().find_with_imports([self.pkg.qualified_name(), ''], name)

	if v:
	    for impl in self.implements:
		implmod = find_fn(impl)
		scope = incut(scope, implmod, domain.ModDom([self]))

	    for dep, opts in self.depends:
		depmod = find_fn(dep)
		scope = incut(scope, depmod, domain.BoolDom([True]))
		for opt, d in opts.items():
		    scope = incut(scope, self.pkg[dep + '.' + opt], d)

	    if self.include_trigger:
		return trigger_handle(cont, scope, self.include_trigger, find_fn)
	else:
	    for impl in self.implements:
		implmod = find_fn(impl)
		scope = incut(scope, implmod, scope[implmod] - domain.ModDom([self]))

	return cont(scope)

    def fix_trigger(self, scope):
	for v in scope[self]:
	    try:
		return cut(scope, self, domain.BoolDom([v]))
	    except CutConflictException:
		pass
	raise CutConflictException(self)

    def implements(self):
	def get_impl(obj):
	    return [obj] + [get_impl(impl) for impl in obj.implements]

	return get_impl(self)[1:]	

    def is_list(self):
	return self.implements

    def __repr__(self):
	return "<Module %s, depends %s, sources %s>" % (self.name, self.depends, self.sources)

    def canon_repr(self):
	opts = map(lambda name_opt_pair: name_opt_pair[0], self.items())
	return common_repr.mod_canon(self.name, opts)

    def __hash__(self):
	return self.hash_value


    def build(self, bld, scope):
	if not scope[self].value():
	    return 

	srcs = []
	header_inc = []
	header_opts = []

	for src in self.sources:
	    fsrc = src.build(bld, self, scope)
	    if re.match('.*\.[cS]', fsrc):
		srcs.append(fsrc)
	    elif re.match('.*\.h', fsrc):
		header_inc.append(fsrc)

	for name, var in self.items():
	    repr = var.build_repr()
	    if not repr:
		continue
	    header_opts.append(inchdr(repr, self.qualified_name(), name, scope[var].value()))

	bld(features = 'module_header',
	    mod_name = self.qualified_name(),
	    header_opts = header_opts,
	    header_inc = header_inc)

	self.build_self(bld, srcs)

    def build_self(self, bld, srcs):
	tgt = self.qualified_name().replace('.', '_') + '.o'

	bld(
	    features = 'c', 
	    #source = srcs,
	    target = tgt,
	    defines = ['__EMBUILD_MOD__'],
	    includes = bld.env.includes,
	    use = srcs,
	)

	bld.out.append(tgt)

class StaticModule(Module):
    def build_self(self, bld, srcs):
	tgt = self.qualified_name().replace('.', '_') + '.o'

	bld(
	    features = 'c cstlib', 
	    source = srcs,
	    target = tgt,
	    defines = ['__EMBUILD_MOD__'],
	    includes = bld.env.includes,
	)

	bld.out.append(tgt)
    
