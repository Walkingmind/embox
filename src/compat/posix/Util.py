
package('embox.compat.posix.util')

module(
	'All',

    	depends = [
		'getopt',
 		'utsname',
 		'time',
	],

) 
module(
	'getopt',

 	static = True,

  	sources = [
		'getopt.c',
	],

 	depends = [
		'embox.lib.LibC',
	],

) 
module(
	'utsname',

 	static = True,

  	sources = [
		IncludePath('src/compat/posix/include',
                    'utsname.c'),
	],

 	depends = [
		'embox.lib.LibC',
	],

) 
module(
	'time',

 	static = True,

  	sources = [
		'time.c',
	],

 	depends = [
		'embox.kernel.time.kernel_time',
                'embox.lib.LibCMath',
	],

) 
