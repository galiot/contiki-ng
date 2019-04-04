#include "oar-json.h"

#include "contiki.h"
#include "contiki-net.h"
#include "sys/node-id.h"
#include "sys/platform.h"
#include "sys/energest.h"
#include "sys/stack-check.h"
#include "dev/watchdog.h"

#include "net/link-stats.h"









// Static functions which needed to be copied                               >>>>> BELOW <<<<<
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

/* ******************************************************
 * os/net/routing/rpl-lite/rpl-neighbors.c              *
 * This file is part of the Contiki operating system.   *
 *                                                      *
 * Logic for DAG neighbors in RPL.                      *
 *                                                      *
 * Joakim Eriksson <joakime@sics.se>                    *               
 * Nicolas Tsiftes <nvt@sics.se>                        *
 * Simon Duquennoy <simon.duquennoy@inria.fr>           *
 *                                                      
 ****************************************************** */

// ######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)########
#if (ROUTING_CONF_RPL_LITE)

    // ----------------------------------------------------------------------------

    static int max_acceptable_rank(void)
    {
        if(curr_instance.max_rankinc == 0) 
        {
            
            return RPL_INFINITE_RANK;   // There is no max rank increment
        } 
        else 
        {
            
            return MIN((uint32_t)curr_instance.dag.lowest_rank + curr_instance.max_rankinc, RPL_INFINITE_RANK); // Make sure not to exceed RPL_INFINITE_RANK
        }
    }

    // ----------------------------------------------------------------------------

    static int acceptable_rank(rpl_rank_t rank)
    {
        return rank != RPL_INFINITE_RANK
            && rank >= ROOT_RANK
            && rank <= max_acceptable_rank();
    }

    // ----------------------------------------------------------------------------

    static rpl_nbr_t *best_parent(int fresh_only)
    {
        rpl_nbr_t *nbr;
        rpl_nbr_t *best = NULL;

        if(curr_instance.used == 0) 
        {
            return NULL;
        }

        for(nbr = nbr_table_head(rpl_neighbors); nbr != NULL; nbr = nbr_table_next(rpl_neighbors, nbr)) // Search for the best parent according to the OF
        {
            if(!acceptable_rank(nbr->rank) || !curr_instance.of->nbr_is_acceptable_parent(nbr)) 
            {
                continue;   // Exclude neighbors with a rank that is not acceptable)
            }

            if(fresh_only && !rpl_neighbor_is_fresh(nbr)) 
            {
                continue;   // Filter out non-fresh nerighbors if fresh_only is set
            }

            
            // vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
            // #########(UIP_ND6_SEND_NS)#########(UIP_ND6_SEND_NS)#########(UIP_ND6_SEND_NS)#########(UIP_ND6_SEND_NS)#########(UIP_ND6_SEND_NS)#########(UIP_ND6_SEND_NS)#########(UIP_ND6_SEND_NS)#########(UIP_ND6_SEND_NS)#########
            
            #if (UIP_ND6_SEND_NS)
            {
                uip_ds6_nbr_t *ds6_nbr = rpl_get_ds6_nbr(nbr);
                
                if(ds6_nbr == NULL || ds6_nbr->state != NBR_REACHABLE)  // Exclude links to a neighbor that is not reachable at a NUD level
                {
                    continue;
                }
            }
            #endif
            
            // #########(UIP_ND6_SEND_NS)#########(UIP_ND6_SEND_NS)#########(UIP_ND6_SEND_NS)#########(UIP_ND6_SEND_NS)#########(UIP_ND6_SEND_NS)#########(UIP_ND6_SEND_NS)#########(UIP_ND6_SEND_NS)#########(UIP_ND6_SEND_NS)#########
            // ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
            

            /* Now we have an acceptable parent, check if it is the new best */
            best = curr_instance.of->best_parent(best, nbr);
        }

        return best;
    }

    // ----------------------------------------------------------------------------

#endif //(ROUTING_CONF_RPL_LITE)
// ######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)########

/* ******************************************************
 * os/net/routing/rpl-lite/rpl-neighbors.c              *
 * This file is part of the Contiki operating system.   *
 *                                                      *
 * Logic for DAG neighbors in RPL.                      *
 *                                                      *
 * Joakim Eriksson <joakime@sics.se>                    *               
 * Nicolas Tsiftes <nvt@sics.se>                        *
 * Simon Duquennoy <simon.duquennoy@inria.fr>           *
 *                                                      
 ****************************************************** */ 

// ----------------------------------------------------------------------------
// function that provides context for ds6 neighbor state

// ######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)########
#if (NETSTACK_CONF_WITH_IPV6)

    static const char *oar_json_ds6_nbr_state_to_str(uint8_t state)
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

#endif //(NETSTACK_CONF_WITH_IPV6)
// ######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)########
// ######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)########
#if (ROUTING_CONF_RPL_LITE)

    // ----------------------------------------------------------------------------
    // function that provides context for RPL directed acyclic graph (DAG) state

    static const char *oar_json_rpl_state_to_str(enum rpl_dag_state state)
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

    static const char *oar_json_rpl_mop_to_str(int mop)
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

    static const char *oar_json_rpl_ocp_to_str(int ocp)
    {
        switch(ocp) 
        {
            case RPL_OCP_OF0: return "OF0";
            case RPL_OCP_MRHOF: return "MRHOF";
            default: return "Unknown";
        }
    }

    // ----------------------------------------------------------------------------

#endif //(ROUTING_CONF_RPL_LITE)
// ######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)########


// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
// Static functions which needed to be copied                               >>>>> ABOVE <<<<<









// HELPER FUNCTIONS                                                         >>>>> BELOW <<<<<
// ()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()
// ()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()
// ()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()
// ()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()

// ######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)########
#if (NETSTACK_CONF_WITH_IPV6)

// ----------------------------------------------------------------------------

    static void oar_json_ipaddr_to_str(char *output, const uip_ipaddr_t *ipaddr) 
    {
        char buf[UIPLIB_IPV6_MAX_STR_LEN];  // UIPLIB_IPV6_MAX_STR_LEN == 40
        
        memset(output, 0, sizeof(output));  // initialization of outpout string
        uiplib_ipaddr_snprint(buf, sizeof(buf), ipaddr);    // function that creates string from ipaddr

        strcpy(output, buf);    // cannot return string, local scope
    }

#endif //(NETSTACK_CONF_WITH_IPV6)
// ######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)########


// ----------------------------------------------------------------------------

