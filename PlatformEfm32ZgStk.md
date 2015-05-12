<img src='http://www.silabs.com/SiteCollectionImages/board-images/efm32zg-stk3200.png' align='right'>
The board features EFM32ZG222F32 Zero Gecko MCU and on-board SEGGER J-Link debugger.<br>
<br>
<h3>Install Toolchain</h3>

<ol><li>Download linux installation toolchain from <a href='https://launchpad.net/gcc-arm-embedded/+download'>https://launchpad.net/gcc-arm-embedded/+download</a>. You need file like gcc-arm-none-eabi-4_8-<code>*</code>-linux.tar.bz2<br>
</li><li>Extract it somewhere. I will assume system-wide installation to <code>/opt</code>, but it could be any directory.<br>
<pre><code>$ cd /opt<br>
$ sudo tar -axf ~/Downloads/gcc-arm-none-eabi-4_8-2013q4-20131204-linux.tar.bz2<br>
</code></pre>
(Because <code>/opt</code> isn't writeable to regular user it is called via <code>sudo</code>)<br>
</li><li>Download and extract SEGGER J-Link software pack for Linux (32 or 64 bit TGZ) from <a href='http://www.segger.com/jlink-software.html'>http://www.segger.com/jlink-software.html</a> When serial number requested click on "I do not have a serial number because I own an eval board with J-Link on-board"</li></ol>

<h3>Configure and build Embox</h3>
<ol><li>Grab an Embox copy. Open termial and  change directory to it's root<br>
<pre><code>$ cd ~/embox<br>
</code></pre>
</li><li>Load template <code>platform/efm32zg_sk3200/debug</code>
<pre><code>$ make confload-platform/efm32zg_sk3200/debug<br>
</code></pre>
</li><li>If you extracted toolchain not to <code>/opt</code>, edit <code>conf/build.conf</code>, change <code>CROSS_COMPILE</code> to match toolchain extraction dir. If you extracted toolchain in <code>~/gcc-arm-embedded</code>, then <code>CROSS_COMPILE</code> should be like<br>
<pre><code>CROSS_COMPILE = ~/gcc-arm-embedded/gcc-arm-none-eabi-4_8-2013q4/bin/arm-none-eabi-<br>
</code></pre>
</li><li>Build it<br>
<pre><code>$ make<br>
</code></pre>
You should see <code>Build complete</code> at the end.</li></ol>

<h3>Load Embox</h3>
Now you should have one terminal opened with Embox root current directory and Embox should be successfully built.<br>
<ol><li>Open second terminal and change directory to SEGGER package extracted directory.<br>
</li><li>In second terminal, run JLink <code>gdb</code> server<br>
<pre><code>$ sudo ./JLinkGDBServer<br>
...<br>
J-Link found 1 JTAG device, Total IRLen = 4<br>
JTAG ID: 0x0BC11477 (Cortex-M0)<br>
Connected to target<br>
Waiting for GDB connection...<br>
</code></pre>
</li><li>Switch to the first terminal with Embox and run <code>gdb</code> from toolchain to debug <code>embox</code> after <code>.gdbinit</code> script loaded. If you've placed toolchain not in <code>/opt</code>, provide another path for gdb.<br>
<pre><code>$ /opt/gcc-arm-none-eabi-4_8-2013q4/bin/arm-none-eabi-gdb build/base/bin/embox -x platform/efm32zg_sk3200/.gdbinit<br>
Target interface speed set to 30 kHz<br>
Target endianess set to "little endian"<br>
Resetting target<br>
Select auto target interface speed (2000 kHz)<br>
Selecting device: EFM32ZG222F32<br>
Flash breakpoints enabled<br>
(gdb) <br>
</code></pre>
</li><li>load Embox to target and start it<br>
<pre><code>(gdb) load<br>
Loading section .text, size 0x53b4 lma 0x0<br>
Loading section .ARM.exidx, size 0x8 lma 0x53b4<br>
Loading section .rodata, size 0x1e20 lma 0x53c0<br>
Loading section .data, size 0x1a0 lma 0x71e0<br>
Start address 0x74, load size 29564<br>
Transfer rate: 14435 KB/sec, 5912 bytes/write.<br>
(gdb) c<br>
Continuing.<br>
</code></pre>