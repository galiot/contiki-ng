#include "oar-json-micro.h"
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

// +/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+
#if (OAR_CONF_JSON_MICRO_RPL) ////////
// +/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+

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



// +/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+
#endif // (OAR_CONF_JSON_MICRO_RPL) //
// +/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+

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

// +/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+
#if (OAR_CONF_JSON_MICRO_RPL) ////////
// +/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+

// ######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)########
#if (ROUTING_CONF_RPL_LITE)

    // ----------------------------------------------------------------------------
    // function that provides context for ds6 neighbor state //////////////////////
    // ----------------------------------------------------------------------------

    // static const char *oar_json_micro_ds6_nbr_state_to_str(uint8_t state)
    // {
    //     switch(state) 
    //     {
    //         case NBR_INCOMPLETE:    return "Incomplete";
    //         case NBR_REACHABLE:     return "Reachable";
    //         case NBR_STALE:         return "Stale";
    //         case NBR_DELAY:         return "Delay";
    //         case NBR_PROBE:         return "Probe";
    //         default:                return "Unknown";
    //     }
    // }

    // ----------------------------------------------------------------------------
    // function that provides context for RPL directed acyclic graph (DAG) state //
    // ----------------------------------------------------------------------------

    static const char *oar_json_micro_rpl_state_to_str(enum rpl_dag_state state)
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
    static const char *oar_json_micro_rpl_mop_to_str(int mop)
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

    static const char *oar_json_micro_rpl_ocp_to_str(int ocp)
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

// +/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+
#endif // (OAR_CONF_JSON_MICRO_RPL) //
// +/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+










// ()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()
// HELPER FUNCTIONS  >>>>> BELOW <<<<< ////////////////////////////////////////////////////////////////////////////////
// ()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()

// +/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+
#if (OAR_CONF_JSON_MICRO_NET || OAR_CONF_JSON_MICRO_RPL) /////
// +/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+

// ######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)########
#if (NETSTACK_CONF_WITH_IPV6)

    ///////////////////////////////////
    // IPADDR ---> STR ////////////////
    ///////////////////////////////////

    static void oar_json_micro_ipaddr_to_str(char *output, const uip_ipaddr_t *ipaddr) 
    {
        char buf[UIPLIB_IPV6_MAX_STR_LEN];  // UIPLIB_IPV6_MAX_STR_LEN == 40
        
        memset(output, 0, sizeof(output));  // initialization of outpout string
        uiplib_ipaddr_snprint(buf, sizeof(buf), ipaddr);    // function that creates string from ipaddr

        strcpy(output, buf);    // cannot return string, local scope
    }


#endif //(NETSTACK_CONF_WITH_IPV6)
// ######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)########

// +/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+
#endif // (OAR_CONF_JSON_MICRO_NET || OAR_CONF_JSON_MICRO_RPL)
// +/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+
// +/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+
#if (OAR_CONF_JSON_MICRO_ID || OAR_CONF_JSON_MICRO_NET || OAR_CONF_JSON_MICRO_RPL) /////
// +/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+

///////////////////////////////////
// LLADDR ---> STR ////////////////
///////////////////////////////////

static void oar_json_micro_lladdr_to_str(char *output, const linkaddr_t *lladdr) 
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

// +/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+
#endif // (OAR_CONF_JSON_MICRO_ID || OAR_CONF_JSON_MICRO_NET || OAR_CONF_JSON_MICRO_RPL)
// +/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+
// +/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+
#if (OAR_CONF_JSON_MICRO_NRG) ////////
// +/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+

// vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
// #########(ENERGEST_CONF_ON)#########(ENERGEST_CONF_ON)#########(ENERGEST_CONF_ON)#########(ENERGEST_CONF_ON)#########(ENERGEST_CONF_ON)#########(ENERGEST_CONF_ON)#########(ENERGEST_CONF_ON))#########

#if (ENERGEST_CONF_ON)

    static unsigned long oar_json_micro_to_seconds(uint64_t time)
    {
        return (unsigned long)(time / ENERGEST_SECOND);
    }

#endif

// #########(ENERGEST_CONF_ON)#########(ENERGEST_CONF_ON)#########(ENERGEST_CONF_ON)#########(ENERGEST_CONF_ON)#########(ENERGEST_CONF_ON)#########(ENERGEST_CONF_ON)#########(ENERGEST_CONF_ON))#########
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

// +/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+
#endif // (OAR_CONF_JSON_MICRO_NRG) //
// +/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+











// ====================================================================================================================
// DECLARATIONS ///////////////////////////////////////////////////////////////////////////////////////////////////////
// ====================================================================================================================


// char oar_json_micro_buf[OAR_CONF_JSON_MICRO_BUF_SIZE];    // global string: will contain the json

// ----------------------------------------------------------------------------

void oar_json_micro_print(char * buf)
{
    printf("%s\n", buf);
}

// +/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+
#if (OAR_CONF_JSON_MICRO_NET || OAR_CONF_JSON_MICRO_RPL) /////
// +/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+

// ######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)########
#if (NETSTACK_CONF_WITH_IPV6)

     static char oar_json_micro_ipaddr[UIPLIB_IPV6_MAX_STR_LEN];

#endif //(NETSTACK_CONF_WITH_IPV6)
// ######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)########

// +/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+
#endif // (OAR_CONF_JSON_MICRO_NET || OAR_CONF_JSON_MICRO_RPL)
// +/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+
// +/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+
#if (OAR_CONF_JSON_MICRO_ID || OAR_CONF_JSON_MICRO_NET || OAR_CONF_JSON_MICRO_RPL) /////
// +/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+
    
static char oar_json_micro_lladdr[UIPLIB_IPV6_MAX_STR_LEN];

// +/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+
#endif // (OAR_CONF_JSON_MICRO_ID || OAR_CONF_JSON_MICRO_NET || OAR_CONF_JSON_MICRO_RPL)
// +/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+




















// ####################################################################################################################
// MAIN FUNCTIONS >>>>> BELOW <<<<< ///////////////////////////////////////////////////////////////////////////////////
// ####################################################################################################################

// ----------------------------------------------------------------------------
// function that initializes (empties) the json string ////////////////////////
// ----------------------------------------------------------------------------

static void oar_json_micro_init(char * buf)
{
    memset(buf, 0, sizeof(buf));        // initialization
}

// ----------------------------------------------------------------------------
// function that appends the entry '{' json character to the string ///////////
// ----------------------------------------------------------------------------
static void oar_json_micro_enter(char * buf)
{
    char str[128];
    sprintf(str,    "{" );  strcat(buf, str);
}

