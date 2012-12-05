
import pyconf.build

top = '.'
out = 'build'

def options(ctx):
    pass

def configure(ctx):
    ctx.env.CC = pyconf.build.CROSS_COMPILE + "gcc"
    ctx.env.AR = pyconf.build.CROSS_COMPILE + "gcc"
    ctx.load('gcc ar')

def build(ctx):
    print ctx.env.CC
    pass
