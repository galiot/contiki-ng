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
void oar_json_construct(char * buf, int rcrd, int ndx);

void oar_json_lladdr_to_str(char *output, const linkaddr_t *lladdr);

#endif // (OAR_JSON_QUANTIZED_H_)