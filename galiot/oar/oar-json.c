////////////////////////
// galiot (2018/2019) //
////////////////////////

#include "oar-json.h"
#include "project-conf.h"

#include "contiki.h"
#include "contiki-net.h"
#include "sys/node-id.h"
#include "sys/platform.h"
#include "sys/energest.h"
#include "sys/stack-check.h"
#include "dev/watchdog.h"

#include "net/link-stats.h"

#include "oar-hash.h"
















// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
// STATIC FUNCTIONS (which needed to be copied)  >>>>> BELOW <<<<< ////////////////////////////////////////////////////
// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::



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
    // FROM os/net/routing/rpl-neighbor.h /////////////////////////////////////////
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
    // FROM os/net/routing/rpl-neighbor.h /////////////////////////////////////////
    // ----------------------------------------------------------------------------

    static int acceptable_rank(rpl_rank_t rank)
    {
        return rank != RPL_INFINITE_RANK
            && rank >= ROOT_RANK
            && rank <= max_acceptable_rank();
    }

    // ----------------------------------------------------------------------------
    // FROM os/net/routing/rpl-neighbor.h /////////////////////////////////////////
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

            // ######## (UIP_ND6_SEND_NS) ######## (UIP_ND6_SEND_NS) ######## (UIP_ND6_SEND_NS) ######## (UIP_ND6_SEND_NS) ######## (UIP_ND6_SEND_NS) ######## (UIP_ND6_SEND_NS) ######## (UIP_ND6_SEND_NS) ######## (UIP_ND6_SEND_NS)
            #if (UIP_ND6_SEND_NS)
            {
                uip_ds6_nbr_t *ds6_nbr = rpl_get_ds6_nbr(nbr);
                
                if(ds6_nbr == NULL || ds6_nbr->state != NBR_REACHABLE)  // Exclude links to a neighbor that is not reachable at a NUD level
                {
                    continue;
                }
            }
            #endif
            // ######## (UIP_ND6_SEND_NS) ######## (UIP_ND6_SEND_NS) ######## (UIP_ND6_SEND_NS) ######## (UIP_ND6_SEND_NS) ######## (UIP_ND6_SEND_NS) ######## (UIP_ND6_SEND_NS) ######## (UIP_ND6_SEND_NS) ######## (UIP_ND6_SEND_NS)

            /* Now we have an acceptable parent, check if it is the new best */
            best = curr_instance.of->best_parent(best, nbr);
        }

        return best;
    }

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

// ######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)########
#if (NETSTACK_CONF_WITH_IPV6)

    //----------------------------------------------------------------------------
    // function that provides context for ds6 neighbor state //////////////////////
    //----------------------------------------------------------------------------

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
    // function that provides context for RPL directed acyclic graph (DAG) state //
    // ----------------------------------------------------------------------------

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
    // function that provides context for RPL mode of operation (MOP) state ///////
    // ----------------------------------------------------------------------------
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
    // function that provides context for RPL objective code point (OCP) //////////
    // ----------------------------------------------------------------------------

    static const char *oar_json_rpl_ocp_to_str(int ocp)
    {
        switch(ocp) 
        {
            case RPL_OCP_OF0: return "OF0";
            case RPL_OCP_MRHOF: return "MRHOF";
            default: return "Unknown";
        }
    }

#endif //(ROUTING_CONF_RPL_LITE)
// ######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)########
















// ()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()
// HELPER FUNCTIONS  >>>>> BELOW <<<<< ////////////////////////////////////////////////////////////////////////////////
// ()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()

// ######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)########
#if (NETSTACK_CONF_WITH_IPV6)

    ///////////////////////////////////
    // IPADDR ---> STR ////////////////
    ///////////////////////////////////

    static void oar_json_ipaddr_to_str(char *output, const uip_ipaddr_t *ipaddr) 
    {
        char buf[UIPLIB_IPV6_MAX_STR_LEN];  // UIPLIB_IPV6_MAX_STR_LEN == 40
        
        memset(output, 0, sizeof(output));  // initialization of outpout string
        uiplib_ipaddr_snprint(buf, sizeof(buf), ipaddr);    // function that creates string from ipaddr

        strcpy(output, buf);    // cannot return string, local scope
    }


#endif //(NETSTACK_CONF_WITH_IPV6)
// ######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)########

///////////////////////////////////
// LLADDR ---> STR ////////////////
///////////////////////////////////

void oar_json_lladdr_to_str(char *output, const linkaddr_t *lladdr) 
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

// ######## (ENERGEST_CONF_ON)######## (ENERGEST_CONF_ON)######## (ENERGEST_CONF_ON)######## (ENERGEST_CONF_ON)######## (ENERGEST_CONF_ON)######## (ENERGEST_CONF_ON)######## (ENERGEST_CONF_ON)######## (ENERGEST_CONF_ON)######## (ENERGEST_CONF_ON)
#if (ENERGEST_CONF_ON)

    static unsigned long oar_json_to_seconds(uint64_t time)
    {
        return (unsigned long)(time / ENERGEST_SECOND);
    }

#endif
















// ====================================================================================================================
// DECLARATIONS ///////////////////////////////////////////////////////////////////////////////////////////////////////
// ====================================================================================================================

void oar_json_print(char * buf)
{
    printf("%s\n", buf);
}

// ######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)########
#if (NETSTACK_CONF_WITH_IPV6)

     static char oar_json_ipaddr[UIPLIB_IPV6_MAX_STR_LEN];

#endif //(NETSTACK_CONF_WITH_IPV6)
// ######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)########
    
char oar_json_lladdr[UIPLIB_IPV6_MAX_STR_LEN];
















// ====================================================================================================================
// MEMORY OVERFLOW PROTECTION /////////////////////////////////////////////////////////////////////////////////////////
// ====================================================================================================================

// ----------------------------------------------------------------------------
// function that initializes (empties) the json string ////////////////////////
// and sends just the pckt section with error appended //////////////////////// 
// ----------------------------------------------------------------------------

// {
// 	"pckt": {
// 		"valid": false,
// 		"error": {
// 			"text": "JSON SEGFUALT",
// 			"code": 604
// 		}
//  },
// 	"id": {
// 		"sT": 77,
// 		"adr": "0012.4b00.0f83.b601",
//      "cd": "RED"
// 	}
// }

static int seguard(char *buf, char *str)
{   
    if (strlen(buf) + strlen(str) > OAR_CONF_JSON_BUF_SIZE)
    {
        char str[128];

        // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        // SECTION START pckt{} ////////////////////////////////
        // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        sprintf(str, "{"                    ); strcpy(buf, str);   // carefull, there is a strcpy() here, resets json
        sprintf(str, "\"" "pckt" "\"" ":"   ); strcat(buf, str);
        sprintf(str, "{"                    ); strcat(buf, str);
        // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

            sprintf(str,        "\"" "vld"    "\"" ":"        "false"                                                         ); strcat(buf, str);

            // ?????????????????????????????????
            sprintf(str, ","); strcat(buf, str);
            // ?????????????????????????????????
        
            // -/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-
            // SUBSECTION START pckt{} > error{} ///////////////////
            // -/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-
            sprintf(str, "\"" "err" "\"" ":"    ); strcat(buf, str);
            sprintf(str, "{"                    ); strcat(buf, str);
            // -/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-

                sprintf(str,    "\"" "txt"     "\"" ":" "\""   "JSON SEGFUALT" "\""    ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                sprintf(str,    "\"" "cd"      "\"" ":"        "604"                                                           ); strcat(buf, str);    

            // -/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/
            sprintf(str, "}"); strcat(buf, str); //
            // -/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/
            // SUBSECTION END pckt{} > error{} ////
            // -/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/

        // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        sprintf(str, "}" ); strcat(buf, str);
        // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        // SECTION END pckt{} ///////////////
        // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

        // ?????????????????????????????????
        sprintf(str, ","); strcat(buf, str);
        // ?????????????????????????????????

        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // SECTION START id{} //////////////////////////////////
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        sprintf(str, "\"" "id" "\"" ":" ); strcat(buf, str); ///
        sprintf(str, "{"                ); strcat(buf, str); ///
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        
            // ttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttt
            sprintf(str,    "\"" "sT"       "\"" ":"            "%lu"                       ,clock_seconds()  ); strcat(buf, str);  sprintf(str, ","); strcat(buf, str);
            // ttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttt

            oar_json_lladdr_to_str(oar_json_lladdr, &linkaddr_node_addr);
            
            sprintf(str,    "\"" "adr"      "\"" ":" "\""    "%s"                   "\""    ,oar_json_lladdr    ); strcat(buf, str);  sprintf(str, ","); strcat(buf, str);
            sprintf(str,    "\"" "cd"       "\"" ":" "\""    OAR_CONF_MOTE_COLOR    "\""                        ); strcat(buf, str);
        
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        sprintf(str, "}" ); strcat(buf, str); //
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // SECTION END id{} ////////////////////
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

        // ?????????????????????????????????
        sprintf(str, ","); strcat(buf, str);
        // ?????????????????????????????????

        sprintf(str,    "\"" "hash"         "\"" ":" "\""    "%u"                   "\""    ,oar_sdbm(buf)    ); strcat(buf, str);
        
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        sprintf(str, "}" ); strcat(buf, str); //
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

        return 1;
    }
    else
    {
        return 0;
    }
}
















// ####################################################################################################################
// MAIN FUNCTIONS >>>>> BELOW <<<<< ///////////////////////////////////////////////////////////////////////////////////
// ####################################################################################################################

// ----------------------------------------------------------------------------
// function that initializes (empties) the json string ////////////////////////
// ----------------------------------------------------------------------------

static void oar_json_init(char * buf)
{
    memset(buf, 0, sizeof(buf));        // initialization
}

// ----------------------------------------------------------------------------
// function that appends the entry '{' json character to the string ///////////
// ----------------------------------------------------------------------------
static int oar_json_enter(char * buf)
{
    char str[128];
    sprintf(str,    "{" );  if(seguard(buf, str)){return 1;} strcat(buf, str);

    return 0;
}

// ----------------------------------------------------------------------------
// function that connects the sections og the json, appending and ',' char ////
// ----------------------------------------------------------------------------

int oar_json_bridge(char * buf)
{
    char str[128];
    sprintf(str,    "," );  if(seguard(buf, str)){return 1;} strcat(buf, str);
    
    return 0;
}

// ----------------------------------------------------------------------------
// function that appends the exit '}' json character to the string ////////////
// ----------------------------------------------------------------------------

static int oar_json_exit(char * buf)
{
    char str[128];
    sprintf(str,    "}" );  if(seguard(buf, str)){return 1;} strcat(buf, str);

    return 0;
}
















// ####################################################################################################################
// MAIN FUNCTIONS >>>>> CONTINUE <<<<< ////////////////////////////////////////////////////////////////////////////////
// ####################################################################################################################

// ----------------------------------------------------------------------------
// function that appends ID section to the json string ////////////////////////
// ----------------------------------------------------------------------------

static int oar_json_append_id(char * buf)
{
    char str[128];

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // SECTION START id{} ///////////////////////////////////////////////////////////////////////
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    sprintf(str, "\"" "id" "\"" ":" ); if(seguard(buf, str)){return 1;} strcat(buf, str); ///////
    sprintf(str, "{"                ); if(seguard(buf, str)){return 1;} strcat(buf, str); ///////
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    
        // ttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttt
        sprintf(str, "\"" "sT"  "\"" ":" "%lu" ,clock_seconds()); if(seguard(buf, str)){return 1;} strcat(buf, str); sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str);
        // ttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttt

        oar_json_lladdr_to_str(oar_json_lladdr, &linkaddr_node_addr);
        
        sprintf(str,        "\""    "adr"   "\""    ":" "\""    "%s"                        "\""        ,oar_json_lladdr    );  if(seguard(buf, str)){return 1;} strcat(buf, str);  sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str);
        sprintf(str,        "\""    "cd"    "\""    ":" "\""    OAR_CONF_MOTE_COLOR         "\""                            );  if(seguard(buf, str)){return 1;} strcat(buf, str);
    
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    sprintf(str, "}" ); if(seguard(buf, str)){return 1;} strcat(buf, str); //
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // SECTION END id{} /////////////////////////////////////////////////////
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    return 0;
}
















// ####################################################################################################################
// MAIN FUNCTIONS >>>>> CONTINUE <<<<< ////////////////////////////////////////////////////////////////////////////////
// ####################################################################################################################

// -----------------------------------------------------------------------------
// function that appends SYS section to the json string ////////////////////////
// -----------------------------------------------------------------------------

// {
// 	"pckt": {
// 		"vld": true,
// 		"err": null
// 	},
// 	"qId": 0,
// 	"id": {
// 		"sT": 133,
// 		"adr": "0012.4b00.0f83.b601"
// 	},
// 	"sys": {
// 		"cV": "Contiki-NG-release/v4.2-305-g256e7c776-dirty",
// 		"rt": "RPL Lite",
// 		"net": "sicslowpan",
// 		"pId": "0xabcd",
// 		"sys": {
// 			"t": "CSMA",
// 			"tDhS": null,
// 			"dCh": 26
// 		},
// 		"nId": 46593,
// 		"tIad": "fe80::212:4b00:f83:b601"
// 	},
// 	"hash": 1623731441
// }

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

static int oar_json_append_sys(char * buf)
{
    char str[128];

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // SECTION START sys{} //////////////////////////////////////////////////////////////////////
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    sprintf(str, "\"" "sys" "\"" ":"    ); if(seguard(buf, str)){return 1;} strcat(buf, str); ///
    sprintf(str, "{"                    ); if(seguard(buf, str)){return 1;} strcat(buf, str); ///
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

        sprintf(str,        "\"" "cV"   "\"" ":" "\""   CONTIKI_VERSION_STRING  "\""                                                        ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str);
        sprintf(str,        "\"" "rt"   "\"" ":" "\""   "%s"                    "\""    ,NETSTACK_ROUTING.name                              ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str);
        sprintf(str,        "\"" "net"  "\"" ":" "\""   "%s"                    "\""    ,NETSTACK_NETWORK.name                              ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str);
        sprintf(str,        "\"" "pId"  "\"" ":" "\""   "0x%04x"                "\""    ,IEEE802154_CONF_PANID                              ); if(seguard(buf, str)){return 1;} strcat(buf, str);    // sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str);
        
        // ???????????????????????????????????????????????????????????????????
        sprintf(str, ",");  if(seguard(buf, str)){return 1;} strcat(buf, str);
        // ???????????????????????????????????????????????????????????????????
        
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // SUBSECTION START sys{} > mac{} ///////////////////////////////////////////////////////////
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        sprintf(str, "\"" "mac" "\"" ":"    ); if(seguard(buf, str)){return 1;} strcat(buf, str); ///
        sprintf(str, "{"                    ); if(seguard(buf, str)){return 1;} strcat(buf, str); ///
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        
            // #########(MAC_CONF_WITH_TSCH)#########(MAC_CONF_WITH_TSCH)#########(MAC_CONF_WITH_TSCH)#########(MAC_CONF_WITH_TSCH)#########(MAC_CONF_WITH_TSCH)#########(MAC_CONF_WITH_TSCH)#########(MAC_CONF_WITH_TSCH)#########
            #if MAC_CONF_WITH_TSCH
            
                sprintf(str,    "\"" "t"    "\"" ":" "\""   "%s"                    "\""    ,NETSTACK_MAC.name                                  ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str);
                sprintf(str,    "\"" "tDhS" "\"" ":"        "%u"                            ,(unsigned)sizeof(TSCH_DEFAULT_HOPPING_SEQUENCE)    ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str);
                sprintf(str,    "\"" "dCh"  "\"" ":"        "null"                                                                              ); if(seguard(buf, str)){return 1;} strcat(buf, str);    
            
            // #########(MAC_CONF_WITH_TSCH)#########(MAC_CONF_WITH_TSCH)#########(MAC_CONF_WITH_TSCH)#########(MAC_CONF_WITH_TSCH)#########(MAC_CONF_WITH_TSCH)#########(MAC_CONF_WITH_TSCH)#########(MAC_CONF_WITH_TSCH)#########
            // ########!(MAC_CONF_WITH_TSCH)########!(MAC_CONF_WITH_TSCH)########!(MAC_CONF_WITH_TSCH)########!(MAC_CONF_WITH_TSCH)########!(MAC_CONF_WITH_TSCH)########!(MAC_CONF_WITH_TSCH)########!(MAC_CONF_WITH_TSCH)########!
            #else
            
                sprintf(str,    "\"" "t"    "\"" ":" "\""   "%s"                    "\""    ,NETSTACK_MAC.name                                  ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str);
                sprintf(str,    "\"" "tDhS" "\"" ":"        "null"                                                                              ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str);
                sprintf(str,    "\"" "dCh"  "\"" ":"        "%u"                            ,IEEE802154_DEFAULT_CHANNEL                         ); if(seguard(buf, str)){return 1;} strcat(buf, str);    
            
            #endif
            // ########!(MAC_CONF_WITH_TSCH)########!(MAC_CONF_WITH_TSCH)########!(MAC_CONF_WITH_TSCH)########!(MAC_CONF_WITH_TSCH)########!(MAC_CONF_WITH_TSCH)########!(MAC_CONF_WITH_TSCH)########!(MAC_CONF_WITH_TSCH)########!

        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        sprintf(str, "}" ); if(seguard(buf, str)){return 1;} strcat(buf, str); //
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // SECTION END id{} > mac{} /////////////////////////////////////////////
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

        // ???????????????????????????????????????????????????????????????????
        sprintf(str, ",");  if(seguard(buf, str)){return 1;} strcat(buf, str);
        // ???????????????????????????????????????????????????????????????????
        
        sprintf(str,        "\"" "nId"   "\"" ":"        "%u"                            ,node_id                                            ); if(seguard(buf, str)){return 1;} strcat(buf, str);   sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str);
                                                                                                                                                                                                    
        // #########(NETSTACK_CONF_WITH_IPV6)#########(NETSTACK_CONF_WITH_IPV6)#########(NETSTACK_CONF_WITH_IPV6)#########(NETSTACK_CONF_WITH_IPV6)#########(NETSTACK_CONF_WITH_IPV6)#########(NETSTACK_CONF_WITH_IPV6)#########
        #if (NETSTACK_CONF_WITH_IPV6)
        
            uip_ds6_addr_t *lladdr;
            
            memcpy(&uip_lladdr.addr, &linkaddr_node_addr, sizeof(uip_lladdr.addr));
            lladdr = uip_ds6_get_link_local(-1);
            
            oar_json_ipaddr_to_str(oar_json_ipaddr, lladdr != NULL ? &lladdr->ipaddr : NULL);
            sprintf(str,    "\"" "tIad" "\"" ":" "\""   "%s"                    "\""    ,oar_json_ipaddr                           ); if(seguard(buf, str)){return 1;} strcat(buf, str);
        
        // #########(NETSTACK_CONF_WITH_IPV6)#########(NETSTACK_CONF_WITH_IPV6)#########(NETSTACK_CONF_WITH_IPV6)#########(NETSTACK_CONF_WITH_IPV6)#########(NETSTACK_CONF_WITH_IPV6)#########(NETSTACK_CONF_WITH_IPV6)#########
        // ########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!
        #else  
        
            sprintf(str,    "\"" "tIadr" "\"" ":"       "null"                                                                              ); if(seguard(buf, str)){return 1;} strcat(buf, str);
        
        #endif
        // ########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!
    
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    sprintf(str, "}" ); if(seguard(buf, str)){return 1;} strcat(buf, str); //
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // SECTION END id{} /////////////////////////////////////////////////////
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    return 0;
}
















// ####################################################################################################################
// MAIN FUNCTIONS >>>>> CONTINUE <<<<< ////////////////////////////////////////////////////////////////////////////////
// ####################################################################################################################

// ----------------------------------------------------------------------------
// function that appends DEVICE section to the json string ////////////////////
// ----------------------------------------------------------------------------

// {
// 	"pckt": {
// 		"vld": true,
// 		"err": null
// 	},
// 	"qId": 1,
// 	"id": {
// 		"sT": 137,
// 		"adr": "0012.4b00.0f83.b601"
// 	},
// 	"dev": {
// 		"tp": 17,
// 		"hd": 91
// 	},
// 	"hash": 3790190472
// }

static int oar_json_append_dev(char * buf)
{
    char str[128];
    
    int temperature = 15 + rand() % 30;
    int humidity = 80 + rand() % 17;

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // SECTION START dev{} //////////////////////////////////////////////////////////////////////
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    sprintf(str, "\"" "dev" "\"" ":"    ); if(seguard(buf, str)){return 1;} strcat(buf, str); ///  
    sprintf(str, "{"                    ); if(seguard(buf, str)){return 1;} strcat(buf, str); ///
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

        sprintf(str, "\"" "tp"  "\"" ":" "%d"  ,temperature );  if(seguard(buf, str)){return 1;} strcat(buf, str); sprintf(str,","); if(seguard(buf, str)){return 1;} strcat(buf, str);
        sprintf(str, "\"" "hd"  "\"" ":" "%d"  ,humidity    );  if(seguard(buf, str)){return 1;} strcat(buf, str); 

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    sprintf(str, "}" ); if(seguard(buf, str)){return 1;} strcat(buf, str); //
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // SECTION END dev{} ////////////////////////////////////////////////////
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


    return 0;
}
















// ####################################################################################################################
// MAIN FUNCTIONS >>>>> CONTINUE <<<<< ////////////////////////////////////////////////////////////////////////////////
// ####################################################################################################################

// ----------------------------------------------------------------------------
// function that appends ENERGY STATISTICS section to the json string /////////
// ----------------------------------------------------------------------------

// {
// 	"pckt": {
// 		"valid": true,
// 		"error": null
// 	},
// 	"qId": 2,
// 	"id": {
// 		"sT": 19,
// 		"adr": "0012.4b00.0f83.b601"
// 	},
// 	"nrg": {
// 		"en": true,
// 		"cp": 0,
// 		"lp": 18,
// 		"dL": 0,
// 		"tT": 19,
// 		"rL": 19,
// 		"rT": 0,
// 		"rO": 0
// 	},
// 	"hash": 3790190472
// }

// ENERGEST_TYPE_CPU	    The CPU is active.                  CPU
// ENERGEST_TYPE_LPM	    The CPU is in low power mode.       LPM
// ENERGEST_TYPE_DEEP_LPM	The CPU is in deep low power mode.  DEEP LPM
//                                                              TOTAL TIME
// ENERGEST_TYPE_LISTEN	    The radio is listening.             RADIO LISTEN 
// ENERGEST_TYPE_TRANSMIT	The radio is transmitting.          RADIO TRANSMIT
//                                                              RADIO OFF
   
static int oar_json_append_nrg(char * buf)
{
    char str[128];

    // #########(ENERGEST_CONF_ON)#########(ENERGEST_CONF_ON)#########(ENERGEST_CONF_ON)#########(ENERGEST_CONF_ON)#########(ENERGEST_CONF_ON)#########(ENERGEST_CONF_ON)#########(ENERGEST_CONF_ON)#########
    #if (ENERGEST_CONF_ON)

        energest_flush();       // Update all energest times.
        
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // SECTION START nrg{} //////////////////////////////////////////////////////////////////////
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        sprintf(str, "\"" "nrg" "\"" ":"    ); if(seguard(buf, str)){return 1;} strcat(buf, str); ///  
        sprintf(str, "{"                    ); if(seguard(buf, str)){return 1;} strcat(buf, str); ///
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

            sprintf(str, "\"" "en"  "\"" ":" "true"                                                                                                                                                    );  if(seguard(buf, str)){return 1;} strcat(buf, str); sprintf(str,","); if(seguard(buf, str)){return 1;} strcat(buf, str);

            sprintf(str, "\"" "cp"  "\"" ":" "%lu"  ,oar_json_to_seconds(energest_type_time(ENERGEST_TYPE_CPU))                                                                              );  if(seguard(buf, str)){return 1;} strcat(buf, str); sprintf(str,","); if(seguard(buf, str)){return 1;} strcat(buf, str);
            sprintf(str, "\"" "lp"  "\"" ":" "%lu"  ,oar_json_to_seconds(energest_type_time(ENERGEST_TYPE_LPM))                                                                              );  if(seguard(buf, str)){return 1;} strcat(buf, str); sprintf(str,","); if(seguard(buf, str)){return 1;} strcat(buf, str);
            sprintf(str, "\"" "dL"  "\"" ":" "%lu"  ,oar_json_to_seconds(energest_type_time(ENERGEST_TYPE_DEEP_LPM))                                                                         );  if(seguard(buf, str)){return 1;} strcat(buf, str); sprintf(str,","); if(seguard(buf, str)){return 1;} strcat(buf, str);
            sprintf(str, "\"" "tT"  "\"" ":" "%lu"  ,oar_json_to_seconds(ENERGEST_GET_TOTAL_TIME())                                                                                          );  if(seguard(buf, str)){return 1;} strcat(buf, str); sprintf(str,","); if(seguard(buf, str)){return 1;} strcat(buf, str);
            sprintf(str, "\"" "rL"  "\"" ":" "%lu"  ,oar_json_to_seconds(energest_type_time(ENERGEST_TYPE_LISTEN))                                                                           );  if(seguard(buf, str)){return 1;} strcat(buf, str); sprintf(str,","); if(seguard(buf, str)){return 1;} strcat(buf, str);
            sprintf(str, "\"" "rT"  "\"" ":" "%lu"  ,oar_json_to_seconds(energest_type_time(ENERGEST_TYPE_TRANSMIT))                                                                         );  if(seguard(buf, str)){return 1;} strcat(buf, str); sprintf(str,","); if(seguard(buf, str)){return 1;} strcat(buf, str);
            sprintf(str, "\"" "rO"  "\"" ":" "%lu"  ,oar_json_to_seconds(ENERGEST_GET_TOTAL_TIME() - energest_type_time(ENERGEST_TYPE_TRANSMIT) - energest_type_time(ENERGEST_TYPE_LISTEN))  );  if(seguard(buf, str)){return 1;} strcat(buf, str); 
            
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        sprintf(str, "}" ); if(seguard(buf, str)){return 1;} strcat(buf, str);
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // SECTION END mrg{} ////////////////
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    // #########(ENERGEST_CONF_ON)#########(ENERGEST_CONF_ON)#########(ENERGEST_CONF_ON)#########(ENERGEST_CONF_ON)#########(ENERGEST_CONF_ON)#########(ENERGEST_CONF_ON)#########(ENERGEST_CONF_ON)#########
    // ########!(ENERGEST_CONF_ON)########!(ENERGEST_CONF_ON)########!(ENERGEST_CONF_ON)########!(ENERGEST_CONF_ON)########!(ENERGEST_CONF_ON)########!(ENERGEST_CONF_ON)########!(ENERGEST_CONF_ON)########!
    #else
        
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // SECTION START mrg{} //////////////////////////////////////////////////////////////////////
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        sprintf(str, "\"" "nrg" "\"" ":"    ); if(seguard(buf, str)){return 1;} strcat(buf, str); ///
        sprintf(str, "{"                    ); if(seguard(buf, str)){return 1;} strcat(buf, str); ///
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

            sprintf(str, "\"" "en"  "\"" ":" "false"    ); if(seguard(buf, str)){return 1;} strcat(buf, str); sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str);

            sprintf(str, "\"" "cp"  "\"" ":" "null"     ); if(seguard(buf, str)){return 1;} strcat(buf, str); sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str);
            sprintf(str, "\"" "lp"  "\"" ":" "null"     ); if(seguard(buf, str)){return 1;} strcat(buf, str); sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str);
            sprintf(str, "\"" "dL"  "\"" ":" "null"     ); if(seguard(buf, str)){return 1;} strcat(buf, str); sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str);
            sprintf(str, "\"" "tT"  "\"" ":" "null"     ); if(seguard(buf, str)){return 1;} strcat(buf, str); sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str);
            sprintf(str, "\"" "rL"  "\"" ":" "null"     ); if(seguard(buf, str)){return 1;} strcat(buf, str); sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str);
            sprintf(str, "\"" "rT"  "\"" ":" "null"     ); if(seguard(buf, str)){return 1;} strcat(buf, str); sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str);
            sprintf(str, "\"" "rO"  "\"" ":" "null"     ); if(seguard(buf, str)){return 1;} strcat(buf, str);
        
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        sprintf(str, "}" ); if(seguard(buf, str)){return 1;} strcat(buf, str); //
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // SECTION END mrg{} ////////////////////////////////////////////////////
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    #endif
    // ########!(ENERGEST_CONF_ON)########!(ENERGEST_CONF_ON)########!(ENERGEST_CONF_ON)########!(ENERGEST_CONF_ON)########!(ENERGEST_CONF_ON)########!(ENERGEST_CONF_ON)########!(ENERGEST_CONF_ON)########!

    return 0;
}
















// ####################################################################################################################
// MAIN FUNCTIONS >>>>> CONTINUE <<<<< ////////////////////////////////////////////////////////////////////////////////
// ####################################################################################################################

// ----------------------------------------------------------------------------
// function that appends IP STATS section to the json string //////////////////
// ----------------------------------------------------------------------------

// {
// 	"pckt": {
// 		"valid": true,
// 		"error": null
// 	},
// 	"qId": 3,
// 	"id": {
// 		"sT": 21,
// 		"adr": "0012.4b00.0f83.b601"
// 	},
// 	"ipSt": {
// 		"uS": true,
// 		"ip": {
// 			"rx": 30,
// 			"tx": 27,
// 			"fw": 0,
// 			"dr": 0,
// 			"vE": 0,
// 			"hE": 0,
// 			"lE": 0,
// 			"fE": 0,
// 			"cE": 0,
// 			"pE": 0
// 		}
// 	},
// 	"hash": 3790190472
// }

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
 ************************************************************************************/

