"NAME\n"
"\tping - send ICMP ECHO_REQUEST to network hosts\n"
"SYNOPSIS\n"
"\tping [-I iface] [-c count] [-W timeout] [-t ttl]\n"
"\t[-p pattern] [-t ttl] [-s packsize] [ -i interval]\n"
"\tdestination\n"
"DESCRIPTION\n"
"\tping uses the ICMP protocol s mandatory ECHO_REQUEST\n"
"\tdatagram to elicit an ICMP ECHO_RESPONSE from a host\n"
"\tor gateway.\n"
"\tTest whether a particular host is reachable\n"
"OPTIONS\n"
"\t-I interface\n"
"\t\tSet source address to specified interface address.\n"
"\t\tby default: eth0\n"
"\t-c count\n"
"\t\tStop after sending count ECHO_REQUEST packets.\n"
"\t\tby default: 4 (-1 infinity)\n"
"\t-W timeout\n"
"\t\tTime to wait for a response, in seconds.\n"
"\t\tby default: 1 second\n"
"\t-t ttl\n"
"\t\tSet the IP Time to Live.\n"
"\t-s packetsize\n"
"\t\tSpecifies  the number of data bytes to be sent.\n"
"\t\tThe default is 56.\n"
"\t-i interval\n"
"\t\tWait  interval seconds between sending each packet.\n"
"\t\tThe default is to wait for 1 second\n"
"\t-p pattern\n"
"\t\t16 ``pad'' bytes to fill out the packet you send.\n"
"EXAMPLES\n"
"\tping -c 3 10.0.3.97\n"
"\tThis will send 3 ECHO_REQUEST to 10.0.3.97\n"
"SEE ALSO\n"
"\tifconfig\n"
"AUTHORS\n"
"\tAlexandr Batyukov\n"
"\tAnton Bondarev\n"
"\tNikolay Korotky"