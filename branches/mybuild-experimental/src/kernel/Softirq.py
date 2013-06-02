
package('embox.kernel')

module(
    'softirq',
    sources = ['softirq.c'],

    options = [
	Integer('nrs_total', default = 32)
    ],

    depends = [
        NoRuntime('critical'),
    ],
)
