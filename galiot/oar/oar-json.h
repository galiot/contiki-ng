////////////////////////
// galiot (2018/2019) //
////////////////////////

#ifndef OAR_JSON_H_
#define OAR_JSON_H_

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

void oar_json_print(char * str);
void oar_json_construct(char * buf, int i);

void oar_json_lladdr_to_str(char *output, const linkaddr_t *lladdr);

#endif // (OAR_JSON_QUANTIZED_H_)

//  {
//      "id": {
//          "t": 51,
//          "mac": "0012.4b00.0f83.b601"
//      },
//      "nrg": {
//          "e": true,
//          "c": 7,
//          "l": 43,
//          "dL": 0,
//          "tT": 51,
//          "rL": 51,
//          "rT": 0,
//          "rO": 0
//      },
//      "st": {
//          "uS": true,
//          "rx": 7,
//          "tx": 7,
//          "fw": 0,
//          "dr": 0,
//          "vE": 0,
//          "hE": 0,
//          "lE": 0,
//          "fE": 0,
//          "cE": 0,
//          "pE": 0
//      },
//      "net": {
//          "v6": true,
//          "addr": ["null", "fd00::212:4b00:f83:b601", "fe80::212:4b00:f83:b601"],
//          "rt": {
//              "df": "fe80::212:4b00:f24:8385",
//              "lt": "infinite"
//          }
//      },
//      "rpl": {
//          "rL": true,
//          "nbr": {
//              "i": true,
//              "c": 3,
//              "ns": [{
//                  "ad": "fe80::212:4b00:f82:a600",
//                  "rk": 274,
//                  "lM": 128,
//                  "rkN": 402,
//                  "f": 0,
//                  "r": false,
//                  "b": false,
//                  "a": true,
//                  "p": false,
//                  "lTx": null,
//                  "bS": null
//              }, {
//                  "ad": "fe80::212:4b00:f24:8385",
//                  "rk": 128,
//                  "lM": 128,
//                  "rkN": 256,
//                  "f": 5,
//                  "r": true,
//                  "b": true,
//                  "a": true,
//                  "p": true,
//                  "lTx": 0,
//                  "bS": null
//              }, {
//                  "ad": "fe80::212:4b00:f82:da03",
//                  "rk": 256,
//                  "lM": 128,
//                  "rkN": 384,
//                  "f": 0,
//                  "r": false,
//                  "b": false,
//                  "a": true,
//                  "p": false,
//                  "lTx": null,
//                  "bS": null
//              }, null, null]
//          },
//          "st": {
//              "iId": 0,
//              "dag": {
//                  "dT": "node",
//                  "dId": "fd00::212:4b00:f24:8385",
//                  "dVer": 240,
//                  "dPf": "fd00::",
//                  "dPfL": 64,
//                  "st": "Reachable",
//                  "pP": "fe80::212:4b00:f24:8385",
//                  "rk": 256,
//                  "lRk": 256,
//                  "maxRkI": 1024,
//                  "dao": {
//                      "lS": 241,
//                      "lA": 241
//                  }
//              },
//              "mop": "Non-storing",
//              "of": "MRHOF",
//              "hRkI": 128,
//              "dLt": 1800,
//              "dtsnO": 240,
//              "tT": {
//                  "cur": 13,
//                  "min": 12,
//                  "max": 20,
//                  "red": 0
//              }
//          }
//      }
//  }

