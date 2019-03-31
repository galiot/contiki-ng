#include "oar-json.h"

#include "contiki.h"
#include "contiki-net.h"
#include "sys/node-id.h"
#include "sys/platform.h"
#include "sys/energest.h"
#include "sys/stack-check.h"
#include "dev/watchdog.h"






// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

void oar_json_ipaddr_to_str(char *output, const uip_ipaddr_t *ipaddr) 
{
    char buf[UIPLIB_IPV6_MAX_STR_LEN];                                      // UIPLIB_IPV6_MAX_STR_LEN == 40
    
    memset(output, 0, sizeof(output));                                      // initialization of outpout string
    uiplib_ipaddr_snprint(buf, sizeof(buf), ipaddr);                        // function that creates string from ipaddr

    strcpy(output, buf);                                                    // cannot return string, local scope
}

// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

void oar_json_lladdr_to_str(char *output, const linkaddr_t *lladdr) 
{
    char buf[5];                                                            // temporary string, local scope
    memset(output, 0, sizeof(output));                                      // initialization of outpout string (else concatenates)

    if (lladdr == NULL)
    {
        strcpy(output, "(NULL LL addr");                                    
    }
    else
    {
        unsigned int i;
        for (i = 0; i < LINKADDR_SIZE; i++)
        {
            if (i > 0 && i % 2 == 0)
            {
                strcat(output, ".");
            }
            
            sprintf(buf, "%02x", lladdr->u8[i]);
            strcat(output, buf);
        }
    }
}


// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

#if (ENERGEST_CONF_ON)

    static unsigned long oar_json_to_seconds(uint64_t time)
    {
        return (unsigned long)(time / ENERGEST_SECOND);
    }

#endif  // (ENERGEST_CONF_ON)
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^


// ----------------------------------------------------------------------------
// function that provides context for ds6 neighbor state
const char *oar_json_ds6_nbr_state_to_str(uint8_t state)
{
    switch(state) 
    {
        case NBR_INCOMPLETE:    return "Incomplete";
        case NBR_REACHABLE:     return "Reachable";
        case NBR_STALE:         return "Stale";
        case NBR_DELAY:         return "Delay";
        case NBR_PROBE:         return "Probe";
        default:                return "Unknown";
    }
}

// ----------------------------------------------------------------------------
// function that provides context for RPL directed acyclic graph (DAG) state
const char *oar_json_rpl_state_to_str(enum rpl_dag_state state)
{
    switch(state) 
    {
        case DAG_INITIALIZED:   return "Initialized";
        case DAG_JOINED:        return "Joined";
        case DAG_REACHABLE:     return "Reachable";
        case DAG_POISONING:     return "Poisoning";
        default:                return "Unknown";
    }
}

// ----------------------------------------------------------------------------
// function that provides context for RPL mode of operation (MOP) state
const char *oar_json_rpl_mop_to_str(int mop)
{
    switch(mop) 
    {
        case RPL_MOP_NO_DOWNWARD_ROUTES: return "No downward routes";
        case RPL_MOP_NON_STORING: return "Non-storing";
        case RPL_MOP_STORING_NO_MULTICAST: return "Storing";
        case RPL_MOP_STORING_MULTICAST: return "Storing+multicast";
        default: return "Unknown";
    }
}

// ----------------------------------------------------------------------------
// function that provides context for RPL objective code point (OCP)
const char *oar_json_rpl_ocp_to_str(int ocp)
{
    switch(ocp) 
    {
        case RPL_OCP_OF0: return "OF0";
        case RPL_OCP_MRHOF: return "MRHOF";
        default: return "Unknown";
    }
}








// ====================================================================================================================

char oar_json_buf[1000];

void oar_json_print(char * buf)
{
    printf("%s\n", buf);
}

void oar_json_init(char * buf)
{
    memset(buf, 0, sizeof(buf));        // initialization
}

void oar_json_enter(char * buf)
{
    char str[128];
    sprintf(str,    "{" );  strcat(buf, str);
}

void oar_json_bridge(char * buf)
{
    char str[128];
    sprintf(str,    "," );  strcat(buf, str);
}

void oar_json_exit(char * buf)
{
    char str[128];
    sprintf(str,    "}" );  strcat(buf, str);
}

// id
// contikiVesrsion                          CONTIKI_VERSION_STRING
// routing                  %s              NETSTACK_ROUTING.name                                   Routing
// net                      %s              NETSTACK_NETWORK.name                                   Net
// mac                      %s              NETSTACK_MAC.name                                       MAC
// ieee802154panid          %04x            IEEE802154_PANID                                        802.15.4 PANID
// ieee802154tschDHSL       %u              (unsigned)sizeof(TSCH_DEFAULT_HOPPING_SEQUENCE)         802.15.4 TSCH default hopping sequence length
// ieee802154defCh          %u              IEEE802154_DEFAULT_CHANNEL                              802.15.4 Default channel
// nodeId                   %u              node_id                                                 Node Id
// lladdr                   %s              &linkaddr_node_addr                                     Link-layer address
// tent6lladdr              %s              lladdr != NULL ? &lladdr->ipaddr : NULL                 Tentative link-local IPv6 address

void oar_json_append_system(char * buf)
{
    char str[128];

    // -------------------------------------------------------------------------------
    sprintf(str,    "\""    "system"    "\""    ":");   strcat(buf, str);
    sprintf(str,    "{" );                              strcat(buf, str);
    // -------------------------------------------------------------------------------

    sprintf(str,        "\""    "contikiVersion"                                "\""    ":" "\""    CONTIKI_VERSION_STRING      "\""                                                        );  strcat(buf, str);   sprintf(str,    "," );  strcat(buf, str);
    sprintf(str,        "\""    "routing"                                       "\""    ":" "\""    "%s"                        "\""    ,NETSTACK_ROUTING.name                              );  strcat(buf, str);   sprintf(str,    "," );  strcat(buf, str);
    sprintf(str,        "\""    "net"                                           "\""    ":" "\""    "%s"                        "\""    ,NETSTACK_NETWORK.name                              );  strcat(buf, str);   sprintf(str,    "," );  strcat(buf, str);
    sprintf(str,        "\""    "mac"                                           "\""    ":" "\""    "%s"                        "\""    ,NETSTACK_MAC.name                                  );  strcat(buf, str);   sprintf(str,    "," );  strcat(buf, str);
    sprintf(str,        "\""    "ieee802154panid"                               "\""    ":" "\""    "0x%04x"                    "\""    ,IEEE802154_CONF_PANID                              );  strcat(buf, str);   sprintf(str,    "," );  strcat(buf, str);
    
    // ############################################################
    #if MAC_CONF_WITH_TSCH

    sprintf(str,        "\""    "ieee802154TSCHDefaultHoppingSequenceLength"    "\""    ":"         "%u"                                ,(unsigned)sizeof(TSCH_DEFAULT_HOPPING_SEQUENCE)    );  strcat(buf, str);   sprintf(str,    "," );  strcat(buf, str);
    
    #else   // MAC_CONF_WITH_TSCH

    sprintf(str,        "\""    "ieee802154defaultChannel"                      "\""    ":"         "%u"                                ,IEEE802154_DEFAULT_CHANNEL                         );  strcat(buf, str);   sprintf(str,    "," );  strcat(buf, str);
    
    #endif  // MAC_CONF_WITH_TSCH
    // ############################################################

    sprintf(str,        "\""    "nodeId"                                         "\""    ":"        "%u"                                ,node_id                                            );  strcat(buf, str);   sprintf(str,    "," );  strcat(buf, str);
    
    oar_json_lladdr_to_str(oar_json_lladdr, &linkaddr_node_addr);
    sprintf(str,        "\""    "linkLayerAddress"                               "\""    ":" "\""    "%s"                    "\""       ,oar_json_lladdr                                    );  strcat(buf, str);   sprintf(str,    "," );  strcat(buf, str);
                                                                                                                                                                                                
    // ############################################################
    #if NETSTACK_CONF_WITH_IPV6

    uip_ds6_addr_t *lladdr;
    memcpy(&uip_lladdr.addr, &linkaddr_node_addr, sizeof(uip_lladdr.addr));
    lladdr = uip_ds6_get_link_local(-1);
    
    oar_json_ipaddr_to_str(oar_json_ipaddr, lladdr != NULL ? &lladdr->ipaddr : NULL);
    sprintf(str,        "\""    "TentativeLinkLocalIPv6address"                 "\""    ":" "\""    "%s"                    "\""       ,oar_json_ipaddr                                    );   strcat(buf, str);   // sprintf(str,    "," );  strcat(buf, str);
    
    #else   // NETSTACK_CONF_WITH_IPV6
    
    sprintf(str,        "\""    "TentativeLinkLocalIPv6address"                 "\""    ":"         "null"                             ,oar_json_ipaddr                                    );   strcat(buf, str);   // sprintf(str,    "," );  strcat(buf, str);
    
    #endif  // NETSTACK_CONF_WITH_IPV6
    // ############################################################

    // -------------------------------------------------------------------------------
    sprintf(str,    "}" );   strcat(buf, str);
    // ------------------------------------------------------------------------------- 

}




void oar_json_append_id(char * buf)
{
    char str[128];

    // -------------------------------------------------------------------------------
    sprintf(str,    "\""    "id"    "\""    ":" );  strcat(buf, str);
    sprintf(str,    "{" );                          strcat(buf, str);
    // -------------------------------------------------------------------------------
    
    sprintf(str,        "\""    "systemTime"    "\""    ":"        "%lu"                                    ,clock_seconds()    );  strcat(buf, str);   sprintf(str,    "," );  strcat(buf, str);
    sprintf(str,        "\""    "systemCode"    "\""    ":" "\""    OAR_CONF_MOTE_COLOR         "\""                            );  strcat(buf, str);   // sprintf(str,    "," );  strcat(buf, str);
    
    // -------------------------------------------------------------------------------
    sprintf(str,    "}" );   strcat(buf, str);
    // -------------------------------------------------------------------------------
}




