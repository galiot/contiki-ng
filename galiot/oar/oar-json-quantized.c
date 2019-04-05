#include "oar-json-quantized.h"
#include "project-conf.h"

#include "contiki.h"
#include "contiki-net.h"
#include "sys/node-id.h"
#include "sys/platform.h"
#include "sys/energest.h"
#include "sys/stack-check.h"
#include "dev/watchdog.h"

#include "net/link-stats.h"











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

    static const char *oar_json_quantized_ds6_nbr_state_to_str(uint8_t state)
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

    static const char *oar_json_quantized_rpl_state_to_str(enum rpl_dag_state state)
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
    static const char *oar_json_quantized_rpl_mop_to_str(int mop)
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

    static const char *oar_json_quantized_rpl_ocp_to_str(int ocp)
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

    static void oar_json_quantized_ipaddr_to_str(char *output, const uip_ipaddr_t *ipaddr) 
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

static void oar_json_quantized_lladdr_to_str(char *output, const linkaddr_t *lladdr) 
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

    static unsigned long oar_json_quantized_to_seconds(uint64_t time)
    {
        return (unsigned long)(time / ENERGEST_SECOND);
    }

#endif
// ######## (ENERGEST_CONF_ON)######## (ENERGEST_CONF_ON)######## (ENERGEST_CONF_ON)######## (ENERGEST_CONF_ON)######## (ENERGEST_CONF_ON)######## (ENERGEST_CONF_ON)######## (ENERGEST_CONF_ON)######## (ENERGEST_CONF_ON)######## (ENERGEST_CONF_ON)











// ====================================================================================================================
// DECLARATIONS ///////////////////////////////////////////////////////////////////////////////////////////////////////
// ====================================================================================================================

void oar_json_quantized_print(char * buf)
{
    printf("%s\n", buf);
}

// ######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)########
#if (NETSTACK_CONF_WITH_IPV6)

     static char oar_json_quantized_ipaddr[UIPLIB_IPV6_MAX_STR_LEN];

#endif //(NETSTACK_CONF_WITH_IPV6)
// ######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)########
    
static char oar_json_quantized_lladdr[UIPLIB_IPV6_MAX_STR_LEN];



















// ####################################################################################################################
// MAIN FUNCTIONS >>>>> BELOW <<<<< ///////////////////////////////////////////////////////////////////////////////////
// ####################################################################################################################

// ----------------------------------------------------------------------------
// function that initializes (empties) the json string ////////////////////////
// ----------------------------------------------------------------------------

static void oar_json_quantized_init(char * buf)
{
    memset(buf, 0, sizeof(buf));        // initialization
}

// ----------------------------------------------------------------------------
// function that appends the entry '{' json character to the string ///////////
// ----------------------------------------------------------------------------
static void oar_json_quantized_enter(char * buf)
{
    char str[128];
    sprintf(str,    "{" );  strcat(buf, str);
}

// ----------------------------------------------------------------------------
// function that connects the sections og the json, appending and ',' char ////
// ----------------------------------------------------------------------------

void oar_json_quantized_bridge(char * buf)
{
    char str[128];
    sprintf(str,    "," );  strcat(buf, str);
}

// ----------------------------------------------------------------------------
// function that appends the exit '}' json character to the string ////////////
// ----------------------------------------------------------------------------

static void oar_json_quantized_exit(char * buf)
{
    char str[128];
    sprintf(str,    "}" );  strcat(buf, str);
}

// ####################################################################################################################
// MAIN FUNCTIONS >>>>> CONTINUE <<<<< ////////////////////////////////////////////////////////////////////////////////
// ####################################################################################################################

// ----------------------------------------------------------------------------
// function that appends ID section to the json string ////////////////////////
// ----------------------------------------------------------------------------

static void oar_json_quantized_append_id(char * buf)
{
    char str[128];

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // SECTION START id{} //////////////////////////////
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    sprintf(str, "\"" "id" "\"" ":" ); strcat(buf, str);
    sprintf(str, "{"                ); strcat(buf, str);
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    
        // ttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttt
        sprintf(str, "\"" "sT"  "\"" ":" "%lu" ,clock_seconds()); strcat(buf, str); sprintf(str, ","); strcat(buf, str);
        // ttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttt

        oar_json_quantized_lladdr_to_str(oar_json_quantized_lladdr, &linkaddr_node_addr);
        sprintf(str,        "\""    "adr"   "\""    ":" "\""    "%s"                        "\""        ,oar_json_quantized_lladdr  );  strcat(buf, str);   // sprintf(str, ","); strcat(buf, str);

        // sprintf(str,     "\""    "cd"    "\""    ":" "\""    OAR_CONF_MOTE_COLOR         "\""                                    );  strcat(buf, str);
    
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    sprintf(str, "}" ); strcat(buf, str);
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // SECTION END id{} /////////////////
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
}

// ####################################################################################################################
// MAIN FUNCTIONS >>>>> CONTINUE <<<<< ////////////////////////////////////////////////////////////////////////////////
// ####################################################################################################################

// -----------------------------------------------------------------------------
// function that appends SYS section to the json string ////////////////////////
// -----------------------------------------------------------------------------

