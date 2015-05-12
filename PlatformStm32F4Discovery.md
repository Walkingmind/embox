<img src='http://embox.googlecode.com/svn/wiki/images/PlatformsDescription/stm32f4_discovery.jpg' align='right' width='320' height='240'>

The board has integrated debugger that allows to program it with single USB-A-USB-mini-B wire. You can run and test Embox after few quite simple steps. Please, read it all before doing anything.<br>
<ul><li>Install OpenOCD v0.6.0 or later.<br>
</li><li>Configure and compile with <b>arm/stm32_f4</b> template.<br>
</li><li>In command line run<br>
<pre><code> $ sudo openocd -f /usr/share/openocd/scripts/board/stm32f4discovery.cfg<br>
</code></pre>
</li><li>Load Embox with usual gdb commands<br>
<pre><code> $ gdb build/base/bin/embox<br>
 (gdb) target extended-remote :3333<br>
 (gdb) monitor halt<br>
 (gdb) load<br>
 (gdb) monitor reset<br>
</code></pre>