void oar_json_append_energy(char * buf)
{
    char str[128];

    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    #if (ENERGEST_CONF_ON)

    energest_flush();       // Update all energest times.
    
    // -------------------------------------------------------------------------------
    sprintf(str,    "\""    "energy"    "\""    ":" );  strcat(buf, str);   
    sprintf(str,    "{" );                              strcat(buf, str);
    // -------------------------------------------------------------------------------

    sprintf(str,        "\""    "valid"         "\""    ":" "true"                                                                                                                                             );  strcat(buf, str); sprintf(str, "," );  strcat(buf, str);
    sprintf(str,        "\""    "cpu"           "\""    ":" "%lu"   ,oar_json_to_seconds(energest_type_time(ENERGEST_TYPE_CPU))                                                                                );  strcat(buf, str);    sprintf(str, "," );  strcat(buf, str);
    sprintf(str,        "\""    "lpm"           "\""    ":" "%lu"   ,oar_json_to_seconds(energest_type_time(ENERGEST_TYPE_LPM))                                                                                );  strcat(buf, str);    sprintf(str, "," );  strcat(buf, str);
    sprintf(str,        "\""    "deepLpm"       "\""    ":" "%lu"   ,oar_json_to_seconds(energest_type_time(ENERGEST_TYPE_DEEP_LPM))                                                                           );  strcat(buf, str);    sprintf(str, "," );  strcat(buf, str);
    sprintf(str,        "\""    "totalTime"     "\""    ":" "%lu"   ,oar_json_to_seconds(ENERGEST_GET_TOTAL_TIME())                                                                                            );  strcat(buf, str);    sprintf(str, "," );  strcat(buf, str);
    sprintf(str,        "\""    "radioListen"   "\""    ":" "%lu"   ,oar_json_to_seconds(energest_type_time(ENERGEST_TYPE_LISTEN))                                                                             );  strcat(buf, str);    sprintf(str, "," );  strcat(buf, str);
    sprintf(str,        "\""    "radioTransmit" "\""    ":" "%lu"   ,oar_json_to_seconds(energest_type_time(ENERGEST_TYPE_TRANSMIT))                                                                           );  strcat(buf, str);    sprintf(str, "," );  strcat(buf, str);
    sprintf(str,        "\""    "radioOff"      "\""    ":" "%lu"   ,oar_json_to_seconds(ENERGEST_GET_TOTAL_TIME() - energest_type_time(ENERGEST_TYPE_TRANSMIT) - energest_type_time(ENERGEST_TYPE_LISTEN))    );  strcat(buf, str);    // sprintf(str, "," );  strcat(buf, str);
    
    // ------------------------------------------------------------------------------
    sprintf(str,    "}" );  strcat(buf, str);
    // ------------------------------------------------------------------------------

    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    #else   // (ENERGEST_CONF_ON)
    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

    // -------------------------------------------------------------------------------
    sprintf(str,    "\""    "energy"    "\""    ":" );  strcat(buf, str);   
    sprintf(str,    "{" );                                 strcat(buf, str);
    // -------------------------------------------------------------------------------

    sprintf(str,        "\""    "valid"         "\""    ":" "false" );  strcat(buf, str); sprintf(str, "," );  strcat(buf, str);
    sprintf(str,        "\""    "cpu"           "\""    ":" "null"  );  strcat(buf, str);    sprintf(str, "," );  strcat(buf, str);
    sprintf(str,        "\""    "lpm"           "\""    ":" "null"  );  strcat(buf, str);    sprintf(str, "," );  strcat(buf, str);
    sprintf(str,        "\""    "deepLpm"       "\""    ":" "null"  );  strcat(buf, str);    sprintf(str, "," );  strcat(buf, str);
    sprintf(str,        "\""    "totalTime"     "\""    ":" "null"  );  strcat(buf, str);    sprintf(str, "," );  strcat(buf, str);
    sprintf(str,        "\""    "radioListen"   "\""    ":" "null"  );  strcat(buf, str);    sprintf(str, "," );  strcat(buf, str);
    sprintf(str,        "\""    "radioTransmit" "\""    ":" "null"  );  strcat(buf, str);    sprintf(str, "," );  strcat(buf, str);
    sprintf(str,        "\""    "radioOff"      "\""    ":" "null"  );  strcat(buf, str);    // sprintf(str, "," );  strcat(buf, str);
    
    // ------------------------------------------------------------------------------
    sprintf(str,    "}" );  strcat(buf, str);
    // ------------------------------------------------------------------------------

    #endif  // (ENERGEST_CONF_ON)
    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
}





//       (ip.recv) >                            received packets at the IP layer
//       (ip.sent) >                                sent packets at the IP layer
//  (ip.forwarded) >                           forwarded packets at the IP layer
//       (ip.drop) >                             dropped packets at the IP layer
//     (ip.vhlerr) >    packets dropped due to wrong IP version or header length
//   (ip.hblenerr) >           packets dropped due to wrong IP length, high byte
//   (ip.lblenerr) >            packets dropped due to wrong IP length, low byte
//    (ip.fragerr) >              packets dropped because they were IP fragments
//     (ip.chkerr) >                   packets dropped due to IP checksum errors
//   (ip.protoerr) > packets dropped because they were neither ICMP, UDP nor TCP

//     (icmp.recv) >                                       received ICMP packets
//     (icmp.sent) >                                           sent ICMP packets
//     (icmp.drop) >                                        dropped ICMP packets
//  (icmp.typeerr) >                              ICMP packets with a wrong type
//   (icmp.chkerr) >                            ICMP packets with a bad checksum

//      (tcp.recv) >                                       received TCP segments
//      (tcp.sent) >                                           sent TCP segments
//      (tcp.drop) >                                        dropped TCP segments
//    (tcp.chkerr) >                            TCP segments with a bad checksum
//    (tcp.ackerr) >                          TCP segments with a bad ACK number
//       (tcp.rst) >                           received TCP RST (reset) segments
//    (tcp.rexmit) >                                  retransmitted TCP segments
//   (tcp.syndrop) >     dropped SYNs because too few connections were available
//    (tcp.synrst) >                     SYNs for closed ports, triggering a RST

//      (udp.drop) >                                        dropped UDP segments
//      (udp.recv) >                                       received UDP segments
//      (udp.sent) >                                           sent UDP segments
//    (udp.chkerr) >                            UDP segments with a bad checksum

//      (nd6.drop) >                                         dropped ND6 packets
//      (nd6.recv) >                                         dropped ND6 packets
//      (nd6.sent) >                                         dropped ND6 packets

