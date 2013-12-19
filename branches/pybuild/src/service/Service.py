
package('embox.sevice')

module(
	'SrvLib',

   	sources = [
		'srv_lib.c',
	],

 ) 
module(
	'Index_service',

   	sources = [
		'index_service.c',
	],

 	depends = [
		'SrvLib',
	],

) 
module(
	'Test_service',

   	sources = [
		IncludePath('third-party/lib/expat',
                    'test_service.c'),
	],

 	depends = [
		'SrvLib',
 		'embox.third_party.expat.expat_lib',
	],

) 