## TSIM ##

  1. Install the last version of [TSIM2 LEON3 Evaluation](http://gaisler.com/index.php/products/simulators/tsim) (Slackware package [here](https://github.com/sikmir/slackbuilds/tree/master/tsim-eval))
  1. tsim-leon3 -fast\_uart -gdb embox
  1. Connect to gdb server
    * if use eclipse see details [here](InstallToolchainEclipseDebug.md)
    * for console debugging you should use command
```
            > sparc-elf-gdb embox
            (gdb) target remote :1234
            (gdb) c
```