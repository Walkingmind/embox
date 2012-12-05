
import pyconf.build
import pybuild.flags
top = '.'
out = 'build'

def options(ctx):
    pass

def it_or_zero(obj, key):
    if obj.__dict__.has_key(key):
	return obj.__dict__[key]
    return []

def configure(ctx):
    ctx.env.CC = pyconf.build.CROSS_COMPILE + "gcc"
    ctx.env.AR = pyconf.build.CROSS_COMPILE + "ar"

    user_CFLAGS = it_or_zero(pyconf.build, 'CFLAGS')
    user_CXXFLAGS = it_or_zero(pyconf.build, 'CXXFLAGS')
    user_CPPFLAGS = it_or_zero(pyconf.build, 'CPPFLAGS')
    user_LDFLAGS = it_or_zero(pyconf.build, 'LDFLAGS')
    user_ARFLAGS = it_or_zero(pyconf.build, 'ARFLAGS')

    ctx.env.CFLAGS = pybuild.flags.CFLAGS + user_CFLAGS + ctx.env.CFLAGS
    ctx.env.CPPFLAGS = pybuild.flags.CPPFLAGS + user_CPPFLAGS + ctx.env.CPPFLAGS
    ctx.env.CXXFLAGS = pybuild.flags.CXXFLAGS + user_CXXFLAGS + ctx.env.CXXFLAGS
    ctx.env.LDFLAGS = pybuild.flags.LDFLAGS + user_LDFLAGS + ctx.env.LDFLAGS
    ctx.env.ARFLAGS = pybuild.flags.ARFLAGS + user_ARFLAGS + ctx.env.ARFLAGS

    ctx.load('gcc c ar')

def build(ctx):
    ctx(features = 'c', 
	source = 'src/kernel/init.c',
	includes = ['src/include',
		    'src/arch/{ARCH}/include'.format(ARCH=pyconf.build.ARCH),
		    'src/compat/posix/include',
		    'src/compat/linux/include']
    )


