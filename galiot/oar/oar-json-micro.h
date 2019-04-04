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

//  {
//  	"id": {
//  		"t": 72,
//  		"mac": "0012.4b00.0f83.b601",
//  		"cd": "RED"
//  	},
//  	"nrg": {
//  		"energest": true,
//  		"cpu": 3,
//  		"lpm": 68,
//  		"dLpm": 0,
//  		"tT": 72,
//  		"rLs": 72,
//  		"rTx": 0,
//  		"rO": 0
//  	},
//  	"stats": {
//  		"uipStats": true,
//  		"rx": 10,
//  		"tx": 9,
//  		"fw": 0,
//  		"dr": 0,
//  		"vhlE": 0,
//  		"hblE": 0,
//  		"lblE": 0,
//  		"fragE": 0,
//  		"chkE": 0,
//  		"protE": 0
//  	},
//  	"net": {
//  		"IPv6": true,
//  		"addr": ["null", "fd00::212:4b00:f83:b601", "fe80::212:4b00:f83:b601"], *
//  		"route": {
//  			"df": "fe80::212:4b00:f24:8385",
//  			"lt": "infinite"
//  		}
//  	}
//  }

#endif // (OAR_JSON_MICRO_H_)