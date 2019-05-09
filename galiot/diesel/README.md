oar
===
A not-so-minimal Contiki-NG backend application:

```
$ make TARGET=cc26x0-cc13x0 BOARD=launchpad/cc2650 savetarget
$ make distclean && make
```

If debuging options are enabled, serial output should be observed:
(ttyACMx the port designation of the mote serial, for example ttyACM2)

```
$ make TARGET=cc26x0-cc13x0 BOARD=launchpad/cc2650 PORT=/dev/ttyACMx login
```