void oar_json_append_stats(char * buf)
{
    char str[128];
    
    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    #if (UIP_CONF_STATISTICS)

    // -------------------------------------------------------------------------------
    sprintf(str,    "\""   "stats"  "\""    ":" );  strcat(buf, str);
    sprintf(str,    "{" );                          strcat(buf, str);
    // --------------------------------------------------------------------------------

    sprintf(str,    "\""    "valid"      "\""    ":" "true");  strcat(buf, str); sprintf(str, "," );  strcat(buf, str);

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    
    sprintf(str,        "\""    "ip"        "\""    ":" );  strcat(buf, str);
    
    sprintf(str, "{" );  strcat(buf, str);
    
    sprintf(str,    "\""    "recv"      "\""    ":" "%lu"   ,uip_stat.ip.recv       );  strcat(buf, str); sprintf(str, "," );  strcat(buf, str);
    sprintf(str,    "\""    "sent"      "\""    ":" "%lu"   ,uip_stat.ip.sent       );  strcat(buf, str); sprintf(str, "," );  strcat(buf, str);
    sprintf(str,    "\""    "forwarded" "\""    ":" "%lu"   ,uip_stat.ip.forwarded  );  strcat(buf, str); sprintf(str, "," );  strcat(buf, str);
    sprintf(str,    "\""    "drop"      "\""    ":" "%lu"   ,uip_stat.ip.drop       );  strcat(buf, str); sprintf(str, "," );  strcat(buf, str);
    sprintf(str,    "\""    "vhlerr"    "\""    ":" "%lu"   ,uip_stat.ip.vhlerr     );  strcat(buf, str); sprintf(str, "," );  strcat(buf, str);
    sprintf(str,    "\""    "hblenerr"  "\""    ":" "%lu"   ,uip_stat.ip.hblenerr   );  strcat(buf, str); sprintf(str, "," );  strcat(buf, str);
    sprintf(str,    "\""    "lblenerr"  "\""    ":" "%lu"   ,uip_stat.ip.lblenerr   );  strcat(buf, str); sprintf(str, "," );  strcat(buf, str);
    sprintf(str,    "\""    "fragerr"   "\""    ":" "%lu"   ,uip_stat.ip.fragerr    );  strcat(buf, str); sprintf(str, "," );  strcat(buf, str);
    sprintf(str,    "\""    "chkerr"    "\""    ":" "%lu"   ,uip_stat.ip.chkerr     );  strcat(buf, str); sprintf(str, "," );  strcat(buf, str);
    sprintf(str,    "\""    "protoerr"  "\""    ":" "%lu"   ,uip_stat.ip.protoerr   );  strcat(buf, str); sprintf(str, "," );  //strcat(buf, str);                                                                                                                                                                                      

    sprintf(str, "}" ); strcat(buf, str);

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    sprintf(str, ",");  strcat(buf, str);
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    
    sprintf(str,        "\""    "icmp"        "\""    ":" );  strcat(buf, str);
    
    sprintf(str, "{" );  strcat(buf, str);
    
    sprintf(str,    "\""    "recv"      "\""    ":" "%lu"   ,uip_stat.icmp.recv     );  strcat(buf, str); sprintf(str, "," );  strcat(buf, str);
    sprintf(str,    "\""    "sent"      "\""    ":" "%lu"   ,uip_stat.icmp.sent     );  strcat(buf, str); sprintf(str, "," );  strcat(buf, str);
    sprintf(str,    "\""    "drop"      "\""    ":" "%lu"   ,uip_stat.icmp.drop     );  strcat(buf, str); sprintf(str, "," );  strcat(buf, str);
    sprintf(str,    "\""    "typeerr"   "\""    ":" "%lu"   ,uip_stat.icmp.typeerr  );  strcat(buf, str); sprintf(str, "," );  strcat(buf, str);
    sprintf(str,    "\""    "chkerr"    "\""    ":" "%lu"   ,uip_stat.icmp.chkerr   );  strcat(buf, str); sprintf(str, "," );  //strcat(buf, str);                                                     

    sprintf(str, "}" ); strcat(buf, str);                                                                                                                                                                              

    // ############################################################
    #if (UIP_TCP)

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    sprintf(str, ",");  strcat(buf, str);
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    sprintf(str,        "\""    "tcp"        "\""    ":" );  strcat(buf, str);
    
    sprintf(str, "{" );  strcat(buf, str);
    
    sprintf(str,    "\""    "tcpUsed"   "\""    ":" "true"                          );  strcat(buf, str); sprintf(str, "," );  strcat(buf, str);
    sprintf(str,    "\""    "recv"      "\""    ":" "%lu"   ,uip_stat.tcp.recv      );  strcat(buf, str); sprintf(str, "," );  strcat(buf, str);
    sprintf(str,    "\""    "sent"      "\""    ":" "%lu"   ,uip_stat.tcp.sent      );  strcat(buf, str); sprintf(str, "," );  strcat(buf, str);
    sprintf(str,    "\""    "drop"      "\""    ":" "%lu"   ,uip_stat.tcp.drop      );  strcat(buf, str); sprintf(str, "," );  strcat(buf, str);
    sprintf(str,    "\""    "chkerr"    "\""    ":" "%lu"   ,uip_stat.tcp.chkerr    );  strcat(buf, str); sprintf(str, "," );  strcat(buf, str);
    sprintf(str,    "\""    "ackerr"    "\""    ":" "%lu"   ,uip_stat.tcp.ackerr    );  strcat(buf, str); sprintf(str, "," );  strcat(buf, str);
    sprintf(str,    "\""    "rst"       "\""    ":" "%lu"   ,uip_stat.tcp.rst       );  strcat(buf, str); sprintf(str, "," );  strcat(buf, str);
    sprintf(str,    "\""    "rexmit"    "\""    ":" "%lu"   ,uip_stat.tcp.rexmit    );  strcat(buf, str); sprintf(str, "," );  strcat(buf, str);
    sprintf(str,    "\""    "syndrop"   "\""    ":" "%lu"   ,uip_stat.tcp.syndrop   );  strcat(buf, str); sprintf(str, "," );  strcat(buf, str);
    sprintf(str,    "\""    "synrst"    "\""    ":" "%lu"   ,uip_stat.tcp.synrst    );  strcat(buf, str); sprintf(str, "," );  //strcat(buf, str);                                                                                                                                                                                      

    sprintf(str, "}" ); strcat(buf, str);
    
    #else   // (UIP,TCP)
    
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    sprintf(str, ",");  strcat(buf, str);
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~                                                                                                                        

    sprintf(str,        "\""    "tcp"        "\""    ":" );  strcat(buf, str);
    
    sprintf(str, "{" );  strcat(buf, str);
    
    sprintf(str,    "\""    "tcpUsed"   "\""    ":" "false" );  strcat(buf, str); sprintf(str, "," );  strcat(buf, str);
    sprintf(str,    "\""    "recv"      "\""    ":" "null"  );  strcat(buf, str); sprintf(str, "," );  strcat(buf, str);
    sprintf(str,    "\""    "sent"      "\""    ":" "null"  );  strcat(buf, str); sprintf(str, "," );  strcat(buf, str);
    sprintf(str,    "\""    "drop"      "\""    ":" "null"  );  strcat(buf, str); sprintf(str, "," );  strcat(buf, str);
    sprintf(str,    "\""    "chkerr"    "\""    ":" "null"  );  strcat(buf, str); sprintf(str, "," );  strcat(buf, str);
    sprintf(str,    "\""    "ackerr"    "\""    ":" "null"  );  strcat(buf, str); sprintf(str, "," );  strcat(buf, str);
    sprintf(str,    "\""    "rst"       "\""    ":" "null"  );  strcat(buf, str); sprintf(str, "," );  strcat(buf, str);
    sprintf(str,    "\""    "rexmit"    "\""    ":" "null"  );  strcat(buf, str); sprintf(str, "," );  strcat(buf, str);
    sprintf(str,    "\""    "syndrop"   "\""    ":" "null"  );  strcat(buf, str); sprintf(str, "," );  strcat(buf, str);
    sprintf(str,    "\""    "synrst"    "\""    ":" "null"  );  strcat(buf, str); sprintf(str, "," );  //strcat(buf, str);                                                                                                                                                                                      

    sprintf(str, "}" ); strcat(buf, str);
    
    #endif  // (UIP_TCP)
    // ############################################################

    // ############################################################
    #if (UIP_UDP)

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    sprintf(str, ",");  strcat(buf, str);
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ 

    sprintf(str,        "\""    "udp"        "\""    ":" );  strcat(buf, str);
    
    sprintf(str, "{" );  strcat(buf, str);
    
    sprintf(str,    "\""    "udpUsed"   "\""    ":" "true"                          );  strcat(buf, str); sprintf(str, "," );  strcat(buf, str);
    sprintf(str,    "\""    "drop"      "\""    ":" "%lu"   ,uip_stat.udp.drop      );  strcat(buf, str); sprintf(str, "," );  strcat(buf, str);
    sprintf(str,    "\""    "recv"      "\""    ":" "%lu"   ,uip_stat.udp.recv      );  strcat(buf, str); sprintf(str, "," );  strcat(buf, str);
    sprintf(str,    "\""    "sent"      "\""    ":" "%lu"   ,uip_stat.udp.sent      );  strcat(buf, str); sprintf(str, "," );  strcat(buf, str);
    sprintf(str,    "\""    "chkerr"    "\""    ":" "%lu"   ,uip_stat.udp.chkerr    );  strcat(buf, str); sprintf(str, "," );  //strcat(buf, str);                                                     

    sprintf(str, "}" ); strcat(buf, str); 

    #else   // (UIP,UDP)

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    sprintf(str, ",");  strcat(buf, str);
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ 

    sprintf(str,        "\""    "udp"        "\""    ":" );  strcat(buf, str);
    
    sprintf(str, "{" );  strcat(buf, str);
    
    sprintf(str,    "\""    "udpUsed"   "\""    ":" "false" );  strcat(buf, str); sprintf(str, "," );  strcat(buf, str);
    sprintf(str,    "\""    "drop"      "\""    ":" "null"  );  strcat(buf, str); sprintf(str, "," );  strcat(buf, str);
    sprintf(str,    "\""    "recv"      "\""    ":" "null"  );  strcat(buf, str); sprintf(str, "," );  strcat(buf, str);
    sprintf(str,    "\""    "sent"      "\""    ":" "null"  );  strcat(buf, str); sprintf(str, "," );  strcat(buf, str);
    sprintf(str,    "\""    "chkerr"    "\""    ":" "null"  );  strcat(buf, str); sprintf(str, "," );  //strcat(buf, str);                                                     

    sprintf(str, "}" ); strcat(buf, str); 

    #endif  // (UIP_UDP)
    // ############################################################

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    sprintf(str, ",");  strcat(buf, str);
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~    
    
    sprintf(str,        "\""    "nd6"        "\""    ":" );  strcat(buf, str);
    
    sprintf(str, "{" );  strcat(buf, str);

    sprintf(str,    "\""    "drop"  "\""    ":" "%lu"   ,uip_stat.nd6.drop  );  strcat(buf, str); sprintf(str, "," );  strcat(buf, str);
    sprintf(str,    "\""    "recv"  "\""    ":" "%lu"   ,uip_stat.nd6.recv  );  strcat(buf, str); sprintf(str, "," );  strcat(buf, str);
    sprintf(str,    "\""    "sent"  "\""    ":" "%lu"   ,uip_stat.nd6.sent  );  strcat(buf, str); sprintf(str, "," );  //strcat(buf, str);                                                     

    sprintf(str, "}" ); strcat(buf, str); 
    
    // ------------------------------------------------------------------------------------
    sprintf(str, "}" ); strcat(buf, str);
    // -------------------------------------------------------------------------------
    
    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    #else   // (UIP_CONF_STATISTICS)
    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

    // -------------------------------------------------------------------------------
    sprintf(str,    "\""   "stats"  "\""    ":" );  strcat(buf, str);
    sprintf(str,    "{" );                          strcat(buf, str);
    // --------------------------------------------------------------------------------

    sprintf(str,    "\""    "valid"      "\""    ":" "false");  strcat(buf, str); sprintf(str, "," );  strcat(buf, str);

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    
    sprintf(str,        "\""    "ip"        "\""    ":" );  strcat(buf, str);
    
    sprintf(str, "{" );  strcat(buf, str);
    
    sprintf(str,    "\""    "recv"      "\""    ":" "null"  );  strcat(buf, str); sprintf(str, "," );  strcat(buf, str);
    sprintf(str,    "\""    "sent"      "\""    ":" "null"  );  strcat(buf, str); sprintf(str, "," );  strcat(buf, str);
    sprintf(str,    "\""    "forwarded" "\""    ":" "null"  );  strcat(buf, str); sprintf(str, "," );  strcat(buf, str);
    sprintf(str,    "\""    "drop"      "\""    ":" "null"  );  strcat(buf, str); sprintf(str, "," );  strcat(buf, str);
    sprintf(str,    "\""    "vhlerr"    "\""    ":" "null"  );  strcat(buf, str); sprintf(str, "," );  strcat(buf, str);
    sprintf(str,    "\""    "hblenerr"  "\""    ":" "null"  );  strcat(buf, str); sprintf(str, "," );  strcat(buf, str);
    sprintf(str,    "\""    "lblenerr"  "\""    ":" "null"  );  strcat(buf, str); sprintf(str, "," );  strcat(buf, str);
    sprintf(str,    "\""    "fragerr"   "\""    ":" "null"  );  strcat(buf, str); sprintf(str, "," );  strcat(buf, str);
    sprintf(str,    "\""    "chkerr"    "\""    ":" "null"  );  strcat(buf, str); sprintf(str, "," );  strcat(buf, str);
    sprintf(str,    "\""    "protoerr"  "\""    ":" "null"  );  strcat(buf, str); sprintf(str, "," );  //strcat(buf, str);                                                                                                                                                                                      

    sprintf(str, "}" ); strcat(buf, str);

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    sprintf(str, ",");  strcat(buf, str);
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    
    sprintf(str,        "\""    "icmp"        "\""    ":" );  strcat(buf, str);
    
    sprintf(str, "{" );  strcat(buf, str);
    
    sprintf(str,    "\""    "recv"      "\""    ":" "null"  );  strcat(buf, str); sprintf(str, "," );  strcat(buf, str);
    sprintf(str,    "\""    "sent"      "\""    ":" "null"  );  strcat(buf, str); sprintf(str, "," );  strcat(buf, str);
    sprintf(str,    "\""    "drop"      "\""    ":" "null"  );  strcat(buf, str); sprintf(str, "," );  strcat(buf, str);
    sprintf(str,    "\""    "typeerr"   "\""    ":" "null"  );  strcat(buf, str); sprintf(str, "," );  strcat(buf, str);
    sprintf(str,    "\""    "chkerr"    "\""    ":" "null"  );  strcat(buf, str); sprintf(str, "," );  //strcat(buf, str);                                                     

    sprintf(str, "}" ); strcat(buf, str);                                                                                                                                                                              

    // ############################################################
    #if (UIP_TCP)

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    sprintf(str, ",");  strcat(buf, str);
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    sprintf(str,        "\""    "tcp"        "\""    ":" );  strcat(buf, str);
    
    sprintf(str, "{" );  strcat(buf, str);
    
    sprintf(str,    "\""    "tcpUsed"   "\""    ":" "null"  );  strcat(buf, str); sprintf(str, "," );  strcat(buf, str);
    sprintf(str,    "\""    "recv"      "\""    ":" "null"  );  strcat(buf, str); sprintf(str, "," );  strcat(buf, str);
    sprintf(str,    "\""    "sent"      "\""    ":" "null"  );  strcat(buf, str); sprintf(str, "," );  strcat(buf, str);
    sprintf(str,    "\""    "drop"      "\""    ":" "null"  );  strcat(buf, str); sprintf(str, "," );  strcat(buf, str);
    sprintf(str,    "\""    "chkerr"    "\""    ":" "null"  );  strcat(buf, str); sprintf(str, "," );  strcat(buf, str);
    sprintf(str,    "\""    "ackerr"    "\""    ":" "null"  );  strcat(buf, str); sprintf(str, "," );  strcat(buf, str);
    sprintf(str,    "\""    "rst"       "\""    ":" "null"  );  strcat(buf, str); sprintf(str, "," );  strcat(buf, str);
    sprintf(str,    "\""    "rexmit"    "\""    ":" "null"  );  strcat(buf, str); sprintf(str, "," );  strcat(buf, str);
    sprintf(str,    "\""    "syndrop"   "\""    ":" "null"  );  strcat(buf, str); sprintf(str, "," );  strcat(buf, str);
    sprintf(str,    "\""    "synrst"    "\""    ":" "null"  );  strcat(buf, str); sprintf(str, "," );  //strcat(buf, str);                                                                                                                                                                                      

    sprintf(str, "}" ); strcat(buf, str);
    
    #else   // (UIP,TCP)
    
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    sprintf(str, ",");  strcat(buf, str);
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~                                                                                                                        

    sprintf(str,        "\""    "tcp"        "\""    ":" );  strcat(buf, str);
    
    sprintf(str, "{" );  strcat(buf, str);
    
    sprintf(str,    "\""    "tcpUsed"   "\""    ":" "null"  );  strcat(buf, str); sprintf(str, "," );  strcat(buf, str);
    sprintf(str,    "\""    "recv"      "\""    ":" "null"  );  strcat(buf, str); sprintf(str, "," );  strcat(buf, str);
    sprintf(str,    "\""    "sent"      "\""    ":" "null"  );  strcat(buf, str); sprintf(str, "," );  strcat(buf, str);
    sprintf(str,    "\""    "drop"      "\""    ":" "null"  );  strcat(buf, str); sprintf(str, "," );  strcat(buf, str);
    sprintf(str,    "\""    "chkerr"    "\""    ":" "null"  );  strcat(buf, str); sprintf(str, "," );  strcat(buf, str);
    sprintf(str,    "\""    "ackerr"    "\""    ":" "null"  );  strcat(buf, str); sprintf(str, "," );  strcat(buf, str);
    sprintf(str,    "\""    "rst"       "\""    ":" "null"  );  strcat(buf, str); sprintf(str, "," );  strcat(buf, str);
    sprintf(str,    "\""    "rexmit"    "\""    ":" "null"  );  strcat(buf, str); sprintf(str, "," );  strcat(buf, str);
    sprintf(str,    "\""    "syndrop"   "\""    ":" "null"  );  strcat(buf, str); sprintf(str, "," );  strcat(buf, str);
    sprintf(str,    "\""    "synrst"    "\""    ":" "null"  );  strcat(buf, str); sprintf(str, "," );  //strcat(buf, str);                                                                                                                                                                                      

    sprintf(str, "}" ); strcat(buf, str);
    
    #endif  // (UIP_TCP)
    // ############################################################

    // ############################################################
    #if (UIP_UDP)

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    sprintf(str, ",");  strcat(buf, str);
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ 

    sprintf(str,        "\""    "udp"        "\""    ":" );  strcat(buf, str);
    
    sprintf(str, "{" );  strcat(buf, str);
    
    sprintf(str,    "\""    "udpUsed"   "\""    ":" "null"  );  strcat(buf, str); sprintf(str, "," );  strcat(buf, str);
    sprintf(str,    "\""    "drop"      "\""    ":" "null"  );  strcat(buf, str); sprintf(str, "," );  strcat(buf, str);
    sprintf(str,    "\""    "recv"      "\""    ":" "null"  );  strcat(buf, str); sprintf(str, "," );  strcat(buf, str);
    sprintf(str,    "\""    "sent"      "\""    ":" "null"  );  strcat(buf, str); sprintf(str, "," );  strcat(buf, str);
    sprintf(str,    "\""    "chkerr"    "\""    ":" "null"  );  strcat(buf, str); sprintf(str, "," );  //strcat(buf, str);                                                     

    sprintf(str, "}" ); strcat(buf, str); 

    #else   // (UIP,UDP)

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    sprintf(str, ",");  strcat(buf, str);
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ 

    sprintf(str,        "\""    "udp"        "\""    ":" );  strcat(buf, str);
    
    sprintf(str, "{" );  strcat(buf, str);
    
    sprintf(str,    "\""    "udpUsed"   "\""    ":" "null"  );  strcat(buf, str); sprintf(str, "," );  strcat(buf, str);
    sprintf(str,    "\""    "drop"      "\""    ":" "null"  );  strcat(buf, str); sprintf(str, "," );  strcat(buf, str);
    sprintf(str,    "\""    "recv"      "\""    ":" "null"  );  strcat(buf, str); sprintf(str, "," );  strcat(buf, str);
    sprintf(str,    "\""    "sent"      "\""    ":" "null"  );  strcat(buf, str); sprintf(str, "," );  strcat(buf, str);
    sprintf(str,    "\""    "chkerr"    "\""    ":" "null"  );  strcat(buf, str); sprintf(str, "," );  //strcat(buf, str);                                                     

    sprintf(str, "}" ); strcat(buf, str); 

    #endif  // (UIP_UDP)
    // ############################################################

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    sprintf(str, ",");  strcat(buf, str);
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~    
    
    sprintf(str,        "\""    "nd6"        "\""    ":" );  strcat(buf, str);
    
    sprintf(str, "{" );  strcat(buf, str);

    sprintf(str,    "\""    "drop"  "\""    ":" "null"  );  strcat(buf, str); sprintf(str, "," );  strcat(buf, str);
    sprintf(str,    "\""    "recv"  "\""    ":" "null"  );  strcat(buf, str); sprintf(str, "," );  strcat(buf, str);
    sprintf(str,    "\""    "sent"  "\""    ":" "null"  );  strcat(buf, str); sprintf(str, "," );  //strcat(buf, str);                                                     

    sprintf(str, "}" ); strcat(buf, str); 
    
    // ------------------------------------------------------------------------------------
    sprintf(str, "}" ); strcat(buf, str);
    // -------------------------------------------------------------------------------
    
    #endif  // (UIP_CONF_STATISTICS)
    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
}


    // (cmd_rpl_nbr) >                                                RPL neighbor          rpl_neighbor_count() 

































