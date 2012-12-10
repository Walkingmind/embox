
import os

#top = os.getcwd()
top = '.'
out = 'build'

import pyconf.build
import pybuild.flags

def options(ctx):
    pass

def configure(ctx):
    ctx.env.CC = pyconf.build.CROSS_COMPILE + "gcc"
    ctx.env.AR = pyconf.build.CROSS_COMPILE + "ar"

    user_CFLAGS = getattr(pyconf.build, 'CFLAGS', [])
    user_CXXFLAGS = getattr(pyconf.build, 'CXXFLAGS', [])
    user_CPPFLAGS = getattr(pyconf.build, 'CPPFLAGS', [])
    user_LDFLAGS = getattr(pyconf.build, 'LDFLAGS', [])
    user_ARFLAGS = getattr(pyconf.build, 'ARFLAGS', [])

    ctx.env.CFLAGS = pybuild.flags.CFLAGS + user_CFLAGS + ctx.env.CFLAGS
    ctx.env.CPPFLAGS = pybuild.flags.CPPFLAGS + user_CPPFLAGS + ctx.env.CPPFLAGS
    ctx.env.CXXFLAGS = pybuild.flags.CXXFLAGS + user_CXXFLAGS + ctx.env.CXXFLAGS
    ctx.env.LDFLAGS = pybuild.flags.LDFLAGS + user_LDFLAGS + ctx.env.LDFLAGS
    ctx.env.ARFLAGS = pybuild.flags.ARFLAGS + user_ARFLAGS + ctx.env.ARFLAGS

    ctx.load('gcc c ar')

def build(ctx):
    includes = ['include',
	        'src/include',
		'src/arch/{ARCH}/include'.format(ARCH=pyconf.build.ARCH),
		'src/compat/posix/include',
		'src/compat/linux/include']

    class Env():
	pass
    
    ctx.env.target   = pyconf.build.TARGET
    ctx.env.includes = includes

    import pybuild.core

    pybuild.core.waf_layer(ctx) 



