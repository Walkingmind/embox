
package('embox.driver.video')

interface('vesa')
 
module(
	'vesadrv',

 	implements = ['vesa'],

  	sources = [
		'vesa.c',
	],

 ) 
