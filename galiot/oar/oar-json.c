#include "oar-json.h"








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
// contiki-ng Energest

#if (ENERGEST_CONF_ON)

    static unsigned long oar_json_to_seconds(uint64_t time)
    {
        return (unsigned long)(time / ENERGEST_SECOND);
    }

    // ------------------------------------------------------------------------

    void oar_json_energest(unsigned long int system_time)
    {
        energest_flush();       // Update all energest times.

        printf("\n");

        printf("[%8lu] DEBUG > ENERGY >                                                                              CPU: %lu \n",    system_time, oar_json_to_seconds(energest_type_time(ENERGEST_TYPE_CPU)));
        printf("[%8lu] DEBUG > ENERGY >                                                                              LPM: %lu \n",    system_time, oar_json_to_seconds(energest_type_time(ENERGEST_TYPE_LPM)));
        printf("[%8lu] DEBUG > ENERGY >                                                                         DEEP LPM: %lu \n",    system_time, oar_json_to_seconds(energest_type_time(ENERGEST_TYPE_DEEP_LPM)));
        printf("[%8lu] DEBUG > ENERGY >                                                                       TOTAL TIME: %lu \n",    system_time, oar_json_to_seconds(ENERGEST_GET_TOTAL_TIME()));
        printf("[%8lu] DEBUG > ENERGY >                                                                     RADIO LISTEN: %lu \n",    system_time, oar_json_to_seconds(energest_type_time(ENERGEST_TYPE_LISTEN)));
        printf("[%8lu] DEBUG > ENERGY >                                                                   RADIO TRANSMIT: %lu \n",    system_time, oar_json_to_seconds(energest_type_time(ENERGEST_TYPE_TRANSMIT)));
        printf("[%8lu] DEBUG > ENERGY >                                                                        RADIO OFF: %lu \n",    system_time, oar_json_to_seconds(ENERGEST_GET_TOTAL_TIME() - energest_type_time(ENERGEST_TYPE_TRANSMIT) - energest_type_time(ENERGEST_TYPE_LISTEN)));
        
}

#endif /* (ENERGEST_CONF_ON) */
