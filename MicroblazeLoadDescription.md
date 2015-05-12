<img src='http://embox.googlecode.com/svn/wiki/images/PlatformsDescription/HW-SPAR3AN-SK-UNI-G.png' align='right' width='320' height='240'>

This page is about running Embox on <a href='http://www.xilinx.com/products/boards-and-kits/HW-SPAR3AN-SK-UNI-G.htm'>Spartan-3AN Starter Kit</a> - FPGA platform evaluation board.<br>
<br>
<h1>Step-by-step</h1>

<ol><li>Install <a href='http://downloads.sourceforge.net/linux-hotplug/fxload-2008_10_13.tar.gz'>fxload</a>
</li><li>Install <b>Xilinx_11.1_ISE_DS_SFD.tar</b>
<pre><code>sudo ./xsetup<br>
</code></pre>
</li><li>Choose to install <b>Embedded Development Kit</b>. Cable drivers probably wouldn't install, so we use drivers from here : <a href='http://rmdir.de/~michael/xilinx/'>http://rmdir.de/~michael/xilinx/</a>. You should not worry, we place precompiled drivers to package below.<br>
</li><li>Download <a href='http://embox.googlecode.com/files/xilinx-spartan-dev-kit.tar.gz'>http://embox.googlecode.com/files/xilinx-spartan-dev-kit.tar.gz</a>, and run debug from there<br>
<pre><code> ./debug<br>
</code></pre>
</li><li>Attach with...<br>
<pre><code>mb-gdb -nw path/to/embox<br>
</code></pre>
</li></ol><blockquote>... and execute these commands:<br>
<pre><code>&gt; target remote localhost:1234<br>
&gt; load<br>
&gt; define ss<br>
&gt; si<br>
&gt; x/2i $pc<br>
&gt; end<br>
</code></pre>