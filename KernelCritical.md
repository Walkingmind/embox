**Critical API** is a special mechanism for tracking the current execution context. An execution context is primarily defined by _conditions_ under which the context may be entered and _capabilities_ of the code running inside it.

To make it easier to understand what is execution context, lets consider an interrupt handler as an example:
  * An interrupt can happen if its priority is higher then the current Interrupt Priority Level or, more precisely, when two conditions are met: interrupts are not disabled by call to `ipl_save()`, and there is no interrupt with higher priority is being handled right now.
  * The interrupt handler can access only a limited set of resources. For instance, it can wake up threads waiting for some event, but it can't lock a mutex or create a new thread.

Depending on how the system is configured there can be different sets of possible execution contexts.

| | Thread switch | Handling Soft IRQ | Handling IRQ |
|:|:--------------|:------------------|:-------------|
| Outside critical context | <font color='green'><b>Permitted</b></font> | <font color='green'><b>Permitted</b></font> | <font color='green'><b>Permitted</b></font> |
| Inside `sched_lock` block | <font color='maroon'><b>Forbidden</b></font> | <font color='green'><b>Permitted</b></font> | <font color='green'><b>Permitted</b></font> |
| Inside Soft IRQ handler | <font color='maroon'><b>Forbidden</b></font> | <font color='olive'><b>Depends on Priority</b></font> | <font color='green'><b>Permitted</b></font> |
| Inside `softirq_lock` block | <font color='maroon'><b>Forbidden</b></font> | <font color='maroon'><b>Forbidden</b></font> | <font color='green'><b>Permitted</b></font> |
| Inside IRQ handler | <font color='maroon'><b>Forbidden</b></font> | <font color='maroon'><b>Forbidden</b></font> | <font color='olive'><b>Depends on Priority</b></font> |
| Inside `irq_lock` block | <font color='maroon'><b>Forbidden</b></font> | <font color='maroon'><b>Forbidden</b></font> | <font color='maroon'><b>Forbidden</b></font> |