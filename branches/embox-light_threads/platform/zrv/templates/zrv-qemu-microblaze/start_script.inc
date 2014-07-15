"ifconfig lo 127.0.0.1 netmask 255.0.0.0 up",
"route add 127.0.0.0 netmask 255.0.0.0 lo",
/* Setup eth0 interface */
"ifconfig eth0 up",
"ifconfig eth0 10.0.2.16 netmask 255.255.255.0 hw ether AA:BB:CC:DD:EE:02",
"route add 10.0.2.0 netmask 255.255.255.0 eth0",
"date -s 201304161719.20",
"mkdir /mnt",

"smac_adm -R high_label -o low_label  -a r",
"smac_adm -R low_label  -o high_label -a w",
"smac_adm -R _  	-o smac_admin -a r",

"smac_adm -R confidentially -o unclassified  -a r",
"smac_adm -R confidentially -o service  -a r",
"smac_adm -R confidentially -o secret  -a r",

"smac_adm -R secret -o unclassified  -a r",
"smac_adm -R secret -o service  -a r",

"smac_adm -R service -o unclassified  -a r",

"su -c telnetd &",
/*"su -c dropbeard", */
"dropbeard",
"su -c httpd &",
"su -c snmpd &",

"login &",
