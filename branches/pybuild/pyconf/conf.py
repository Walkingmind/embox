
#include('embox.kernel.softirq')
#include('embox.arch.arm.lds')
#include('embox.arch.arm.kernel.arch')
#include('embox.arch.arm.cortexm3.kernel.locore')
#include('embox.arch.system', {'core_freq' : 8000000} )
#include('embox.kernel.stack', { 'stack_size' : 4096, 'alignment' : 4})
#include('embox.kernel.task.idx_table', {'task_res_quantity' : 8})
#include('embox.kernel.task.api' , {'max_resource_size' : 256})
#include('embox.driver.interrupt.stm32_nvic')
#include('embox.driver.clock.stm32_systick')
#include('embox.driver.diag.stm32_usart')
#include('embox.kernel.time.timer')
#include('embox.kernel.timer.timer')
#include('embox.kernel.time.kernel_time')
#include('embox.init.start_script')
#include('embox.cmd.sh.tish')
#include('embox.cmd.version')
#include('embox.cmd.help')
#include('embox.kernel.critical')
#include('embox.kernel.irq')
#include('embox.mem.pool_adapter')
#include('embox.prom.prom_printf')
#include('embox.util.LibUtil')
#include('embox.framework.LibFramework')
#include('embox.arch.arm.libarch')
#include('embox.lib.LibC')
#include('embox.compat.posix.no_open')
#include('embox.util.num_alloc_array')
#include('embox.init.make_term')

include ('embox.kernel.stack')
include ('embox.arch.x86.lds')
include ('embox.arch.x86.kernel.arch')
include ('embox.framework.mod')
include ('embox.driver.interrupt.i8259')
include ('embox.framework.runlevel')
include ('embox.kernel.kernel', runlevel=0)
include ('embox.lib.LibC')
include ('embox.kernel.critical')
include ('embox.kernel.irq')
include ('embox.driver.diag.i8250', {'baud_rate': IntegerDom([115200])})
#include ('embox.arch.arm.libarch')
