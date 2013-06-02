
package('embox.kernel')

module(
	'syscall',

    	depends = [
		'embox.arch.syscall',
 		'embox.kernel.syscall_table',
	],

) 