// ----------------------------------------------------------------------------
// function that connects the sections og the json, appending and ',' char ////
// ----------------------------------------------------------------------------

void oar_json_micro_bridge(char * buf)
{
    char str[128];
    sprintf(str,    "," );  strcat(buf, str);
}

// ----------------------------------------------------------------------------
// function that appends the exit '}' json character to the string ////////////
// ----------------------------------------------------------------------------

static void oar_json_micro_exit(char * buf)
{
    char str[128];
    sprintf(str,    "}" );  strcat(buf, str);
}

// ####################################################################################################################
// MAIN FUNCTIONS >>>>> CONTINUE <<<<< ////////////////////////////////////////////////////////////////////////////////
// ####################################################################################################################

// +/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+
#if (OAR_CONF_JSON_MICRO_ID) /////////
// +/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+

    // ----------------------------------------------------------------------------
    // function that appends ID section to the json string ////////////////////////
    // ----------------------------------------------------------------------------
    
    static void oar_json_micro_append_id(char * buf)
    {
        char str[128];
    
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // SECTION START id{} /////////////////////////////
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ 
        sprintf(str, "\"" "id" "\"" ":" ); strcat(buf, str);
        sprintf(str, "{"                ); strcat(buf, str);
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        
            sprintf(str,        "\""    "t"    "\""    ":"        "%lu"                                    ,clock_seconds()    );  strcat(buf, str);   sprintf(str,    "," );  strcat(buf, str);
    
            oar_json_micro_lladdr_to_str(oar_json_micro_lladdr, &linkaddr_node_addr);
            sprintf(str,        "\""    "mac"       "\""    ":" "\""    "%s"                        "\""        ,oar_json_micro_lladdr    ); strcat(buf, str); sprintf(str, ","); strcat(buf, str);
    
            sprintf(str,        "\""    "cd"    "\""    ":" "\""    OAR_CONF_MOTE_COLOR         "\""                            );  strcat(buf, str);
        
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        sprintf(str, "}" ); strcat(buf, str);
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // SECTION END id{} /////////////////
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    }

// +/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+
#endif //(OAR_CONF_JSON_MICRO_ID) ////
// +/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+
// +/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+
#if (OAR_CONF_JSON_MICRO_NRG) ////////
// +/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+

    // ----------------------------------------------------------------------------
    // function that appends ENERGY section to the json string ////////////////////
    // ----------------------------------------------------------------------------

    static void oar_json_micro_append_nrg(char * buf)
    {
        char str[128];

        // #########(ENERGEST_CONF_ON)#########(ENERGEST_CONF_ON)#########(ENERGEST_CONF_ON)#########(ENERGEST_CONF_ON)#########(ENERGEST_CONF_ON)#########(ENERGEST_CONF_ON)#########(ENERGEST_CONF_ON)#########
        #if (ENERGEST_CONF_ON)

            energest_flush();       // Update all energest times.
            
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            // SECTION START energy{} //////////////////////////////
            sprintf(str, "\"" "nrg" "\"" ":"    ); strcat(buf, str);   
            sprintf(str, "{"                    ); strcat(buf, str);
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

                sprintf(str, "\"" "energest"    "\"" ":" "true"                                                                                                                                                 );  strcat(buf, str); sprintf(str,","); strcat(buf, str);

                sprintf(str, "\"" "cpu"         "\"" ":" "%lu"   ,oar_json_micro_to_seconds(energest_type_time(ENERGEST_TYPE_CPU))                                                                              );  strcat(buf, str); sprintf(str,","); strcat(buf, str);
                sprintf(str, "\"" "lpm"         "\"" ":" "%lu"   ,oar_json_micro_to_seconds(energest_type_time(ENERGEST_TYPE_LPM))                                                                              );  strcat(buf, str); sprintf(str,","); strcat(buf, str);
                sprintf(str, "\"" "dLpm"        "\"" ":" "%lu"   ,oar_json_micro_to_seconds(energest_type_time(ENERGEST_TYPE_DEEP_LPM))                                                                         );  strcat(buf, str); sprintf(str,","); strcat(buf, str);
                sprintf(str, "\"" "tT"          "\"" ":" "%lu"   ,oar_json_micro_to_seconds(ENERGEST_GET_TOTAL_TIME())                                                                                          );  strcat(buf, str); sprintf(str,","); strcat(buf, str);
                sprintf(str, "\"" "rLs"         "\"" ":" "%lu"   ,oar_json_micro_to_seconds(energest_type_time(ENERGEST_TYPE_LISTEN))                                                                           );  strcat(buf, str); sprintf(str,","); strcat(buf, str);
                sprintf(str, "\"" "rTx"         "\"" ":" "%lu"   ,oar_json_micro_to_seconds(energest_type_time(ENERGEST_TYPE_TRANSMIT))                                                                         );  strcat(buf, str); sprintf(str,","); strcat(buf, str);
                sprintf(str, "\"" "rO"          "\"" ":" "%lu"   ,oar_json_micro_to_seconds(ENERGEST_GET_TOTAL_TIME() - energest_type_time(ENERGEST_TYPE_TRANSMIT) - energest_type_time(ENERGEST_TYPE_LISTEN))  );  strcat(buf, str); 
                
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
            sprintf(str, "\"" "nrg" "\"" ":"    ); strcat(buf, str);   
            sprintf(str, "{"                    ); strcat(buf, str);
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

                sprintf(str, "\"" "energest"    "\"" ":" "false"    ); strcat(buf, str); sprintf(str, ","); strcat(buf, str);

                sprintf(str, "\"" "cpu"         "\"" ":" "null"     ); strcat(buf, str); sprintf(str, ","); strcat(buf, str);
                sprintf(str, "\"" "lpm"         "\"" ":" "null"     ); strcat(buf, str); sprintf(str, ","); strcat(buf, str);
                sprintf(str, "\"" "dLpm"        "\"" ":" "null"     ); strcat(buf, str); sprintf(str, ","); strcat(buf, str);
                sprintf(str, "\"" "tT"          \"" ":"  "null"     ); strcat(buf, str); sprintf(str, ","); strcat(buf, str);
                sprintf(str, "\"" "rLs"         "\"" ":" "null"     ); strcat(buf, str); sprintf(str, ","); strcat(buf, str);
                sprintf(str, "\"" "rTx"         "\"" ":" "null"     ); strcat(buf, str); sprintf(str, ","); strcat(buf, str);
                sprintf(str, "\"" "rO"          "\"" ":" "null"     ); strcat(buf, str);
            
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            sprintf(str, "}" ); strcat(buf, str);
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            // SECTION END energy{} /////////////
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

        #endif
        // ########!(ENERGEST_CONF_ON)########!(ENERGEST_CONF_ON)########!(ENERGEST_CONF_ON)########!(ENERGEST_CONF_ON)########!(ENERGEST_CONF_ON)########!(ENERGEST_CONF_ON)########!(ENERGEST_CONF_ON)########!
    }

