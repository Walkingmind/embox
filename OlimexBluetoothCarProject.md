# Introduction #

On success of Lego NXT porting with bluetooth remote control ability, it was interesting to repeat those function on more general, cheap and simple hardware.

As a first step, it was chosen to make a bluetooth car, simple toy, that can move by remote control performed via bluetooth.

# Details #
## Hardware ##
  1. Head controller: Olimex SAM7S256 debug board was chosed as well supported and known platform
  1. Bluetooth module: [BTM112](http://www.sparkfun.com/datasheets/Wireless/Bluetooth/BTM112_wATcommands.pdf) as one with simple UART interface
  1. [L298](http://www.sandorobotics.com/attachments/l298motores.pdf) motor driver
  1. Cheap radio RC car toy

Bluetooth was connected to UART1 lines on Olimex SAM7 (RX, TX, CTS, RTS lines). Toy car motors are controlled through motor driver as described in reference to L298.

## Software ##

Embox built with arm/olimex\_bluetooth template.

Flashing firmware can be done throug JTAG or Samba.