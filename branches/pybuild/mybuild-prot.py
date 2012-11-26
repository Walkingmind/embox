
import unittest
import operator
from copy import copy

def get_all_options(obj):
    option_set = set()
    for mod in [obj] + obj.supers():
	option_set |= set(mod.options.keys())
    return option_set

def one_or_many(obj):

    if not obj:
	return []

    try:
	return [e for e in obj]
    except TypeError:
	return [obj] 

class Instance():
    def __init__(self, meta, option_overwrite={}):
	self.meta = meta 
	misset = set(option_overwrite.keys()) - set(get_all_options(meta))

	for i in misset:
	    raise AttributeError(i)

	self.option_overwrite = option_overwrite

    def option_val(self, option):
	if self.option_overwrite.has_key(option):
	    return self.option_overwrite[option]
	return self.meta.option_val(option)

    def __repr__(self):
	return "Instance of %s with:%s\n" % \
		(self.meta,
		reduce(operator.add, 
		    ['\n\t\t %s = %s' % (str(i), str(self.option_val(i))) 
			for i in get_all_options(self.meta)], 
		    ""), 
		)

class Inherit():
    def __init__(self, super=None):
	self.super = super

    def supers(self):
	if self.super:
	    return [self.super] + self.super.supers()
	return []

class Module(Inherit):
    def __init__(self, name, options={}, super=None, implements=(), depends=(), check_fn=None):
	self.super = super
	self.name = name
	self.depends = one_or_many(depends)
	self.implements = one_or_many(implements)
	self.options = options
	self.check_fn = check_fn

    def implements(self):
	def get_impl(obj):
	    return [obj] + [get_impl(impl) for impl in obj.implements]

	return get_impl(self)[1:]	

    def option_val(self, option):
	for s in [self] + self.supers():
	    if s.options.has_key(option):
		return s.options[option]
	    
    def is_list(self):
	return self.implements

    def __repr__(self):
	return "Module '" + self.name + "'"

    def inst(self):
	return Instance(self)

    def subeval(self, scope):
	try:
	    if self.check_fn and not self.check_fn(scope):
		return False
	except:
	    return False

	res = True
	for i in self.depends:
	    res &= scope.eval(i)

	return res

    def __hash(self):
	return self.name.__hash__()

class Interface(Inherit):
    def __init__(self, name, super=()):
	self.name = name
	self.super = one_or_many(super)

    def is_list(self):
	return oneself.supers()

    def inst(self):
	return Instanse(self)

    def subeval(self, scope):
	return True

    def __repr__(self):
	return "Interface '" + self.name + "'"

class Scope(dict):
    def __init__(self):
	self.do_later = []

    def eval(self, ent, opts={}):
	
	inst = Instance(ent, opts)
   
	if ent.subeval(self):
	    self[ent] = inst
	    for i in ent.is_list():
		self[i] = inst
	    return True
	return False

    def __repr__(self):
	return 'Scope {' + \
	    reduce (operator.add, map(lambda x: "\t%s: %s" % x, self.items())) + \
	    "\n\tdo_later: " + self.do_later.__repr__() + "\n}"

    def copy(self):
	return copy(self)

def try_add_step(scope, ent, options = {}):

    new_scope = scope.copy()

    if new_scope.eval(ent, options):
	return new_scope

    scope.do_later.append((ent, options))
    return scope

def finalize(scope):
    if not scope:
	return False

    if not scope.do_later:
	return scope 

    for i in range(0,len(scope.do_later)):
	new_scope = scope.copy()
	new_scope.do_later = scope.do_later[0:i] + scope.do_later[i+1:]
	tup = scope.do_later[i]
	
	if new_scope.eval(*tup):
	    return new_scope

    return False

class TestCase(unittest.TestCase):
    def test_recursive_feature_add(self):
	blck = Module('module block')
	stdio = Module('module stdio')
	fs = Module('module FS', depends=(blck, stdio))
	test2 = Module('test2', depends=Module('test'))

	with_fs = try_add_step(Scope(), fs)
	final = finalize(try_add_step(with_fs, test2))
	self.assertEqual(len(final), 5)

    def test_interface(self):
	timer_api = Interface("Timer api")
	head_timer = Module("Head timer", implements=timer_api)

	final = finalize(try_add_step(Scope(), head_timer))
	self.assertEqual(final[timer_api], final[head_timer])

    def test_options(self):
	timer_api = Interface("Timer api")
	head_timer = Module("Head timer", implements=timer_api, options = {'timer_nr' : 32, 'impl_name' : None})
	rt = Module("Hard realtime head timer", implements=timer_api, super=head_timer, options={'impl_name' : "rt timer"})

	scope = try_add_step(Scope(), rt)
	scope = try_add_step(scope, head_timer)
	scope = finalize(scope)

	self.assertEqual(scope[rt].option_val('timer_nr'), 32)
	self.assertEqual(scope[rt].option_val('impl_name'), "rt timer")
	self.assertEqual(scope[head_timer].option_val('impl_name'), None)

    def test_options_error(self):
	timer = Module("Head timer", options = {'timer_nr' : 32})
	self.assertRaises(AttributeError, try_add_step, Scope(), timer, options = {'inobviously incorrect name' : 32 })

    def test_constraints(self):
	stack_lds = Module("stack", options = {'stack_sz' : 1024})

	def test_c(scope):
	    return scope[stack_lds].option_val('stack_sz') > 4096

	thread_core = Module("thread_core", check_fn=test_c)

	scope = try_add_step(Scope(), stack_lds)
	self.assertTrue(scope)
	scope = try_add_step(scope, thread_core)
	self.assertTrue(scope)
	self.assertFalse(finalize(scope))

    def test_constraints_unordered(self):
	stack_lds = Module("stack", options = {'stack_sz' : 8192})

	def test_c(scope):
	    return scope[stack_lds].option_val('stack_sz') > 4096

	thread_core = Module("thread_core", check_fn=test_c)

	scope = try_add_step(Scope(), thread_core)
	self.assertFalse(scope)
	scope = try_add_step(scope, stack_lds)
	self.assertTrue(scope)
	scope = finalize(scope)
	print scope
	self.assertTrue(scope)

if __name__ == '__main__':
    unittest.main()
