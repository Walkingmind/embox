
package('embox.compat.posix.proc')

module(
	'All',

    	depends = [
		'exec',
 		'fork',
 		'wait',
 		'signal',
	],

) 
module(
	'exec',

 	static = True,

  	sources = [
		IncludePath('src/compat/posix/include',
                    'exec.c'),
	],

 	depends = [
		'embox.util.LibUtil',
	],

) 
module(
	'fork',

 	static = True,

  	sources = [
		IncludePath('src/compat/posix/include',
                    'fork.c'),
	],

 	depends = [
		'embox.util.LibUtil',
	],

) 
module(
	'wait',

 	static = True,

  	sources = [
		IncludePath('src/compat/posix/include',
                    'wait.c'),
	],

 	depends = [
		'embox.util.LibUtil',
	],

) 
module(
	'signal',

 	static = True,

  	sources = [
		IncludePath('src/compat/posix/include',
                    'signal.c'),
	],

 	depends = [
		'embox.kernel.task.std_signal',
 		'embox.kernel.task.rt_signal',
	],

) 
