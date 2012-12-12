
import unittest
import operator
import itertools

import traceback

from functools import partial

def tup_or_list(obj):
    if isinstance(obj, tuple) or isinstance(obj, list):
	return True

    return False

def one_or_many(obj):
    return obj if tup_or_list(obj) else [obj]

class Package(dict):
    def __init__(self, name, pkg=None):
	self.name = name
	self.pkg = pkg  

    def __getitem__(self, key):
	splt = key.split('.', 1)
	obj = dict.__getitem__(self, splt[0])

	if len(splt) > 1:
	    return obj[splt[1]]

	return obj

    def built_subpack(self, key):
	splt = key.split('.', 1)
	obj = self

	if not self.has_key(splt[0]):
	    dict.__setitem__(self, splt[0], Package(splt[0], self))

	if len(splt) > 1:
	    self[splt[0]].built_subpack(splt[1])

    def qualified_name(self):
	if self.pkg == None:
	    return ""
	parent = self.pkg.qualified_name()
	if parent:
		return '%s.%s' % (parent, self.name)
	return self.name

    def root(self):
	if self.pkg == None:
	    return self
	return self.pkg.root()

    def find_with_imports(self, imports, name):
	for impt in imports:
	    if impt:
		pkg = self[impt]
	    else:
		pkg = self

	    try:
		return pkg[name]
	    except KeyError:
		pass
	raise KeyError(name)

def obj_package(cls, package, name, *args, **kargs): 
    kargs['pkg'] = package
    package[name] = cls(name, *args, **kargs)

def module_package(package, name, *args, **kargs):
    obj_package(Module, package, name, *args, **kargs)

class Domain(frozenset):
    def value(self):
	if len(self) == 1:
	    for v in self:
		return v
	return None
    
    def force_value(self):
	for v in sorted(self):
	    return v
	raise CutConflictException(self)

class ListDom(Domain):
    def __nonzero__(self):
	return True

    def force_value(self):
	return self

class IntegerDom(Domain):
    def __repr__(self):
	return '<IntegerDom: [%d-%d]' % (min(self), max(self))

class ModDom(Domain):
    def __and__(self, other):
	if isinstance(other, BoolDom):
	    if True in other:
		return ModDom(self)
	    return ModDom([])
	return Domain.__and__(self, other)

class BoolDom(Domain):
    pass

class Option:
    def __init__(self, name='', domain=None, pkg=None):
	self.name = name

	if domain == None:
	    self.domain = self.__class__.domain
	else: 
	    self.domain = Domain(domain)

	self.pkg = pkg

    def cut_trigger(self, cont, scope, domain):
	return cont(scope)

    def add_trigger(self, scope):
	return scope

    def fix_trigger(self, scope):
	domain = scope[self]
	scope[self] = Domain([domain.force_value()])

	return scope

    def qualified_name(self):
	return '%s.%s' % (self.pkg.qualified_name(), self.name)

class DefaultOption(Option):
    def __init__(self, name, domain=None, default=None, pkg=None):
	Option.__init__(self, name, domain, pkg)
	self.default = default 

    def fix_trigger(self, scope):
	domain = scope[self]
	if hasattr(self, 'default') and self.default in domain:
	    scope[self] = Domain([self.default])
	else:
	    return Option.fix_trigger(self, scope)

	return scope

class List(Option):
    domain = ListDom([])
    
class Integer(DefaultOption):
    domain = IntegerDom(range(0, 0x10000))

class String(Option):
    def __init__(self, name='', default=None, pkg=None):
	self.name = name
	self.default = default 
	self.pkg = pkg

class Boolean(DefaultOption):
    domain = BoolDom([True, False])

class Inherit():
    def __init__(self, super=None):
	self.super = super

    def supers(self):
	if self.super:
	    return [self.super] + self.super.supers()
	return []

class BaseScope(dict):
    def __init__(self, parent=None):
	self.parent = parent
	
    def __getitem__(self, x):
	if dict.has_key(self, x):
	    return dict.__getitem__(self, x)
	elif self.parent:
	    return self.parent[x]
	else:
	    raise AttributeError

    def __len__(self):
	par = 0
	if self.parent:
	    par = len(self.parent)
	return dict.__len__(self) + par

    def keys(self):
	par_keys = set()
	if self.parent: 
	    par_keys = set(self.parent.keys())

	return set(dict.keys(self)) | par_keys

    def items(self):
	return ((k, self[k]) for k in self.keys())

    def has_key(self, k):
	return k in self.keys()

    def __nonzero__(self):
	return True

