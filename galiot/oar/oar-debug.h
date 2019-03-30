#ifndef PROJECT_DEBUG_H_
#define PROJECT_DEBUG_H_

// ----------------------------------------------------------------------------

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



void oar_debug_(char dash, int times);

// ========================================================================================== // Energest

#if (ENERGEST_CONF_ON)

    // static unsigned long to_seconds(uint64_t time);
    void oar_debug_energest(unsigned long int system_time);

#endif // (ENERGEST_CONF_ON)

// ========================================================================================== // uIP TCP/IP Statistics

#if (UIP_CONF_STATISTICS)

    void oar_debug_stats_ip(unsigned long int system_time);
    void oar_debug_stats_icmp(unsigned long int system_time);

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    #if (UIP_TCP)

        void oar_debug_stats_tcp(unsigned long int system_time);

    #endif // (UIP_TCP)
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    #if (UIP_UDP)

        void oar_debug_stats_udp(unsigned long int system_time);

    #endif // (UIP_UDP)
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    void oar_debug_stats_nd6(unsigned long int system_time);

#endif // (UIP_CONF_STATISTICS)

// ========================================================================================== // contiki-ng Shell (gets)

#if (OAR_DEBUG_SHELL)

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    #if (NETSTACK_CONF_WITH_IPV6)
    
        void oar_debug_ipaddr_to_str(char *output, const uip_ipaddr_t *ipaddr);
    
    #endif // (NETSTACK_CONF_WITH_IPV6)
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    void oar_debug_lladdr_to_str(char *output, const linkaddr_t *lladdr);
    
    const char *oar_debug_ds6_nbr_state_to_str(uint8_t state);
    const char *oar_debug_rpl_state_to_str(enum rpl_dag_state state);
    const char *oar_debug_rpl_mop_to_str(int mop);
    const char *oar_debug_rpl_ocp_to_str(int ocp);
    
    char oar_debug_ipaddr[UIPLIB_IPV6_MAX_STR_LEN];
    char oar_debug_lladdr[UIPLIB_IPV6_MAX_STR_LEN];
    
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    #if (ROUTING_CONF_RPL_LITE)
    
        void oar_debug_cmd_rpl_nbr(unsigned long int system_time);
        void oar_debug_cmd_rpl_status(unsigned long int system_time);
    
    #endif // (ROUTING_CONF_RPL_LITE)
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    
    void oar_debug_cmd_macaddr(unsigned long int system_time);
    
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    #if (NETSTACK_CONF_WITH_IPV6)
    
        void oar_debug_cmd_ipaddr(unsigned long int system_time);
        void oar_debug_cmd_ip_neighbors(unsigned long int system_time);
    
    #endif // (NETSTACK_CONF_WITH_IPV6)
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    #if (MAC_CONF_WITH_TSCH)
    
        void oar_debug_cmd_tsch_status(unsigned long int system_time);
    
    #endif // (MAC_CONF_WITH_TSCH)
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    #if (NETSTACK_CONF_WITH_IPV6)
    
        void oar_debug_cmd_routes(unsigned long int system_time);
    
    #endif // (NETSTACK_CONF_WITH_IPV6)
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#endif // (OAR_DEBUG_SHELL)
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    























#endif /* PROJECT_DEBUG_H_ */