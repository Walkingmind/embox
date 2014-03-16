/* Setup loopback interface */
"ifconfig lo 127.0.0.1 netmask 255.0.0.0 up",
"route add 127.0.0.0 netmask 255.0.0.0 lo",
/* Setup eth0 interface */
"ifconfig eth0 up",
"ifconfig eth0 192.168.1.5 netmask 255.255.255.0 hw ether AA:BB:CC:DD:EE:02",
"route add 192.168.1.0 netmask 255.255.255.0 eth0",
"date -s 201402111719.20",
"iptables -F INPUT",
"control_srv &",
"login",




