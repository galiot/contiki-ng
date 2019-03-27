oar
===
A minimal Contiki-NG backend application, simple acquiring, printing and sending out
several mote statistics, comprised of 3 discrete information groups:

* Energest statistics, for power consumption monitoring purposes.
* Link statistics, for network quality-of-service monitoring purposes.
* Routing statistics, for network behaviour monitoring purposes.

This application runs a full IPv6 stack with 6LoWPAN and RPL.
It extends the following examples:

* hello-world, part of the Contiki operating system.
* websense-db, part of "Practical Contiki-NG: Programming for Wireless Sensor Networks" by Agus Kurniawan (2018)

```
$ make TARGET=cc26x0-cc13x0 BOARD=launchpad/cc2650 savetarget
$ make distclean && make
```

If debuging options are enables, serial output should be observed:
(ttyACMx the port designation of the mote serial, for example ttyACM2)

```
$ make TARGET=cc26x0-cc13x0 BOARD=launchpad/cc2650 PORT=/dev/ttyACMx login
```