static int oar_json_append_stats_ip(char * buf)
{
    char str[128];
    
    // ######## (UIP_CONF_STATISTICS)######## (UIP_CONF_STATISTICS)######## (UIP_CONF_STATISTICS)######## (UIP_CONF_STATISTICS)######## (UIP_CONF_STATISTICS)######## (UIP_CONF_STATISTICS)######## (UIP_CONF_STATISTICS)########
    #if (UIP_CONF_STATISTICS)

        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // SECTION START ipSt{} /////////////////////////////////////////////////////////////////////////
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        sprintf(str, "\""   "ipSt"  "\""    ":" ); if(seguard(buf, str)){return 1;} strcat(buf, str); ///
        sprintf(str, "{"                        ); if(seguard(buf, str)){return 1;} strcat(buf, str); ///
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

            sprintf(str, "\"" "uS"  "\"" ":" "true" ); if(seguard(buf, str)){return 1;} strcat(buf, str);

            // ???????????????????????????????????????????????????????????????????
            sprintf(str, ",");  if(seguard(buf, str)){return 1;} strcat(buf, str);
            // ???????????????????????????????????????????????????????????????????

            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            // SUBSECTION START ipSt{} > ip{} ///////////////////////////////////////////////////////////////
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            sprintf(str, "\""   "ip"  "\""    ":"   ); if(seguard(buf, str)){return 1;} strcat(buf, str); ///
            sprintf(str, "{"                        ); if(seguard(buf, str)){return 1;} strcat(buf, str); ///
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~        
                
                sprintf(str, "\"" "rx"  "\"" ":" "%lu" ,uip_stat.ip.recv      ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str);
                sprintf(str, "\"" "tx"  "\"" ":" "%lu" ,uip_stat.ip.sent      ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str);
                sprintf(str, "\"" "fw"  "\"" ":" "%lu" ,uip_stat.ip.forwarded ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str);
                sprintf(str, "\"" "dr"  "\"" ":" "%lu" ,uip_stat.ip.drop      ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str);
                sprintf(str, "\"" "vE"  "\"" ":" "%lu" ,uip_stat.ip.vhlerr    ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str);
                sprintf(str, "\"" "hE"  "\"" ":" "%lu" ,uip_stat.ip.hblenerr  ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str);
                sprintf(str, "\"" "lE"  "\"" ":" "%lu" ,uip_stat.ip.lblenerr  ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str);
                sprintf(str, "\"" "fE"  "\"" ":" "%lu" ,uip_stat.ip.fragerr   ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str);
                sprintf(str, "\"" "cE"  "\"" ":" "%lu" ,uip_stat.ip.chkerr    ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str);
                sprintf(str, "\"" "pE"  "\"" ":" "%lu" ,uip_stat.ip.protoerr  ); if(seguard(buf, str)){return 1;} strcat(buf, str);

            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            sprintf(str, "}"); if(seguard(buf, str)){return 1;} strcat(buf, str); ///
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            // SECTION END ipSt{} > ip{} ////////////////////////////////////////////
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                                                                                                                                                                                
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        sprintf(str, "}"); if(seguard(buf, str)){return 1;} strcat(buf, str);
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // SECTION END ipSt{} //////////////
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    // ######## (UIP_CONF_STATISTICS)######## (UIP_CONF_STATISTICS)######## (UIP_CONF_STATISTICS)######## (UIP_CONF_STATISTICS)######## (UIP_CONF_STATISTICS)######## (UIP_CONF_STATISTICS)######## (UIP_CONF_STATISTICS)########
    // ########!(UIP_CONF_STATISTICS)########!(UIP_CONF_STATISTICS)########!(UIP_CONF_STATISTICS)########!(UIP_CONF_STATISTICS)########!(UIP_CONF_STATISTICS)########!(UIP_CONF_STATISTICS)########!(UIP_CONF_STATISTICS)########!
    #else

        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // SECTION START ipSt{} /////////////////////////////////////////////////////////////////////////
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        sprintf(str, "\""   "ipSt"  "\""    ":" ); if(seguard(buf, str)){return 1;} strcat(buf, str); ///
        sprintf(str, "{"                        ); if(seguard(buf, str)){return 1;} strcat(buf, str); ///
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

            sprintf(str, "\"" "uS"  "\"" ":" "false" ); if(seguard(buf, str)){return 1;} strcat(buf, str);

            // ???????????????????????????????????????????????????????????????????
            sprintf(str, ",");  if(seguard(buf, str)){return 1;} strcat(buf, str);
            // ???????????????????????????????????????????????????????????????????

            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            // SUBSECTION START ip{} > ipSt{} ///////////////////////////////////////////////////////////////
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            sprintf(str, "\""   "ip"  "\""    ":"   ); if(seguard(buf, str)){return 1;} strcat(buf, str); ///
            sprintf(str, "{"                        ); if(seguard(buf, str)){return 1;} strcat(buf, str); ///
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~       
                
                sprintf(str, "\"" "rx"  "\"" ":" "null"   ); if(seguard(buf, str)){return 1;} strcat(buf, str); sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str);
                sprintf(str, "\"" "tx"  "\"" ":" "null"   ); if(seguard(buf, str)){return 1;} strcat(buf, str); sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str);
                sprintf(str, "\"" "fw"  "\"" ":" "null"   ); if(seguard(buf, str)){return 1;} strcat(buf, str); sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str);
                sprintf(str, "\"" "dr"  "\"" ":" "null"   ); if(seguard(buf, str)){return 1;} strcat(buf, str); sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str);
                sprintf(str, "\"" "vE"  "\"" ":" "null"   ); if(seguard(buf, str)){return 1;} strcat(buf, str); sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str);
                sprintf(str, "\"" "hE"  "\"" ":" "null"   ); if(seguard(buf, str)){return 1;} strcat(buf, str); sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str);
                sprintf(str, "\"" "lE"  "\"" ":" "null"   ); if(seguard(buf, str)){return 1;} strcat(buf, str); sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str);
                sprintf(str, "\"" "fE"  "\"" ":" "null"   ); if(seguard(buf, str)){return 1;} strcat(buf, str); sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str);
                sprintf(str, "\"" "cE"  "\"" ":" "null"   ); if(seguard(buf, str)){return 1;} strcat(buf, str); sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str);
                sprintf(str, "\"" "pE"  "\"" ":" "null"   ); if(seguard(buf, str)){return 1;} strcat(buf, str);

            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            sprintf(str, "}"); if(seguard(buf, str)){return 1;} strcat(buf, str); ///
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            // SECTION END ip{} > ipSt{} ////////////////////////////////////////////
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        sprintf(str, "}"); if(seguard(buf, str)){return 1;} strcat(buf, str); ///
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // SECTION END ipSt{} ///////////////////////////////////////////////////
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    #endif
    // ########!(UIP_CONF_STATISTICS)########!(UIP_CONF_STATISTICS)########!(UIP_CONF_STATISTICS)########!(UIP_CONF_STATISTICS)########!(UIP_CONF_STATISTICS)########!(UIP_CONF_STATISTICS)########!(UIP_CONF_STATISTICS)########!

    return 0;
}
















// ####################################################################################################################
// MAIN FUNCTIONS >>>>> CONTINUE <<<<< ////////////////////////////////////////////////////////////////////////////////
// ####################################################################################################################

// ----------------------------------------------------------------------------
// function that appends ICMP STATS section to the json string ////////////////
// ----------------------------------------------------------------------------

// {
// 	"pckt": {
// 		"valid": true,
// 		"error": null
// 	},
// 	"qId": 4,
// 	"id": {
// 		"sT": 23,
// 		"adr": "0012.4b00.0f83.b601"
// 	},
// 	"icSt": {
// 		"uS": true,
// 		"ic": {
// 			"rx": 4,
// 			"tx": 6,
// 			"dr": 0,
// 			"tE": 0,
// 			"cE": 0
// 		}
// 	},
// 	"hash": 3790190472
// }

/* **********************************************************************************
 *     (icmp.recv) >                                       received ICMP packets    *
 *     (icmp.sent) >                                           sent ICMP packets    *
 *     (icmp.drop) >                                        dropped ICMP packets    *
 *  (icmp.typeerr) >                              ICMP packets with a wrong type    *
 *   (icmp.chkerr) >                            ICMP packets with a bad checksum    *
 ************************************************************************************/

static int oar_json_append_stats_icmp(char * buf)
{
    char str[128];
    
    // ######## (UIP_CONF_STATISTICS)######## (UIP_CONF_STATISTICS)######## (UIP_CONF_STATISTICS)######## (UIP_CONF_STATISTICS)######## (UIP_CONF_STATISTICS)######## (UIP_CONF_STATISTICS)######## (UIP_CONF_STATISTICS)########
    #if (UIP_CONF_STATISTICS)

        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // SECTION START icSt{} /////////////////////////////////////////////////////////////////////////
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        sprintf(str, "\""   "icSt"  "\""    ":" ); if(seguard(buf, str)){return 1;} strcat(buf, str); ///
        sprintf(str, "{"                        ); if(seguard(buf, str)){return 1;} strcat(buf, str); ///
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

            sprintf(str, "\"" "uS"  "\"" ":" "true" ); if(seguard(buf, str)){return 1;} strcat(buf, str);

            // ???????????????????????????????????????????????????????????????????
            sprintf(str, ",");  if(seguard(buf, str)){return 1;} strcat(buf, str);
            // ???????????????????????????????????????????????????????????????????

            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            // SUBSECTION START icSt{} > ic{} ///////////////////////////////////////////////////////////////
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            sprintf(str, "\""   "ic"  "\""    ":"   ); if(seguard(buf, str)){return 1;} strcat(buf, str); ///
            sprintf(str, "{"                        ); if(seguard(buf, str)){return 1;} strcat(buf, str); ///
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

                sprintf(str, "\"" "rx"  "\"" ":" "%lu" ,uip_stat.icmp.recv      ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str);
                sprintf(str, "\"" "tx"  "\"" ":" "%lu" ,uip_stat.icmp.sent      ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str);
                sprintf(str, "\"" "dr"  "\"" ":" "%lu" ,uip_stat.icmp.drop      ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str);
                sprintf(str, "\"" "tE"  "\"" ":" "%lu" ,uip_stat.icmp.typeerr   ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str);
                sprintf(str, "\"" "cE"  "\"" ":" "%lu" ,uip_stat.icmp.chkerr    ); if(seguard(buf, str)){return 1;} strcat(buf, str);               

            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            sprintf(str, "}"); if(seguard(buf, str)){return 1;} strcat(buf, str); ///
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            // SECTION END icSt{} > icmp{} //////////////////////////////////////////
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        sprintf(str, "}"); if(seguard(buf, str)){return 1;} strcat(buf, str); ///
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // SECTION END icSt{} ///////////////////////////////////////////////////
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    // ######## (UIP_CONF_STATISTICS)######## (UIP_CONF_STATISTICS)######## (UIP_CONF_STATISTICS)######## (UIP_CONF_STATISTICS)######## (UIP_CONF_STATISTICS)######## (UIP_CONF_STATISTICS)######## (UIP_CONF_STATISTICS)########
    // ########!(UIP_CONF_STATISTICS)########!(UIP_CONF_STATISTICS)########!(UIP_CONF_STATISTICS)########!(UIP_CONF_STATISTICS)########!(UIP_CONF_STATISTICS)########!(UIP_CONF_STATISTICS)########!(UIP_CONF_STATISTICS)########!
    #else

        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // SECTION START icSt{} /////////////////////////////////////////////////////////////////////////
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        sprintf(str, "\""   "icSt"  "\""    ":" ); if(seguard(buf, str)){return 1;} strcat(buf, str); ///
        sprintf(str, "{"                        ); if(seguard(buf, str)){return 1;} strcat(buf, str); ///
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

            sprintf(str, "\"" "uS"  "\"" ":" "false" ); if(seguard(buf, str)){return 1;} strcat(buf, str);

            // ???????????????????????????????????????????????????????????????????
            sprintf(str, ",");  if(seguard(buf, str)){return 1;} strcat(buf, str);
            // ???????????????????????????????????????????????????????????????????

            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            // SUBSECTION START icSt{} > ic{} ///////////////////////////////////////////////////////////////
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            sprintf(str, "\""   "ic"  "\""    ":"   ); if(seguard(buf, str)){return 1;} strcat(buf, str); ///
            sprintf(str, "{"                        ); if(seguard(buf, str)){return 1;} strcat(buf, str); ///
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

                sprintf(str, "\"" "rx"  "\"" ":" "null"   ); if(seguard(buf, str)){return 1;} strcat(buf, str); sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str);
                sprintf(str, "\"" "tx"  "\"" ":" "null"   ); if(seguard(buf, str)){return 1;} strcat(buf, str); sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str);
                sprintf(str, "\"" "dr"  "\"" ":" "null"   ); if(seguard(buf, str)){return 1;} strcat(buf, str); sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str);
                sprintf(str, "\"" "tE"  "\"" ":" "null"   ); if(seguard(buf, str)){return 1;} strcat(buf, str); sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str);
                sprintf(str, "\"" "cE"  "\"" ":" "null"   ); if(seguard(buf, str)){return 1;} strcat(buf, str); sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str);

            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            sprintf(str, "}"); if(seguard(buf, str)){return 1;} strcat(buf, str); ///
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            // SECTION END icSt{} > ic{} ////////////////////////////////////////////
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        sprintf(str, "}"); if(seguard(buf, str)){return 1;} strcat(buf, str); ///
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // SECTION END icSt{} ///////////////////////////////////////////////////
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    #endif
    // ########!(UIP_CONF_STATISTICS)########!(UIP_CONF_STATISTICS)########!(UIP_CONF_STATISTICS)########!(UIP_CONF_STATISTICS)########!(UIP_CONF_STATISTICS)########!(UIP_CONF_STATISTICS)########!(UIP_CONF_STATISTICS)########!

    return 0;
}
















// ####################################################################################################################
// MAIN FUNCTIONS >>>>> CONTINUE <<<<< ////////////////////////////////////////////////////////////////////////////////
// ####################################################################################################################

// ----------------------------------------------------------------------------
// function that appends TRANSPORT STATS section to the json string ///////////
// ----------------------------------------------------------------------------

// {
// 	"pckt": {
// 		"valid": true,
// 		"error": null
// 	},
// 	"qId": 5,
// 	"id": {
// 		"sT": 25,
// 		"adr": "0012.4b00.0f83.b601"
// 	},
// 	"tSt": {
// 		"uS": true,
// 		"tcp": {
// 			"use": true,
// 			"rx": 40,
// 			"tx": 33,
// 			"dr": 0,
// 			"cE": 0,
// 			"aA": 0,
// 			"rst": 0,
// 			"rM": 0,
// 			"sD": 0,
// 			"sR": 0
// 		},
// 		"udp": {
// 			"use": true,
// 			"dr": 0,
// 			"rx": 0,
// 			"tx": 0,
// 			"cE": 0
// 		}
// 	},
// 	"hash": 3790190472
// }

/* **********************************************************************************
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
 ************************************************************************************/

static int oar_json_append_stats_tcp_udp(char * buf)
{
    char str[128];
    
    // ######## (UIP_CONF_STATISTICS)######## (UIP_CONF_STATISTICS)######## (UIP_CONF_STATISTICS)######## (UIP_CONF_STATISTICS)######## (UIP_CONF_STATISTICS)######## (UIP_CONF_STATISTICS)######## (UIP_CONF_STATISTICS)########
    #if (UIP_CONF_STATISTICS)

        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // SECTION START tSt{} //////////////////////////////////////////////////////////////////////////
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        sprintf(str, "\""   "tSt"  "\""    ":"  ); if(seguard(buf, str)){return 1;} strcat(buf, str); ///
        sprintf(str, "{"                        ); if(seguard(buf, str)){return 1;} strcat(buf, str); ///
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

            sprintf(str, "\"" "uS"  "\"" ":" "true" ); if(seguard(buf, str)){return 1;} strcat(buf, str);

            // ???????????????????????????????????????????????????????????????????
            sprintf(str, ",");  if(seguard(buf, str)){return 1;} strcat(buf, str);
            // ???????????????????????????????????????????????????????????????????

                // ######## (UIP_CONF_STATISTICS)> (UIP_TCP)######## (UIP_CONF_STATISTICS)> (UIP_TCP)######## (UIP_CONF_STATISTICS)> (UIP_TCP)######## (UIP_CONF_STATISTICS)> (UIP_TCP)########
                #if (UIP_TCP)

                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    // SUBSECTION START tSt{} > tcp{} ///////////////////////////////////////////////////////////
                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    sprintf(str, "\"" "tcp" "\"" ":"    ); if(seguard(buf, str)){return 1;} strcat(buf, str); ///
                    sprintf(str, "{"                    ); if(seguard(buf, str)){return 1;} strcat(buf, str); ///
                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    
                        sprintf(str, "\"" "use" "\"" ":" "true"                         ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str);
                        sprintf(str, "\"" "rx"  "\"" ":" "%lu"  ,uip_stat.tcp.recv      ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str);
                        sprintf(str, "\"" "tx"  "\"" ":" "%lu"  ,uip_stat.tcp.sent      ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str);
                        sprintf(str, "\"" "dr"  "\"" ":" "%lu"  ,uip_stat.tcp.drop      ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str);
                        sprintf(str, "\"" "cE"  "\"" ":" "%lu"  ,uip_stat.tcp.chkerr    ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str);
                        sprintf(str, "\"" "aA"  "\"" ":" "%lu"  ,uip_stat.tcp.ackerr    ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str);
                        sprintf(str, "\"" "rst" "\"" ":" "%lu"  ,uip_stat.tcp.rst       ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str);
                        sprintf(str, "\"" "rM"  "\"" ":" "%lu"  ,uip_stat.tcp.rexmit    ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str);
                        sprintf(str, "\"" "sD"  "\"" ":" "%lu"  ,uip_stat.tcp.syndrop   ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str);
                        sprintf(str, "\"" "sR"  "\"" ":" "%lu"  ,uip_stat.tcp.synrst    ); if(seguard(buf, str)){return 1;} strcat(buf, str);                                                                                                                                                                                         

                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    sprintf(str, "}"); if(seguard(buf, str)){return 1;} strcat(buf, str); ///
                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    // SUBSECTION END tST{} > tcp{} /////////////////////////////////////////
                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        
            // ######## (UIP_CONF_STATISTICS)> (UIP_TCP)######## (UIP_CONF_STATISTICS)> (UIP_TCP)######## (UIP_CONF_STATISTICS)> (UIP_TCP)######## (UIP_CONF_STATISTICS)> (UIP_TCP)########
            // ######## (UIP_CONF_STATISTICS)>!(UIP_TCP)######## (UIP_CONF_STATISTICS)>!(UIP_TCP)######## (UIP_CONF_STATISTICS)>!(UIP_TCP)######## (UIP_CONF_STATISTICS)>!(UIP_TCP)########
            #else

                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                // SUBSECTION START tSt{} > tcp{} ///////////////////////////////////////////////////////////
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                sprintf(str, "\"" "tcp" "\"" ":"    ); if(seguard(buf, str)){return 1;} strcat(buf, str); ///
                sprintf(str, "{"                    ); if(seguard(buf, str)){return 1;} strcat(buf, str); ///
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                
                    sprintf(str, "\"" "use" "\"" ":" "false"    ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, "," ); if(seguard(buf, str)){return 1;} strcat(buf, str);
                    sprintf(str, "\"" "rx"  "\"" ":" "null"     ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, "," ); if(seguard(buf, str)){return 1;} strcat(buf, str);
                    sprintf(str, "\"" "tx"  "\"" ":" "null"     ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, "," ); if(seguard(buf, str)){return 1;} strcat(buf, str);
                    sprintf(str, "\"" "dr"  "\"" ":" "null"     ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, "," ); if(seguard(buf, str)){return 1;} strcat(buf, str);
                    sprintf(str, "\"" "cE"  "\"" ":" "null"     ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, "," ); if(seguard(buf, str)){return 1;} strcat(buf, str);
                    sprintf(str, "\"" "aE"  "\"" ":" "null"     ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, "," ); if(seguard(buf, str)){return 1;} strcat(buf, str);
                    sprintf(str, "\"" "rst" "\"" ":" "null"     ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, "," ); if(seguard(buf, str)){return 1;} strcat(buf, str);
                    sprintf(str, "\"" "rM"  "\"" ":" "null"     ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, "," ); if(seguard(buf, str)){return 1;} strcat(buf, str);
                    sprintf(str, "\"" "sD"  "\"" ":" "null"     ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, "," ); if(seguard(buf, str)){return 1;} strcat(buf, str);
                    sprintf(str, "\"" "sR"  "\"" ":" "null"     ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, "," ); //if(seguard(buf, str)){return 1;} strcat(buf, str);                                                                                                                                                                                      

                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                sprintf(str, "}"); if(seguard(buf, str)){return 1;} strcat(buf, str); ///
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                // SUBSECTION END tSt{} > tcp{} /////////////////////////////////////////
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

            #endif
            // ######## (UIP_CONF_STATISTICS)>!(UIP_TCP)######## (UIP_CONF_STATISTICS)>!(UIP_TCP)######## (UIP_CONF_STATISTICS)>!(UIP_TCP)######## (UIP_CONF_STATISTICS)>!(UIP_TCP)########

            // ???????????????????????????????????????????????????????????????????
            sprintf(str, ",");  if(seguard(buf, str)){return 1;} strcat(buf, str);
            // ???????????????????????????????????????????????????????????????????

            // ######## (UIP_CONF_STATISTICS)> (UIP_UDP)######## (UIP_CONF_STATISTICS)> (UIP_UDP)######## (UIP_CONF_STATISTICS)> (UIP_UDP)######## (UIP_CONF_STATISTICS)> (UIP_UDP)########
            #if (UIP_UDP)

                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                // SUBSECTION START tSt{} > udp{} ///////////////////////////////////////////////////////////
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                sprintf(str, "\"" "udp" "\"" ":"    ); if(seguard(buf, str)){return 1;} strcat(buf, str); ///
                sprintf(str, "{"                    ); if(seguard(buf, str)){return 1;} strcat(buf, str); ///
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                
                    sprintf(str, "\"" "use" "\"" ":" "true"                         ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str);
                    sprintf(str, "\"" "dr"  "\"" ":" "%lu"  ,uip_stat.udp.drop      ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str);
                    sprintf(str, "\"" "rx"  "\"" ":" "%lu"  ,uip_stat.udp.recv      ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str);
                    sprintf(str, "\"" "tx"  "\"" ":" "%lu"  ,uip_stat.udp.sent      ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str);
                    sprintf(str, "\"" "cE"  "\"" ":" "%lu"  ,uip_stat.udp.chkerr    ); if(seguard(buf, str)){return 1;} strcat(buf, str);                                                    

                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                sprintf(str, "}"); if(seguard(buf, str)){return 1;} strcat(buf, str); ///
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                // SUBSECTION END tST{} > udp{} /////////////////////////////////////////
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

            // ######## (UIP_CONF_STATISTICS)> (UIP_UDP)######## (UIP_CONF_STATISTICS)> (UIP_UDP)######## (UIP_CONF_STATISTICS)> (UIP_UDP)######## (UIP_CONF_STATISTICS)> (UIP_UDP)########
            // ######## (UIP_CONF_STATISTICS)>!(UIP_UDP)######## (UIP_CONF_STATISTICS)>!(UIP_UDP)######## (UIP_CONF_STATISTICS)>!(UIP_UDP)######## (UIP_CONF_STATISTICS)>!(UIP_UDP)########
            #else

                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                // SUBSECTION START tSt{} > udp{} ///////////////////////////////////////////////////////////
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                sprintf(str, "\"" "udp" "\"" ":"    ); if(seguard(buf, str)){return 1;} strcat(buf, str); ///
                sprintf(str, "{"                    ); if(seguard(buf, str)){return 1;} strcat(buf, str); ///
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                
                    sprintf(str, "\"" "use" "\"" ":" "false"    ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str);
                    sprintf(str, "\"" "dr"  "\"" ":" "null"     ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str);
                    sprintf(str, "\"" "rx"  "\"" ":" "null"     ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str);
                    sprintf(str, "\"" "tx"  "\"" ":" "null"     ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str);
                    sprintf(str, "\"" "cE"  "\"" ":" "null"     ); if(seguard(buf, str)){return 1;} strcat(buf, str);                                                    

                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                sprintf(str, "}"); if(seguard(buf, str)){return 1;} strcat(buf, str); ///
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                // SUBSECTION END tST{} > udp{} /////////////////////////////////////////
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        
            #endif
            // ######## (UIP_CONF_STATISTICS)>!(UIP_UDP)######## (UIP_CONF_STATISTICS)>!(UIP_UDP)######## (UIP_CONF_STATISTICS)>!(UIP_UDP)######## (UIP_CONF_STATISTICS)>!(UIP_UDP)########

        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        sprintf(str, "}"); if(seguard(buf, str)){return 1;} strcat(buf, str); ///
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // SECTION END nSt{} ////////////////////////////////////////////////////
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    
    // ######## (UIP_CONF_STATISTICS)######## (UIP_CONF_STATISTICS)######## (UIP_CONF_STATISTICS)######## (UIP_CONF_STATISTICS)######## (UIP_CONF_STATISTICS)######## (UIP_CONF_STATISTICS)######## (UIP_CONF_STATISTICS)########
    // ########!(UIP_CONF_STATISTICS)########!(UIP_CONF_STATISTICS)########!(UIP_CONF_STATISTICS)########!(UIP_CONF_STATISTICS)########!(UIP_CONF_STATISTICS)########!(UIP_CONF_STATISTICS)########!(UIP_CONF_STATISTICS)########!
    #else

        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // SECTION START tSt{} //////////////////////////////////////////////////////////////////////////
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        sprintf(str, "\""   "tSt"  "\""    ":"  ); if(seguard(buf, str)){return 1;} strcat(buf, str); ///
        sprintf(str, "{"                        ); if(seguard(buf, str)){return 1;} strcat(buf, str); ///
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

            sprintf(str, "\"" "uS"  "\"" ":" "false" ); if(seguard(buf, str)){return 1;} strcat(buf, str);

            // ???????????????????????????????????????????????????????????????????
            sprintf(str, ",");  if(seguard(buf, str)){return 1;} strcat(buf, str);
            // ???????????????????????????????????????????????????????????????????

            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            // SUBSECTION START stats{} > tcp{} /////////////////////////////////////////////////////////
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            sprintf(str, "\"" "tcp" "\"" ":"    ); if(seguard(buf, str)){return 1;} strcat(buf, str); ///
            sprintf(str, "{"                    ); if(seguard(buf, str)){return 1;} strcat(buf, str); ///
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            
                sprintf(str, "\"" "use" "\"" ":" "null"     ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, "," ); if(seguard(buf, str)){return 1;} strcat(buf, str);
                sprintf(str, "\"" "rx"  "\"" ":" "null"     ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, "," ); if(seguard(buf, str)){return 1;} strcat(buf, str);
                sprintf(str, "\"" "tx"  "\"" ":" "null"     ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, "," ); if(seguard(buf, str)){return 1;} strcat(buf, str);
                sprintf(str, "\"" "dr"  "\"" ":" "null"     ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, "," ); if(seguard(buf, str)){return 1;} strcat(buf, str);
                sprintf(str, "\"" "cE"  "\"" ":" "null"     ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, "," ); if(seguard(buf, str)){return 1;} strcat(buf, str);
                sprintf(str, "\"" "aE"  "\"" ":" "null"     ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, "," ); if(seguard(buf, str)){return 1;} strcat(buf, str);
                sprintf(str, "\"" "rst" "\"" ":" "null"     ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, "," ); if(seguard(buf, str)){return 1;} strcat(buf, str);
                sprintf(str, "\"" "rM"  "\"" ":" "null"     ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, "," ); if(seguard(buf, str)){return 1;} strcat(buf, str);
                sprintf(str, "\"" "sD"  "\"" ":" "null"     ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, "," ); if(seguard(buf, str)){return 1;} strcat(buf, str);
                sprintf(str, "\"" "sR"  "\"" ":" "null"     ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, "," ); //if(seguard(buf, str)){return 1;} strcat(buf, str);                                                                                                                                                                                      

            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            sprintf(str, "}"); if(seguard(buf, str)){return 1;} strcat(buf, str); ///
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            // SUBSECTION END stats{} > tcp{} ///////////////////////////////////////
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

            // ???????????????????????????????????????????????????????????????????
            sprintf(str, ",");  if(seguard(buf, str)){return 1;} strcat(buf, str);
            // ???????????????????????????????????????????????????????????????????

            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            // SUBSECTION START tSt{} > udp{} ///////////////////////////////////////////////////////////
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            sprintf(str, "\"" "udp" "\"" ":"    ); if(seguard(buf, str)){return 1;} strcat(buf, str); ///
            sprintf(str, "{"                    ); if(seguard(buf, str)){return 1;} strcat(buf, str); ///
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            
                sprintf(str, "\"" "use" "\"" ":" "null" ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str);
                sprintf(str, "\"" "dr"  "\"" ":" "null" ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str);
                sprintf(str, "\"" "rx"  "\"" ":" "null" ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str);
                sprintf(str, "\"" "tx"  "\"" ":" "null" ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str);
                sprintf(str, "\"" "cE"  "\"" ":" "null" ); if(seguard(buf, str)){return 1;} strcat(buf, str);                                                    

            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            sprintf(str, "}"); if(seguard(buf, str)){return 1;} strcat(buf, str); ///
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            // SUBSECTION END tST{} > udp{} /////////////////////////////////////////
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        sprintf(str, "}"); if(seguard(buf, str)){return 1;} strcat(buf, str); ///
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // SECTION END tSt{} ////////////////////////////////////////////////////
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    #endif
    // ########!(UIP_CONF_STATISTICS)########!(UIP_CONF_STATISTICS)########!(UIP_CONF_STATISTICS)########!(UIP_CONF_STATISTICS)########!(UIP_CONF_STATISTICS)########!(UIP_CONF_STATISTICS)########!(UIP_CONF_STATISTICS)########!

    return 0;
}
















// ####################################################################################################################
// MAIN FUNCTIONS >>>>> CONTINUE <<<<< ////////////////////////////////////////////////////////////////////////////////
// ####################################################################################################################

// ----------------------------------------------------------------------------
// function that appends NETWORK DISCOVERY STATS section to the json string ///
// ----------------------------------------------------------------------------

