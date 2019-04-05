#ifndef OAR_JSON_EXTENDED_H_
#define OAR_JSON_EXTENDED_H_

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


// char oar_json_extended_buf[OAR_CONF_JSON_BUF_SIZE];
void oar_json_extended_print(char * str);
void oar_json_extended_construct(char * buf);

#endif // (OAR_DEBUG_EXTENDED_H_)





//    {
//        "system": {
//            "contikiVersion": "Contiki-NG-release/v4.2-266-g1d586e448-dirty",
//            "routing": "RPL Lite",
//            "net": "sicslowpan",
//            "mac": "CSMA",
//            "ieee802154panid": "0xabcd",
//            "ieee802154TSCHDefaultHoppingSequenceLength": null,
//            "ieee802154defaultChannel": 26,
//            "nodeId": 46593,
//            "linkLayerAddress": "0012.4b00.0f83.b601",
//            "TentativeLinkLocalIPv6address": "fe80::212:4b00:f83:b601"
//        },
//        "id": {
//            "systemTime": 93,
//            "systemCode": "RED"
//        },
//        "energy": {
//            "valid": true,
//            "cpu": 27,
//            "lpm": 66,
//            "deepLpm": 0,
//            "totalTime": 93,
//            "radioListen": 93,
//            "radioTransmit": 0,
//            "radioOff": 0
//        },
//        "stats": {
//            "valid": true,
//            "ip": {
//                "recv": 18,
//                "sent": 15,
//                "forwarded": 4,
//                "drop": 0,
//                "vhlerr": 0,
//                "hblenerr": 0,
//                "lblenerr": 0,
//                "fragerr": 0,
//                "chkerr": 0,
//                "protoerr": 0
//            },
//            "icmp": {
//                "recv": 14,
//                "sent": 11,
//                "drop": 0,
//                "typeerr": 0,
//                "chkerr": 0
//            },
//            "tcp": {
//                "tcpUsed": false,
//                "recv": null,
//                "sent": null,
//                "drop": null,
//                "chkerr": null,
//                "ackerr": null,
//                "rst": null,
//                "rexmit": null,
//                "syndrop": null,
//                "synrst": null
//            },
//            "udp": {
//                "udpUsed": true,
//                "drop": 0,
//                "recv": 0,
//                "sent": 0,
//                "chkerr": 0
//            },
//            "nd6": {
//                "drop": 0,
//                "recv": 0,
//                "sent": 0
//            }
//        },
//        "net": {
//            "rplLiteUsed": true,
//            "rplNbr": {
//                "valid": true,
//                "currentInstanceUsed": true,
//                "rplNeighborCount": 3,
//                "rplNeighbors": [{
//                    "ipAddr": "fe80::212:4b00:f24:8385",
//                    "rank": 128,
//                    "linkMetric": 128,
//                    "rankViaNbr": 256,
//                    "freshStats": 7,
//                    "rootRank": true,
//                    "bestNbr": true,
//                    "acceptRank_AND_acceptPrnt": true,
//                    "prefParent": true,
//                    "lastTxMinutesAgo": 0,
//                    "betterParentSinceMinute": null
//                }, {
//                    "ipAddr": "fe80::212:4b00:f82:a600",
//                    "rank": 384,
//                    "linkMetric": 128,
//                    "rankViaNbr": 512,
//                    "freshStats": 2,
//                    "rootRank": false,
//                    "bestNbr": false,
//                    "acceptRank_AND_acceptPrnt": true,
//                    "prefParent": false,
//                    "lastTxMinutesAgo": 0,
//                    "betterParentSinceMinute": null
//                }, {
//                    "ipAddr": "fe80::212:4b00:f82:da03",
//                    "rank": 546,
//                    "linkMetric": 128,
//                    "rankViaNbr": 674,
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
//                "valid": true,
//                "instanceId": 0,
//                "dag": {
//                    "valid": true,
//                    "dagType": "node",
//                    "dagId": "fd00::212:4b00:f24:8385",
//                    "dagVersion": 240,
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
//                    "current": 14,
//                    "min": 12,
//                    "max": 20,
//                    "redundency": 0
//                }
//            },
//            "nodeMacAddress": "0012.4b00.0f83.b601",
//            "ipv6Used": true,
//            "ipAddr": {
//                "valid": true,
//                "nodeIpv6addresses": ["null", "fd00::212:4b00:f83:b601", "fe80::212:4b00:f83:b601"],
//                "addrIssuedCount": 2
//            },
//            "ipNbr": {
//                "valid": true,
//                "nodeIpv6neigbors": [{
//                    "ipAddr": "fe80::212:4b00:f24:8385",
//                    "llAddr": "0012.4b00.0f24.8385",
//                    "router": 0,
//                    "state": "Reachable"
//                }, {
//                    "ipAddr": "fe80::212:4b00:f82:a600",
//                    "llAddr": "0012.4b00.0f82.a600",
//                    "router": 0,
//                    "state": "Reachable"
//                }, {
//                    "ipAddr": "fe80::212:4b00:f82:da03",
//                    "llAddr": "0012.4b00.0f82.da03",
//                    "router": 0,
//                    "state": "Reachable"
//                }, {
//                    "ipAddr": null,
//                    "llAddr": null,
//                    "router": null,
//                    "state": null
//                }, {
//                    "ipAddr": null,
//                    "llAddr": null,
//                    "router": null,
//                    "state": null
//                }],
//                "ipNbrCount": 3
//            },
//            "routes": {
//                "valid": true,
//                "defaultRoute": "fe80::212:4b00:f24:8385",
//                "lifetimeSeconds": "infinite",
//                "routingLinks": {
//                    "valid": true,
//                    "links": ["null", "null", "null", "null", "null"],
//                    "uipSrLinkCount": "none"
//                },
//                "routingEntries": {
//                    "valid": false,
//                    "total": null,
//                    "entries": [{
//                        "route": null,
//                        "via": null,
//                        "lifetime": null
//                    }, {
//                        "route": null,
//                        "via": null,
//                        "lifetime": null
//                    }, {
//                        "route": null,
//                        "via": null,
//                        "lifetime": null
//                    }, {
//                        "route": null,
//                        "via": null,
//                        "lifetime": null
//                    }, {
//                        "route": null,
//                        "via": null,
//                        "lifetime": null
//                    }]
//                }
//            }
//        }
//    }