class Scope(BaseScope):
    def value(self, opt):
	d = self[opt]
	if len(d) > 1:
	    raise MultiValueException(opt)
	elif len(d) < 1:
	    raise CutConflictException(opt)
	return d.force_value()

    def __repr__(self):
	return 'Scope {' + \
	    reduce (operator.add, map(lambda x: "\t%s: %s" % x, self.items()), "")

def trigger_handle(cont, scope, trig):
    opt = None
    try:
	trig_ret = trig(scope)

	if isinstance(trig_ret, Scope):
	    return cont(trig_ret)

	return cont(scope)
    except MultiValueException, excp:
	opt = excp.opt

    dom = scope[opt]
    for value in dom:
	value_scope = cut(scope, opt, Domain([value]))

	try:
	    return trigger_handle(cont, value_scope, trig)
	except CutConflictException or MultiValueException, excp:
	    pass

    raise CutConflictException(opt)

class Module(Boolean, Inherit, BaseScope):
    def __init__(self, name, pkg=None, sources=[], options=[], super=None, implements=(), depends=(), include_trigger=None):
	self.parent = super
	self.name = name
	self.include_trigger = include_trigger
	self.sources = sources

	self.domain = Boolean.domain
	self.pkg = pkg 

	self.options = []
	self.options += options
	self.hash_value = hash(name + '.include_module')

	if not tup_or_list(depends):
	    self.depends = ((depends, {}),)
	else:
	    self.depends = []
	    for d in depends:
		if not tup_or_list(d):
		    self.depends.append((d, {}))
		else:
		    self.depends.append(d)

	self.implements = one_or_many(implements)

	for o in self.options:
	    o.pkg = self
	    self[o.name] = o

    def add_trigger(self, scope):
	for impl in self.implements:
	    implmod = self.pkg.root().find_with_imports([self.pkg.qualified_name(), ''], impl)
	    scope[implmod] |= ModDom([self])
	return scope

    def cut_trigger(self, cont, scope, old_domain):
	domain = scope[self]
	v = domain.value()
	if len(domain) > 1: 
	    return cont(scope)

	if v:
	    for impl in self.implements:
		implmod = self.pkg.root().find_with_imports([self.pkg.qualified_name(), ''], impl)
		scope = incut(scope, implmod, ModDom([self]))

	    for dep, opts in self.depends:
		depmod = self.pkg.root().find_with_imports([self.pkg.qualified_name(), ''], dep)
		scope = incut(scope, depmod, BoolDom([True]))
		for opt, d in opts.items():
		    scope = incut(scope, self.pkg[dep + '.' + opt], d)

	    if self.include_trigger:
		return trigger_handle(cont, scope, self.include_trigger)
	else:
	    for impl in self.implements:
		implmod = self.pkg.root().find_with_imports([self.pkg.qualified_name(), ''], impl)
		scope = incut(scope, implmod, scope[implmod] - ModDom([self]))

	return cont(scope)

    def fix_trigger(self, scope):
	for v in scope[self]:
	    try:
		return cut(scope, self, BoolDom([v]))
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

    def __hash__(self):
	return self.hash_value

class DefImplMod(Module):
    def add_trigger(self, scope):
	return scope

    def cut_trigger(self, cont, scope, old_domain):
	domain = scope[self]
	if domain.force_value():
	    raise CutConflictException(self)

	return cont(scope)

class Interface(DefaultOption, Inherit, BaseScope):
    def __init__(self, name, pkg, super=None):
	self.name = name
	self.hash_value = hash(name + ".include_interface")
	self.super = one_or_many(super)
	self.pkg = pkg
	self.parent = super
	self.def_impl = DefImplMod(self.qualified_name() + "_def_impl", pkg=pkg, implements=[self])
	self.domain = ModDom([self.def_impl])

    def items(self):
	return [('Default Impl', self.def_impl)]

    def cut_trigger(self, cont, scope, old_domain):
	domain = scope[self]
	cant_be = old_domain - domain
	for old_impl in cant_be:
	    scope = cont(incut(scope, old_impl, BoolDom([False])))

	if len(domain) == 1:
	    return cont(incut(scope, domain.value(), BoolDom([True])))

	return cont(scope)

    def fix_trigger(self, scope):
	for impl in scope[self]:
	    try:
		return cut(scope, self, ModDom([impl]))
	    except CutConflictException:
		pass
	
	raise CutConflictException(self)

    def __repr__(self):
	return "Interface '" + self.name + "'"

    def __hash__(self):
	return self.hash_value

class Feature(Option):
    def __init__(self, name, pkg):
	self.name = name
	self.pkg = pkg 

    def __repr__(self):
	return "Feature '" + self.name + "'"