// {
// 	"pckt": {
// 		"valid": true,
// 		"error": null
// 	},
// 	"qId": 6,
// 	"id": {
// 		"sT": 27,
// 		"adr": "0012.4b00.0f83.b601"
// 	},
// 	"dSt": {
// 		"uS": true,
// 		"nd6": {
// 			"dr": 0,
// 			"rx": 0,
// 			"tx": 0
// 		}
// 	},
// 	"hash": 3790190472
// }

/* **********************************************************************************
 *      (nd6.drop) >                                         dropped ND6 packets    *
 *      (nd6.recv) >                                        received ND6 packets    *
 *      (nd6.sent) >                                            dent ND6 packets    *
 ************************************************************************************/

static int oar_json_append_stats_nd6(char * buf)
{
    char str[128];
    
    // ######## (UIP_CONF_STATISTICS)######## (UIP_CONF_STATISTICS)######## (UIP_CONF_STATISTICS)######## (UIP_CONF_STATISTICS)######## (UIP_CONF_STATISTICS)######## (UIP_CONF_STATISTICS)######## (UIP_CONF_STATISTICS)########
    #if (UIP_CONF_STATISTICS)

        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // SECTION START dSt{} //////////////////////////////////////////////////////////////////////////
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        sprintf(str, "\""   "dSt"  "\""    ":"  ); if(seguard(buf, str)){return 1;} strcat(buf, str); ///
        sprintf(str, "{"                        ); if(seguard(buf, str)){return 1;} strcat(buf, str); ///
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

            sprintf(str, "\"" "uS"  "\"" ":" "true" ); if(seguard(buf, str)){return 1;} strcat(buf, str);

            // ???????????????????????????????????????????????????????????????????
            sprintf(str, ",");  if(seguard(buf, str)){return 1;} strcat(buf, str);
            // ???????????????????????????????????????????????????????????????????

            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            // SUBSECTION START dSt{} > nd6{} ///////////////////////////////////////////////////////////////
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            sprintf(str, "\""   "nd6"  "\""    ":"  ); if(seguard(buf, str)){return 1;} strcat(buf, str); ///
            sprintf(str, "{"                        ); if(seguard(buf, str)){return 1;} strcat(buf, str); ///
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~        
                
                sprintf(str, "\"" "dr" "\"" ":" "%lu" ,uip_stat.nd6.drop); if(seguard(buf, str)){return 1;} strcat(buf, str);  sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str);
                sprintf(str, "\"" "rx" "\"" ":" "%lu" ,uip_stat.nd6.recv); if(seguard(buf, str)){return 1;} strcat(buf, str);  sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str);
                sprintf(str, "\"" "tx" "\"" ":" "%lu" ,uip_stat.nd6.sent); if(seguard(buf, str)){return 1;} strcat(buf, str);
            
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            sprintf(str, "}"); if(seguard(buf, str)){return 1;} strcat(buf, str); ///
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            // SECTION END nSt{} > nd6{} ////////////////////////////////////////////
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    sprintf(str, "}"); if(seguard(buf, str)){return 1;} strcat(buf, str); ///
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // SECTION END tSt{} ////////////////////////////////////////////////////
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    
    // ######## (UIP_CONF_STATISTICS)######## (UIP_CONF_STATISTICS)######## (UIP_CONF_STATISTICS)######## (UIP_CONF_STATISTICS)######## (UIP_CONF_STATISTICS)######## (UIP_CONF_STATISTICS)######## (UIP_CONF_STATISTICS)########
    // ########!(UIP_CONF_STATISTICS)########!(UIP_CONF_STATISTICS)########!(UIP_CONF_STATISTICS)########!(UIP_CONF_STATISTICS)########!(UIP_CONF_STATISTICS)########!(UIP_CONF_STATISTICS)########!(UIP_CONF_STATISTICS)########!
    #else

        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // SECTION START dSt{} //////////////////////////////////////////////////////////////////////////
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        sprintf(str, "\""   "dSt"  "\""    ":"  ); if(seguard(buf, str)){return 1;} strcat(buf, str); ///
        sprintf(str, "{"                        ); if(seguard(buf, str)){return 1;} strcat(buf, str); ///
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

            sprintf(str, "\"" "uS"  "\"" ":" "false" ); if(seguard(buf, str)){return 1;} strcat(buf, str);

            // ???????????????????????????????????????????????????????????????????
            sprintf(str, ",");  if(seguard(buf, str)){return 1;} strcat(buf, str);
            // ???????????????????????????????????????????????????????????????????

            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            // SUBSECTION START dSt{} > nd6{} ///////////////////////////////////////////////////////////////
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            sprintf(str, "\""   "nd6"  "\""    ":"  ); if(seguard(buf, str)){return 1;} strcat(buf, str); ///
            sprintf(str, "{"                        ); if(seguard(buf, str)){return 1;} strcat(buf, str); ///
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~     

                sprintf(str, "\"" "dr" "\"" ":" "null"); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str);
                sprintf(str, "\"" "rx" "\"" ":" "null"); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str);
                sprintf(str, "\"" "tx" "\"" ":" "null"); if(seguard(buf, str)){return 1;} strcat(buf, str);

            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            sprintf(str, "}"); if(seguard(buf, str)){return 1;} strcat(buf, str); ///
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            // SECTION END nSt{} > nd6{} ////////////////////////////////////////////
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        sprintf(str, "}"); if(seguard(buf, str)){return 1;} strcat(buf, str); ///
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // SECTION END tSt{} ////////////////////////////////////////////////////
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ 

    #endif
    // ########!(UIP_CONF_STATISTICS)########!(UIP_CONF_STATISTICS)########!(UIP_CONF_STATISTICS)########!(UIP_CONF_STATISTICS)########!(UIP_CONF_STATISTICS)########!(UIP_CONF_STATISTICS)########!(UIP_CONF_STATISTICS)########!

    return 0;
}
















// ####################################################################################################################
// MAIN FUNCTIONS >>>>> CONTINUE <<<<< ////////////////////////////////////////////////////////////////////////////////
// ####################################################################################################################

// ----------------------------------------------------------------------------
// function that appends IPv6 ADDRESSES section to the json string ////////////
// ----------------------------------------------------------------------------

// {
// 	"pckt": {
// 		"valid": true,
// 		"error": null
// 	},
// 	"qId": 7,
// 	"id": {
// 		"sT": 29,
// 		"adr": "0012.4b00.0f83.b601"
// 	},
// 	"addr": {
// 		"IPv6": true,
// 		"ad": ["null", "fd00::212:4b00:f83:b601", "fe80::212:4b00:f83:b601"]
// 	}
// }

// Node IPv6 addresses: fd00::212:4b00:f83:b601
// Node IPv6 addresses: fe80::212:4b00:f83:b601

static int oar_json_append_ipv6_addr(char * buf)
{
    char str[128];
    
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // SECTION START addr{} /////////////////////////////////////////////////////////////////////
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    sprintf(str, "\"" "addr" "\"" ":"   ); if(seguard(buf, str)){return 1;} strcat(buf, str); /// 
    sprintf(str, "{"                    ); if(seguard(buf, str)){return 1;} strcat(buf, str); ///
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    // ######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)########
    #if (NETSTACK_CONF_WITH_IPV6)

        sprintf(str, "\"" "IPv6" "\"" ":" "true"); if(seguard(buf, str)){return 1;} strcat(buf, str);

        // ???????????????????????????????????????????????????????????????????
        sprintf(str, ",");  if(seguard(buf, str)){return 1;} strcat(buf, str);
        // ??????????????????????????????????????????????????????????????????? 

        uint8_t state;

        // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
        // SUBARRAY START net{} > ad[] //////////////////////////////////////////////////////////////
        // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
        sprintf(str, "\"" "ad" "\"" ":" ); if(seguard(buf, str)){return 1;} strcat(buf, str); ///////
        // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

            // [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]
            sprintf(str, "["); if(seguard(buf, str)){return 1;} strcat(buf, str);

            for(int i = 0; i < UIP_DS6_ADDR_NB; i++) 
            {
                state = uip_ds6_if.addr_list[i].state;

                if(uip_ds6_if.addr_list[i].isused && (state == ADDR_TENTATIVE || state == ADDR_PREFERRED)) 
                {   
                    oar_json_ipaddr_to_str(oar_json_ipaddr, &uip_ds6_if.addr_list[i].ipaddr);
                    sprintf(str, "\""   "%s"      "\"" ,oar_json_ipaddr ); if(seguard(buf, str)){return 1;} strcat(buf, str);

                    if (i != (UIP_DS6_ADDR_NB - 1)) { sprintf(str, "," );  if(seguard(buf, str)){return 1;} strcat(buf, str); }
                }
                else
                {

                    sprintf(str,        "null"                          ); if(seguard(buf, str)){return 1;} strcat(buf, str);
                    
                    if (i != (UIP_DS6_ADDR_NB - 1)) { sprintf(str, ","  );  if(seguard(buf, str)){return 1;} strcat(buf, str); } 
                }
            }

            sprintf(str, "]"); if(seguard(buf, str)){return 1;} strcat(buf, str);
            // [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]

        // :::::::::::::::::::::::::::::
        // SUBARRAY END  addr{} > nbrs[] 
        // ::::::::::::::::::::::::::::: 

        
    
    // ######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)########
    // ########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!
    #else

        sprintf(str, "\"" "IPv6" "\"" ":" "false"); if(seguard(buf, str)){return 1;} strcat(buf, str);

        // ???????????????????????????????????????????????????????????????????
        sprintf(str, ",");  if(seguard(buf, str)){return 1;} strcat(buf, str);
        // ??????????????????????????????????????????????????????????????????? 

        // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
        // SUBARRAY START addr{} > ads[] ////////////////////////////////////////////////////////////
        // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
        sprintf(str, "\"" "addr" "\"" ":" ); if(seguard(buf, str)){return 1;} strcat(buf, str); /////  
        // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

            // [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]
            sprintf(str,"["); if(seguard(buf, str)){return 1;} strcat(buf, str);

            for(int i = 0; i < UIP_DS6_ADDR_NB; i++) 
            {
                sprintf(str, "null"); if(seguard(buf, str)){return 1;} strcat(buf, str);
                    
                if (i != (UIP_DS6_ADDR_NB - 1)) { sprintf(str, "," );  if(seguard(buf, str)){return 1;} strcat(buf, str); }
            }

            sprintf(str, "]"); if(seguard(buf, str)){return 1;} strcat(buf, str);
            // [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]

        // :::::::::::::::::::::::::::::
        // SUBARRAY END  addr{} > nbrs[] 
        // :::::::::::::::::::::::::::::

    #endif
    // ########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    sprintf(str, "}"); if(seguard(buf, str)){return 1;} strcat(buf, str); ///
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // SECTION END addr{} ///////////////////////////////////////////////////
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    return 0;
}
















// ####################################################################################################################
// MAIN FUNCTIONS >>>>> CONTINUE <<<<< ////////////////////////////////////////////////////////////////////////////////
// ####################################################################################################################

// ----------------------------------------------------------------------------
// function that appends IPv6 ADDRESSES section to the json string ////////////
// ----------------------------------------------------------------------------

// {
// 	"pckt": {
// 		"valid": true,
// 		"error": null
// 	},
// 	"qId": 8,
// 	"id": {
// 		"sT": 31,
// 		"adr": "0012.4b00.0f83.b601"
// 	},
// 	"nsIP": {
// 		"IPv6": true,
// 		"ns": [{
// 			"ipAddr": "fe80::212:4b00:f24:8385"
// 		}, {
// 			"ipAddr": "fe80::212:4b00:f82:da03"
// 		}, {
// 			"ipAddr": "fe80::212:4b00:f82:a600"
// 		}, null, null]
// 	},
// 	"hash": 3790190472
// }

// Node IPv6 neighbor 1: fe80::212:4b00:f24:8385 <-> 0012.4b00.0f24.8385, router 0, state Reachable 
// Node IPv6 neighbor 2: fe80::212:4b00:f82:a600 <-> 0012.4b00.0f82.a600, router 0, state Reachable 
// Node IPv6 neighbor 3: fe80::212:4b00:f82:da03 <-> 0012.4b00.0f82.da03, router 0, state Reachable 

static int oar_json_append_ipv6_nbrs_ip(char * buf)
{
    char str[128];
    
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // SECTION START nsIP{} /////////////////////////////////////////////////////////////////////
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    sprintf(str, "\"" "nsIP" "\"" ":"   ); if(seguard(buf, str)){return 1;} strcat(buf, str); ///   
    sprintf(str, "{"                    ); if(seguard(buf, str)){return 1;} strcat(buf, str); ///
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    // ######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)########
    #if (NETSTACK_CONF_WITH_IPV6)

        sprintf(str, "\"" "IPv6" "\"" ":" "true"); if(seguard(buf, str)){return 1;} strcat(buf, str);

        // ???????????????????????????????????????????????????????????????????
        sprintf(str, ",");  if(seguard(buf, str)){return 1;} strcat(buf, str);
        // ??????????????????????????????????????????????????????????????????? 

        uip_ds6_nbr_t *nbr;
        int oar_json_ip_neighbor_count = 0;

        nbr = uip_ds6_nbr_head();

        if(nbr == NULL)
        {
            // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
            //  (nbr == NULL) ///////////////////////////////////////////////////////////////////////////
            // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
            // SUBARRAY START nsIP{} > nbrs[] > /////////////////////////////////////////////////////////
            // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
            sprintf(str, "\"" "ns" "\"" ":"); if(seguard(buf, str)){return 1;} strcat(buf, str); ////////
            // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

                // [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]
                sprintf(str, "["); if(seguard(buf, str)){return 1;} strcat(buf, str);

                for (int i = 0; i < NBR_TABLE_CONF_MAX_NEIGHBORS; i++)
                {
                    sprintf(str,    "null"  );  if(seguard(buf, str)){return 1;} strcat(buf, str);
                    if (i != (NBR_TABLE_CONF_MAX_NEIGHBORS - 1)) { sprintf(str, "," );  if(seguard(buf, str)){return 1;} strcat(buf, str); } 
                }

                sprintf(str, "]"); if(seguard(buf, str)){return 1;} strcat(buf, str);
                // [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]
            
            // ::::::::::::::::::::::::::::
            // SUBARRAY END  net{} > nbrs[] 
            // ::::::::::::::::::::::::::::
        }
        else
        {
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            //  (nbr == NULL) ///////////////////////////////////////////////
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            // SUBARRAY START nsIP{} > ns[] > ///////////////////////////////
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            sprintf(str, "\"" "ns" "\"" ":"); if(seguard(buf, str)){return 1;} strcat(buf, str); /////////////
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

                // [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]
                sprintf(str, "["); if(seguard(buf, str)){return 1;} strcat(buf, str);
            
                while(nbr != NULL)
                {
                    oar_json_ip_neighbor_count++;
                    
                    // {{{{{{{{{{{{{{{{{}}}}}}}}}}}}}}}}}
                    sprintf(str, "{"); if(seguard(buf, str)){return 1;} strcat(buf, str);
                    
                        oar_json_ipaddr_to_str(oar_json_ipaddr, uip_ds6_nbr_get_ipaddr(nbr));
                        sprintf(str,    "\""    "ipAddr"    "\""    ":" "\""    "%s"    "\""    ,oar_json_ipaddr                            ); if(seguard(buf, str)){return 1;} strcat(buf, str);

                    sprintf(str, "}"); if(seguard(buf, str)){return 1;} strcat(buf, str);
                    // {{{{{{{{{{{{{{{{{}}}}}}}}}}}}}}}}}

                    if (oar_json_ip_neighbor_count != NBR_TABLE_CONF_MAX_NEIGHBORS) { sprintf(str, "," );  if(seguard(buf, str)){return 1;} strcat(buf, str); }
                    
                    nbr = uip_ds6_nbr_next(nbr);
                }

                for (int j = oar_json_ip_neighbor_count; j < NBR_TABLE_CONF_MAX_NEIGHBORS; j++)
                {
                    sprintf(str,    "null"  );  if(seguard(buf, str)){return 1;} strcat(buf, str);
                    
                    if (j != (NBR_TABLE_CONF_MAX_NEIGHBORS - 1)) { sprintf(str, "," );  if(seguard(buf, str)){return 1;} strcat(buf, str); } 
                }

                sprintf(str, "]"); if(seguard(buf, str)){return 1;} strcat(buf, str);
                // [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]

            // ::::::::::::::::::::::::::::
            // SUBARRAY END  net{} > nbrs[] 
            // ::::::::::::::::::::::::::::
        }

    // ######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)########
    // ########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!
    #else

        sprintf(str, "\"" "IPv6" "\"" ":" "false"); if(seguard(buf, str)){return 1;} strcat(buf, str);

        // ???????????????????????????????????????????????????????????????????
        sprintf(str, ",");  if(seguard(buf, str)){return 1;} strcat(buf, str);
        // ???????????????????????????????????????????????????????????????????

        // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
        // SUBARRAY START net{} > nbrs[] ////////////////////////////////////////////////////////////
        // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
        sprintf(str, "\"" "ns" "\"" ":"); if(seguard(buf, str)){return 1;} strcat(buf, str); ////////
        // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
        
            // [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]
            sprintf(str,"["); if(seguard(buf, str)){return 1;} strcat(buf, str);

            for(int i = 0; i < UIP_DS6_ADDR_NB; i++) 
            {
                sprintf(str, "\"" "null" "\""); if(seguard(buf, str)){return 1;} strcat(buf, str);
                    
                if (i != (UIP_DS6_ADDR_NB - 1)) { sprintf(str, "," );  if(seguard(buf, str)){return 1;} strcat(buf, str); }
            }

            sprintf(str, "]"); if(seguard(buf, str)){return 1;} strcat(buf, str);
            // [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]

        // ::::::::::::::::::::::::::::
        // SUBARRAY END  net{} > nbrs[] 
        // ::::::::::::::::::::::::::::

    #endif
    // ########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    sprintf(str, "}"); if(seguard(buf, str)){return 1;} strcat(buf, str); ///
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // SECTION END nsIP{} ///////////////////////////////////////////////////
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    return 0;
}
















// ####################################################################################################################
// MAIN FUNCTIONS >>>>> CONTINUE <<<<< ////////////////////////////////////////////////////////////////////////////////
// ####################################################################################################################

// ---------------------------------------------------------------------------
// function that appends IPv6 NEIGBORS LL ADDRESSES section to the json string
// ---------------------------------------------------------------------------

// {
// 	"pckt": {
// 		"valid": true,
// 		"error": null
// 	},
// 	"qId": 9,
// 	"id": {
// 		"sT": 33,
// 		"adr": "0012.4b00.0f83.b601"
// 	},
// 	"nsLL": {
// 		"IPv6": true,
// 		"ns": [{
// 			"llAddr": "0012.4b00.0f24.8385"
// 		}, {
// 			"llAddr": "0012.4b00.0f82.da03"
// 		}, {
// 			"llAddr": "0012.4b00.0f82.a600"
// 		}, null, null]
// 	},
// 	"hash": 3790190472
// }

// Node IPv6 neighbor 1: fe80::212:4b00:f24:8385 <-> 0012.4b00.0f24.8385, router 0, state Reachable 
// Node IPv6 neighbor 2: fe80::212:4b00:f82:a600 <-> 0012.4b00.0f82.a600, router 0, state Reachable 
// Node IPv6 neighbor 3: fe80::212:4b00:f82:da03 <-> 0012.4b00.0f82.da03, router 0, state Reachable 

static int oar_json_append_ipv6_nbrs_ll(char * buf)
{
    char str[128];
    
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // SECTION START nsLL{} /////////////////////////////////////////////////////////////////////
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    sprintf(str, "\"" "nsLL" "\"" ":"   ); if(seguard(buf, str)){return 1;} strcat(buf, str); ///  
    sprintf(str, "{"                    ); if(seguard(buf, str)){return 1;} strcat(buf, str); ///
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    // ######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)########
    #if (NETSTACK_CONF_WITH_IPV6)

        sprintf(str, "\"" "IPv6" "\"" ":" "true"); if(seguard(buf, str)){return 1;} strcat(buf, str);

        // ???????????????????????????????????????????????????????????????????
        sprintf(str, ",");  if(seguard(buf, str)){return 1;} strcat(buf, str);
        // ??????????????????????????????????????????????????????????????????? 

        uip_ds6_nbr_t *nbr;
        int oar_json_ip_neighbor_count = 0;

        nbr = uip_ds6_nbr_head();

        if(nbr == NULL)
        {
            // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
            //  (nbr == NULL) ///////////////////////////////////////////////////////////////////////////
            // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
            // SUBARRAY START nsLL{} > ns[] > ///////////////////////////////////////////////////////////
            // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
            sprintf(str, "\"" "nbrs" "\"" ":"); if(seguard(buf, str)){return 1;} strcat(buf, str); //////
            // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

                // [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]
                sprintf(str, "["); if(seguard(buf, str)){return 1;} strcat(buf, str);

                for (int i = 0; i < NBR_TABLE_CONF_MAX_NEIGHBORS; i++)
                {
                    sprintf(str,    "null"  );  if(seguard(buf, str)){return 1;} strcat(buf, str);
                    if (i != (NBR_TABLE_CONF_MAX_NEIGHBORS - 1)) { sprintf(str, "," );  if(seguard(buf, str)){return 1;} strcat(buf, str); } 
                }

                sprintf(str, "]"); if(seguard(buf, str)){return 1;} strcat(buf, str);
                // [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]
            
            // ::::::::::::::::::::::::::::
            // SUBARRAY END  net{} > nbrs[] 
            // ::::::::::::::::::::::::::::
        }
        else
        {
            // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
            //  (nbr == NULL) ///////////////////////////////////////////////////////////////////////////
            // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
            // SUBARRAY START nsLL{} > ns[] > ///////////////////////////////////////////////////////////
            // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
            sprintf(str, "\"" "ns" "\"" ":"); if(seguard(buf, str)){return 1;} strcat(buf, str); ////////
            // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

                // [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]
                sprintf(str, "["); if(seguard(buf, str)){return 1;} strcat(buf, str);
            
                while(nbr != NULL)
                {
                    oar_json_ip_neighbor_count++;
                    
                    // {{{{{{{{{{{{{{{{{}}}}}}}}}}}}}}}}}
                    sprintf(str, "{"); if(seguard(buf, str)){return 1;} strcat(buf, str);
                    
                        oar_json_lladdr_to_str(oar_json_lladdr, (linkaddr_t *)uip_ds6_nbr_get_ll(nbr));
                        sprintf(str,    "\""    "llAddr"    "\""    ":" "\""    "%s"    "\""    ,oar_json_lladdr                            ); if(seguard(buf, str)){return 1;} strcat(buf, str);

                    sprintf(str, "}"); if(seguard(buf, str)){return 1;} strcat(buf, str);
                    // {{{{{{{{{{{{{{{{{}}}}}}}}}}}}}}}}}

                    if (oar_json_ip_neighbor_count != NBR_TABLE_CONF_MAX_NEIGHBORS) { sprintf(str, "," );  if(seguard(buf, str)){return 1;} strcat(buf, str); }
                    
                    nbr = uip_ds6_nbr_next(nbr);
                }

                for (int j = oar_json_ip_neighbor_count; j < NBR_TABLE_CONF_MAX_NEIGHBORS; j++)
                {
                    sprintf(str,    "null"  );  if(seguard(buf, str)){return 1;} strcat(buf, str);
                    
                    if (j != (NBR_TABLE_CONF_MAX_NEIGHBORS - 1)) { sprintf(str, "," );  if(seguard(buf, str)){return 1;} strcat(buf, str); } 
                }

                sprintf(str, "]"); if(seguard(buf, str)){return 1;} strcat(buf, str);
                // [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]

            // ::::::::::::::::::::::::::::
            // SUBARRAY END  net{} > nbrs[] 
            // ::::::::::::::::::::::::::::
        }

    // ######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)########
    // ########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!
    #else

        sprintf(str, "\"" "IPv6" "\"" ":" "false"); if(seguard(buf, str)){return 1;} strcat(buf, str);

        // ???????????????????????????????????????????????????????????????????
        sprintf(str, ",");  if(seguard(buf, str)){return 1;} strcat(buf, str);
        // ???????????????????????????????????????????????????????????????????

        // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
        // SUBARRAY START nsLL > ns[] ///////////////////////////////////////////////////////////////
        // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
        sprintf(str, "\"" "nbrs" "\"" ":"); if(seguard(buf, str)){return 1;} strcat(buf, str); //////
        // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
        
            // [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]
            sprintf(str,"["); if(seguard(buf, str)){return 1;} strcat(buf, str);

            for(int i = 0; i < UIP_DS6_ADDR_NB; i++) 
            {
                sprintf(str, "\"" "null" "\""); if(seguard(buf, str)){return 1;} strcat(buf, str);
                    
                if (i != (UIP_DS6_ADDR_NB - 1)) { sprintf(str, "," );  if(seguard(buf, str)){return 1;} strcat(buf, str); }
            }

            sprintf(str, "]"); if(seguard(buf, str)){return 1;} strcat(buf, str);
            // [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]

        // ::::::::::::::::::::::::::::
        // SUBARRAY END  net{} > nbrs[] 
        // ::::::::::::::::::::::::::::

    #endif
    // ########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    sprintf(str, "}"); if(seguard(buf, str)){return 1;} strcat(buf, str); ///
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // SECTION END nsLL{} ///////////////////////////////////////////////////
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    return 0;
}
















// ####################################################################################################################
// MAIN FUNCTIONS >>>>> CONTINUE <<<<< ////////////////////////////////////////////////////////////////////////////////
// ####################################################################################################################

// ----------------------------------------------------------------------------
// function that appends IPv6 NEIGHBOR STATES section to the json string //////
// ----------------------------------------------------------------------------

// {
// 	"pckt": {
// 		"valid": true,
// 		"error": null
// 	},
// 	"qId": 10,
// 	"id": {
// 		"sT": 35,
// 		"adr": "0012.4b00.0f83.b601"
// 	},
// 	"nsSt": {
// 		"IPv6": true,
// 		"ns": [{
// 			"router": 0,
// 			"state": "Reachable"
// 		}, {
// 			"router": 0,
// 			"state": "Reachable"
// 		}, {
// 			"router": 0,
// 			"state": "Reachable"
// 		}, null, null]
// 	},
// 	"hash": 3790190472
// }

// Node IPv6 neighbor 1: fe80::212:4b00:f24:8385 <-> 0012.4b00.0f24.8385, router 0, state Reachable 
// Node IPv6 neighbor 2: fe80::212:4b00:f82:a600 <-> 0012.4b00.0f82.a600, router 0, state Reachable 
// Node IPv6 neighbor 3: fe80::212:4b00:f82:da03 <-> 0012.4b00.0f82.da03, router 0, state Reachable 

static int oar_json_append_ipv6_nbrs_states(char * buf)
{
    char str[128];
    
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // SECTION START nsSt{} /////////////////////////////////////////////////////////////////////
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    sprintf(str, "\"" "nsSt" "\"" ":"   ); if(seguard(buf, str)){return 1;} strcat(buf, str); ///  
    sprintf(str, "{"                    ); if(seguard(buf, str)){return 1;} strcat(buf, str); ///
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    // ######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)########
    #if (NETSTACK_CONF_WITH_IPV6)

        sprintf(str, "\"" "IPv6" "\"" ":" "true"); if(seguard(buf, str)){return 1;} strcat(buf, str);

        // ???????????????????????????????????????????????????????????????????
        sprintf(str, ",");  if(seguard(buf, str)){return 1;} strcat(buf, str);
        // ??????????????????????????????????????????????????????????????????? 

        uip_ds6_nbr_t *nbr;
        int oar_json_ip_neighbor_count = 0;

        nbr = uip_ds6_nbr_head();

        if(nbr == NULL)
        {
            // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
            //  (nbr == NULL) ///////////////////////////////////////////////////////////////////////////
            // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
            // SUBARRAY START nsSt{} > ns[] > ///////////////////////////////////////////////////////////
            // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
            sprintf(str, "\"" "ns" "\"" ":"); if(seguard(buf, str)){return 1;} strcat(buf, str); ////////
            // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

                // [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]
                sprintf(str, "["); if(seguard(buf, str)){return 1;} strcat(buf, str);

                for (int i = 0; i < NBR_TABLE_CONF_MAX_NEIGHBORS; i++)
                {
                    sprintf(str,    "null"  );  if(seguard(buf, str)){return 1;} strcat(buf, str);
                    if (i != (NBR_TABLE_CONF_MAX_NEIGHBORS - 1)) { sprintf(str, "," );  if(seguard(buf, str)){return 1;} strcat(buf, str); } 
                }

                sprintf(str, "]"); if(seguard(buf, str)){return 1;} strcat(buf, str);
                // [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]
            
            // :::::::::::::::::::::::::::
            // SUBARRAY END  nsSt{} > ns[]
            // ::::::::::::::::::::::::::: 
        }
        else
        {
            // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
            //  (nbr == NULL) ///////////////////////////////////////////////////////////////////////////
            // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
            // SUBARRAY START nsSt{} > ns[] > ///////////////////////////////////////////////////////////
            // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
            sprintf(str, "\"" "ns" "\"" ":"); if(seguard(buf, str)){return 1;} strcat(buf, str); ////////
            // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

                // [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]
                sprintf(str, "["); if(seguard(buf, str)){return 1;} strcat(buf, str);
            
                while(nbr != NULL)
                {
                    oar_json_ip_neighbor_count++;
                    
                    // {{{{{{{{{{{{{{{{{}}}}}}}}}}}}}}}}}
                    sprintf(str, "{"); if(seguard(buf, str)){return 1;} strcat(buf, str);
                    
                        sprintf(str,    "\""    "router"    "\""    ":"         "%u"            ,nbr->isrouter                              ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, ",");  if(seguard(buf, str)){return 1;} strcat(buf, str);
                        sprintf(str,    "\""    "state"     "\""    ":" "\""    "%s"    "\""    ,oar_json_ds6_nbr_state_to_str(nbr->state)  ); if(seguard(buf, str)){return 1;} strcat(buf, str);

                    sprintf(str, "}"); if(seguard(buf, str)){return 1;} strcat(buf, str);
                    // {{{{{{{{{{{{{{{{{}}}}}}}}}}}}}}}}}

                    if (oar_json_ip_neighbor_count != NBR_TABLE_CONF_MAX_NEIGHBORS) { sprintf(str, "," );  if(seguard(buf, str)){return 1;} strcat(buf, str); }
                    
                    nbr = uip_ds6_nbr_next(nbr);
                }

                for (int j = oar_json_ip_neighbor_count; j < NBR_TABLE_CONF_MAX_NEIGHBORS; j++)
                {
                    sprintf(str,    "null"  );  if(seguard(buf, str)){return 1;} strcat(buf, str);
                    
                    if (j != (NBR_TABLE_CONF_MAX_NEIGHBORS - 1)) { sprintf(str, "," );  if(seguard(buf, str)){return 1;} strcat(buf, str); } 
                }

                sprintf(str, "]"); if(seguard(buf, str)){return 1;} strcat(buf, str);
                // [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]

            // :::::::::::::::::::::::::::
            // SUBARRAY END  nsSt{} > ns[]
            // :::::::::::::::::::::::::::
        }

    // ######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)########
    // ########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!
    #else

        sprintf(str, "\"" "IPv6" "\"" ":" "false"); if(seguard(buf, str)){return 1;} strcat(buf, str);

        // ???????????????????????????????????????????????????????????????????
        sprintf(str, ",");  if(seguard(buf, str)){return 1;} strcat(buf, str);
        // ???????????????????????????????????????????????????????????????????

        // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
        // SUBARRAY START nsSt{} > ns[] /////////////////////////////////////////////////////////////
        // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
        sprintf(str, "\"" "ns" "\"" ":"); if(seguard(buf, str)){return 1;} strcat(buf, str); ////////
        // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
        
            // [[[[[[[[[[[[[[[[]]]]]]]]]]]]]]]]
            sprintf(str,"["); if(seguard(buf, str)){return 1;} strcat(buf, str);

            for(int i = 0; i < UIP_DS6_ADDR_NB; i++) 
            {
                sprintf(str, "\"" "null" "\""); if(seguard(buf, str)){return 1;} strcat(buf, str);
                    
                if (i != (UIP_DS6_ADDR_NB - 1)) { sprintf(str, "," );  if(seguard(buf, str)){return 1;} strcat(buf, str); }
            }

            sprintf(str, "]"); if(seguard(buf, str)){return 1;} strcat(buf, str);
            // [[[[[[[[[[[[[[[[[]]]]]]]]]]]]]]]]]

        // :::::::::::::::::::::::::::
        // SUBARRAY END  nsSt{} > ns[]
        // :::::::::::::::::::::::::::

    #endif
    // ########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    sprintf(str, "}"); if(seguard(buf, str)){return 1;} strcat(buf, str); ///
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // SECTION END nbrs{} ///////////////////////////////////////////////////
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    return 0;
}
















