
import os

import logging
#logging.basicConfig(level=logging.DEBUG)

#top = os.getcwd()
top = '.'
out = 'build'

import pyconf.build
import mybuild.pybuild.flags

def options(ctx):
    ctx.add_option('--method', choices=['A', 'E'], default='A',
	    help='Model method, either A (for Anton\'s) or E (for Eldar\'s')

def configure(ctx):
    ctx.env.METHOD = ctx.options.method
    crosstool = getattr(pyconf.build, 'CROSS_COMPILE', '')
    ctx.env.CC = crosstool + "gcc"
    ctx.env.AR = crosstool + "ar"
    ctx.env.LD = crosstool + "ld"
    
    for flag in ['CFLAGS', 'CXXFLAGS', 'CPPFLAGS', 'LDFLAGS', 'ARFLAGS', 'ASFLAGS']:
        setattr(ctx.env, 'user_' + flag, getattr(pyconf.build, flag, []))
        setattr(ctx.env, 'system_' + flag, getattr(mybuild.pybuild.flags, flag, []))
        setattr(ctx.env, flag, getattr(ctx.env, 'system_' + flag) + 
                               getattr(ctx.env, 'user_' + flag) + 
                               getattr(ctx.env, flag))
    ctx.load('gcc c ar')

from waflib.TaskGen import feature, after
from waflib import TaskGen, Task
from waflib import Utils

from waflib.Tools.ccroot import link_task

@TaskGen.extension('.S','.asm','.ASM','.spp','.SPP')
def asm_hook(self,node):
	return self.create_compiled_task('c',node)

@TaskGen.extension('.lds.S')
def lds_s_hook(self, node):
    tgtnode = node.change_ext('.lds', '.lds.S')
    self.env['DEFINES'] = self.defines
    return self.create_task('lds_s', node, tgtnode)

class lds_s(Task.Task):
    run_str = '${CC} ${ARCH_ST:ARCH} ${CFLAGS} ${CPPFLAGS} ${FRAMEWORKPATH_ST:FRAMEWORKPATH} ${CPPPATH_ST:INCPATHS} ${DEFINES_ST:DEFINES} ${CC_SRC_F}${SRC} -E -P -o ${TGT}'
    ext_out = ['.lds'] # set the build order easily by using ext_out=['.h']

from waflib.Tools.ccroot import  USELIB_VARS
from waflib.Tools.c import cprogram

USELIB_VARS['ld'] = {'LINKFLAGS'}

class ld(cprogram):
    run_str='${LD} ${LINKFLAGS} ${CCLNK_SRC_F}${SRC} ${RAWLIB_ST:STLIB} ${CCLNK_TGT_F}${TGT[0].abspath()}'

@feature('module_header')
def header_gen(self):
    header = '''
#ifndef {GUARD}
#define {GUARD}

{INCLUDES}

{OPTIONS}

#endif /* {GUARD} */
'''

    hdr = header.format(GUARD=self.mod_name.replace('.', '_').upper(),
	OPTIONS=''.join(map(lambda str: '#define %s\n\n' %(str,), self.header_opts)),
	INCLUDES=''.join(map(lambda str: '#include<%s>\n\n' % (str,), self.header_inc)))

    self.target = 'include/module/%s.h' % (self.mod_name.replace('.','/'),)
    self.rule = lambda self: self.outputs[0].write(hdr)

    self.ext_out = ['.h']

def build(ctx):
    includes = [
		'.',
		'include',
		'src/include',
		'src/arch/{ARCH}/include'.format(ARCH=pyconf.build.ARCH),
		'src/compat/posix/include',
		'src/compat/linux/include']

    ctx.env['RAWLIB_ST'] = 'lib%s.a'
    ctx.env.target   = pyconf.build.TARGET
    ctx.env.includes = includes

    import mybuild.build

    mybuild.build.waf_entry(ctx) 

