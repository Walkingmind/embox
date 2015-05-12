<img src='http://embox.googlecode.com/svn/wiki/images/PlatformsDescription/ml505.png' align='right' width='320' height='240'>
This page describes how to load Embox image on <a href='http://www.xilinx.com/products/boards-and-kits/HW-V5-ML505-UNI-G.htm'>Virtex-5 LXT FPGA ML505 Evaluation Platform</a>. We assume you have the <a href='http://www.gaisler.com/cms/index.php?option=com_content&task=view&id=13&Itemid=53'>LEON3 CPU</a> firmware flashed on the board.<br>
<br>
<h1>Flashing the image</h1>
To load the image you can use <a href='http://www.gaisler.com/cms/index.php?option=com_content&task=view&id=39&Itemid=253'>GRMON</a> - a debug monitor for LEON processors.  An Evaluation/Academic version for Linux and Windows is available for downloading <a href='ftp://gaisler.com/gaisler.com/grmon/grmon-eval-1.1.44.tar.gz'>here</a>.<br>
<br>
<blockquote>Once you have installed the GRMON, run it:<br>
<pre><code>$ grmon-eval -xilusb -nb -ni<br>
</code></pre></blockquote>

<blockquote>Execute the following commands:<br>
<pre><code>&gt; flash unlock all<br>
&gt; flash erase 0 0x10000<br>
&gt; flash load path/to/embox<br>
&gt; verify path/to/embox<br>
&gt; flash lock all<br>
&gt; quit<br>
</code></pre>