// ####################################################################################################################
// MAIN FUNCTIONS >>>>> CONTINUE <<<<< ////////////////////////////////////////////////////////////////////////////////
// ####################################################################################################################

// ----------------------------------------------------------------------------
// function that appends ROUTING section to the json string ///////////////////
// ----------------------------------------------------------------------------

// {
// 	"pckt": {
// 		"valid": true,
// 		"error": null
// 	},
// 	"qId": 11,
// 	"id": {
// 		"sT": 37,
// 		"adr": "0012.4b00.0f83.b601"
// 	},
// 	"rt": {
// 		"IPv6": true,
// 		"df": "fe80::212:4b00:f24:8385",
// 		"lt": "infinite"
// 	},
// 	"hash": 3790190472
// }

// Default route: fe80::212:4b00:f24:8385 (lifetime: infinite)

static int oar_json_append_routing(char * buf)
{
    char str[128];

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // SECTION START rt{} ///////////////////////////////////////////////////////////////////////
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    sprintf(str, "\"" "rt" "\"" ":"     ); if(seguard(buf, str)){return 1;} strcat(buf, str); ///   
    sprintf(str, "{"                    ); if(seguard(buf, str)){return 1;} strcat(buf, str); ///
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

        // ######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)########
        #if (NETSTACK_CONF_WITH_IPV6)

            sprintf(str, "\"" "IPv6" "\"" ":" "true"); if(seguard(buf, str)){return 1;} strcat(buf, str);

            // ???????????????????????????????????????????????????????????????????
            sprintf(str, ",");  if(seguard(buf, str)){return 1;} strcat(buf, str);
            // ??????????????????????????????????????????????????????????????????? 

            uip_ds6_defrt_t *default_route;
            default_route = uip_ds6_defrt_lookup(uip_ds6_defrt_choose());

            if(default_route != NULL)
            {
                oar_json_ipaddr_to_str(oar_json_ipaddr, &default_route->ipaddr);
                sprintf(str,    "\""    "df"    "\""    ":" "\""    "%s"    "\""    ,oar_json_ipaddr   );  if(seguard(buf, str)){return 1;} strcat(buf, str);   sprintf(str, "," );  if(seguard(buf, str)){return 1;} strcat(buf, str);

                if (default_route->lifetime.interval != 0)  { sprintf(str,   "\""    "lt"   "\""    ":" "\""    "%lu"      "\""    ,(unsigned long)default_route->lifetime.interval      );  if(seguard(buf, str)){return 1;} strcat(buf, str);   sprintf(str, "," );  if(seguard(buf, str)){return 1;} strcat(buf, str); }
                else                                        { sprintf(str,   "\""    "lt"   "\""    ":" "\""    "infinite" "\""                                                          );  if(seguard(buf, str)){return 1;} strcat(buf, str); }   // sprintf(str, "," );  if(seguard(buf, str)){return 1;} strcat(buf, str);  
            }
            else
            {
                sprintf(str,    "\""    "df"    "\""    ":" "\""    "none"  "\""                            );  if(seguard(buf, str)){return 1;} strcat(buf, str);   sprintf(str, "," );  if(seguard(buf, str)){return 1;} strcat(buf, str);
                sprintf(str,    "\""    "lt"    "\""    ":"         "null"                                  );  if(seguard(buf, str)){return 1;} strcat(buf, str);   

            }


        // ######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)########
        // ########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!
        #else

            sprintf(str, "\"" "IPv6" "\"" ":" "false"); if(seguard(buf, str)){return 1;} strcat(buf, str);
            
            sprintf(str, "\"" "df"  "\"" ":"    "null"      ); if(seguard(buf, str)){return 1;} strcat(buf, str);   sprintf(str, "," ); if(seguard(buf, str)){return 1;} strcat(buf, str);
            sprintf(str, "\"" "lt"  "\"" ":"    "null"      ); if(seguard(buf, str)){return 1;} strcat(buf, str);


        #endif
        // ########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    sprintf(str, "}"); if(seguard(buf, str)){return 1;} strcat(buf, str); ///
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // SECTION END net{} ////////////////////////////////////////////////////
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    return 0;
}
















// ####################################################################################################################
// MAIN FUNCTIONS >>>>> CONTINUE <<<<< ////////////////////////////////////////////////////////////////////////////////
// ####################################################################################################################

// ----------------------------------------------------------------------------------
// function that appends ROUTING LINK SOURCES section to the json string ////////////
// ----------------------------------------------------------------------------------

// {
// 	"pckt": {
// 		"valid": true,
// 		"error": null
// 	},
// 	"qId": 12,
// 	"id": {
// 		"sT": 39,
// 		"adr": "0012.4b00.0f83.b601"
// 	},
// 	"rtLS": {
// 		"IPv6": true,
// 		"rpl": true,
//      "totLs" : 0,
// 		"ls": ["null", "null", "null", "null", "null"]
// 	},
// 	"hash": 3790190472
// }

// |---> Routing links (%u in total): ["&child_ipaddr ""/(DODAG root) <---| to &parent_ipaddr (lifetime: infinite/%lu seconds)", "null", "null", "null", "null"]

static int oar_json_append_routing_link_sources(char * buf)
{
    char str[128];

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // SECTION START rtLS{} /////////////////////////////////////////////////////////////////////
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    sprintf(str, "\"" "rtLS" "\"" ":"   ); if(seguard(buf, str)){return 1;} strcat(buf, str); ///  
    sprintf(str, "{"                    ); if(seguard(buf, str)){return 1;} strcat(buf, str); ///
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

        // ######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)########
        #if (NETSTACK_CONF_WITH_IPV6)

            sprintf(str, "\"" "IPv6" "\"" ":" "true"); if(seguard(buf, str)){return 1;} strcat(buf, str);

            // ???????????????????????????????????????????????????????????????????
            sprintf(str, ",");  if(seguard(buf, str)){return 1;} strcat(buf, str);
            // ??????????????????????????????????????????????????????????????????? 

            // ######## (NETSTACK_CONF_WITH_IPV6)> (UIP_CONF_IPV6_RPL)######## (NETSTACK_CONF_WITH_IPV6)> (UIP_CONF_IPV6_RPL)######## (NETSTACK_CONF_WITH_IPV6)> (UIP_CONF_IPV6_RPL)######## (NETSTACK_CONF_WITH_IPV6)> (UIP_CONF_IPV6_RPL)######## 
            #if (UIP_CONF_IPV6_RPL)

                sprintf(str, "\"" "rpl"     "\"" ":" "true"                     ); if(seguard(buf, str)){return 1;} strcat(buf, str);

                // ???????????????????????????????????????????????????????????????????
                sprintf(str, ",");  if(seguard(buf, str)){return 1;} strcat(buf, str);
                // ??????????????????????????????????????????????????????????????????? 

                int oar_json_uip_sr_links_count = 0;

                if (uip_sr_num_nodes() > 0)
                {
                
                    uip_sr_node_t *link;
                    link = uip_sr_node_head();

                    sprintf(str, "\"" "totLs"   "\"" ":" "%u"   ,uip_sr_num_nodes()); if(seguard(buf, str)){return 1;} strcat(buf, str);

                    // ???????????????????????????????????????????????????????????????????
                    sprintf(str, ",");  if(seguard(buf, str)){return 1;} strcat(buf, str);
                    // ???????????????????????????????????????????????????????????????????

                    // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
                    // !(uip_sr_num_nodes() > 0) ////////////////////////////////////////////////////////////////
                    // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
                    // SUBARRAY START rtLS{} > ls[] /////////////////////////////////////////////////////////////
                    // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
                    sprintf(str, "\"" "ls" "\"" ":"); if(seguard(buf, str)){return 1;} strcat(buf, str); ////////
                    // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

                        // [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]
                        sprintf(str,"["); if(seguard(buf, str)){return 1;} strcat(buf, str);

                        uip_ipaddr_t child_ipaddr;  // DODAG root to -->
                        // uip_ipaddr_t parent_ipaddr; // <-- to

                        NETSTACK_ROUTING.get_sr_node_ipaddr(&child_ipaddr, link);
                        // NETSTACK_ROUTING.get_sr_node_ipaddr(&parent_ipaddr, link->parent);
                        
                        while(link != NULL) 
                        {
                            oar_json_uip_sr_links_count++;

                            // uip_sr_link_snprint(goa_buf, sizeof(goa_buf), link);
                            
                            oar_json_ipaddr_to_str(oar_json_ipaddr, &child_ipaddr);
                            sprintf(str,    "\""    "from"    "\""    ":" "\""    "%s"    "\""    ,oar_json_ipaddr   );  if(seguard(buf, str)){return 1;} strcat(buf, str);   sprintf(str, "," );  if(seguard(buf, str)){return 1;} strcat(buf, str);

                            if(link->parent == NULL)
                            {
                                sprintf(str, "\"" "root" "\"" ":" "true"); if(seguard(buf, str)){return 1;} strcat(buf, str); 
                            }
                            else
                            {
                                sprintf(str, "\"" "root" "\"" ":" "false"); if(seguard(buf, str)){return 1;} strcat(buf, str);
                            }

                            
                            if (oar_json_uip_sr_links_count != NBR_TABLE_CONF_MAX_NEIGHBORS)    { sprintf(str, "," );  if(seguard(buf, str)){return 1;} strcat(buf, str); }

                            link = uip_sr_node_next(link);
                        }

                        for (int j = oar_json_uip_sr_links_count; j < NBR_TABLE_CONF_MAX_NEIGHBORS; j++)
                        {
                            
                            sprintf(str, "null"); if(seguard(buf, str)){return 1;} strcat(buf, str);
                            
                            if (j != (NBR_TABLE_CONF_MAX_NEIGHBORS - 1)) { sprintf(str, "," );  if(seguard(buf, str)){return 1;} strcat(buf, str); };
                        }

                        sprintf(str, "]"); if(seguard(buf, str)){return 1;} strcat(buf, str);   
                        // [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]

                    // ::::::::::::::::::::::::::
                    // SUBARRAY END rtLS{} > ls[]
                    // ::::::::::::::::::::::::::
                }
                else
                {
                    sprintf(str, "\"" "totLs"   "\"" ":" "%u"   ,0); if(seguard(buf, str)){return 1;} strcat(buf, str);

                    // ???????????????????????????????????????????????????????????????????
                    sprintf(str, ",");  if(seguard(buf, str)){return 1;} strcat(buf, str);
                    // ???????????????????????????????????????????????????????????????????
                    
                    // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
                    // !(uip_sr_num_nodes() > 0) ////////////////////////////////////////////////////////////////
                    // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
                    // SUBARRAY START rtLS{} > ls[] /////////////////////////////////////////////////////////////
                    // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
                    sprintf(str, "\"" "ls" "\"" ":"); if(seguard(buf, str)){return 1;} strcat(buf, str); ////////
                    // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

                        // [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]
                        sprintf(str,"["); if(seguard(buf, str)){return 1;} strcat(buf, str);

                        for (int j = 0; j < NBR_TABLE_CONF_MAX_NEIGHBORS; j++)
                        {
                            
                            sprintf(str, "null"); if(seguard(buf, str)){return 1;} strcat(buf, str);
                            
                            if (j != (NBR_TABLE_CONF_MAX_NEIGHBORS - 1)) { sprintf(str, "," );  if(seguard(buf, str)){return 1;} strcat(buf, str); };
                        }
                        
                        sprintf(str, "]"); if(seguard(buf, str)){return 1;} strcat(buf, str);   
                        // [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]
                    
                    // ::::::::::::::::::::::::::
                    // SUBARRAY END rtLS{} > ls[]
                    // ::::::::::::::::::::::::::
                }

            // ######## (NETSTACK_CONF_WITH_IPV6)> (UIP_CONF_IPV6_RPL)######## (NETSTACK_CONF_WITH_IPV6)> (UIP_CONF_IPV6_RPL)######## (NETSTACK_CONF_WITH_IPV6)> (UIP_CONF_IPV6_RPL)######## (NETSTACK_CONF_WITH_IPV6)> (UIP_CONF_IPV6_RPL)######## 
            // ######## (NETSTACK_CONF_WITH_IPV6)>!(UIP_CONF_IPV6_RPL)######## (NETSTACK_CONF_WITH_IPV6)>!(UIP_CONF_IPV6_RPL)######## (NETSTACK_CONF_WITH_IPV6)>!(UIP_CONF_IPV6_RPL)######## (NETSTACK_CONF_WITH_IPV6)>!(UIP_CONF_IPV6_RPL)######## 
            #else

                sprintf(str, "\"" "rpl"     "\"" ":" "false"); if(seguard(buf, str)){return 1;} strcat(buf, str);

                // ???????????????????????????????????????????????????????????????????
                sprintf(str, ",");  if(seguard(buf, str)){return 1;} strcat(buf, str);
                // ???????????????????????????????????????????????????????????????????

                sprintf(str, "\"" "totLs"   "\"" ":" "null" ); if(seguard(buf, str)){return 1;} strcat(buf, str);

                // ???????????????????????????????????????????????????????????????????
                sprintf(str, ",");  if(seguard(buf, str)){return 1;} strcat(buf, str);
                // ???????????????????????????????????????????????????????????????????

                // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
                // SUBARRAY START rtLS{} > ls[] /////////////////////////////////////////////////////////////
                // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
                sprintf(str, "\"" "ls" "\"" ":"); if(seguard(buf, str)){return 1;} strcat(buf, str); ////////
                // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
                
                    // [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]
                    sprintf(str,"["); if(seguard(buf, str)){return 1;} strcat(buf, str);

                    for (int j = 0; j < NBR_TABLE_CONF_MAX_NEIGHBORS; j++)
                    {
                        
                        sprintf(str, "null"); if(seguard(buf, str)){return 1;} strcat(buf, str);
                        
                        if (j != (NBR_TABLE_CONF_MAX_NEIGHBORS - 1)) { sprintf(str, "," );  if(seguard(buf, str)){return 1;} strcat(buf, str); };
                    }
                        
                    sprintf(str, "]"); if(seguard(buf, str)){return 1;} strcat(buf, str);   
                    // [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]

            // ::::::::::::::::::::::::::
            // SUBARRAY END rtLS{} > ls[]
            // ::::::::::::::::::::::::::

            #endif
            // ######## (NETSTACK_CONF_WITH_IPV6)>!(UIP_CONF_IPV6_RPL)######## (NETSTACK_CONF_WITH_IPV6)>!(UIP_CONF_IPV6_RPL)######## (NETSTACK_CONF_WITH_IPV6)>!(UIP_CONF_IPV6_RPL)######## (NETSTACK_CONF_WITH_IPV6)>!(UIP_CONF_IPV6_RPL)########
            

        // ######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)########
        // ########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!
        #else

            sprintf(str, "\"" "IPv6" "\"" ":" "false"); if(seguard(buf, str)){return 1;} strcat(buf, str);

            // ???????????????????????????????????????????????????????????????????
            sprintf(str, ",");  if(seguard(buf, str)){return 1;} strcat(buf, str);
            // ??????????????????????????????????????????????????????????????????? 

            sprintf(str, "\"" "rpl"     "\"" ":" "null"); if(seguard(buf, str)){return 1;} strcat(buf, str);

            // ???????????????????????????????????????????????????????????????????
            sprintf(str, ",");  if(seguard(buf, str)){return 1;} strcat(buf, str);
            // ???????????????????????????????????????????????????????????????????

            sprintf(str, "\"" "totLs"   "\"" ":" "null"); if(seguard(buf, str)){return 1;} strcat(buf, str);

            // ???????????????????????????????????????????????????????????????????
            sprintf(str, ",");  if(seguard(buf, str)){return 1;} strcat(buf, str);
            // ???????????????????????????????????????????????????????????????????

            // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
            // SUBARRAY START rtLS{} > ls[] /////////////////////////////////////////////////////////////
            // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
            sprintf(str, "\"" "ls" "\"" ":"); if(seguard(buf, str)){return 1;} strcat(buf, str); ////////
            // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
            
                // [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]
                sprintf(str,"["); if(seguard(buf, str)){return 1;} strcat(buf, str);

                for (int j = 0; j < NBR_TABLE_CONF_MAX_NEIGHBORS; j++)
                {
                    
                    sprintf(str, "null"); if(seguard(buf, str)){return 1;} strcat(buf, str);
                    
                    if (j != (NBR_TABLE_CONF_MAX_NEIGHBORS - 1)) { sprintf(str, "," );  if(seguard(buf, str)){return 1;} strcat(buf, str); };
                }
                    
                sprintf(str, "]"); if(seguard(buf, str)){return 1;} strcat(buf, str);   
                // [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]

            // ::::::::::::::::::::::::::
            // SUBARRAY END rtLS{} > ls[]
            // ::::::::::::::::::::::::::

        #endif
        // ########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    sprintf(str, "}"); if(seguard(buf, str)){return 1;} strcat(buf, str); ///
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // SECTION END rtLS{} ///////////////////////////////////////////////////
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    return 0;
}
















// ####################################################################################################################
// MAIN FUNCTIONS >>>>> CONTINUE <<<<< ////////////////////////////////////////////////////////////////////////////////
// ####################################################################################################################

// ----------------------------------------------------------------------------------
// function that appends ROUTING LINK DESTINATIONS section to the json string ///////
// ----------------------------------------------------------------------------------

// {
// 	"pckt": {
// 		"valid": true,
// 		"error": null
// 	},
// 	"qId": 13,
// 	"id": {
// 		"sT": 41,
// 		"adr": "0012.4b00.0f83.b601"
// 	},
// 	"rtLD": {
// 		"IPv6": true,
// 		"rpl": true,
//      "totLs" : 0,
// 		"ls": ["null", "null", "null", "null", "null"]
// 	},
// 	"hash": 3790190472
// }

// Routing links (%u in total): ["&child_ipaddr ""/(DODAG root) |---> to &parent_ipaddr (lifetime: infinite/%lu seconds)", "null", "null", "null", "null"] <---|

static int oar_json_append_routing_link_destinations(char * buf)
{
    char str[128];

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // SECTION START rtLD{} /////////////////////////////////////////////////////////////////////
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    sprintf(str, "\"" "rtLD" "\"" ":"   ); if(seguard(buf, str)){return 1;} strcat(buf, str); ///   
    sprintf(str, "{"                    ); if(seguard(buf, str)){return 1;} strcat(buf, str); ///
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

        // ######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)########
        #if (NETSTACK_CONF_WITH_IPV6)

            sprintf(str, "\"" "IPv6" "\"" ":" "true"); if(seguard(buf, str)){return 1;} strcat(buf, str);

            // ???????????????????????????????????????????????????????????????????
            sprintf(str, ",");  if(seguard(buf, str)){return 1;} strcat(buf, str);
            // ??????????????????????????????????????????????????????????????????? 

            // ######## (NETSTACK_CONF_WITH_IPV6)> (UIP_CONF_IPV6_RPL)######## (NETSTACK_CONF_WITH_IPV6)> (UIP_CONF_IPV6_RPL)######## (NETSTACK_CONF_WITH_IPV6)> (UIP_CONF_IPV6_RPL)######## (NETSTACK_CONF_WITH_IPV6)> (UIP_CONF_IPV6_RPL)######## 
            #if (UIP_CONF_IPV6_RPL)

                sprintf(str, "\"" "rpl" "\"" ":" "true"); if(seguard(buf, str)){return 1;} strcat(buf, str);

                // ???????????????????????????????????????????????????????????????????
                sprintf(str, ",");  if(seguard(buf, str)){return 1;} strcat(buf, str);
                // ??????????????????????????????????????????????????????????????????? 

                int oar_json_uip_sr_links_count = 0;

                if (uip_sr_num_nodes() > 0)
                {
                
                    uip_sr_node_t *link;
                    link = uip_sr_node_head();

                    sprintf(str, "\"" "totLs"   "\"" ":" "%u"   ,uip_sr_num_nodes()); if(seguard(buf, str)){return 1;} strcat(buf, str);

                    // ???????????????????????????????????????????????????????????????????
                    sprintf(str, ",");  if(seguard(buf, str)){return 1;} strcat(buf, str);
                    // ???????????????????????????????????????????????????????????????????

                    // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
                    // !(uip_sr_num_nodes() > 0) ////////////////////////////////////////////////////////////////
                    // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
                    // SUBARRAY START rtLD{} > ls[] /////////////////////////////////////////////////////////////
                    // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
                    sprintf(str, "\"" "ls" "\"" ":"); if(seguard(buf, str)){return 1;} strcat(buf, str); ////////
                    // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

                        // [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]
                        sprintf(str,"["); if(seguard(buf, str)){return 1;} strcat(buf, str);

                        // uip_ipaddr_t child_ipaddr;  // DODAG root to -->
                        uip_ipaddr_t parent_ipaddr; // <-- to

                        // NETSTACK_ROUTING.get_sr_node_ipaddr(&child_ipaddr, link);
                        NETSTACK_ROUTING.get_sr_node_ipaddr(&parent_ipaddr, link->parent);
                        
                        while(link != NULL) 
                        {
                            oar_json_uip_sr_links_count++;
                            

                            oar_json_ipaddr_to_str(oar_json_ipaddr, &parent_ipaddr);
                            sprintf(str,    "\""    "to"    "\""    ":" "\""    "%s"    "\""    ,oar_json_ipaddr   );  if(seguard(buf, str)){return 1;} strcat(buf, str);   sprintf(str, "," );  if(seguard(buf, str)){return 1;} strcat(buf, str);

                            if(link->lifetime != UIP_SR_INFINITE_LIFETIME)
                            {
                                sprintf(str, "\"" "lf" "\"" ":" "%lu"                   ,(unsigned long)link->lifetime  ); if(seguard(buf, str)){return 1;} strcat(buf, str); 
                            }
                            else
                            {
                                sprintf(str, "\"" "lf" "\"" ":" "\"" "infinite" "\""                                    ); if(seguard(buf, str)){return 1;} strcat(buf, str); 
                            }

                            
                            if (oar_json_uip_sr_links_count != NBR_TABLE_CONF_MAX_NEIGHBORS)    { sprintf(str, "," );  if(seguard(buf, str)){return 1;} strcat(buf, str); }

                            link = uip_sr_node_next(link);
                        }

                        for (int j = oar_json_uip_sr_links_count; j < NBR_TABLE_CONF_MAX_NEIGHBORS; j++)
                        {
                            
                            sprintf(str, "null"); if(seguard(buf, str)){return 1;} strcat(buf, str);
                            
                            if (j != (NBR_TABLE_CONF_MAX_NEIGHBORS - 1)) { sprintf(str, "," );  if(seguard(buf, str)){return 1;} strcat(buf, str); };
                        }

                        sprintf(str, "]"); if(seguard(buf, str)){return 1;} strcat(buf, str);   
                        // [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]

                    // ::::::::::::::::::::::::::
                    // SUBARRAY END rtLD{} > ls[]
                    // ::::::::::::::::::::::::::
                }
                else
                {
                    sprintf(str, "\"" "totLs"   "\"" ":" "%u"   ,0); if(seguard(buf, str)){return 1;} strcat(buf, str);

                    // ???????????????????????????????????????????????????????????????????
                    sprintf(str, ",");  if(seguard(buf, str)){return 1;} strcat(buf, str);
                    // ???????????????????????????????????????????????????????????????????
                    
                    // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
                    // !(uip_sr_num_nodes() > 0) ////////////////////////////////////////////////////////////////
                    // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
                    // SUBARRAY START rtLD{} > ls[] /////////////////////////////////////////////////////////////
                    // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
                    sprintf(str, "\"" "ls" "\"" ":"); if(seguard(buf, str)){return 1;} strcat(buf, str); ////////
                    // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

                        // [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]
                        sprintf(str,"["); if(seguard(buf, str)){return 1;} strcat(buf, str);

                        for (int j = 0; j < NBR_TABLE_CONF_MAX_NEIGHBORS; j++)
                        {
                            
                            sprintf(str, "null"); if(seguard(buf, str)){return 1;} strcat(buf, str);
                            
                            if (j != (NBR_TABLE_CONF_MAX_NEIGHBORS - 1)) { sprintf(str, "," );  if(seguard(buf, str)){return 1;} strcat(buf, str); };
                        }
                        
                        sprintf(str, "]"); if(seguard(buf, str)){return 1;} strcat(buf, str);   
                        // [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]
                    
                    // ::::::::::::::::::::::::::
                    // SUBARRAY END rtLD{} > ls[]
                    // ::::::::::::::::::::::::::
                }

            // ######## (NETSTACK_CONF_WITH_IPV6)> (UIP_CONF_IPV6_RPL)######## (NETSTACK_CONF_WITH_IPV6)> (UIP_CONF_IPV6_RPL)######## (NETSTACK_CONF_WITH_IPV6)> (UIP_CONF_IPV6_RPL)######## (NETSTACK_CONF_WITH_IPV6)> (UIP_CONF_IPV6_RPL)######## 
            // ######## (NETSTACK_CONF_WITH_IPV6)>!(UIP_CONF_IPV6_RPL)######## (NETSTACK_CONF_WITH_IPV6)>!(UIP_CONF_IPV6_RPL)######## (NETSTACK_CONF_WITH_IPV6)>!(UIP_CONF_IPV6_RPL)######## (NETSTACK_CONF_WITH_IPV6)>!(UIP_CONF_IPV6_RPL)######## 
            #else

                sprintf(str, "\"" "rpl"     "\"" ":" "false"); if(seguard(buf, str)){return 1;} strcat(buf, str);

                // ???????????????????????????????????????????????????????????????????
                sprintf(str, ",");  if(seguard(buf, str)){return 1;} strcat(buf, str);
                // ???????????????????????????????????????????????????????????????????

                sprintf(str, "\"" "totLs"   "\"" ":" "null"); if(seguard(buf, str)){return 1;} strcat(buf, str);

                // ???????????????????????????????????????????????????????????????????
                sprintf(str, ",");  if(seguard(buf, str)){return 1;} strcat(buf, str);
                // ??????????????????????????????????????????????????????????????????? 

                // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
                // SUBARRAY START net{} > rtLD{} > ls[] /////////////////////////////////////////////////////
                // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
                sprintf(str, "\"" "ls" "\"" ":"); if(seguard(buf, str)){return 1;} strcat(buf, str); ////////
                // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
                
                    // [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]
                    sprintf(str,"["); if(seguard(buf, str)){return 1;} strcat(buf, str);

                    for (int j = 0; j < NBR_TABLE_CONF_MAX_NEIGHBORS; j++)
                    {
                        
                        sprintf(str, "null"); if(seguard(buf, str)){return 1;} strcat(buf, str);
                        
                        if (j != (NBR_TABLE_CONF_MAX_NEIGHBORS - 1)) { sprintf(str, "," );  if(seguard(buf, str)){return 1;} strcat(buf, str); };
                    }
                        
                    sprintf(str, "]"); if(seguard(buf, str)){return 1;} strcat(buf, str);   
                    // [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]

                // ::::::::::::::::::::::::::
                // SUBARRAY END rtLD{} > ls[]
                // ::::::::::::::::::::::::::

            #endif
            // ######## (NETSTACK_CONF_WITH_IPV6)>!(UIP_CONF_IPV6_RPL)######## (NETSTACK_CONF_WITH_IPV6)>!(UIP_CONF_IPV6_RPL)######## (NETSTACK_CONF_WITH_IPV6)>!(UIP_CONF_IPV6_RPL)######## (NETSTACK_CONF_WITH_IPV6)>!(UIP_CONF_IPV6_RPL)########
            

        // ######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)########
        // ########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!
        #else

            sprintf(str, "\"" "IPv6" "\"" ":" "false"); if(seguard(buf, str)){return 1;} strcat(buf, str);

            // ???????????????????????????????????????????????????????????????????
            sprintf(str, ",");  if(seguard(buf, str)){return 1;} strcat(buf, str);
            // ??????????????????????????????????????????????????????????????????? 

            sprintf(str, "\"" "rpl"     "\"" ":" "null"); if(seguard(buf, str)){return 1;} strcat(buf, str);

            // ???????????????????????????????????????????????????????????????????
            sprintf(str, ",");  if(seguard(buf, str)){return 1;} strcat(buf, str);
            // ???????????????????????????????????????????????????????????????????

            sprintf(str, "\"" "totLs"   "\"" ":" "null"); if(seguard(buf, str)){return 1;} strcat(buf, str);

            // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
            // SUBARRAY START rtLD{} > ls[] /////////////////////////////////////////////////////////////
            // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
            sprintf(str, "\"" "ls" "\"" ":"); if(seguard(buf, str)){return 1;} strcat(buf, str); ////////
            // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
            
                // [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]
                sprintf(str,"["); if(seguard(buf, str)){return 1;} strcat(buf, str);

                for (int j = 0; j < NBR_TABLE_CONF_MAX_NEIGHBORS; j++)
                {
                    
                    sprintf(str, "null"); if(seguard(buf, str)){return 1;} strcat(buf, str);
                    
                    if (j != (NBR_TABLE_CONF_MAX_NEIGHBORS - 1)) { sprintf(str, "," );  if(seguard(buf, str)){return 1;} strcat(buf, str); };
                }
                    
                sprintf(str, "]"); if(seguard(buf, str)){return 1;} strcat(buf, str);   
                // [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]

            // ::::::::::::::::::::::::::
            // SUBARRAY END rtLD{} > ls[]
            // ::::::::::::::::::::::::::

        #endif
        // ########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    sprintf(str, "}"); if(seguard(buf, str)){return 1;} strcat(buf, str); ///
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // SECTION END rtLs{} ///////////////////////////////////////////////////
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    return 0;
}
