void oar_json_append_net(char * buf)
{
    char str[128];
    
    // -------------------------------------------------------------------------------
    sprintf(str,    "\""    "net"    "\""    ":" );  strcat(buf, str);   
    sprintf(str,    "{" );                              strcat(buf, str);
    // -------------------------------------------------------------------------------




    // ####################################################################################################################################################################################
    #if (ROUTING_CONF_RPL_LITE)




    sprintf(str,        "\""    "rplLiteUsed"           "\""    ":" "true"   );  strcat(buf, str);    sprintf(str, "," );  strcat(buf, str);




    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    sprintf(str,        "\""    "rplNbr"        "\""    ":" );  strcat(buf, str);
    sprintf(str, "{" );                                         strcat(buf, str);
    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

    sprintf(str,        "\""    "valid"           "\""    ":" "true"   );  strcat(buf, str);    sprintf(str, "," );  strcat(buf, str);

    if (!curr_instance.used || rpl_neighbor_count() == 0)
    {
        
        if (!curr_instance.used)    { sprintf(str,    "\""    "currentInstanceUsed"   "\""    ":" "false"   );  strcat(buf, str);    sprintf(str, "," );  strcat(buf, str); }
        else                        { sprintf(str,    "\""    "currentInstanceUsed"   "\""    ":" "true"    );  strcat(buf, str);    sprintf(str, "," );  strcat(buf, str); }
     
        sprintf(str,    "\""    "rplNeighborCount"      "\""    ":" "%u"    ,rpl_neighbor_count()  );  strcat(buf, str);    sprintf(str, "," );  strcat(buf, str);
        
        // [[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
        sprintf(str,    "\""    "rplNeighbors"      "\""    ":" );  strcat(buf, str);  
        sprintf(str,    "["      );                                 strcat(buf, str);

        for (int i = 0; i < NBR_TABLE_CONF_MAX_NEIGHBORS; i++)
        {
            sprintf(str,    "null"  );  strcat(buf, str);
            if (i != (NBR_TABLE_CONF_MAX_NEIGHBORS - 1)) { sprintf(str, "," );  strcat(buf, str); } 
        }

        sprintf(str,    "]"      );                                 strcat(buf, str);
        // [[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
    }
    else
    {
        
        rpl_nbr_t *nbr = nbr_table_head(rpl_neighbors);

        int oar_json_rpl_neighbor_count = 0;

        sprintf(str,    "\""    "currentInstanceUsed"   "\""    ":" "true"     );  strcat(buf, str);    sprintf(str, "," );  strcat(buf, str);
        sprintf(str,    "\""    "rplNeighborCount"      "\""    ":" "%u"    ,rpl_neighbor_count()   );  strcat(buf, str);    sprintf(str, "," );  strcat(buf, str);

        // [[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
        sprintf(str,    "\""    "rplNeighbors"      "\""    ":" );  strcat(buf, str);  
        sprintf(str,    "["      );                                 strcat(buf, str);

        while(nbr != NULL)
        {
            oar_json_rpl_neighbor_count++;
            
            char temp_str[120]; 
            rpl_neighbor_snprint(temp_str, sizeof(temp_str), nbr);

            sprintf(str,    "\""    "%s"    "\""    ,temp_str   );  strcat(buf, str);
            if (oar_json_rpl_neighbor_count < NBR_TABLE_CONF_MAX_NEIGHBORS) { sprintf(str,    "," );  strcat(buf, str); }

            nbr = nbr_table_next(rpl_neighbors, nbr);
        }
        
        for (int i = oar_json_rpl_neighbor_count; i < NBR_TABLE_CONF_MAX_NEIGHBORS; i++)
        {
            sprintf(str,    "null"  );  strcat(buf, str);
            if (i != (NBR_TABLE_CONF_MAX_NEIGHBORS - 1)) { sprintf(str, "," );  strcat(buf, str); }
        }

        sprintf(str,    "]"      );                                 strcat(buf, str);
        // [[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

    }
    
    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    sprintf(str, "}" ); strcat(buf, str);
    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%




    // $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
    sprintf(str, ",");  strcat(buf, str);
    // $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$




    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    sprintf(str,        "\""    "rplStatus"        "\""    ":" );  strcat(buf, str);
    sprintf(str, "{" );                                         strcat(buf, str);
    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

    sprintf(str,        "\""    "valid"           "\""    ":" "true"   );  strcat(buf, str);    sprintf(str, "," );  strcat(buf, str);




    if(!curr_instance.used)             
    { 
        sprintf(str,        "\""    "instanceId"    "\""    ":" "\""  "none"      "\""                                );  strcat(buf, str);   sprintf(str,    "," );  strcat(buf, str);
        
        // ------------------------------------------------------------------------------
        sprintf(str,        "\""    "dag"        "\""    ":" );         strcat(buf, str);
        sprintf(str,        "{" );                                      strcat(buf, str);
        // ------------------------------------------------------------------------------
        
            sprintf(str,        "\""    "valid"             "\""    ":"       "false"   );  strcat(buf, str);   sprintf(str,    "," );  strcat(buf, str);
            sprintf(str,        "\""    "dagType"           "\""    ":"       "null"    );  strcat(buf, str);   sprintf(str,    "," );  strcat(buf, str);
            sprintf(str,        "\""    "dagId"             "\""    ":"       "null"    );  strcat(buf, str);   sprintf(str,    "," );  strcat(buf, str);
            sprintf(str,        "\""    "dagVersion"        "\""    ":"       "null"    );  strcat(buf, str);   sprintf(str,    "," );  strcat(buf, str);
            sprintf(str,        "\""    "dagPrefix"         "\""    ":"       "null"    );  strcat(buf, str);   sprintf(str,    "," );  strcat(buf, str);
            sprintf(str,        "\""    "dagPrefixLength"   "\""    ":"       "null"    );  strcat(buf, str);   sprintf(str,    "," );  strcat(buf, str);
            sprintf(str,        "\""    "state"             "\""    ":"       "null"    );  strcat(buf, str);   sprintf(str,    "," );  strcat(buf, str);
            sprintf(str,        "\""    "preferredParent"   "\""    ":"       "null"    );  strcat(buf, str);   sprintf(str,    "," );  strcat(buf, str);
            sprintf(str,        "\""    "rank"              "\""    ":"       "null"    );  strcat(buf, str);   sprintf(str,    "," );  strcat(buf, str);
            sprintf(str,        "\""    "lowestRank"        "\""    ":"       "null"    );  strcat(buf, str);   sprintf(str,    "," );  strcat(buf, str);
            sprintf(str,        "\""    "maxRankInc"        "\""    ":"       "null"    );  strcat(buf, str);   sprintf(str,    "," );  strcat(buf, str);
            
            // ------------------------------------------------------------------------------
            sprintf(str,        "\""    "daoSequence"        "\""    ":" );         strcat(buf, str);
            sprintf(str,        "{" );                                      strcat(buf, str);
            // ------------------------------------------------------------------------------

            sprintf(str,    "\""    "valid"             "\""    ":"         "false" );  strcat(buf, str);   sprintf(str,    "," );  strcat(buf, str);
            sprintf(str,    "\""    "lastSent"  "\""            ":"         "null"  );  strcat(buf, str);   sprintf(str,    "," );  strcat(buf, str);
            sprintf(str,    "\""    "lastAcked" "\""            ":"         "null"  );  strcat(buf, str);   // sprintf(str,    "," );  strcat(buf, str);


            // ------------------------------------------------------------------------------
            sprintf(str,        "}" );                                  strcat(buf, str);
            // sprintf(str,        "," );                                  strcat(buf, str);
            // ------------------------------------------------------------------------------

        // ------------------------------------------------------------------------------
        sprintf(str,        "}" );                                  strcat(buf, str);
        sprintf(str,        "," );                                  strcat(buf, str);
        // ------------------------------------------------------------------------------

        sprintf(str,        "\""    "mop"               "\""    ":"       "null"    );  strcat(buf, str);   sprintf(str,    "," );  strcat(buf, str);
        sprintf(str,        "\""    "of"                "\""    ":"       "null"    );  strcat(buf, str);   sprintf(str,    "," );  strcat(buf, str);
        sprintf(str,        "\""    "hopRankIncrement"  "\""    ":"       "null"    );  strcat(buf, str);   sprintf(str,    "," );  strcat(buf, str);
        sprintf(str,        "\""    "defaultLifetime"   "\""    ":"       "null"    );  strcat(buf, str);   sprintf(str,    "," );  strcat(buf, str);
        sprintf(str,        "\""    "dtsnOut"           "\""    ":"       "null"    );  strcat(buf, str);   sprintf(str,    "," );  strcat(buf, str);

        // ------------------------------------------------------------------------------
        sprintf(str,    "\""    "trickleTimer"  "\""    ":" );  strcat(buf, str);
        sprintf(str,    "{"                                 );  strcat(buf, str);
        // ------------------------------------------------------------------------------

            sprintf(str,    "\""    "valid"         "\""    ":"       "false"   );  strcat(buf, str);   sprintf(str,    "," );  strcat(buf, str);
            sprintf(str,    "\""    "currentt"      "\""    ":"       "null"    );  strcat(buf, str);   sprintf(str,    "," );  strcat(buf, str);
            sprintf(str,    "\""    "nim"           "\""    ":"       "null"    );  strcat(buf, str);   sprintf(str,    "," );  strcat(buf, str);
            sprintf(str,    "\""    "max"           "\""    ":"       "null"    );  strcat(buf, str);   sprintf(str,    "," );  strcat(buf, str);
            sprintf(str,    "\""    "redundancy"    "\""    ":"       "null"    );  strcat(buf, str);   // sprintf(str,    "," );  strcat(buf, str);


        // ------------------------------------------------------------------------------
        sprintf(str,        "}" );                                  strcat(buf, str);
        // sprintf(str,        "," );                                  strcat(buf, str);
        // ------------------------------------------------------------------------------
        




    } 
    else                                
    { 
        sprintf(str,    "\""    "instanceId"    "\""    ":"                 "%u"                ,curr_instance.instance_id  );  strcat(buf, str);   sprintf(str,    "," );  strcat(buf, str);

        // ------------------------------------------------------------------------------
        sprintf(str,        "\""    "dag"        "\""    ":" );         strcat(buf, str);
        sprintf(str,        "{" );                                      strcat(buf, str);
        // ------------------------------------------------------------------------------
        
            sprintf(str,    "\""    "valid"         "\""    ":"                 "true"                                                          );  strcat(buf, str);   sprintf(str,    "," );  strcat(buf, str);

            if(NETSTACK_ROUTING.node_is_root()) { sprintf(str,    "\""    "dagType"     "\""    ":" "\""  "root"      "\""  );  strcat(buf, str);   sprintf(str,    "," );  strcat(buf, str); } 
            else                                { sprintf(str,    "\""    "dagType"     "\""    ":" "\""  "node"      "\""  );  strcat(buf, str);   sprintf(str,    "," );  strcat(buf, str); } 
    
            oar_json_ipaddr_to_str(oar_json_ipaddr, &curr_instance.dag.dag_id);
            sprintf(str,    "\""    "dagId"         "\""    ":"     "\""        "%s" "\""           ,oar_json_ipaddr                                        );  strcat(buf, str);   sprintf(str,    "," );  strcat(buf, str);
            
            sprintf(str,    "\""    "dagVersion"    "\""    ":"                 "%u"                ,curr_instance.dag.version                              );  strcat(buf, str);   sprintf(str,    "," );  strcat(buf, str);

            oar_json_ipaddr_to_str(oar_json_ipaddr, &curr_instance.dag.prefix_info.prefix);
            sprintf(str,    "\""    "dagPrefix"         "\""    ":"     "\""    "%s" "\""           ,oar_json_ipaddr                                        );  strcat(buf, str);   sprintf(str,    "," );  strcat(buf, str);
            
            sprintf(str,    "\""    "dagPrefixLength"   "\""    ":"                 "%u"            ,curr_instance.dag.prefix_info.length                   );  strcat(buf, str);   sprintf(str,    "," );  strcat(buf, str);
            sprintf(str,    "\""    "state"             "\""    ":"     "\""        "%s" "\""       ,oar_json_rpl_state_to_str(curr_instance.dag.state)    );  strcat(buf, str);   sprintf(str,    "," );  strcat(buf, str);

            if (curr_instance.dag.preferred_parent) 
            {
                oar_json_ipaddr_to_str(oar_json_ipaddr, rpl_neighbor_get_ipaddr(curr_instance.dag.preferred_parent));
                sprintf(str,    "\""    "preferredParent"   "\""    ":"     "\""        "%s"    "\""       ,oar_json_ipaddr     );  strcat(buf, str);   sprintf(str,    "," );  strcat(buf, str);
            }
            else
            {
                sprintf(str,    "\""    "preferredParent"   "\""    ":"     "\""        "none"  "\""                            );  strcat(buf, str);   sprintf(str,    "," );  strcat(buf, str);
            }

            sprintf(str,    "\""    "rank"              "\""    ":"                 "%u"                ,curr_instance.dag.rank                                 );  strcat(buf, str);   sprintf(str,    "," );  strcat(buf, str);
            sprintf(str,    "\""    "lowestRank"        "\""    ":"                 "%u"                ,curr_instance.dag.lowest_rank                          );  strcat(buf, str);   sprintf(str,    "," );  strcat(buf, str);
            sprintf(str,    "\""    "maxRankInc"        "\""    ":"                 "%u"                ,curr_instance.max_rankinc                              );  strcat(buf, str);   sprintf(str,    "," );  strcat(buf, str);
            
            // ------------------------------------------------------------------------------
            sprintf(str,        "\""    "daoSequence"        "\""    ":" );         strcat(buf, str);
            sprintf(str,        "{" );                                      strcat(buf, str);
            // ------------------------------------------------------------------------------

                sprintf(str,    "\""    "valid"             "\""    ":" "true"                                         );  strcat(buf, str);   sprintf(str,    "," );  strcat(buf, str);
                sprintf(str,    "\""    "lastSent"  "\""            ":" "%u"    ,curr_instance.dag.dao_last_seqno       );  strcat(buf, str);   sprintf(str,    "," );  strcat(buf, str);
                sprintf(str,    "\""    "lastAcked" "\""            ":" "%u"    ,curr_instance.dag.dao_last_acked_seqno );  strcat(buf, str);   // sprintf(str,    "," );  strcat(buf, str);

            // ------------------------------------------------------------------------------
            sprintf(str,        "}" );                                  strcat(buf, str);
            // sprintf(str,        "," );                                  strcat(buf, str);
            // ------------------------------------------------------------------------------

        // ------------------------------------------------------------------------------
        sprintf(str,        "}" );                                  strcat(buf, str);
        sprintf(str,        "," );                                  strcat(buf, str);
        // ------------------------------------------------------------------------------

        sprintf(str,    "\""    "mop"               "\""    ":"     "\""        "%s" "\""           ,oar_json_rpl_mop_to_str(curr_instance.mop)            );  strcat(buf, str);   sprintf(str,    "," );  strcat(buf, str);
        sprintf(str,    "\""    "of"                "\""    ":"     "\""        "%s" "\""           ,oar_json_rpl_ocp_to_str(curr_instance.of->ocp)        );  strcat(buf, str);   sprintf(str,    "," );  strcat(buf, str);
        sprintf(str,    "\""    "hopRankIncrement"  "\""    ":"                 "%u"                ,curr_instance.min_hoprankinc                           );  strcat(buf, str);   sprintf(str,    "," );  strcat(buf, str);
        sprintf(str,    "\""    "defaultLifetime"   "\""    ":"                 "%lu"               ,RPL_LIFETIME(curr_instance.default_lifetime)           );  strcat(buf, str);   sprintf(str,    "," );  strcat(buf, str);
        sprintf(str,    "\""    "dtsnOut"           "\""    ":"                 "%u"                ,curr_instance.dtsn_out                                 );  strcat(buf, str);   sprintf(str,    "," );  strcat(buf, str);
        
        // ------------------------------------------------------------------------------
        sprintf(str,        "\""    "trickleTimer"  "\""    ":" );          strcat(buf, str);
        sprintf(str,        "{" );                                          strcat(buf, str);
        // ------------------------------------------------------------------------------

            sprintf(str,    "\""    "valid"         "\""    ":" "true"                                                          );  strcat(buf, str);   sprintf(str,    "," );  strcat(buf, str);
            sprintf(str,    "\""    "current"       "\""    ":" "%u"    ,curr_instance.dag.dio_intcurrent                       );  strcat(buf, str);   sprintf(str,    "," );  strcat(buf, str);
            sprintf(str,    "\""    "min"           "\""    ":" "%u"    ,curr_instance.dio_intmin                               );  strcat(buf, str);   sprintf(str,    "," );  strcat(buf, str);
            sprintf(str,    "\""    "max"           "\""    ":" "%u"    ,curr_instance.dio_intmin + curr_instance.dio_intdoubl  );  strcat(buf, str);   sprintf(str,    "," );  strcat(buf, str);
            sprintf(str,    "\""    "redundency"    "\""    ":" "%u"    ,curr_instance.dio_redundancy                           );  strcat(buf, str);   // sprintf(str,    "," );  strcat(buf, str);

        // ------------------------------------------------------------------------------
        sprintf(str,        "}" );                                  strcat(buf, str);
        // sprintf(str,        "," );                                  strcat(buf, str);
        // ------------------------------------------------------------------------------

    }





































    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    sprintf(str, "}" ); strcat(buf, str);
    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%




    // ####################################################################################################################################################################################
    #else   // (ROUTING_CONF_RPL_LITE)
    // ####################################################################################################################################################################################




    sprintf(str,        "\""    "rplLiteUsed"           "\""    ":" "false"   );  strcat(buf, str);    sprintf(str, "," );  strcat(buf, str);




    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    sprintf(str,        "\""    "rplNbr"        "\""    ":" );  strcat(buf, str);
    sprintf(str, "{" );                                         strcat(buf, str);
    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    
    sprintf(str,        "\""    "valid"           "\""    ":" "false"   );  strcat(buf, str);    sprintf(str, "," );  strcat(buf, str);

    sprintf(str,    "\""    "currentInstanceUsed"   "\""    ":" "null"     );  strcat(buf, str);    sprintf(str, "," );  strcat(buf, str);
    sprintf(str,    "\""    "rplNeighborCount"      "\""    ":" "null"     );  strcat(buf, str);    sprintf(str, "," );  strcat(buf, str);

    // [[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
    sprintf(str,    "\""    "rplNeighbors"      "\""    ":" );  strcat(buf, str);  
    sprintf(str,    "["      );                                 strcat(buf, str);

    for (int i = 0; i < NBR_TABLE_CONF_MAX_NEIGHBORS; i++)
    {
        sprintf(str,    "null"  );  strcat(buf, str);
        if (i != (NBR_TABLE_CONF_MAX_NEIGHBORS - 1)) { sprintf(str, "," );  strcat(buf, str); } 
    }

    sprintf(str,    "]"      );                                 strcat(buf, str);
    // [[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    sprintf(str, "}" ); strcat(buf, str);
    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%




    // $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
    sprintf(str, ",");  strcat(buf, str);
    // $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$




    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    sprintf(str,        "\""    "rplStatus"        "\""    ":" );  strcat(buf, str);
    sprintf(str, "{" );                                         strcat(buf, str);
    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

    sprintf(str,        "\""    "valid"           "\""    ":" "false"   );  strcat(buf, str);    sprintf(str, "," );  strcat(buf, str);


    sprintf(str,        "\""    "instanceId"    "\""    ":" "\""  "none"      "\""                                );  strcat(buf, str);   sprintf(str,    "," );  strcat(buf, str);
        
        // ------------------------------------------------------------------------------
        sprintf(str,        "\""    "dag"        "\""    ":" );         strcat(buf, str);
        sprintf(str,        "{" );                                      strcat(buf, str);
        // ------------------------------------------------------------------------------
        
            sprintf(str,        "\""    "valid"             "\""    ":"       "false"   );  strcat(buf, str);   sprintf(str,    "," );  strcat(buf, str);
            sprintf(str,        "\""    "dagType"           "\""    ":"       "null"    );  strcat(buf, str);   sprintf(str,    "," );  strcat(buf, str);
            sprintf(str,        "\""    "dagId"             "\""    ":"       "null"    );  strcat(buf, str);   sprintf(str,    "," );  strcat(buf, str);
            sprintf(str,        "\""    "dagVersion"        "\""    ":"       "null"    );  strcat(buf, str);   sprintf(str,    "," );  strcat(buf, str);
            sprintf(str,        "\""    "dagPrefix"         "\""    ":"       "null"    );  strcat(buf, str);   sprintf(str,    "," );  strcat(buf, str);
            sprintf(str,        "\""    "dagPrefixLength"   "\""    ":"       "null"    );  strcat(buf, str);   sprintf(str,    "," );  strcat(buf, str);
            sprintf(str,        "\""    "state"             "\""    ":"       "null"    );  strcat(buf, str);   sprintf(str,    "," );  strcat(buf, str);
            sprintf(str,        "\""    "preferredParent"   "\""    ":"       "null"    );  strcat(buf, str);   sprintf(str,    "," );  strcat(buf, str);
            sprintf(str,        "\""    "rank"              "\""    ":"       "null"    );  strcat(buf, str);   sprintf(str,    "," );  strcat(buf, str);
            sprintf(str,        "\""    "lowestRank"        "\""    ":"       "null"    );  strcat(buf, str);   sprintf(str,    "," );  strcat(buf, str);
            sprintf(str,        "\""    "maxRankInc"        "\""    ":"       "null"    );  strcat(buf, str);   sprintf(str,    "," );  strcat(buf, str);
            
            // ------------------------------------------------------------------------------
            sprintf(str,        "\""    "daoSequence"        "\""    ":" );         strcat(buf, str);
            sprintf(str,        "{" );                                      strcat(buf, str);
            // ------------------------------------------------------------------------------

            sprintf(str,    "\""    "valid"             "\""    ":"         "false" );  strcat(buf, str);   sprintf(str,    "," );  strcat(buf, str);
            sprintf(str,    "\""    "lastSent"  "\""            ":"         "null"  );  strcat(buf, str);   sprintf(str,    "," );  strcat(buf, str);
            sprintf(str,    "\""    "lastAcked" "\""            ":"         "null"  );  strcat(buf, str);   // sprintf(str,    "," );  strcat(buf, str);


            // ------------------------------------------------------------------------------
            sprintf(str,        "}" );                                  strcat(buf, str);
            // sprintf(str,        "," );                                  strcat(buf, str);
            // ------------------------------------------------------------------------------

        // ------------------------------------------------------------------------------
        sprintf(str,        "}" );                                  strcat(buf, str);
        sprintf(str,        "," );                                  strcat(buf, str);
        // ------------------------------------------------------------------------------

        sprintf(str,        "\""    "mop"               "\""    ":"       "null"    );  strcat(buf, str);   sprintf(str,    "," );  strcat(buf, str);
        sprintf(str,        "\""    "of"                "\""    ":"       "null"    );  strcat(buf, str);   sprintf(str,    "," );  strcat(buf, str);
        sprintf(str,        "\""    "hopRankIncrement"  "\""    ":"       "null"    );  strcat(buf, str);   sprintf(str,    "," );  strcat(buf, str);
        sprintf(str,        "\""    "defaultLifetime"   "\""    ":"       "null"    );  strcat(buf, str);   sprintf(str,    "," );  strcat(buf, str);
        sprintf(str,        "\""    "dtsnOut"           "\""    ":"       "null"    );  strcat(buf, str);   sprintf(str,    "," );  strcat(buf, str);

        // ------------------------------------------------------------------------------
        sprintf(str,    "\""    "trickleTimer"  "\""    ":" );  strcat(buf, str);
        sprintf(str,    "{"                                 );  strcat(buf, str);
        // ------------------------------------------------------------------------------

            sprintf(str,    "\""    "valid"         "\""    ":"       "false"   );  strcat(buf, str);   sprintf(str,    "," );  strcat(buf, str);
            sprintf(str,    "\""    "currentt"      "\""    ":"       "null"    );  strcat(buf, str);   sprintf(str,    "," );  strcat(buf, str);
            sprintf(str,    "\""    "nim"           "\""    ":"       "null"    );  strcat(buf, str);   sprintf(str,    "," );  strcat(buf, str);
            sprintf(str,    "\""    "max"           "\""    ":"       "null"    );  strcat(buf, str);   sprintf(str,    "," );  strcat(buf, str);
            sprintf(str,    "\""    "redundancy"    "\""    ":"       "null"    );  strcat(buf, str);   // sprintf(str,    "," );  strcat(buf, str);


        // ------------------------------------------------------------------------------
        sprintf(str,        "}" );                                  strcat(buf, str);
        // sprintf(str,        "," );                                  strcat(buf, str);
        // ------------------------------------------------------------------------------

    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    sprintf(str, "}" ); strcat(buf, str);
    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%




    #endif  // (ROUTING_CONF_RPL_LITE)
    // ####################################################################################################################################################################################
    
    sprintf(str,    "," );  strcat(buf, str);

    oar_json_lladdr_to_str(oar_json_lladdr, &linkaddr_node_addr);
    sprintf(str,    "\""    "nodeMacAddress"    "\""    ":" "\""    "%s"    "\""    ,oar_json_lladdr    );  strcat(buf, str);   sprintf(str,    "," );  strcat(buf, str);
















    // ####################################################################################################################################################################################
    #if (NETSTACK_CONF_WITH_IPV6)

    sprintf(str,        "\""    "ipv6Used"           "\""    ":" "true"   );  strcat(buf, str);    sprintf(str, "," );  strcat(buf, str);

    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    sprintf(str,        "\""    "ipAddr"        "\""    ":" );  strcat(buf, str);
    sprintf(str, "{" );                                         strcat(buf, str);
    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

        sprintf(str,        "\""    "valid"           "\""    ":" "true"   );  strcat(buf, str);    sprintf(str, "," );  strcat(buf, str);

        uint8_t state;
        int oar_json_ipaddr_count = 0;

        // [[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
        sprintf(str,    "\""    "nodeIpv6addresses"      "\""    ":" ); strcat(buf, str);  
        sprintf(str,    "["      );                                     strcat(buf, str);

        for(int i = 0; i < UIP_DS6_ADDR_NB; i++) 
        {
            state = uip_ds6_if.addr_list[i].state;

            if(uip_ds6_if.addr_list[i].isused && (state == ADDR_TENTATIVE || state == ADDR_PREFERRED)) 
            {
                oar_json_ipaddr_count++;
                
                oar_json_ipaddr_to_str(oar_json_ipaddr, &uip_ds6_if.addr_list[i].ipaddr);
                sprintf(str,    "\""    "%s"    "\""    ,oar_json_ipaddr    );  strcat(buf, str);

                if (i != (UIP_DS6_ADDR_NB - 1)) { sprintf(str, "," );  strcat(buf, str); }

            }
            else
            {
                
                sprintf(str,    "\""    "null"  "\""                        );  strcat(buf, str);
                
                if (i != (UIP_DS6_ADDR_NB - 1)) { sprintf(str, "," );  strcat(buf, str); } 
            }
            
        }

        sprintf(str,    "]"      );                                 strcat(buf, str);   sprintf(str, "," );  strcat(buf, str);
        // [[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

        sprintf(str,    "\""    "addrIssuedCount"           "\""    ":" "%u"    ,oar_json_ipaddr_count                               );  strcat(buf, str);   // sprintf(str,    "," );  strcat(buf, str);

    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    sprintf(str,    "}" );  strcat(buf, str);
    sprintf(str,    "," );  strcat(buf, str);
    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    sprintf(str,        "\""    "ipNbr"        "\""    ":" );  strcat(buf, str);
    sprintf(str, "{" );                                         strcat(buf, str);
    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

        sprintf(str,        "\""    "valid"           "\""    ":" "true"   );  strcat(buf, str);    sprintf(str, "," );  strcat(buf, str);
        
        uip_ds6_nbr_t *nbr;
        int oar_json_ip_neighbor_count = 0;

        nbr = uip_ds6_nbr_head();

        if(nbr == NULL)
        {
            
            // [[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
            sprintf(str,    "\""    "nodeIpv6neigbors"      "\""    ":" ); strcat(buf, str);  
            sprintf(str,    "["      );                                    strcat(buf, str);

            for (int i = 0; i < NBR_TABLE_CONF_MAX_NEIGHBORS; i++)
            {
                sprintf(str,    "{" );  strcat(buf, str);
                
                sprintf(str,    "\""    "ipAddr"    "\""    ":" "null"  ); strcat(buf, str);    sprintf(str, "," );  strcat(buf, str);
                sprintf(str,    "\""    "llAddr"    "\""    ":" "null"  ); strcat(buf, str);    sprintf(str, "," );  strcat(buf, str);
                sprintf(str,    "\""    "router"    "\""    ":" "null"  ); strcat(buf, str);    sprintf(str, "," );  strcat(buf, str);
                sprintf(str,    "\""    "state"     "\""    ":" "null"  ); strcat(buf, str);

                sprintf(str,    "}" );  strcat(buf, str);

                if (i != (NBR_TABLE_CONF_MAX_NEIGHBORS - 1)) { sprintf(str, "," );  strcat(buf, str); };
            }

            sprintf(str,    "]"      );                                 strcat(buf, str);   sprintf(str, "," );  strcat(buf, str);
            // [[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

            sprintf(str,    "\""    "ipNbrCount"    "\""    ":" "%u"    ,oar_json_ip_neighbor_count );  strcat(buf, str); 
        }
        else
        {
            
            // [[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
            sprintf(str,    "\""    "nodeIpv6neigbors"      "\""    ":" ); strcat(buf, str);  
            sprintf(str,    "["      );                                    strcat(buf, str);
            
            while(nbr != NULL)
            {
                oar_json_ip_neighbor_count++;
                
                sprintf(str,    "{" );  strcat(buf, str);
                
                oar_json_ipaddr_to_str(oar_json_ipaddr, uip_ds6_nbr_get_ipaddr(nbr));
                sprintf(str,    "\""    "ipAddr"    "\""    ":" "\""    "%s"    "\""    ,oar_json_ipaddr                            ); strcat(buf, str);    sprintf(str, "," );  strcat(buf, str);

                oar_json_lladdr_to_str(oar_json_lladdr, (linkaddr_t *)uip_ds6_nbr_get_ll(nbr));
                sprintf(str,    "\""    "llAddr"    "\""    ":" "\""    "%s"    "\""    ,oar_json_lladdr                            ); strcat(buf, str);    sprintf(str, "," );  strcat(buf, str);

                sprintf(str,    "\""    "router"    "\""    ":"         "%u"            ,nbr->isrouter                              ); strcat(buf, str);    sprintf(str, "," );  strcat(buf, str);
                sprintf(str,    "\""    "state"     "\""    ":" "\""    "%s"    "\""    ,oar_json_ds6_nbr_state_to_str(nbr->state) ); strcat(buf, str);

                sprintf(str,    "}" );  strcat(buf, str);

                if (oar_json_ip_neighbor_count != NBR_TABLE_CONF_MAX_NEIGHBORS) { sprintf(str, "," );  strcat(buf, str); }
                
                nbr = uip_ds6_nbr_next(nbr);
            }

            for (int j = oar_json_ip_neighbor_count; j < NBR_TABLE_CONF_MAX_NEIGHBORS; j++)
            {
                
                sprintf(str,    "{" );  strcat(buf, str);
                
                sprintf(str,    "\""    "ipAddr"    "\""    ":" "null"  ); strcat(buf, str);    sprintf(str, "," );  strcat(buf, str);
                sprintf(str,    "\""    "llAddr"    "\""    ":" "null"  ); strcat(buf, str);    sprintf(str, "," );  strcat(buf, str);
                sprintf(str,    "\""    "router"    "\""    ":" "null"  ); strcat(buf, str);    sprintf(str, "," );  strcat(buf, str);
                sprintf(str,    "\""    "state"     "\""    ":" "null"  ); strcat(buf, str);

                sprintf(str,    "}" );  strcat(buf, str);

                if (j != (NBR_TABLE_CONF_MAX_NEIGHBORS - 1)) { sprintf(str, "," );  strcat(buf, str); };
            }

            sprintf(str,    "]"      );                                 strcat(buf, str);   sprintf(str, "," );  strcat(buf, str);
            // [[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

            sprintf(str,    "\""    "ipNbrCount"    "\""    ":" "%u"    ,oar_json_ip_neighbor_count );  strcat(buf, str); 
        }
        


    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    sprintf(str, "}" ); strcat(buf, str);
    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
















    // ####################################################################################################################################################################################
    #else   // (NETSTACK_CONF_WITH_IPV6)
    // ####################################################################################################################################################################################

    sprintf(str,        "\""    "ipv6Used"           "\""    ":" "false"   );  strcat(buf, str);    sprintf(str, "," );  strcat(buf, str);





    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    sprintf(str,        "\""    "ipAddr"        "\""    ":" );  strcat(buf, str);
    sprintf(str, "{" );                                         strcat(buf, str);
    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

        sprintf(str,        "\""    "valid"           "\""    ":" "false"   );  strcat(buf, str);    sprintf(str, "," );  strcat(buf, str);

        // [[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
        sprintf(str,    "\""    "nodeIpv6addresses"      "\""    ":" ); strcat(buf, str);  
        sprintf(str,    "["      );                                     strcat(buf, str);

        for(int i = 0; i < UIP_DS6_ADDR_NB; i++) 
        {
            sprintf(str,    "\""    "null"  "\""                        );  strcat(buf, str);
                
            if (i != (UIP_DS6_ADDR_NB - 1)) { sprintf(str, "," );  strcat(buf, str); }
        }

        sprintf(str,    "]"      );                                 strcat(buf, str);   sprintf(str, "," );  strcat(buf, str);
        // [[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

        sprintf(str,    "\""    "addrIssuedCount"           "\""    ":" "null"  );  strcat(buf, str);   // sprintf(str,    "," );  strcat(buf, str);


    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    sprintf(str,    "}" );  strcat(buf, str);
    sprintf(str,    "," );  strcat(buf, str);
    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    sprintf(str,        "\""    "ipNeighbors"        "\""    ":" );  strcat(buf, str);
    sprintf(str, "{" );                                         strcat(buf, str);
    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

        sprintf(str,        "\""    "valid"           "\""    ":" "true"   );  strcat(buf, str);    sprintf(str, "," );  strcat(buf, str);

        int oar_json_ip_neighbor_count = 0;

        // [[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
        sprintf(str,    "\""    "nodeIpv6neigbors"      "\""    ":" ); strcat(buf, str);  
        sprintf(str,    "["      );                                    strcat(buf, str);

        for (int i = 0; i < NBR_TABLE_CONF_MAX_NEIGHBORS; i++)
        {
            sprintf(str,    "{" );  strcat(buf, str);

            sprintf(str,    "\""    "ipAddr"    "\""    ":" "null"  ); strcat(buf, str);    sprintf(str, "," );  strcat(buf, str);
            sprintf(str,    "\""    "llAddr"    "\""    ":" "null"  ); strcat(buf, str);    sprintf(str, "," );  strcat(buf, str);
            sprintf(str,    "\""    "router"    "\""    ":" "null"  ); strcat(buf, str);    sprintf(str, "," );  strcat(buf, str);
            sprintf(str,    "\""    "state"     "\""    ":" "null"  ); strcat(buf, str);

            sprintf(str,    "}" );  strcat(buf, str);

            if (i != (NBR_TABLE_CONF_MAX_NEIGHBORS - 1)) { sprintf(str, "," );  strcat(buf, str); };
        }

        sprintf(str,    "]"      );                                 strcat(buf, str);   sprintf(str, "," );  strcat(buf, str);
        // [[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

        sprintf(str,    "\""    "ipNbrCount"    "\""    ":" "%u"    ,oar_json_ip_neighbor_count );  strcat(buf, str); 




    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    sprintf(str, "}" ); strcat(buf, str);
    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%





    








    #endif  // (NETSTACK_CONF_WITH_IPV6)
    // ####################################################################################################################################################################################
    




    
    
    
    
    
    
    
    
    
    // sprintf(str,        "\""    "cpu"           "\""    ":" "%lu"   ,oar_json_to_seconds(energest_type_time(ENERGEST_TYPE_CPU))                                                                                );  strcat(buf, str);    sprintf(str, "," );  strcat(buf, str);
    // sprintf(str,        "\""    "lpm"           "\""    ":" "%lu"   ,oar_json_to_seconds(energest_type_time(ENERGEST_TYPE_LPM))                                                                                );  strcat(buf, str);    sprintf(str, "," );  strcat(buf, str);
    // sprintf(str,        "\""    "deepLpm"       "\""    ":" "%lu"   ,oar_json_to_seconds(energest_type_time(ENERGEST_TYPE_DEEP_LPM))                                                                           );  strcat(buf, str);    sprintf(str, "," );  strcat(buf, str);
    // sprintf(str,        "\""    "totalTime"     "\""    ":" "%lu"   ,oar_json_to_seconds(ENERGEST_GET_TOTAL_TIME())                                                                                            );  strcat(buf, str);    sprintf(str, "," );  strcat(buf, str);
    // sprintf(str,        "\""    "radioListen"   "\""    ":" "%lu"   ,oar_json_to_seconds(energest_type_time(ENERGEST_TYPE_LISTEN))                                                                             );  strcat(buf, str);    sprintf(str, "," );  strcat(buf, str);
    // sprintf(str,        "\""    "radioTransmit" "\""    ":" "%lu"   ,oar_json_to_seconds(energest_type_time(ENERGEST_TYPE_TRANSMIT))                                                                           );  strcat(buf, str);    sprintf(str, "," );  strcat(buf, str);
    // sprintf(str,        "\""    "radioOff"      "\""    ":" "%lu"   ,oar_json_to_seconds(ENERGEST_GET_TOTAL_TIME() - energest_type_time(ENERGEST_TYPE_TRANSMIT) - energest_type_time(ENERGEST_TYPE_LISTEN))    );  strcat(buf, str);    // sprintf(str, "," );  strcat(buf, str);
    
    // ------------------------------------------------------------------------------
    sprintf(str,    "}" );  strcat(buf, str);
    // ------------------------------------------------------------------------------
}














void oar_json_construct(char * buf)
{
    oar_json_init(buf);
    oar_json_enter(buf);
    oar_json_append_system(buf);
    oar_json_bridge(buf);
    oar_json_append_id(buf);
    oar_json_bridge(buf);
    oar_json_append_energy(buf);
    oar_json_bridge(buf);
    oar_json_append_stats(buf);
    oar_json_bridge(buf);
    oar_json_append_net(buf);
    oar_json_exit(buf);
}