// +/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+
#endif //(OAR_CONF_JSON_MICRO_NRG) ///
// +/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+
// +/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+
#if (OAR_CONF_JSON_MICRO_STATS) //////
// +/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+

    // ----------------------------------------------------------------------------
    // function that appends STATS section to the json string /////////////////////
    // ----------------------------------------------------------------------------

    static void oar_json_micro_append_stats(char * buf)
    {
        char str[128];
        
        // ######## (UIP_CONF_STATISTICS)######## (UIP_CONF_STATISTICS)######## (UIP_CONF_STATISTICS)######## (UIP_CONF_STATISTICS)######## (UIP_CONF_STATISTICS)######## (UIP_CONF_STATISTICS)######## (UIP_CONF_STATISTICS)########
        #if (UIP_CONF_STATISTICS)

            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            // SECTION START stats{} ///////////////////////////////////
            sprintf(str, "\""   "stats"  "\""    ":"); strcat(buf, str);
            sprintf(str, "{"                        ); strcat(buf, str);
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

                sprintf(str, "\"" "uipStats"    "\"" ":" "true"                       ); strcat(buf, str);   sprintf(str, ","); strcat(buf, str);        
                
                sprintf(str, "\"" "rx"          "\"" ":" "%lu" ,uip_stat.ip.recv      ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                sprintf(str, "\"" "tx"          "\"" ":" "%lu" ,uip_stat.ip.sent      ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                sprintf(str, "\"" "fw"          "\"" ":" "%lu" ,uip_stat.ip.forwarded ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                sprintf(str, "\"" "dr"          "\"" ":" "%lu" ,uip_stat.ip.drop      ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                sprintf(str, "\"" "vhlE"        "\"" ":" "%lu" ,uip_stat.ip.vhlerr    ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                sprintf(str, "\"" "hblE"        "\"" ":" "%lu" ,uip_stat.ip.hblenerr  ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                sprintf(str, "\"" "lblE"        "\"" ":" "%lu" ,uip_stat.ip.lblenerr  ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                sprintf(str, "\"" "fragE"       "\"" ":" "%lu" ,uip_stat.ip.fragerr   ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                sprintf(str, "\"" "chkE"        "\"" ":" "%lu" ,uip_stat.ip.chkerr    ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                sprintf(str, "\"" "protE"       "\"" ":" "%lu" ,uip_stat.ip.protoerr  ); strcat(buf, str);                                                                                                                                                                                         
            
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

                sprintf(str, "\"" "uipStats"    "\"" ":" "false"  );  strcat(buf, str); sprintf(str, "," );  strcat(buf, str);       
                
                sprintf(str, "\"" "rx"         "\"" ":" "null"   ); strcat(buf, str); sprintf(str, ","); strcat(buf, str);
                sprintf(str, "\"" "tx"         "\"" ":" "null"   ); strcat(buf, str); sprintf(str, ","); strcat(buf, str);
                sprintf(str, "\"" "fw"         "\"" ":" "null"   ); strcat(buf, str); sprintf(str, ","); strcat(buf, str);
                sprintf(str, "\"" "dr"         "\"" ":" "null"   ); strcat(buf, str); sprintf(str, ","); strcat(buf, str);
                sprintf(str, "\"" "vhlE"       "\"" ":" "null"   ); strcat(buf, str); sprintf(str, ","); strcat(buf, str);
                sprintf(str, "\"" "hblE"       "\"" ":" "null"   ); strcat(buf, str); sprintf(str, ","); strcat(buf, str);
                sprintf(str, "\"" "lblE"       "\"" ":" "null"   ); strcat(buf, str); sprintf(str, ","); strcat(buf, str);
                sprintf(str, "\"" "fragE"      "\"" ":" "null"   ); strcat(buf, str); sprintf(str, ","); strcat(buf, str);
                sprintf(str, "\"" "chkE"       "\"" ":" "null"   ); strcat(buf, str); sprintf(str, ","); strcat(buf, str);
                sprintf(str, "\"" "protE"      "\"" ":" "null"   ); strcat(buf, str);                                                                                                                                                                      
            
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            sprintf(str, "}"); strcat(buf, str);
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            // SECTION END stats{} /////////////
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        
        #endif
        // ########!(UIP_CONF_STATISTICS)########!(UIP_CONF_STATISTICS)########!(UIP_CONF_STATISTICS)########!(UIP_CONF_STATISTICS)########!(UIP_CONF_STATISTICS)########!(UIP_CONF_STATISTICS)########!(UIP_CONF_STATISTICS)########!
    }

// +/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+
#endif //(OAR_CONF_JSON_MICRO_STATS) /
// +/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+
// +/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+
#if (OAR_CONF_JSON_MICRO_NET) ////////
// +/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+

    // ----------------------------------------------------------------------------
    // function that appends NET section to the json string ////////////////////
    // ----------------------------------------------------------------------------


    static void oar_json_micro_append_net(char * buf)
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

        sprintf(str, "\"" "IPv6" "\"" ":" "true"); strcat(buf, str);

        // ??????????????????????????????????
        sprintf(str, ",");  strcat(buf, str);
        // ?????????????????????????????????? 

            uint8_t state;

            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            // SUBARRAY START net{} > IPv6addr[] /////////////////////////////
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
                        oar_json_micro_ipaddr_to_str(oar_json_micro_ipaddr, &uip_ds6_if.addr_list[i].ipaddr);
                        sprintf(str, "\"" "%s"      "\"" ,oar_json_micro_ipaddr   ); strcat(buf, str);

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

            // ??????????????????????????????????
            sprintf(str, ",");  strcat(buf, str);
            // ?????????????????????????????????? 

            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            // SUBSECTION START net{} > route{} ///////////////////
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            sprintf(str, "\"" "route" "\"" ":" ); strcat(buf, str);
            sprintf(str, "{"                    ); strcat(buf, str);
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

                uip_ds6_defrt_t *default_route;
                default_route = uip_ds6_defrt_lookup(uip_ds6_defrt_choose());

                if(default_route != NULL)
                {
                    oar_json_micro_ipaddr_to_str(oar_json_micro_ipaddr, &default_route->ipaddr);
                    sprintf(str,    "\""        "df"      "\""        ":"     "\""        "%s"        "\""        ,oar_json_micro_ipaddr    );  strcat(buf, str);   sprintf(str, "," );  strcat(buf, str);

                    if (default_route->lifetime.interval != 0)  { sprintf(str,   "\""    "lt"   "\""    ":" "\""    "%lu"      "\""    ,(unsigned long)default_route->lifetime.interval      );  strcat(buf, str);   sprintf(str, "," );  strcat(buf, str); }
                    else                                        { sprintf(str,   "\""    "lt"   "\""    ":" "\""    "infinite" "\""                                                          );  strcat(buf, str); }   // sprintf(str, "," );  strcat(buf, str);  
                }
                else
                {
                    sprintf(str,    "\""        "df"      "\""        ":"     "\""        "none"      "\""                                  );  strcat(buf, str);   sprintf(str, "," );  strcat(buf, str);
                    sprintf(str,    "\""        "lt"      "\""        ":"                 "null"                                            );  strcat(buf, str);   

                }

            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            sprintf(str, "}"); strcat(buf, str);
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            // SUBSECTION END net{} > route{} /
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

        // ######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)######## (NETSTACK_CONF_WITH_IPV6)########
        // ########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!
        #else

            sprintf(str, "\"" "IPv6" "\"" ":" "false"); strcat(buf, str);

            // ??????????????????????????????????
            sprintf(str, ",");  strcat(buf, str);
            // ?????????????????????????????????? 

            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            // SUBARRAY START net{} > IPv6addr[] /////////////////////////////
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            sprintf(str, "\"" "addr" "\"" ":"         ); strcat(buf, str);  
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

            // ??????????????????????????????????
            sprintf(str, ",");  strcat(buf, str);
            // ?????????????????????????????????? 

            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            // SUBSECTION START net{} > route{} ///////////////////
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            sprintf(str, "\"" "routes" "\"" ":" ); strcat(buf, str);
            sprintf(str, "{"                    ); strcat(buf, str);
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

                sprintf(str, "\"" "df"  "\"" ":"        "null"      ); strcat(buf, str);   sprintf(str, "," ); strcat(buf, str);
                sprintf(str, "\"" "lt"  "\"" ":"        "null"      ); strcat(buf, str);   

            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            sprintf(str, "}"); strcat(buf, str);
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            // SUBSECTION END net{} > route{} /
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

        #endif
        // ########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!(NETSTACK_CONF_WITH_IPV6)########!

        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        sprintf(str, "}"); strcat(buf, str);
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // SECTION END net{} ///////////////
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    }

// +/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+
#endif // (OAR_CONF_JSON_MICRO_NET) //
// +/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+
// +/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+
#if (OAR_CONF_JSON_MICRO_RPL) ////////
// +/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+

    // ----------------------------------------------------------------------------
    // function that appends RPL section to the json string ////////////////////
    // ----------------------------------------------------------------------------

    static void oar_json_micro_append_rpl(char * buf)
    {
        char str[128];
        
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // SECTION START rpl{} /////////////////////////////////
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        sprintf(str, "\"" "rpl" "\"" ":"    ); strcat(buf, str);   
        sprintf(str, "{"                    ); strcat(buf, str);
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

            // ######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)########
            #if (ROUTING_CONF_RPL_LITE)

                sprintf(str,        "\""    "rplLite"           "\""    ":" "true"   );  strcat(buf, str);    sprintf(str, "," );  strcat(buf, str);

                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                // SUBSECTION START rpl{} > rplNbr{} ///////////////////
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                sprintf(str, "\"" "nbr" "\"" ":" ); strcat(buf, str);
                sprintf(str, "{"                    ); strcat(buf, str);
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

                    // sprintf(str, "\"" "valid" "\"" ":" "true" ); strcat(buf, str);  sprintf(str, "," ); strcat(buf, str);

                    if (!curr_instance.used || rpl_neighbor_count() == 0)
                    {
                        
                        if (!curr_instance.used)    { sprintf(str, "\"" "inst" "\"" ":" "false"  ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str); }
                        else                        { sprintf(str, "\"" "inst" "\"" ":" "true"   ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str); }
                    
                        sprintf(str, "\"" "cnt" "\"" ":" "%u" ,rpl_neighbor_count()); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                        
                        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                        //  (!curr_instance.used || rpl_neighbor_count() == 0) ///////
                        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                        // SUBARRAY START rpl{} > rplNbr{} > rplNeighbors[] //////////
                        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                        sprintf(str, "\"" "nbrs" "\"" ":");  strcat(buf, str);
                        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  
                        
                            // [][][][][][][][][][][][][][][][][]
                            sprintf(str, "["); strcat(buf, str);

                            for (int i = 0; i < NBR_TABLE_CONF_MAX_NEIGHBORS; i++)
                            {
                                // {{{{{{{{{{{{{{{{{}}}}}}}}}}}}}}}}}
                                sprintf(str, "{"); strcat(buf, str);

                                    sprintf(str, "\"" "addr"    "\"" ":" "null"); strcat(buf, str); sprintf(str, "," ); strcat(buf, str);
                                    sprintf(str, "\"" "rank"    "\"" ":" "null"); strcat(buf, str); sprintf(str, "," ); strcat(buf, str);
                                    sprintf(str, "\"" "lMetr"   "\"" ":" "null"); strcat(buf, str); sprintf(str, "," ); strcat(buf, str);
                                    sprintf(str, "\"" "rankNbr" "\"" ":" "null"); strcat(buf, str); sprintf(str, "," ); strcat(buf, str);
                                    sprintf(str, "\"" "f"       "\"" ":" "null"); strcat(buf, str); sprintf(str, "," ); strcat(buf, str);
                                    sprintf(str, "\"" "r"       "\"" ":" "null"); strcat(buf, str); sprintf(str, "," ); strcat(buf, str);
                                    sprintf(str, "\"" "b"       "\"" ":" "null"); strcat(buf, str); sprintf(str, "," ); strcat(buf, str);
                                    sprintf(str, "\"" "a"       "\"" ":" "null"); strcat(buf, str); sprintf(str, "," ); strcat(buf, str);
                                    sprintf(str, "\"" "p"       "\"" ":" "null"); strcat(buf, str); sprintf(str, "," ); strcat(buf, str);
                                    sprintf(str, "\"" "lastTx"  "\"" ":" "null"); strcat(buf, str); sprintf(str, "," );  strcat(buf, str);
                                    sprintf(str, "\"" "bSince"  "\"" ":" "null"); strcat(buf, str);

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

                        int oar_json_micro_rpl_neighbor_count = 0;

                        sprintf(str, "\"" "inst"     "\"" ":" "true"                         ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                        sprintf(str, "\"" "cnt"        "\"" ":" "%u"   ,rpl_neighbor_count()   ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);

                        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                        // !(!curr_instance.used || rpl_neighbor_count() == 0)
                        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                        // SUBARRAY START rpl{} > rplNbr{} > rplNeighbors[] /////////////////////////
                        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                        sprintf(str, "\"" "nbrs" "\"" ":");  strcat(buf, str);
                        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~    
                        
                            // [][][][][][][][][][][][][][][][][]
                            sprintf(str, "["); strcat(buf, str);

                            while(nbr != NULL)
                            {
                                oar_json_micro_rpl_neighbor_count++; 
                                
                                rpl_nbr_t *oar_json_micro_rpl_nbr_best = best_parent(0);
                                const struct link_stats *oar_json_micro_rpl_nbr_stats = rpl_neighbor_get_link_stats(nbr);
                                clock_time_t oar_json_micro_rpl_nbr_clock_now = clock_time();

                                // {{{{{{{{{{{{{{{{{}}}}}}}}}}}}}}}}}
                                sprintf(str, "{" ); strcat(buf, str);

                                    oar_json_micro_ipaddr_to_str(oar_json_micro_ipaddr, rpl_neighbor_get_ipaddr(nbr));
                                    sprintf(str, "\"" "addr"                              "\"" ":" "\""   "%s"    "\""       ,oar_json_micro_ipaddr); strcat(buf, str); sprintf(str, ","); strcat(buf, str);
                                    
                                    sprintf(str, "\"" "rank"    "\"" ":"    "%5u"   ,nbr->rank                                                                                                           ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                                    sprintf(str, "\"" "lMetr"   "\"" ":"    "%5u"   ,rpl_neighbor_get_link_metric(nbr)                                                                                   ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                                    sprintf(str, "\"" "rankNbr" "\"" ":"    "%u"    ,rpl_neighbor_rank_via_nbr(nbr)                                                                                      ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                                    sprintf(str, "\"" "f"       "\"" ":"    "%2u"   ,oar_json_micro_rpl_nbr_stats != NULL ? oar_json_micro_rpl_nbr_stats->freshness : 0                                  ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                                    sprintf(str, "\"" "r"       "\"" ":"    "%s"    ,(nbr->rank == ROOT_RANK) ? "true" : "false"                                                                         ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                                    sprintf(str, "\"" "b"       "\"" ":"    "%s"    ,nbr == oar_json_micro_rpl_nbr_best ? "true" : "false"                                                               ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                                    sprintf(str, "\"" "a"       "\"" ":"    "%s"    ,((acceptable_rank(rpl_neighbor_rank_via_nbr(nbr)) && rpl_neighbor_is_acceptable_parent(nbr))) ? "true" : "false"    ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                                    sprintf(str, "\"" "p"       "\"" ":"    "%s"    ,nbr == curr_instance.dag.preferred_parent ? "true" : "false"                                                        ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);

                                    if(oar_json_micro_rpl_nbr_stats->last_tx_time > 0) 
                                    {
                                        sprintf(str, "\"" "lastTx"  "\"" ":"    "%u"    ,(unsigned)((oar_json_micro_rpl_nbr_clock_now - oar_json_micro_rpl_nbr_stats->last_tx_time) / (60 * CLOCK_SECOND))  ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                                    }
                                    else
                                    {
                                        sprintf(str, "\"" "lastTx"  "\"" ":"    "null"                                                                                                                       ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                                    }

                                    if(nbr->better_parent_since > 0) 
                                    {
                                        sprintf(str, "\"" "bSince"  "\"" ":"    "%u"    ,(unsigned)((oar_json_micro_rpl_nbr_clock_now - nbr->better_parent_since) / (60 * CLOCK_SECOND))                      ); strcat(buf, str);   
                                    }
                                    else
                                    {
                                        sprintf(str, "\"" "bSince"  "\"" ":"    "null"                                                                                                                        ); strcat(buf, str);  
                                    }
                                    
                                sprintf(str,    "}"      ); strcat(buf, str);
                                // {{{{{{{{{{{{{{{{{}}}}}}}}}}}}}}}}}
                                
                                // rpl_neighbor_snprint(temp_str, sizeof(temp_str), nbr);  // sprintf(str,    "\""    "%s"    "\""    ,temp_str   );  strcat(buf, str);
                                
                                if (oar_json_micro_rpl_neighbor_count < NBR_TABLE_CONF_MAX_NEIGHBORS) { sprintf(str, ","); strcat(buf, str); }
                                nbr = nbr_table_next(rpl_neighbors, nbr);
                            }
                            
                            for (int i = oar_json_micro_rpl_neighbor_count; i < NBR_TABLE_CONF_MAX_NEIGHBORS; i++)
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
                // SUBSECTION END rpl{} > rplNbr{}
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

                // ??????????????????????????????????
                sprintf(str, ",");  strcat(buf, str);
                // ?????????????????????????????????? 

                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                // SUBSECTION START rpl{} > rplStatus{} ////////////////////
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                sprintf(str, "\"" "status" "\""  ":" ); strcat(buf, str);
                sprintf(str, "{"                        ); strcat(buf, str);
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

                    // sprintf(str, "\"" "valid" "\"" ":" "true"); strcat(buf, str);   sprintf(str, ","); strcat(buf, str);

                    if(!curr_instance.used)             
                    { 
                        sprintf(str, "\"" "instId" "\"" ":" "\"" "none" "\""); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                        
                        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                        // (!curr_instance.used) ///////////////////////////
                        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                        // SUBSECTION START rpl{} > rplStatus{} > dag{} ////
                        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                        sprintf(str, "\"" "dag" "\"" ":"); strcat(buf, str);
                        sprintf(str, "{"                ); strcat(buf, str);
                        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                        
                            sprintf(str, "\"" "dType"       "\"" ":" "null" ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                            sprintf(str, "\"" "dId"         "\"" ":" "null" ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                            sprintf(str, "\"" "dVer"        "\"" ":" "null" ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                            sprintf(str, "\"" "dPf"         "\"" ":" "null" ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                            sprintf(str, "\"" "dPfLen"      "\"" ":" "null" ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                            sprintf(str, "\"" "state"       "\"" ":" "null" ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                            sprintf(str, "\"" "pPrnt"       "\"" ":" "null" ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                            sprintf(str, "\"" "rank"        "\"" ":" "null" ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                            sprintf(str, "\"" "lowRank"     "\"" ":" "null" ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                            sprintf(str, "\"" "maxRankInc"  "\"" ":" "null" ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                            
                            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                            // SUBSECTION START rpl{} > rplStatus{} > dag{} > daoSequence{}
                            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                            sprintf(str, "\"" "dao" "\"" ":"); strcat(buf, str); //
                            sprintf(str, "{"                        ); strcat(buf, str); //
                            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

                                sprintf(str, "\"" "lastSent"    "\"" ":" "null"     ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                                sprintf(str, "\"" "lastAcked"   "\"" ":" "null"     ); strcat(buf, str);

                            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                            // SUSECTION END rpl{} > rplStatus{} > dag{} > daoSequence{}
                            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                            sprintf(str, "}"); strcat(buf, str); ///////////////////////
                            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    
                        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                        // SUSECTION END rpl{} > rplStatus{} > dag{}
                        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                        sprintf(str, "}"); strcat(buf, str); ///////
                        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                        
                        // ??????????????????????????????????
                        sprintf(str, ",");  strcat(buf, str);
                        // ?????????????????????????????????? 

                        sprintf(str, "\"" "mop"         "\"" ":" "null"); strcat(buf, str); sprintf(str, ","); strcat(buf, str);
                        sprintf(str, "\"" "of"          "\"" ":" "null"); strcat(buf, str); sprintf(str, ","); strcat(buf, str);
                        sprintf(str, "\"" "hopRankInc"  "\"" ":" "null"); strcat(buf, str); sprintf(str, ","); strcat(buf, str);
                        sprintf(str, "\"" "defLt"       "\"" ":" "null"); strcat(buf, str); sprintf(str, ","); strcat(buf, str);
                        sprintf(str, "\"" "dtsnOut"     "\"" ":" "null"); strcat(buf, str); sprintf(str, ","); strcat(buf, str);

                        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                        // SUBSECTION START rpl{} > rplStatus{} > trickleTimer{} ///////
                        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                        sprintf(str, "\"" "trickleT" "\"" ":"   ); strcat(buf, str);
                        sprintf(str, "{"                        ); strcat(buf, str);
                        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

                            sprintf(str,    "\""    "curr"      "\""    ":" "null"    );  strcat(buf, str);   sprintf(str,    "," );  strcat(buf, str);
                            sprintf(str,    "\""    "nim"       "\""    ":" "null"    );  strcat(buf, str);   sprintf(str,    "," );  strcat(buf, str);
                            sprintf(str,    "\""    "max"       "\""    ":" "null"    );  strcat(buf, str);   sprintf(str,    "," );  strcat(buf, str);
                            sprintf(str,    "\""    "redund"    "\""    ":" "null"    );  strcat(buf, str);   

                        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                        // SUBSECTION END rpl{} > rplStatus{} > tricleTimer{}
                        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                        sprintf(str, "}"); strcat(buf, str); ////////////////
                        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    
                    } 
                    else                                
                    { 
                        sprintf(str, "\"" "instId" "\"" ":" "%u" ,curr_instance.instance_id); strcat(buf, str); sprintf(str, "," ); strcat(buf, str);

                        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                        // !(!curr_instance.used) //////////////////////////
                        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                        // SUBSECTION START rpl{} > rplStatus{} > dag{} ////
                        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                        sprintf(str, "\"" "dag" "\"" ":"); strcat(buf, str);
                        sprintf(str, "{"                ); strcat(buf, str);
                        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                        
                            // sprintf(str, "\"" "valid"          "\"" ":"         "true"                                                                  ); strcat(buf, str);    sprintf(str,  ","); strcat(buf, str);

                            if(NETSTACK_ROUTING.node_is_root()) { sprintf(str, "\"" "dType" "\"" ":" "\"" "root" "\""); strcat(buf, str); sprintf(str, ","); strcat(buf, str); } 
                            else                                { sprintf(str, "\"" "dType" "\"" ":" "\"" "node" "\""); strcat(buf, str); sprintf(str, ","); strcat(buf, str); } 
                    
                            oar_json_micro_ipaddr_to_str(oar_json_micro_ipaddr, &curr_instance.dag.dag_id);
                            sprintf(str, "\"" "dId"         "\"" ":" "\""   "%s"    "\""    ,oar_json_micro_ipaddr                                        ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                            
                            sprintf(str, "\"" "dVer"        "\"" ":"        "%u"            ,curr_instance.dag.version                              ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);

                            oar_json_micro_ipaddr_to_str(oar_json_micro_ipaddr, &curr_instance.dag.prefix_info.prefix);
                            sprintf(str, "\"" "dPf"        "\"" ":" "\""   "%s"    "\""    ,oar_json_micro_ipaddr                                        ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                            
                            sprintf(str, "\"" "dPfLen"      "\"" ":"        "%u"            ,curr_instance.dag.prefix_info.length                   ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                            sprintf(str, "\"" "state"       "\"" ":" "\""   "%s"    "\""    ,oar_json_micro_rpl_state_to_str(curr_instance.dag.state)     ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);

                            if (curr_instance.dag.preferred_parent) 
                            {
                                oar_json_micro_ipaddr_to_str(oar_json_micro_ipaddr, rpl_neighbor_get_ipaddr(curr_instance.dag.preferred_parent));
                                sprintf(str, "\"" "pPrnt" "\"" ":" "\"" "%s"      "\""    ,oar_json_micro_ipaddr    ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                            }
                            else
                            {
                                sprintf(str, "\"" "pPrnt" "\"" ":" "\"" "none"    "\""                              ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                            }

                            sprintf(str, "\"" "rank"        "\"" ":"          "%u"          ,curr_instance.dag.rank                                 ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                            sprintf(str, "\"" "lRank"       "\"" ":"          "%u"          ,curr_instance.dag.lowest_rank                          ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                            sprintf(str, "\"" "maxRankInc"  "\"" ":"          "%u"          ,curr_instance.max_rankinc                              ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                            
                            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                            // SUBSECTION START rpl{} > rplStatus{} > dag{} > daoSequence{}
                            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                            sprintf(str, "\"" "dao" "\"" ":"); strcat(buf, str); //
                            sprintf(str, "{"                        ); strcat(buf, str); //
                            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

                                sprintf(str, "\"" "lastSent"    "\"" ":" "%u"   ,curr_instance.dag.dao_last_seqno       ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                                sprintf(str, "\"" "lastAcked"   "\"" ":" "%u"   ,curr_instance.dag.dao_last_acked_seqno ); strcat(buf, str);   

                            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                            // SUSECTION END rpl{} > rplStatus{} > dag{} > daoSequence{}
                            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                            sprintf(str, "}"); strcat(buf, str); ///////////////////////
                            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

                        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                        // SUSECTION END rpl{} > rplStatus{} > dag{}
                        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                        sprintf(str, "}"); strcat(buf, str); ///////
                        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

                        // ??????????????????????????????????
                        sprintf(str, ",");  strcat(buf, str);
                        // ?????????????????????????????????? 

                        sprintf(str, "\"" "mop"         "\"" ":" "\""   "%s"    "\""    ,oar_json_micro_rpl_mop_to_str(curr_instance.mop)       ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                        sprintf(str, "\"" "of"          "\"" ":" "\""   "%s"    "\""    ,oar_json_micro_rpl_ocp_to_str(curr_instance.of->ocp)   ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                        sprintf(str, "\"" "hopRankInc"  "\"" ":"        "%u"            ,curr_instance.min_hoprankinc                           ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                        sprintf(str, "\"" "defLt"       "\"" ":"        "%lu"           ,RPL_LIFETIME(curr_instance.default_lifetime)           ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                        sprintf(str, "\"" "dtsnOut"     "\"" ":"        "%u"            ,curr_instance.dtsn_out                                 ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                        
                        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                        // SUBSECTION START rpl{} > rplStatus{} > trickleTimer{} ///////
                        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                        sprintf(str, "\"" "trickleT" "\"" ":"   ); strcat(buf, str);
                        sprintf(str, "{"                            ); strcat(buf, str);
                        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

                        
                            sprintf(str, "\"" "curr"    "\"" ":" "%u"    ,curr_instance.dag.dio_intcurrent                       ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                            sprintf(str, "\"" "min"     "\"" ":" "%u"    ,curr_instance.dio_intmin                               ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                            sprintf(str, "\"" "max"     "\"" ":" "%u"    ,curr_instance.dio_intmin + curr_instance.dio_intdoubl  ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                            sprintf(str, "\"" "redund"  "\"" ":" "%u"    ,curr_instance.dio_redundancy                           ); strcat(buf, str);    

                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    sprintf(str, "}"); strcat(buf, str);
                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    // SUBSECTION END rpl{} > rplStatus > tricleTimer{}
                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                }

            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            sprintf(str, "}"); strcat(buf, str);
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            // SUBSECTION END rpl{} > rplStatus{}
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

        // ######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)######## (ROUTING_CONF_RPL_LITE)########
        // ########!(ROUTING_CONF_RPL_LITE)########!(ROUTING_CONF_RPL_LITE)########!(ROUTING_CONF_RPL_LITE)########!(ROUTING_CONF_RPL_LITE)########!(ROUTING_CONF_RPL_LITE)########!(ROUTING_CONF_RPL_LITE)########!
        #else

            sprintf(str, "\"" "rplLite" "\"" ":" "false"); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);

            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            // SUBSECTION START rpl{} > rplNbr{} ///////////////////
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            sprintf(str, "\"" "nbr" "\"" ":" ); strcat(buf, str);
            sprintf(str, "{"                    ); strcat(buf, str);
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            
                // sprintf(str, "\"" "valid"               "\""  ":" "false"   ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);

                sprintf(str, "\"" "inst"    "\"" ":" "null"     ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                sprintf(str, "\"" "cnt"     "\"" ":" "null"     ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);

                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                // SUBARRAY START rpl{} > rplNbr{} > rplNeighbors[] //////////
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                sprintf(str, "\"" "nbrs" "\"" ":");  strcat(buf, str);
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
            // SUBSECTION END rpl{} > rplNbr{}
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

            // ??????????????????????????????????
            sprintf(str, ",");  strcat(buf, str);
            // ??????????????????????????????????

            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            // SUBSECTION START rpl{} > rplStatus{} ////////////////////
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            sprintf(str, "\"" "status" "\""  ":" ); strcat(buf, str);
            sprintf(str, "{"                        ); strcat(buf, str);
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

                // sprintf(str, "\"" "valid"       "\"" ":"       "false"          ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                sprintf(str, "\"" "instId"  "\"" ":" "\""  "none"       "\""); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                    
                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    // SUBSECTION START rpl{} > rplStatus{} > dag{} ////
                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    sprintf(str, "\"" "dag" "\"" ":"); strcat(buf, str);
                    sprintf(str, "{"                ); strcat(buf, str);
                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    
                        
                        sprintf(str, "\"" "dType"       "\"" ":" "null"     ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                        sprintf(str, "\"" "dId"         "\"" ":" "null"     ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                        sprintf(str, "\"" "dVer"        "\"" ":" "null"     ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                        sprintf(str, "\"" "dPf"         "\"" ":" "null"     ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                        sprintf(str, "\"" "dPfLen"      "\"" ":" "null"     ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                        sprintf(str, "\"" "state"       "\"" ":" "null"     ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                        sprintf(str, "\"" "pdPrnt"      "\"" ":" "null"     ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                        sprintf(str, "\"" "rank"        "\"" ":" "null"     ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                        sprintf(str, "\"" "lRank"       "\"" ":" "null"     ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                        sprintf(str, "\"" "maxRankInc"  "\"" ":" "null"     ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                        
                        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                        // SUBSECTION START rpl{} > rplStatus{} > dag{} > daoSequence{}
                        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                        sprintf(str, "\"" "dao" "\"" ":"); strcat(buf, str); //
                        sprintf(str, "{"                        ); strcat(buf, str); //
                        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

                            
                            sprintf(str, "\"" "lastSent"    "\"" ":" "null"     ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                            sprintf(str, "\"" "lastAcked"   "\"" ":" "null"     ); strcat(buf, str);    


                        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                        // SUSECTION END rpl{} > rplStatus{} > dag{} > daoSequence{}
                        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                        sprintf(str, "}"); strcat(buf, str); ///////////////////////
                        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    // SUSECTION END rpl{} > rplStatus{} > dag{}
                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    sprintf(str, "}"); strcat(buf, str); ///////
                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

                    // ??????????????????????????????????
                    sprintf(str, ",");  strcat(buf, str);
                    // ?????????????????????????????????? 

                    sprintf(str, "\"" "mop"         "\"" ":" "null"); strcat(buf, str); sprintf(str, ","); strcat(buf, str);
                    sprintf(str, "\"" "of"          "\"" ":" "null"); strcat(buf, str); sprintf(str, ","); strcat(buf, str);
                    sprintf(str, "\"" "hopRankInc"  "\"" ":" "null"); strcat(buf, str); sprintf(str, ","); strcat(buf, str);
                    sprintf(str, "\"" "dfLt"        "\"" ":" "null"); strcat(buf, str); sprintf(str, ","); strcat(buf, str);
                    sprintf(str, "\"" "dtsnOut"     "\"" ":" "null"); strcat(buf, str); sprintf(str, ","); strcat(buf, str);

                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    // SUBSECTION START rpl{} > rplStatus{} > trickleTimer{} ///////
                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    sprintf(str, "\"" "trickleTimer" "\"" ":"   ); strcat(buf, str);
                    sprintf(str, "{"                            ); strcat(buf, str);
                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

                        
                        sprintf(str, "\"" "curr"    "\"" ":" "null"     ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                        sprintf(str, "\"" "nim"     "\"" ":" "null"     ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                        sprintf(str, "\"" "max"     "\"" ":" "null"     ); strcat(buf, str);    sprintf(str, "," ); strcat(buf, str);
                        sprintf(str, "\"" "redund"  "\"" ":" "null"     ); strcat(buf, str);    

                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                sprintf(str, "}"); strcat(buf, str);
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                // SUBSECTION END rpl{} > rplStatus > tricleTimer{}
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            sprintf(str, "}"); strcat(buf, str);
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            // SUBSECTION END rpl{} > rplStatus{}
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

        #endif
        // ########!(ROUTING_CONF_RPL_LITE)########!(ROUTING_CONF_RPL_LITE)########!(ROUTING_CONF_RPL_LITE)########!(ROUTING_CONF_RPL_LITE)########!(ROUTING_CONF_RPL_LITE)########!(ROUTING_CONF_RPL_LITE)########!

        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        sprintf(str, "}"); strcat(buf, str);
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // SECTION END rpl{} ///////////////
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    }


// +/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+
#endif // (OAR_CONF_JSON_MICRO_RPL) //
// +/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+/+

// ####################################################################################################################
// MAIN FUNCTIONS >>>>> ABOVE <<<<< ////////////////////////////////////////////////////////////////////////////////
// ####################################################################################################################






void oar_json_micro_construct(char * buf)
{
    oar_json_micro_init(buf);
    oar_json_micro_enter(buf);
    
    #if (OAR_CONF_JSON_MICRO_ID)

        oar_json_micro_append_id(buf);
    
    #endif
    #if (OAR_CONF_JSON_MICRO_NRG)

        oar_json_micro_bridge(buf);
        oar_json_micro_append_nrg(buf);

    #endif
    #if (OAR_CONF_JSON_MICRO_STATS)

        oar_json_micro_bridge(buf);
        oar_json_micro_append_stats(buf);

    #endif
    #if (OAR_CONF_JSON_MICRO_NET)

        oar_json_micro_bridge(buf);
        oar_json_micro_append_net(buf);

    #endif
    #if (OAR_CONF_JSON_MICRO_RPL)

        oar_json_micro_bridge(buf);
        oar_json_micro_append_rpl(buf);
        
    #endif

    oar_json_micro_exit(buf);
}








//  {
//      "id": {
//          "t": 105,
//          "mac": "0012.4b00.0f83.b601",
//          "cd": "RED"
//      },
//      "nrg": {
//          "energest": true,
//          "cpu": 19,
//          "lpm": 85,
//          "dLpm": 0,
//          "tT": 105,
//          "rLs": 105,
//          "rTx": 0,
//          "rO": 0
//      },
//      "stats": {
//          "uipStats": true,
//          "rx": 12,
//          "tx": 10,
//          "fw": 0,
//          "dr": 0,
//          "vhlE": 0,
//          "hblE": 0,
//          "lblE": 0,
//          "fragE": 0,
//          "chkE": 0,
//          "protE": 0
//      },
//      "net": {
//          "IPv6": true,
//          "addr": ["null", "fd00::212:4b00:f83:b601", "fe80::212:4b00:f83:b601"],
//          "route": {
//              "df": "fe80::212:4b00:f24:8385",
//              "lt": "infinite"
//          }
//      },
//      "rpl": {
//          "rplLite": true,
//          "nbr": {
//              "inst": true,
//              "cnt": 3,
//              "nbrs": [{
//                  "addr": "fe80::212:4b00:f82:da03",
//                  "rank": 256,
//                  "lMetr": 128,
//                  "rankNbr": 384,
//                  "f": 0,
//                  "r": false,
//                  "b": false,
//                  "a": true,
//                  "p": false,
//                  "lastTx": null,
//                  "bSince": null
//              }, {
//                  "addr": "fe80::212:4b00:f24:8385",
//                  "rank": 128,
//                  "lMetr": 128,
//                  "rankNbr": 256,
//                  "f": 5,
//                  "r": true,
//                  "b": true,
//                  "a": true,
//                  "p": true,
//                  "lastTx": 0,
//                  "bSince": null
//              }, {
//                  "addr": "fe80::212:4b00:f82:a600",
//                  "rank": 307,
//                  "lMetr": 128,
//                  "rankNbr": 435,
//                  "f": 0,
//                  "r": false,
//                  "b": false,
//                  "a": true,
//                  "p": false,
//                  "lastTx": null,
//                  "bSince": null
//              }, null, null]
//          },
//          "status": {
//              "instId": 0,
//              "dag": {
//                  "dType": "node",
//                  "dId": "fd00::212:4b00:f24:8385",
//                  "dVer": 240,
//                  "dPf": "fd00::",
//                  "dPfLen": 64,
//                  "state": "Reachable",
//                  "pPrnt": "fe80::212:4b00:f24:8385",
//                  "rank": 256,
//                  "lRank": 256,
//                  "maxRankInc": 1024,
//                  "dao": {
//                      "lastSent": 241,
//                      "lastAcked": 241
//                  }
//              },
//              "mop": "Non-storing",
//              "of": "MRHOF",
//              "hopRankInc": 128,
//              "defLt": 1800,
//              "dtsnOut": 240,
//              "trickleT": {
//                  "curr": 15,
//                  "min": 12,
//                  "max": 20,
//                  "redund": 0
//              }
//          }
//      }
//  }