// ####################################################################################################################
// MAIN FUNCTIONS >>>>> CONTINUE <<<<< ////////////////////////////////////////////////////////////////////////////////
// ####################################################################################################################

// ----------------------------------------------------------------------------------
// function that appends ROUTING ENTRY ROUTES section to the json string ////////////
// ----------------------------------------------------------------------------------

// {
// 	"pckt": {
// 		"valid": true,
// 		"error": null
// 	},
// 	"qId": 14,
// 	"id": {
// 		"sT": 43,
// 		"adr": "0012.4b00.0f83.b601"
// 	},
// 	"rtERt": {
// 		"IPv6": true,
// 		"maxRtsN0": false,
// 		"totEs": null,
// 		"es": ["null", "null", "null", "null", "null"]
// 	},
// 	"hash": 3790190472
// }

// |---> Routing entries (%u in total): ["-- &route->ipaddr <---| via uip_ds6_route_nexthop(route) (lifetime: infinite/%lu seconds)", "null", "null", "null", "null"]

static int oar_json_append_routing_entry_routes(char * buf)
{
    char str[128];

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // SECTION START rtEs{} /////////////////////////////////////////////////////////////////////
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    sprintf(str, "\"" "rtERt" "\"" ":"  ); if(seguard(buf, str)){return 1;} strcat(buf, str); ///  
    sprintf(str, "{"                    ); if(seguard(buf, str)){return 1;} strcat(buf, str); ///
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

        // ######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)########
        #if (NETSTACK_CONF_WITH_IPV6)

            sprintf(str, "\"" "IPv6" "\"" ":" "true"); if(seguard(buf, str)){return 1;} strcat(buf, str);

            // ???????????????????????????????????????????????????????????????????
            sprintf(str, ",");  if(seguard(buf, str)){return 1;} strcat(buf, str);
            // ???????????????????????????????????????????????????????????????????

            // ######## (NETSTACK_CONF_WITH_IPV6)> (UIP_MAX_ROUTES != 0)######## (NETSTACK_CONF_WITH_IPV6)> (UIP_MAX_ROUTES != 0)######## (NETSTACK_CONF_WITH_IPV6)> (UIP_MAX_ROUTES != 0)######## (NETSTACK_CONF_WITH_IPV6)> (UIP_MAX_ROUTES != 0)######## 
            #if (UIP_MAX_ROUTES != 0)

                sprintf(str, "\"" "maxRtsN0" "\"" ":" "true"); if(seguard(buf, str)){return 1;} strcat(buf, str);

                // ???????????????????????????????????????????????????????????????????
                sprintf(str, ",");  if(seguard(buf, str)){return 1;} strcat(buf, str);
                // ???????????????????????????????????????????????????????????????????

                if(uip_ds6_route_num_routes() > 0)
                {
                    uip_ds6_route_t *route;
                    sprintf(str, "\"" "totEs" "\"" ":" "%u" ,uip_ds6_route_num_routes()); if(seguard(buf, str)){return 1;} strcat(buf, str);

                    // ???????????????????????????????????????????????????????????????????
                    sprintf(str, ",");  if(seguard(buf, str)){return 1;} strcat(buf, str);
                    // ??????????????????????????????????????????????????????????????????? 

                    route = uip_ds6_route_head();
                    int oar_json_ds6_route_count = 0;

                    // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
                    //  (uip_ds6_route_num_routes() > 0) ////////////////////////////////////////////////////////
                    // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
                    // SUBARRAY START rtEs{} > es[] /////////////////////////////////////////////////////////////
                    // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
                    sprintf(str, "\"" "es" "\"" ":"); if(seguard(buf, str)){return 1;} strcat(buf, str); ////////
                    // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

                        // [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]
                        sprintf(str,"["); if(seguard(buf, str)){return 1;} strcat(buf, str);
                        
                        while(route != NULL) 
                        {
                            oar_json_ds6_route_count++;

                            // {{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}
                            sprintf(str, "{"); if(seguard(buf, str)){return 1;} strcat(buf, str);

                                oar_json_ipaddr_to_str(oar_json_ipaddr, &route->ipaddr);
                                sprintf(str,    "\""    "rt"     "\""    ":" "\""    "%s"    "\""    ,oar_json_ipaddr); if(seguard(buf, str)){return 1;} strcat(buf, str);    

                            // {{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}
                            sprintf(str, "}"); if(seguard(buf, str)){return 1;} strcat(buf, str);
                        
                            if (oar_json_ds6_route_count != NBR_TABLE_CONF_MAX_NEIGHBORS)    { sprintf(str, "," );  if(seguard(buf, str)){return 1;} strcat(buf, str); }
                        }

                        for (int j = oar_json_ds6_route_count; j < NBR_TABLE_CONF_MAX_NEIGHBORS; j++)
                        {
                            
                            sprintf(str, "null"); if(seguard(buf, str)){return 1;} strcat(buf, str);
                            
                            if (j != (NBR_TABLE_CONF_MAX_NEIGHBORS - 1)) { sprintf(str, "," );  if(seguard(buf, str)){return 1;} strcat(buf, str); };
                        }

                        sprintf(str, "]"); if(seguard(buf, str)){return 1;} strcat(buf, str);
                        // [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]
                    
                    // ::::::::::::::::::::::::::
                    // SUBARRAY END rtEs{} > es[]
                    // ::::::::::::::::::::::::::
                }
                else
                {
                    sprintf(str, "\"" "totEs" "\"" ":" "\"" "none" "\"" ); if(seguard(buf, str)){return 1;} strcat(buf, str);    
                        
                    // ???????????????????????????????????????????????????????????????????
                    sprintf(str, ",");  if(seguard(buf, str)){return 1;} strcat(buf, str);
                    // ??????????????????????????????????????????????????????????????????? 

                    // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
                    // !(uip_ds6_route_num_routes() > 0) ////////////////////////////////////////////////////////
                    // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
                    // SUBARRAY START rtEs{} > es[] /////////////////////////////////////////////////////////////
                    // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
                    sprintf(str, "\"" "es" "\"" ":"); if(seguard(buf, str)){return 1;} strcat(buf, str);
                    // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
                    
                        // [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]
                        sprintf(str,"["); if(seguard(buf, str)){return 1;} strcat(buf, str);

                        for (int j = 0; j < NBR_TABLE_CONF_MAX_NEIGHBORS; j++)
                        {
                            
                            sprintf(str, "null"); if(seguard(buf, str)){return 1;} strcat(buf, str);
                            
                            if (j != (NBR_TABLE_CONF_MAX_NEIGHBORS - 1)) { sprintf(str, "," );  if(seguard(buf, str)){return 1;} strcat(buf, str); };
                        }

                        sprintf(str, "]"); if(seguard(buf, str)){return 1;} strcat(buf, str);
                        // [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]

                    // ::::::::::::::::::::::::::
                    // SUBARRAY END rtEs{} > es[]
                    // ::::::::::::::::::::::::::
                }

            // ######## (NETSTACK_CONF_WITH_IPV6)> (UIP_MAX_ROUTES != 0)######## (NETSTACK_CONF_WITH_IPV6)> (UIP_MAX_ROUTES != 0)######## (NETSTACK_CONF_WITH_IPV6)> (UIP_MAX_ROUTES != 0)######## (NETSTACK_CONF_WITH_IPV6)> (UIP_MAX_ROUTES != 0)######## 
            // ######## (NETSTACK_CONF_WITH_IPV6)>!(UIP_MAX_ROUTES != 0)######## (NETSTACK_CONF_WITH_IPV6)>!(UIP_MAX_ROUTES != 0)######## (NETSTACK_CONF_WITH_IPV6)>!(UIP_MAX_ROUTES != 0)######## (NETSTACK_CONF_WITH_IPV6)>!(UIP_MAX_ROUTES != 0)######## 
            #else

                sprintf(str, "\"" "maxRtsN0" "\"" ":" "false"); if(seguard(buf, str)){return 1;} strcat(buf, str);

                // ???????????????????????????????????????????????????????????????????
                sprintf(str, ",");  if(seguard(buf, str)){return 1;} strcat(buf, str);
                // ???????????????????????????????????????????????????????????????????

                sprintf(str, "\"" "totEs" "\"" ":" "null" ); if(seguard(buf, str)){return 1;} strcat(buf, str); 

                // ???????????????????????????????????????????????????????????????????
                sprintf(str, ",");  if(seguard(buf, str)){return 1;} strcat(buf, str);
                // ??????????????????????????????????????????????????????????????????? 

                // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
                // SUBARRAY START rtEs{} > es[] /////////////////////////////////////////////////////////////
                // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
                sprintf(str, "\"" "es" "\"" ":"); if(seguard(buf, str)){return 1;} strcat(buf, str); ////////
                // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
                
                    // [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]
                    sprintf(str,"["); if(seguard(buf, str)){return 1;} strcat(buf, str);

                    for (int j = 0; j < NBR_TABLE_CONF_MAX_NEIGHBORS; j++)
                    {
                        
                        sprintf(str, "null"); if(seguard(buf, str)){return 1;} strcat(buf, str);
                        
                        if (j != (NBR_TABLE_CONF_MAX_NEIGHBORS - 1)) { sprintf(str, "," );  if(seguard(buf, str)){return 1;} strcat(buf, str); };
                    }

                    sprintf(str, "]"); if(seguard(buf, str)){return 1;} strcat(buf, str);
                    // [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]
                
                // ::::::::::::::::::::::::::
                // SUBARRAY END rtEs{} > es[]
                // ::::::::::::::::::::::::::

            #endif
            // ######## (NETSTACK_CONF_WITH_IPV6)>!(UIP_MAX_ROUTES != 0)######## (NETSTACK_CONF_WITH_IPV6)>!(UIP_MAX_ROUTES != 0)######## (NETSTACK_CONF_WITH_IPV6)>!(UIP_MAX_ROUTES != 0)######## (NETSTACK_CONF_WITH_IPV6)>!(UIP_MAX_ROUTES != 0)######## 

        // ######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)########
        // ########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!
        #else

            sprintf(str, "\"" "IPv6" "\"" ":" "false"); if(seguard(buf, str)){return 1;} strcat(buf, str);

            // ???????????????????????????????????????????????????????????????????
            sprintf(str, ",");  if(seguard(buf, str)){return 1;} strcat(buf, str);
            // ???????????????????????????????????????????????????????????????????

            sprintf(str, "\"" "maxRtsN0" "\"" ":" "null"); if(seguard(buf, str)){return 1;} strcat(buf, str);

                // ???????????????????????????????????????????????????????????????????
                sprintf(str, ",");  if(seguard(buf, str)){return 1;} strcat(buf, str);
                // ???????????????????????????????????????????????????????????????????

                sprintf(str, "\"" "totEs" "\"" ":" "null" ); if(seguard(buf, str)){return 1;} strcat(buf, str); 

                // ???????????????????????????????????????????????????????????????????
                sprintf(str, ",");  if(seguard(buf, str)){return 1;} strcat(buf, str);
                // ??????????????????????????????????????????????????????????????????? 

                // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
                // SUBARRAY START net{} > routes{} > routingEntries{} > entries[] //////////////////////////
                // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
                sprintf(str, "\"" "es" "\"" ":"); if(seguard(buf, str)){return 1;} strcat(buf, str); ////////
                // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
                
                    // [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]
                    sprintf(str,"["); if(seguard(buf, str)){return 1;} strcat(buf, str);

                    for (int j = 0; j < NBR_TABLE_CONF_MAX_NEIGHBORS; j++)
                    {
                        
                        sprintf(str, "null"); if(seguard(buf, str)){return 1;} strcat(buf, str);
                        
                        if (j != (NBR_TABLE_CONF_MAX_NEIGHBORS - 1)) { sprintf(str, "," );  if(seguard(buf, str)){return 1;} strcat(buf, str); };
                    }

                    sprintf(str, "]"); if(seguard(buf, str)){return 1;} strcat(buf, str);
                    // [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]

                // ::::::::::::::::::::::::::
                // SUBARRAY END rtEs{} > es[]
                // ::::::::::::::::::::::::::
        
        #endif
        // ########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    sprintf(str, "}"); if(seguard(buf, str)){return 1;} strcat(buf, str); ///
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // SECTION END rtEs{} ///////////////////////////////////////////////////
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    return 0;
}
















// ####################################################################################################################
// MAIN FUNCTIONS >>>>> CONTINUE <<<<< ////////////////////////////////////////////////////////////////////////////////
// ####################################################################################################################

// ----------------------------------------------------------------------------------
// function that appends ROUTING ENTRY VIAs section to the json string ////////////
// ----------------------------------------------------------------------------------

// {
// 	"pckt": {
// 		"valid": true,
// 		"error": null
// 	},
// 	"qId": 15,
// 	"id": {
// 		"sT": 45,
// 		"adr": "0012.4b00.0f83.b601"
// 	},
// 	"rtEVia": {
// 		"IPv6": true,
// 		"maxRtsN0": false,
// 		"totEs": null,
// 		"es": ["null", "null", "null", "null", "null"]
// 	},
// 	"hash": 3790190472
// }

// Routing entries (%u in total): ["&route->ipaddr |---> via uip_ds6_route_nexthop(route) (lifetime: infinite/%lu seconds) <---| ", "null", "null", "null", "null"]

static int oar_json_append_routing_entry_vias(char * buf)
{
    char str[128];

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // SECTION START rtEs{} /////////////////////////////////////////////////////////////////////
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    sprintf(str, "\"" "rtEVia" "\"" ":" ); if(seguard(buf, str)){return 1;} strcat(buf, str); ///  
    sprintf(str, "{"                    ); if(seguard(buf, str)){return 1;} strcat(buf, str); ///
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

        // ######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)########
        #if (NETSTACK_CONF_WITH_IPV6)

            sprintf(str, "\"" "IPv6" "\"" ":" "true"); if(seguard(buf, str)){return 1;} strcat(buf, str);

            // ???????????????????????????????????????????????????????????????????
            sprintf(str, ",");  if(seguard(buf, str)){return 1;} strcat(buf, str);
            // ???????????????????????????????????????????????????????????????????

            // ######## (NETSTACK_CONF_WITH_IPV6)> (UIP_MAX_ROUTES != 0)######## (NETSTACK_CONF_WITH_IPV6)> (UIP_MAX_ROUTES != 0)######## (NETSTACK_CONF_WITH_IPV6)> (UIP_MAX_ROUTES != 0)######## (NETSTACK_CONF_WITH_IPV6)> (UIP_MAX_ROUTES != 0)######## 
            #if (UIP_MAX_ROUTES != 0)

                sprintf(str, "\"" "maxRtsN0" "\"" ":" "true"); if(seguard(buf, str)){return 1;} strcat(buf, str);

                // ???????????????????????????????????????????????????????????????????
                sprintf(str, ",");  if(seguard(buf, str)){return 1;} strcat(buf, str);
                // ???????????????????????????????????????????????????????????????????

                if(uip_ds6_route_num_routes() > 0)
                {
                    uip_ds6_route_t *route;
                    sprintf(str, "\"" "totEs" "\"" ":" "%u" ,uip_ds6_route_num_routes()); if(seguard(buf, str)){return 1;} strcat(buf, str);

                    // ???????????????????????????????????????????????????????????????????
                    sprintf(str, ",");  if(seguard(buf, str)){return 1;} strcat(buf, str);
                    // ??????????????????????????????????????????????????????????????????? 

                    route = uip_ds6_route_head();
                    int oar_json_ds6_route_count = 0;

                    // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
                    //  (uip_ds6_route_num_routes() > 0) ////////////////////////////////////////////////////////
                    // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
                    // SUBARRAY START rtEs{} > es[] /////////////////////////////////////////////////////////////
                    // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
                    sprintf(str, "\"" "es" "\"" ":"); if(seguard(buf, str)){return 1;} strcat(buf, str); ////////
                    // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

                        // [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]
                        sprintf(str,"["); if(seguard(buf, str)){return 1;} strcat(buf, str);
                        
                        while(route != NULL) 
                        {
                            oar_json_ds6_route_count++;

                            // {{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}
                            sprintf(str, "{"); if(seguard(buf, str)){return 1;} strcat(buf, str);

                                oar_json_ipaddr_to_str(oar_json_ipaddr, uip_ds6_route_nexthop(route));
                                sprintf(str,    "\""    "via"       "\""    ":" "\""    "%s"    "\""    ,oar_json_ipaddr); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, "," );  if(seguard(buf, str)){return 1;} strcat(buf, str);

                                if ((unsigned long)route->state.lifetime != 0xFFFFFFFF) { sprintf(str,  "\""  "lf"    "\""    ":"         "%u"                ,(unsigned long)route->state.lifetime); if(seguard(buf, str)){return 1;} strcat(buf, str); }
                                else                                                    { sprintf(str,  "\""  "lf"    "\""    ":" "\""    "infinite"  "\""                                         ); if(seguard(buf, str)){return 1;} strcat(buf, str); }

                            // {{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}
                            sprintf(str, "}"); if(seguard(buf, str)){return 1;} strcat(buf, str);
                        
                            if (oar_json_ds6_route_count != NBR_TABLE_CONF_MAX_NEIGHBORS)    { sprintf(str, "," );  if(seguard(buf, str)){return 1;} strcat(buf, str); }
                        }

                        for (int j = oar_json_ds6_route_count; j < NBR_TABLE_CONF_MAX_NEIGHBORS; j++)
                        {
                            
                            sprintf(str, "null"); if(seguard(buf, str)){return 1;} strcat(buf, str);
                            
                            if (j != (NBR_TABLE_CONF_MAX_NEIGHBORS - 1)) { sprintf(str, "," );  if(seguard(buf, str)){return 1;} strcat(buf, str); };
                        }

                        sprintf(str, "]"); if(seguard(buf, str)){return 1;} strcat(buf, str);
                        // [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]
                    
                    // ::::::::::::::::::::::::::
                    // SUBARRAY END rtEs{} > es[]
                    // ::::::::::::::::::::::::::
                }
                else
                {
                    sprintf(str, "\"" "totEs" "\"" ":" "\"" "none" "\"" ); if(seguard(buf, str)){return 1;} strcat(buf, str);    
                        
                    // ???????????????????????????????????????????????????????????????????
                    sprintf(str, ",");  if(seguard(buf, str)){return 1;} strcat(buf, str);
                    // ??????????????????????????????????????????????????????????????????? 

                    // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
                    // !(uip_ds6_route_num_routes() > 0) ////////////////////////////////////////////////////////
                    // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
                    // SUBARRAY START rtEs{} > es[] /////////////////////////////////////////////////////////////
                    // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
                    sprintf(str, "\"" "es" "\"" ":"); if(seguard(buf, str)){return 1;} strcat(buf, str); ////////
                    // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
                    
                        // [[[[[[[[[[[[[[[[]]]]]]]]]]]]]]]]
                        sprintf(str,"["); if(seguard(buf, str)){return 1;} strcat(buf, str);

                        for (int j = 0; j < NBR_TABLE_CONF_MAX_NEIGHBORS; j++)
                        {
                            
                            sprintf(str, "null"); if(seguard(buf, str)){return 1;} strcat(buf, str);
                            
                            if (j != (NBR_TABLE_CONF_MAX_NEIGHBORS - 1)) { sprintf(str, "," );  if(seguard(buf, str)){return 1;} strcat(buf, str); };
                        }

                        sprintf(str, "]"); if(seguard(buf, str)){return 1;} strcat(buf, str);
                        // [[[[[[[[[[[[[[[[[]]]]]]]]]]]]]]]]]

                    // ::::::::::::::::::::::::::
                    // SUBARRAY END rtEs{} > es[]
                    // ::::::::::::::::::::::::::
                }

            // ######## (NETSTACK_CONF_WITH_IPV6)> (UIP_MAX_ROUTES != 0)######## (NETSTACK_CONF_WITH_IPV6)> (UIP_MAX_ROUTES != 0)######## (NETSTACK_CONF_WITH_IPV6)> (UIP_MAX_ROUTES != 0)######## (NETSTACK_CONF_WITH_IPV6)> (UIP_MAX_ROUTES != 0)######## 
            // ######## (NETSTACK_CONF_WITH_IPV6)>!(UIP_MAX_ROUTES != 0)######## (NETSTACK_CONF_WITH_IPV6)>!(UIP_MAX_ROUTES != 0)######## (NETSTACK_CONF_WITH_IPV6)>!(UIP_MAX_ROUTES != 0)######## (NETSTACK_CONF_WITH_IPV6)>!(UIP_MAX_ROUTES != 0)######## 
            #else

                sprintf(str, "\"" "maxRtsN0" "\"" ":" "false"); if(seguard(buf, str)){return 1;} strcat(buf, str);

                // ???????????????????????????????????????????????????????????????????
                sprintf(str, ",");  if(seguard(buf, str)){return 1;} strcat(buf, str);
                // ???????????????????????????????????????????????????????????????????

                sprintf(str, "\"" "totEs" "\"" ":" "null" ); if(seguard(buf, str)){return 1;} strcat(buf, str); 

                // ???????????????????????????????????????????????????????????????????
                sprintf(str, ",");  if(seguard(buf, str)){return 1;} strcat(buf, str);
                // ??????????????????????????????????????????????????????????????????? 

                // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
                // SUBARRAY START rtEs{} > es[] /////////////////////////////////////////////////////////////
                // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
                sprintf(str, "\"" "es" "\"" ":"); if(seguard(buf, str)){return 1;} strcat(buf, str); ////////
                // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
                
                    // [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]
                    sprintf(str,"["); if(seguard(buf, str)){return 1;} strcat(buf, str);

                    for (int j = 0; j < NBR_TABLE_CONF_MAX_NEIGHBORS; j++)
                    {
                        
                        sprintf(str, "null"); if(seguard(buf, str)){return 1;} strcat(buf, str);
                        
                        if (j != (NBR_TABLE_CONF_MAX_NEIGHBORS - 1)) { sprintf(str, "," );  if(seguard(buf, str)){return 1;} strcat(buf, str); };
                    }

                    sprintf(str, "]"); if(seguard(buf, str)){return 1;} strcat(buf, str);
                    // [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]
                
                // ::::::::::::::::::::::::::
                // SUBARRAY END rtEs{} > es[]
                // ::::::::::::::::::::::::::

            #endif
            // ######## (NETSTACK_CONF_WITH_IPV6)>!(UIP_MAX_ROUTES != 0)######## (NETSTACK_CONF_WITH_IPV6)>!(UIP_MAX_ROUTES != 0)######## (NETSTACK_CONF_WITH_IPV6)>!(UIP_MAX_ROUTES != 0)######## (NETSTACK_CONF_WITH_IPV6)>!(UIP_MAX_ROUTES != 0)######## 

        // ######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)########
        // ########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!
        #else

            sprintf(str, "\"" "IPv6" "\"" ":" "false"); if(seguard(buf, str)){return 1;} strcat(buf, str);

            // ???????????????????????????????????????????????????????????????????
            sprintf(str, ",");  if(seguard(buf, str)){return 1;} strcat(buf, str);
            // ???????????????????????????????????????????????????????????????????

            sprintf(str, "\"" "maxRtsN0" "\"" ":" "null"); if(seguard(buf, str)){return 1;} strcat(buf, str);

                // ???????????????????????????????????????????????????????????????????
                sprintf(str, ",");  if(seguard(buf, str)){return 1;} strcat(buf, str);
                // ???????????????????????????????????????????????????????????????????

                sprintf(str, "\"" "totEs" "\"" ":" "null" ); if(seguard(buf, str)){return 1;} strcat(buf, str); 

                // ???????????????????????????????????????????????????????????????????
                sprintf(str, ",");  if(seguard(buf, str)){return 1;} strcat(buf, str);
                // ??????????????????????????????????????????????????????????????????? 

                // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
                // SUBARRAY START net{} > routes{} > routingEntries{} > entries[] ///////////////////////////
                // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
                sprintf(str, "\"" "es" "\"" ":"); if(seguard(buf, str)){return 1;} strcat(buf, str); ////////
                // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
                
                    // [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]
                    sprintf(str,"["); if(seguard(buf, str)){return 1;} strcat(buf, str);

                    for (int j = 0; j < NBR_TABLE_CONF_MAX_NEIGHBORS; j++)
                    {
                        
                        sprintf(str, "null"); if(seguard(buf, str)){return 1;} strcat(buf, str);
                        
                        if (j != (NBR_TABLE_CONF_MAX_NEIGHBORS - 1)) { sprintf(str, "," );  if(seguard(buf, str)){return 1;} strcat(buf, str); };
                    }

                    sprintf(str, "]"); if(seguard(buf, str)){return 1;} strcat(buf, str);
                    // [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]
        
        #endif
        // ########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    sprintf(str, "}"); if(seguard(buf, str)){return 1;} strcat(buf, str); ///
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // SECTION END rtEs{} ///////////////////////////////////////////////////
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    return 0;
}
















// ####################################################################################################################
// MAIN FUNCTIONS >>>>> CONTINUE <<<<< ////////////////////////////////////////////////////////////////////////////////
// ####################################################################################################################

// ----------------------------------------------------------------------------
// function that appends RPL STATUS section to the json string ////////////////
// ----------------------------------------------------------------------------

// {
// 	"pckt": {
// 		"valid": true,
// 		"error": null
// 	},
// 	"qId": 16,
// 	"id": {
// 		"sT": 47,
// 		"adr": "0012.4b00.0f83.b601"
// 	},
// 	"rSt": {
// 		"rL": true,
// 		"iId": 0,
// 		"mop": "Non-storing",
// 		"of": "MRHOF",
// 		"hRkI": 128,
// 		"dLt": 1800,
// 		"dtsnO": 240
// 	},
// 	"hash": 3790190472
// }

// RPL status: -- Instance: None/   %u -- DAG   root/node -- DAG:   %s, version   %u -- Prefix: %s/ %u -- MOP  %s -- OF:   %s -- Hop rank increment:   %u -- Default lifetime: %lu seconds -- State:   %s -- Preferred parent:  %s  (last DTSN:    %u)/None -- Rank:   %u -- Lowest rank:  %u (    %u) -- DTSN out:    %u -- DAO sequence: last sent   %u, last acked  %u -- Trickle timer: current    %u, min     %u, max     %u, redundancy  %u
//                                  iId                                                                        mop         of                          hRkI                    dLt                                                                                                                                 dO

