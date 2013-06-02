
package('embox.kernel')

module (
    'irq',

    sources = ['irq.c'],

    depends = [
        'irq_lock',
        'embox.mem.objalloc',
        'embox.driver.interrupt.irqctrl_api',
        'embox.profiler.trace'
    ]
)

module (
    'irq_lock',

    sources = ['irq_lock.c'],

    depends = [
	NoRuntime('critical'),
    ]
)