static void oar_json_quantized_append_sys(char * buf)
{
    char str[128];

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // SECTION START sys{} /////////////////////////////////
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    sprintf(str, "\"" "sys" "\"" ":"    ); strcat(buf, str);
    sprintf(str, "{"                    ); strcat(buf, str);
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

        sprintf(str,        "\"" "cV"   "\"" ":" "\""   CONTIKI_VERSION_STRING  "\""                                                        ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
        sprintf(str,        "\"" "rt"   "\"" ":" "\""   "%s"                    "\""    ,NETSTACK_ROUTING.name                              ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
        sprintf(str,        "\"" "net"  "\"" ":" "\""   "%s"                    "\""    ,NETSTACK_NETWORK.name                              ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
        sprintf(str,        "\"" "pId"  "\"" ":" "\""   "0x%04x"                "\""    ,IEEE802154_CONF_PANID                              ); strcat(buf, str);    // sprintf(str, ","); strcat(buf, str);
        
        // ??????????????????????????????????
        sprintf(str, ",");  strcat(buf, str);
        // ??????????????????????????????????
        
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // SUBSECTION START sys{} > mac{} //////////////////////
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        sprintf(str, "\"" "sys" "\"" ":"    ); strcat(buf, str);
        sprintf(str, "{"                    ); strcat(buf, str);
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        
            // #########(MAC_CONF_WITH_TSCH)#########(MAC_CONF_WITH_TSCH)#########(MAC_CONF_WITH_TSCH)#########(MAC_CONF_WITH_TSCH)#########(MAC_CONF_WITH_TSCH)#########(MAC_CONF_WITH_TSCH)#########(MAC_CONF_WITH_TSCH)#########
            #if MAC_CONF_WITH_TSCH
            
                sprintf(str,    "\"" "t"    "\"" ":" "\""   "%s"                    "\""    ,NETSTACK_MAC.name                                  ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                sprintf(str,    "\"" "tDhS" "\"" ":"        "%u"                            ,(unsigned)sizeof(TSCH_DEFAULT_HOPPING_SEQUENCE)    ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                sprintf(str,    "\"" "dCh"  "\"" ":"        "null"                                                                              ); strcat(buf, str);    
            
            // #########(MAC_CONF_WITH_TSCH)#########(MAC_CONF_WITH_TSCH)#########(MAC_CONF_WITH_TSCH)#########(MAC_CONF_WITH_TSCH)#########(MAC_CONF_WITH_TSCH)#########(MAC_CONF_WITH_TSCH)#########(MAC_CONF_WITH_TSCH)#########
            // ########!(MAC_CONF_WITH_TSCH)########!(MAC_CONF_WITH_TSCH)########!(MAC_CONF_WITH_TSCH)########!(MAC_CONF_WITH_TSCH)########!(MAC_CONF_WITH_TSCH)########!(MAC_CONF_WITH_TSCH)########!(MAC_CONF_WITH_TSCH)########!
            #else
            
                sprintf(str,    "\"" "t"    "\"" ":" "\""   "%s"                    "\""    ,NETSTACK_MAC.name                                  ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                sprintf(str,    "\"" "tDhS" "\"" ":"        "null"                                                                              ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                sprintf(str,    "\"" "dCh"  "\"" ":"        "%u"                            ,IEEE802154_DEFAULT_CHANNEL                         ); strcat(buf, str);    
            
            #endif
            // ########!(MAC_CONF_WITH_TSCH)########!(MAC_CONF_WITH_TSCH)########!(MAC_CONF_WITH_TSCH)########!(MAC_CONF_WITH_TSCH)########!(MAC_CONF_WITH_TSCH)########!(MAC_CONF_WITH_TSCH)########!(MAC_CONF_WITH_TSCH)########!

        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        sprintf(str, "}" ); strcat(buf, str);
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // SECTION END id{} > mac{} /////////
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

        // ??????????????????????????????????
        sprintf(str, ",");  strcat(buf, str);
        // ??????????????????????????????????
        
        sprintf(str,        "\"" "nId"   "\"" ":"        "%u"                            ,node_id                                            ); strcat(buf, str);   sprintf(str, ","); strcat(buf, str);
                                                                                                                                                                                                    
        // #########(NETSTACK_CONF_WITH_IPV6)#########(NETSTACK_CONF_WITH_IPV6)#########(NETSTACK_CONF_WITH_IPV6)#########(NETSTACK_CONF_WITH_IPV6)#########(NETSTACK_CONF_WITH_IPV6)#########(NETSTACK_CONF_WITH_IPV6)#########
        #if (NETSTACK_CONF_WITH_IPV6)
        
            uip_ds6_addr_t *lladdr;
            
            memcpy(&uip_lladdr.addr, &linkaddr_node_addr, sizeof(uip_lladdr.addr));
            lladdr = uip_ds6_get_link_local(-1);
            
            oar_json_quantized_ipaddr_to_str(oar_json_quantized_ipaddr, lladdr != NULL ? &lladdr->ipaddr : NULL);
            sprintf(str,    "\"" "tIad" "\"" ":" "\""   "%s"                    "\""    ,oar_json_quantized_ipaddr                           ); strcat(buf, str);
        
        // #########(NETSTACK_CONF_WITH_IPV6)#########(NETSTACK_CONF_WITH_IPV6)#########(NETSTACK_CONF_WITH_IPV6)#########(NETSTACK_CONF_WITH_IPV6)#########(NETSTACK_CONF_WITH_IPV6)#########(NETSTACK_CONF_WITH_IPV6)#########
        // ########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!
        #else  
        
            sprintf(str,    "\"" "tIadr" "\"" ":"       "null"                                                                              ); strcat(buf, str);
        
        #endif
        // ########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!
    
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    sprintf(str, "}" ); strcat(buf, str);
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // SECTION END id{} /////////////////
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
}

// ####################################################################################################################
// MAIN FUNCTIONS >>>>> CONTINUE <<<<< ////////////////////////////////////////////////////////////////////////////////
// ####################################################################################################################

// ----------------------------------------------------------------------------
// function that appends ENERGY section to the json string ////////////////////
// ----------------------------------------------------------------------------

static void oar_json_quantized_append_dev(char * buf)
{
    char str[128];
    
    int temperature = 15 + rand() % 30;
    int humidity = 80 + rand() % 17;

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // SECTION START dev{} /////////////////////////////////
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    sprintf(str, "\"" "dev" "\"" ":"    ); strcat(buf, str);   
    sprintf(str, "{"                    ); strcat(buf, str);
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

        sprintf(str, "\"" "tp"  "\"" ":" "%d"  ,temperature );  strcat(buf, str); sprintf(str,","); strcat(buf, str);
        sprintf(str, "\"" "hd"  "\"" ":" "%d"  ,humidity    );  strcat(buf, str); 

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    sprintf(str, "}" ); strcat(buf, str);
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // SECTION END dev{} ////////////////
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

}

// ####################################################################################################################
// MAIN FUNCTIONS >>>>> CONTINUE <<<<< ////////////////////////////////////////////////////////////////////////////////
// ####################################################################################################################

// ----------------------------------------------------------------------------
// function that appends ENERGY section to the json string ////////////////////
// ----------------------------------------------------------------------------

static void oar_json_quantized_append_nrg(char * buf)
{
    char str[128];

    // #########(ENERGEST_CONF_ON)#########(ENERGEST_CONF_ON)#########(ENERGEST_CONF_ON)#########(ENERGEST_CONF_ON)#########(ENERGEST_CONF_ON)#########(ENERGEST_CONF_ON)#########(ENERGEST_CONF_ON)#########
    #if (ENERGEST_CONF_ON)

        energest_flush();       // Update all energest times.
        
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // SECTION START nrg{} /////////////////////////////////
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        sprintf(str, "\"" "nrg" "\"" ":"    ); strcat(buf, str);   
        sprintf(str, "{"                    ); strcat(buf, str);
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

            sprintf(str, "\"" "en"  "\"" ":" "true"                                                                                                                                                    );  strcat(buf, str); sprintf(str,","); strcat(buf, str);

            sprintf(str, "\"" "cp"  "\"" ":" "%lu"  ,oar_json_quantized_to_seconds(energest_type_time(ENERGEST_TYPE_CPU))                                                                              );  strcat(buf, str); sprintf(str,","); strcat(buf, str);
            sprintf(str, "\"" "lp"  "\"" ":" "%lu"  ,oar_json_quantized_to_seconds(energest_type_time(ENERGEST_TYPE_LPM))                                                                              );  strcat(buf, str); sprintf(str,","); strcat(buf, str);
            sprintf(str, "\"" "dL"  "\"" ":" "%lu"  ,oar_json_quantized_to_seconds(energest_type_time(ENERGEST_TYPE_DEEP_LPM))                                                                         );  strcat(buf, str); sprintf(str,","); strcat(buf, str);
            sprintf(str, "\"" "tT"  "\"" ":" "%lu"  ,oar_json_quantized_to_seconds(ENERGEST_GET_TOTAL_TIME())                                                                                          );  strcat(buf, str); sprintf(str,","); strcat(buf, str);
            sprintf(str, "\"" "rL"  "\"" ":" "%lu"  ,oar_json_quantized_to_seconds(energest_type_time(ENERGEST_TYPE_LISTEN))                                                                           );  strcat(buf, str); sprintf(str,","); strcat(buf, str);
            sprintf(str, "\"" "rT"  "\"" ":" "%lu"  ,oar_json_quantized_to_seconds(energest_type_time(ENERGEST_TYPE_TRANSMIT))                                                                         );  strcat(buf, str); sprintf(str,","); strcat(buf, str);
            sprintf(str, "\"" "rO"  "\"" ":" "%lu"  ,oar_json_quantized_to_seconds(ENERGEST_GET_TOTAL_TIME() - energest_type_time(ENERGEST_TYPE_TRANSMIT) - energest_type_time(ENERGEST_TYPE_LISTEN))  );  strcat(buf, str); 
            
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        sprintf(str, "}" ); strcat(buf, str);
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // SECTION END mrg{} ////////////////
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    // #########(ENERGEST_CONF_ON)#########(ENERGEST_CONF_ON)#########(ENERGEST_CONF_ON)#########(ENERGEST_CONF_ON)#########(ENERGEST_CONF_ON)#########(ENERGEST_CONF_ON)#########(ENERGEST_CONF_ON)#########
    // ########!(ENERGEST_CONF_ON)########!(ENERGEST_CONF_ON)########!(ENERGEST_CONF_ON)########!(ENERGEST_CONF_ON)########!(ENERGEST_CONF_ON)########!(ENERGEST_CONF_ON)########!(ENERGEST_CONF_ON)########!
    #else
        
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // SECTION START mrg{} /////////////////////////////////
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        sprintf(str, "\"" "nrg" "\"" ":"    ); strcat(buf, str);   
        sprintf(str, "{"                    ); strcat(buf, str);
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

            sprintf(str, "\"" "en"  "\"" ":" "false"    ); strcat(buf, str); sprintf(str, ","); strcat(buf, str);

            sprintf(str, "\"" "cp"  "\"" ":" "null"     ); strcat(buf, str); sprintf(str, ","); strcat(buf, str);
            sprintf(str, "\"" "lp"  "\"" ":" "null"     ); strcat(buf, str); sprintf(str, ","); strcat(buf, str);
            sprintf(str, "\"" "dL"  "\"" ":" "null"     ); strcat(buf, str); sprintf(str, ","); strcat(buf, str);
            sprintf(str, "\"" "tT"  "\"" ":" "null"     ); strcat(buf, str); sprintf(str, ","); strcat(buf, str);
            sprintf(str, "\"" "rL"  "\"" ":" "null"     ); strcat(buf, str); sprintf(str, ","); strcat(buf, str);
            sprintf(str, "\"" "rT"  "\"" ":" "null"     ); strcat(buf, str); sprintf(str, ","); strcat(buf, str);
            sprintf(str, "\"" "rO"  "\"" ":" "null"     ); strcat(buf, str);
        
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        sprintf(str, "}" ); strcat(buf, str);
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // SECTION END mrg{} ////////////////
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    #endif
    // ########!(ENERGEST_CONF_ON)########!(ENERGEST_CONF_ON)########!(ENERGEST_CONF_ON)########!(ENERGEST_CONF_ON)########!(ENERGEST_CONF_ON)########!(ENERGEST_CONF_ON)########!(ENERGEST_CONF_ON)########!
}

// ####################################################################################################################
// MAIN FUNCTIONS >>>>> CONTINUE <<<<< ////////////////////////////////////////////////////////////////////////////////
// ####################################################################################################################

// ----------------------------------------------------------------------------
// function that appends IP STATS section to the json string //////////////////
// ----------------------------------------------------------------------------

static void oar_json_quantized_append_stats_IP(char * buf)
{
    char str[128];
    
    // ######## (UIP_CONF_STATISTICS)######## (UIP_CONF_STATISTICS)######## (UIP_CONF_STATISTICS)######## (UIP_CONF_STATISTICS)######## (UIP_CONF_STATISTICS)######## (UIP_CONF_STATISTICS)######## (UIP_CONF_STATISTICS)########
    #if (UIP_CONF_STATISTICS)

        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // SECTION START ipSt{} //////////////////////////////////////
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        sprintf(str, "\""   "ipSt"  "\""    ":"  ); strcat(buf, str);
        sprintf(str, "{"                        ); strcat(buf, str);
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

            sprintf(str, "\"" "uS"  "\"" ":" "true" ); strcat(buf, str);

            // ??????????????????????????????????
            sprintf(str, ",");  strcat(buf, str);
            // ??????????????????????????????????

            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            // SUBSECTION START ipSt{} > ip{} ///////////////////////////
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            sprintf(str, "\""   "ip"  "\""    ":"   ); strcat(buf, str);
            sprintf(str, "{"                        ); strcat(buf, str);
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~        
                
                sprintf(str, "\"" "rx"  "\"" ":" "%lu" ,uip_stat.ip.recv      ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                sprintf(str, "\"" "tx"  "\"" ":" "%lu" ,uip_stat.ip.sent      ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                sprintf(str, "\"" "fw"  "\"" ":" "%lu" ,uip_stat.ip.forwarded ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                sprintf(str, "\"" "dr"  "\"" ":" "%lu" ,uip_stat.ip.drop      ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                sprintf(str, "\"" "vE"  "\"" ":" "%lu" ,uip_stat.ip.vhlerr    ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                sprintf(str, "\"" "hE"  "\"" ":" "%lu" ,uip_stat.ip.hblenerr  ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                sprintf(str, "\"" "lE"  "\"" ":" "%lu" ,uip_stat.ip.lblenerr  ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                sprintf(str, "\"" "fE"  "\"" ":" "%lu" ,uip_stat.ip.fragerr   ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                sprintf(str, "\"" "cE"  "\"" ":" "%lu" ,uip_stat.ip.chkerr    ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                sprintf(str, "\"" "pE"  "\"" ":" "%lu" ,uip_stat.ip.protoerr  ); strcat(buf, str);

            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            sprintf(str, "}"); strcat(buf, str);
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            // SECTION END ipSt{} > ip{} ///////
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                                                                                                                                                                                
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        sprintf(str, "}"); strcat(buf, str);
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // SECTION END ipSt{} //////////////
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    // ######## (UIP_CONF_STATISTICS)######## (UIP_CONF_STATISTICS)######## (UIP_CONF_STATISTICS)######## (UIP_CONF_STATISTICS)######## (UIP_CONF_STATISTICS)######## (UIP_CONF_STATISTICS)######## (UIP_CONF_STATISTICS)########
    // ########!(UIP_CONF_STATISTICS)########!(UIP_CONF_STATISTICS)########!(UIP_CONF_STATISTICS)########!(UIP_CONF_STATISTICS)########!(UIP_CONF_STATISTICS)########!(UIP_CONF_STATISTICS)########!(UIP_CONF_STATISTICS)########!
    #else

        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // SECTION START ipSt{} /////////////////////////////////////
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        sprintf(str, "\""   "ipSt"  "\""    ":" ); strcat(buf, str);
        sprintf(str, "{"                        ); strcat(buf, str);
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

            sprintf(str, "\"" "uS"  "\"" ":" "false" ); strcat(buf, str);

            // ??????????????????????????????????
            sprintf(str, ",");  strcat(buf, str);
            // ??????????????????????????????????

            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            // SUBSECTION START ip{} > ipSt{} //////////////////////////
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            sprintf(str, "\""   "ip"  "\""    ":"   ); strcat(buf, str);
            sprintf(str, "{"                        ); strcat(buf, str);
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~       
                
                sprintf(str, "\"" "rx"  "\"" ":" "null"   ); strcat(buf, str); sprintf(str, ","); strcat(buf, str);
                sprintf(str, "\"" "tx"  "\"" ":" "null"   ); strcat(buf, str); sprintf(str, ","); strcat(buf, str);
                sprintf(str, "\"" "fw"  "\"" ":" "null"   ); strcat(buf, str); sprintf(str, ","); strcat(buf, str);
                sprintf(str, "\"" "dr"  "\"" ":" "null"   ); strcat(buf, str); sprintf(str, ","); strcat(buf, str);
                sprintf(str, "\"" "vE"  "\"" ":" "null"   ); strcat(buf, str); sprintf(str, ","); strcat(buf, str);
                sprintf(str, "\"" "hE"  "\"" ":" "null"   ); strcat(buf, str); sprintf(str, ","); strcat(buf, str);
                sprintf(str, "\"" "lE"  "\"" ":" "null"   ); strcat(buf, str); sprintf(str, ","); strcat(buf, str);
                sprintf(str, "\"" "fE"  "\"" ":" "null"   ); strcat(buf, str); sprintf(str, ","); strcat(buf, str);
                sprintf(str, "\"" "cE"  "\"" ":" "null"   ); strcat(buf, str); sprintf(str, ","); strcat(buf, str);
                sprintf(str, "\"" "pE"  "\"" ":" "null"   ); strcat(buf, str);

            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            sprintf(str, "}"); strcat(buf, str);
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            // SECTION END ip{} > ipSt{} ////////
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        sprintf(str, "}"); strcat(buf, str);
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // SECTION END ipSt{} ///////////////
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    
    #endif
    // ########!(UIP_CONF_STATISTICS)########!(UIP_CONF_STATISTICS)########!(UIP_CONF_STATISTICS)########!(UIP_CONF_STATISTICS)########!(UIP_CONF_STATISTICS)########!(UIP_CONF_STATISTICS)########!(UIP_CONF_STATISTICS)########!
}

// ####################################################################################################################
// MAIN FUNCTIONS >>>>> CONTINUE <<<<< ////////////////////////////////////////////////////////////////////////////////
// ####################################################################################################################

// ----------------------------------------------------------------------------
// function that appends ICMP STATS section to the json string ////////////////
// ----------------------------------------------------------------------------

static void oar_json_quantized_append_stats_ICMP(char * buf)
{
    char str[128];
    
    // ######## (UIP_CONF_STATISTICS)######## (UIP_CONF_STATISTICS)######## (UIP_CONF_STATISTICS)######## (UIP_CONF_STATISTICS)######## (UIP_CONF_STATISTICS)######## (UIP_CONF_STATISTICS)######## (UIP_CONF_STATISTICS)########
    #if (UIP_CONF_STATISTICS)

        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // SECTION START icSt{} ////////////////////////////////////
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        sprintf(str, "\""   "icSt"  "\""    ":"  ); strcat(buf, str);
        sprintf(str, "{"                        ); strcat(buf, str);
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

            sprintf(str, "\"" "uS"  "\"" ":" "true" ); strcat(buf, str);

            // ??????????????????????????????????
            sprintf(str, ",");  strcat(buf, str);
            // ??????????????????????????????????

            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            // SUBSECTION START icSt{} > ic{} //////////////////////////
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            sprintf(str, "\""   "ic"  "\""    ":"   ); strcat(buf, str);
            sprintf(str, "{"                        ); strcat(buf, str);
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

                sprintf(str, "\"" "rx"  "\"" ":" "%lu" ,uip_stat.icmp.recv      ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                sprintf(str, "\"" "tx"  "\"" ":" "%lu" ,uip_stat.icmp.sent      ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                sprintf(str, "\"" "dr"  "\"" ":" "%lu" ,uip_stat.icmp.drop      ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                sprintf(str, "\"" "tE"  "\"" ":" "%lu" ,uip_stat.icmp.typeerr   ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                sprintf(str, "\"" "cE"  "\"" ":" "%lu" ,uip_stat.icmp.chkerr    ); strcat(buf, str);               

            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            sprintf(str, "}"); strcat(buf, str);
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            // SECTION END icSt{} > icmp{} /////
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        sprintf(str, "}"); strcat(buf, str);
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // SECTION END icSt{} //////////////
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    // ######## (UIP_CONF_STATISTICS)######## (UIP_CONF_STATISTICS)######## (UIP_CONF_STATISTICS)######## (UIP_CONF_STATISTICS)######## (UIP_CONF_STATISTICS)######## (UIP_CONF_STATISTICS)######## (UIP_CONF_STATISTICS)########
    // ########!(UIP_CONF_STATISTICS)########!(UIP_CONF_STATISTICS)########!(UIP_CONF_STATISTICS)########!(UIP_CONF_STATISTICS)########!(UIP_CONF_STATISTICS)########!(UIP_CONF_STATISTICS)########!(UIP_CONF_STATISTICS)########!
    #else

        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // SECTION START icSt{} ////////////////////////////////////
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        sprintf(str, "\""   "icSt"  "\""    ":"  ); strcat(buf, str);
        sprintf(str, "{"                        ); strcat(buf, str);
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

            sprintf(str, "\"" "uS"  "\"" ":" "false" ); strcat(buf, str);

            // ??????????????????????????????????
            sprintf(str, ",");  strcat(buf, str);
            // ??????????????????????????????????

            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            // SUBSECTION START icSt{} > ic{} //////////////////////////
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            sprintf(str, "\""   "ic"  "\""    ":"   ); strcat(buf, str);
            sprintf(str, "{"                        ); strcat(buf, str);
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

                sprintf(str, "\"" "rx"  "\"" ":" "null"   ); strcat(buf, str); sprintf(str, ","); strcat(buf, str);
                sprintf(str, "\"" "tx"  "\"" ":" "null"   ); strcat(buf, str); sprintf(str, ","); strcat(buf, str);
                sprintf(str, "\"" "dr"  "\"" ":" "null"   ); strcat(buf, str); sprintf(str, ","); strcat(buf, str);
                sprintf(str, "\"" "tE"  "\"" ":" "null"   ); strcat(buf, str); sprintf(str, ","); strcat(buf, str);
                sprintf(str, "\"" "cE"  "\"" ":" "null"   ); strcat(buf, str); sprintf(str, ","); strcat(buf, str);

            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            sprintf(str, "}"); strcat(buf, str);
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            // SECTION END icSt{} > ic{} ///////
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ 

        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        sprintf(str, "}"); strcat(buf, str);
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // SECTION END icSt{} //////////////
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    #endif
    // ########!(UIP_CONF_STATISTICS)########!(UIP_CONF_STATISTICS)########!(UIP_CONF_STATISTICS)########!(UIP_CONF_STATISTICS)########!(UIP_CONF_STATISTICS)########!(UIP_CONF_STATISTICS)########!(UIP_CONF_STATISTICS)########!
}

// ####################################################################################################################
// MAIN FUNCTIONS >>>>> CONTINUE <<<<< ////////////////////////////////////////////////////////////////////////////////
// ####################################################################################################################

// ----------------------------------------------------------------------------
// function that appends TRANSPORT STATS section to the json string ///////////
// ----------------------------------------------------------------------------

static void oar_json_quantized_append_stats_transport(char * buf)
{
    char str[128];
    
    // ######## (UIP_CONF_STATISTICS)######## (UIP_CONF_STATISTICS)######## (UIP_CONF_STATISTICS)######## (UIP_CONF_STATISTICS)######## (UIP_CONF_STATISTICS)######## (UIP_CONF_STATISTICS)######## (UIP_CONF_STATISTICS)########
    #if (UIP_CONF_STATISTICS)

        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // SECTION START tSt{} //////////////////////////////////////
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        sprintf(str, "\""   "tSt"  "\""    ":"  ); strcat(buf, str);
        sprintf(str, "{"                        ); strcat(buf, str);
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

            sprintf(str, "\"" "uS"  "\"" ":" "true" ); strcat(buf, str);

            // ??????????????????????????????????
            sprintf(str, ",");  strcat(buf, str);
            // ??????????????????????????????????

                // ######## (UIP_CONF_STATISTICS)> (UIP_TCP)######## (UIP_CONF_STATISTICS)> (UIP_TCP)######## (UIP_CONF_STATISTICS)> (UIP_TCP)######## (UIP_CONF_STATISTICS)> (UIP_TCP)########
                #if (UIP_TCP)

                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    // SUBSECTION START tSt{} > tcp{} //////////////////////
                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    sprintf(str, "\"" "tcp" "\"" ":"    ); strcat(buf, str);
                    sprintf(str, "{"                    ); strcat(buf, str);
                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    
                        sprintf(str, "\"" "use" "\"" ":" "true"                         ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                        sprintf(str, "\"" "rx"  "\"" ":" "%lu"  ,uip_stat.tcp.recv      ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                        sprintf(str, "\"" "tx"  "\"" ":" "%lu"  ,uip_stat.tcp.sent      ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                        sprintf(str, "\"" "dr"  "\"" ":" "%lu"  ,uip_stat.tcp.drop      ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                        sprintf(str, "\"" "cE"  "\"" ":" "%lu"  ,uip_stat.tcp.chkerr    ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                        sprintf(str, "\"" "aA"  "\"" ":" "%lu"  ,uip_stat.tcp.ackerr    ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                        sprintf(str, "\"" "rst" "\"" ":" "%lu"  ,uip_stat.tcp.rst       ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                        sprintf(str, "\"" "rM"  "\"" ":" "%lu"  ,uip_stat.tcp.rexmit    ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                        sprintf(str, "\"" "sD"  "\"" ":" "%lu"  ,uip_stat.tcp.syndrop   ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                        sprintf(str, "\"" "sR"  "\"" ":" "%lu"  ,uip_stat.tcp.synrst    ); strcat(buf, str);                                                                                                                                                                                         

                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    sprintf(str, "}"); strcat(buf, str);
                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    // SUBSECTION END tST{} > tcp{} ////
                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ 
        
            // ######## (UIP_CONF_STATISTICS)> (UIP_TCP)######## (UIP_CONF_STATISTICS)> (UIP_TCP)######## (UIP_CONF_STATISTICS)> (UIP_TCP)######## (UIP_CONF_STATISTICS)> (UIP_TCP)########
            // ######## (UIP_CONF_STATISTICS)>!(UIP_TCP)######## (UIP_CONF_STATISTICS)>!(UIP_TCP)######## (UIP_CONF_STATISTICS)>!(UIP_TCP)######## (UIP_CONF_STATISTICS)>!(UIP_TCP)########
            #else

                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                // SUBSECTION START tSt{} > tcp{} //////////////////////
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                sprintf(str, "\"" "tcp" "\"" ":"    ); strcat(buf, str);
                sprintf(str, "{"                    ); strcat(buf, str);
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                
                    sprintf(str, "\"" "use" "\"" ":" "false"    ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                    sprintf(str, "\"" "rx"  "\"" ":" "null"     ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                    sprintf(str, "\"" "tx"  "\"" ":" "null"     ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                    sprintf(str, "\"" "dr"  "\"" ":" "null"     ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                    sprintf(str, "\"" "cE"  "\"" ":" "null"     ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                    sprintf(str, "\"" "aE"  "\"" ":" "null"     ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                    sprintf(str, "\"" "rst" "\"" ":" "null"     ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                    sprintf(str, "\"" "rM"  "\"" ":" "null"     ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                    sprintf(str, "\"" "sD"  "\"" ":" "null"     ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                    sprintf(str, "\"" "sR"  "\"" ":" "null"     ); strcat(buf, str);    sprintf(str, "," ); //strcat(buf, str);                                                                                                                                                                                      

                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                sprintf(str, "}"); strcat(buf, str);
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                // SUBSECTION END tSt{} > tcp{} ////
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

            #endif
            // ######## (UIP_CONF_STATISTICS)>!(UIP_TCP)######## (UIP_CONF_STATISTICS)>!(UIP_TCP)######## (UIP_CONF_STATISTICS)>!(UIP_TCP)######## (UIP_CONF_STATISTICS)>!(UIP_TCP)########

            // ??????????????????????????????????
            sprintf(str, ",");  strcat(buf, str);
            // ??????????????????????????????????

            // ######## (UIP_CONF_STATISTICS)> (UIP_UDP)######## (UIP_CONF_STATISTICS)> (UIP_UDP)######## (UIP_CONF_STATISTICS)> (UIP_UDP)######## (UIP_CONF_STATISTICS)> (UIP_UDP)########
            #if (UIP_UDP)

                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                // SUBSECTION START tSt{} > udp{} //////////////////////
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                sprintf(str, "\"" "udp" "\"" ":"    ); strcat(buf, str);
                sprintf(str, "{"                    ); strcat(buf, str);
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                
                    sprintf(str, "\"" "use" "\"" ":" "true"                         ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                    sprintf(str, "\"" "dr"  "\"" ":" "%lu"  ,uip_stat.udp.drop      ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                    sprintf(str, "\"" "rx"  "\"" ":" "%lu"  ,uip_stat.udp.recv      ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                    sprintf(str, "\"" "tx"  "\"" ":" "%lu"  ,uip_stat.udp.sent      ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                    sprintf(str, "\"" "cE"  "\"" ":" "%lu"  ,uip_stat.udp.chkerr    ); strcat(buf, str);                                                    

                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                sprintf(str, "}"); strcat(buf, str);
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                // SUBSECTION END tST{} > udp{} ////
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ 

            // ######## (UIP_CONF_STATISTICS)> (UIP_UDP)######## (UIP_CONF_STATISTICS)> (UIP_UDP)######## (UIP_CONF_STATISTICS)> (UIP_UDP)######## (UIP_CONF_STATISTICS)> (UIP_UDP)########
            // ######## (UIP_CONF_STATISTICS)>!(UIP_UDP)######## (UIP_CONF_STATISTICS)>!(UIP_UDP)######## (UIP_CONF_STATISTICS)>!(UIP_UDP)######## (UIP_CONF_STATISTICS)>!(UIP_UDP)########
            #else

                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                // SUBSECTION START tSt{} > udp{} //////////////////////
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                sprintf(str, "\"" "udp" "\"" ":"    ); strcat(buf, str);
                sprintf(str, "{"                    ); strcat(buf, str);
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                
                    sprintf(str, "\"" "use" "\"" ":" "false"    ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                    sprintf(str, "\"" "dr"  "\"" ":" "null"     ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                    sprintf(str, "\"" "rx"  "\"" ":" "null"     ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                    sprintf(str, "\"" "tx"  "\"" ":" "null"     ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                    sprintf(str, "\"" "cE"  "\"" ":" "null"     ); strcat(buf, str);                                                    

                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                sprintf(str, "}"); strcat(buf, str);
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                // SUBSECTION END tST{} > udp{} ////
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ 
        
            #endif
            // ######## (UIP_CONF_STATISTICS)>!(UIP_UDP)######## (UIP_CONF_STATISTICS)>!(UIP_UDP)######## (UIP_CONF_STATISTICS)>!(UIP_UDP)######## (UIP_CONF_STATISTICS)>!(UIP_UDP)########

        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        sprintf(str, "}"); strcat(buf, str);
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // SECTION END nSt{} ///////////////
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    
    // ######## (UIP_CONF_STATISTICS)######## (UIP_CONF_STATISTICS)######## (UIP_CONF_STATISTICS)######## (UIP_CONF_STATISTICS)######## (UIP_CONF_STATISTICS)######## (UIP_CONF_STATISTICS)######## (UIP_CONF_STATISTICS)########
    // ########!(UIP_CONF_STATISTICS)########!(UIP_CONF_STATISTICS)########!(UIP_CONF_STATISTICS)########!(UIP_CONF_STATISTICS)########!(UIP_CONF_STATISTICS)########!(UIP_CONF_STATISTICS)########!(UIP_CONF_STATISTICS)########!
    #else

        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // SECTION START tSt{} //////////////////////////////////////
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        sprintf(str, "\""   "tSt"  "\""    ":"  ); strcat(buf, str);
        sprintf(str, "{"                        ); strcat(buf, str);
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

            sprintf(str, "\"" "uS"  "\"" ":" "false" ); strcat(buf, str);

            // ??????????????????????????????????
            sprintf(str, ",");  strcat(buf, str);
            // ??????????????????????????????????

            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            // SUBSECTION START stats{} > tcp{} ////////////////////
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            sprintf(str, "\"" "tcp" "\"" ":"    ); strcat(buf, str);
            sprintf(str, "{"                    ); strcat(buf, str);
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            
                sprintf(str, "\"" "use" "\"" ":" "null"    ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                sprintf(str, "\"" "rx"  "\"" ":" "null"     ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                sprintf(str, "\"" "tx"  "\"" ":" "null"     ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                sprintf(str, "\"" "dr"  "\"" ":" "null"     ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                sprintf(str, "\"" "cE"  "\"" ":" "null"     ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                sprintf(str, "\"" "aE"  "\"" ":" "null"     ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                sprintf(str, "\"" "rst" "\"" ":" "null"     ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                sprintf(str, "\"" "rM"  "\"" ":" "null"     ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                sprintf(str, "\"" "sD"  "\"" ":" "null"     ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                sprintf(str, "\"" "sR"  "\"" ":" "null"     ); strcat(buf, str);    sprintf(str, "," ); //strcat(buf, str);                                                                                                                                                                                      

            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            sprintf(str, "}"); strcat(buf, str);
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            // SUBSECTION END stats{} > tcp{}
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

            // ??????????????????????????????????
            sprintf(str, ",");  strcat(buf, str);
            // ??????????????????????????????????

            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                // SUBSECTION START tSt{} > udp{} //////////////////////
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                sprintf(str, "\"" "udp" "\"" ":"    ); strcat(buf, str);
                sprintf(str, "{"                    ); strcat(buf, str);
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                
                    sprintf(str, "\"" "use" "\"" ":" "null" ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                    sprintf(str, "\"" "dr"  "\"" ":" "null" ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                    sprintf(str, "\"" "rx"  "\"" ":" "null" ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                    sprintf(str, "\"" "tx"  "\"" ":" "null" ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                    sprintf(str, "\"" "cE"  "\"" ":" "null" ); strcat(buf, str);                                                    

                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                sprintf(str, "}"); strcat(buf, str);
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                // SUBSECTION END tST{} > udp{} ////
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ 

        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        sprintf(str, "}"); strcat(buf, str);
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // SECTION END tSt{} ///////////////
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    #endif
    // ########!(UIP_CONF_STATISTICS)########!(UIP_CONF_STATISTICS)########!(UIP_CONF_STATISTICS)########!(UIP_CONF_STATISTICS)########!(UIP_CONF_STATISTICS)########!(UIP_CONF_STATISTICS)########!(UIP_CONF_STATISTICS)########!
}

// ####################################################################################################################
// MAIN FUNCTIONS >>>>> CONTINUE <<<<< ////////////////////////////////////////////////////////////////////////////////
// ####################################################################################################################

// ----------------------------------------------------------------------------
// function that appends NETWORK DISCOVERY STATS section to the json string ///
// ----------------------------------------------------------------------------

static void oar_json_quantized_append_stats_nd6(char * buf)
{
    char str[128];
    
    // ######## (UIP_CONF_STATISTICS)######## (UIP_CONF_STATISTICS)######## (UIP_CONF_STATISTICS)######## (UIP_CONF_STATISTICS)######## (UIP_CONF_STATISTICS)######## (UIP_CONF_STATISTICS)######## (UIP_CONF_STATISTICS)########
    #if (UIP_CONF_STATISTICS)

        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // SECTION START dSt{} /////////////////////////////////////
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        sprintf(str, "\""   "dSt"  "\""    ":"  ); strcat(buf, str);
        sprintf(str, "{"                        ); strcat(buf, str);
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

            sprintf(str, "\"" "uS"  "\"" ":" "true" ); strcat(buf, str);

            // ??????????????????????????????????
            sprintf(str, ",");  strcat(buf, str);
            // ??????????????????????????????????

            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            // SUBSECTION START dSt{} > nd6{} //////////////////////////
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            sprintf(str, "\""   "nd6"  "\""    ":"  ); strcat(buf, str);
            sprintf(str, "{"                        ); strcat(buf, str);
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~        
                
                sprintf(str, "\"" "dr" "\"" ":" "%lu" ,uip_stat.nd6.drop); strcat(buf, str);  sprintf(str, ","); strcat(buf, str);
                sprintf(str, "\"" "rx" "\"" ":" "%lu" ,uip_stat.nd6.recv); strcat(buf, str);  sprintf(str, ","); strcat(buf, str);
                sprintf(str, "\"" "tx" "\"" ":" "%lu" ,uip_stat.nd6.sent); strcat(buf, str);
            
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            sprintf(str, "}"); strcat(buf, str);
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            // SECTION END nSt{} > nd6{} ///////
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    sprintf(str, "}"); strcat(buf, str);
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // SECTION END tSt{} ///////////////
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    
    // ######## (UIP_CONF_STATISTICS)######## (UIP_CONF_STATISTICS)######## (UIP_CONF_STATISTICS)######## (UIP_CONF_STATISTICS)######## (UIP_CONF_STATISTICS)######## (UIP_CONF_STATISTICS)######## (UIP_CONF_STATISTICS)########
    // ########!(UIP_CONF_STATISTICS)########!(UIP_CONF_STATISTICS)########!(UIP_CONF_STATISTICS)########!(UIP_CONF_STATISTICS)########!(UIP_CONF_STATISTICS)########!(UIP_CONF_STATISTICS)########!(UIP_CONF_STATISTICS)########!
    #else

        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // SECTION START dSt{} /////////////////////////////////////
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        sprintf(str, "\""   "dSt"  "\""    ":"  ); strcat(buf, str);
        sprintf(str, "{"                        ); strcat(buf, str);
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

            sprintf(str, "\"" "uS"  "\"" ":" "false" ); strcat(buf, str);

            // ??????????????????????????????????
            sprintf(str, ",");  strcat(buf, str);
            // ??????????????????????????????????

            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            // SUBSECTION START dSt{} > nd6{} //////////////////////////
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            sprintf(str, "\""   "nd6"  "\""    ":"  ); strcat(buf, str);
            sprintf(str, "{"                        ); strcat(buf, str);
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~     

                sprintf(str, "\"" "dr" "\"" ":" "null"); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                sprintf(str, "\"" "rx" "\"" ":" "null"); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                sprintf(str, "\"" "tx" "\"" ":" "null"); strcat(buf, str);

            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            sprintf(str, "}"); strcat(buf, str);
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            // SECTION END nSt{} > nd6{} ///////
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        sprintf(str, "}"); strcat(buf, str);
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // SECTION END tSt{} ///////////////
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~   

    #endif
    // ########!(UIP_CONF_STATISTICS)########!(UIP_CONF_STATISTICS)########!(UIP_CONF_STATISTICS)########!(UIP_CONF_STATISTICS)########!(UIP_CONF_STATISTICS)########!(UIP_CONF_STATISTICS)########!(UIP_CONF_STATISTICS)########!
}

// ####################################################################################################################
// MAIN FUNCTIONS >>>>> CONTINUE <<<<< ////////////////////////////////////////////////////////////////////////////////
// ####################################################################################################################

// ----------------------------------------------------------------------------
// function that appends NET section to the json string ////////////////////
// ----------------------------------------------------------------------------

static void oar_json_quantized_append_net(char * buf)
{
    char str[128];
    
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // SECTION START net{} /////////////////////////////////
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    sprintf(str, "\"" "net" "\"" ":"    ); strcat(buf, str);   
    sprintf(str, "{"                    ); strcat(buf, str);
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    // ######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)########
    #if (NETSTACK_CONF_WITH_IPV6)

        sprintf(str, "\"" "v6" "\"" ":" "true"); strcat(buf, str);

        // ??????????????????????????????????
        sprintf(str, ",");  strcat(buf, str);
        // ?????????????????????????????????? 

        uint8_t state;

        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // SUBARRAY START net{} > addr[] /////////////////////////////////
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        sprintf(str, "\"" "addr" "\"" ":"         ); strcat(buf, str);  
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

            // [[[[[[[[[[[[[[[[[]]]]]]]]]]]]]]]]]
            sprintf(str, "["); strcat(buf, str);

            for(int i = 0; i < UIP_DS6_ADDR_NB; i++) 
            {
                state = uip_ds6_if.addr_list[i].state;

                if(uip_ds6_if.addr_list[i].isused && (state == ADDR_TENTATIVE || state == ADDR_PREFERRED)) 
                {   
                    oar_json_quantized_ipaddr_to_str(oar_json_quantized_ipaddr, &uip_ds6_if.addr_list[i].ipaddr);
                    sprintf(str, "\"" "%s"      "\"" ,oar_json_quantized_ipaddr   ); strcat(buf, str);

                    if (i != (UIP_DS6_ADDR_NB - 1)) { sprintf(str, "," );  strcat(buf, str); }
                }
                else
                {

                    sprintf(str, "\""  "null"   "\""                    ); strcat(buf, str);
                    if (i != (UIP_DS6_ADDR_NB - 1)) { sprintf(str, ","  );  strcat(buf, str); } 
                }
            }

            sprintf(str, "]"); strcat(buf, str);
            // [[[[[[[[[[[[[[[[[]]]]]]]]]]]]]]]]]

        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // SUBARRAY END  net{} > addr[] /////////////
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~   

        // ??????????????????????????????????
        sprintf(str, ",");  strcat(buf, str);
        // ?????????????????????????????????? 

            uip_ds6_nbr_t *nbr;
            int oar_json_quantized_ip_neighbor_count = 0;

            nbr = uip_ds6_nbr_head();

            if(nbr == NULL)
            {
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                //  (nbr == NULL) ///////////////////////////////////////////////
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                // SUBARRAY START net{} > nbrs[] > //////////////////////////////
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                sprintf(str, "\"" "nbrs" "\"" ":"); strcat(buf, str); ///////////
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

                    // [][][][][][][][][][][][][][][][][]
                    sprintf(str, "["); strcat(buf, str);

                    for (int i = 0; i < NBR_TABLE_CONF_MAX_NEIGHBORS; i++)
                    {
                        sprintf(str,    "null"  );  strcat(buf, str);
                        if (i != (NBR_TABLE_CONF_MAX_NEIGHBORS - 1)) { sprintf(str, "," );  strcat(buf, str); } 
                    }

                    sprintf(str, "]"); strcat(buf, str);
                    // [][][][][][][][][][][][][][][][][]
                
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                // SUBARRAY END  net{} > nbrs[] /////////////
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~   
            }
            else
            {
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                //  (nbr == NULL) ///////////////////////////////////////////////
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                // SUBARRAY START net{} > nbrs[] > //////////////////////////////
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                sprintf(str, "\"" "nbrs" "\"" ":"); strcat(buf, str); ///////////
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

                    // [[[[[[[[[[[[[[[[[]]]]]]]]]]]]]]]]]
                    sprintf(str, "["); strcat(buf, str);
                
                    while(nbr != NULL)
                    {
                        oar_json_quantized_ip_neighbor_count++;
                        
                        // {{{{{{{{{{{{{{{{{}}}}}}}}}}}}}}}}}
                        sprintf(str, "{"); strcat(buf, str);
                        
                            oar_json_quantized_ipaddr_to_str(oar_json_quantized_ipaddr, uip_ds6_nbr_get_ipaddr(nbr));
                            sprintf(str,    "\""    "ipAddr"    "\""    ":" "\""    "%s"    "\""    ,oar_json_quantized_ipaddr                            ); strcat(buf, str);    sprintf(str, ",");  strcat(buf, str);

                            oar_json_quantized_lladdr_to_str(oar_json_quantized_lladdr, (linkaddr_t *)uip_ds6_nbr_get_ll(nbr));
                            sprintf(str,    "\""    "llAddr"    "\""    ":" "\""    "%s"    "\""    ,oar_json_quantized_lladdr                            ); strcat(buf, str);    sprintf(str, ",");  strcat(buf, str);

                            sprintf(str,    "\""    "router"    "\""    ":"         "%u"            ,nbr->isrouter                              ); strcat(buf, str);    sprintf(str, ",");  strcat(buf, str);
                            sprintf(str,    "\""    "state"     "\""    ":" "\""    "%s"    "\""    ,oar_json_quantized_ds6_nbr_state_to_str(nbr->state)  ); strcat(buf, str);

                        sprintf(str, "}"); strcat(buf, str);
                        // {{{{{{{{{{{{{{{{{}}}}}}}}}}}}}}}}}

                        if (oar_json_quantized_ip_neighbor_count != NBR_TABLE_CONF_MAX_NEIGHBORS) { sprintf(str, "," );  strcat(buf, str); }
                        
                        nbr = uip_ds6_nbr_next(nbr);
                    }

                    for (int j = oar_json_quantized_ip_neighbor_count; j < NBR_TABLE_CONF_MAX_NEIGHBORS; j++)
                    {
                        sprintf(str,    "null"  );  strcat(buf, str);
                        
                        if (j != (NBR_TABLE_CONF_MAX_NEIGHBORS - 1)) { sprintf(str, "," );  strcat(buf, str); } 
                    }

                sprintf(str, "]"); strcat(buf, str);
                // [[[[[[[[[[[[[[[[[]]]]]]]]]]]]]]]]]
            }
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // SUBARRAY END  net{} > nbrs[] /////////////
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  
    
    // ######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)########
    // ########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!
    #else

        sprintf(str, "\"" "v6" "\"" ":" "false"); strcat(buf, str);

        // ??????????????????????????????????
        sprintf(str, ",");  strcat(buf, str);
        // ?????????????????????????????????? 

        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // SUBARRAY START net{} > addr[] /////////////////////////////////
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        sprintf(str, "\"" "addr" "\"" ":"         ); strcat(buf, str); ///  
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

            // [[[[[[[[[[[[[[[[]]]]]]]]]]]]]]]]
            sprintf(str,"["); strcat(buf, str);

            for(int i = 0; i < UIP_DS6_ADDR_NB; i++) 
            {
                sprintf(str, "\"" "null" "\""); strcat(buf, str);
                    
                if (i != (UIP_DS6_ADDR_NB - 1)) { sprintf(str, "," );  strcat(buf, str); }
            }

            sprintf(str, "]"); strcat(buf, str);
            // [[[[[[[[[[[[[[[[[]]]]]]]]]]]]]]]]]

        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // SUBARRAY END  net{} > addr[] /////////////
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

        // ??????????????????????????????????
        sprintf(str, ",");  strcat(buf, str);
        // ?????????????????????????????????? 

        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // SUBARRAY START net{} > nbrs[] /////////////////////////////////
        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        sprintf(str, "\"" "nbrs" "\"" ":"); strcat(buf, str); ////////////
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

        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // SUBARRAY END  net{} > nbrs[] /////////////
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~   

    #endif
    // ########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    sprintf(str, "}"); strcat(buf, str);
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // SECTION END net{} ///////////////
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
}

// ####################################################################################################################
// MAIN FUNCTIONS >>>>> CONTINUE <<<<< ////////////////////////////////////////////////////////////////////////////////
// ####################################################################################################################

// ----------------------------------------------------------------------------
// function that appends ROUTING section to the json string ///////////////////
// ----------------------------------------------------------------------------

static void oar_json_quantized_append_rt(char * buf)
{
    char str[128];

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // SECTION START rt{} /////////////////////////////////
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    sprintf(str, "\"" "rt" "\"" ":"     ); strcat(buf, str);   
    sprintf(str, "{"                    ); strcat(buf, str);
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

        // ######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)########
        #if (NETSTACK_CONF_WITH_IPV6)

            sprintf(str, "\"" "v6" "\"" ":" "true"); strcat(buf, str);

            // ??????????????????????????????????
            sprintf(str, ",");  strcat(buf, str);
            // ?????????????????????????????????? 

            uip_ds6_defrt_t *default_route;
            default_route = uip_ds6_defrt_lookup(uip_ds6_defrt_choose());

            if(default_route != NULL)
            {
                oar_json_quantized_ipaddr_to_str(oar_json_quantized_ipaddr, &default_route->ipaddr);
                sprintf(str,    "\""    "df"    "\""    ":" "\""    "%s"    "\""    ,oar_json_quantized_ipaddr   );  strcat(buf, str);   sprintf(str, "," );  strcat(buf, str);

                if (default_route->lifetime.interval != 0)  { sprintf(str,   "\""    "lt"   "\""    ":" "\""    "%lu"      "\""    ,(unsigned long)default_route->lifetime.interval      );  strcat(buf, str);   sprintf(str, "," );  strcat(buf, str); }
                else                                        { sprintf(str,   "\""    "lt"   "\""    ":" "\""    "infinite" "\""                                                          );  strcat(buf, str); }   // sprintf(str, "," );  strcat(buf, str);  
            }
            else
            {
                sprintf(str,    "\""    "df"    "\""    ":" "\""    "none"  "\""                            );  strcat(buf, str);   sprintf(str, "," );  strcat(buf, str);
                sprintf(str,    "\""    "lt"    "\""    ":"         "null"                                  );  strcat(buf, str);   

            }

            // ??????????????????????????????????
            sprintf(str, ",");  strcat(buf, str);
            // ??????????????????????????????????

            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            // SUBSECTION START rt{} > rLs{} ///////////////////////////////
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            sprintf(str, "\"" "rLs" "\"" ":"   ); strcat(buf, str); ////////
            sprintf(str, "{"                   ); strcat(buf, str); ////////
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            
                // ######## (NETSTACK_CONF_WITH_IPV6)> (UIP_CONF_IPV6_RPL)######## (NETSTACK_CONF_WITH_IPV6)> (UIP_CONF_IPV6_RPL)######## (NETSTACK_CONF_WITH_IPV6)> (UIP_CONF_IPV6_RPL)######## (NETSTACK_CONF_WITH_IPV6)> (UIP_CONF_IPV6_RPL)######## 
                #if (UIP_CONF_IPV6_RPL)

                    sprintf(str, "\"" "rpl" "\"" ":" "true"); strcat(buf, str);

                    // ??????????????????????????????????
                    sprintf(str, ",");  strcat(buf, str);
                    // ?????????????????????????????????? 

                    int oar_json_quantized_uip_sr_links_count = 0;

                    if (uip_sr_num_nodes() > 0)
                    {
                    
                        uip_sr_node_t *link;
                        link = uip_sr_node_head();

                        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                        //  (uip_sr_num_nodes() > 0) ////////////////////////////////
                        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                        // SUBARRAY START net{} > rLs{} > ls[] //////////////////////
                        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                        sprintf(str, "\"" "ls" "\"" ":" ); strcat(buf, str); ////////
                        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

                            // [[[[[[[[[[[[[[[[]]]]]]]]]]]]]]]]
                            sprintf(str,"["); strcat(buf, str);
                            
                            while(link != NULL) 
                            {
                                char goa_buf[100];
                                oar_json_quantized_uip_sr_links_count++;

                                uip_sr_link_snprint(goa_buf, sizeof(goa_buf), link);
                                
                                sprintf(str,    "\""    "%s"    "\""    ,goa_buf ); strcat(buf, str);
                                
                                if (oar_json_quantized_uip_sr_links_count != NBR_TABLE_CONF_MAX_NEIGHBORS)    { sprintf(str, "," );  strcat(buf, str); }

                                link = uip_sr_node_next(link);
                            }

                            for (int j = oar_json_quantized_uip_sr_links_count; j < NBR_TABLE_CONF_MAX_NEIGHBORS; j++)
                            {
                                
                                sprintf(str,    "\""    "null"    "\""  ); strcat(buf, str);
                                
                                if (j != (NBR_TABLE_CONF_MAX_NEIGHBORS - 1)) { sprintf(str, "," );  strcat(buf, str); };
                            }

                            sprintf(str, "]"); strcat(buf, str);   
                            // [[[[[[[[[[[[[[[[[]]]]]]]]]]]]]]]]]

                        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                        // SUBARRAY END net{} > rLs{} > ls[] ////////////////////////
                        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    }
                    else
                    {
                        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                        // !(uip_sr_num_nodes() > 0) ////////////////////////////////
                        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                        // SUBARRAY START net{} > rLs{} > ls[] //////////////////////
                        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                        sprintf(str, "\"" "ls" "\"" ":"); strcat(buf, str); /////////
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
                        
                        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                        // SUBARRAY END net{} > rLs{} > ls[] ////////////////////////
                        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    }

                // ######## (NETSTACK_CONF_WITH_IPV6)> (UIP_CONF_IPV6_RPL)######## (NETSTACK_CONF_WITH_IPV6)> (UIP_CONF_IPV6_RPL)######## (NETSTACK_CONF_WITH_IPV6)> (UIP_CONF_IPV6_RPL)######## (NETSTACK_CONF_WITH_IPV6)> (UIP_CONF_IPV6_RPL)######## 
                // ######## (NETSTACK_CONF_WITH_IPV6)>!(UIP_CONF_IPV6_RPL)######## (NETSTACK_CONF_WITH_IPV6)>!(UIP_CONF_IPV6_RPL)######## (NETSTACK_CONF_WITH_IPV6)>!(UIP_CONF_IPV6_RPL)######## (NETSTACK_CONF_WITH_IPV6)>!(UIP_CONF_IPV6_RPL)######## 
                #else

                    sprintf(str, "\"" "rpl" "\"" ":" "true"); strcat(buf, str);

                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    // SUBARRAY START net{} > rLs{} > ls[] //////////////////////
                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    sprintf(str, "\"" "ls" "\"" ":"); strcat(buf, str); /////////
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

                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    // SUBARRAY END net{} > rLs{} > ls[] ////////////////////////
                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

                #endif
                // ######## (NETSTACK_CONF_WITH_IPV6)>!(UIP_CONF_IPV6_RPL)######## (NETSTACK_CONF_WITH_IPV6)>!(UIP_CONF_IPV6_RPL)######## (NETSTACK_CONF_WITH_IPV6)>!(UIP_CONF_IPV6_RPL)######## (NETSTACK_CONF_WITH_IPV6)>!(UIP_CONF_IPV6_RPL)########
            
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            sprintf(str, "}"); strcat(buf, str); //////////////
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            // SUBSECTION END rt{} > rLs{} ////////////////////
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

            // ??????????????????????????????????
            sprintf(str, ",");  strcat(buf, str);
            // ??????????????????????????????????

            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            // SUBSECTION START rt{} > rEs /////////////////////////////////
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            sprintf(str, "\"" "rE" "\"" ":"     ); strcat(buf, str); ///////
            sprintf(str, "{"                    ); strcat(buf, str); ///////
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

            // ######## (NETSTACK_CONF_WITH_IPV6)> (UIP_MAX_ROUTES != 0)######## (NETSTACK_CONF_WITH_IPV6)> (UIP_MAX_ROUTES != 0)######## (NETSTACK_CONF_WITH_IPV6)> (UIP_MAX_ROUTES != 0)######## (NETSTACK_CONF_WITH_IPV6)> (UIP_MAX_ROUTES != 0)######## 
            #if (UIP_MAX_ROUTES != 0)

                sprintf(str, "\"" "xRtsNZ" "\"" ":" "true"); strcat(buf, str);

                // ??????????????????????????????????
                sprintf(str, ",");  strcat(buf, str);
                // ??????????????????????????????????

                if(uip_ds6_route_num_routes() > 0)
                {
                    uip_ds6_route_t *route;
                    sprintf(str, "\"" "totEs" "\"" ":" "%u" ,uip_ds6_route_num_routes()); strcat(buf, str);

                    // ??????????????????????????????????
                    sprintf(str, ",");  strcat(buf, str);
                    // ?????????????????????????????????? 

                    route = uip_ds6_route_head();
                    int oar_json_quantized_ds6_route_count = 0;

                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    //  (uip_ds6_route_num_routes() > 0) ////////////////////////////
                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    // SUBARRAY START rt{} > rEs > es[] /////////////////////////////
                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    sprintf(str, "\"" "es" "\"" ":"); strcat(buf, str); /////////////
                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

                    // [[[[[[[[[[[[[[[[]]]]]]]]]]]]]]]]
                    sprintf(str,"["); strcat(buf, str);
                    
                    while(route != NULL) 
                    {
                        oar_json_quantized_ds6_route_count++;

                        // {{{{{{{{{{{{{{{{{}}}}}}}}}}}}}}}}}
                        sprintf(str, "{"); strcat(buf, str);

                            oar_json_quantized_ipaddr_to_str(oar_json_quantized_ipaddr, &route->ipaddr);
                            sprintf(str,    "\""    "rt"     "\""    ":" "\""    "%s"    "\""    ,oar_json_quantized_ipaddr); strcat(buf, str);    sprintf(str, "," );  strcat(buf, str);

                            oar_json_quantized_ipaddr_to_str(oar_json_quantized_ipaddr, uip_ds6_route_nexthop(route));
                            sprintf(str,    "\""    "via"       "\""    ":" "\""    "%s"    "\""    ,oar_json_quantized_ipaddr); strcat(buf, str);    sprintf(str, "," );  strcat(buf, str);

                            if ((unsigned long)route->state.lifetime != 0xFFFFFFFF) { sprintf(str,  "\""  "lf"    "\""    ":"         "%u"                ,(unsigned long)route->state.lifetime); strcat(buf, str); }
                            else                                                    { sprintf(str,  "\""  "lf"    "\""    ":" "\""    "infinite"  "\""                                         ); strcat(buf, str); }

                        // {{{{{{{{{{{{{{{{{}}}}}}}}}}}}}}}}}
                        sprintf(str, "}"); strcat(buf, str);
                    
                        if (oar_json_quantized_ds6_route_count != NBR_TABLE_CONF_MAX_NEIGHBORS)    { sprintf(str, "," );  strcat(buf, str); }
                    }

                    for (int j = oar_json_quantized_ds6_route_count; j < NBR_TABLE_CONF_MAX_NEIGHBORS; j++)
                    {
                        
                        sprintf(str,    "\""    "null"    "\""  ); strcat(buf, str);
                        
                        if (j != (NBR_TABLE_CONF_MAX_NEIGHBORS - 1)) { sprintf(str, "," );  strcat(buf, str); };
                    }

                    sprintf(str, "]"); strcat(buf, str);
                    // [[[[[[[[[[[[[[[[[]]]]]]]]]]]]]]]]]
                }
                else
                {
                    sprintf(str, "\"" "totEs" "\"" ":" "\"" "none" "\"" ); strcat(buf, str);    
                        
                    // ??????????????????????????????????
                    sprintf(str, ",");  strcat(buf, str);
                    // ?????????????????????????????????? 

                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    // !(uip_ds6_route_num_routes() > 0) ////////////////////////////
                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    // SUBARRAY START net{} > routes{} > routingEntries{} > entries[]
                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    sprintf(str, "\"" "es" "\"" ":"); strcat(buf, str); /////////////
                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    
                        // [[[[[[[[[[[[[[[[]]]]]]]]]]]]]]]]
                        sprintf(str,"["); strcat(buf, str);

                        for (int j = 0; j < NBR_TABLE_CONF_MAX_NEIGHBORS; j++)
                        {
                            
                            sprintf(str,    "\""    "null"    "\""  ); strcat(buf, str);
                            
                            if (j != (NBR_TABLE_CONF_MAX_NEIGHBORS - 1)) { sprintf(str, "," );  strcat(buf, str); };
                        }

                        sprintf(str, "]"); strcat(buf, str);
                        // [[[[[[[[[[[[[[[[[]]]]]]]]]]]]]]]]]
                }

            // ######## (NETSTACK_CONF_WITH_IPV6)> (UIP_MAX_ROUTES != 0)######## (NETSTACK_CONF_WITH_IPV6)> (UIP_MAX_ROUTES != 0)######## (NETSTACK_CONF_WITH_IPV6)> (UIP_MAX_ROUTES != 0)######## (NETSTACK_CONF_WITH_IPV6)> (UIP_MAX_ROUTES != 0)######## 
            // ######## (NETSTACK_CONF_WITH_IPV6)>!(UIP_MAX_ROUTES != 0)######## (NETSTACK_CONF_WITH_IPV6)>!(UIP_MAX_ROUTES != 0)######## (NETSTACK_CONF_WITH_IPV6)>!(UIP_MAX_ROUTES != 0)######## (NETSTACK_CONF_WITH_IPV6)>!(UIP_MAX_ROUTES != 0)######## 
            #else

                sprintf(str, "\"" "xRtsNZ" "\"" ":" "false"); strcat(buf, str);

                // ??????????????????????????????????
                sprintf(str, ",");  strcat(buf, str);
                // ??????????????????????????????????

                sprintf(str, "\"" "totEs" "\"" ":" "null" ); strcat(buf, str); 

                // ??????????????????????????????????
                sprintf(str, ",");  strcat(buf, str);
                // ?????????????????????????????????? 

                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                // SUBARRAY START net{} > routes{} > routingEntries{} > entries[]
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                sprintf(str, "\"" "es" "\"" ":"); strcat(buf, str); /////////////
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                
                    // [[[[[[[[[[[[[[[[]]]]]]]]]]]]]]]]
                    sprintf(str,"["); strcat(buf, str);

                    for (int j = 0; j < NBR_TABLE_CONF_MAX_NEIGHBORS; j++)
                    {
                        
                        sprintf(str,    "\""    "null"    "\""  ); strcat(buf, str);
                        
                        if (j != (NBR_TABLE_CONF_MAX_NEIGHBORS - 1)) { sprintf(str, "," );  strcat(buf, str); };
                    }

                    sprintf(str, "]"); strcat(buf, str);
                    // [[[[[[[[[[[[[[[[[]]]]]]]]]]]]]]]]]

            #endif
            // ######## (NETSTACK_CONF_WITH_IPV6)>!(UIP_MAX_ROUTES != 0)######## (NETSTACK_CONF_WITH_IPV6)>!(UIP_MAX_ROUTES != 0)######## (NETSTACK_CONF_WITH_IPV6)>!(UIP_MAX_ROUTES != 0)######## (NETSTACK_CONF_WITH_IPV6)>!(UIP_MAX_ROUTES != 0)######## 

            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            sprintf(str, "}"); strcat(buf, str); //////////////
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            // SUBSECTION END rt{} > rEs{} ////////////////////
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


        // ######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)########
        // ########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!
        #else

            sprintf(str, "\"" "v6" "\"" ":" "false"); strcat(buf, str);
            
            sprintf(str, "\"" "df"  "\"" ":"    "null"      ); strcat(buf, str);   sprintf(str, "," ); strcat(buf, str);
            sprintf(str, "\"" "lt"  "\"" ":"    "null"      ); strcat(buf, str); 

            // ??????????????????????????????????
            sprintf(str, ",");  strcat(buf, str);
            // ?????????????????????????????????? 

            // ########!(NETSTACK_CONF_WITH_IPV6)> (UIP_CONF_IPV6_RPL)########!(NETSTACK_CONF_WITH_IPV6)> (UIP_CONF_IPV6_RPL)########!(NETSTACK_CONF_WITH_IPV6)> (UIP_CONF_IPV6_RPL)########!(NETSTACK_CONF_WITH_IPV6)> (UIP_CONF_IPV6_RPL)######## 
            #if (UIP_CONF_IPV6_RPL)

                sprintf(str, "\"" "rpl" "\"" ":" "flase"); strcat(buf, str);




            // ########!(NETSTACK_CONF_WITH_IPV6)> (UIP_CONF_IPV6_RPL)########!(NETSTACK_CONF_WITH_IPV6)> (UIP_CONF_IPV6_RPL)########!(NETSTACK_CONF_WITH_IPV6)> (UIP_CONF_IPV6_RPL)########!(NETSTACK_CONF_WITH_IPV6)> (UIP_CONF_IPV6_RPL)######## 
            // ########!(NETSTACK_CONF_WITH_IPV6)>!(UIP_CONF_IPV6_RPL)########!(NETSTACK_CONF_WITH_IPV6)>!(UIP_CONF_IPV6_RPL)########!(NETSTACK_CONF_WITH_IPV6)>!(UIP_CONF_IPV6_RPL)########!(NETSTACK_CONF_WITH_IPV6)>!(UIP_CONF_IPV6_RPL)######## 
            #else

            #endif 
            // ########!(NETSTACK_CONF_WITH_IPV6)>!(UIP_CONF_IPV6_RPL)########!(NETSTACK_CONF_WITH_IPV6)>!(UIP_CONF_IPV6_RPL)########!(NETSTACK_CONF_WITH_IPV6)>!(UIP_CONF_IPV6_RPL)########!(NETSTACK_CONF_WITH_IPV6)>!(UIP_CONF_IPV6_RPL)######## 

            // ########!(NETSTACK_CONF_WITH_IPV6)> (UIP_MAX_ROUTES != 0)########!(NETSTACK_CONF_WITH_IPV6)> (UIP_MAX_ROUTES != 0)########!(NETSTACK_CONF_WITH_IPV6)> (UIP_MAX_ROUTES != 0)########!(NETSTACK_CONF_WITH_IPV6)> (UIP_MAX_ROUTES != 0)########! 
            #if (UIP_MAX_ROUTES != 0)

            // ########!(NETSTACK_CONF_WITH_IPV6)> (UIP_MAX_ROUTES != 0)########!(NETSTACK_CONF_WITH_IPV6)> (UIP_MAX_ROUTES != 0)########!(NETSTACK_CONF_WITH_IPV6)> (UIP_MAX_ROUTES != 0)########!(NETSTACK_CONF_WITH_IPV6)> (UIP_MAX_ROUTES != 0)########! 
            // ########!(NETSTACK_CONF_WITH_IPV6)>!(UIP_MAX_ROUTES != 0)########!(NETSTACK_CONF_WITH_IPV6)>!(UIP_MAX_ROUTES != 0)########!(NETSTACK_CONF_WITH_IPV6)>!(UIP_MAX_ROUTES != 0)########!(NETSTACK_CONF_WITH_IPV6)>!(UIP_MAX_ROUTES != 0)########! 
            #else

            #endif 
            // ########!(NETSTACK_CONF_WITH_IPV6)>!(UIP_MAX_ROUTES != 0)########!(NETSTACK_CONF_WITH_IPV6)>!(UIP_MAX_ROUTES != 0)########!(NETSTACK_CONF_WITH_IPV6)>!(UIP_MAX_ROUTES != 0)########!(NETSTACK_CONF_WITH_IPV6)>!(UIP_MAX_ROUTES != 0)########! 
             


        #endif
        // ########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    sprintf(str, "}"); strcat(buf, str);
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // SECTION END net{} ///////////////
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
}

// ####################################################################################################################
// MAIN FUNCTIONS >>>>> CONTINUE <<<<< ////////////////////////////////////////////////////////////////////////////////
// ####################################################################################################################

// ----------------------------------------------------------------------------
// function that appends RPL STATUS section to the json string ////////////////
// ----------------------------------------------------------------------------

static void oar_json_quantized_append_rpl_status(char * buf)
{
    char str[128];
    
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // SECTION START rSt{} /////////////////////////////////
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    sprintf(str, "\"" "rSt" "\"" ":"    ); strcat(buf, str);   
    sprintf(str, "{"                    ); strcat(buf, str);
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

        // ######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)########
        #if (ROUTING_CONF_RPL_LITE)

            sprintf(str, "\"" "rL" "\"" ":" "true");  strcat(buf, str);

            // ??????????????????????????????????
            sprintf(str, ",");  strcat(buf, str);
            // ?????????????????????????????????? 

            if(!curr_instance.used)             
                { 
                    sprintf(str, "\"" "iId" "\"" ":" "\"" "none" "\""); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                    
                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    // (!curr_instance.used) ///////////////////////////
                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    // SUBSECTION START rSt{} > dag{} //////////////////
                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    sprintf(str, "\"" "dag" "\"" ":"); strcat(buf, str);
                    sprintf(str, "{"                ); strcat(buf, str);
                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    
                        sprintf(str, "\"" "dT"      "\"" ":" "null" ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                        sprintf(str, "\"" "dId"     "\"" ":" "null" ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                        sprintf(str, "\"" "dVer"    "\"" ":" "null" ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                        sprintf(str, "\"" "dPf"     "\"" ":" "null" ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                        sprintf(str, "\"" "dPfL"    "\"" ":" "null" ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                        sprintf(str, "\"" "st"      "\"" ":" "null" ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                        sprintf(str, "\"" "pP"      "\"" ":" "null" ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                        sprintf(str, "\"" "rk"      "\"" ":" "null" ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                        sprintf(str, "\"" "lRk"     "\"" ":" "null" ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                        sprintf(str, "\"" "mRkI"    "\"" ":" "null" ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                        
                        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                        // SUBSECTION START rSt{} > dag{} > dao{} /////////////////////
                        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                        sprintf(str, "\"" "dao" "\"" ":"); strcat(buf, str); //////////
                        sprintf(str, "{"                ); strcat(buf, str); //////////
                        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

                            sprintf(str, "\"" "lS"    "\"" ":" "null"     ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                            sprintf(str, "\"" "lA"   "\"" ":" "null"     ); strcat(buf, str);

                        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                        // SUSECTION END rSt{} > dag{} > dao{} /////////////////////
                        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                        sprintf(str, "}"); strcat(buf, str); ///////////////////////
                        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                
                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    // SUSECTION END rSt{} > dag{} /////////////
                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    sprintf(str, "}"); strcat(buf, str); ///////
                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    
                    // ??????????????????????????????????
                    sprintf(str, ",");  strcat(buf, str);
                    // ?????????????????????????????????? 

                    sprintf(str, "\"" "mop"     "\"" ":" "null"); strcat(buf, str); sprintf(str, ","); strcat(buf, str);
                    sprintf(str, "\"" "of"      "\"" ":" "null"); strcat(buf, str); sprintf(str, ","); strcat(buf, str);
                    sprintf(str, "\"" "hRkI"    "\"" ":" "null"); strcat(buf, str); sprintf(str, ","); strcat(buf, str);
                    sprintf(str, "\"" "dLt"     "\"" ":" "null"); strcat(buf, str); sprintf(str, ","); strcat(buf, str);
                    sprintf(str, "\"" "dO"      "\"" ":" "null"); strcat(buf, str); sprintf(str, ","); strcat(buf, str);

                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    // SUBSECTION START rSt{} > tT{} ///////////////////////////////
                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    sprintf(str, "\"" "tT" "\"" ":"   ); strcat(buf, str);
                    sprintf(str, "{"                  ); strcat(buf, str);
                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

                        sprintf(str,    "\""    "cur"   "\""    ":" "null"    );  strcat(buf, str);   sprintf(str,    "," );  strcat(buf, str);
                        sprintf(str,    "\""    "nim"   "\""    ":" "null"    );  strcat(buf, str);   sprintf(str,    "," );  strcat(buf, str);
                        sprintf(str,    "\""    "max"   "\""    ":" "null"    );  strcat(buf, str);   sprintf(str,    "," );  strcat(buf, str);
                        sprintf(str,    "\""    "red"   "\""    ":" "null"    );  strcat(buf, str);   

                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    // SUBSECTION END rSt{} > tT{} //////////////////////
                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    sprintf(str, "}"); strcat(buf, str); ////////////////
                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                
                } 
                else                                
                { 
                    sprintf(str, "\"" "iId" "\"" ":" "%u" ,curr_instance.instance_id); strcat(buf, str); sprintf(str, "," ); strcat(buf, str);

                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    // !(!curr_instance.used) //////////////////////////
                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    // SUBSECTION START rSt{} > dag{} //////////////////
                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    sprintf(str, "\"" "dag" "\"" ":"); strcat(buf, str);
                    sprintf(str, "{"                ); strcat(buf, str);
                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    
                        // sprintf(str, "\"" "valid"          "\"" ":"         "true"                                                                  ); strcat(buf, str);    sprintf(str,  ","); strcat(buf, str);

                        if(NETSTACK_ROUTING.node_is_root()) { sprintf(str, "\"" "dT" "\"" ":" "\"" "root" "\""); strcat(buf, str); sprintf(str, ","); strcat(buf, str); } 
                        else                                { sprintf(str, "\"" "dT" "\"" ":" "\"" "node" "\""); strcat(buf, str); sprintf(str, ","); strcat(buf, str); } 
                
                        oar_json_quantized_ipaddr_to_str(oar_json_quantized_ipaddr, &curr_instance.dag.dag_id);
                        sprintf(str, "\"" "dId"     "\"" ":" "\""   "%s"    "\""    ,oar_json_quantized_ipaddr                                        ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                        
                        sprintf(str, "\"" "dVer"    "\"" ":"        "%u"            ,curr_instance.dag.version                              ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);

                        oar_json_quantized_ipaddr_to_str(oar_json_quantized_ipaddr, &curr_instance.dag.prefix_info.prefix);
                        sprintf(str, "\"" "dPf"     "\"" ":" "\""   "%s"    "\""    ,oar_json_quantized_ipaddr                                        ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                        
                        sprintf(str, "\"" "dPfL"    "\"" ":"        "%u"            ,curr_instance.dag.prefix_info.length                   ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                        sprintf(str, "\"" "st"      "\"" ":" "\""   "%s"    "\""    ,oar_json_quantized_rpl_state_to_str(curr_instance.dag.state)     ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);

                        if (curr_instance.dag.preferred_parent) 
                        {
                            oar_json_quantized_ipaddr_to_str(oar_json_quantized_ipaddr, rpl_neighbor_get_ipaddr(curr_instance.dag.preferred_parent));
                            sprintf(str, "\"" "pP"  "\"" ":" "\"" "%s"      "\""    ,oar_json_quantized_ipaddr    ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                        }
                        else
                        {
                            sprintf(str, "\"" "pP" "\"" ":" "\"" "none"    "\""                              ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                        }

                        sprintf(str, "\"" "rk"      "\"" ":"          "%u"          ,curr_instance.dag.rank                                 ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                        sprintf(str, "\"" "lRk"     "\"" ":"          "%u"          ,curr_instance.dag.lowest_rank                          ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                        sprintf(str, "\"" "mRkI"    "\"" ":"          "%u"          ,curr_instance.max_rankinc                              ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                        
                        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                        // SUBSECTION START rplSt{} > dag{} > dao{} ///////////////////
                        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                        sprintf(str, "\"" "dao" "\"" ":"); strcat(buf, str); //
                        sprintf(str, "{"                        ); strcat(buf, str); //
                        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

                            sprintf(str, "\"" "lS"  "\"" ":" "%u"   ,curr_instance.dag.dao_last_seqno       ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                            sprintf(str, "\"" "lA"  "\"" ":" "%u"   ,curr_instance.dag.dao_last_acked_seqno ); strcat(buf, str);   

                        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                        // SUSECTION END rplSt{} > dag{} > dao{} ///////////////////
                        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                        sprintf(str, "}"); strcat(buf, str); ///////////////////////
                        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    // SUSECTION END rSt{} > dag{} /////////////
                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    sprintf(str, "}"); strcat(buf, str); ///////
                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

                    // ??????????????????????????????????
                    sprintf(str, ",");  strcat(buf, str);
                    // ?????????????????????????????????? 

                    sprintf(str, "\"" "mop"     "\"" ":" "\""   "%s"    "\""    ,oar_json_quantized_rpl_mop_to_str(curr_instance.mop)       ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                    sprintf(str, "\"" "of"      "\"" ":" "\""   "%s"    "\""    ,oar_json_quantized_rpl_ocp_to_str(curr_instance.of->ocp)   ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                    sprintf(str, "\"" "hRkI"    "\"" ":"        "%u"            ,curr_instance.min_hoprankinc                           ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                    sprintf(str, "\"" "dLt"     "\"" ":"        "%lu"           ,RPL_LIFETIME(curr_instance.default_lifetime)           ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                    sprintf(str, "\"" "dtsnO"   "\"" ":"        "%u"            ,curr_instance.dtsn_out                                 ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                    
                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    // SUBSECTION START rSt{} > dag{} > tT{} ///////////////////////
                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    sprintf(str, "\"" "tT" "\"" ":"   ); strcat(buf, str); /////////
                    sprintf(str, "{"                  ); strcat(buf, str); /////////
                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

                    
                        sprintf(str, "\"" "cur" "\"" ":" "%u"    ,curr_instance.dag.dio_intcurrent                       ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                        sprintf(str, "\"" "min" "\"" ":" "%u"    ,curr_instance.dio_intmin                               ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                        sprintf(str, "\"" "max" "\"" ":" "%u"    ,curr_instance.dio_intmin + curr_instance.dio_intdoubl  ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                        sprintf(str, "\"" "red" "\"" ":" "%u"    ,curr_instance.dio_redundancy                           ); strcat(buf, str);    

                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                sprintf(str, "}"); strcat(buf, str); //////////////
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                // SUBSECTION END rSt{} > dag{} > tT{} ////////////
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            }

        // ######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)########
        // ########!(ROUTING_CONF_RPL_LITE)########!(ROUTING_CONF_RPL_LITE)########!(ROUTING_CONF_RPL_LITE)########!(ROUTING_CONF_RPL_LITE)########!(ROUTING_CONF_RPL_LITE)########!(ROUTING_CONF_RPL_LITE)########!
        #else

            sprintf(str, "\"" "rL" "\"" ":" "false");  strcat(buf, str); 

            // ??????????????????????????????????
            sprintf(str, ",");  strcat(buf, str);
            // ?????????????????????????????????? 

            sprintf(str, "\"" "iId"  "\"" ":" "null"); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                // SUBSECTION START rSt{} > dag{} //////////////////
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                sprintf(str, "\"" "dag" "\"" ":"); strcat(buf, str);
                sprintf(str, "{"                ); strcat(buf, str);
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                
                    
                    sprintf(str, "\"" "dT"      "\"" ":" "null"     ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                    sprintf(str, "\"" "dId"     "\"" ":" "null"     ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                    sprintf(str, "\"" "dVer"    "\"" ":" "null"     ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                    sprintf(str, "\"" "dPf"     "\"" ":" "null"     ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                    sprintf(str, "\"" "dPfL"    "\"" ":" "null"     ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                    sprintf(str, "\"" "st"      "\"" ":" "null"     ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                    sprintf(str, "\"" "pP"      "\"" ":" "null"     ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                    sprintf(str, "\"" "rk"      "\"" ":" "null"     ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                    sprintf(str, "\"" "lRk"     "\"" ":" "null"     ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                    sprintf(str, "\"" "mRkI"    "\"" ":" "null"     ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                    
                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    // SUBSECTION START rSt{} > dag{} > dao{} /////////////////////
                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    sprintf(str, "\"" "dao" "\"" ":"    ); strcat(buf, str); //////
                    sprintf(str, "{"                    ); strcat(buf, str); //////
                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

                        sprintf(str, "\"" "lS"  "\"" ":" "null"     ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                        sprintf(str, "\"" "lA"  "\"" ":" "null"     ); strcat(buf, str);    

                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    // SUSECTION END rSt{} > dag{} > dao{} /////////////////////
                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    sprintf(str, "}"); strcat(buf, str); ///////////////////////
                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                // SUSECTION END rSt{} > dag{} /////////////
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                sprintf(str, "}"); strcat(buf, str); ///////
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

                // ??????????????????????????????????
                sprintf(str, ",");  strcat(buf, str);
                // ?????????????????????????????????? 

                sprintf(str, "\"" "mop"     "\"" ":" "null"); strcat(buf, str); sprintf(str, ","); strcat(buf, str);
                sprintf(str, "\"" "of"      "\"" ":" "null"); strcat(buf, str); sprintf(str, ","); strcat(buf, str);
                sprintf(str, "\"" "hRkI"    "\"" ":" "null"); strcat(buf, str); sprintf(str, ","); strcat(buf, str);
                sprintf(str, "\"" "dLt"     "\"" ":" "null"); strcat(buf, str); sprintf(str, ","); strcat(buf, str);
                sprintf(str, "\"" "dtsnO"   "\"" ":" "null"); strcat(buf, str); sprintf(str, ","); strcat(buf, str);

                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                // SUBSECTION START rSt{} > tT{} ///////////////////////////////
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                sprintf(str, "\"" "tT" "\"" ":"   ); strcat(buf, str);
                sprintf(str, "{"                            ); strcat(buf, str);
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

                    
                    sprintf(str, "\"" "cur" "\"" ":" "null"     ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                    sprintf(str, "\"" "nim" "\"" ":" "null"     ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                    sprintf(str, "\"" "max" "\"" ":" "null"     ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                    sprintf(str, "\"" "red" "\"" ":" "null"     ); strcat(buf, str);    

            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            sprintf(str, "}"); strcat(buf, str); //////////////
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            // SUBSECTION END rSt{} > tT{} ////////////////////
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

        #endif
        // ########!(ROUTING_CONF_RPL_LITE)########!(ROUTING_CONF_RPL_LITE)########!(ROUTING_CONF_RPL_LITE)########!(ROUTING_CONF_RPL_LITE)########!(ROUTING_CONF_RPL_LITE)########!(ROUTING_CONF_RPL_LITE)########!
    
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    sprintf(str, "}"); strcat(buf, str);
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // SUBSECTION END rSt{} ////////////
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
}

// ####################################################################################################################
// MAIN FUNCTIONS >>>>> CONTINUE <<<<< ////////////////////////////////////////////////////////////////////////////////
// ####################################################################################################################

// ----------------------------------------------------------------------------
// function that appends RPL NEIGBORS section to the json string //////////////
// ----------------------------------------------------------------------------

static void oar_json_quantized_append_rpl_neighbors(char * buf)
{
    char str[128];
    
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // SECTION START rN{} //////////////////////////////////
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    sprintf(str, "\"" "rN" "\"" ":"     ); strcat(buf, str);   
    sprintf(str, "{"                    ); strcat(buf, str);
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

        // ######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)########
        #if (ROUTING_CONF_RPL_LITE)

            sprintf(str, "\"" "rL" "\"" ":" "true");  strcat(buf, str);

            // ??????????????????????????????????
            sprintf(str, ",");  strcat(buf, str);
            // ??????????????????????????????????

            if (!curr_instance.used || rpl_neighbor_count() == 0)
            {
                
                if (!curr_instance.used)    { sprintf(str, "\"" "i" "\"" ":" "false"  ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str); }
                else                        { sprintf(str, "\"" "i" "\"" ":" "true"   ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str); }
            
                sprintf(str, "\"" "c" "\"" ":" "%u" ,rpl_neighbor_count()); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                //  (!curr_instance.used || rpl_neighbor_count() == 0) ///////
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                // SUBARRAY START rN{} > ns[] ////////////////////////////////
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                sprintf(str, "\"" "ns" "\"" ":");  strcat(buf, str); /////////
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
            }
            else
            {
                
                rpl_nbr_t *nbr = nbr_table_head(rpl_neighbors);

                int oar_json_quantized_rpl_neighbor_count = 0;

                sprintf(str, "\"" "i"   "\"" ":" "true"                         ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                sprintf(str, "\"" "c"   "\"" ":" "%u"   ,rpl_neighbor_count()   ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);

                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                // !(!curr_instance.used || rpl_neighbor_count() == 0) //////////////////////
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                // SUBARRAY START rN{} > ns /////////////////////////////////////////////////
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                sprintf(str, "\"" "ns" "\"" ":");  strcat(buf, str); ////////////////////////
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~    
                
                    // [][][][][][][][][][][][][][][][][]
                    sprintf(str, "["); strcat(buf, str);

                    while(nbr != NULL)
                    {
                        oar_json_quantized_rpl_neighbor_count++; 
                        
                        rpl_nbr_t *oar_json_quantized_rpl_nbr_best = best_parent(0);
                        const struct link_stats *oar_json_quantized_rpl_nbr_stats = rpl_neighbor_get_link_stats(nbr);
                        clock_time_t oar_json_quantized_rpl_nbr_clock_now = clock_time();

                        // {{{{{{{{{{{{{{{{{}}}}}}}}}}}}}}}}}
                        sprintf(str, "{" ); strcat(buf, str);

                            oar_json_quantized_ipaddr_to_str(oar_json_quantized_ipaddr, rpl_neighbor_get_ipaddr(nbr));
                            sprintf(str, "\"" "ad"                              "\"" ":" "\""   "%s"    "\""       ,oar_json_quantized_ipaddr); strcat(buf, str); sprintf(str, ","); strcat(buf, str);
                            
                            sprintf(str, "\"" "rk"  "\"" ":"    "%5u"   ,nbr->rank                                                                                                           ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                            sprintf(str, "\"" "lM"  "\"" ":"    "%5u"   ,rpl_neighbor_get_link_metric(nbr)                                                                                   ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                            sprintf(str, "\"" "rkN" "\"" ":"    "%u"    ,rpl_neighbor_rank_via_nbr(nbr)                                                                                      ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                            sprintf(str, "\"" "f"   "\"" ":"    "%2u"   ,oar_json_quantized_rpl_nbr_stats != NULL ? oar_json_quantized_rpl_nbr_stats->freshness : 0                                  ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                            sprintf(str, "\"" "r"   "\"" ":"    "%s"    ,(nbr->rank == ROOT_RANK) ? "true" : "false"                                                                         ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                            sprintf(str, "\"" "b"   "\"" ":"    "%s"    ,nbr == oar_json_quantized_rpl_nbr_best ? "true" : "false"                                                               ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                            sprintf(str, "\"" "a"   "\"" ":"    "%s"    ,((acceptable_rank(rpl_neighbor_rank_via_nbr(nbr)) && rpl_neighbor_is_acceptable_parent(nbr))) ? "true" : "false"    ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                            sprintf(str, "\"" "p"   "\"" ":"    "%s"    ,nbr == curr_instance.dag.preferred_parent ? "true" : "false"                                                        ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);

                            if(oar_json_quantized_rpl_nbr_stats->last_tx_time > 0) 
                            {
                                sprintf(str, "\"" "lTx"  "\"" ":"    "%u"    ,(unsigned)((oar_json_quantized_rpl_nbr_clock_now - oar_json_quantized_rpl_nbr_stats->last_tx_time) / (60 * CLOCK_SECOND))  ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                            }
                            else
                            {
                                sprintf(str, "\"" "lTx"  "\"" ":"    "null"                                                                                                                       ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                            }

                            if(nbr->better_parent_since > 0) 
                            {
                                sprintf(str, "\"" "bS"  "\"" ":"    "%u"    ,(unsigned)((oar_json_quantized_rpl_nbr_clock_now - nbr->better_parent_since) / (60 * CLOCK_SECOND))                      ); strcat(buf, str);   
                            }
                            else
                            {
                                sprintf(str, "\"" "bS"  "\"" ":"    "null"                                                                                                                        ); strcat(buf, str);  
                            }
                            
                        sprintf(str,    "}" ); strcat(buf, str);
                        // {{{{{{{{{{{{{{{{{}}}}}}}}}}}}}}}}}
                        
                        // rpl_neighbor_snprint(temp_str, sizeof(temp_str), nbr);  // sprintf(str,    "\""    "%s"    "\""    ,temp_str   );  strcat(buf, str);
                        
                        if (oar_json_quantized_rpl_neighbor_count < NBR_TABLE_CONF_MAX_NEIGHBORS) { sprintf(str, ","); strcat(buf, str); }
                        nbr = nbr_table_next(rpl_neighbors, nbr);
                    }
                    
                    for (int i = oar_json_quantized_rpl_neighbor_count; i < NBR_TABLE_CONF_MAX_NEIGHBORS; i++)
                    {
                        sprintf(str, "null"); strcat(buf, str);
                        if (i != (NBR_TABLE_CONF_MAX_NEIGHBORS - 1)) { sprintf(str, "," );  strcat(buf, str); }
                    }

                    sprintf(str, "]"); strcat(buf, str);
                    // [][][][][][][][][][][][][][][][][]
            }

        // ######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)########
        // ########!(ROUTING_CONF_RPL_LITE)########!(ROUTING_CONF_RPL_LITE)########!(ROUTING_CONF_RPL_LITE)########!(ROUTING_CONF_RPL_LITE)########!(ROUTING_CONF_RPL_LITE)########!(ROUTING_CONF_RPL_LITE)########!
        #else

            sprintf(str, "\"" "rL" "\"" ":" "false");  strcat(buf, str); 

            // ??????????????????????????????????
            sprintf(str, ",");  strcat(buf, str);
            // ??????????????????????????????????

            sprintf(str, "\"" "i"   "\"" ":" "null"     ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                sprintf(str, "\"" "c"   "\"" ":" "null"     ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);

                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                // SUBARRAY START rpl{} > rplNbr{} > rplNeighbors[] //////////
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                sprintf(str, "\"" "ns" "\"" ":");  strcat(buf, str);
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
        
        #endif
        // ########!(ROUTING_CONF_RPL_LITE)########!(ROUTING_CONF_RPL_LITE)########!(ROUTING_CONF_RPL_LITE)########!(ROUTING_CONF_RPL_LITE)########!(ROUTING_CONF_RPL_LITE)########!(ROUTING_CONF_RPL_LITE)########!

        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        sprintf(str, "}"); strcat(buf, str);
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // SECTION END rN{} ////////////////
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    }

// ####################################################################################################################
// MAIN FUNCTIONS >>>>> ABOVE <<<<< ////////////////////////////////////////////////////////////////////////////////
// ####################################################################################################################        

void oar_json_quantized_construct(char * buf, int quantum_id)
{   
    char str[32];
    switch (quantum_id)
    {
        
        case 0:
            oar_json_quantized_init(buf);
            oar_json_quantized_enter(buf);

            sprintf(str, "\"" "qId" "\"" ":" "%d", quantum_id); strcat(buf, str);

            oar_json_quantized_bridge(buf);
            oar_json_quantized_append_id(buf);

            oar_json_quantized_bridge(buf);
            oar_json_quantized_append_sys(buf);

            oar_json_quantized_exit(buf);
            
            break;

        case 1:
            oar_json_quantized_init(buf);
            oar_json_quantized_enter(buf);

            sprintf(str, "\"" "qId" "\"" ":" "%d", quantum_id); strcat(buf, str);

            oar_json_quantized_bridge(buf);
            oar_json_quantized_append_id(buf);

            oar_json_quantized_bridge(buf);
            oar_json_quantized_append_dev(buf);

            oar_json_quantized_exit(buf);
            
            break;
        
        case 2:
            oar_json_quantized_init(buf);
            oar_json_quantized_enter(buf);

            sprintf(str, "\"" "qId" "\"" ":" "%d", quantum_id); strcat(buf, str);

            oar_json_quantized_bridge(buf);
            oar_json_quantized_append_id(buf);

            oar_json_quantized_bridge(buf);
            oar_json_quantized_append_nrg(buf);

            oar_json_quantized_exit(buf);
            
            break;

        case 3:
            oar_json_quantized_init(buf);
            oar_json_quantized_enter(buf);

            sprintf(str, "\"" "qId" "\"" ":" "%d", quantum_id); strcat(buf, str);

            oar_json_quantized_bridge(buf);
            oar_json_quantized_append_id(buf);

            oar_json_quantized_bridge(buf);
            oar_json_quantized_append_stats_IP(buf);

            oar_json_quantized_exit(buf);
            
            break;

        case 4:
            oar_json_quantized_init(buf);
            oar_json_quantized_enter(buf);

            sprintf(str, "\"" "qId" "\"" ":" "%d", quantum_id); strcat(buf, str);

            oar_json_quantized_bridge(buf);
            oar_json_quantized_append_id(buf);

            oar_json_quantized_bridge(buf);
            oar_json_quantized_append_stats_ICMP(buf);

            oar_json_quantized_exit(buf);
            
            break;

        case 5:
            oar_json_quantized_init(buf);
            oar_json_quantized_enter(buf);

            sprintf(str, "\"" "qId" "\"" ":" "%d", quantum_id); strcat(buf, str);

            oar_json_quantized_bridge(buf);
            oar_json_quantized_append_id(buf);

            oar_json_quantized_bridge(buf);
            oar_json_quantized_append_stats_transport(buf);

            oar_json_quantized_exit(buf);
            
            break;

        case 6:
            oar_json_quantized_init(buf);
            oar_json_quantized_enter(buf);

            sprintf(str, "\"" "qId" "\"" ":" "%d", quantum_id); strcat(buf, str);

            oar_json_quantized_bridge(buf);
            oar_json_quantized_append_id(buf);

            oar_json_quantized_bridge(buf);
            oar_json_quantized_append_stats_nd6(buf);

            oar_json_quantized_exit(buf);
            
            break;

        case 7:
            oar_json_quantized_init(buf);
            oar_json_quantized_enter(buf);

            sprintf(str, "\"" "qId" "\"" ":" "%d", quantum_id); strcat(buf, str);

            oar_json_quantized_bridge(buf);
            oar_json_quantized_append_id(buf);

            oar_json_quantized_bridge(buf);
            oar_json_quantized_append_net(buf);

            oar_json_quantized_exit(buf);
            
            break;

        case 8:
            oar_json_quantized_init(buf);
            oar_json_quantized_enter(buf);

            sprintf(str, "\"" "qId" "\"" ":" "%d", quantum_id); strcat(buf, str);

            oar_json_quantized_bridge(buf);
            oar_json_quantized_append_id(buf);

            oar_json_quantized_bridge(buf);
            oar_json_quantized_append_rt(buf);

            oar_json_quantized_exit(buf);
            
            break;

        case 9:
            oar_json_quantized_init(buf);
            oar_json_quantized_enter(buf);

            sprintf(str, "\"" "qId" "\"" ":" "%d", quantum_id); strcat(buf, str);

            oar_json_quantized_bridge(buf);
            oar_json_quantized_append_id(buf);

            oar_json_quantized_bridge(buf);
            oar_json_quantized_append_rpl_status(buf);

            oar_json_quantized_exit(buf);
            
            break;

        case 10:
            oar_json_quantized_init(buf);
            oar_json_quantized_enter(buf);

            sprintf(str, "\"" "qId" "\"" ":" "%d", quantum_id); strcat(buf, str);

            oar_json_quantized_bridge(buf);
            oar_json_quantized_append_id(buf);

            oar_json_quantized_bridge(buf);
            oar_json_quantized_append_rpl_neighbors(buf);

            oar_json_quantized_exit(buf);
            
            break;
        
        default:
            oar_json_quantized_init(buf);
            oar_json_quantized_enter(buf);

            sprintf(str, "\"" "qId" "\"" ":" "%d", quantum_id); strcat(buf, str);

            oar_json_quantized_exit(buf);

            break;
    }
}








//  {
//      "id": {
//          "t": 51,
//          "mac": "0012.4b00.0f83.b601"
//      },
//      "nrg": {
//          "e": true,
//          "c": 7,
//          "l": 43,
//          "dL": 0,
//          "tT": 51,
//          "rL": 51,
//          "rT": 0,
//          "rO": 0
//      },
//      "st": {
//          "uS": true,
//          "rx": 7,
//          "tx": 7,
//          "fw": 0,
//          "dr": 0,
//          "vE": 0,
//          "hE": 0,
//          "lE": 0,
//          "fE": 0,
//          "cE": 0,
//          "pE": 0
//      },
//      "net": {
//          "v6": true,
//          "addr": ["null", "fd00::212:4b00:f83:b601", "fe80::212:4b00:f83:b601"],
//          "rt": {
//              "df": "fe80::212:4b00:f24:8385",
//              "lt": "infinite"
//          }
//      },
//      "rpl": {
//          "rL": true,
//          "nbr": {
//              "i": true,
//              "c": 3,
//              "ns": [{
//                  "ad": "fe80::212:4b00:f82:a600",
//                  "rk": 274,
//                  "lM": 128,
//                  "rkN": 402,
//                  "f": 0,
//                  "r": false,
//                  "b": false,
//                  "a": true,
//                  "p": false,
//                  "lTx": null,
//                  "bS": null
//              }, {
//                  "ad": "fe80::212:4b00:f24:8385",
//                  "rk": 128,
//                  "lM": 128,
//                  "rkN": 256,
//                  "f": 5,
//                  "r": true,
//                  "b": true,
//                  "a": true,
//                  "p": true,
//                  "lTx": 0,
//                  "bS": null
//              }, {
//                  "ad": "fe80::212:4b00:f82:da03",
//                  "rk": 256,
//                  "lM": 128,
//                  "rkN": 384,
//                  "f": 0,
//                  "r": false,
//                  "b": false,
//                  "a": true,
//                  "p": false,
//                  "lTx": null,
//                  "bS": null
//              }, null, null]
//          },
//          "st": {
//              "iId": 0,
//              "dag": {
//                  "dT": "node",
//                  "dId": "fd00::212:4b00:f24:8385",
//                  "dVer": 240,
//                  "dPf": "fd00::",
//                  "dPfL": 64,
//                  "st": "Reachable",
//                  "pP": "fe80::212:4b00:f24:8385",
//                  "rk": 256,
//                  "lRk": 256,
//                  "mRkI": 1024,
//                  "dao": {
//                      "lS": 241,
//                      "lA": 241
//                  }
//              },
//              "mop": "Non-storing",
//              "of": "MRHOF",
//              "hRkI": 128,
//              "dLt": 1800,
//              "dtsnO": 240,
//              "tT": {
//                  "cur": 13,
//                  "min": 12,
//                  "max": 20,
//                  "red": 0
//              }
//          }
//      }
//  }