static int oar_json_append_rpl_status(char * buf)
{
    char str[128];
    
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // SECTION START rSt{} //////////////////////////////////////////////////////////////////////
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    sprintf(str, "\"" "rSt" "\"" ":"    ); if(seguard(buf, str)){return 1;} strcat(buf, str); ///   
    sprintf(str, "{"                    ); if(seguard(buf, str)){return 1;} strcat(buf, str); ///
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

        // ######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)########
        #if (ROUTING_CONF_RPL_LITE)

            sprintf(str, "\"" "rL" "\"" ":" "true");  if(seguard(buf, str)){return 1;} strcat(buf, str);

            // ???????????????????????????????????????????????????????????????????
            sprintf(str, ",");  if(seguard(buf, str)){return 1;} strcat(buf, str);
            // ??????????????????????????????????????????????????????????????????? 

            if(!curr_instance.used)             
                { 
                    sprintf(str, "\"" "iId" "\"" ":" "\"" "none" "\""); if(seguard(buf, str)){return 1;} strcat(buf, str);
                    
                    // ???????????????????????????????????????????????????????????????????
                    sprintf(str, ",");  if(seguard(buf, str)){return 1;} strcat(buf, str);
                    // ??????????????????????????????????????????????????????????????????? 

                    sprintf(str, "\"" "mop"     "\"" ":" "null"); if(seguard(buf, str)){return 1;} strcat(buf, str); sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str);
                    sprintf(str, "\"" "of"      "\"" ":" "null"); if(seguard(buf, str)){return 1;} strcat(buf, str); sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str);
                    sprintf(str, "\"" "hRkI"    "\"" ":" "null"); if(seguard(buf, str)){return 1;} strcat(buf, str); sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str);
                    sprintf(str, "\"" "dLt"     "\"" ":" "null"); if(seguard(buf, str)){return 1;} strcat(buf, str); sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str);
                    sprintf(str, "\"" "dO"      "\"" ":" "null"); if(seguard(buf, str)){return 1;} strcat(buf, str);
                
                } 
                else                                
                { 
                    sprintf(str, "\"" "iId" "\"" ":" "%u" ,curr_instance.instance_id); if(seguard(buf, str)){return 1;} strcat(buf, str);

                    // ???????????????????????????????????????????????????????????????????
                    sprintf(str, ",");  if(seguard(buf, str)){return 1;} strcat(buf, str);
                    // ??????????????????????????????????????????????????????????????????? 

                    sprintf(str, "\"" "mop"     "\"" ":" "\""   "%s"    "\""    ,oar_json_rpl_mop_to_str(curr_instance.mop)       ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, "," ); if(seguard(buf, str)){return 1;} strcat(buf, str);
                    sprintf(str, "\"" "of"      "\"" ":" "\""   "%s"    "\""    ,oar_json_rpl_ocp_to_str(curr_instance.of->ocp)   ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, "," ); if(seguard(buf, str)){return 1;} strcat(buf, str);
                    sprintf(str, "\"" "hRkI"    "\"" ":"        "%u"            ,curr_instance.min_hoprankinc                               ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, "," ); if(seguard(buf, str)){return 1;} strcat(buf, str);
                    sprintf(str, "\"" "dLt"     "\"" ":"        "%lu"           ,RPL_LIFETIME(curr_instance.default_lifetime)               ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, "," ); if(seguard(buf, str)){return 1;} strcat(buf, str);
                    sprintf(str, "\"" "dtsnO"   "\"" ":"        "%u"            ,curr_instance.dtsn_out                                     ); if(seguard(buf, str)){return 1;} strcat(buf, str);    
            }

        // ######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)########
        // ########!(ROUTING_CONF_RPL_LITE)########!(ROUTING_CONF_RPL_LITE)########!(ROUTING_CONF_RPL_LITE)########!(ROUTING_CONF_RPL_LITE)########!(ROUTING_CONF_RPL_LITE)########!(ROUTING_CONF_RPL_LITE)########!
        #else

            sprintf(str, "\"" "rL" "\"" ":" "false");  if(seguard(buf, str)){return 1;} strcat(buf, str); 

            // ???????????????????????????????????????????????????????????????????
            sprintf(str, ",");  if(seguard(buf, str)){return 1;} strcat(buf, str);
            // ??????????????????????????????????????????????????????????????????? 

            sprintf(str, "\"" "iId"  "\"" ":" "null"); if(seguard(buf, str)){return 1;} strcat(buf, str);  

            // ???????????????????????????????????????????????????????????????????
            sprintf(str, ",");  if(seguard(buf, str)){return 1;} strcat(buf, str);
            // ??????????????????????????????????????????????????????????????????? 

            sprintf(str, "\"" "mop"     "\"" ":" "null"); if(seguard(buf, str)){return 1;} strcat(buf, str); sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str);
            sprintf(str, "\"" "of"      "\"" ":" "null"); if(seguard(buf, str)){return 1;} strcat(buf, str); sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str);
            sprintf(str, "\"" "hRkI"    "\"" ":" "null"); if(seguard(buf, str)){return 1;} strcat(buf, str); sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str);
            sprintf(str, "\"" "dLt"     "\"" ":" "null"); if(seguard(buf, str)){return 1;} strcat(buf, str); sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str);
            sprintf(str, "\"" "dtsnO"   "\"" ":" "null"); if(seguard(buf, str)){return 1;} strcat(buf, str); sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str);

        #endif
        // ########!(ROUTING_CONF_RPL_LITE)########!(ROUTING_CONF_RPL_LITE)########!(ROUTING_CONF_RPL_LITE)########!(ROUTING_CONF_RPL_LITE)########!(ROUTING_CONF_RPL_LITE)########!(ROUTING_CONF_RPL_LITE)########!
    
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    sprintf(str, "}"); if(seguard(buf, str)){return 1;} strcat(buf, str); ///
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // SUBSECTION END rSt{} /////////////////////////////////////////////////
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    return 0;
}
















// ####################################################################################################################
// MAIN FUNCTIONS >>>>> CONTINUE <<<<< ////////////////////////////////////////////////////////////////////////////////
// ####################################################################################################################

// ----------------------------------------------------------------------------
// function that appends RPL STATUS section to the json string ////////////////
// ----------------------------------------------------------------------------

// {
// 	"pckt": {
// 		"valid": true,
// 		"error": null
// 	},
// 	"qId": 17,
// 	"id": {
// 		"sT": 49,
// 		"adr": "0012.4b00.0f83.b601"
// 	},
// 	"rStDag": {
// 		"rL": true,
// 		"iId": 0,
// 		"dT": "node",
// 		"dId": "fd00::212:4b00:f24:8385",
// 		"dVer": 240,
// 		"dPf": "fd00::",
// 		"dPfL": 64,
// 		"st": "Reachable",
// 		"pP": "fe80::212:4b00:f24:8385",
// 		"rk": 256,
// 		"lRk": 256,
// 		"mRkI": 1024,
// 		"dao": {
// 			"lS": 241,
// 			"lA": 241
// 		}
// 	},
// 	"hash": 3790190472
// }

// RPL status: -- Instance: None/   %u -- DAG   root/node -- DAG:   %s, version   %u -- Prefix: %s/ %u -- MOP    %s -- OF:   %s -- Hop rank increment:   %u -- Default lifetime: %lu seconds -- State:   %s -- Preferred parent:    %s  (last DTSN:    %u)/None -- Rank:   %u -- Lowest rank:  %u (    %u) -- DTSN out:    %u -- DAO sequence: last sent   %u, last acked  %u -- Trickle timer: current    %u, min     %u, max     %u, redundancy  %u
//                                  iId         dT                  dId           dVer          dPf dPfL                                                                                                 st                         pP                                     rk                  lRk     mRkI                                                lS              lA

static int oar_json_append_rpl_status_dag(char * buf)
{
    char str[128];
    
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // SECTION START rStDag{} ///////////////////////////////////////////////////////////////////
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    sprintf(str, "\"" "rStDag" "\"" ":" ); if(seguard(buf, str)){return 1;} strcat(buf, str); ///  
    sprintf(str, "{"                    ); if(seguard(buf, str)){return 1;} strcat(buf, str); ///
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

        // ######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)########
        #if (ROUTING_CONF_RPL_LITE)

            sprintf(str, "\"" "rL" "\"" ":" "true");  if(seguard(buf, str)){return 1;} strcat(buf, str);

            // ???????????????????????????????????????????????????????????????????
            sprintf(str, ",");  if(seguard(buf, str)){return 1;} strcat(buf, str);
            // ???????????????????????????????????????????????????????????????????

            if(!curr_instance.used)             
            { 
                sprintf(str, "\"" "iId" "\"" ":" "\"" "none" "\""); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str);
                
                sprintf(str, "\"" "dT"      "\"" ":" "null" ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, "," ); if(seguard(buf, str)){return 1;} strcat(buf, str);
                sprintf(str, "\"" "dId"     "\"" ":" "null" ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, "," ); if(seguard(buf, str)){return 1;} strcat(buf, str);
                sprintf(str, "\"" "dVer"    "\"" ":" "null" ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, "," ); if(seguard(buf, str)){return 1;} strcat(buf, str);
                sprintf(str, "\"" "dPf"     "\"" ":" "null" ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, "," ); if(seguard(buf, str)){return 1;} strcat(buf, str);
                sprintf(str, "\"" "dPfL"    "\"" ":" "null" ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, "," ); if(seguard(buf, str)){return 1;} strcat(buf, str);
                sprintf(str, "\"" "st"      "\"" ":" "null" ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, "," ); if(seguard(buf, str)){return 1;} strcat(buf, str);
                sprintf(str, "\"" "pP"      "\"" ":" "null" ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, "," ); if(seguard(buf, str)){return 1;} strcat(buf, str);
                sprintf(str, "\"" "rk"      "\"" ":" "null" ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, "," ); if(seguard(buf, str)){return 1;} strcat(buf, str);
                sprintf(str, "\"" "lRk"     "\"" ":" "null" ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, "," ); if(seguard(buf, str)){return 1;} strcat(buf, str);
                sprintf(str, "\"" "mRkI"    "\"" ":" "null" ); if(seguard(buf, str)){return 1;} strcat(buf, str);    

                // ???????????????????????????????????????????????????????????????????
                sprintf(str, ",");  if(seguard(buf, str)){return 1;} strcat(buf, str);
                // ???????????????????????????????????????????????????????????????????
                    
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                // SUBSECTION START rStDag{} > dao{} ////////////////////////////////////////////////////////
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                sprintf(str, "\"" "dao" "\"" ":"    ); if(seguard(buf, str)){return 1;} strcat(buf, str); ///
                sprintf(str, "{"                    ); if(seguard(buf, str)){return 1;} strcat(buf, str); ///
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

                    sprintf(str, "\"" "lS"   "\"" ":" "null"     ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str);
                    sprintf(str, "\"" "lA"   "\"" ":" "null"     ); if(seguard(buf, str)){return 1;} strcat(buf, str);

                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                // SUSECTION END rStDag{} > dao{} ///////////////////////////////////////
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                sprintf(str, "}"); if(seguard(buf, str)){return 1;} strcat(buf, str); ///
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            }
            else
            {
                sprintf(str, "\"" "iId" "\"" ":" "%u" ,curr_instance.instance_id); if(seguard(buf, str)){return 1;} strcat(buf, str); sprintf(str, "," ); if(seguard(buf, str)){return 1;} strcat(buf, str);

                if(NETSTACK_ROUTING.node_is_root()) { sprintf(str, "\"" "dT" "\"" ":" "\"" "root" "\""); if(seguard(buf, str)){return 1;} strcat(buf, str); sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str); } 
                else                                { sprintf(str, "\"" "dT" "\"" ":" "\"" "node" "\""); if(seguard(buf, str)){return 1;} strcat(buf, str); sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str); } 
        
                oar_json_ipaddr_to_str(oar_json_ipaddr, &curr_instance.dag.dag_id);
                sprintf(str, "\"" "dId"     "\"" ":" "\""   "%s"    "\""    ,oar_json_ipaddr                                        ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str);
                
                sprintf(str, "\"" "dVer"    "\"" ":"        "%u"            ,curr_instance.dag.version                              ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str);

                oar_json_ipaddr_to_str(oar_json_ipaddr, &curr_instance.dag.prefix_info.prefix);
                sprintf(str, "\"" "dPf"     "\"" ":" "\""   "%s"    "\""    ,oar_json_ipaddr                                        ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str);
                
                sprintf(str, "\"" "dPfL"    "\"" ":"        "%u"            ,curr_instance.dag.prefix_info.length                   ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str);
                sprintf(str, "\"" "st"      "\"" ":" "\""   "%s"    "\""    ,oar_json_rpl_state_to_str(curr_instance.dag.state)     ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str);

                if (curr_instance.dag.preferred_parent) 
                {
                    oar_json_ipaddr_to_str(oar_json_ipaddr, rpl_neighbor_get_ipaddr(curr_instance.dag.preferred_parent));
                    sprintf(str, "\"" "pP"  "\"" ":" "\"" "%s"      "\""    ,oar_json_ipaddr    ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, "," ); if(seguard(buf, str)){return 1;} strcat(buf, str);
                }
                else
                {
                    sprintf(str, "\"" "pP" "\"" ":" "\"" "none"    "\""                              ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, "," ); if(seguard(buf, str)){return 1;} strcat(buf, str);
                }

                sprintf(str, "\"" "rk"      "\"" ":"          "%u"          ,curr_instance.dag.rank                                 ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str);
                sprintf(str, "\"" "lRk"     "\"" ":"          "%u"          ,curr_instance.dag.lowest_rank                          ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str);
                sprintf(str, "\"" "mRkI"    "\"" ":"          "%u"          ,curr_instance.max_rankinc                              ); if(seguard(buf, str)){return 1;} strcat(buf, str);    

                // ???????????????????????????????????????????????????????????????????
                sprintf(str, ",");  if(seguard(buf, str)){return 1;} strcat(buf, str);
                // ???????????????????????????????????????????????????????????????????        
                
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                // SUBSECTION START rStDag{} > dao{} ////////////////////////////////////////////////////////
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                sprintf(str, "\"" "dao" "\"" ":"    ); if(seguard(buf, str)){return 1;} strcat(buf, str); ///
                sprintf(str, "{"                    ); if(seguard(buf, str)){return 1;} strcat(buf, str); ///
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

                    sprintf(str, "\"" "lS"  "\"" ":" "%u"   ,curr_instance.dag.dao_last_seqno       ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str);
                    sprintf(str, "\"" "lA"  "\"" ":" "%u"   ,curr_instance.dag.dao_last_acked_seqno ); if(seguard(buf, str)){return 1;} strcat(buf, str);   

                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                // SUSECTION END rStDag{} > dao{} ///////////////////////////////////////
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                sprintf(str, "}"); if(seguard(buf, str)){return 1;} strcat(buf, str); ///
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            }

        // ######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)########
        // ########!(ROUTING_CONF_RPL_LITE)########!(ROUTING_CONF_RPL_LITE)########!(ROUTING_CONF_RPL_LITE)########!(ROUTING_CONF_RPL_LITE)########!(ROUTING_CONF_RPL_LITE)########!(ROUTING_CONF_RPL_LITE)########!
        #else

            sprintf(str, "\"" "rL" "\"" ":" "true");  if(seguard(buf, str)){return 1;} strcat(buf, str);

            // ???????????????????????????????????????????????????????????????????
            sprintf(str, ",");  if(seguard(buf, str)){return 1;} strcat(buf, str);
            // ???????????????????????????????????????????????????????????????????
            
            sprintf(str, "\"" "iId"  "\"" ":" "null"); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str);

            sprintf(str, "\"" "dT"      "\"" ":" "null"     ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, "," ); if(seguard(buf, str)){return 1;} strcat(buf, str);
            sprintf(str, "\"" "dId"     "\"" ":" "null"     ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, "," ); if(seguard(buf, str)){return 1;} strcat(buf, str);
            sprintf(str, "\"" "dVer"    "\"" ":" "null"     ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, "," ); if(seguard(buf, str)){return 1;} strcat(buf, str);
            sprintf(str, "\"" "dPf"     "\"" ":" "null"     ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, "," ); if(seguard(buf, str)){return 1;} strcat(buf, str);
            sprintf(str, "\"" "dPfL"    "\"" ":" "null"     ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, "," ); if(seguard(buf, str)){return 1;} strcat(buf, str);
            sprintf(str, "\"" "st"      "\"" ":" "null"     ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, "," ); if(seguard(buf, str)){return 1;} strcat(buf, str);
            sprintf(str, "\"" "pP"      "\"" ":" "null"     ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, "," ); if(seguard(buf, str)){return 1;} strcat(buf, str);
            sprintf(str, "\"" "rk"      "\"" ":" "null"     ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, "," ); if(seguard(buf, str)){return 1;} strcat(buf, str);
            sprintf(str, "\"" "lRk"     "\"" ":" "null"     ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, "," ); if(seguard(buf, str)){return 1;} strcat(buf, str);
            sprintf(str, "\"" "mRkI"    "\"" ":" "null"     ); if(seguard(buf, str)){return 1;} strcat(buf, str);    

            // ???????????????????????????????????????????????????????????????????
            sprintf(str, ",");  if(seguard(buf, str)){return 1;} strcat(buf, str);
            // ???????????????????????????????????????????????????????????????????

            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            // SUBSECTION START rStDag{} > dao{} ////////////////////////////////////////////////////////
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            sprintf(str, "\"" "dao" "\"" ":"    ); if(seguard(buf, str)){return 1;} strcat(buf, str); ///
            sprintf(str, "{"                    ); if(seguard(buf, str)){return 1;} strcat(buf, str); ///
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

                sprintf(str, "\"" "lS"   "\"" ":" "null"     ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str);
                sprintf(str, "\"" "lA"   "\"" ":" "null"     ); if(seguard(buf, str)){return 1;} strcat(buf, str);

            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            // SUSECTION END rStDag{} > dao{} ///////////////////////////////////////
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            sprintf(str, "}"); if(seguard(buf, str)){return 1;} strcat(buf, str); ///
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

        #endif
        // ########!(ROUTING_CONF_RPL_LITE)########!(ROUTING_CONF_RPL_LITE)########!(ROUTING_CONF_RPL_LITE)########!(ROUTING_CONF_RPL_LITE)########!(ROUTING_CONF_RPL_LITE)########!(ROUTING_CONF_RPL_LITE)########!
    
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    sprintf(str, "}"); if(seguard(buf, str)){return 1;} strcat(buf, str); ///
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // SUBSECTION END rStDag{} //////////////////////////////////////////////
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    return 0;
}
















// ####################################################################################################################
// MAIN FUNCTIONS >>>>> CONTINUE <<<<< ////////////////////////////////////////////////////////////////////////////////
// ####################################################################################################################

// ----------------------------------------------------------------------------
// function that appends RPL STATUS TRICKLE TIMER section to the json string //
// ----------------------------------------------------------------------------

// {
// 	"pckt": {
// 		"valid": true,
// 		"error": null
// 	},
// 	"qId": 18,
// 	"id": {
// 		"sT": 51,
// 		"adr": "0012.4b00.0f83.b601"
// 	},
// 	"rStTt": {
// 		"rL": true,
// 		"iId": "none",
// 		"cur": 15,
// 		"min": 12,
// 		"max": 20,
// 		"red": 0
// 	},
// 	"hash": 3790190472
// }

// RPL status: -- Instance: None/   %u -- DAG   root/node -- DAG:   %s, version   %u -- Prefix: %s/ %u -- MOP    %s -- OF:   %s -- Hop rank increment:   %u -- Default lifetime: %lu seconds -- State:   %s -- Preferred parent:    %s  (last DTSN:    %u)/None -- Rank:   %u -- Lowest rank:  %u (    %u) -- DTSN out:    %u -- DAO sequence: last sent   %u, last acked  %u -- Trickle timer: current    %u, min     %u, max     %u, redundancy  %u
//                                  iId                                                                                                                                                                                                                                                                                                                                                                    cur         min         max             red

static int oar_json_append_rpl_status_trickle_timer(char * buf)
{
    char str[128];
    
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // SECTION START rStTt{} ////////////////////////////////////////////////////////////////////
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    sprintf(str, "\"" "rStTt" "\"" ":"  ); if(seguard(buf, str)){return 1;} strcat(buf, str); ///   
    sprintf(str, "{"                    ); if(seguard(buf, str)){return 1;} strcat(buf, str); ///
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

        // ######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)########
        #if (ROUTING_CONF_RPL_LITE)

            sprintf(str, "\"" "rL" "\"" ":" "true");  if(seguard(buf, str)){return 1;} strcat(buf, str);

            // ???????????????????????????????????????????????????????????????????
            sprintf(str, ",");  if(seguard(buf, str)){return 1;} strcat(buf, str);
            // ???????????????????????????????????????????????????????????????????

            if(!curr_instance.used)             
            { 
                sprintf(str, "\"" "iId" "\"" ":" "\"" "none" "\""); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str);

                sprintf(str, "\"" "cur" "\"" ":" "null"     ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, "," ); if(seguard(buf, str)){return 1;} strcat(buf, str);
                sprintf(str, "\"" "min" "\"" ":" "null"     ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, "," ); if(seguard(buf, str)){return 1;} strcat(buf, str);
                sprintf(str, "\"" "max" "\"" ":" "null"     ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, "," ); if(seguard(buf, str)){return 1;} strcat(buf, str);
                sprintf(str, "\"" "red" "\"" ":" "null"     ); if(seguard(buf, str)){return 1;} strcat(buf, str);    
            }
            else
            {
                sprintf(str, "\"" "iId" "\"" ":" "\"" "none" "\""); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str);

                sprintf(str, "\"" "cur" "\"" ":" "%u"    ,curr_instance.dag.dio_intcurrent                       ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, "," ); if(seguard(buf, str)){return 1;} strcat(buf, str);
                sprintf(str, "\"" "min" "\"" ":" "%u"    ,curr_instance.dio_intmin                               ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, "," ); if(seguard(buf, str)){return 1;} strcat(buf, str);
                sprintf(str, "\"" "max" "\"" ":" "%u"    ,curr_instance.dio_intmin + curr_instance.dio_intdoubl  ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, "," ); if(seguard(buf, str)){return 1;} strcat(buf, str);
                sprintf(str, "\"" "red" "\"" ":" "%u"    ,curr_instance.dio_redundancy                           ); if(seguard(buf, str)){return 1;} strcat(buf, str);    
            }
            
        // ######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)########
        // ########!(ROUTING_CONF_RPL_LITE)########!(ROUTING_CONF_RPL_LITE)########!(ROUTING_CONF_RPL_LITE)########!(ROUTING_CONF_RPL_LITE)########!(ROUTING_CONF_RPL_LITE)########!(ROUTING_CONF_RPL_LITE)########!
        #else

        sprintf(str, "\"" "rL" "\"" ":" "false");  if(seguard(buf, str)){return 1;} strcat(buf, str);

        // ???????????????????????????????????????????????????????????????????
        sprintf(str, ",");  if(seguard(buf, str)){return 1;} strcat(buf, str);
        // ???????????????????????????????????????????????????????????????????

        sprintf(str, "\"" "iId" "\"" ":" "null"); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str);

        sprintf(str, "\"" "cur" "\"" ":" "null"     ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, "," ); if(seguard(buf, str)){return 1;} strcat(buf, str);
        sprintf(str, "\"" "nim" "\"" ":" "null"     ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, "," ); if(seguard(buf, str)){return 1;} strcat(buf, str);
        sprintf(str, "\"" "max" "\"" ":" "null"     ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, "," ); if(seguard(buf, str)){return 1;} strcat(buf, str);
        sprintf(str, "\"" "red" "\"" ":" "null"     ); if(seguard(buf, str)){return 1;} strcat(buf, str);    

    #endif
    // ########!(ROUTING_CONF_RPL_LITE)########!(ROUTING_CONF_RPL_LITE)########!(ROUTING_CONF_RPL_LITE)########!(ROUTING_CONF_RPL_LITE)########!(ROUTING_CONF_RPL_LITE)########!(ROUTING_CONF_RPL_LITE)########!
    
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    sprintf(str, "}"); if(seguard(buf, str)){return 1;} strcat(buf, str); ///
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // SUBSECTION END rStTt{} ///////////////////////////////////////////////
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    return 0;
}
















// ####################################################################################################################
// MAIN FUNCTIONS >>>>> CONTINUE <<<<< ////////////////////////////////////////////////////////////////////////////////
// ####################################################################################################################

// ----------------------------------------------------------------------------
// function that appends RPL NEIGBOR ADDR section to the json string //////////
// ----------------------------------------------------------------------------

// {
// 	"pckt": {
// 		"valid": true,
// 		"error": null
// 	},
// 	"qId": 19,
// 	"id": {
// 		"sT": 53,
// 		"adr": "0012.4b00.0f83.b601"
// 	},
// 	"rN": {
// 		"rL": true,
// 		"iId": true,
// 		"c": 3,
// 		"ns": [{
// 			"ad": "fe80::212:4b00:f24:8385"
// 		}, {
// 			"ad": "fe80::212:4b00:f82:da03"
// 		}, {
// 			"ad": "fe80::212:4b00:f82:a600"
// 		}, null, null]
// 	},
// 	"hash": 3790190472
// }

// RPL neighbor 1/3: |---> fe80::212:4b00:f24:8385 <---|  128,   128 =>   256 --  7 rbafp (last tx 0 min ago)
// RPL neighbor 2/3: |---> fe80::212:4b00:f82:a600 <---|  384,   128 =>   512 --  2   a   (last tx 0 min ago)
// RPL neighbor 3/3: |---> fe80::212:4b00:f82:da03 <---|  546,   128 =>   674 --  0   a   (no tx)


static int oar_json_append_rpl_neighbor(char * buf)
{
    char str[128];
    
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // SECTION START rN{} ///////////////////////////////////////////////////////////////////////
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    sprintf(str, "\"" "rN" "\"" ":"     ); if(seguard(buf, str)){return 1;} strcat(buf, str); ///  
    sprintf(str, "{"                    ); if(seguard(buf, str)){return 1;} strcat(buf, str); ///
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

        // ######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)########
        #if (ROUTING_CONF_RPL_LITE)

            sprintf(str, "\"" "rL" "\"" ":" "true");  if(seguard(buf, str)){return 1;} strcat(buf, str);

            // ???????????????????????????????????????????????????????????????????
            sprintf(str, ",");  if(seguard(buf, str)){return 1;} strcat(buf, str);
            // ???????????????????????????????????????????????????????????????????

            if (!curr_instance.used || rpl_neighbor_count() == 0)
            {
                
                if (!curr_instance.used)    { sprintf(str, "\"" "iId" "\"" ":" "false"  ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str); }
                else                        { sprintf(str, "\"" "iId" "\"" ":" "true"   ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str); }
            
                sprintf(str, "\"" "c" "\"" ":" "%u" ,rpl_neighbor_count()); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str);
                
                // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
                //  (!curr_instance.used || rpl_neighbor_count() == 0) //////////////////////////////////////
                // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
                // SUBARRAY START rN{} > ns[] ///////////////////////////////////////////////////////////////
                // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
                sprintf(str, "\"" "ns" "\"" ":");  if(seguard(buf, str)){return 1;} strcat(buf, str); ///////
                // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
                
                    // [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]
                    sprintf(str, "["); if(seguard(buf, str)){return 1;} strcat(buf, str);

                    for (int i = 0; i < NBR_TABLE_CONF_MAX_NEIGHBORS; i++)
                    {
                        sprintf(str,    "null"  );  if(seguard(buf, str)){return 1;} strcat(buf, str);
                        if (i != (NBR_TABLE_CONF_MAX_NEIGHBORS - 1)) { sprintf(str, "," );  if(seguard(buf, str)){return 1;} strcat(buf, str); } 
                    }

                    sprintf(str, "]"); if(seguard(buf, str)){return 1;} strcat(buf, str);
                    // [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]
                
                // :::::::::::::::::::::::
                // SUBARRAY END rN{} > ns
                // :::::::::::::::::::::::
            }
            else
            {
                
                rpl_nbr_t *nbr = nbr_table_head(rpl_neighbors);

                int oar_json_rpl_neighbor_count = 0;

                sprintf(str, "\"" "iId"     "\"" ":" "true"                         ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, "," ); if(seguard(buf, str)){return 1;} strcat(buf, str);
                sprintf(str, "\"" "c"       "\"" ":" "%u"   ,rpl_neighbor_count()   ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, "," ); if(seguard(buf, str)){return 1;} strcat(buf, str);

                // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
                // !(!curr_instance.used || rpl_neighbor_count() == 0) //////////////////////////////////////
                // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
                // SUBARRAY START rNR{} > ns[] //////////////////////////////////////////////////////////////
                // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
                sprintf(str, "\"" "ns" "\"" ":");  if(seguard(buf, str)){return 1;} strcat(buf, str); ///////
                // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
                
                    // [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]
                    sprintf(str, "["); if(seguard(buf, str)){return 1;} strcat(buf, str);

                    while(nbr != NULL)
                    {
                        oar_json_rpl_neighbor_count++; 
                        
                        // rpl_nbr_t *oar_json_rpl_nbr_best = best_parent(0);
                        // const struct link_stats *oar_json_rpl_nbr_stats = rpl_neighbor_get_link_stats(nbr);
                        // clock_time_t oar_json_rpl_nbr_clock_now = clock_time();

                        // {{{{{{{{{{{{{{{{{}}}}}}}}}}}}}}}}}
                        sprintf(str, "{" ); if(seguard(buf, str)){return 1;} strcat(buf, str);

                            oar_json_ipaddr_to_str(oar_json_ipaddr, rpl_neighbor_get_ipaddr(nbr));
                            sprintf(str, "\"" "ad"                              "\"" ":" "\""   "%s"    "\""       ,oar_json_ipaddr); if(seguard(buf, str)){return 1;} strcat(buf, str);
                            
                        sprintf(str,    "}" ); if(seguard(buf, str)){return 1;} strcat(buf, str);
                        // {{{{{{{{{{{{{{{{{}}}}}}}}}}}}}}}}}
                        
                        if (oar_json_rpl_neighbor_count < NBR_TABLE_CONF_MAX_NEIGHBORS) { sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str); }
                        nbr = nbr_table_next(rpl_neighbors, nbr);
                    }
                    
                    for (int i = oar_json_rpl_neighbor_count; i < NBR_TABLE_CONF_MAX_NEIGHBORS; i++)
                    {
                        sprintf(str, "null"); if(seguard(buf, str)){return 1;} strcat(buf, str);
                        if (i != (NBR_TABLE_CONF_MAX_NEIGHBORS - 1)) { sprintf(str, "," );  if(seguard(buf, str)){return 1;} strcat(buf, str); }
                    }

                    sprintf(str, "]"); if(seguard(buf, str)){return 1;} strcat(buf, str);
                    // [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]

                // :::::::::::::::::::::::
                // SUBARRAY END rN{} > ns
                // :::::::::::::::::::::::
            }

        // ######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)########
        // ########!(ROUTING_CONF_RPL_LITE)########!(ROUTING_CONF_RPL_LITE)########!(ROUTING_CONF_RPL_LITE)########!(ROUTING_CONF_RPL_LITE)########!(ROUTING_CONF_RPL_LITE)########!(ROUTING_CONF_RPL_LITE)########!
        #else

            sprintf(str, "\"" "rL" "\"" ":" "false");  if(seguard(buf, str)){return 1;} strcat(buf, str); 

            // ???????????????????????????????????????????????????????????????????
            sprintf(str, ",");  if(seguard(buf, str)){return 1;} strcat(buf, str);
            // ???????????????????????????????????????????????????????????????????

            sprintf(str, "\"" "i"   "\"" ":" "null"     ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str);
            sprintf(str, "\"" "c"   "\"" ":" "null"     ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str);

            // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
            // SUBARRAY START rN{} > ns[] ///////////////////////////////////////////////////////////////
            // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
            sprintf(str, "\"" "ns" "\"" ":");  if(seguard(buf, str)){return 1;} strcat(buf, str); ///////
            // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
            
                // [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]
                sprintf(str, "["); if(seguard(buf, str)){return 1;} strcat(buf, str);

                for (int i = 0; i < NBR_TABLE_CONF_MAX_NEIGHBORS; i++)
                {
                    sprintf(str,    "null"  );  if(seguard(buf, str)){return 1;} strcat(buf, str);
                    if (i != (NBR_TABLE_CONF_MAX_NEIGHBORS - 1)) { sprintf(str, "," );  if(seguard(buf, str)){return 1;} strcat(buf, str); } 
                }

                sprintf(str, "]"); if(seguard(buf, str)){return 1;} strcat(buf, str);
                // [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]
            
            // :::::::::::::::::::::::
            // SUBARRAY END rN{} > ns
            // :::::::::::::::::::::::
        
        #endif
        // ########!(ROUTING_CONF_RPL_LITE)########!(ROUTING_CONF_RPL_LITE)########!(ROUTING_CONF_RPL_LITE)########!(ROUTING_CONF_RPL_LITE)########!(ROUTING_CONF_RPL_LITE)########!(ROUTING_CONF_RPL_LITE)########!

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    sprintf(str, "}"); if(seguard(buf, str)){return 1;} strcat(buf, str); ///
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // SECTION END rN{} /////////////////////////////////////////////////////
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    return 0;
}
















