#ifndef OAR_ADDR_H
#define OAR_ADDR_H

#include "net/ipv6/uip.h"
#include "net/ipv6/uiplib.h"
#include "net/ipv6/uip-icmp6.h"
#include "net/ipv6/uip-ds6.h"

#if ROUTING_CONF_RPL_LITE
    #include "net/routing/rpl-lite/rpl.h"
#elif ROUTING_CONF_RPL_CLASSIC
    #include "net/routing/rpl-classic/rpl.h"
#endif

void oar_ipaddr_to_str(char *output, const uip_ipaddr_t *ipaddr);
void oar_ipaddr_to_str(char *output, const uip_ipaddr_t *ipaddr);

const char *oar_ds6_nbr_state_to_str(uint8_t state);
const char *oar_rpl_state_to_str(enum rpl_dag_state state);
const char *oar_rpl_mop_to_str(int mop);
const char *oar_rpl_ocp_to_str(int ocp);





#endif  /* OAR_ADDR_H */