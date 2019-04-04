#ifndef OAR_JSON_MICRO_H_
#define OAR_JSON_MICRO_H_

#include "project-conf.h"

#include "net/ipv6/uip.h"
#include "net/ipv6/uiplib.h"
#include "net/ipv6/uip-icmp6.h"
#include "net/ipv6/uip-ds6.h"

#if ROUTING_CONF_RPL_LITE
    #include "net/routing/rpl-lite/rpl.h"
#elif ROUTING_CONF_RPL_CLASSIC
    #include "net/routing/rpl-classic/rpl.h"
#endif

#include "net/routing/routing.h"

#include <stdio.h>                  
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "sys/energest.h"
#include "net/ipv6/uip.h"

char oar_json_micro_buf[OAR_CONF_JSON_MICRO_BUF_SIZE];

void oar_json_micro_print(char * str);
void oar_json_micro_construct(char * buf);

#endif // (OAR_JSON_MICRO_H_)

//  {
//      "id": {
//          "t": 105,
//          "mac": "0012.4b00.0f83.b601",
//          "cd": "RED"
//      },
//      "nrg": {
//          "energest": true,
//          "cpu": 19,
//          "lpm": 85,
//          "dLpm": 0,
//          "tT": 105,
//          "rLs": 105,
//          "rTx": 0,
//          "rO": 0
//      },
//      "stats": {
//          "uipStats": true,
//          "rx": 12,
//          "tx": 10,
//          "fw": 0,
//          "dr": 0,
//          "vhlE": 0,
//          "hblE": 0,
//          "lblE": 0,
//          "fragE": 0,
//          "chkE": 0,
//          "protE": 0
//      },
//      "net": {
//          "IPv6": true,
//          "addr": ["null", "fd00::212:4b00:f83:b601", "fe80::212:4b00:f83:b601"],
//          "route": {
//              "df": "fe80::212:4b00:f24:8385",
//              "lt": "infinite"
//          }
//      },
//      "rpl": {
//          "rplLite": true,
//          "nbr": {
//              "inst": true,
//              "cnt": 3,
//              "nbrs": [{
//                  "addr": "fe80::212:4b00:f82:da03",
//                  "rank": 256,
//                  "lMetr": 128,
//                  "rankNbr": 384,
//                  "f": 0,
//                  "r": false,
//                  "b": false,
//                  "a": true,
//                  "p": false,
//                  "lastTx": null,
//                  "bSince": null
//              }, {
//                  "addr": "fe80::212:4b00:f24:8385",
//                  "rank": 128,
//                  "lMetr": 128,
//                  "rankNbr": 256,
//                  "f": 5,
//                  "r": true,
//                  "b": true,
//                  "a": true,
//                  "p": true,
//                  "lastTx": 0,
//                  "bSince": null
//              }, {
//                  "addr": "fe80::212:4b00:f82:a600",
//                  "rank": 307,
//                  "lMetr": 128,
//                  "rankNbr": 435,
//                  "f": 0,
//                  "r": false,
//                  "b": false,
//                  "a": true,
//                  "p": false,
//                  "lastTx": null,
//                  "bSince": null
//              }, null, null]
//          },
//          "status": {
//              "instId": 0,
//              "dag": {
//                  "dType": "node",
//                  "dId": "fd00::212:4b00:f24:8385",
//                  "dVer": 240,
//                  "dPf": "fd00::",
//                  "dPfLen": 64,
//                  "state": "Reachable",
//                  "pPrnt": "fe80::212:4b00:f24:8385",
//                  "rank": 256,
//                  "lRank": 256,
//                  "maxRankInc": 1024,
//                  "dao": {
//                      "lastSent": 241,
//                      "lastAcked": 241
//                  }
//              },
//              "mop": "Non-storing",
//              "of": "MRHOF",
//              "hopRankInc": 128,
//              "defLt": 1800,
//              "dtsnOut": 240,
//              "trickleT": {
//                  "curr": 15,
//                  "min": 12,
//                  "max": 20,
//                  "redund": 0
//              }
//          }
//      }
//  }

