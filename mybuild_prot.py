
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
    def __init__(self, name, parent=None):
	self.name = name
	self.parent = parent
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


def obj_package(cls, package, name, *args, **kargs): 
    kargs['root_package'] = package
    package[name] = cls(name, *args, **kargs)

def module_package(package, name, *args, **kargs):
    obj_package(Module, package, name, *args, **kargs)

class Option:
    def __init__(self, name='', value=None):
	self.name = name
	self.value = value

    def trigger(self, cont, scope, domain):
	return cont(scope)

class Integer(Option):
    def __init__(self, name='', domain=None, default=None):
	self.name = name
	if domain == None:
	    domain = range(0,32000)
	self.domain = Domain(domain)
	self.default = default 

class String(Option):
    def __init__(self, name='', value=None):
	self.name = name
	self.value = value
	pass

class Boolean(Option):
    def __init__(self, name='', domain=None, value=None):
	self.name = name
	if domain == None:
	    domain = [False, True]
	self.domain = Domain(domain)
	self.value = value
    pass

class Domain(frozenset):
    def value(self):
	if len(self) == 1:
	    for v in self:
		return v
	return None
    
    def force_value(self):
	for v in sorted(self):
	    return v

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

class Scope(BaseScope):
    def value(self, opt):
	d = self[opt]
	if len(d) > 1:
	    raise MultiValueException(opt)
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
    def __init__(self, modname, root_package=None, sources=[], options=[], super=None, implements=(), depends=(), include_trigger=None):
	self.parent = super
	self.modname = modname
	self.name = 'self'
	self.include_trigger = include_trigger
	self.sources = sources

	self.root_package = root_package

	self.domain = Domain([True, False])

	self.options = [self]
	self.options += options
	self.hash_value = (modname + '.include_module').__hash__()


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
	    dict.__setitem__(self, o.name, o)

    def trigger(self, cont, scope, domain):
	v = domain.value()
	if None == v or not v:
	    return cont(scope)

	for dep, opts in self.depends:
	    scope = incut(scope, self.root_package[dep], Domain([True]))
	    for opt, d in opts.items():
		scope = incut(scope, self.root_package[dep + '.' + opt], d)

	if self.include_trigger:
	    return trigger_handle(cont, scope, self.include_trigger)

	return cont(scope)

    def implements(self):
	def get_impl(obj):
	    return [obj] + [get_impl(impl) for impl in obj.implements]

	return get_impl(self)[1:]	

    def is_list(self):
	return self.implements

    def __repr__(self):
	return "<Module %s, depends %s, sources %s>" % (self.modname, self.depends, self.sources)

    def __hash__(self):
	return self.hash_value

class Interface(Boolean, Inherit, BaseScope):
    def __init__(self, intname, root_package, super=()):
	self.intname = intname
	self.name = 'self'
	self.id = intname + ".include_interface" 
	self.super = one_or_many(super)

    def __repr__(self):
	return "Interface '" + self.intname + "'"

class MultiValueException(Exception):
    def __init__(self, opt):
	self.opt = opt 

class CutConflictException(Exception):
    def __init__(self, opt):
	self.opt = opt 

def add_many(scope, ents):
    for ent in ents:
	for name, opt in ent.items():
	    if scope.has_key(opt):
		raise Exception
	    scope[opt] = opt.domain

def cut_many(scope, opts):
    has_no_trigger = filter(lambda m: not isinstance(m, Module) or not m.include_trigger, [m for m, d in opts])
    d = dict(opts)

    for opt in has_no_trigger:
	scope = incut(scope, opt, d[opt])
	del d[opt]

    return cut_iter(scope, [(opt, dom) for opt, dom in d.items()])

def incut_cont(cont, scope, opt, domain):
    strict_domain = scope[opt] & domain
    if strict_domain:
	scope[opt] = strict_domain
	scope = opt.trigger(cont, scope, strict_domain)
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
    new_scope = Scope(scope)

    for k, v in scope.items():
	opt = k
	value = v.force_value()

	if hasattr(opt, 'default') and opt.default in v:
	    value = opt.default

	new_scope[k] = value

    return new_scope

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
	add_many(scope, map(lambda s: package[s], ['blck', 'stdio', 'fs', 'test', 'test2', 'test3']))

	scope = cut_many(scope, [(package['fs'], Domain([True])), (package['test2'], Domain([True]))])

	final = fixate(scope)
	
	self.assertTrue(final[package['blck']])
	self.assertTrue(final[package['stdio']])
	self.assertTrue(final[package['fs']])
	self.assertTrue(final[package['test']])
	self.assertTrue(final[package['test2']])
	self.assertFalse(final[package['test3']])

    def test_depends_with_options(self):
	package = Package('root')
	module_package(package, 'stack', options = [Integer('stack_sz', domain = range(8192,1000000))])
	module_package(package, 'thread_core', depends = [ ('stack', {'stack_sz' : Domain([16000])}) ])

	scope = Scope()
	add_many(scope, map(lambda s: package[s], ['stack', 'thread_core']))

	scope = cut_many(scope, [(package['stack'], Domain([True])), (package['thread_core'], Domain([True]))])

	final = fixate(scope)

	self.assertTrue(final[package['thread_core']])
	self.assertTrue(final[package['stack']])
	self.assertEqual(final[package['stack.stack_sz']], 16000)

    def test_depends_with_options2(self):
	package = Package('root')
	module_package(package, 'stack', options = [Integer('stack_sz', domain = range(8192,12000))])
	module_package(package, 'thread_core', depends = [ ('stack', {'stack_sz' : Domain([16000])}) ])

	scope = Scope()
	add_many(scope, map(lambda s: package[s], ['stack', 'thread_core']))


	self.assertRaises(CutConflictException, cut, scope, package['thread_core'], Domain([True]))

    def test_optional_include(self):
	package = Package('root')
	module_package(package, 'amba')

	def uart_trigger(scope):
	    if scope.value(package['uart.amba_pp']):
		return cut(scope, package['amba'], Domain([True]))
	    return scope

	module_package(package, 'uart', options = [Boolean('amba_pp')] , include_trigger=uart_trigger)
	
	scope = Scope()
	add_many(scope, [package['uart'], 
			 package['amba']])

	scope = cut_many(scope, [(package['uart'], Domain([True])), 
				 (package['uart.amba_pp'], Domain([True]))])

	self.assertTrue(scope != False)

	final = fixate(scope)

	self.assertTrue(final[package['amba']])

    def test_optional_include2(self):
	package = Package('root')
	module_package(package, 'amba', depends = 'bad_module')
	module_package(package, 'bad_module')

	def uart_trigger(scope):
	    if scope.value(package['uart.amba_pp']):
		return cut(scope, package['amba'], Domain([True]))
	    return cut(scope, package['bad_module'], Domain([True]))

	module_package(package, 'uart', options = [Boolean('amba_pp')] , include_trigger=uart_trigger)

	scope = Scope()
	add_many(scope, map(lambda s: package[s], ['uart', 'amba', 'bad_module']))

	self.assertRaises(CutConflictException, 
		cut_many, scope, [(package['uart'],	  Domain([True])), 
				  (package['bad_module'], Domain([False]))])

    def test_interface(self):
	package = Package('root')
	obj_package(Interface, 'timer_api')
	module_package('head_timer', implements='timer_api')

	add_many(scope, map(lambda s: package[s], ['timer_api', 'head_timer']))

	cut_many(scope, [(head_timer, Domain([True]))])

	final = fixate(scope)

	self.assertEqual(scope[package['timer_api']], scope[head_timer])

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