class MultiValueException(Exception):
    def __init__(self, opt):
	self.opt = opt 

class CutConflictException(Exception):
    def __init__(self, opt):
	self.opt = opt 
    def __str__(self):
	return self.opt

def add_many(scope, ents):
    for ent in ents:
	scope[ent] = ent.domain
	if hasattr(ent,'items'):
	    for name, opt in ent.items():
		scope[opt] = opt.domain

    for ent in ents:
	scope = ent.add_trigger(scope)
	if hasattr(ent,'items'):
	    for name, opt in ent.items():
		scope = opt.add_trigger(scope)
    
    return scope

def cut_many(scope, opts):
    has_no_trigger = filter(lambda m: not isinstance(m, Module) or not m.include_trigger, [m for m, d in opts])
    d = dict(opts)

    for opt in has_no_trigger:
	scope = incut(scope, opt, d[opt])
	del d[opt]

    return cut_iter(scope, [(opt, dom) for opt, dom in d.items()])

def incut_cont(cont, scope, opt, domain):
    strict_domain = scope[opt] & domain
    old_domain = scope[opt]
    print 'cut %s for %s' % (opt, domain)
    if strict_domain:
	differ = strict_domain != old_domain
	scope[opt] = strict_domain
	if differ:
	    scope = opt.cut_trigger(cont, scope, old_domain)
    else:
	raise CutConflictException(opt)

    return scope

def incut(scope, opt, domain):
    return incut_cont(lambda x: x, scope, opt, domain)

def cut(scope, opt, domain):

    scope = Scope(scope)

    scope = incut(scope, opt, domain)

    return scope

def cut_iter(scope, opts):
    if not opts:
	return scope

    opt, domain = opts[0]
    return incut_cont(partial(cut_iter,opts=opts[1:]), scope, opt, domain)

def fixate(scope):
    scope = Scope(scope)

    for opt, domain in scope.items():
	print 'fixing %s within %s' %(opt, domain)
	scope = opt.fix_trigger(scope)

    return scope

