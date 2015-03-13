/* Setup loopback interface */
"ifconfig lo 127.0.0.1 netmask 255.0.0.0 up",
"route add 127.0.0.0 netmask 255.0.0.0 lo",
"ifconfig eth0 10.0.1.2 netmask 255.255.255.0 hw ether AA:BB:CC:DD:EE:12 up",
"route add 10.0.1.0 netmask 255.255.255.0 eth0",
"ifconfig eth1 10.0.2.2 netmask 255.255.255.0 hw ether AA:BB:CC:DD:EE:22 up",
"route add 10.0.2.0 netmask 255.255.255.0 eth1",