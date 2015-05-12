

# Introduction #

The terminal is a server which allows serial input/output through a hardware device driver. It looks like as tty devices in **NIX** systems. A process/thread can request a terminal during creation.

We separate three levels of the terminal:
| shell   | command interpreter |
|:--------|:--------------------|
| console | tty driver |
| port    | device driver |

# Features #
  1. We can setup different device drivers
  1. We can setup different command interpreters
  1. We can setup different mode of console (VT102, VT100...)
  1. We can setup different mode of console (Raw, CANONICAL)
  1. We can use very simple console (the only output) or statically linked part of terminal

# Roadmap #
The first of our terminal was described [here](RuIOShell.md).

Started milestone 0.1.8 we decided rework this subsystem duided by the requirements of the Features. First of all we made up our mind to implement [simple terminal](RuShellTalking.md)