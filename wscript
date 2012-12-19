
import os

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
    ctx.env.AS = crosstool + "gcc"

    user_CFLAGS = getattr(pyconf.build, 'CFLAGS', [])
    user_CXXFLAGS = getattr(pyconf.build, 'CXXFLAGS', [])
    user_CPPFLAGS = getattr(pyconf.build, 'CPPFLAGS', [])
    user_LDFLAGS = getattr(pyconf.build, 'LDFLAGS', [])
    user_ARFLAGS = getattr(pyconf.build, 'ARFLAGS', [])
    user_ASFLAGS = getattr(pyconf.build, 'ASFLAGS', [])
    user_ASFLAGS += user_CFLAGS

    ctx.env.CFLAGS = mybuild.pybuild.flags.CFLAGS + user_CFLAGS + ctx.env.CFLAGS
    ctx.env.CPPFLAGS = mybuild.pybuild.flags.CPPFLAGS + user_CPPFLAGS + ctx.env.CPPFLAGS
    ctx.env.CXXFLAGS = mybuild.pybuild.flags.CXXFLAGS + user_CXXFLAGS + ctx.env.CXXFLAGS
    ctx.env.LDFLAGS = mybuild.pybuild.flags.LDFLAGS + user_LDFLAGS + ctx.env.LDFLAGS
    ctx.env.ARFLAGS = mybuild.pybuild.flags.ARFLAGS + user_ARFLAGS + ctx.env.ARFLAGS
    ctx.env.ASFLAGS = mybuild.pybuild.flags.ASFLAGS + user_ASFLAGS + ctx.env.ASFLAGS

    ctx.load('gcc c ar gas')

from waflib.TaskGen import feature, after
from waflib import TaskGen, Task
from waflib import Utils

@TaskGen.extension('.lds.S')
def lds_s_hook(self, node):
    tgtnode = node.change_ext('.lds', '.lds.S')
    self.env['DEFINES'] = self.defines
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
    hdr = header.format(GUARD=self.mod_name.replace('.', '_').upper(),
	OPTIONS=''.join(map(lambda str: '#define %s\n\n' %(str,), self.header_opts)),
	INCLUDES=''.join(map(lambda str: '#include<%s>\n\n' % (str,), self.header_inc)))

    self.target = 'include/module/%s.h' % (self.mod_name.replace('.','/'),)
    self.rule = lambda self: self.outputs[0].write(hdr)

def build(ctx):
    includes = [
		'.',
		'include',
		'src/include',
		'src/arch/{ARCH}/include'.format(ARCH=pyconf.build.ARCH),
		'src/compat/posix/include',
		'src/compat/linux/include']

    ctx.env.target   = pyconf.build.TARGET
    ctx.env.includes = includes

    import mybuild.build

    mybuild.build.waf_entry(ctx) 