// ####################################################################################################################
// MAIN FUNCTIONS >>>>> CONTINUE <<<<< ////////////////////////////////////////////////////////////////////////////////
// ####################################################################################################################

// ----------------------------------------------------------------------------
// function that appends RPL NEIGBOR RANKS section to the json string /////////
// ----------------------------------------------------------------------------

// {
// 	"pckt": {
// 		"valid": true,
// 		"error": null
// 	},
// 	"qId": 20,
// 	"id": {
// 		"sT": 55,
// 		"adr": "0012.4b00.0f83.b601"
// 	},
// 	"rNR": {
// 		"rL": true,
// 		"iId": true,
// 		"c": 3,
// 		"ns": [{
// 			"rk": 128,
// 			"lM": 128,
// 			"rkN": 256
// 		}, {
// 			"rk": 256,
// 			"lM": 128,
// 			"rkN": 384
// 		}, {
// 			"rk": 256,
// 			"lM": 128,
// 			"rkN": 384
// 		}, null, null]
// 	},
// 	"hash": 3790190472
// }

// RPL neighbor 1/3: fe80::212:4b00:f24:8385 |--->  128,   128 =>   256 <---| --  7 rbafp (last tx 0 min ago)
// RPL neighbor 2/3: fe80::212:4b00:f82:a600 |--->  384,   128 =>   512 <---| --  2   a   (last tx 0 min ago)
// RPL neighbor 3/3: fe80::212:4b00:f82:da03 |--->  546,   128 =>   674 <---| --  0   a   (no tx)

static int oar_json_append_rpl_neighbor_ranks(char * buf)
{
    char str[128];
    
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // SECTION START rNR{} //////////////////////////////////////////////////////////////////////
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    sprintf(str, "\"" "rNR" "\"" ":"    ); if(seguard(buf, str)){return 1;} strcat(buf, str); ///   
    sprintf(str, "{"                    ); if(seguard(buf, str)){return 1;} strcat(buf, str); ///
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

        // ######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)########
        #if (ROUTING_CONF_RPL_LITE)

            sprintf(str, "\"" "rL" "\"" ":" "true");  if(seguard(buf, str)){return 1;} strcat(buf, str);

            // ???????????????????????????????????????????????????????????????????
            sprintf(str, ",");  if(seguard(buf, str)){return 1;} strcat(buf, str);
            // ???????????????????????????????????????????????????????????????????

            if (!curr_instance.used || rpl_neighbor_count() == 0)
            {
                
                if (!curr_instance.used)    { sprintf(str, "\"" "iId" "\"" ":" "false"  ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str); }
                else                        { sprintf(str, "\"" "iId" "\"" ":" "true"   ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str); }
            
                sprintf(str, "\"" "c" "\"" ":" "%u" ,rpl_neighbor_count()); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str);
                
                // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
                //  (!curr_instance.used || rpl_neighbor_count() == 0) //////////////////////////////////////
                // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
                // SUBARRAY START rNR{} > ns[] //////////////////////////////////////////////////////////////
                // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
                sprintf(str, "\"" "ns" "\"" ":");  if(seguard(buf, str)){return 1;} strcat(buf, str); ///////
                // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
                
                    // [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]
                    sprintf(str, "["); if(seguard(buf, str)){return 1;} strcat(buf, str);

                    for (int i = 0; i < NBR_TABLE_CONF_MAX_NEIGHBORS; i++)
                    {
                        sprintf(str,    "null"  );  if(seguard(buf, str)){return 1;} strcat(buf, str);
                        if (i != (NBR_TABLE_CONF_MAX_NEIGHBORS - 1)) { sprintf(str, "," );  if(seguard(buf, str)){return 1;} strcat(buf, str); } 
                    }

                    sprintf(str, "]"); if(seguard(buf, str)){return 1;} strcat(buf, str);
                    // [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]
                
                // :::::::::::::::::::::::
                // SUBARRAY END rNR{} > ns
                // :::::::::::::::::::::::
            }
            else
            {
                
                rpl_nbr_t *nbr = nbr_table_head(rpl_neighbors);

                int oar_json_rpl_neighbor_count = 0;

                sprintf(str, "\"" "iId"     "\"" ":" "true"                         ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, "," ); if(seguard(buf, str)){return 1;} strcat(buf, str);
                sprintf(str, "\"" "c"       "\"" ":" "%u"   ,rpl_neighbor_count()   ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, "," ); if(seguard(buf, str)){return 1;} strcat(buf, str);

                // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
                // !(!curr_instance.used || rpl_neighbor_count() == 0) //////////////////////////////////////
                // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
                // SUBARRAY START rNR{} > ns[] //////////////////////////////////////////////////////////////
                // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
                sprintf(str, "\"" "ns" "\"" ":");  if(seguard(buf, str)){return 1;} strcat(buf, str); ///////
                // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
                
                    // [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]
                    sprintf(str, "["); if(seguard(buf, str)){return 1;} strcat(buf, str);

                    while(nbr != NULL)
                    {
                        oar_json_rpl_neighbor_count++; 
                        
                        // rpl_nbr_t *oar_json_rpl_nbr_best = best_parent(0);
                        // const struct link_stats *oar_json_rpl_nbr_stats = rpl_neighbor_get_link_stats(nbr);
                        // clock_time_t oar_json_rpl_nbr_clock_now = clock_time();

                        // {{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}
                        sprintf(str, "{" ); if(seguard(buf, str)){return 1;} strcat(buf, str);
                            
                            sprintf(str, "\"" "rk"  "\"" ":"    "%u"    ,nbr->rank                                                                                                           ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str);
                            sprintf(str, "\"" "lM"  "\"" ":"    "%u"    ,rpl_neighbor_get_link_metric(nbr)                                                                                   ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str);
                            sprintf(str, "\"" "rkN" "\"" ":"    "%u"    ,rpl_neighbor_rank_via_nbr(nbr)                                                                                      ); if(seguard(buf, str)){return 1;} strcat(buf, str);    
                            
                        sprintf(str,    "}" ); if(seguard(buf, str)){return 1;} strcat(buf, str);
                        // {{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}
                        
                        if (oar_json_rpl_neighbor_count < NBR_TABLE_CONF_MAX_NEIGHBORS) { sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str); }
                        nbr = nbr_table_next(rpl_neighbors, nbr);
                    }
                    
                    for (int i = oar_json_rpl_neighbor_count; i < NBR_TABLE_CONF_MAX_NEIGHBORS; i++)
                    {
                        sprintf(str, "null"); if(seguard(buf, str)){return 1;} strcat(buf, str);
                        if (i != (NBR_TABLE_CONF_MAX_NEIGHBORS - 1)) { sprintf(str, "," );  if(seguard(buf, str)){return 1;} strcat(buf, str); }
                    }

                    sprintf(str, "]"); if(seguard(buf, str)){return 1;} strcat(buf, str);
                    // [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]

                // :::::::::::::::::::::::
                // SUBARRAY END rNR{} > ns
                // :::::::::::::::::::::::
            }

        // ######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)########
        // ########!(ROUTING_CONF_RPL_LITE)########!(ROUTING_CONF_RPL_LITE)########!(ROUTING_CONF_RPL_LITE)########!(ROUTING_CONF_RPL_LITE)########!(ROUTING_CONF_RPL_LITE)########!(ROUTING_CONF_RPL_LITE)########!
        #else

            sprintf(str, "\"" "rL" "\"" ":" "false");  if(seguard(buf, str)){return 1;} strcat(buf, str); 

            // ???????????????????????????????????????????????????????????????????
            sprintf(str, ",");  if(seguard(buf, str)){return 1;} strcat(buf, str);
            // ???????????????????????????????????????????????????????????????????

            sprintf(str, "\"" "i"   "\"" ":" "null"     ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str);
            sprintf(str, "\"" "c"   "\"" ":" "null"     ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str);

            // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
            // SUBARRAY START rNR{} > ns[] //////////////////////////////////////////////////////////////
            // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
            sprintf(str, "\"" "ns" "\"" ":");  if(seguard(buf, str)){return 1;} strcat(buf, str); ///////
            // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
            
                // [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]
                sprintf(str, "["); if(seguard(buf, str)){return 1;} strcat(buf, str);

                for (int i = 0; i < NBR_TABLE_CONF_MAX_NEIGHBORS; i++)
                {
                    sprintf(str,    "null"  );  if(seguard(buf, str)){return 1;} strcat(buf, str);
                    if (i != (NBR_TABLE_CONF_MAX_NEIGHBORS - 1)) { sprintf(str, "," );  if(seguard(buf, str)){return 1;} strcat(buf, str); } 
                }

                sprintf(str, "]"); if(seguard(buf, str)){return 1;} strcat(buf, str);
                // [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]
            
            // :::::::::::::::::::::::
            // SUBARRAY END rNR{} > ns
            // :::::::::::::::::::::::
        
        #endif
        // ########!(ROUTING_CONF_RPL_LITE)########!(ROUTING_CONF_RPL_LITE)########!(ROUTING_CONF_RPL_LITE)########!(ROUTING_CONF_RPL_LITE)########!(ROUTING_CONF_RPL_LITE)########!(ROUTING_CONF_RPL_LITE)########!

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    sprintf(str, "}"); if(seguard(buf, str)){return 1;} strcat(buf, str); ///
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // SECTION END rNR{} ////////////////////////////////////////////////////
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    return 0;
}
















// ####################################################################################################################
// MAIN FUNCTIONS >>>>> CONTINUE <<<<< ////////////////////////////////////////////////////////////////////////////////
// ####################################################################################################################

// ----------------------------------------------------------------------------
// function that appends RPL NEIGBOR VALUES section to the json string ////////
// ----------------------------------------------------------------------------

// {
// 	"pckt": {
// 		"valid": true,
// 		"error": null
// 	},
// 	"qId": 21,
// 	"id": {
// 		"sT": 57,
// 		"adr": "0012.4b00.0f83.b601"
// 	},
// 	"rNV": {
// 		"rL": true,
// 		"iId": true,
// 		"c": 3,
// 		"ns": [{
// 			"f": 16,
// 			"r": true,
// 			"b": true,
// 			"a": true,
// 			"p": true
// 		}, {
// 			"f": 0,
// 			"r": false,
// 			"b": false,
// 			"a": true,
// 			"p": false
// 		}, {
// 			"f": 0,
// 			"r": false,
// 			"b": false,
// 			"a": true,
// 			"p": false
// 		}, null, null]
// 	},
// 	"hash": 3790190472
// }

// RPL neighbor 1/3: fe80::212:4b00:f24:8385  128,   128 =>   256 |---> --  7 rbafp <---| (last tx 0 min ago)
// RPL neighbor 2/3: fe80::212:4b00:f82:a600  384,   128 =>   512 |---> --  2   a   <---| (last tx 0 min ago)
// RPL neighbor 3/3: fe80::212:4b00:f82:da03  546,   128 =>   674 |---> --  0   a   <---| (no tx)

static int oar_json_append_rpl_neighbor_values(char * buf)
{
    char str[128];
    
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // SECTION START rNV{} //////////////////////////////////////////////////////////////////////
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    sprintf(str, "\"" "rNV" "\"" ":"    ); if(seguard(buf, str)){return 1;} strcat(buf, str); ///  
    sprintf(str, "{"                    ); if(seguard(buf, str)){return 1;} strcat(buf, str); ///
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

        // ######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)########
        #if (ROUTING_CONF_RPL_LITE)

            sprintf(str, "\"" "rL" "\"" ":" "true");  if(seguard(buf, str)){return 1;} strcat(buf, str);

            // ???????????????????????????????????????????????????????????????????
            sprintf(str, ",");  if(seguard(buf, str)){return 1;} strcat(buf, str);
            // ???????????????????????????????????????????????????????????????????

            if (!curr_instance.used || rpl_neighbor_count() == 0)
            {
                
                if (!curr_instance.used)    { sprintf(str, "\"" "iId" "\"" ":" "false"  ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str); }
                else                        { sprintf(str, "\"" "iId" "\"" ":" "true"   ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str); }
            
                sprintf(str, "\"" "c" "\"" ":" "%u" ,rpl_neighbor_count()); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str);
                
                // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
                //  (!curr_instance.used || rpl_neighbor_count() == 0) //////////////////////////////////////
                // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
                // SUBARRAY START rNV{} > ns[] //////////////////////////////////////////////////////////////
                // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
                sprintf(str, "\"" "ns" "\"" ":");  if(seguard(buf, str)){return 1;} strcat(buf, str); ///////
                // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
                
                    // [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]
                    sprintf(str, "["); if(seguard(buf, str)){return 1;} strcat(buf, str);

                    for (int i = 0; i < NBR_TABLE_CONF_MAX_NEIGHBORS; i++)
                    {
                        sprintf(str,    "null"  );  if(seguard(buf, str)){return 1;} strcat(buf, str);
                        if (i != (NBR_TABLE_CONF_MAX_NEIGHBORS - 1)) { sprintf(str, "," );  if(seguard(buf, str)){return 1;} strcat(buf, str); } 
                    }

                    sprintf(str, "]"); if(seguard(buf, str)){return 1;} strcat(buf, str);
                    // [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]
                
                // :::::::::::::::::::::::
                // SUBARRAY END rNV{} > ns
                // :::::::::::::::::::::::
            }
            else
            {
                
                rpl_nbr_t *nbr = nbr_table_head(rpl_neighbors);

                int oar_json_rpl_neighbor_count = 0;

                sprintf(str, "\"" "iId"     "\"" ":" "true"                         ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, "," ); if(seguard(buf, str)){return 1;} strcat(buf, str);
                sprintf(str, "\"" "c"       "\"" ":" "%u"   ,rpl_neighbor_count()   ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, "," ); if(seguard(buf, str)){return 1;} strcat(buf, str);

                // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
                // !(!curr_instance.used || rpl_neighbor_count() == 0) //////////////////////////////////////
                // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
                // SUBARRAY START rNV{} > ns[] //////////////////////////////////////////////////////////////
                // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
                sprintf(str, "\"" "ns" "\"" ":");  if(seguard(buf, str)){return 1;} strcat(buf, str); ///////
                // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
                
                    // [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]
                    sprintf(str, "["); if(seguard(buf, str)){return 1;} strcat(buf, str);

                    while(nbr != NULL)
                    {
                        oar_json_rpl_neighbor_count++; 
                        
                        rpl_nbr_t *oar_json_rpl_nbr_best = best_parent(0);
                        const struct link_stats *oar_json_rpl_nbr_stats = rpl_neighbor_get_link_stats(nbr);
                        // clock_time_t oar_json_rpl_nbr_clock_now = clock_time();

                        // {{{{{{{{{{{{{{{{{}}}}}}}}}}}}}}}}}
                        sprintf(str, "{" ); if(seguard(buf, str)){return 1;} strcat(buf, str);

                            sprintf(str, "\"" "fr"  "\"" ":"    "%u"    ,oar_json_rpl_nbr_stats != NULL ? oar_json_rpl_nbr_stats->freshness : 0                                             ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str);

                            sprintf(str, "\"" "r"   "\"" ":"    "%s"    ,(nbr->rank == ROOT_RANK) ? "true" : "false"                                                                        ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str);
                            sprintf(str, "\"" "b"   "\"" ":"    "%s"    ,nbr == oar_json_rpl_nbr_best ? "true" : "false"                                                                    ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str);
                            sprintf(str, "\"" "a"   "\"" ":"    "%s"    ,((acceptable_rank(rpl_neighbor_rank_via_nbr(nbr)) && rpl_neighbor_is_acceptable_parent(nbr))) ? "true" : "false"   ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str);
                            sprintf(str, "\"" "f"   "\"" ":"    "%s"    ,link_stats_is_fresh(oar_json_rpl_nbr_stats) ? "true" : "false"                                                     ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str);
                            sprintf(str, "\"" "p"   "\"" ":"    "%s"    ,nbr == curr_instance.dag.preferred_parent ? "true" : "false"                                                       ); if(seguard(buf, str)){return 1;} strcat(buf, str);    

                            
                        sprintf(str,    "}" ); if(seguard(buf, str)){return 1;} strcat(buf, str);
                        // {{{{{{{{{{{{{{{{{}}}}}}}}}}}}}}}}}
                        
                        // rpl_neighbor_snprint(temp_str, sizeof(temp_str), nbr);  // sprintf(str,    "\""    "%s"    "\""    ,temp_str   );  if(seguard(buf, str)){return 1;} strcat(buf, str);
                        
                        if (oar_json_rpl_neighbor_count < NBR_TABLE_CONF_MAX_NEIGHBORS) { sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str); }
                        nbr = nbr_table_next(rpl_neighbors, nbr);
                    }
                    
                    for (int i = oar_json_rpl_neighbor_count; i < NBR_TABLE_CONF_MAX_NEIGHBORS; i++)
                    {
                        sprintf(str, "null"); if(seguard(buf, str)){return 1;} strcat(buf, str);
                        if (i != (NBR_TABLE_CONF_MAX_NEIGHBORS - 1)) { sprintf(str, "," );  if(seguard(buf, str)){return 1;} strcat(buf, str); }
                    }

                    sprintf(str, "]"); if(seguard(buf, str)){return 1;} strcat(buf, str);
                    // [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]

                // :::::::::::::::::::::::
                // SUBARRAY END rNV{} > ns
                // :::::::::::::::::::::::
            }

        // ######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)########
        // ########!(ROUTING_CONF_RPL_LITE)########!(ROUTING_CONF_RPL_LITE)########!(ROUTING_CONF_RPL_LITE)########!(ROUTING_CONF_RPL_LITE)########!(ROUTING_CONF_RPL_LITE)########!(ROUTING_CONF_RPL_LITE)########!
        #else

            sprintf(str, "\"" "rL" "\"" ":" "false");  if(seguard(buf, str)){return 1;} strcat(buf, str); 

            // ???????????????????????????????????????????????????????????????????
            sprintf(str, ",");  if(seguard(buf, str)){return 1;} strcat(buf, str);
            // ???????????????????????????????????????????????????????????????????

            sprintf(str, "\"" "iId"     "\"" ":" "null"     ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str);
            sprintf(str, "\"" "c"       "\"" ":" "null"     ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str);

            // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
            // SUBARRAY START rNV{} > ns[] //////////////////////////////////////////////////////////////
            // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
            sprintf(str, "\"" "ns" "\"" ":");  if(seguard(buf, str)){return 1;} strcat(buf, str); ///////
            // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
            
                // [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]
                sprintf(str, "["); if(seguard(buf, str)){return 1;} strcat(buf, str);

                for (int i = 0; i < NBR_TABLE_CONF_MAX_NEIGHBORS; i++)
                {
                    sprintf(str,    "null"  );  if(seguard(buf, str)){return 1;} strcat(buf, str);
                    if (i != (NBR_TABLE_CONF_MAX_NEIGHBORS - 1)) { sprintf(str, "," );  if(seguard(buf, str)){return 1;} strcat(buf, str); } 
                }

                sprintf(str, "]"); if(seguard(buf, str)){return 1;} strcat(buf, str);
                // [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]
            
            // :::::::::::::::::::::::
            // SUBARRAY END rNV{} > ns
            // :::::::::::::::::::::::
        
        #endif
        // ########!(ROUTING_CONF_RPL_LITE)########!(ROUTING_CONF_RPL_LITE)########!(ROUTING_CONF_RPL_LITE)########!(ROUTING_CONF_RPL_LITE)########!(ROUTING_CONF_RPL_LITE)########!(ROUTING_CONF_RPL_LITE)########!

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    sprintf(str, "}"); if(seguard(buf, str)){return 1;} strcat(buf, str); ///
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // SECTION END rNv{} ////////////////////////////////////////////////////
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    return 0;
}
















// ####################################################################################################################
// MAIN FUNCTIONS >>>>> CONTINUE <<<<< ////////////////////////////////////////////////////////////////////////////////
// ####################################################################################################################

// ----------------------------------------------------------------------------
// function that appends RPL NEIGBORS () section to the json string ///////////
// ----------------------------------------------------------------------------

// {
// 	"pckt": {
// 		"valid": true,
// 		"error": null
// 	},
// 	"qId": 22,
// 	"id": {
// 		"sT": 59,
// 		"adr": "0012.4b00.0f83.b601"
// 	},
// 	"rNP": {
// 		"rL": true,
// 		"iId": true,
// 		"c": 3,
// 		"ns": [{
// 			"lTx": 0,
// 			"bS": null
// 		}, {
// 			"lTx": null,
// 			"bS": null
// 		}, {
// 			"lTx": null,
// 			"bS": null
// 		}, null, null]
// 	},
// 	"hash": 3790190472
// }

// RPL neighbor 1/3: fe80::212:4b00:f24:8385  128,   128 =>   256 --  7 rbafp |---> (last tx 0 min ago) <---|
// RPL neighbor 2/3: fe80::212:4b00:f82:a600  384,   128 =>   512 --  2   a   |---> (last tx 0 min ago) <---|
// RPL neighbor 3/3: fe80::212:4b00:f82:da03  546,   128 =>   674 --  0   a   |---> (no tx)             <---|

static int oar_json_append_rpl_neighbor_parens(char * buf)
{
    char str[128];
    
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // SECTION START rNP{} //////////////////////////////////////////////////////////////////////
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    sprintf(str, "\"" "rNP" "\"" ":"    ); if(seguard(buf, str)){return 1;} strcat(buf, str); ///   
    sprintf(str, "{"                    ); if(seguard(buf, str)){return 1;} strcat(buf, str); ///
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

        // ######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)########
        #if (ROUTING_CONF_RPL_LITE)

            sprintf(str, "\"" "rL" "\"" ":" "true");  if(seguard(buf, str)){return 1;} strcat(buf, str);

            // ???????????????????????????????????????????????????????????????????
            sprintf(str, ",");  if(seguard(buf, str)){return 1;} strcat(buf, str);
            // ???????????????????????????????????????????????????????????????????

            if (!curr_instance.used || rpl_neighbor_count() == 0)
            {
                
                if (!curr_instance.used)    { sprintf(str, "\"" "iId" "\"" ":" "false"  ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str); }
                else                        { sprintf(str, "\"" "iId" "\"" ":" "true"   ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str); }
            
                sprintf(str, "\"" "c" "\"" ":" "%u" ,rpl_neighbor_count()); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str);
                
                // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
                //  (!curr_instance.used || rpl_neighbor_count() == 0) //////////////////////////////////////
                // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
                // SUBARRAY START rNP{} > ns[] //////////////////////////////////////////////////////////////
                // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
                sprintf(str, "\"" "ns" "\"" ":");  if(seguard(buf, str)){return 1;} strcat(buf, str); ///////
                // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
                
                    // [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]
                    sprintf(str, "["); if(seguard(buf, str)){return 1;} strcat(buf, str);

                    for (int i = 0; i < NBR_TABLE_CONF_MAX_NEIGHBORS; i++)
                    {
                        sprintf(str,    "null"  );  if(seguard(buf, str)){return 1;} strcat(buf, str);
                        if (i != (NBR_TABLE_CONF_MAX_NEIGHBORS - 1)) { sprintf(str, "," );  if(seguard(buf, str)){return 1;} strcat(buf, str); } 
                    }

                    sprintf(str, "]"); if(seguard(buf, str)){return 1;} strcat(buf, str);
                    // [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]
                
                // :::::::::::::::::::::::
                // SUBARRAY END rNr{} > ns
                // :::::::::::::::::::::::
            }
            else
            {
                
                rpl_nbr_t *nbr = nbr_table_head(rpl_neighbors);

                int oar_json_rpl_neighbor_count = 0;

                sprintf(str, "\"" "iId"     "\"" ":" "true"                         ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, "," ); if(seguard(buf, str)){return 1;} strcat(buf, str);
                sprintf(str, "\"" "c"       "\"" ":" "%u"   ,rpl_neighbor_count()   ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, "," ); if(seguard(buf, str)){return 1;} strcat(buf, str);

                // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
                // !(!curr_instance.used || rpl_neighbor_count() == 0) //////////////////////////////////////
                // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
                // SUBARRAY START rNP{} > ns[] //////////////////////////////////////////////////////////////
                // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
                sprintf(str, "\"" "ns" "\"" ":");  if(seguard(buf, str)){return 1;} strcat(buf, str); ///////
                // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
                
                    // [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]
                    sprintf(str, "["); if(seguard(buf, str)){return 1;} strcat(buf, str);

                    while(nbr != NULL)
                    {
                        oar_json_rpl_neighbor_count++; 
                        
                        // rpl_nbr_t *oar_json_rpl_nbr_best = best_parent(0);
                        const struct link_stats *oar_json_rpl_nbr_stats = rpl_neighbor_get_link_stats(nbr);
                        clock_time_t oar_json_rpl_nbr_clock_now = clock_time();

                        // {{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}
                        sprintf(str, "{" ); if(seguard(buf, str)){return 1;} strcat(buf, str);

                            if(oar_json_rpl_nbr_stats->last_tx_time > 0) 
                            {
                                sprintf(str, "\"" "lTx" "\"" ":"    "%u"    ,(unsigned)((oar_json_rpl_nbr_clock_now - oar_json_rpl_nbr_stats->last_tx_time) / (60 * CLOCK_SECOND))  ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str);
                            }
                            else
                            {
                                sprintf(str, "\"" "lTx" "\"" ":"    "null"                                                                                                          ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str);
                            }

                            if(nbr->better_parent_since > 0) 
                            {
                                sprintf(str, "\"" "bS"  "\"" ":"    "%u"    ,(unsigned)((oar_json_rpl_nbr_clock_now - nbr->better_parent_since) / (60 * CLOCK_SECOND))              ); if(seguard(buf, str)){return 1;} strcat(buf, str);   
                            }
                            else
                            {
                                sprintf(str, "\"" "bS"  "\"" ":"    "null"                                                                                                          ); if(seguard(buf, str)){return 1;} strcat(buf, str);  
                            }
                            
                        sprintf(str,    "}" ); if(seguard(buf, str)){return 1;} strcat(buf, str);
                        // {{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}
                        
                        // rpl_neighbor_snprint(temp_str, sizeof(temp_str), nbr);  // sprintf(str,    "\""    "%s"    "\""    ,temp_str   );  if(seguard(buf, str)){return 1;} strcat(buf, str);
                        
                        if (oar_json_rpl_neighbor_count < NBR_TABLE_CONF_MAX_NEIGHBORS) { sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str); }
                        nbr = nbr_table_next(rpl_neighbors, nbr);
                    }
                    
                    for (int i = oar_json_rpl_neighbor_count; i < NBR_TABLE_CONF_MAX_NEIGHBORS; i++)
                    {
                        sprintf(str, "null"); if(seguard(buf, str)){return 1;} strcat(buf, str);
                        if (i != (NBR_TABLE_CONF_MAX_NEIGHBORS - 1)) { sprintf(str, "," );  if(seguard(buf, str)){return 1;} strcat(buf, str); }
                    }

                    sprintf(str, "]"); if(seguard(buf, str)){return 1;} strcat(buf, str);
                    // [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]
                
                // :::::::::::::::::::::::
                // SUBARRAY END rNP{} > ns
                // :::::::::::::::::::::::
            }

        // ######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)########
        // ########!(ROUTING_CONF_RPL_LITE)########!(ROUTING_CONF_RPL_LITE)########!(ROUTING_CONF_RPL_LITE)########!(ROUTING_CONF_RPL_LITE)########!(ROUTING_CONF_RPL_LITE)########!(ROUTING_CONF_RPL_LITE)########!
        #else

            sprintf(str, "\"" "rL" "\"" ":" "false");  if(seguard(buf, str)){return 1;} strcat(buf, str); 

            // ???????????????????????????????????????????????????????????????????
            sprintf(str, ",");  if(seguard(buf, str)){return 1;} strcat(buf, str);
            // ???????????????????????????????????????????????????????????????????

            sprintf(str, "\"" "i"   "\"" ":" "null"     ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str);
            sprintf(str, "\"" "c"   "\"" ":" "null"     ); if(seguard(buf, str)){return 1;} strcat(buf, str);    sprintf(str, ","); if(seguard(buf, str)){return 1;} strcat(buf, str);

                // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
                // SUBARRAY START rNP{} > ns[] //////////////////////////////////////////////////////////////
                // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
                sprintf(str, "\"" "ns" "\"" ":");  if(seguard(buf, str)){return 1;} strcat(buf, str); ///////
                // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
                
                    // [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]
                    sprintf(str, "["); if(seguard(buf, str)){return 1;} strcat(buf, str);

                    for (int i = 0; i < NBR_TABLE_CONF_MAX_NEIGHBORS; i++)
                    {
                        sprintf(str,    "null"  );  if(seguard(buf, str)){return 1;} strcat(buf, str);
                        if (i != (NBR_TABLE_CONF_MAX_NEIGHBORS - 1)) { sprintf(str, "," );  if(seguard(buf, str)){return 1;} strcat(buf, str); } 
                    }

                    sprintf(str, "]"); if(seguard(buf, str)){return 1;} strcat(buf, str);
                    // [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]

                // :::::::::::::::::::::::
                // SUBARRAY END rNr{} > ns
                // :::::::::::::::::::::::
        
        #endif
        // ########!(ROUTING_CONF_RPL_LITE)########!(ROUTING_CONF_RPL_LITE)########!(ROUTING_CONF_RPL_LITE)########!(ROUTING_CONF_RPL_LITE)########!(ROUTING_CONF_RPL_LITE)########!(ROUTING_CONF_RPL_LITE)########!

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    sprintf(str, "}"); if(seguard(buf, str)){return 1;} strcat(buf, str); ///
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // SECTION END rP{} /////////////////////////////////////////////////////
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    return 0;
}
















