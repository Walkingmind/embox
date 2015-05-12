# Description #

Project Embox has been ported on platform [lego-mindstorms](http://mindstorms.lego.com/en-us/Default.aspx).
We use this platform to show possibilities of Embox to manage realtime systems
which include limited hardware resources.
Platform [Lego Mindstorms](http://en.wikipedia.org/wiki/LEGO_Mindstorms) can work
with two types of controllers: RCX and NXT. LEGO Mindstorms NXT is a computational
module based on Atmel AT91SAM7S256 ARM7TDMI microcontroller and attached to it
AVR controller via I2C interface. AVR is used to collect data from most of the
sensors and control motors. Explanations and the technical specifications below.

<img src='http://embox.googlecode.com/svn/wiki/images/PlatformLegoNxt/9841-0000-xx-12-1.png' width='320' height='240'>

<ul><li>Atmel 32-bit ARM, AT91SAM7S256 microcontroller<br>
<ul><li>256 Kb flash<br>
</li><li>64 Kb RAM<br>
</li><li>48 MHz<br>
</li></ul></li><li>Atmel 8-bit AVR, ATmega48 controller<br>
<ul><li>4 Kb flash<br>
</li><li>512 byte RAM<br>
</li><li>8 MHz<br>
</li></ul></li><li>Bluetooth wireless CSR BlueCore 4 v2.0 +EDR System<br>
</li><li>USB 2.0 full speed (12 Mbit/s)<br>
</li><li>4 input ports<br>
</li><li>3 output ports<br>
</li><li>black and white display 100x64 pixel<br>
</li><li>speaker 2-16 KHz<br>
</li><li>4 buttons<br>
</li><li>6 AA battery/ 1400 mAH accumilator</li></ul>

<img src='http://embox.googlecode.com/svn/wiki/images/PlatformLegoNxt/LEGO-NXT-Scheme.PNG' width='350' height='250'>

OS Embox working on the NXT controller.<br>
<br>
<h1>Development</h1>

The code for the platform part of the Lego Nxt is located in the folder /platform/lego_nxt/.<br>
It contains code driver, description, interfaces, and usage examples.<br>
<br>
To develop under this platform, you must install the environment:<br>
<ul><li>cross-compiler ARM gcc<br>
</li><li>Eclipse (CDT)<br>
</li><li>Cygwin or MinGW (for Windows users)</li></ul>

<h2>Drivers</h2>
Embox supports the following devices that are part of Lego Mindstorms.<br>
<ul><li>motor<br>
</li><li>touch sensor<br>
</li><li>sonar<br>
</li><li>light sensor</li></ul>

<h2>API <a href='under.md'>construction</a></h2>
You can use these functions to work with Lego.<br>
