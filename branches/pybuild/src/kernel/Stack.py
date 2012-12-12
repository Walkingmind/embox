
package('embox.kernel')

from string import Template

def incl_trigger(scope, find_fn):
    sects = find_fn('embox.arch.arm.lds.sections')
    sz = scope.value(find_fn('stack.stack_size'))
    alignment = scope.value(find_fn('stack.alignment'))

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
    new_dom = scope[sects] + [out]
    return cut(scope, sects, new_dom)

module (
    "stack",

    #sources = [LDScript("stack.lds.S")],

    depends = ['embox.arch.arm.lds'],

    include_trigger = incl_trigger,

    options = [
	Integer('stack_size', default = 65536),
	Integer('alignment',  default = 0x1000),
    ]
)