// ####################################################################################################################
// MAIN FUNCTIONS >>>>> ABOVE <<<<< ////////////////////////////////////////////////////////////////////////////////
// ####################################################################################################################

// ----------------------------------------------------------------------------
// function that appends RPL NEIGBORS () section to the json string ///////////
// ----------------------------------------------------------------------------

static void oar_json_append_pckt(char * buf, int valid, char *error_text, int error_code)
{
    char str[128];

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // SECTION START pckt{} ////////////////////////////////
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    sprintf(str, "\"" "pckt" "\"" ":"   ); strcat(buf, str);
    sprintf(str, "{"                    ); strcat(buf, str);
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    
        sprintf(str, "\"" "vld" "\"" ":" "%s" ,valid ? "true" : "false"); strcat(buf, str);

        // ?????????????????????????????????
        sprintf(str, ","); strcat(buf, str);
        // ?????????????????????????????????

        if (valid)
        {
            sprintf(str,        "\"" "err"  "\"" ":"        "null"                  ); strcat(buf, str);
        }
        else
        {
            // ><><><><><><><><><><><><><><><><><><><><><><><><><><>
            // SUBSECTION START pckt{} > error{} ///////////////////
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            sprintf(str, "\"" "err" "\"" ":"    ); strcat(buf, str);
            sprintf(str, "{"                    ); strcat(buf, str);
            // ><><><><><><><><><><><><><><><><><><><><><><><><><><>

                sprintf(str,    "\"" "txt"  "\"" ":" "\""   "%s" "\""   ,error_text ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                sprintf(str,    "\"" "cd"   "\"" ":"        "%d"        ,error_code ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);

            // <><><><><><><><><><><><><><><><><>
            sprintf(str, "}"); strcat(buf, str);
            // <><><><><><><><><><><><><><><><><>
            // SUBSECTION END pckt{} > error{} //
            // <><><><><><><><><><><><><><><><><>
        }

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    sprintf(str, "}"); strcat(buf, str);
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // SECTION END pckt{} //////////////
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
}
















// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// JSON CONTRUCTOR %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


void oar_json_construct(char * buf, int rcrd, int ndx)
{   
    char str[32];
    switch (ndx)
    {
        
        case 0:
            oar_json_init(buf);
            if(oar_json_enter(buf))                                                                 {return;}

            oar_json_append_pckt(buf, 1, NULL, 0);

            if(oar_json_bridge(buf))                                                                {return;}
            sprintf(str, "\"" "rcrd"    "\"" ":" "%d", rcrd             ); if(seguard(buf, str))    {return;} strcat(buf, str);

            if(oar_json_bridge(buf))                                                                {return;}
            sprintf(str, "\"" "ndx"     "\"" ":" "%d", ndx              ); if(seguard(buf, str))    {return;} strcat(buf, str);

            if(oar_json_bridge(buf))                                                                {return;}
            if(oar_json_append_id(buf))                                                             {return;}

            if(oar_json_bridge(buf))                                                                {return;}
            if(oar_json_append_sys(buf))                                                            {return;}

            if(oar_json_bridge(buf))                                                                {return;}
            sprintf(str, "\"" "hash"    "\"" ":" "%u", oar_sdbm(buf)    ); if(seguard(buf, str))    {return;} strcat(buf, str);

            if(oar_json_exit(buf))                                                                  {return;}
            
            break;

        case 1:
            oar_json_init(buf);
            if(oar_json_enter(buf))                                                                 {return;}

            oar_json_append_pckt(buf, 1, NULL, 0);

            if(oar_json_bridge(buf))                                                                {return;}
            sprintf(str, "\"" "rcrd"    "\"" ":" "%d", rcrd             ); if(seguard(buf, str))    {return;} strcat(buf, str);

            if(oar_json_bridge(buf))                                                                {return;}
            sprintf(str, "\"" "ndx"     "\"" ":" "%d", ndx              ); if(seguard(buf, str))    {return;} strcat(buf, str);

            if(oar_json_bridge(buf))                                                                {return;}
            if(oar_json_append_id(buf))                                                             {return;}

            if(oar_json_bridge(buf))                                                                {return;}
            if(oar_json_append_dev(buf))                                                            {return;}

            if(oar_json_bridge(buf))                                                                {return;}
            sprintf(str, "\"" "hash"    "\"" ":" "%u", oar_sdbm(buf)    ); if(seguard(buf, str))    {return;} strcat(buf, str);

            if(oar_json_exit(buf))                                                                  {return;}
            
            break;
        
        case 2:
            oar_json_init(buf);
            if(oar_json_enter(buf))                                                                 {return;}

            oar_json_append_pckt(buf, 1, NULL, 0);

            if(oar_json_bridge(buf))                                                                {return;}
            sprintf(str, "\"" "rcrd"    "\"" ":" "%d", rcrd             ); if(seguard(buf, str))    {return;} strcat(buf, str);

            if(oar_json_bridge(buf))                                                                {return;}
            sprintf(str, "\"" "ndx"     "\"" ":" "%d", ndx              ); if(seguard(buf, str))    {return;} strcat(buf, str);

            if(oar_json_bridge(buf))                                                                {return;}
            if(oar_json_append_id(buf))                                                             {return;}

            if(oar_json_bridge(buf))                                                                {return;}
            if(oar_json_append_nrg(buf))                                                            {return;}

            if(oar_json_bridge(buf))                                                                {return;}
            sprintf(str, "\"" "hash"    "\"" ":" "%u", oar_sdbm(buf)    ); if(seguard(buf, str))    {return;} strcat(buf, str);

            if(oar_json_exit(buf))                                                                  {return;}
            
            break;

        case 3:
            oar_json_init(buf);
            if(oar_json_enter(buf))                                                                 {return;}

            oar_json_append_pckt(buf, 1, NULL, 0);

            if(oar_json_bridge(buf))                                                                {return;}
            sprintf(str, "\"" "rcrd"    "\"" ":" "%d", rcrd             ); if(seguard(buf, str))    {return;} strcat(buf, str);

            if(oar_json_bridge(buf))                                                                {return;}
            sprintf(str, "\"" "ndx"     "\"" ":" "%d", ndx              ); if(seguard(buf, str))    {return;} strcat(buf, str);

            if(oar_json_bridge(buf))                                                                {return;}
            if(oar_json_append_id(buf))                                                             {return;}

            if(oar_json_bridge(buf))                                                                {return;}
            if(oar_json_append_stats_ip(buf))                                                       {return;}

            if(oar_json_bridge(buf))                                                                {return;}
            sprintf(str, "\"" "hash"    "\"" ":" "%u", oar_sdbm(buf)    ); if(seguard(buf, str))    {return;} strcat(buf, str);

            if(oar_json_exit(buf))                                                                  {return;}
            
            break;

        case 4:
            oar_json_init(buf);
            if(oar_json_enter(buf))                                                                 {return;}

            oar_json_append_pckt(buf, 1, NULL, 0);

            if(oar_json_bridge(buf))                                                                {return;}
            sprintf(str, "\"" "rcrd"    "\"" ":" "%d", rcrd             ); if(seguard(buf, str))    {return;} strcat(buf, str);

            if(oar_json_bridge(buf))                                                                {return;}
            sprintf(str, "\"" "ndx"     "\"" ":" "%d", ndx              ); if(seguard(buf, str))    {return;} strcat(buf, str);

            if(oar_json_bridge(buf))                                                                {return;}
            if(oar_json_append_id(buf))                                                             {return;}

            if(oar_json_bridge(buf))                                                                {return;}
            if(oar_json_append_stats_icmp(buf))                                                     {return;}

            if(oar_json_bridge(buf))                                                                {return;}
            sprintf(str, "\"" "hash"    "\"" ":" "%u", oar_sdbm(buf)    ); if(seguard(buf, str))    {return;} strcat(buf, str);

            if(oar_json_exit(buf))                                                                  {return;}
            
            break;

        case 5:
            oar_json_init(buf);
            if(oar_json_enter(buf))                                                                 {return;}

            oar_json_append_pckt(buf, 1, NULL, 0);

            if(oar_json_bridge(buf))                                                                {return;}
            sprintf(str, "\"" "rcrd"    "\"" ":" "%d", rcrd             ); if(seguard(buf, str))    {return;} strcat(buf, str);

            if(oar_json_bridge(buf))                                                                {return;}
            sprintf(str, "\"" "ndx"     "\"" ":" "%d", ndx              ); if(seguard(buf, str))    {return;} strcat(buf, str);
            
            if(oar_json_bridge(buf))                                                                {return;}
            if(oar_json_append_id(buf))                                                             {return;}

            if(oar_json_bridge(buf))                                                                {return;}
            if(oar_json_append_stats_tcp_udp(buf))                                                  {return;}

            if(oar_json_bridge(buf))                                                                {return;}
            sprintf(str, "\"" "hash"    "\"" ":" "%u", oar_sdbm(buf)    ); if(seguard(buf, str))    {return;} strcat(buf, str);

            if(oar_json_exit(buf))                                                                  {return;}
            
            break;

        case 6:
            oar_json_init(buf);
            if(oar_json_enter(buf))                                                                 {return;}

            oar_json_append_pckt(buf, 1, NULL, 0);

            if(oar_json_bridge(buf))                                                                {return;}
            sprintf(str, "\"" "rcrd"    "\"" ":" "%d", rcrd             ); if(seguard(buf, str))    {return;} strcat(buf, str);

            if(oar_json_bridge(buf))                                                                {return;}
            sprintf(str, "\"" "ndx"     "\"" ":" "%d", ndx              ); if(seguard(buf, str))    {return;} strcat(buf, str);

            if(oar_json_bridge(buf))                                                                {return;}
            if(oar_json_append_id(buf))                                                             {return;}

            if(oar_json_bridge(buf))                                                                {return;}
            if(oar_json_append_stats_nd6(buf))                                                      {return;}

            if(oar_json_bridge(buf))                                                                {return;}
            sprintf(str, "\"" "hash"    "\"" ":" "%u", oar_sdbm(buf)    ); if(seguard(buf, str))    {return;} strcat(buf, str);

            if(oar_json_exit(buf))                                                                  {return;}
            
            break;

        case 7:
            oar_json_init(buf);
            if(oar_json_enter(buf))                                                                 {return;}

            oar_json_append_pckt(buf, 1, NULL, 0);

            if(oar_json_bridge(buf))                                                                {return;}
            sprintf(str, "\"" "rcrd"    "\"" ":" "%d", rcrd             ); if(seguard(buf, str))    {return;} strcat(buf, str);

            if(oar_json_bridge(buf))                                                                {return;}
            sprintf(str, "\"" "ndx"     "\"" ":" "%d", ndx              ); if(seguard(buf, str))    {return;} strcat(buf, str);

            if(oar_json_bridge(buf))                                                                {return;}
            if(oar_json_append_id(buf))                                                             {return;}

            if(oar_json_bridge(buf))                                                                {return;}
            if(oar_json_append_ipv6_addr(buf))                                                      {return;}

            if(oar_json_bridge(buf))                                                                {return;}
            sprintf(str, "\"" "hash"    "\"" ":" "%u", oar_sdbm(buf)    ); if(seguard(buf, str))    {return;} strcat(buf, str);

            if(oar_json_exit(buf))                                                                  {return;}
            
            break;

        case 8:
            oar_json_init(buf);
            if(oar_json_enter(buf))                                                                 {return;}

            oar_json_append_pckt(buf, 1, NULL, 0);

            if(oar_json_bridge(buf))                                                                {return;}
            sprintf(str, "\"" "rcrd"    "\"" ":" "%d", rcrd             ); if(seguard(buf, str))    {return;} strcat(buf, str);

            if(oar_json_bridge(buf))                                                                {return;}
            sprintf(str, "\"" "ndx"     "\"" ":" "%d", ndx              ); if(seguard(buf, str))    {return;} strcat(buf, str);

            if(oar_json_bridge(buf))                                                                {return;}
            if(oar_json_append_id(buf))                                                             {return;}

            if(oar_json_bridge(buf))                                                                {return;}
            if(oar_json_append_ipv6_nbrs_ip(buf))                                                   {return;}

            if(oar_json_bridge(buf))                                                                {return;}
            sprintf(str, "\"" "hash"    "\"" ":" "%u", oar_sdbm(buf)    ); if(seguard(buf, str))    {return;} strcat(buf, str);

            if(oar_json_exit(buf))                                                                  {return;}
            
            break;
        
        case 9:
            oar_json_init(buf);
            if(oar_json_enter(buf))                                                                 {return;}

            oar_json_append_pckt(buf, 1, NULL, 0);

            if(oar_json_bridge(buf))                                                                {return;}
            sprintf(str, "\"" "rcrd"    "\"" ":" "%d", rcrd             ); if(seguard(buf, str))    {return;} strcat(buf, str);

            if(oar_json_bridge(buf))                                                                {return;}
            sprintf(str, "\"" "ndx"     "\"" ":" "%d", ndx              ); if(seguard(buf, str))    {return;} strcat(buf, str);

            if(oar_json_bridge(buf))                                                                {return;}
            if(oar_json_append_id(buf))                                                             {return;}

            if(oar_json_bridge(buf))                                                                {return;}
            if(oar_json_append_ipv6_nbrs_ll(buf))                                                   {return;}

            if(oar_json_bridge(buf))                                                                {return;}
            sprintf(str, "\"" "hash"    "\"" ":" "%u", oar_sdbm(buf)    ); if(seguard(buf, str))    {return;} strcat(buf, str);

            if(oar_json_exit(buf))                                                                  {return;}
            
            break;

        case 10:
            oar_json_init(buf);
            if(oar_json_enter(buf))                                                                 {return;}

            oar_json_append_pckt(buf, 1, NULL, 0);

            if(oar_json_bridge(buf))                                                                {return;}
            sprintf(str, "\"" "rcrd"    "\"" ":" "%d", rcrd             ); if(seguard(buf, str))    {return;} strcat(buf, str);

            if(oar_json_bridge(buf))                                                                {return;}
            sprintf(str, "\"" "ndx"     "\"" ":" "%d", ndx              ); if(seguard(buf, str))    {return;} strcat(buf, str);

            if(oar_json_bridge(buf))                                                                {return;}
            if(oar_json_append_id(buf))                                                             {return;}

            if(oar_json_bridge(buf))                                                                {return;}
            if(oar_json_append_ipv6_nbrs_states(buf))                                               {return;}

            if(oar_json_bridge(buf))                                                                {return;}
            sprintf(str, "\"" "hash"    "\"" ":" "%u", oar_sdbm(buf)    ); if(seguard(buf, str))    {return;} strcat(buf, str);

            if(oar_json_exit(buf))                                                                  {return;}
            
            break;

        case 11:
            oar_json_init(buf);
            if(oar_json_enter(buf))                                                                 {return;}

            oar_json_append_pckt(buf, 1, NULL, 0);

            if(oar_json_bridge(buf))                                                                {return;}
            sprintf(str, "\"" "rcrd"    "\"" ":" "%d", rcrd             ); if(seguard(buf, str))    {return;} strcat(buf, str);

            if(oar_json_bridge(buf))                                                                {return;}
            sprintf(str, "\"" "ndx"     "\"" ":" "%d", ndx              ); if(seguard(buf, str))    {return;} strcat(buf, str);

            if(oar_json_bridge(buf))                                                                {return;}
            if(oar_json_append_id(buf))                                                             {return;}

            if(oar_json_bridge(buf))                                                                {return;}
            if(oar_json_append_routing(buf))                                                        {return;}

            if(oar_json_bridge(buf))                                                                {return;}
            sprintf(str, "\"" "hash"    "\"" ":" "%u", oar_sdbm(buf)    ); if(seguard(buf, str))    {return;} strcat(buf, str);

            if(oar_json_exit(buf))                                                                  {return;}
            
            break;

        case 12:
            oar_json_init(buf);
            if(oar_json_enter(buf))                                                                 {return;}

            oar_json_append_pckt(buf, 1, NULL, 0);

            if(oar_json_bridge(buf))                                                                {return;}
            sprintf(str, "\"" "rcrd"    "\"" ":" "%d", rcrd             ); if(seguard(buf, str))    {return;} strcat(buf, str);

            if(oar_json_bridge(buf))                                                                {return;}
            sprintf(str, "\"" "ndx"     "\"" ":" "%d", ndx              ); if(seguard(buf, str))    {return;} strcat(buf, str);

            if(oar_json_bridge(buf))                                                                {return;}
            if(oar_json_append_id(buf))                                                             {return;}

            if(oar_json_bridge(buf))                                                                {return;}
            if(oar_json_append_routing_link_sources(buf))                                           {return;}

            if(oar_json_bridge(buf))                                                                {return;}
            sprintf(str, "\"" "hash"    "\"" ":" "%u", oar_sdbm(buf)    ); if(seguard(buf, str))    {return;} strcat(buf, str);

            if(oar_json_exit(buf))                                                                  {return;}
            
            break;

        case 13:
            oar_json_init(buf);
            if(oar_json_enter(buf))                                                                 {return;}

            oar_json_append_pckt(buf, 1, NULL, 0);

            if(oar_json_bridge(buf))                                                                {return;}
            sprintf(str, "\"" "rcrd"    "\"" ":" "%d", rcrd             ); if(seguard(buf, str))    {return;} strcat(buf, str);

            if(oar_json_bridge(buf))                                                                {return;}
            sprintf(str, "\"" "ndx"     "\"" ":" "%d", ndx              ); if(seguard(buf, str))    {return;} strcat(buf, str);

            if(oar_json_bridge(buf))                                                                {return;}
            if(oar_json_append_id(buf))                                                             {return;}

            if(oar_json_bridge(buf))                                                                {return;}
            if(oar_json_append_routing_link_destinations(buf))                                      {return;}

            if(oar_json_bridge(buf))                                                                {return;}
            sprintf(str, "\"" "hash"    "\"" ":" "%u", oar_sdbm(buf)    ); if(seguard(buf, str))    {return;} strcat(buf, str);

            if(oar_json_exit(buf))                                                                  {return;}
            
            break;

        case 14:
            oar_json_init(buf);
            if(oar_json_enter(buf))                                                                 {return;}

            oar_json_append_pckt(buf, 1, NULL, 0);

            if(oar_json_bridge(buf))                                                                {return;}
            sprintf(str, "\"" "rcrd"    "\"" ":" "%d", rcrd             ); if(seguard(buf, str))    {return;} strcat(buf, str);

            if(oar_json_bridge(buf))                                                                {return;}
            sprintf(str, "\"" "ndx"     "\"" ":" "%d", ndx              ); if(seguard(buf, str))    {return;} strcat(buf, str);

            if(oar_json_bridge(buf))                                                                {return;}
            if(oar_json_append_id(buf))                                                             {return;}

            if(oar_json_bridge(buf))                                                                {return;}
            if(oar_json_append_routing_entry_routes(buf))                                           {return;}

            if(oar_json_bridge(buf))                                                                {return;}
            sprintf(str, "\"" "hash"    "\"" ":" "%u", oar_sdbm(buf)    ); if(seguard(buf, str))    {return;} strcat(buf, str);

            if(oar_json_exit(buf))                                                                  {return;}
            
            break;

        case 15:
            oar_json_init(buf);
            if(oar_json_enter(buf))                                                                 {return;}

            oar_json_append_pckt(buf, 1, NULL, 0);

            if(oar_json_bridge(buf))                                                                {return;}
            sprintf(str, "\"" "rcrd"    "\"" ":" "%d", rcrd             ); if(seguard(buf, str))    {return;} strcat(buf, str);

            if(oar_json_bridge(buf))                                                                {return;}
            sprintf(str, "\"" "ndx"     "\"" ":" "%d", ndx              ); if(seguard(buf, str))    {return;} strcat(buf, str);

            if(oar_json_bridge(buf))                                                                {return;}
            if(oar_json_append_id(buf))                                                             {return;}

            if(oar_json_bridge(buf))                                                                {return;}
            if(oar_json_append_routing_entry_vias(buf))                                             {return;}

            if(oar_json_bridge(buf))                                                                {return;}
            sprintf(str, "\"" "hash"    "\"" ":" "%u", oar_sdbm(buf)    ); if(seguard(buf, str))    {return;} strcat(buf, str);

            if(oar_json_exit(buf))                                                                  {return;}
            
            break;

        case 16:
            oar_json_init(buf);
            if(oar_json_enter(buf))                                                                 {return;}

            oar_json_append_pckt(buf, 1, NULL, 0);

            if(oar_json_bridge(buf))                                                                {return;}
            sprintf(str, "\"" "rcrd"    "\"" ":" "%d", rcrd             ); if(seguard(buf, str))    {return;} strcat(buf, str);

            if(oar_json_bridge(buf))                                                                {return;}
            sprintf(str, "\"" "ndx"     "\"" ":" "%d", ndx              ); if(seguard(buf, str))    {return;} strcat(buf, str);

            if(oar_json_bridge(buf))                                                                {return;}
            if(oar_json_append_id(buf))                                                             {return;}

            if(oar_json_bridge(buf))                                                                {return;}
            if(oar_json_append_rpl_status(buf))                                                     {return;}

            if(oar_json_bridge(buf))                                                                {return;}
            sprintf(str, "\"" "hash"    "\"" ":" "%u", oar_sdbm(buf)    ); if(seguard(buf, str))    {return;} strcat(buf, str);

            if(oar_json_exit(buf))                                                                  {return;}
            
            break;

        case 17:
            oar_json_init(buf);
            if(oar_json_enter(buf))                                                                 {return;}

            oar_json_append_pckt(buf, 1, NULL, 0);

            if(oar_json_bridge(buf))                                                                {return;}
            sprintf(str, "\"" "rcrd"    "\"" ":" "%d", rcrd             ); if(seguard(buf, str))    {return;} strcat(buf, str);

            if(oar_json_bridge(buf))                                                                {return;}
            sprintf(str, "\"" "ndx"     "\"" ":" "%d", ndx              ); if(seguard(buf, str))    {return;} strcat(buf, str);

            if(oar_json_bridge(buf))                                                                {return;}
            if(oar_json_append_id(buf))                                                             {return;}

            if(oar_json_bridge(buf))                                                                {return;}
            if(oar_json_append_rpl_status_dag(buf))                                                 {return;}

            if(oar_json_bridge(buf))                                                                {return;}
            sprintf(str, "\"" "hash"    "\"" ":" "%u", oar_sdbm(buf)    ); if(seguard(buf, str))    {return;} strcat(buf, str);

            if(oar_json_exit(buf))                                                                  {return;}
            
            break;

        case 18:
            oar_json_init(buf);
            if(oar_json_enter(buf))                                                                 {return;}

            oar_json_append_pckt(buf, 1, NULL, 0);

            if(oar_json_bridge(buf))                                                                {return;}
            sprintf(str, "\"" "rcrd"    "\"" ":" "%d", rcrd             ); if(seguard(buf, str))    {return;} strcat(buf, str);

            if(oar_json_bridge(buf))                                                                {return;}
            sprintf(str, "\"" "ndx"     "\"" ":" "%d", ndx              ); if(seguard(buf, str))    {return;} strcat(buf, str);

            if(oar_json_bridge(buf))                                                                {return;}
            if(oar_json_append_id(buf))                                                             {return;}

            if(oar_json_bridge(buf))                                                                {return;}
            if(oar_json_append_rpl_status_trickle_timer(buf))                                       {return;}

            if(oar_json_bridge(buf))                                                                {return;}
            sprintf(str, "\"" "hash"    "\"" ":" "%u", oar_sdbm(buf)    ); if(seguard(buf, str))    {return;} strcat(buf, str);

            if(oar_json_exit(buf))                                                                  {return;}
            
            break;

        case 19:
            oar_json_init(buf);
            if(oar_json_enter(buf))                                                                 {return;}

            oar_json_append_pckt(buf, 1, NULL, 0);

            if(oar_json_bridge(buf))                                                                {return;}
            sprintf(str, "\"" "rcrd"    "\"" ":" "%d", rcrd             ); if(seguard(buf, str))    {return;} strcat(buf, str);

            if(oar_json_bridge(buf))                                                                {return;}
            sprintf(str, "\"" "ndx"     "\"" ":" "%d", ndx              ); if(seguard(buf, str))    {return;} strcat(buf, str);

            if(oar_json_bridge(buf))                                                                {return;}
            if(oar_json_append_id(buf))                                                             {return;}

            if(oar_json_bridge(buf))                                                                {return;}
            if(oar_json_append_rpl_neighbor(buf))                                                   {return;}

            if(oar_json_bridge(buf))                                                                {return;}
            sprintf(str, "\"" "hash"    "\"" ":" "%u", oar_sdbm(buf)    ); if(seguard(buf, str))    {return;} strcat(buf, str);

            if(oar_json_exit(buf))                                                                  {return;}
            
            break;

        case 20:
            oar_json_init(buf);
            if(oar_json_enter(buf))                                                                 {return;}

            oar_json_append_pckt(buf, 1, NULL, 0);

            if(oar_json_bridge(buf))                                                                {return;}
            sprintf(str, "\"" "rcrd"    "\"" ":" "%d", rcrd             ); if(seguard(buf, str))    {return;} strcat(buf, str);

            if(oar_json_bridge(buf))                                                                {return;}
            sprintf(str, "\"" "ndx"     "\"" ":" "%d", ndx              ); if(seguard(buf, str))    {return;} strcat(buf, str);

            if(oar_json_bridge(buf))                                                                {return;}
            if(oar_json_append_id(buf))                                                             {return;}

            if(oar_json_bridge(buf))                                                                {return;}
            if(oar_json_append_rpl_neighbor_ranks(buf))                                             {return;}

            if(oar_json_bridge(buf))                                                                {return;}
            sprintf(str, "\"" "hash"    "\"" ":" "%u", oar_sdbm(buf)    ); if(seguard(buf, str))    {return;} strcat(buf, str);

            if(oar_json_exit(buf))                                                                  {return;}
            
            break;

        case 21:
            oar_json_init(buf);
            if(oar_json_enter(buf))                                                                 {return;}

            oar_json_append_pckt(buf, 1, NULL, 0);

            if(oar_json_bridge(buf))                                                                {return;}
            sprintf(str, "\"" "rcrd"    "\"" ":" "%d", rcrd             ); if(seguard(buf, str))    {return;} strcat(buf, str);

            if(oar_json_bridge(buf))                                                                {return;}
            sprintf(str, "\"" "ndx"     "\"" ":" "%d", ndx              ); if(seguard(buf, str))    {return;} strcat(buf, str);

            if(oar_json_bridge(buf))                                                                {return;}
            if(oar_json_append_id(buf))                                                             {return;}

            if(oar_json_bridge(buf))                                                                {return;}
            if(oar_json_append_rpl_neighbor_values(buf))                                            {return;}

            if(oar_json_bridge(buf))                                                                {return;}
            sprintf(str, "\"" "hash"    "\"" ":" "%u", oar_sdbm(buf)    ); if(seguard(buf, str))    {return;} strcat(buf, str);

            if(oar_json_exit(buf))                                                                  {return;}
            
            break;

        case 22:
            oar_json_init(buf);
            if(oar_json_enter(buf))                                                                 {return;}

            oar_json_append_pckt(buf, 1, NULL, 0);

            if(oar_json_bridge(buf))                                                                {return;}
            sprintf(str, "\"" "rcrd"    "\"" ":" "%d", rcrd             ); if(seguard(buf, str))    {return;} strcat(buf, str);

            if(oar_json_bridge(buf))                                                                {return;}
            sprintf(str, "\"" "ndx"     "\"" ":" "%d", ndx              ); if(seguard(buf, str))    {return;} strcat(buf, str);

            if(oar_json_bridge(buf))                                                                {return;}
            if(oar_json_append_id(buf))                                                             {return;}

            if(oar_json_bridge(buf))                                                                {return;}
            if(oar_json_append_rpl_neighbor_parens(buf))                                            {return;}

            if(oar_json_bridge(buf))                                                                {return;}
            sprintf(str, "\"" "hash"    "\"" ":" "%u", oar_sdbm(buf)    ); if(seguard(buf, str))    {return;} strcat(buf, str);

            if(oar_json_exit(buf))                                                                  {return;}
            
            break;
        
        default:
            oar_json_init(buf);
            if(oar_json_enter(buf))                                                                 {return;}

            oar_json_append_pckt(buf, 1, NULL, 0);

            if(oar_json_bridge(buf))                                                                {return;}
            sprintf(str, "\"" "rcrd"    "\"" ":" "%d", rcrd             ); if(seguard(buf, str))    {return;} strcat(buf, str);

            if(oar_json_bridge(buf))                                                                {return;}
            sprintf(str, "\"" "ndx"     "\"" ":" "%d", ndx              ); if(seguard(buf, str))    {return;} strcat(buf, str);

            if(oar_json_bridge(buf))                                                                {return;}
            sprintf(str, "\"" "hash"    "\"" ":" "%u", oar_sdbm(buf)    ); if(seguard(buf, str))    {return;} strcat(buf, str);

            if(oar_json_exit(buf))                                                                  {return;}

            break;
    }
}