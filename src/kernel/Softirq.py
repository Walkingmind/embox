
package('embox.kernel')

module(
    'softirq',
    sources = ['softirq.c'],
    options = {
	'nrs_total' : 32
    }
)
