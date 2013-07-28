/* Setup loopback interface */
"ifconfig lo 127.0.0.1 netmask 255.0.0.0 up",
"route add 127.0.0.0 netmask 255.0.0.0 lo",
/* Setup eth0 interface */
"ifconfig eth0 10.0.2.16 netmask 255.255.255.0 hw ether AA:BB:CC:DD:EE:02 up",
"route add 10.0.2.0 netmask 255.255.255.0 eth0",
"route add default gw 10.0.2.10 eth0",
"mkdir /mandatory_test",
"mount -t ext2 /dev/hda /mandatory_test",

"smac_adm -R high_label -o low_label  -a r",
"smac_adm -R low_label  -o high_label -a w",
"smac_adm -R _  	-o smac_admin -a rw",

"smac_adm -R confidentially -o unclassified  -a r",
"smac_adm -R confidentially -o service  -a r",
"smac_adm -R confidentially -o secret  -a r",

"smac_adm -R secret -o unclassified  -a r",
"smac_adm -R secret -o service  -a r",

"smac_adm -R service -o unclassified  -a r",

"smac_adm -R high_label		-o default   -a rwx",
"smac_adm -R low_label		-o default   -a rwx",
"smac_adm -R confidentially  	-o default   -a rwx",
"smac_adm -R secret  		-o default   -a rwx",
"smac_adm -R service    	-o default   -a rwx",
"smac_adm -R unclassified    	-o default   -a rwx",
"smac_adm -R _			-o default   -a rwx",

"login",
