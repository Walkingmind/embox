
package('embox.kernel')

def incl_trigger(scope, find_fn):
    from string import Template
    from pybuild.ops import *

    sects = find_fn('embox.arch.x86.lds.sections')
    sz = find_fn('stack.stack_size').value(scope)
    alignment = find_fn('stack.alignment').value(scope)

    tmpl = '''
	.stack (NOLOAD): {
		. = ALIGN($align);
		ALIGNMENT();
		. += $sz;
		ALIGNMENT();
		. = ALIGN($align);
		__stack = .;
	} SECTION_REGION(stack)
	SECTION_SYMBOLS(stack)
'''
    out = Template(tmpl).substitute(align = alignment, sz = sz) 
    new_dom = scope[sects] + [(99, out)]
    return cut(scope, sects, new_dom)

module (
    "stack",

    #sources = [LDScript("stack.lds.S")],

    depends = ['embox.arch.x86.lds'],

    include_trigger = incl_trigger,

    options = [
	Integer('stack_size', default = 65536),
	Integer('alignment',  default = 0x1000),
    ]
)

