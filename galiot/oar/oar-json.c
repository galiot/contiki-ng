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

char oar_json_buf[500];

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

    sprintf(str,        "\""    "system"                                        "\""    ":"                                                                                                 );  strcat(buf, str);
    sprintf(str,    "{"                                                                                                                                                                     );  strcat(buf, str);
    sprintf(str,        "\""    "contikiVersion"                                "\""    ":" "\""    CONTIKI_VERSION_STRING      "\""                                                        );  strcat(buf, str);
    sprintf(str,    "," );                                                                                                                                                                      strcat(buf, str);
    sprintf(str,        "\""    "routing"                                       "\""    ":" "\""    "%s"                        "\""    ,NETSTACK_ROUTING.name                              );  strcat(buf, str);
    sprintf(str,    "," );                                                                                                                                                                      strcat(buf, str);
    sprintf(str,        "\""    "net"                                           "\""    ":" "\""    "%s"                        "\""    ,NETSTACK_NETWORK.name                              );  strcat(buf, str);
    sprintf(str,    "," );                                                                                                                                                                      strcat(buf, str);
    sprintf(str,        "\""    "mac"                                           "\""    ":" "\""    "%s"                        "\""    ,NETSTACK_MAC.name                                  );  strcat(buf, str);
    sprintf(str,    "," );                                                                                                                                                                      strcat(buf, str);
    sprintf(str,        "\""    "ieee802154panid"                               "\""    ":" "\""    "0x%04x"                    "\""    ,IEEE802154_CONF_PANID                              );  strcat(buf, str);
    sprintf(str,    "," );                                                                                                                                                                      strcat(buf, str);
    
    // ----------------------------------------
    #if MAC_CONF_WITH_TSCH
    sprintf(str,        "\""    "ieee802154TSCHDefaultHoppingSequenceLength"    "\""    ":"         "%u"                                ,(unsigned)sizeof(TSCH_DEFAULT_HOPPING_SEQUENCE)    );  strcat(buf, str);
    sprintf(str,    "," );                                                                                                                                                                      strcat(buf, str);
    #else   // MAC_CONF_WITH_TSCH
    sprintf(str,        "\""    "ieee802154defaultChannel"                      "\""    ":"         "%u"                                ,IEEE802154_DEFAULT_CHANNEL                         );  strcat(buf, str);
    sprintf(str,    "," );                                                                                                                                                                      strcat(buf, str);
    #endif  // MAC_CONF_WITH_TSCH
    // ----------------------------------------

    sprintf(str,        "\""    "nodeId"                                         "\""    ":"        "%u"                                ,node_id                                            );  strcat(buf, str);
    sprintf(str,    "," );                                                                                                                                                                      strcat(buf, str);
    
    oar_json_lladdr_to_str(oar_json_lladdr, &linkaddr_node_addr);
    
    sprintf(str,        "\""    "linkLayerAddress"                               "\""    ":" "\""    "%s"                    "\""       ,oar_json_lladdr                                    );  strcat(buf, str);
    sprintf(str,    "," );                                                                                                                                                                      strcat(buf, str);
                                                                                                                                                                                                
    // ----------------------------------------
    #if NETSTACK_CONF_WITH_IPV6

    uip_ds6_addr_t *lladdr;
    memcpy(&uip_lladdr.addr, &linkaddr_node_addr, sizeof(uip_lladdr.addr));
    lladdr = uip_ds6_get_link_local(-1);
    
    oar_json_ipaddr_to_str(oar_json_ipaddr, lladdr != NULL ? &lladdr->ipaddr : NULL);

    sprintf(str,        "\""    "TentativeLinkLocalIPv6address"                 "\""    ":" "\""    "%s"                    "\""       ,oar_json_ipaddr                                    );   strcat(buf, str);
    // sprintf(str,    "," );                                                                                                                                                                   strcat(buf, str);
    #else   // NETSTACK_CONF_WITH_IPV6
    sprintf(str,        "\""    "TentativeLinkLocalIPv6address"                 "\""    ":"         "null"                             ,oar_json_ipaddr                                    );   strcat(buf, str);
    // sprintf(str,    "," );                                                                                                                                                                   strcat(buf, str);
    #endif  // NETSTACK_CONF_WITH_IPV6
    // ----------------------------------------

    sprintf(str,    "}"                                                                                                                                                                    );   strcat(buf, str);

}