class TestCase(unittest.TestCase):
    def test_recursive_feature_add(self):
	package = Package('root')
	module_package(package, 'blck')
	module_package(package, 'stdio')
	module_package(package, 'fs', depends = ['blck', 'stdio'])
	module_package(package, 'test')
	module_package(package, 'test2', depends = 'test')
	module_package(package, 'test3')

	scope = Scope()
	scope = add_many(scope, map(lambda s: package[s], ['blck', 'stdio', 'fs', 'test', 'test2', 'test3']))

	scope = cut_many(scope, [(package['fs'], BoolDom([True])), (package['test2'], BoolDom([True]))])

	final = fixate(scope)
	
	self.assertEqual(final[package['blck']],  BoolDom([True]))
	self.assertEqual(final[package['stdio']], BoolDom([True]))
	self.assertEqual(final[package['fs']],    BoolDom([True]))
	self.assertEqual(final[package['test']],  BoolDom([True]))
	self.assertEqual(final[package['test2']], BoolDom([True]))
	self.assertEqual(final[package['test3']], BoolDom([False]))

    def test_depends_with_options(self):
	package = Package('root')
	module_package(package, 'stack', options = [Integer('stack_sz', domain = range(8192,1000000))])
	module_package(package, 'thread_core', depends = [ ('stack', {'stack_sz' : Domain([16000])}) ])

	scope = Scope()
	scope = add_many(scope, map(lambda s: package[s], ['stack', 'thread_core']))

	scope = cut_many(scope, [(package['stack'], BoolDom([True])), (package['thread_core'], BoolDom([True]))])

	final = fixate(scope)

	self.assertTrue(final[package['thread_core']])
	self.assertTrue(final[package['stack']])
	self.assertEqual(final[package['stack.stack_sz']], Domain([16000]))

    def test_depends_with_options2(self):
	package = Package('root')
	module_package(package, 'stack', options = [Integer('stack_sz', domain = range(8192,12000))])
	module_package(package, 'thread_core', depends = [ ('stack', {'stack_sz' : Domain([16000])}) ])

	scope = Scope()
	scope = add_many(scope, map(lambda s: package[s], ['stack', 'thread_core']))


	self.assertRaises(CutConflictException, cut, scope, package['thread_core'], BoolDom([True]))

    def test_optional_include(self):
	package = Package('root')
	module_package(package, 'amba')

	def uart_trigger(scope):
	    if scope.value(package['uart.amba_pp']):
		return cut(scope, package['amba'], BoolDom([True]))
	    return scope

	module_package(package, 'uart', options = [Boolean('amba_pp')] , include_trigger=uart_trigger)
	
	scope = Scope()
	scope = add_many(scope, [package['uart'], 
			 package['amba']])

	scope = cut_many(scope, [(package['uart'], BoolDom([True])), 
				 (package['uart.amba_pp'], BoolDom([True]))])

	self.assertTrue(scope != False)

	final = fixate(scope)

	self.assertTrue(final[package['amba']])

    def test_optional_include2(self):
	package = Package('root')
	module_package(package, 'amba', depends = 'bad_module')
	module_package(package, 'bad_module')

	def uart_trigger(scope):
	    if scope.value(package['uart.amba_pp']):
		return cut(scope, package['amba'], BoolDom([True]))
	    return cut(scope, package['bad_module'], BoolDom([True]))

	module_package(package, 'uart', options = [Boolean('amba_pp')] , include_trigger=uart_trigger)

	scope = Scope()
	scope = add_many(scope, map(lambda s: package[s], ['uart', 'amba', 'bad_module']))

	self.assertRaises(CutConflictException, 
		cut_many, scope, [(package['uart'],	  BoolDom([True])), 
				  (package['bad_module'], BoolDom([False]))])

    def test_interface(self):
	package = Package('root')
	obj_package(Interface, package, 'timer_api')
	module_package(package, 'head_timer', implements='timer_api')

	scope = Scope()
	scope = add_many(scope, map(lambda s: package[s], ['timer_api', 'head_timer']))

	cut_many(scope, [(package['head_timer'], BoolDom([True]))])

	final = fixate(scope)

	self.assertEqual(final[package['timer_api']], Domain([package['head_timer']]))

    def test_interface2(self):
	package = Package('root')
	obj_package(Interface, package, 'timer_api')
	module_package(package, 'head_timer', implements='timer_api')
	module_package(package, 'timer_exmp', depends = ['timer_api'])

	scope = Scope()
	scope = add_many(scope, map(lambda s: package[s], ['timer_api', 'head_timer', 'timer_exmp']))

	cut_many(scope, [(package['timer_exmp'], BoolDom([True]))])

	final = fixate(scope)

	self.assertEqual(final[package['timer_api']], ModDom([package['head_timer']]))

    @unittest.expectedFailure 
    def test_options(self):
	timer_api = Interface("Timer api")
	head_timer = Module("Head timer", implements=timer_api, options = {'timer_nr' : 32, 'impl_name' : None})
	rt = Module("Hard realtime head timer", implements=timer_api, super=head_timer, options={'impl_name' : "rt timer"})

	scope = try_add_step(Scope(), rt)
	scope = try_add_step(scope, head_timer, options = {'timer_nr' : 64})

	self.assertEqual(rt.option_val(scope, 'timer_nr'),	    64)
	self.assertEqual(rt.option_val(scope, 'impl_name'),	    "rt timer")
	self.assertEqual(head_timer.option_val(scope, 'impl_name'), None)

    @unittest.expectedFailure 
    def test_options_error(self):
	timer = Module("Head timer", options = {'timer_nr' : 32})
	self.assertRaises(AttributeError, try_add_step, Scope(), timer, options = {'inobviously incorrect name' : 32 })

    @unittest.expectedFailure 
    def test_constraints(self):
	stack_lds = Module("stack", options = {'stack_sz' : 1024})
	tunings = [Tuning(stack_lds, None, lambda scope: ent.option_val(scope, 'stack_sz') > 4096)]

	thread_core = Module("thread_core", tunings=tunings)

	scope = try_add_step(Scope(), stack_lds)
	self.assertTrue(False != scope[stack_lds])
	scope = try_add_step(scope, thread_core)
	self.assertRaises(AttributeError, scope.__getitem__, thread_core)

    @unittest.expectedFailure 
    def test_constraints_unordered(self):
	stack_lds = Module("stack", options = {'stack_sz' : 8192})
	tunings = [Tuning(stack_lds, None, lambda scope: ent.option_val(scope, 'stack_sz') > 4096)]

	thread_core = Module("thread_core", tunings=tunings)

	scope = try_add_step(Scope(), thread_core)
	scope = try_add_step(scope, stack_lds)
	self.assertTrue(False != scope[thread_core])
	self.assertTrue(False != scope[stack_lds])

    def test_scope_pred(self):
	scope = Scope()
	self.assertTrue(scope != False)
	scope = Scope(scope)
	self.assertTrue(scope != False)


if __name__ == '__main__':
    unittest.main()
