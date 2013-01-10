
#include('embox.kernel.softirq')
#include('embox.arch.x86.lds', {'sections' : ()})

#include ('embox.kernel.stack', stack_size = 1, alignment = 2)
#include ('embox.arch.x86.kernel.arch')
#include ('embox.arch.x86.kernel.interrupt')
#include ('embox.arch.x86.kernel.context')
#include ('embox.arch.system')
#include ('embox.framework.mod')
#include ('embox.driver.interrupt.i8259')
#include ('embox.framework.runlevel')
#include ('embox.lib.LibC')
#include ('embox.kernel.critical')
#include ('embox.kernel.irq')
#include ('embox.driver.diag.i8250', baud_rate = 115200)
#include ('embox.prom.prom_printf')

include ('embox.arch.x86.lds', runlevel = 2)
include ('embox.arch.x86.kernel.arch', runlevel = 2)
include ('embox.arch.x86.kernel.locore', runlevel = 2)
include ('embox.arch.x86.kernel.context', runlevel = 2)
include ('embox.arch.x86.kernel.interrupt', runlevel = 2)
include ('embox.arch.x86.stackframe', runlevel = 2)
include ('embox.lib.debug.Backtrace', runlevel = 2)
include ('embox.driver.interrupt.i8259', runlevel = 2)
include ('embox.driver.clock.pit', runlevel = 2)
include ('embox.driver.terminal', runlevel = 2)
include ('embox.driver.keyboard', runlevel = 2)
include ('embox.driver.net.ne2k_pci', runlevel = 2)
include ('embox.driver.diag.i8250', baud_rate=38400, runlevel = 2)
include ('embox.driver.serial.serial_port', baud_rate=38400, runlevel = 2)
include ('embox.driver.net.loopback', runlevel = 2)
include ('embox.profiler.tracing', runlevel = 2)
include ('embox.driver.ide', runlevel = 2)
include ('embox.fs.node', fnode_quantity=128, runlevel = 2)
include ('embox.fs.driver.fat', inode_quantity=128, runlevel = 2)
include ('embox.fs.driver.cdfs', runlevel = 2)
#include ('embox.fs.driver.initfs', runlevel = 2)
include ('embox.fs.driver.nfs', runlevel = 2)
include ('embox.fs.driver.tmpfs', runlevel = 2)
include ('embox.fs.rootfs', runlevel = 2)

include ('embox.kernel.time.timer', runlevel = 1)
include ('embox.kernel.time.kernel_time', runlevel = 1)
include ('embox.kernel.thread.core', thread_pool_size =  512, thread_stack_size = 0x4000, runlevel = 1)
include ('embox.test.critical', runlevel = 1)
include ('embox.test.framework.mod.member.ops_test', runlevel = 1)
include ('embox.test.kernel.softirq_test', runlevel = 1)
include ('embox.test.kernel.timer_test', runlevel = 1)
include ('embox.test.recursion', runlevel = 1)
include ('embox.test.kernel.timer.sleep_test', runlevel = 1)
include ('embox.test.stdlib.bsearch_test', runlevel = 1)
include ('embox.test.stdlib.qsort_test', runlevel = 1)
include ('embox.test.stdlib.math_test', runlevel = 1)
include ('embox.test.fs.ramdisk_test', runlevel = 1)
include ('embox.test.fs.filesystem_test', runlevel = 1)
include ('embox.test.fs.file_test', runlevel = 1)
include ('embox.test.util.array_test', runlevel = 1)
include ('embox.test.util.bit_test', runlevel = 1)
include ('embox.test.util.list_test', runlevel = 1)
include ('embox.test.util.slist_test', runlevel = 1)
include ('embox.test.util.tree_test', runlevel = 1)
include ('embox.test.util.tree_set_test', runlevel = 1)
include ('embox.test.mem.pool', runlevel = 1)
include ('embox.test.net.socket.port_test', runlevel = 1)
include ('embox.test.kernel.thread.thread_priority_test', runlevel = 1)
include ('embox.test.net.parser.url_parser_test', runlevel = 1)
#include ('embox.test.net.parser.request_parser_test', runlevel = 1)
include ('embox.test.third_party.trex_test', runlevel = 1)
include ('embox.cmd.shell', runlevel = 3)
include ('embox.cmd.sh.tish', runlevel = 3)
include ('embox.init.start_script', shell_name = "tish",tty_dev="uart",input_buffer=80, runlevel = 3)

