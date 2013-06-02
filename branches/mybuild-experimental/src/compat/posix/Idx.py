
package('embox.compat.posix.idx')

module(
	'All',

    	depends = [
		'isatty',
 		'select',
 		'dup',
                'pipe',
	],

) 
module(
	'isatty',

 	static = True,

  	sources = [
		IncludePath('src/compat/posix/include',
                    'isatty.c'),
	],

 	depends = [
		'embox.kernel.task.api',
	],

) 
module(
	'select',

 	static = True,

  	sources = [
		IncludePath('src/compat/posix/include',
                    'select.c'),
	],

 	depends = [
		'embox.kernel.task.api',
 		'embox.compat.posix.io_sync',
	],

) 
module(
	'dup',

 	static = True,

  	sources = [
		IncludePath('src/compat/posix/include',
                    'dup.c'),
	],

 	depends = [
		'embox.kernel.task.api',
	],

) 
module(
	'pipe',

 	static = True,

 	options = [
		Integer('pipe_buffer_size', default=256),
 		Integer('max_pipe_buffer_size', default=1024),
	],

 	sources = [
		IncludePath('src/compat/posix/include',
                    'pipe.c'),
	],

 	depends = [
		'embox.mem.heap_api',
 		'embox.util.LibSync',
 		'embox.kernel.task.api',
 		'embox.util.LibUtil',
 		'embox.compat.posix.io_sync',
	],

) 