void oar_json_append_id(char * buf)
{
    char str[128];

    sprintf(str,        "\""    "id"                                        "\""    ":"                                                                                                     );  strcat(buf, str);
    sprintf(str,    "{"                                                                                                                                                                     );  strcat(buf, str);
    sprintf(str,        "\""    "systemTime"                                "\""    ":"        "%lu"                                    ,clock_seconds()                                    );  strcat(buf, str);
    sprintf(str,    ","                                                                                                                                                                     );  strcat(buf, str);
    sprintf(str,        "\""    "systemCode"                                "\""    ":" "\""    OAR_CONF_MOTE_COLOR         "\""                                                            );  strcat(buf, str);
    // sprintf(str,    "," );                                                                                                                                                                   strcat(buf, str);
    sprintf(str,    "}"                                                                                                                                                                    );   strcat(buf, str);
}


void oar_json_append_energy(char * buf)
{
    char str[128];

    #if (ENERGEST_CONF_ON)

    energest_flush();       // Update all energest times.
    
    sprintf(str,        "\""    "energy"        "\""    ":"                                                                                                                                                     );  strcat(buf, str);
    sprintf(str,    "{"                                                                                                                                                                                         );  strcat(buf, str);
    sprintf(str,        "\""    "cpu"           "\""    ":" "%lu"   ,oar_json_to_seconds(energest_type_time(ENERGEST_TYPE_CPU))                                                                                );  strcat(buf, str);
    sprintf(str,    ","                                                                                                                                                                                         );  strcat(buf, str);
    sprintf(str,        "\""    "lpm"           "\""    ":" "%lu"   ,oar_json_to_seconds(energest_type_time(ENERGEST_TYPE_LPM))                                                                                );  strcat(buf, str);
    sprintf(str,    ","                                                                                                                                                                                         );  strcat(buf, str);
    sprintf(str,        "\""    "deepLpm"       "\""    ":" "%lu"   ,oar_json_to_seconds(energest_type_time(ENERGEST_TYPE_DEEP_LPM))                                                                           );  strcat(buf, str);
    sprintf(str,    ","                                                                                                                                                                                         );  strcat(buf, str);
    sprintf(str,        "\""    "totalTime"     "\""    ":" "%lu"   ,oar_json_to_seconds(ENERGEST_GET_TOTAL_TIME())                                                                                            );  strcat(buf, str);
    sprintf(str,    ","                                                                                                                                                                                         );  strcat(buf, str);
    sprintf(str,        "\""    "radioListen"   "\""    ":" "%lu"   ,oar_json_to_seconds(energest_type_time(ENERGEST_TYPE_LISTEN))                                                                             );  strcat(buf, str);
    sprintf(str,    ","                                                                                                                                                                                         );  strcat(buf, str);
    sprintf(str,        "\""    "radioTransmit" "\""    ":" "%lu"   ,oar_json_to_seconds(energest_type_time(ENERGEST_TYPE_TRANSMIT))                                                                           );  strcat(buf, str);
    sprintf(str,    ","                                                                                                                                                                                         );  strcat(buf, str);
    sprintf(str,        "\""    "radioOff"      "\""    ":" "%lu"   ,oar_json_to_seconds(ENERGEST_GET_TOTAL_TIME() - energest_type_time(ENERGEST_TYPE_TRANSMIT) - energest_type_time(ENERGEST_TYPE_LISTEN))    );  strcat(buf, str);
    // sprintf(str,    ","                                                                                                                                                                                        );  strcat(buf, str);
    sprintf(str,    "}"                                                                                                                                                                                         );  strcat(buf, str);

    #else   // (ENERGEST_CONF_ON)

    sprintf(str,        "\""    "energy"        "\""    ":"         );  strcat(buf, str);
    sprintf(str,    "{"                                             );  strcat(buf, str);
    sprintf(str,        "\""    "cpu"           "\""    ":" "null"  );  strcat(buf, str);
    sprintf(str,    ","                                             );  strcat(buf, str);
    sprintf(str,        "\""    "lpm"           "\""    ":" "null"  );  strcat(buf, str);
    sprintf(str,    ","                                             );  strcat(buf, str);
    sprintf(str,        "\""    "deepLpm"       "\""    ":" "null"  );  strcat(buf, str);
    sprintf(str,    ","                                             );  strcat(buf, str);
    sprintf(str,        "\""    "totalTime"     "\""    ":" "null"  );  strcat(buf, str);
    sprintf(str,    ","                                             );  strcat(buf, str);
    sprintf(str,        "\""    "radioListen"   "\""    ":" "null"  );  strcat(buf, str);
    sprintf(str,    ","                                             );  strcat(buf, str);
    sprintf(str,        "\""    "radioTransmit" "\""    ":" "null"  );  strcat(buf, str);
    sprintf(str,    ","                                             );  strcat(buf, str);
    sprintf(str,        "\""    "radioOff"      "\""    ":" "null"  );  strcat(buf, str);
    // sprintf(str,    ","                                            );  strcat(buf, str);
    sprintf(str,    "}"                                             );  strcat(buf, str);

    #endif  // (ENERGEST_CONF_ON)







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
    oar_json_exit(buf);
}









