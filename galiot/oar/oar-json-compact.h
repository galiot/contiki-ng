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








// void oar_json_compact_lladdr_to_str(char *output, const linkaddr_t *lladdr);
    
// const char *oar_json_compact_ds6_nbr_state_to_str(uint8_t state);
// const char *oar_json_compact_rpl_state_to_str(enum rpl_dag_state state);
// const char *oar_json_compact_rpl_mop_to_str(int mop);
// const char *oar_json_compact_rpl_ocp_to_str(int ocp);

// char oar_json_compact_ipaddr[UIPLIB_IPV6_MAX_STR_LEN];
// char oar_json_compact_lladdr[UIPLIB_IPV6_MAX_STR_LEN];



// ==================================================
char oar_json_compact_buf[OAR_CONF_JSON_COMPACT_BUF_SIZE];
void oar_json_compact_print(char * str);
void oar_json_compact_construct(char * buf);
// ==================================================



// void oar_json_energest(unsigned long int system_time);









#endif // (OAR_COMPACT_DEBUG_H_)