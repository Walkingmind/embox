
package('embox.kernel')

module (
    'irq',

    sources = ['irq.c'],

    depends = [
	'embox.mem.objalloc',
	'embox.driver.interrupt.irqctrl_api',
	'embox.profiler.trace'
    ]
)

module (
    'irq_lock',

    sources = ['irq.c'],

    depends = [
	NoRuntime('critical'),
    ]
)