#include ('embox.cmd.net.arp')
#include ('embox.cmd.net.arping')
#include ('embox.cmd.net.rarping')
#include ('embox.cmd.net.ifconfig')
#include ('embox.cmd.net.ping')
#include ('embox.cmd.net.route')
#include ('embox.cmd.net.tftp')
#include ('embox.cmd.fs.cat')
#include ('embox.cmd.fs.ls')
#include ('embox.cmd.md5sum')
#include ('embox.cmd.fs.rm')
#include ('embox.cmd.example')
#include ('embox.cmd.help')
#include ('embox.cmd.lsmod')
#include ('embox.cmd.lspci')
#include ('embox.cmd.man')
#include ('embox.cmd.mem')
#include ('embox.cmd.test')
#include ('embox.cmd.version')
#include ('embox.cmd.wmem')
#include ('embox.cmd.log')
#include ('embox.cmd.net.httpd')
#include ('embox.cmd.net.servd')
#include ('embox.cmd.net.telnetd')
#include ('embox.cmd.fs.mkfs')
#include ('embox.cmd.fs.mount')
#include ('embox.cmd.fs.echo')
#include ('embox.cmd.fs.touch')
#include ('embox.cmd.fs.mkdir')
#include ('embox.cmd.fs.cp')
#include ('embox.cmd.net.nslookup')
#include ('embox.cmd.ide')
#include ('embox.cmd.memmap')
#include ('embox.cmd.thread')

#include ('embox.example.net.tcp_accepter')
#include ('embox.example.net.gethostent')
#include ('embox.example.net.gethostbyname')
#include ('embox.example.net.tcp_connect')
#include ('embox.example.net.tcp_receiver')
#include ('embox.example.net.tcp_echo')
#include ('embox.example.net.tcp_sender')
#include ('embox.example.net.httpd')
#include ('embox.example.net.checkopts')
#include ('embox.example.net.rpc.msg_clnt')

include ('embox.net.core', runlevel = 2)
include ('embox.net.socket', runlevel = 2)
include ('embox.net.dev', runlevel = 2)
include ('embox.net.af_inet', runlevel = 2)
include ('embox.net.ipv4', runlevel = 2)
include ('embox.net.arp', runlevel = 2)
include ('embox.net.rarp', runlevel = 2)
include ('embox.net.icmp', runlevel = 2)
include ('embox.net.udp', runlevel = 2)
include ('embox.net.tcp', runlevel = 2)
include ('embox.net.udp_sock', runlevel = 2)
include ('embox.net.tcp_sock', runlevel = 2)
include ('embox.net.raw_sock', runlevel = 2)
include ('embox.net.eth', runlevel = 2)
include ('embox.net.net_entry', runlevel = 2)

include ('embox.kernel.thread.sched_policy.priority_based', runlevel = 2)
include ('embox.kernel.timer.sleep', runlevel = 2)
include ('embox.kernel.timer.timer', runlevel = 2)
include ('embox.kernel.softirq', runlevel = 2)
include ('embox.kernel.irq', runlevel = 2)
include ('embox.kernel.critical', runlevel = 2)

include ('embox.mem.pool_adapter', runlevel = 2)
include ('embox.kernel.task.multi', runlevel = 2)
include ('embox.prom.prom_printf', runlevel = 2)
include ('embox.mem.bitmask', runlevel = 2)
include ('embox.mem.heap_bm', heap_size=16777216, runlevel = 2)

include ('embox.util.LibUtil', runlevel = 2)
include ('embox.framework.LibFramework', runlevel = 2)
include ('embox.arch.x86.libarch', runlevel = 2)
include ('embox.lib.LibC', runlevel = 2)
