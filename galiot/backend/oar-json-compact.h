////////////////////////
// galiot (2018/2019) //
////////////////////////

#ifndef OAR_JSON_COMPACT_H_
#define OAR_JSON_COMPACT_H_

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

void oar_json_compact_lladdr_to_str(char *output, const linkaddr_t *lladdr);

void oar_json_compact_print(char * str);
void oar_json_compact_construct(char * buf);

#endif // (OAR_COMPACT_DEBUG_H_)





//    {
//        "id": {
//            "systemTime": 75,
//            "macAddr": "0012.4b00.0f83.b601",
//            "systemCode": "RED"
//        },
//        "erg": {
//            "energest": true,
//            "cpu": 30,
//            "lpm": 44,
//            "deepLpm": 0,
//            "totalTime": 75,
//            "radioListen": 75,
//            "radioTransmit": 0,
//            "radioOff": 0
//        },
//        "stats": {
//            "uipStats": true,
//            "recv": 8,
//            "sent": 10,
//            "forwarded": 0,
//            "drop": 0,
//            "vhlerr": 0,
//            "hblenerr": 0,
//            "lblenerr": 0,
//            "fragerr": 0,
//            "chkerr": 0,
//            "protoerr": 0
//        },
//        "net": {
//            "IPv6": true,
//            "addresses": ["null", "fd00::212:4b00:f83:b601", "fe80::212:4b00:f83:b601"],
//            "routes": {
//                "defaultRoute": "fe80::212:4b00:f24:8385",
//                "lifetimeSeconds": "infinite"
//            }
//        },
//        "rpl": {
//            "rplLite": true,
//            "rplNbr": {
//                "currentInstanceUsed": true,
//                "rplNeighborCount": 3,
//                "rplNeighbors": [{
//                    "ipAddr": "fe80::212:4b00:f24:8385",
//                    "rank": 128,
//                    "linkMetric": 128,
//                    "rankViaNbr": 256,
//                    "freshStats": 5,
//                    "rootRank": true,
//                    "bestNbr": true,
//                    "acceptRank_AND_acceptPrnt": true,
//                    "prefParent": true,
//                    "lastTxMinutesAgo": 1,
//                    "betterParentSinceMinute": null
//                }, {
//                    "ipAddr": "fe80::212:4b00:f82:a600",
//                    "rank": 256,
//                    "linkMetric": 128,
//                    "rankViaNbr": 384,
//                    "freshStats": 1,
//                    "rootRank": false,
//                    "bestNbr": false,
//                    "acceptRank_AND_acceptPrnt": true,
//                    "prefParent": false,
//                    "lastTxMinutesAgo": 0,
//                    "betterParentSinceMinute": null
//                }, {
//                    "ipAddr": "fe80::212:4b00:f82:da03",
//                    "rank": 281,
//                    "linkMetric": 128,
//                    "rankViaNbr": 409,
//                    "freshStats": 0,
//                    "rootRank": false,
//                    "bestNbr": false,
//                    "acceptRank_AND_acceptPrnt": true,
//                    "prefParent": false,
//                    "lastTxMinutesAgo": null,
//                    "betterParentSinceMinute": null
//                }, null, null]
//            },
//            "rplStatus": {
//                "instanceId": 0,
//                "dag": {
//                    "dagType": "node",
//                    "dagId": "fd00::212:4b00:f24:8385",
//                    "dagVersion": 9,
//                    "dagPrefix": "fd00::",
//                    "dagPrefixLength": 64,
//                    "state": "Reachable",
//                    "preferredParent": "fe80::212:4b00:f24:8385",
//                    "rank": 256,
//                    "lowestRank": 256,
//                    "maxRankInc": 1024,
//                    "daoSequence": {
//                        "valid": true,
//                        "lastSent": 241,
//                        "lastAcked": 241
//                    }
//                },
//                "mop": "Non-storing",
//                "of": "MRHOF",
//                "hopRankIncrement": 128,
//                "defaultLifetime": 1800,
//                "dtsnOut": 240,
//                "trickleTimer": {
//                    "valid": true,
//                    "current": 16,
//                    "min": 12,
//                    "max": 20,
//                    "redundency": 0
//                }
//            }
//        }
//    }