static void oar_json_lladdr_to_str(char *output, const linkaddr_t *lladdr) 
{
    char buf[5];    // temporary string, local scope
    memset(output, 0, sizeof(output));  // initialization of outpout string (else concatenates)

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

// ----------------------------------------------------------------------------

// vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
// #########(ENERGEST_CONF_ON)#########(ENERGEST_CONF_ON)#########(ENERGEST_CONF_ON)#########(ENERGEST_CONF_ON)#########(ENERGEST_CONF_ON)#########(ENERGEST_CONF_ON)#########(ENERGEST_CONF_ON))#########

#if (ENERGEST_CONF_ON)

    static unsigned long oar_json_to_seconds(uint64_t time)
    {
        return (unsigned long)(time / ENERGEST_SECOND);
    }

#endif

// #########(ENERGEST_CONF_ON)#########(ENERGEST_CONF_ON)#########(ENERGEST_CONF_ON)#########(ENERGEST_CONF_ON)#########(ENERGEST_CONF_ON)#########(ENERGEST_CONF_ON)#########(ENERGEST_CONF_ON))#########
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

// ----------------------------------------------------------------------------

// ()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()
// ()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()
// ()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()
// ()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()
// HELPER FUNCTIONS                                                         >>>>> ABOVE <<<<<










// ====================================================================================================================

char oar_json_buf[OAR_CONF_JSON_BUF_SIZE];    // global string: will contain the json

// ----------------------------------------------------------------------------

void oar_json_print(char * buf)
{
    printf("%s\n", buf);
}

// ----------------------------------------------------------------------------

// ######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)########
#if (NETSTACK_CONF_WITH_IPV6)

     static char oar_json_ipaddr[UIPLIB_IPV6_MAX_STR_LEN];

#endif //(NETSTACK_CONF_WITH_IPV6)
// ######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)########

static char oar_json_lladdr[UIPLIB_IPV6_MAX_STR_LEN];

// ====================================================================================================================









// MAIN FUNCTIONS                                                           >>>>> BELOW <<<<<
// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

// ----------------------------------------------------------------------------
// function that initializes (empties) the json string

static void oar_json_init(char * buf)
{
    memset(buf, 0, sizeof(buf));        // initialization
}

// ----------------------------------------------------------------------------
// function that appends the entry '{' json character to the string

static void oar_json_enter(char * buf)
{
    char str[128];
    sprintf(str,    "{" );  strcat(buf, str);
}

// ----------------------------------------------------------------------------
// function that connects the sections og the json, appending and ',' char

static void oar_json_bridge(char * buf)
{
    char str[128];
    sprintf(str,    "," );  strcat(buf, str);
}

// ----------------------------------------------------------------------------
// function that appends the exit '}' json character to the string

static void oar_json_exit(char * buf)
{
    char str[128];
    sprintf(str,    "}" );  strcat(buf, str);
}





/* **************************************************************************************************************************************************
 * contikiVesrsion                          CONTIKI_VERSION_STRING                                                                                  *
 * routing                  %s              NETSTACK_ROUTING.name                                   Routing                                         *                                                
 * net                      %s              NETSTACK_NETWORK.name                                   Net                                             *
 * mac                      %s              NETSTACK_MAC.name                                       MAC                                             *
 * ieee802154panid          %04x            IEEE802154_PANID                                        802.15.4 PANID                                  *
 * ieee802154tschDHSL       %u              (unsigned)sizeof(TSCH_DEFAULT_HOPPING_SEQUENCE)         802.15.4 TSCH default hopping sequence length   *
 * ieee802154defCh          %u              IEEE802154_DEFAULT_CHANNEL                              802.15.4 Default channel                        *
 * nodeId                   %u              node_id                                                 Node Id                                         *
 * lladdr                   %s              &linkaddr_node_addr                                     Link-layer address                              *
 * tent6lladdr              %s              lladdr != NULL ? &lladdr->ipaddr : NULL                 Tentative link-local IPv6 address               *
 ****************************************************************************************************************************************************/

// ----------------------------------------------------------------------------
// function that appends SYSTEM section to the json string

static void oar_json_append_system(char * buf)
{
    char str[128];

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // SECTION START system{} //////////////////////////////
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ 
    sprintf(str, "\"" "system" "\"" ":" ); strcat(buf, str);
    sprintf(str, "{"                    ); strcat(buf, str);
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    
        sprintf(str, "\"" "contikiVersion"  "\"" ":" "\"" CONTIKI_VERSION_STRING    "\""                        ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
        sprintf(str, "\"" "routing"         "\"" ":" "\"" "%s"                      "\"" ,NETSTACK_ROUTING.name ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
        sprintf(str, "\"" "net"             "\"" ":" "\"" "%s"                      "\"" ,NETSTACK_NETWORK.name ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
        sprintf(str, "\"" "mac"             "\"" ":" "\"" "%s"                      "\"" ,NETSTACK_MAC.name     ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
        sprintf(str, "\"" "ieee802154panid" "\"" ":" "\"" "0x%04x"                  "\"" ,IEEE802154_CONF_PANID ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
        
        // #########(MAC_CONF_WITH_TSCH)#########(MAC_CONF_WITH_TSCH)#########(MAC_CONF_WITH_TSCH)#########(MAC_CONF_WITH_TSCH)#########(MAC_CONF_WITH_TSCH)#########(MAC_CONF_WITH_TSCH)#########(MAC_CONF_WITH_TSCH)#########
        #if MAC_CONF_WITH_TSCH
        
            sprintf(str, "\"" "ieee802154TSCHDefaultHoppingSequenceLength"  "\"" ":" "%u"   ,(unsigned)sizeof(TSCH_DEFAULT_HOPPING_SEQUENCE)    ); strcat(buf, str);    sprintf(str,"," ); strcat(buf, str);
            sprintf(str, "\"" "ieee802154defaultChannel"                    "\"" ":" "null"                                                     ); strcat(buf, str);    sprintf(str,"," ); strcat(buf, str);
        
        // #########(MAC_CONF_WITH_TSCH)#########(MAC_CONF_WITH_TSCH)#########(MAC_CONF_WITH_TSCH)#########(MAC_CONF_WITH_TSCH)#########(MAC_CONF_WITH_TSCH)#########(MAC_CONF_WITH_TSCH)#########(MAC_CONF_WITH_TSCH)#########
        // ########!(MAC_CONF_WITH_TSCH)########!(MAC_CONF_WITH_TSCH)########!(MAC_CONF_WITH_TSCH)########!(MAC_CONF_WITH_TSCH)########!(MAC_CONF_WITH_TSCH)########!(MAC_CONF_WITH_TSCH)########!(MAC_CONF_WITH_TSCH)########!
        #else
        
            sprintf(str, "\"" "ieee802154TSCHDefaultHoppingSequenceLength"  "\"" ":" "null"                             ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
            sprintf(str, "\"" "ieee802154defaultChannel"                    "\"" ":" "%u"   ,IEEE802154_DEFAULT_CHANNEL ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
        
        #endif
        // ########!(MAC_CONF_WITH_TSCH)########!(MAC_CONF_WITH_TSCH)########!(MAC_CONF_WITH_TSCH)########!(MAC_CONF_WITH_TSCH)########!(MAC_CONF_WITH_TSCH)########!(MAC_CONF_WITH_TSCH)########!(MAC_CONF_WITH_TSCH)########!

        sprintf(str, "\"" "nodeId" "\"" ":" "%u" ,node_id); strcat(buf, str);   sprintf(str, "," ); strcat(buf, str);
        
        oar_json_lladdr_to_str(oar_json_lladdr, &linkaddr_node_addr);
        sprintf(str, "\"" "linkLayerAddress" "\"" ":" "\"" "%s" "\"" ,oar_json_lladdr ); strcat(buf, str);  sprintf(str, ","); strcat(buf, str);
                                                                                                                                                                                                    
        // #########(NETSTACK_CONF_WITH_IPV6)#########(NETSTACK_CONF_WITH_IPV6)#########(NETSTACK_CONF_WITH_IPV6)#########(NETSTACK_CONF_WITH_IPV6)#########(NETSTACK_CONF_WITH_IPV6)#########(NETSTACK_CONF_WITH_IPV6)#########
        #if (NETSTACK_CONF_WITH_IPV6)
        
            uip_ds6_addr_t *lladdr;
            
            memcpy(&uip_lladdr.addr, &linkaddr_node_addr, sizeof(uip_lladdr.addr));
            lladdr = uip_ds6_get_link_local(-1);
            
            oar_json_ipaddr_to_str(oar_json_ipaddr, lladdr != NULL ? &lladdr->ipaddr : NULL);
            sprintf(str, "\""    "TentativeLinkLocalIPv6address" "\"" ":" "\""  "%s"    "\"" ,oar_json_ipaddr   ); strcat(buf, str);
        
        // #########(NETSTACK_CONF_WITH_IPV6)#########(NETSTACK_CONF_WITH_IPV6)#########(NETSTACK_CONF_WITH_IPV6)#########(NETSTACK_CONF_WITH_IPV6)#########(NETSTACK_CONF_WITH_IPV6)#########(NETSTACK_CONF_WITH_IPV6)#########
        // ########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!
        #else  
        
            sprintf(str, "\""    "TentativeLinkLocalIPv6address" "\"" ":"       "null"                          ); strcat(buf, str);
        
        #endif
        // ########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!
    
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    sprintf(str,    "}" ); strcat(buf, str);
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ 
    // SECTION END system {} ///////////////
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
}





// ----------------------------------------------------------------------------
// function that appends ID section to the json string

static void oar_json_append_id(char * buf)
{
    char str[128];

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // SECTION START id{} /////////////////////////////
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ 
    sprintf(str, "\"" "id" "\"" ":" ); strcat(buf, str);
    sprintf(str, "{"                ); strcat(buf, str);
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    
        sprintf(str,        "\""    "systemTime"    "\""    ":"        "%lu"                                    ,clock_seconds()    );  strcat(buf, str);   sprintf(str,    "," );  strcat(buf, str);
        sprintf(str,        "\""    "systemCode"    "\""    ":" "\""    OAR_CONF_MOTE_COLOR         "\""                            );  strcat(buf, str);   
    
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    sprintf(str, "}" ); strcat(buf, str);
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // SECTION END id{} /////////////////
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
}





// ----------------------------------------------------------------------------
// function that appends ENERGY section to the json string

static void oar_json_append_energy(char * buf)
{
    char str[128];

    // #########(ENERGEST_CONF_ON)#########(ENERGEST_CONF_ON)#########(ENERGEST_CONF_ON)#########(ENERGEST_CONF_ON)#########(ENERGEST_CONF_ON)#########(ENERGEST_CONF_ON)#########(ENERGEST_CONF_ON)#########
    #if (ENERGEST_CONF_ON)

        energest_flush();       // Update all energest times.
        
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // SECTION START energy{} //////////////////////////////
        sprintf(str, "\"" "energy" "\"" ":" ); strcat(buf, str);   
        sprintf(str, "{"                    ); strcat(buf, str);
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

            sprintf(str, "\"" "valid"         "\"" ":" "true"                                                                                                                                             );  strcat(buf, str); sprintf(str,","); strcat(buf, str);
            sprintf(str, "\"" "cpu"           "\"" ":" "%lu"   ,oar_json_to_seconds(energest_type_time(ENERGEST_TYPE_CPU))                                                                                );  strcat(buf, str); sprintf(str,","); strcat(buf, str);
            sprintf(str, "\"" "lpm"           "\"" ":" "%lu"   ,oar_json_to_seconds(energest_type_time(ENERGEST_TYPE_LPM))                                                                                );  strcat(buf, str); sprintf(str,","); strcat(buf, str);
            sprintf(str, "\"" "deepLpm"       "\"" ":" "%lu"   ,oar_json_to_seconds(energest_type_time(ENERGEST_TYPE_DEEP_LPM))                                                                           );  strcat(buf, str); sprintf(str,","); strcat(buf, str);
            sprintf(str, "\"" "totalTime"     "\"" ":" "%lu"   ,oar_json_to_seconds(ENERGEST_GET_TOTAL_TIME())                                                                                            );  strcat(buf, str); sprintf(str,","); strcat(buf, str);
            sprintf(str, "\"" "radioListen"   "\"" ":" "%lu"   ,oar_json_to_seconds(energest_type_time(ENERGEST_TYPE_LISTEN))                                                                             );  strcat(buf, str); sprintf(str,","); strcat(buf, str);
            sprintf(str, "\"" "radioTransmit" "\"" ":" "%lu"   ,oar_json_to_seconds(energest_type_time(ENERGEST_TYPE_TRANSMIT))                                                                           );  strcat(buf, str); sprintf(str,","); strcat(buf, str);
            sprintf(str, "\"" "radioOff"      "\"" ":" "%lu"   ,oar_json_to_seconds(ENERGEST_GET_TOTAL_TIME() - energest_type_time(ENERGEST_TYPE_TRANSMIT) - energest_type_time(ENERGEST_TYPE_LISTEN))    );  strcat(buf, str); 
            
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        sprintf(str, "}" ); strcat(buf, str);
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // SECTION END energy{} /////////////
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


    // #########(ENERGEST_CONF_ON)#########(ENERGEST_CONF_ON)#########(ENERGEST_CONF_ON)#########(ENERGEST_CONF_ON)#########(ENERGEST_CONF_ON)#########(ENERGEST_CONF_ON)#########(ENERGEST_CONF_ON)#########
    // ########!(ENERGEST_CONF_ON)########!(ENERGEST_CONF_ON)########!(ENERGEST_CONF_ON)########!(ENERGEST_CONF_ON)########!(ENERGEST_CONF_ON)########!(ENERGEST_CONF_ON)########!(ENERGEST_CONF_ON)########!
    #else
        

        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // SECTION START energy{} //////////////////////////////
        sprintf(str, "\"" "energy" "\"" ":" ); strcat(buf, str);   
        sprintf(str, "{"                    ); strcat(buf, str);
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

            sprintf(str, "\"" "valid"         "\"" ":" "false" ); strcat(buf, str); sprintf(str, ","); strcat(buf, str);
            sprintf(str, "\"" "cpu"           "\"" ":" "null"  ); strcat(buf, str); sprintf(str, ","); strcat(buf, str);
            sprintf(str, "\"" "lpm"           "\"" ":" "null"  ); strcat(buf, str); sprintf(str, ","); strcat(buf, str);
            sprintf(str, "\"" "deepLpm"       "\"" ":" "null"  ); strcat(buf, str); sprintf(str, ","); strcat(buf, str);
            sprintf(str, "\"" "totalTime"     "\"" ":" "null"  ); strcat(buf, str); sprintf(str, ","); strcat(buf, str);
            sprintf(str, "\"" "radioListen"   "\"" ":" "null"  ); strcat(buf, str); sprintf(str, ","); strcat(buf, str);
            sprintf(str, "\"" "radioTransmit" "\"" ":" "null"  ); strcat(buf, str); sprintf(str, ","); strcat(buf, str);
            sprintf(str, "\"" "radioOff"      "\"" ":" "null"  ); strcat(buf, str);
        
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        sprintf(str, "}" ); strcat(buf, str);
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // SECTION END energy{} /////////////
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    #endif
    // ########!(ENERGEST_CONF_ON)########!(ENERGEST_CONF_ON)########!(ENERGEST_CONF_ON)########!(ENERGEST_CONF_ON)########!(ENERGEST_CONF_ON)########!(ENERGEST_CONF_ON)########!(ENERGEST_CONF_ON)########!
}





/* **********************************************************************************
 *       (ip.recv) >                            received packets at the IP layer    *
 *       (ip.sent) >                                sent packets at the IP layer    *
 *  (ip.forwarded) >                           forwarded packets at the IP layer    *
 *       (ip.drop) >                             dropped packets at the IP layer    *
 *     (ip.vhlerr) >    packets dropped due to wrong IP version or header length    *
 *   (ip.hblenerr) >           packets dropped due to wrong IP length, high byte    *
 *   (ip.lblenerr) >            packets dropped due to wrong IP length, low byte    *
 *    (ip.fragerr) >              packets dropped because they were IP fragments    *
 *     (ip.chkerr) >                   packets dropped due to IP checksum errors    *
 *   (ip.protoerr) > packets dropped because they were neither ICMP, UDP nor TCP    *
 *                                                                                  *
 *     (icmp.recv) >                                       received ICMP packets    *
 *     (icmp.sent) >                                           sent ICMP packets    *
 *     (icmp.drop) >                                        dropped ICMP packets    *
 *  (icmp.typeerr) >                              ICMP packets with a wrong type    *
 *   (icmp.chkerr) >                            ICMP packets with a bad checksum    *
 *                                                                                  *
 *      (tcp.recv) >                                       received TCP segments    *
 *      (tcp.sent) >                                           sent TCP segments    *
 *      (tcp.drop) >                                        dropped TCP segments    *
 *    (tcp.chkerr) >                            TCP segments with a bad checksum    *
 *    (tcp.ackerr) >                          TCP segments with a bad ACK number    *
 *       (tcp.rst) >                           received TCP RST (reset) segments    *
 *    (tcp.rexmit) >                                  retransmitted TCP segments    *
 *   (tcp.syndrop) >     dropped SYNs because too few connections were available    *
 *    (tcp.synrst) >                     SYNs for closed ports, triggering a RST    *
 *                                                                                  *
 *      (udp.drop) >                                        dropped UDP segments    *
 *      (udp.recv) >                                       received UDP segments    *
 *      (udp.sent) >                                           sent UDP segments    *
 *    (udp.chkerr) >                            UDP segments with a bad checksum    *
 *                                                                                  *
 *      (nd6.drop) >                                         dropped ND6 packets    *
 *      (nd6.recv) >                                         dropped ND6 packets    *
 *      (nd6.sent) >                                         dropped ND6 packets    *
 ************************************************************************************/

// ----------------------------------------------------------------------------
// function that appends STATS section to the json string

static void oar_json_append_stats(char * buf)
{
    char str[128];
    
    // ######## (UIP_CONF_STATISTICS)######## (UIP_CONF_STATISTICS)######## (UIP_CONF_STATISTICS)######## (UIP_CONF_STATISTICS)######## (UIP_CONF_STATISTICS)######## (UIP_CONF_STATISTICS)######## (UIP_CONF_STATISTICS)########
    #if (UIP_CONF_STATISTICS)

        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // SECTION START stats{} ///////////////////////////////////
        sprintf(str, "\""   "stats"  "\""    ":"); strcat(buf, str);
        sprintf(str, "{"                        ); strcat(buf, str);
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

            sprintf(str, "\"" "valid" "\"" ":" "true"); strcat(buf, str);   sprintf(str, ","); strcat(buf, str);        
            
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            // SUBSECTION START stats{} > ip{} /////////////////
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            sprintf(str, "\"" "ip" "\"" ":" ); strcat(buf, str);
            sprintf(str, "{"                ); strcat(buf, str);
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            
                sprintf(str, "\"" "recv"        "\"" ":" "%lu" ,uip_stat.ip.recv        ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                sprintf(str, "\"" "sent"        "\"" ":" "%lu" ,uip_stat.ip.sent        ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                sprintf(str, "\"" "forwarded"   "\"" ":" "%lu" ,uip_stat.ip.forwarded   ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                sprintf(str, "\"" "drop"        "\"" ":" "%lu" ,uip_stat.ip.drop        ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                sprintf(str, "\"" "vhlerr"      "\"" ":" "%lu" ,uip_stat.ip.vhlerr      ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                sprintf(str, "\"" "hblenerr"    "\"" ":" "%lu" ,uip_stat.ip.hblenerr    ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                sprintf(str, "\"" "lblenerr"    "\"" ":" "%lu" ,uip_stat.ip.lblenerr    ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                sprintf(str, "\"" "fragerr"     "\"" ":" "%lu" ,uip_stat.ip.fragerr     ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                sprintf(str, "\"" "chkerr"      "\"" ":" "%lu" ,uip_stat.ip.chkerr      ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                sprintf(str, "\"" "protoerr"    "\"" ":" "%lu" ,uip_stat.ip.protoerr    ); strcat(buf, str);                                                                                                                                                                                         

            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            sprintf(str, "}"); strcat(buf, str);
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            // SUBSECTION END stats{} > ip{}
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

            // ??????????????????????????????????
            sprintf(str, ",");  strcat(buf, str);
            // ??????????????????????????????????
            
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            // SUBSECTION START stats{} > icmp{} ///////////////////
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            sprintf(str, "\"" "icmp" "\"" ":"   ); strcat(buf, str);
            sprintf(str, "{"                    ); strcat(buf, str);
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            
                sprintf(str, "\"" "recv"    "\"" ":" "%lu" ,uip_stat.icmp.recv      ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                sprintf(str, "\"" "sent"    "\"" ":" "%lu" ,uip_stat.icmp.sent      ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                sprintf(str, "\"" "drop"    "\"" ":" "%lu" ,uip_stat.icmp.drop      ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                sprintf(str, "\"" "typeerr" "\"" ":" "%lu" ,uip_stat.icmp.typeerr   ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                sprintf(str, "\"" "chkerr"  "\"" ":" "%lu" ,uip_stat.icmp.chkerr    ); strcat(buf, str);                                                    

            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            sprintf(str, "}"); strcat(buf, str);
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            // SUBSECTION END stats{} > icmp{}
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~                                                                                                                                                                                   

            // ######## (UIP_CONF_STATISTICS)> (UIP_TCP)######## (UIP_CONF_STATISTICS)> (UIP_TCP)######## (UIP_CONF_STATISTICS)> (UIP_TCP)######## (UIP_CONF_STATISTICS)> (UIP_TCP)########
            #if (UIP_TCP)

                // ??????????????????????????????????
                sprintf(str, ",");  strcat(buf, str);
                // ??????????????????????????????????

                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                // SUBSECTION START stats{} > tcp{} ////////////////////
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                sprintf(str, "\"" "tcp" "\"" ":"    ); strcat(buf, str);
                sprintf(str, "{"                    ); strcat(buf, str);
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                
                    sprintf(str, "\"" "tcpUsed" "\"" ":" "true"                         ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                    sprintf(str, "\"" "recv"    "\"" ":" "%lu"  ,uip_stat.tcp.recv      ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                    sprintf(str, "\"" "sent"    "\"" ":" "%lu"  ,uip_stat.tcp.sent      ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                    sprintf(str, "\"" "drop"    "\"" ":" "%lu"  ,uip_stat.tcp.drop      ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                    sprintf(str, "\"" "chkerr"  "\"" ":" "%lu"  ,uip_stat.tcp.chkerr    ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                    sprintf(str, "\"" "ackerr"  "\"" ":" "%lu"  ,uip_stat.tcp.ackerr    ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                    sprintf(str, "\"" "rst"     "\"" ":" "%lu"  ,uip_stat.tcp.rst       ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                    sprintf(str, "\"" "rexmit"  "\"" ":" "%lu"  ,uip_stat.tcp.rexmit    ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                    sprintf(str, "\"" "syndrop" "\"" ":" "%lu"  ,uip_stat.tcp.syndrop   ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                    sprintf(str, "\"" "synrst"  "\"" ":" "%lu"  ,uip_stat.tcp.synrst    ); strcat(buf, str);                                                                                                                                                                                         

                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                sprintf(str, "}"); strcat(buf, str);
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                // SUBSECTION END stats{} > tcp{}
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ 
            
            // ######## (UIP_CONF_STATISTICS)> (UIP_TCP)######## (UIP_CONF_STATISTICS)> (UIP_TCP)######## (UIP_CONF_STATISTICS)> (UIP_TCP)######## (UIP_CONF_STATISTICS)> (UIP_TCP)########
            // ######## (UIP_CONF_STATISTICS)>!(UIP_TCP)######## (UIP_CONF_STATISTICS)>!(UIP_TCP)######## (UIP_CONF_STATISTICS)>!(UIP_TCP)######## (UIP_CONF_STATISTICS)>!(UIP_TCP)########
            #else
            
            // ??????????????????????????????????
            sprintf(str, ",");  strcat(buf, str);
            // ??????????????????????????????????                                                                                                                      

                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                // SUBSECTION START stats{} > tcp{} ////////////////////
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                sprintf(str, "\"" "tcp" "\"" ":"    ); strcat(buf, str);
                sprintf(str, "{"                    ); strcat(buf, str);
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                
                    sprintf(str, "\"" "tcpUsed" "\"" ":" "false"    ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                    sprintf(str, "\"" "recv"    "\"" ":" "null"     ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                    sprintf(str, "\"" "sent"    "\"" ":" "null"     ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                    sprintf(str, "\"" "drop"    "\"" ":" "null"     ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                    sprintf(str, "\"" "chkerr"  "\"" ":" "null"     ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                    sprintf(str, "\"" "ackerr"  "\"" ":" "null"     ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                    sprintf(str, "\"" "rst"     "\"" ":" "null"     ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                    sprintf(str, "\"" "rexmit"  "\"" ":" "null"     ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                    sprintf(str, "\"" "syndrop" "\"" ":" "null"     ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                    sprintf(str, "\"" "synrst"  "\"" ":" "null"     ); strcat(buf, str);    sprintf(str, "," ); //strcat(buf, str);                                                                                                                                                                                      

                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                sprintf(str, "}"); strcat(buf, str);
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                // SUBSECTION END stats{} > tcp{}
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ 
            
            #endif
            // ######## (UIP_CONF_STATISTICS)>!(UIP_TCP)######## (UIP_CONF_STATISTICS)>!(UIP_TCP)######## (UIP_CONF_STATISTICS)>!(UIP_TCP)######## (UIP_CONF_STATISTICS)>!(UIP_TCP)########

            // ######## (UIP_CONF_STATISTICS)> (UIP_UDP)######## (UIP_CONF_STATISTICS)> (UIP_UDP)######## (UIP_CONF_STATISTICS)> (UIP_UDP)######## (UIP_CONF_STATISTICS)> (UIP_UDP)########
            #if (UIP_UDP)

                // ??????????????????????????????????
                sprintf(str, ",");  strcat(buf, str);
                // ??????????????????????????????????

                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                // SUBSECTION START stats{} > udp{} ////////////////////
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                sprintf(str, "\"" "udp" "\"" ":"    ); strcat(buf, str);
                sprintf(str, "{"                    ); strcat(buf, str);
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                
                    sprintf(str, "\"" "udpUsed" "\"" ":" "true"                         ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                    sprintf(str, "\"" "drop"    "\"" ":" "%lu"  ,uip_stat.udp.drop      ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                    sprintf(str, "\"" "recv"    "\"" ":" "%lu"  ,uip_stat.udp.recv      ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                    sprintf(str, "\"" "sent"    "\"" ":" "%lu"  ,uip_stat.udp.sent      ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                    sprintf(str, "\"" "chkerr"  "\"" ":" "%lu"  ,uip_stat.udp.chkerr    ); strcat(buf, str);                                                    

                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                sprintf(str, "}"); strcat(buf, str);
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                // SUBSECTION END stats{} > udp{}
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ 

            // ######## (UIP_CONF_STATISTICS)> (UIP_UDP)######## (UIP_CONF_STATISTICS)> (UIP_UDP)######## (UIP_CONF_STATISTICS)> (UIP_UDP)######## (UIP_CONF_STATISTICS)> (UIP_UDP)########
            // ######## (UIP_CONF_STATISTICS)>!(UIP_UDP)######## (UIP_CONF_STATISTICS)>!(UIP_UDP)######## (UIP_CONF_STATISTICS)>!(UIP_UDP)######## (UIP_CONF_STATISTICS)>!(UIP_UDP)########
            #else

                // ??????????????????????????????????
                sprintf(str, ",");  strcat(buf, str);
                // ??????????????????????????????????

                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                // SUBSECTION START stats{} > udp{} ////////////////////
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                sprintf(str, "\"" "udp" "\"" ":"    ); strcat(buf, str);
                sprintf(str, "{"                    ); strcat(buf, str);
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                
                    sprintf(str, "\"" "udpUsed" "\"" ":" "false"    ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                    sprintf(str, "\"" "drop"    "\"" ":" "null"     ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                    sprintf(str, "\"" "recv"    "\"" ":" "null"     ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                    sprintf(str, "\"" "sent"    "\"" ":" "null"     ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                    sprintf(str, "\"" "chkerr"  "\"" ":" "null"     ); strcat(buf, str);                                                    

                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                sprintf(str, "}"); strcat(buf, str);
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                // SUBSECTION END stats{} > udp{}
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  

            #endif
            // ######## (UIP_CONF_STATISTICS)>!(UIP_UDP)######## (UIP_CONF_STATISTICS)>!(UIP_UDP)######## (UIP_CONF_STATISTICS)>!(UIP_UDP)######## (UIP_CONF_STATISTICS)>!(UIP_UDP)########

            // ??????????????????????????????????
            sprintf(str, ",");  strcat(buf, str);
            // ??????????????????????????????????
            
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            // SUBSECTION START stats{} > nd6{} ////////////////////
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            sprintf(str, "\"" "nd6" "\"" ":"    ); strcat(buf, str);
            sprintf(str, "{"                    ); strcat(buf, str);
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

                sprintf(str, "\"" "drop" "\"" ":" "%lu" ,uip_stat.nd6.drop); strcat(buf, str);  sprintf(str, ","); strcat(buf, str);
                sprintf(str, "\"" "recv" "\"" ":" "%lu" ,uip_stat.nd6.recv); strcat(buf, str);  sprintf(str, ","); strcat(buf, str);
                sprintf(str, "\"" "sent" "\"" ":" "%lu" ,uip_stat.nd6.sent); strcat(buf, str);                                                 

            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            sprintf(str, "}"); strcat(buf, str);
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            // SUBSECTION END stats{} > nd6{}
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        sprintf(str, "}"); strcat(buf, str);
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // SECTION END stats{} /////////////
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    
    // ######## (UIP_CONF_STATISTICS)######## (UIP_CONF_STATISTICS)######## (UIP_CONF_STATISTICS)######## (UIP_CONF_STATISTICS)######## (UIP_CONF_STATISTICS)######## (UIP_CONF_STATISTICS)######## (UIP_CONF_STATISTICS)########
    // ########!(UIP_CONF_STATISTICS)########!(UIP_CONF_STATISTICS)########!(UIP_CONF_STATISTICS)########!(UIP_CONF_STATISTICS)########!(UIP_CONF_STATISTICS)########!(UIP_CONF_STATISTICS)########!(UIP_CONF_STATISTICS)########!
    #else

        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // SECTION START stats{} ///////////////////////////////////
        sprintf(str, "\""   "stats"  "\""    ":"); strcat(buf, str);
        sprintf(str, "{"                        ); strcat(buf, str);
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

            sprintf(str,    "\""    "valid"      "\""    ":" "false");  strcat(buf, str); sprintf(str, "," );  strcat(buf, str);
            
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            // SUBSECTION START stats{} > ip{} /////////////////
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            sprintf(str, "\"" "ip" "\"" ":" ); strcat(buf, str);
            sprintf(str, "{"                ); strcat(buf, str);
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            
                sprintf(str, "\"" "recv"        "\"" ":" "null"); strcat(buf, str); sprintf(str, ","); strcat(buf, str);
                sprintf(str, "\"" "sent"        "\"" ":" "null"); strcat(buf, str); sprintf(str, ","); strcat(buf, str);
                sprintf(str, "\"" "forwarded"   "\"" ":" "null"); strcat(buf, str); sprintf(str, ","); strcat(buf, str);
                sprintf(str, "\"" "drop"        "\"" ":" "null"); strcat(buf, str); sprintf(str, ","); strcat(buf, str);
                sprintf(str, "\"" "vhlerr"      "\"" ":" "null"); strcat(buf, str); sprintf(str, ","); strcat(buf, str);
                sprintf(str, "\"" "hblenerr"    "\"" ":" "null"); strcat(buf, str); sprintf(str, ","); strcat(buf, str);
                sprintf(str, "\"" "lblenerr"    "\"" ":" "null"); strcat(buf, str); sprintf(str, ","); strcat(buf, str);
                sprintf(str, "\"" "fragerr"     "\"" ":" "null"); strcat(buf, str); sprintf(str, ","); strcat(buf, str);
                sprintf(str, "\"" "chkerr"      "\"" ":" "null"); strcat(buf, str); sprintf(str, ","); strcat(buf, str);
                sprintf(str, "\"" "protoerr"    "\"" ":" "null"); strcat(buf, str);                                                                                                                                                                                  

            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            sprintf(str, "}"); strcat(buf, str);
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            // SUBSECTION END stats{} > ip{}
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               

            // ??????????????????????????????????
            sprintf(str, ",");  strcat(buf, str);
            // ??????????????????????????????????
            
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            // SUBSECTION START stats{} > icmp{} ///////////////////
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            sprintf(str, "\"" "icmp" "\"" ":"   ); strcat(buf, str);
            sprintf(str, "{"                    ); strcat(buf, str);
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            
                sprintf(str, "\"" "recv"    "\"" ":" "null"); strcat(buf, str); sprintf(str, ","); strcat(buf, str);
                sprintf(str, "\"" "sent"    "\"" ":" "null"); strcat(buf, str); sprintf(str, ","); strcat(buf, str);
                sprintf(str, "\"" "drop"    "\"" ":" "null"); strcat(buf, str); sprintf(str, ","); strcat(buf, str);
                sprintf(str, "\"" "typeerr" "\"" ":" "null"); strcat(buf, str); sprintf(str, ","); strcat(buf, str);
                sprintf(str, "\"" "chkerr"  "\"" ":" "null"); strcat(buf, str);                                              

            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            sprintf(str, "}"); strcat(buf, str);
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            // SUBSECTION END stats{} > icmp{}
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~                                                                                                                                                                               

            // ########!(UIP_CONF_STATISTICS)> (UIP_TCP)########!(UIP_CONF_STATISTICS)> (UIP_TCP)########!(UIP_CONF_STATISTICS)> (UIP_TCP)########!(UIP_CONF_STATISTICS)> (UIP_TCP)#######!
            #if (UIP_TCP)

                // ??????????????????????????????????
                sprintf(str, ",");  strcat(buf, str);
                // ??????????????????????????????????

                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                // SUBSECTION START stats{} > tcp{} ////////////////////
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                sprintf(str, "\"" "tcp" "\"" ":"    ); strcat(buf, str);
                sprintf(str, "{"                    ); strcat(buf, str);
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                
                sprintf(str, "\"" "tcpUsed" "\"" ":" "null"); strcat(buf, str); sprintf(str, ","); strcat(buf, str);
                sprintf(str, "\"" "recv"    "\"" ":" "null"); strcat(buf, str); sprintf(str, ","); strcat(buf, str);
                sprintf(str, "\"" "sent"    "\"" ":" "null"); strcat(buf, str); sprintf(str, ","); strcat(buf, str);
                sprintf(str, "\"" "drop"    "\"" ":" "null"); strcat(buf, str); sprintf(str, ","); strcat(buf, str);
                sprintf(str, "\"" "chkerr"  "\"" ":" "null"); strcat(buf, str); sprintf(str, ","); strcat(buf, str);
                sprintf(str, "\"" "ackerr"  "\"" ":" "null"); strcat(buf, str); sprintf(str, ","); strcat(buf, str);
                sprintf(str, "\"" "rst"     "\"" ":" "null"); strcat(buf, str); sprintf(str, ","); strcat(buf, str);
                sprintf(str, "\"" "rexmit"  "\"" ":" "null"); strcat(buf, str); sprintf(str, ","); strcat(buf, str);
                sprintf(str, "\"" "syndrop" "\"" ":" "null"); strcat(buf, str); sprintf(str, ","); strcat(buf, str);
                sprintf(str, "\"" "synrst"  "\"" ":" "null"); strcat(buf, str);                                                                                                                                                                                

                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                sprintf(str, "}"); strcat(buf, str);
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                // SUBSECTION END stats{} > tcp{}
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ 
            
            // ########!(UIP_CONF_STATISTICS)> (UIP_TCP)########!(UIP_CONF_STATISTICS)> (UIP_TCP)########!(UIP_CONF_STATISTICS)> (UIP_TCP)########!(UIP_CONF_STATISTICS)> (UIP_TCP)#######!
            // ########!(UIP_CONF_STATISTICS)>!(UIP_TCP)########!(UIP_CONF_STATISTICS)>!(UIP_TCP)########!(UIP_CONF_STATISTICS)>!(UIP_TCP)########!(UIP_CONF_STATISTICS)>!(UIP_TCP)#######!
            #else   
            
                // ??????????????????????????????????
                sprintf(str, ",");  strcat(buf, str);
                // ??????????????????????????????????                                                                                                                    

                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                // SUBSECTION START stats{} > tcp{} ////////////////////
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                sprintf(str, "\"" "tcp" "\"" ":"    ); strcat(buf, str);
                sprintf(str, "{"                    ); strcat(buf, str);
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                
                    sprintf(str, "\"" "tcpUsed" "\"" ":" "null"); strcat(buf, str); sprintf(str, ","); strcat(buf, str);
                    sprintf(str, "\"" "recv"    "\"" ":" "null"); strcat(buf, str); sprintf(str, ","); strcat(buf, str);
                    sprintf(str, "\"" "sent"    "\"" ":" "null"); strcat(buf, str); sprintf(str, ","); strcat(buf, str);
                    sprintf(str, "\"" "drop"    "\"" ":" "null"); strcat(buf, str); sprintf(str, ","); strcat(buf, str);
                    sprintf(str, "\"" "chkerr"  "\"" ":" "null"); strcat(buf, str); sprintf(str, ","); strcat(buf, str);
                    sprintf(str, "\"" "ackerr"  "\"" ":" "null"); strcat(buf, str); sprintf(str, ","); strcat(buf, str);
                    sprintf(str, "\"" "rst"     "\"" ":" "null"); strcat(buf, str); sprintf(str, ","); strcat(buf, str);
                    sprintf(str, "\"" "rexmit"  "\"" ":" "null"); strcat(buf, str); sprintf(str, ","); strcat(buf, str);
                    sprintf(str, "\"" "syndrop" "\"" ":" "null"); strcat(buf, str); sprintf(str, ","); strcat(buf, str);
                    sprintf(str, "\"" "synrst"  "\"" ":" "null"); strcat(buf, str);                                                                                                                                                                                    

                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                sprintf(str, "}"); strcat(buf, str);
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                // SUBSECTION END stats{} > tcp{}
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ 
                
            #endif  
            // ########!(UIP_CONF_STATISTICS)>!(UIP_TCP)########!(UIP_CONF_STATISTICS)>!(UIP_TCP)########!(UIP_CONF_STATISTICS)>!(UIP_TCP)########!(UIP_CONF_STATISTICS)>!(UIP_TCP)#######!

            // ########!(UIP_CONF_STATISTICS)> (UIP_UDP)########!(UIP_CONF_STATISTICS)> (UIP_UDP)########!(UIP_CONF_STATISTICS)> (UIP_UDP)########!(UIP_CONF_STATISTICS)> (UIP_UDP)#######!    
            #if (UIP_UDP)

                // ??????????????????????????????????
                sprintf(str, ",");  strcat(buf, str);
                // ??????????????????????????????????

                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                // SUBSECTION START stats{} > udp{} ////////////////////
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                sprintf(str, "\"" "udp" "\"" ":"    ); strcat(buf, str);
                sprintf(str, "{"                    ); strcat(buf, str);
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                
                    sprintf(str, "\"" "udpUsed" "\"" ":" "null"); strcat(buf, str); sprintf(str, "," ); strcat(buf, str);
                    sprintf(str, "\"" "drop"    "\"" ":" "null"); strcat(buf, str); sprintf(str, "," ); strcat(buf, str);
                    sprintf(str, "\"" "recv"    "\"" ":" "null"); strcat(buf, str); sprintf(str, "," ); strcat(buf, str);
                    sprintf(str, "\"" "sent"    "\"" ":" "null"); strcat(buf, str); sprintf(str, "," ); strcat(buf, str);
                    sprintf(str, "\"" "chkerr"  "\"" ":" "null"); strcat(buf, str);                                                      

                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                sprintf(str, "}"); strcat(buf, str);
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                // SUBSECTION END stats{} > udp{}
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ 

            // ########!(UIP_CONF_STATISTICS)> (UIP_UDP)########!(UIP_CONF_STATISTICS)> (UIP_UDP)########!(UIP_CONF_STATISTICS)> (UIP_UDP)########!(UIP_CONF_STATISTICS)> (UIP_UDP)#######!
            // ########!(UIP_CONF_STATISTICS)>!(UIP_UDP)########!(UIP_CONF_STATISTICS)>!(UIP_UDP)########!(UIP_CONF_STATISTICS)>!(UIP_UDP)########!(UIP_CONF_STATISTICS)>!(UIP_UDP)#######!
            #else

                // ??????????????????????????????????
                sprintf(str, ",");  strcat(buf, str);
                // ?????????????????????????????????? 

                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                // SUBSECTION START stats{} > udp{} ////////////////////
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                sprintf(str, "\"" "udp" "\"" ":"    ); strcat(buf, str);
                sprintf(str, "{"                    ); strcat(buf, str);
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                
                    sprintf(str, "\"" "udpUsed" "\"" ":" "null"); strcat(buf, str); sprintf(str, ","); strcat(buf, str);
                    sprintf(str, "\"" "drop"    "\"" ":" "null"); strcat(buf, str); sprintf(str, ","); strcat(buf, str);
                    sprintf(str, "\"" "recv"    "\"" ":" "null"); strcat(buf, str); sprintf(str, ","); strcat(buf, str);
                    sprintf(str, "\"" "sent"    "\"" ":" "null"); strcat(buf, str); sprintf(str, ","); strcat(buf, str);
                    sprintf(str, "\"" "chkerr"  "\"" ":" "null"); strcat(buf, str);                                                     

                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                sprintf(str, "}"); strcat(buf, str);
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                // SUBSECTION END stats{} > udp{}
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ 

            #endif  
            // ########!(UIP_CONF_STATISTICS)>!(UIP_UDP)########!(UIP_CONF_STATISTICS)>!(UIP_UDP)########!(UIP_CONF_STATISTICS)>!(UIP_UDP)########!(UIP_CONF_STATISTICS)>!(UIP_UDP)#######!

            // ??????????????????????????????????
            sprintf(str, ",");  strcat(buf, str);
            // ??????????????????????????????????  
            
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            // SUBSECTION START stats{} > nd6{} ////////////////////
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            sprintf(str, "\"" "nd6" "\"" ":"    ); strcat(buf, str);
            sprintf(str, "{"                    ); strcat(buf, str);
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

                sprintf(str, "\"" "drop" "\"" ":" "null"); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                sprintf(str, "\"" "recv" "\"" ":" "null"); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                sprintf(str, "\"" "sent" "\"" ":" "null"); strcat(buf, str);                                                         

            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            sprintf(str, "}"); strcat(buf, str);
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            // SUBSECTION END stats{} > nd6{}
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        sprintf(str, "}"); strcat(buf, str);
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // SECTION END stats{} /////////////
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    
    #endif
    // ########!(UIP_CONF_STATISTICS)########!(UIP_CONF_STATISTICS)########!(UIP_CONF_STATISTICS)########!(UIP_CONF_STATISTICS)########!(UIP_CONF_STATISTICS)########!(UIP_CONF_STATISTICS)########!(UIP_CONF_STATISTICS)########!
}





// ----------------------------------------------------------------------------
// function that appends NET section to the json string

static void oar_json_append_net(char * buf)
{
    char str[128];
    
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // SECTION START net{} /////////////////////////////////
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    sprintf(str, "\"" "net" "\"" ":"    ); strcat(buf, str);   
    sprintf(str, "{"                    ); strcat(buf, str);
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

        // ######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)########
        #if (ROUTING_CONF_RPL_LITE)

            sprintf(str,        "\""    "rplLiteUsed"           "\""    ":" "true"   );  strcat(buf, str);    sprintf(str, "," );  strcat(buf, str);

            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            // SUBSECTION START net{} > rplNbr{} ///////////////////
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            sprintf(str, "\"" "rplNbr" "\"" ":" ); strcat(buf, str);
            sprintf(str, "{"                    ); strcat(buf, str);
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

                sprintf(str, "\"" "valid" "\"" ":" "true" ); strcat(buf, str);  sprintf(str, "," ); strcat(buf, str);

                if (!curr_instance.used || rpl_neighbor_count() == 0)
                {
                    
                    if (!curr_instance.used)    { sprintf(str, "\"" "currentInstanceUsed" "\"" ":" "false"  ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str); }
                    else                        { sprintf(str, "\"" "currentInstanceUsed" "\"" ":" "true"   ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str); }
                
                    sprintf(str, "\"" "rplNeighborCount" "\"" ":" "%u" ,rpl_neighbor_count()); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                    
                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    //  (!curr_instance.used || rpl_neighbor_count() == 0) ///////
                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    // SUBARRAY START net{} > rplNbr{} > rplNeighbors[] //////////
                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    sprintf(str, "\"" "rplNeighbors" "\"" ":");  strcat(buf, str);
                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  
                    
                        // [][][][][][][][][][][][][][][][][]
                        sprintf(str, "["); strcat(buf, str);

                        for (int i = 0; i < NBR_TABLE_CONF_MAX_NEIGHBORS; i++)
                        {
                            // {{{{{{{{{{{{{{{{{}}}}}}}}}}}}}}}}}
                            sprintf(str, "{"); strcat(buf, str);

                                sprintf(str, "\"" "ipAddr"                      "\"" ":" "null"); strcat(buf, str); sprintf(str, "," ); strcat(buf, str);
                                sprintf(str, "\"" "rank"                        "\"" ":" "null"); strcat(buf, str); sprintf(str, "," ); strcat(buf, str);
                                sprintf(str, "\"" "linkMetric"                  "\"" ":" "null"); strcat(buf, str); sprintf(str, "," ); strcat(buf, str);
                                sprintf(str, "\"" "rankViaNbr"                  "\"" ":" "null"); strcat(buf, str); sprintf(str, "," ); strcat(buf, str);
                                sprintf(str, "\"" "freshStats"                  "\"" ":" "null"); strcat(buf, str); sprintf(str, "," ); strcat(buf, str);
                                sprintf(str, "\"" "rootRank"                    "\"" ":" "null"); strcat(buf, str); sprintf(str, "," ); strcat(buf, str);
                                sprintf(str, "\"" "bestNbr"                     "\"" ":" "null"); strcat(buf, str); sprintf(str, "," ); strcat(buf, str);
                                sprintf(str, "\"" "acceptRank_AND_acceptPrnt"   "\"" ":" "null"); strcat(buf, str); sprintf(str, "," ); strcat(buf, str);
                                sprintf(str, "\"" "prefParent"                  "\"" ":" "null"); strcat(buf, str); sprintf(str, "," ); strcat(buf, str);
                                sprintf(str, "\"" "lastTxMinutesAgo"            "\"" ":" "null"); strcat(buf, str); sprintf(str, "," );  strcat(buf, str);
                                sprintf(str, "\"" "betterParentSinceMinute"     "\"" ":" "null"); strcat(buf, str);

                            sprintf(str, "}"); strcat(buf, str);
                            // {{{{{{{{{{{{{{{{{}}}}}}}}}}}}}}}}}

                            if (i != (NBR_TABLE_CONF_MAX_NEIGHBORS - 1)) { sprintf(str, "," );  strcat(buf, str); } 
                        }

                        sprintf(str, "]"); strcat(buf, str);
                        // [][][][][][][][][][][][][][][][][]
                }
                else
                {
                    
                    rpl_nbr_t *nbr = nbr_table_head(rpl_neighbors);

                    int oar_json_rpl_neighbor_count = 0;

                    sprintf(str, "\"" "currentInstanceUsed"     "\"" ":" "true"                         ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                    sprintf(str, "\"" "rplNeighborCount"        "\"" ":" "%u"   ,rpl_neighbor_count()   ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);

                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    // !(!curr_instance.used || rpl_neighbor_count() == 0)
                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    // SUBARRAY START net{} > rplNbr{} > rplNeighbors[] /////////////////////////
                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    sprintf(str, "\"" "rplNeighbors" "\"" ":");  strcat(buf, str);
                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~    
                    
                        // [][][][][][][][][][][][][][][][][]
                        sprintf(str, "["); strcat(buf, str);

                        while(nbr != NULL)
                        {
                            oar_json_rpl_neighbor_count++; 
                            
                            rpl_nbr_t *oar_json_rpl_nbr_best = best_parent(0);
                            const struct link_stats *oar_json_rpl_nbr_stats = rpl_neighbor_get_link_stats(nbr);
                            clock_time_t oar_json_rpl_nbr_clock_now = clock_time();

                            // {{{{{{{{{{{{{{{{{}}}}}}}}}}}}}}}}}
                            sprintf(str, "{" ); strcat(buf, str);

                                oar_json_ipaddr_to_str(oar_json_ipaddr, rpl_neighbor_get_ipaddr(nbr));
                                sprintf(str, "\"" "ipAddr"                              "\"" ":" "\""   "%s"    "\""       ,oar_json_ipaddr); strcat(buf, str); sprintf(str, ","); strcat(buf, str);
                                
                                sprintf(str, "\"" "rank"                        "\"" ":"                "%5u"              ,nbr->rank                                                                                                           ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                                sprintf(str, "\"" "linkMetric"                  "\"" ":"                "%5u"              ,rpl_neighbor_get_link_metric(nbr)                                                                                   ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                                sprintf(str, "\"" "rankViaNbr"                  "\"" ":"                "%u"               ,rpl_neighbor_rank_via_nbr(nbr)                                                                                      ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                                sprintf(str, "\"" "freshStats"                  "\"" ":"                "%2u"              ,oar_json_rpl_nbr_stats != NULL ? oar_json_rpl_nbr_stats->freshness : 0                                              ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                                sprintf(str, "\"" "rootRank"                    "\"" ":"                "%s"               ,(nbr->rank == ROOT_RANK) ? "true" : "false"                                                                         ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                                sprintf(str, "\"" "bestNbr"                     "\"" ":"                "%s"               ,nbr == oar_json_rpl_nbr_best ? "true" : "false"                                                                     ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                                sprintf(str, "\"" "acceptRank_AND_acceptPrnt"   "\"" ":"                "%s"               ,((acceptable_rank(rpl_neighbor_rank_via_nbr(nbr)) && rpl_neighbor_is_acceptable_parent(nbr))) ? "true" : "false"    ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                                sprintf(str, "\"" "prefParent"                  "\"" ":"                "%s"               ,nbr == curr_instance.dag.preferred_parent ? "true" : "false"                                                        ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);

                                if(oar_json_rpl_nbr_stats->last_tx_time > 0) 
                                {
                                    sprintf(str, "\"" "lastTxMinutesAgo"        "\"" ":"                "%u"                ,(unsigned)((oar_json_rpl_nbr_clock_now - oar_json_rpl_nbr_stats->last_tx_time) / (60 * CLOCK_SECOND))              ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                                }
                                else
                                {
                                    sprintf(str, "\"" "lastTxMinutesAgo"        "\"" ":"                "null"                                                                                                                                  ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                                }

                                if(nbr->better_parent_since > 0) 
                                {
                                    sprintf(str, "\"" "betterParentSinceMinute" "\"" ":"                "%u"           ,(unsigned)((oar_json_rpl_nbr_clock_now - nbr->better_parent_since) / (60 * CLOCK_SECOND))                               ); strcat(buf, str);   
                                }
                                else
                                {
                                    sprintf(str, "\"" "betterParentSinceMinute" "\"" ":"                "null"                                                                                                                                  ); strcat(buf, str);  
                                }
                                
                            sprintf(str,    "}"      ); strcat(buf, str);
                            // {{{{{{{{{{{{{{{{{}}}}}}}}}}}}}}}}}
                            
                            // rpl_neighbor_snprint(temp_str, sizeof(temp_str), nbr);  // sprintf(str,    "\""    "%s"    "\""    ,temp_str   );  strcat(buf, str);
                            
                            if (oar_json_rpl_neighbor_count < NBR_TABLE_CONF_MAX_NEIGHBORS) { sprintf(str, ","); strcat(buf, str); }
                            nbr = nbr_table_next(rpl_neighbors, nbr);
                        }
                        
                        for (int i = oar_json_rpl_neighbor_count; i < NBR_TABLE_CONF_MAX_NEIGHBORS; i++)
                        {
                            sprintf(str, "null"); strcat(buf, str);
                            if (i != (NBR_TABLE_CONF_MAX_NEIGHBORS - 1)) { sprintf(str, "," );  strcat(buf, str); }
                        }

                        sprintf(str, "]"); strcat(buf, str);
                        // [][][][][][][][][][][][][][][][][]
                }
                
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            sprintf(str, "}"); strcat(buf, str);
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            // SUBSECTION END net{} > rplNbr{}
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

            // ??????????????????????????????????
            sprintf(str, ",");  strcat(buf, str);
            // ?????????????????????????????????? 

            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            // SUBSECTION START net{} > rplStatus{} ////////////////////
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            sprintf(str, "\"" "rplStatus" "\""  ":" ); strcat(buf, str);
            sprintf(str, "{"                        ); strcat(buf, str);
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

                sprintf(str, "\"" "valid" "\"" ":" "true"); strcat(buf, str);   sprintf(str, ","); strcat(buf, str);

                if(!curr_instance.used)             
                { 
                    sprintf(str, "\"" "instanceId" "\"" ":" "\"" "none" "\""); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                    
                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    // (!curr_instance.used) ///////////////////////////
                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    // SUBSECTION START net{} > rplStatus{} > dag{} ////
                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    sprintf(str, "\"" "dag" "\"" ":"); strcat(buf, str);
                    sprintf(str, "{"                ); strcat(buf, str);
                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    
                        sprintf(str, "\"" "valid"           "\"" ":" "false"    ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                        sprintf(str, "\"" "dagType"         "\"" ":" "null"     ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                        sprintf(str, "\"" "dagId"           "\"" ":" "null"     ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                        sprintf(str, "\"" "dagVersion"      "\"" ":" "null"     ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                        sprintf(str, "\"" "dagPrefix"       "\"" ":" "null"     ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                        sprintf(str, "\"" "dagPrefixLength" "\"" ":" "null"     ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                        sprintf(str, "\"" "state"           "\"" ":" "null"     ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                        sprintf(str, "\"" "preferredParent" "\"" ":" "null"     ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                        sprintf(str, "\"" "rank"            "\"" ":" "null"     ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                        sprintf(str, "\"" "lowestRank"      "\"" ":" "null"     ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                        sprintf(str, "\"" "maxRankInc"      "\"" ":" "null"     ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                        
                        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                        // SUBSECTION START net{} > rplStatus{} > dag{} > daoSequence{}
                        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                        sprintf(str, "\"" "daoSequence" "\"" ":"); strcat(buf, str); //
                        sprintf(str, "{"                        ); strcat(buf, str); //
                        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

                            sprintf(str, "\"" "valid"       "\"" ":" "false"    ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                            sprintf(str, "\"" "lastSent"    "\"" ":" "null"     ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                            sprintf(str, "\"" "lastAcked"   "\"" ":" "null"     ); strcat(buf, str);

                        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                        // SUSECTION END net{} > rplStatus{} > dag{} > daoSequence{}
                        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                        sprintf(str, "}"); strcat(buf, str); ///////////////////////
                        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                   
                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    // SUSECTION END net{} > rplStatus{} > dag{}
                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    sprintf(str, "}"); strcat(buf, str); ///////
                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    
                    // ??????????????????????????????????
                    sprintf(str, ",");  strcat(buf, str);
                    // ?????????????????????????????????? 

                    sprintf(str, "\"" "mop"                 "\"" ":" "null"); strcat(buf, str); sprintf(str, ","); strcat(buf, str);
                    sprintf(str, "\"" "of"                  "\"" ":" "null"); strcat(buf, str); sprintf(str, ","); strcat(buf, str);
                    sprintf(str, "\"" "hopRankIncrement"    "\"" ":" "null"); strcat(buf, str); sprintf(str, ","); strcat(buf, str);
                    sprintf(str, "\"" "defaultLifetime"     "\"" ":" "null"); strcat(buf, str); sprintf(str, ","); strcat(buf, str);
                    sprintf(str, "\"" "dtsnOut"             "\"" ":" "null"); strcat(buf, str); sprintf(str, ","); strcat(buf, str);

                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    // SUBSECTION START net{} > rplStatus{} > trickleTimer{} ///////
                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    sprintf(str, "\"" "trickleTimer" "\"" ":"   ); strcat(buf, str);
                    sprintf(str, "{"                            ); strcat(buf, str);
                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

                        sprintf(str,    "\""    "valid"         "\""    ":"       "false"   );  strcat(buf, str);   sprintf(str,    "," );  strcat(buf, str);
                        sprintf(str,    "\""    "currentt"      "\""    ":"       "null"    );  strcat(buf, str);   sprintf(str,    "," );  strcat(buf, str);
                        sprintf(str,    "\""    "nim"           "\""    ":"       "null"    );  strcat(buf, str);   sprintf(str,    "," );  strcat(buf, str);
                        sprintf(str,    "\""    "max"           "\""    ":"       "null"    );  strcat(buf, str);   sprintf(str,    "," );  strcat(buf, str);
                        sprintf(str,    "\""    "redundancy"    "\""    ":"       "null"    );  strcat(buf, str);   // sprintf(str,    "," );  strcat(buf, str);

                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    // SUBSECTION END net{} > rplStatus{} > tricleTimer{}
                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    sprintf(str, "}"); strcat(buf, str); ////////////////
                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                   
                } 
                else                                
                { 
                    sprintf(str, "\"" "instanceId" "\"" ":" "%u" ,curr_instance.instance_id); strcat(buf, str); sprintf(str, "," ); strcat(buf, str);

                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    // !(!curr_instance.used) //////////////////////////
                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    // SUBSECTION START net{} > rplStatus{} > dag{} ////
                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    sprintf(str, "\"" "dag" "\"" ":"); strcat(buf, str);
                    sprintf(str, "{"                ); strcat(buf, str);
                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    
                        sprintf(str, "\"" "valid"          "\"" ":"         "true"                                                                  ); strcat(buf, str);    sprintf(str,  ","); strcat(buf, str);

                        if(NETSTACK_ROUTING.node_is_root()) { sprintf(str, "\"" "dagType" "\"" ":" "\"" "root" "\""); strcat(buf, str); sprintf(str, ","); strcat(buf, str); } 
                        else                                { sprintf(str, "\"" "dagType" "\"" ":" "\"" "node" "\""); strcat(buf, str); sprintf(str, ","); strcat(buf, str); } 
                
                        oar_json_ipaddr_to_str(oar_json_ipaddr, &curr_instance.dag.dag_id);
                        sprintf(str, "\"" "dagId"           "\"" ":" "\""   "%s"    "\""    ,oar_json_ipaddr                                        ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                        
                        sprintf(str, "\"" "dagVersion"      "\"" ":"        "%u"            ,curr_instance.dag.version                              ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);

                        oar_json_ipaddr_to_str(oar_json_ipaddr, &curr_instance.dag.prefix_info.prefix);
                        sprintf(str, "\"" "dagPrefix"       "\"" ":" "\""   "%s"    "\""    ,oar_json_ipaddr                                        ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                        
                        sprintf(str, "\"" "dagPrefixLength" "\"" ":"        "%u"            ,curr_instance.dag.prefix_info.length                   ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                        sprintf(str, "\"" "state"           "\"" ":" "\""   "%s"    "\""    ,oar_json_rpl_state_to_str(curr_instance.dag.state)     ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);

                        if (curr_instance.dag.preferred_parent) 
                        {
                            oar_json_ipaddr_to_str(oar_json_ipaddr, rpl_neighbor_get_ipaddr(curr_instance.dag.preferred_parent));
                            sprintf(str, "\"" "preferredParent" "\"" ":" "\"" "%s"      "\""    ,oar_json_ipaddr    ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                        }
                        else
                        {
                            sprintf(str, "\"" "preferredParent" "\"" ":" "\"" "none"    "\""                        ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                        }

                        sprintf(str, "\"" "rank"            "\"" ":"          "%u"          ,curr_instance.dag.rank                                 ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                        sprintf(str, "\"" "lowestRank"      "\"" ":"          "%u"          ,curr_instance.dag.lowest_rank                          ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                        sprintf(str, "\"" "maxRankInc"      "\"" ":"          "%u"          ,curr_instance.max_rankinc                              ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                        
                        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                        // SUBSECTION START net{} > rplStatus{} > dag{} > daoSequence{}
                        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                        sprintf(str, "\"" "daoSequence" "\"" ":"); strcat(buf, str); //
                        sprintf(str, "{"                        ); strcat(buf, str); //
                        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

                            sprintf(str, "\"" "valid"       "\"" ":" "true"                                         ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                            sprintf(str, "\"" "lastSent"    "\"" ":" "%u"   ,curr_instance.dag.dao_last_seqno       ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                            sprintf(str, "\"" "lastAcked"   "\"" ":" "%u"   ,curr_instance.dag.dao_last_acked_seqno ); strcat(buf, str);   

                        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                        // SUSECTION END net{} > rplStatus{} > dag{} > daoSequence{}
                        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                        sprintf(str, "}"); strcat(buf, str); ///////////////////////
                        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    // SUSECTION END net{} > rplStatus{} > dag{}
                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    sprintf(str, "}"); strcat(buf, str); ///////
                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

                    // ??????????????????????????????????
                    sprintf(str, ",");  strcat(buf, str);
                    // ?????????????????????????????????? 

                    sprintf(str, "\"" "mop"                 "\"" ":" "\""   "%s"    "\""    ,oar_json_rpl_mop_to_str(curr_instance.mop)     ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                    sprintf(str, "\"" "of"                  "\"" ":" "\""   "%s"    "\""    ,oar_json_rpl_ocp_to_str(curr_instance.of->ocp) ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                    sprintf(str, "\"" "hopRankIncrement"    "\"" ":"        "%u"            ,curr_instance.min_hoprankinc                   ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                    sprintf(str, "\"" "defaultLifetime"     "\"" ":"        "%lu"           ,RPL_LIFETIME(curr_instance.default_lifetime)   ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                    sprintf(str, "\"" "dtsnOut"             "\"" ":"        "%u"            ,curr_instance.dtsn_out                         ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                    
                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    // SUBSECTION START net{} > rplStatus{} > trickleTimer{} ///////
                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    sprintf(str, "\"" "trickleTimer" "\"" ":"   ); strcat(buf, str);
                    sprintf(str, "{"                            ); strcat(buf, str);
                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

                        sprintf(str, "\"" "valid"      "\"" ":" "true"                                                          ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                        sprintf(str, "\"" "current"    "\"" ":" "%u"    ,curr_instance.dag.dio_intcurrent                       ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                        sprintf(str, "\"" "min"        "\"" ":" "%u"    ,curr_instance.dio_intmin                               ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                        sprintf(str, "\"" "max"        "\"" ":" "%u"    ,curr_instance.dio_intmin + curr_instance.dio_intdoubl  ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                        sprintf(str, "\"" "redundency" "\"" ":" "%u"    ,curr_instance.dio_redundancy                           ); strcat(buf, str);    

                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                sprintf(str, "}"); strcat(buf, str);
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                // SUBSECTION END net{} > rplStatus > tricleTimer{}
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            }

        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        sprintf(str, "}"); strcat(buf, str);
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // SUBSECTION END net{} > rplStatus{}
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    // ######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)########
    // ########!(ROUTING_CONF_RPL_LITE)########!(ROUTING_CONF_RPL_LITE)########!(ROUTING_CONF_RPL_LITE)########!(ROUTING_CONF_RPL_LITE)########!(ROUTING_CONF_RPL_LITE)########!(ROUTING_CONF_RPL_LITE)########!
    #else

        sprintf(str, "\"" "rplLiteUsed" "\"" ":" "false"); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);

        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // SUBSECTION START net{} > rplNbr{} ///////////////////
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        sprintf(str, "\"" "rplNbr" "\"" ":" ); strcat(buf, str);
        sprintf(str, "{"                    ); strcat(buf, str);
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        
            sprintf(str, "\"" "valid"               "\""  ":" "false"   ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);

            sprintf(str, "\"" "currentInstanceUsed" "\"" ":" "null"     ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
            sprintf(str, "\"" "rplNeighborCount"    "\"" ":" "null"     ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);

            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            // SUBARRAY START net{} > rplNbr{} > rplNeighbors[] //////////
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            sprintf(str, "\"" "rplNeighbors" "\"" ":");  strcat(buf, str);
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            
                // [][][][][][][][][][][][][][][][][]
                sprintf(str, "["); strcat(buf, str);

                for (int i = 0; i < NBR_TABLE_CONF_MAX_NEIGHBORS; i++)
                {
                    sprintf(str,    "null"  );  strcat(buf, str);
                    if (i != (NBR_TABLE_CONF_MAX_NEIGHBORS - 1)) { sprintf(str, "," );  strcat(buf, str); } 
                }

                sprintf(str, "]"); strcat(buf, str);
                // [][][][][][][][][][][][][][][][][]
            

        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        sprintf(str, "}"); strcat(buf, str);
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // SUBSECTION END net{} > rplNbr{}
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

        // ??????????????????????????????????
        sprintf(str, ",");  strcat(buf, str);
        // ??????????????????????????????????

        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // SUBSECTION START net{} > rplStatus{} ////////////////////
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        sprintf(str, "\"" "rplStatus" "\""  ":" ); strcat(buf, str);
        sprintf(str, "{"                        ); strcat(buf, str);
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

            sprintf(str, "\"" "valid"       "\"" ":"       "false"          ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
            sprintf(str, "\"" "instanceId"  "\"" ":" "\""  "none"       "\""); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                // SUBSECTION START net{} > rplStatus{} > dag{} ////
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                sprintf(str, "\"" "dag" "\"" ":"); strcat(buf, str);
                sprintf(str, "{"                ); strcat(buf, str);
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                
                    sprintf(str, "\"" "valid"           "\"" ":" "false"    ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                    sprintf(str, "\"" "dagType"         "\"" ":" "null"     ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                    sprintf(str, "\"" "dagId"           "\"" ":" "null"     ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                    sprintf(str, "\"" "dagVersion"      "\"" ":" "null"     ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                    sprintf(str, "\"" "dagPrefix"       "\"" ":" "null"     ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                    sprintf(str, "\"" "dagPrefixLength" "\"" ":" "null"     ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                    sprintf(str, "\"" "state"           "\"" ":" "null"     ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                    sprintf(str, "\"" "preferredParent" "\"" ":" "null"     ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                    sprintf(str, "\"" "rank"            "\"" ":" "null"     ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                    sprintf(str, "\"" "lowestRank"      "\"" ":" "null"     ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                    sprintf(str, "\"" "maxRankInc"      "\"" ":" "null"     ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                    
                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    // SUBSECTION START net{} > rplStatus{} > dag{} > daoSequence{}
                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    sprintf(str, "\"" "daoSequence" "\"" ":"); strcat(buf, str); //
                    sprintf(str, "{"                        ); strcat(buf, str); //
                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

                        sprintf(str, "\"" "valid"       "\"" ":" "false"    ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                        sprintf(str, "\"" "lastSent"    "\"" ":" "null"     ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                        sprintf(str, "\"" "lastAcked"   "\"" ":" "null"     ); strcat(buf, str);    


                     // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    // SUSECTION END net{} > rplStatus{} > dag{} > daoSequence{}
                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    sprintf(str, "}"); strcat(buf, str); ///////////////////////
                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                // SUSECTION END net{} > rplStatus{} > dag{}
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                sprintf(str, "}"); strcat(buf, str); ///////
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

                // ??????????????????????????????????
                sprintf(str, ",");  strcat(buf, str);
                // ?????????????????????????????????? 

                sprintf(str, "\"" "mop"                 "\"" ":" "null"); strcat(buf, str); sprintf(str, ","); strcat(buf, str);
                sprintf(str, "\"" "of"                  "\"" ":" "null"); strcat(buf, str); sprintf(str, ","); strcat(buf, str);
                sprintf(str, "\"" "hopRankIncrement"    "\"" ":" "null"); strcat(buf, str); sprintf(str, ","); strcat(buf, str);
                sprintf(str, "\"" "defaultLifetime"     "\"" ":" "null"); strcat(buf, str); sprintf(str, ","); strcat(buf, str);
                sprintf(str, "\"" "dtsnOut"             "\"" ":" "null"); strcat(buf, str); sprintf(str, ","); strcat(buf, str);

                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                // SUBSECTION START net{} > rplStatus{} > trickleTimer{} ///////
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                sprintf(str, "\"" "trickleTimer" "\"" ":"   ); strcat(buf, str);
                sprintf(str, "{"                            ); strcat(buf, str);
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

                    sprintf(str, "\"" "valid"       "\"" ":" "false"    ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                    sprintf(str, "\"" "currentt"    "\"" ":" "null"     ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                    sprintf(str, "\"" "nim"         "\"" ":" "null"     ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                    sprintf(str, "\"" "max"         "\"" ":" "null"     ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                    sprintf(str, "\"" "redundancy"  "\"" ":" "null"     ); strcat(buf, str);    

            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            sprintf(str, "}"); strcat(buf, str);
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            // SUBSECTION END net{} > rplStatus > tricleTimer{}
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        sprintf(str, "}"); strcat(buf, str);
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // SUBSECTION END net{} > rplStatus{}
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    #endif
    // ########!(ROUTING_CONF_RPL_LITE)########!(ROUTING_CONF_RPL_LITE)########!(ROUTING_CONF_RPL_LITE)########!(ROUTING_CONF_RPL_LITE)########!(ROUTING_CONF_RPL_LITE)########!(ROUTING_CONF_RPL_LITE)########!
    
    // ??????????????????????????????????
    sprintf(str, ",");  strcat(buf, str);
    // ?????????????????????????????????? 

    oar_json_lladdr_to_str(oar_json_lladdr, &linkaddr_node_addr);
    sprintf(str, "\"" "nodeMacAddress" "\"" ":" "\"" "%s" "\"" ,oar_json_lladdr); strcat(buf, str); sprintf(str, ","); strcat(buf, str);

    // ######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)########
    #if (NETSTACK_CONF_WITH_IPV6)

        sprintf(str, "\"" "ipv6Used" "\"" ":" "true"); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);

        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // SUBSECTION START net{} > ipAddr{} //////////////////
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        sprintf(str, "\"" "ipAddr" "\"" ":" ); strcat(buf, str);
        sprintf(str, "{"                    ); strcat(buf, str);
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

            sprintf(str, "\"" "valid" "\"" ":" "true"); strcat(buf, str);   sprintf(str, ","); strcat(buf, str);

            uint8_t state;
            int oar_json_ipaddr_count = 0;

            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            // SUBARRAY START net{} > ipAddr{} > nodeIpv6addresses[] /////////
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            sprintf(str, "\"" "nodeIpv6addresses" "\"" ":"); strcat(buf, str);  
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

                // [[[[[[[[[[[[[[[[[]]]]]]]]]]]]]]]]]
                sprintf(str, "["); strcat(buf, str);

                for(int i = 0; i < UIP_DS6_ADDR_NB; i++) 
                {
                    state = uip_ds6_if.addr_list[i].state;

                    if(uip_ds6_if.addr_list[i].isused && (state == ADDR_TENTATIVE || state == ADDR_PREFERRED)) 
                    {
                        oar_json_ipaddr_count++;
                        
                        oar_json_ipaddr_to_str(oar_json_ipaddr, &uip_ds6_if.addr_list[i].ipaddr);
                        sprintf(str, "\"" "%s"      "\"" ,oar_json_ipaddr   ); strcat(buf, str);

                        if (i != (UIP_DS6_ADDR_NB - 1)) { sprintf(str, "," );  strcat(buf, str); }
                    }
                    else
                    {

                        sprintf(str, "\""  "null"   "\""                    ); strcat(buf, str);
                        
                        if (i != (UIP_DS6_ADDR_NB - 1)) { sprintf(str, "," );  strcat(buf, str); } 
                    }
                    
                }

                sprintf(str, "]"); strcat(buf, str);
                // [[[[[[[[[[[[[[[[[]]]]]]]]]]]]]]]]]   
                
            // ??????????????????????????????????
            sprintf(str, ",");  strcat(buf, str);
            // ?????????????????????????????????? 

            sprintf(str,    "\""    "addrIssuedCount"           "\""    ":" "%u"    ,oar_json_ipaddr_count                               );  strcat(buf, str);   // sprintf(str,    "," );  strcat(buf, str);

        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        sprintf(str, "}"); strcat(buf, str);
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // SUBSECTION END net{} > ipAddr{} /
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        
        // ??????????????????????????????????
        sprintf(str, ",");  strcat(buf, str);
        // ?????????????????????????????????? 

        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // SUBSECTION START net{} > ipNbr{} //////////////////
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        sprintf(str, "\"" "ipNbr" "\"" ":"  ); strcat(buf, str);
        sprintf(str, "{"                    ); strcat(buf, str);
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

            sprintf(str, "\"" "valid"  "\"" ":" "true"); strcat(buf, str);  sprintf(str, ","); strcat(buf, str);
            
            uip_ds6_nbr_t *nbr;
            int oar_json_ip_neighbor_count = 0;

            nbr = uip_ds6_nbr_head();

            if(nbr == NULL)
            {
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                //  (nbr == NULL) ///////////////////////////////////////////////
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                // SUBARRAY START net{} > ipNbr{} > nodeIpv6neigbors[] //////////
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                sprintf(str, "\"" "nodeIpv6neigbors" "\"" ":"); strcat(buf, str); 
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

                    // [[[[[[[[[[[[[[[[[]]]]]]]]]]]]]]]]]
                    sprintf(str, "["); strcat(buf, str);

                    for (int i = 0; i < NBR_TABLE_CONF_MAX_NEIGHBORS; i++)
                    {
                        // {{{{{{{{{{{{{{{{{}}}}}}}}}}}}}}}}}
                        sprintf(str, "{"); strcat(buf, str);
                        
                            sprintf(str, "\"" "ipAddr" "\"" ":" "null"); strcat(buf, str);  sprintf(str, "," );  strcat(buf, str);
                            sprintf(str, "\"" "llAddr" "\"" ":" "null"); strcat(buf, str);  sprintf(str, "," );  strcat(buf, str);
                            sprintf(str, "\"" "router" "\"" ":" "null"); strcat(buf, str);  sprintf(str, "," );  strcat(buf, str);
                            sprintf(str, "\"" "state"  "\"" ":" "null"); strcat(buf, str);

                        // {{{{{{{{{{{{{{{{{}}}}}}}}}}}}}}}}}
                        sprintf(str, "}"); strcat(buf, str);

                        if (i != (NBR_TABLE_CONF_MAX_NEIGHBORS - 1)) { sprintf(str, "," );  strcat(buf, str); };
                    }

                    sprintf(str, "]"); strcat(buf, str);
                    // [[[[[[[[[[[[[[[[[]]]]]]]]]]]]]]]]]  

                // ??????????????????????????????????
                sprintf(str, ",");  strcat(buf, str);
                // ?????????????????????????????????? 

                sprintf(str,    "\""    "ipNbrCount"    "\""    ":" "%u"    ,oar_json_ip_neighbor_count );  strcat(buf, str); 
            }
            else
            {
                
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                // !(nbr == NULL) ///////////////////////////////////////////////
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                // SUBARRAY START net{} > ipNbr{} > nodeIpv6neigbors[] //////////
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                sprintf(str, "\"" "nodeIpv6neigbors" "\"" ":"); strcat(buf, str); 
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                
                        // [[[[[[[[[[[[[[[[[]]]]]]]]]]]]]]]]]
                        sprintf(str, "["); strcat(buf, str);
                    
                        while(nbr != NULL)
                        {
                            oar_json_ip_neighbor_count++;
                            
                            // {{{{{{{{{{{{{{{{{}}}}}}}}}}}}}}}}}
                            sprintf(str, "{"); strcat(buf, str);
                            
                                oar_json_ipaddr_to_str(oar_json_ipaddr, uip_ds6_nbr_get_ipaddr(nbr));
                                sprintf(str,    "\""    "ipAddr"    "\""    ":" "\""    "%s"    "\""    ,oar_json_ipaddr                            ); strcat(buf, str);    sprintf(str, ",");  strcat(buf, str);

                                oar_json_lladdr_to_str(oar_json_lladdr, (linkaddr_t *)uip_ds6_nbr_get_ll(nbr));
                                sprintf(str,    "\""    "llAddr"    "\""    ":" "\""    "%s"    "\""    ,oar_json_lladdr                            ); strcat(buf, str);    sprintf(str, ",");  strcat(buf, str);

                                sprintf(str,    "\""    "router"    "\""    ":"         "%u"            ,nbr->isrouter                              ); strcat(buf, str);    sprintf(str, ",");  strcat(buf, str);
                                sprintf(str,    "\""    "state"     "\""    ":" "\""    "%s"    "\""    ,oar_json_ds6_nbr_state_to_str(nbr->state)  ); strcat(buf, str);

                            sprintf(str, "}"); strcat(buf, str);
                            // {{{{{{{{{{{{{{{{{}}}}}}}}}}}}}}}}}

                            if (oar_json_ip_neighbor_count != NBR_TABLE_CONF_MAX_NEIGHBORS) { sprintf(str, "," );  strcat(buf, str); }
                            
                            nbr = uip_ds6_nbr_next(nbr);
                        }

                        for (int j = oar_json_ip_neighbor_count; j < NBR_TABLE_CONF_MAX_NEIGHBORS; j++)
                        {
                            
                            // {{{{{{{{{{{{{{{{{}}}}}}}}}}}}}}}}}
                            sprintf(str, "{"); strcat(buf, str);
                            
                                sprintf(str, "\"" "ipAddr" "\"" ":" "null"); strcat(buf, str);  sprintf(str, "," ); strcat(buf, str);
                                sprintf(str, "\"" "llAddr" "\"" ":" "null"); strcat(buf, str);  sprintf(str, "," ); strcat(buf, str);
                                sprintf(str, "\"" "router" "\"" ":" "null"); strcat(buf, str);  sprintf(str, "," ); strcat(buf, str);
                                sprintf(str, "\"" "state"  "\"" ":" "null"); strcat(buf, str);

                            sprintf(str, "}"); strcat(buf, str);
                            // {{{{{{{{{{{{{{{{{}}}}}}}}}}}}}}}}}

                            if (j != (NBR_TABLE_CONF_MAX_NEIGHBORS - 1)) { sprintf(str, "," );  strcat(buf, str); };
                        }

                    sprintf(str, "]"); strcat(buf, str);
                    // [[[[[[[[[[[[[[[[[]]]]]]]]]]]]]]]]]


                // ??????????????????????????????????
                sprintf(str, ",");  strcat(buf, str);
                // ?????????????????????????????????? 

                sprintf(str, "\"" "ipNbrCount" "\""  ":" "%u" ,oar_json_ip_neighbor_count);  strcat(buf, str); 
            }
            
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        sprintf(str, "}"); strcat(buf, str);
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // SUBSECTION END net{} > ipNbr{} /
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        
        // ??????????????????????????????????
        sprintf(str, ",");  strcat(buf, str);
        // ?????????????????????????????????? 

        
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // SUBSECTION START net{} > routes{} ///////////////////
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        sprintf(str, "\"" "routes" "\"" ":" ); strcat(buf, str);
        sprintf(str, "{"                    ); strcat(buf, str);
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

            sprintf(str, "\"" "valid" "\"" ":" "true"); strcat(buf, str);   sprintf(str, ","); strcat(buf, str);

            uip_ds6_defrt_t *default_route;
            default_route = uip_ds6_defrt_lookup(uip_ds6_defrt_choose());

            if(default_route != NULL)
            {
                oar_json_ipaddr_to_str(oar_json_ipaddr, &default_route->ipaddr);
                sprintf(str,    "\""        "defaultRoute"      "\""        ":"     "\""        "%s"        "\""        ,oar_json_ipaddr        );  strcat(buf, str);   sprintf(str, "," );  strcat(buf, str);

                if (default_route->lifetime.interval != 0)  { sprintf(str,   "\""    "lifetimeSeconds"   "\""    ":" "\""    "%lu"      "\""    ,(unsigned long)default_route->lifetime.interval      );  strcat(buf, str);   sprintf(str, "," );  strcat(buf, str); }
                else                                        { sprintf(str,   "\""    "lifetimeSeconds"   "\""    ":" "\""    "infinite" "\""                                                          );  strcat(buf, str); }   // sprintf(str, "," );  strcat(buf, str);  
            }
            else
            {
                sprintf(str,    "\""        "defaultRoute"      "\""        ":"     "\""        "none"      "\""                                );  strcat(buf, str);   sprintf(str, "," );  strcat(buf, str);
                sprintf(str,    "\""        "lifetimeSeconds"   "\""        ":"                 "null"                                          );  strcat(buf, str);   // sprintf(str, "," );  strcat(buf, str);

            }

            // ######## (NETSTACK_CONF_WITH_IPV6)> (UIP_CONF_IPV6_RPL)######## (NETSTACK_CONF_WITH_IPV6)> (UIP_CONF_IPV6_RPL)######## (NETSTACK_CONF_WITH_IPV6)> (UIP_CONF_IPV6_RPL)######## (NETSTACK_CONF_WITH_IPV6)> (UIP_CONF_IPV6_RPL)######## 
            #if (UIP_CONF_IPV6_RPL)

                // ??????????????????????????????????
                sprintf(str, ",");  strcat(buf, str);
                // ?????????????????????????????????? 

                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                // SUBSECTION START net{} > routes{} > routingLinks{} //////////
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                sprintf(str, "\"" "routingLinks" "\"" ":"   ); strcat(buf, str);  
                sprintf(str, "{"                            ); strcat(buf, str);
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

                sprintf(str, "\"" "valid" "\"" ":" "true"); strcat(buf, str);   sprintf(str, "," ); strcat(buf, str);

                int oar_json_uip_sr_links_count = 0;
                

                if (uip_sr_num_nodes() > 0)
                {
                    
                    uip_sr_node_t *link;
                    link = uip_sr_node_head();

                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    //  (uip_sr_num_nodes() > 0) ////////////////////////////////
                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    // SUBARRAY START net{} > routes{} > routingLinks{} > links[]
                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    sprintf(str, "\"" "links" "\"" ":"); strcat(buf, str); //////
                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    
                        // [[[[[[[[[[[[[[[[]]]]]]]]]]]]]]]]
                        sprintf(str,"["); strcat(buf, str);
                        
                        while(link != NULL) 
                        {
                            char goa_buf[100];
                            oar_json_uip_sr_links_count++;

                            uip_sr_link_snprint(goa_buf, sizeof(goa_buf), link);
                            
                            sprintf(str,    "\""    "%s"    "\""    ,goa_buf ); strcat(buf, str);
                            
                            if (oar_json_uip_sr_links_count != NBR_TABLE_CONF_MAX_NEIGHBORS)    { sprintf(str, "," );  strcat(buf, str); }

                            link = uip_sr_node_next(link);
                        }

                        for (int j = oar_json_uip_sr_links_count; j < NBR_TABLE_CONF_MAX_NEIGHBORS; j++)
                        {
                            
                            sprintf(str,    "\""    "null"    "\""  ); strcat(buf, str);
                            
                            if (j != (NBR_TABLE_CONF_MAX_NEIGHBORS - 1)) { sprintf(str, "," );  strcat(buf, str); };
                        }

                        sprintf(str, "]"); strcat(buf, str);   
                        // [[[[[[[[[[[[[[[[[]]]]]]]]]]]]]]]]]

                    // ??????????????????????????????????
                    sprintf(str, ",");  strcat(buf, str);
                    // ?????????????????????????????????? 

                    sprintf(str,    "\""    "uipSrLinkCount"    "\""    ":" "%u"    ,oar_json_uip_sr_links_count );  strcat(buf, str); 

                }
                else
                {

                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    // !(uip_sr_num_nodes() > 0) ////////////////////////////////
                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    // SUBARRAY START net{} > routes{} > routingLinks{} > links[]
                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    sprintf(str, "\"" "links" "\"" ":"); strcat(buf, str); //////
                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

                        // [[[[[[[[[[[[[[[[]]]]]]]]]]]]]]]]
                        sprintf(str,"["); strcat(buf, str);

                        for (int j = 0; j < NBR_TABLE_CONF_MAX_NEIGHBORS; j++)
                        {
                            
                            sprintf(str,    "\""    "null"    "\""  ); strcat(buf, str);
                            
                            if (j != (NBR_TABLE_CONF_MAX_NEIGHBORS - 1)) { sprintf(str, "," );  strcat(buf, str); };
                        }
                        
                        sprintf(str, "]"); strcat(buf, str);   
                        // [[[[[[[[[[[[[[[[[]]]]]]]]]]]]]]]]]

                    // ??????????????????????????????????
                    sprintf(str, ",");  strcat(buf, str);
                    // ?????????????????????????????????? 

                    sprintf(str,    "\""    "uipSrLinkCount"    "\""    ":"    "\""    "none"  "\""    );  strcat(buf, str); 
                }
                
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                sprintf(str, "}"); strcat(buf, str); //////////////
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                // SUBSECTION END net{} > routes{} > routingLinks{}
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                
            // ######## (NETSTACK_CONF_WITH_IPV6)> (UIP_CONF_IPV6_RPL)######## (NETSTACK_CONF_WITH_IPV6)> (UIP_CONF_IPV6_RPL)######## (NETSTACK_CONF_WITH_IPV6)> (UIP_CONF_IPV6_RPL)######## (NETSTACK_CONF_WITH_IPV6)> (UIP_CONF_IPV6_RPL)######## 
            // ######## (NETSTACK_CONF_WITH_IPV6)>!(UIP_CONF_IPV6_RPL)######## (NETSTACK_CONF_WITH_IPV6)>!(UIP_CONF_IPV6_RPL)######## (NETSTACK_CONF_WITH_IPV6)>!(UIP_CONF_IPV6_RPL)######## (NETSTACK_CONF_WITH_IPV6)>!(UIP_CONF_IPV6_RPL)######## 
            # else
        
                // ??????????????????????????????????
                sprintf(str, ",");  strcat(buf, str);
                // ?????????????????????????????????? 

                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                // SUBSECTION START net{} > routes{} > routingLinks{} //////////
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                sprintf(str, "\"" "routingLinks" "\"" ":"   ); strcat(buf, str);  
                sprintf(str, "{"                            ); strcat(buf, str);
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

                    sprintf(str, "\"" "valid" "\"" ":" "false"); strcat(buf, str);  sprintf(str, ","); strcat(buf, str);

                    
                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    // SUBARRAY START net{} > routes{} > routingLinks{} > links[]
                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    sprintf(str, "\"" "links" "\"" ":"); strcat(buf, str); //////
                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    
                        // [[[[[[[[[[[[[[[[]]]]]]]]]]]]]]]]
                        sprintf(str,"["); strcat(buf, str);

                        for (int j = 0; j < NBR_TABLE_CONF_MAX_NEIGHBORS; j++)
                        {
                            
                            sprintf(str,    "\""    "null"    "\""  ); strcat(buf, str);
                            
                            if (j != (NBR_TABLE_CONF_MAX_NEIGHBORS - 1)) { sprintf(str, "," );  strcat(buf, str); };
                        }
                            
                        sprintf(str, "]"); strcat(buf, str);   
                        // [[[[[[[[[[[[[[[[[]]]]]]]]]]]]]]]]]

                    // ??????????????????????????????????
                    sprintf(str, ",");  strcat(buf, str);
                    // ?????????????????????????????????? 

                    sprintf(str,    "\""    "uipSrLink_count"    "\""    ":"    "null"  );  strcat(buf, str); 

                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                sprintf(str, "}"); strcat(buf, str); //////////////
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                // SUBSECTION END net{} > routes{} > routingLinks{}
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

            #endif
            // ######## (NETSTACK_CONF_WITH_IPV6)>!(UIP_CONF_IPV6_RPL)######## (NETSTACK_CONF_WITH_IPV6)>!(UIP_CONF_IPV6_RPL)######## (NETSTACK_CONF_WITH_IPV6)>!(UIP_CONF_IPV6_RPL)######## (NETSTACK_CONF_WITH_IPV6)>!(UIP_CONF_IPV6_RPL)########

            // ######## (NETSTACK_CONF_WITH_IPV6)> (UIP_MAX_ROUTES != 0)######## (NETSTACK_CONF_WITH_IPV6)> (UIP_MAX_ROUTES != 0)######## (NETSTACK_CONF_WITH_IPV6)> (UIP_MAX_ROUTES != 0)######## (NETSTACK_CONF_WITH_IPV6)> (UIP_MAX_ROUTES != 0)######## 
            #if (UIP_MAX_ROUTES != 0)

                // ??????????????????????????????????
                sprintf(str, ",");  strcat(buf, str);
                // ?????????????????????????????????? 

                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                // SUBSECTION START net{} > routes{} > routingEntries{} ////////
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                sprintf(str, "\"" "routingEntries" "\"" ":" ); strcat(buf, str);  
                sprintf(str, "{"                            ); strcat(buf, str);
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

                    sprintf(str, "\"" "valid" "\"" ":" "true"); strcat(buf, str);   
                    
                    // ??????????????????????????????????
                    sprintf(str, ",");  strcat(buf, str);
                    // ?????????????????????????????????? 
                    

                    if(uip_ds6_route_num_routes() > 0)
                    {
                        uip_ds6_route_t *route;
                        sprintf(str, "\"" "total" "\"" ":" "%u" ,uip_ds6_route_num_routes()); strcat(buf, str); sprintf(str, "," ); strcat(buf, str);

                        route = uip_ds6_route_head();
                        int oar_json_ds6_route_count = 0;

                        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                        //  (uip_ds6_route_num_routes() > 0) ////////////////////////////
                        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                        // SUBARRAY START net{} > routes{} > routingEntries{} > entries[]
                        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                        sprintf(str, "\"" "entries" "\"" ":"); strcat(buf, str); ////////
                        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

                        // [[[[[[[[[[[[[[[[]]]]]]]]]]]]]]]]
                        sprintf(str,"["); strcat(buf, str);
                        
                        while(route != NULL) 
                        {
                            oar_json_ds6_route_count++;

                            // {{{{{{{{{{{{{{{{{}}}}}}}}}}}}}}}}}
                            sprintf(str, "{"); strcat(buf, str);

                                oar_json_ipaddr_to_str(oar_json_ipaddr, &route->ipaddr);
                                sprintf(str,    "\""    "route"     "\""    ":" "\""    "%s"    "\""    ,oar_json_ipaddr); strcat(buf, str);    sprintf(str, "," );  strcat(buf, str);

                                oar_json_ipaddr_to_str(oar_json_ipaddr, uip_ds6_route_nexthop(route));
                                sprintf(str,    "\""    "via"       "\""    ":" "\""    "%s"    "\""    ,oar_json_ipaddr); strcat(buf, str);    sprintf(str, "," );  strcat(buf, str);

                                if ((unsigned long)route->state.lifetime != 0xFFFFFFFF) { sprintf(str,  "\""  "lifetime"    "\""    ":"         "%u"                ,(unsigned long)route->state.lifetime); strcat(buf, str); }
                                else                                                    { sprintf(str,  "\""  "lifetime"    "\""    ":" "\""    "infinite"  "\""                                         ); strcat(buf, str); }

                            // {{{{{{{{{{{{{{{{{}}}}}}}}}}}}}}}}}
                            sprintf(str, "}"); strcat(buf, str);
                        
                            if (oar_json_ds6_route_count != NBR_TABLE_CONF_MAX_NEIGHBORS)    { sprintf(str, "," );  strcat(buf, str); }
                        }

                        for (int j = oar_json_ds6_route_count; j < NBR_TABLE_CONF_MAX_NEIGHBORS; j++)
                        {
                            
                            // {{{{{{{{{{{{{{{{{}}}}}}}}}}}}}}}}}
                            sprintf(str, "{"); strcat(buf, str);

                                sprintf(str,    "\""    "route"     "\""    ":" "null"  ); strcat(buf, str);    sprintf(str, "," );  strcat(buf, str);
                                sprintf(str,    "\""    "via"       "\""    ":" "null"  ); strcat(buf, str);    sprintf(str, "," );  strcat(buf, str);
                                sprintf(str,    "\""    "lifetime"  "\""    ":" "null"  ); strcat(buf, str);    // sprintf(str, "," );  strcat(buf, str);

                            // {{{{{{{{{{{{{{{{{}}}}}}}}}}}}}}}}}
                            sprintf(str, "}"); strcat(buf, str);
                            
                            if (j != (NBR_TABLE_CONF_MAX_NEIGHBORS - 1)) { sprintf(str, "," );  strcat(buf, str); };
                        }

                        sprintf(str, "]"); strcat(buf, str);
                        // [[[[[[[[[[[[[[[[[]]]]]]]]]]]]]]]]]
                    }
                    else
                    {
                        sprintf(str, "\"" "total" "\"" ":" "\"" "none" "\"" ); strcat(buf, str);    
                        
                        // ??????????????????????????????????
                        sprintf(str, ",");  strcat(buf, str);
                        // ?????????????????????????????????? 

                        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                        // !(uip_ds6_route_num_routes() > 0) ////////////////////////////
                        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                        // SUBARRAY START net{} > routes{} > routingEntries{} > entries[]
                        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                        sprintf(str, "\"" "entries" "\"" ":"); strcat(buf, str); ////////
                        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                        
                            // [[[[[[[[[[[[[[[[]]]]]]]]]]]]]]]]
                            sprintf(str,"["); strcat(buf, str);

                            for (int j = 0; j < NBR_TABLE_CONF_MAX_NEIGHBORS; j++)
                            {
                                
                                // {{{{{{{{{{{{{{{{{}}}}}}}}}}}}}}}}}
                                sprintf(str, "{"); strcat(buf, str);

                                    sprintf(str, "\"" "route"     "\"" ":" "null"); strcat(buf, str);   sprintf(str, "," );  strcat(buf, str);
                                    sprintf(str, "\"" "via"       "\"" ":" "null"); strcat(buf, str);   sprintf(str, "," );  strcat(buf, str);
                                    sprintf(str, "\"" "lifetime"  "\"" ":" "null"); strcat(buf, str);

                                // {{{{{{{{{{{{{{{{{}}}}}}}}}}}}}}}}}
                                sprintf(str, "}"); strcat(buf, str);
                                
                                if (j != (NBR_TABLE_CONF_MAX_NEIGHBORS - 1)) { sprintf(str, "," );  strcat(buf, str); };
                            }

                            sprintf(str, "]"); strcat(buf, str);
                            // [[[[[[[[[[[[[[[[[]]]]]]]]]]]]]]]]]
                    }
                    
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                sprintf(str, "}"); strcat(buf, str); ////////////////
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                // SUBSECTION END net{} > routes{} > routingEntries{}
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                

            // ######## (NETSTACK_CONF_WITH_IPV6)> (UIP_MAX_ROUTES != 0)######## (NETSTACK_CONF_WITH_IPV6)> (UIP_MAX_ROUTES != 0)######## (NETSTACK_CONF_WITH_IPV6)> (UIP_MAX_ROUTES != 0)######## (NETSTACK_CONF_WITH_IPV6)> (UIP_MAX_ROUTES != 0)######## 
            // ######## (NETSTACK_CONF_WITH_IPV6)>!(UIP_MAX_ROUTES != 0)######## (NETSTACK_CONF_WITH_IPV6)>!(UIP_MAX_ROUTES != 0)######## (NETSTACK_CONF_WITH_IPV6)>!(UIP_MAX_ROUTES != 0)######## (NETSTACK_CONF_WITH_IPV6)>!(UIP_MAX_ROUTES != 0)######## 
            #else
            

                // ??????????????????????????????????
                sprintf(str, ",");  strcat(buf, str);
                // ?????????????????????????????????? 


                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                // SUBSECTION START net{} > routes{} > routingEntries{} ////////
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                sprintf(str, "\"" "routingEntries" "\"" ":" ); strcat(buf, str);  
                sprintf(str, "{"                            ); strcat(buf, str);
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

                    sprintf(str, "\"" "valid" "\"" ":" "false"  ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                    sprintf(str, "\"" "total" "\"" ":" "null"   ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);

                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    // SUBARRAY START net{} > routes{} > routingEntries{} > entries[]
                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    sprintf(str, "\"" "entries" "\"" ":"); strcat(buf, str); ////////
                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    
                        // [[[[[[[[[[[[[[[[]]]]]]]]]]]]]]]]
                        sprintf(str,"["); strcat(buf, str);

                        for (int j = 0; j < NBR_TABLE_CONF_MAX_NEIGHBORS; j++)
                        {
                            
                            // {{{{{{{{{{{{{{{{{}}}}}}}}}}}}}}}}}
                            sprintf(str, "{"); strcat(buf, str);

                                sprintf(str, "\"" "route"    "\"" ":" "null"); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                                sprintf(str, "\"" "via"      "\"" ":" "null"); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                                sprintf(str, "\"" "lifetime" "\"" ":" "null"); strcat(buf, str);    

                            // {{{{{{{{{{{{{{{{{}}}}}}}}}}}}}}}}}
                            sprintf(str, "}"); strcat(buf, str);
                            
                            if (j != (NBR_TABLE_CONF_MAX_NEIGHBORS - 1)) { sprintf(str, "," );  strcat(buf, str); };
                        }

                        sprintf(str, "]"); strcat(buf, str);
                        // [[[[[[[[[[[[[[[[[]]]]]]]]]]]]]]]]]

                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                sprintf(str, "}"); strcat(buf, str); ////////////////
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                // SUBSECTION END net{} > routes{} > routingEntries{}
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

            #endif
            // ######## (NETSTACK_CONF_WITH_IPV6)>!(UIP_MAX_ROUTES != 0)######## (NETSTACK_CONF_WITH_IPV6)>!(UIP_MAX_ROUTES != 0)######## (NETSTACK_CONF_WITH_IPV6)>!(UIP_MAX_ROUTES != 0)######## (NETSTACK_CONF_WITH_IPV6)>!(UIP_MAX_ROUTES != 0)######## 

        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        sprintf(str, "}"); strcat(buf, str);
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // SUBSECTION END net{} > routes{} /
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    // ######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)########
    // ########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!
    #else
        
        sprintf(str, "\"" "ipv6Used" "\"" ":" "false"); strcat(buf, str);    
        
        // ??????????????????????????????????
        sprintf(str, ",");  strcat(buf, str);
        // ?????????????????????????????????? 

        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // SUBSECTION START net{} > ipAddr{} ///////////////////
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        sprintf(str, "\"" "ipAddr" "\"" ":" ); strcat(buf, str);
        sprintf(str, "{"                    ); strcat(buf, str);
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

            sprintf(str,        "\""    "valid"           "\""    ":" "false"   );  strcat(buf, str);    sprintf(str, "," );  strcat(buf, str);

            //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            // SUBARRAY START net{} > ipAddr{} > nodeIpv6addresses[] /////////
            //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            sprintf(str, "\"" "nodeIpv6addresses" "\"" ":"); strcat(buf, str);
            //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  
            
                // [[[[[[[[[[[[[[[[]]]]]]]]]]]]]]]]
                sprintf(str,"["); strcat(buf, str);

                for(int i = 0; i < UIP_DS6_ADDR_NB; i++) 
                {
                    sprintf(str, "\"" "null" "\""); strcat(buf, str);
                        
                    if (i != (UIP_DS6_ADDR_NB - 1)) { sprintf(str, "," );  strcat(buf, str); }
                }

                sprintf(str, "]"); strcat(buf, str);
                // [[[[[[[[[[[[[[[[[]]]]]]]]]]]]]]]]]

            // ??????????????????????????????????
            sprintf(str, ",");  strcat(buf, str);
            // ?????????????????????????????????? 

            sprintf(str,    "\""    "addrIssuedCount"           "\""    ":" "null"  );  strcat(buf, str);

        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        sprintf(str, "}"); strcat(buf, str);
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // SUBSECTION END net{} > ipAddr{} /
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        
        // ??????????????????????????????????
        sprintf(str, ",");  strcat(buf, str);
        // ?????????????????????????????????? 

        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // SUBSECTION START net{} > ipNbr{} ////////////////////
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        sprintf(str, "\"" "ipNbr" "\"" ":"  ); strcat(buf, str);
        sprintf(str, "{"                    ); strcat(buf, str);
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

            sprintf(str,        "\""    "valid"           "\""    ":" "true"   );  strcat(buf, str);    sprintf(str, "," );  strcat(buf, str);

            int oar_json_ip_neighbor_count = 0;

            //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            // SUBARRAY START net{} > ipNeighbors{} > nodeIpv6addresses[] ///
            //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            sprintf(str, "\"" "nodeIpv6neigbors" "\"" ":"); strcat(buf, str);  
            //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

                // [[[[[[[[[[[[[[[[]]]]]]]]]]]]]]]]
                sprintf(str,"["); strcat(buf, str);

                for (int i = 0; i < NBR_TABLE_CONF_MAX_NEIGHBORS; i++)
                {
                    // {{{{{{{{{{{{{{{{{}}}}}}}}}}}}}}}}}
                    sprintf(str, "{"); strcat(buf, str);

                        sprintf(str,    "\""    "ipAddr"    "\""    ":" "null"  ); strcat(buf, str);    sprintf(str, "," );  strcat(buf, str);
                        sprintf(str,    "\""    "llAddr"    "\""    ":" "null"  ); strcat(buf, str);    sprintf(str, "," );  strcat(buf, str);
                        sprintf(str,    "\""    "router"    "\""    ":" "null"  ); strcat(buf, str);    sprintf(str, "," );  strcat(buf, str);
                        sprintf(str,    "\""    "state"     "\""    ":" "null"  ); strcat(buf, str);

                    sprintf(str, "}"); strcat(buf, str);
                    // {{{{{{{{{{{{{{{{{}}}}}}}}}}}}}}}}}

                    if (i != (NBR_TABLE_CONF_MAX_NEIGHBORS - 1)) { sprintf(str, "," );  strcat(buf, str); };
                }

                sprintf(str, "]"); strcat(buf, str);
                // [[[[[[[[[[[[[[[[[]]]]]]]]]]]]]]]]]  
            
            // ??????????????????????????????????
            sprintf(str, ",");  strcat(buf, str);
            // ?????????????????????????????????? 

            sprintf(str,    "\""    "ipNbrCount"    "\""    ":" "%u"    ,oar_json_ip_neighbor_count );  strcat(buf, str); 




        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        sprintf(str, "}"); strcat(buf, str);
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // SUBSECTION END net{} > ipNbr{} //
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

        // ??????????????????????????????????
        sprintf(str, ",");  strcat(buf, str);
        // ?????????????????????????????????? 

        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // SUBSECTION START net{} > routes{} ///////////////////
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        sprintf(str, "\"" "routes" "\"" ":" ); strcat(buf, str);
        sprintf(str, "{"                    ); strcat(buf, str);
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

            sprintf(str, "\"" "valid"           "\"" ":"        "false"     ); strcat(buf, str);   sprintf(str, "," ); strcat(buf, str);

            sprintf(str, "\"" "defaultRoute"    "\"" ":"        "null"      ); strcat(buf, str);   sprintf(str, "," ); strcat(buf, str);
            sprintf(str, "\"" "lifetimeSeconds" "\"" ":"        "null"      ); strcat(buf, str);   


            // ########!(NETSTACK_CONF_WITH_IPV6)> (UIP_CONF_IPV6_RPL)########!(NETSTACK_CONF_WITH_IPV6)> (UIP_CONF_IPV6_RPL)########!(NETSTACK_CONF_WITH_IPV6)> (UIP_CONF_IPV6_RPL)########!(NETSTACK_CONF_WITH_IPV6)> (UIP_CONF_IPV6_RPL)######## 
            #if (UIP_CONF_IPV6_RPL)

                // ??????????????????????????????????
                sprintf(str, ",");  strcat(buf, str);
                // ?????????????????????????????????? 

                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                // SUBSECTION START net{} > routes{} > routingLinks{} //////////
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                sprintf(str, "\"" "routingLinks" "\"" ":"   ); strcat(buf, str);  
                sprintf(str, "{"                            ); strcat(buf, str);
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

                    sprintf(str,    "\""    "valid"           "\""    ":" "false"   );  strcat(buf, str);    sprintf(str, "," );  strcat(buf, str);

                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    // SUBARRAY START net{} > routes{} > routingLinks{} > links[]
                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    sprintf(str, "\"" "links" "\"" ":"); strcat(buf, str); //////
                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    
                        // [[[[[[[[[[[[[[[[]]]]]]]]]]]]]]]]
                        sprintf(str,"["); strcat(buf, str);


                        for (int j = 0; j < NBR_TABLE_CONF_MAX_NEIGHBORS; j++)
                        {
                            
                            sprintf(str,    "\""    "null"    "\""  ); strcat(buf, str);
                            
                            if (j != (NBR_TABLE_CONF_MAX_NEIGHBORS - 1)) { sprintf(str, "," );  strcat(buf, str); };
                        }
                        
                        sprintf(str, "]"); strcat(buf, str);
                        // [[[[[[[[[[[[[[[[[]]]]]]]]]]]]]]]]]  

                    sprintf(str,    "\""    "uipSrLinkCount"    "\""    ":"    "null"  );  strcat(buf, str); 

                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                sprintf(str, "}"); strcat(buf, str); //////////////
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                // SUBSECTION END net{} > routes{} > routingLinks{}
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

            // ########!(NETSTACK_CONF_WITH_IPV6)> (UIP_CONF_IPV6_RPL)########!(NETSTACK_CONF_WITH_IPV6)> (UIP_CONF_IPV6_RPL)########!(NETSTACK_CONF_WITH_IPV6)> (UIP_CONF_IPV6_RPL)########!(NETSTACK_CONF_WITH_IPV6)> (UIP_CONF_IPV6_RPL)######## 
            // ########!(NETSTACK_CONF_WITH_IPV6)>!(UIP_CONF_IPV6_RPL)########!(NETSTACK_CONF_WITH_IPV6)>!(UIP_CONF_IPV6_RPL)########!(NETSTACK_CONF_WITH_IPV6)>!(UIP_CONF_IPV6_RPL)########!(NETSTACK_CONF_WITH_IPV6)>!(UIP_CONF_IPV6_RPL)######## 
            #else
            
                // ??????????????????????????????????
                sprintf(str, ",");  strcat(buf, str);
                // ?????????????????????????????????? 

                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                // SUBSECTION START net{} > routes{} > routingLinks{} //////////
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                sprintf(str, "\"" "routingLinks" "\"" ":"   ); strcat(buf, str);  
                sprintf(str, "{"                            ); strcat(buf, str);
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

                 sprintf(str,    "\""    "valid"           "\""    ":" "false"   );  strcat(buf, str);    sprintf(str, "," );  strcat(buf, str);

                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    // SUBARRAY START net{} > routes{} > routingLinks{} > links[]
                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    sprintf(str, "\"" "links" "\"" ":"); strcat(buf, str); //////
                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    
                        // [[[[[[[[[[[[[[[[]]]]]]]]]]]]]]]]
                        sprintf(str,"["); strcat(buf, str);


                        for (int j = 0; j < NBR_TABLE_CONF_MAX_NEIGHBORS; j++)
                        {
                            
                            sprintf(str,    "\""    "null"    "\""  ); strcat(buf, str);
                            
                            if (j != (NBR_TABLE_CONF_MAX_NEIGHBORS - 1)) { sprintf(str, "," );  strcat(buf, str); };
                        }
                        
                        sprintf(str, "]"); strcat(buf, str);
                        // [[[[[[[[[[[[[[[[[]]]]]]]]]]]]]]]]]  

                    sprintf(str,    "\""    "uipSrLinkCount"    "\""    ":"    "null"  );  strcat(buf, str); 

                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                sprintf(str, "}"); strcat(buf, str); //////////////
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                // SUBSECTION END net{} > routes{} > routingLinks{}
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

            #endif 
            // ########!(NETSTACK_CONF_WITH_IPV6)>!(UIP_CONF_IPV6_RPL)########!(NETSTACK_CONF_WITH_IPV6)>!(UIP_CONF_IPV6_RPL)########!(NETSTACK_CONF_WITH_IPV6)>!(UIP_CONF_IPV6_RPL)########!(NETSTACK_CONF_WITH_IPV6)>!(UIP_CONF_IPV6_RPL)######## 

            // ########!(NETSTACK_CONF_WITH_IPV6)> (UIP_MAX_ROUTES != 0)########!(NETSTACK_CONF_WITH_IPV6)> (UIP_MAX_ROUTES != 0)########!(NETSTACK_CONF_WITH_IPV6)> (UIP_MAX_ROUTES != 0)########!(NETSTACK_CONF_WITH_IPV6)> (UIP_MAX_ROUTES != 0)########! 
            #if (UIP_MAX_ROUTES != 0)

                // ??????????????????????????????????
                sprintf(str, ",");  strcat(buf, str);
                // ?????????????????????????????????? 

                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                // SUBSECTION START net{} > routes{} > routingEntries{} ////////
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                sprintf(str, "\"" "routingEntries" "\"" ":" ); strcat(buf, str);  
                sprintf(str, "{"                            ); strcat(buf, str);
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

                    sprintf(str,    "\""    "valid" "\""    ":" "false" ); strcat(buf, str);    sprintf(str, "," );  strcat(buf, str);
                    sprintf(str,    "\""    "total" "\""    ":" "null"  ); strcat(buf, str);    sprintf(str, "," );  strcat(buf, str);

                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    // SUBARRY START net{} > routes{} > routingEntries{} > entries[]
                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    sprintf(str, "\"" "entries" "\"" ":"); strcat(buf, str); ///////
                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ 
                    
                        // [[[[[[[[[[[[[[[[]]]]]]]]]]]]]]]]
                        sprintf(str,"["); strcat(buf, str);
                                

                        for (int j = 0; j < NBR_TABLE_CONF_MAX_NEIGHBORS; j++)
                        {
                            
                            sprintf(str,    "{" );  strcat(buf, str);

                            sprintf(str,    "\""    "route"     "\""    ":" "null"  ); strcat(buf, str);    sprintf(str, "," );  strcat(buf, str);
                            sprintf(str,    "\""    "via"       "\""    ":" "null"  ); strcat(buf, str);    sprintf(str, "," );  strcat(buf, str);
                            sprintf(str,    "\""    "lifetime"  "\""    ":" "null"  ); strcat(buf, str);    // sprintf(str, "," );  strcat(buf, str);

                            sprintf(str,    "}" );  strcat(buf, str);
                            
                            if (j != (NBR_TABLE_CONF_MAX_NEIGHBORS - 1)) { sprintf(str, "," );  strcat(buf, str); };
                        }

                        sprintf(str, "]"); strcat(buf, str);
                        // [[[[[[[[[[[[[[[[[]]]]]]]]]]]]]]]]]  

                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                sprintf(str, "}"); strcat(buf, str); ////////////////
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                // SUBSECTION END net{} > routes{} > routingEntries{}
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

            // ########!(NETSTACK_CONF_WITH_IPV6)> (UIP_MAX_ROUTES != 0)########!(NETSTACK_CONF_WITH_IPV6)> (UIP_MAX_ROUTES != 0)########!(NETSTACK_CONF_WITH_IPV6)> (UIP_MAX_ROUTES != 0)########!(NETSTACK_CONF_WITH_IPV6)> (UIP_MAX_ROUTES != 0)########! 
            // ########!(NETSTACK_CONF_WITH_IPV6)>!(UIP_MAX_ROUTES != 0)########!(NETSTACK_CONF_WITH_IPV6)>!(UIP_MAX_ROUTES != 0)########!(NETSTACK_CONF_WITH_IPV6)>!(UIP_MAX_ROUTES != 0)########!(NETSTACK_CONF_WITH_IPV6)>!(UIP_MAX_ROUTES != 0)########! 
            #else

                // ??????????????????????????????????
                sprintf(str, ",");  strcat(buf, str);
                // ?????????????????????????????????? 

                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                // SUBSECTION START net{} > routes{} > routingEntries{} ////////
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                sprintf(str, "\"" "routingEntries" "\"" ":" ); strcat(buf, str);  
                sprintf(str, "{"                            ); strcat(buf, str);
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

                    sprintf(str,    "\""    "valid" "\""    ":" "false"   );  strcat(buf, str);    sprintf(str, "," );  strcat(buf, str);

                    sprintf(str,    "\""    "total" "\""    ":" "null"  );  strcat(buf, str);   sprintf(str, "," );  strcat(buf, str);

                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    // SUBARRY START net{} > routes{} > routingEntries{} > entries[]
                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    sprintf(str, "\"" "entries" "\"" ":"); strcat(buf, str); ///////
                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    
                     // [[[[[[[[[[[[[[[[]]]]]]]]]]]]]]]]
                    sprintf(str,"["); strcat(buf, str);       

                    for (int j = 0; j < NBR_TABLE_CONF_MAX_NEIGHBORS; j++)
                    {
                        
                        // {{{{{{{{{{{{{{{{{}}}}}}}}}}}}}}}}}
                        sprintf(str, "{"); strcat(buf, str);

                            sprintf(str, "\"" "route"       "\"" ":" "null"); strcat(buf, str); sprintf(str, ","); strcat(buf, str);
                            sprintf(str, "\"" "via"         "\"" ":" "null"); strcat(buf, str); sprintf(str, ","); strcat(buf, str);
                            sprintf(str, "\"" "lifetime"    "\"" ":" "null"); strcat(buf, str); 

                        sprintf(str, "}"); strcat(buf, str);
                        // {{{{{{{{{{{{{{{{{}}}}}}}}}}}}}}}}}
                        
                        if (j != (NBR_TABLE_CONF_MAX_NEIGHBORS - 1)) { sprintf(str, "," );  strcat(buf, str); };
                    }

                    sprintf(str, "]"); strcat(buf, str);
                    // [[[[[[[[[[[[[[[[[]]]]]]]]]]]]]]]]]  


                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                sprintf(str, "}"); strcat(buf, str); ////////////////
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                // SUBSECTION END net{} > routes{} > routingEntries{}
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

            #endif 
            // ########!(NETSTACK_CONF_WITH_IPV6)>!(UIP_MAX_ROUTES != 0)########!(NETSTACK_CONF_WITH_IPV6)>!(UIP_MAX_ROUTES != 0)########!(NETSTACK_CONF_WITH_IPV6)>!(UIP_MAX_ROUTES != 0)########!(NETSTACK_CONF_WITH_IPV6)>!(UIP_MAX_ROUTES != 0)########! 
            
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        sprintf(str, "}"); strcat(buf, str);
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // SUBSECTION END net{} > routes{} /
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        
    #endif
    // ########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    sprintf(str, "}"); strcat(buf, str);
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // SECTION END net{} ///////////////
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
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









