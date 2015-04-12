/* Setup loopback interface */
"ifconfig lo 127.0.0.1 netmask 255.0.0.0 up",
"route add 127.0.0.0 netmask 255.0.0.0 lo",
/* Setup eth0 interface */
"ifconfig eth0 up",
"ifconfig eth0 192.168.51.191 netmask 255.255.255.0 hw ether AA:BB:CC:DD:EE:02",
"route add 192.168.51.0 netmask 255.255.255.0 eth0",
"date -s 201304161719.20",
"iptables -F INPUT",
"iptables -A INPUT ! -s 192.168.51.192 -j DROP",
"tst_srv &",
"login",




