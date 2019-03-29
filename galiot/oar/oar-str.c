#include "oar-str.h"

const char *oar_ds6_nbr_state_to_str(uint8_t state)
{
    switch(state) 
    {
        case NBR_INCOMPLETE:
            return "Incomplete";

        case NBR_REACHABLE:
            return "Reachable";

        case NBR_STALE:
            return "Stale";

        case NBR_DELAY:
            return "Delay";

        case NBR_PROBE:
            return "Probe";

        default:
            return "Unknown";
    }
}

const char *oar_rpl_state_to_str(enum rpl_dag_state state)
{
    switch(state) 
    {
        case DAG_INITIALIZED:
            return "Initialized";

        case DAG_JOINED:
            return "Joined";

        case DAG_REACHABLE:
            return "Reachable";

        case DAG_POISONING:
            return "Poisoning";

        default:
          return "Unknown";
    }
}

const char *oar_rpl_mop_to_str(int mop)
{
    switch(mop) 
    {
        case RPL_MOP_NO_DOWNWARD_ROUTES:
            return "No downward routes";

        case RPL_MOP_NON_STORING:
            return "Non-storing";

        case RPL_MOP_STORING_NO_MULTICAST:
            return "Storing";

        case RPL_MOP_STORING_MULTICAST:
            return "Storing+multicast";

        default:
            return "Unknown";
    }
}

const char *oar_rpl_ocp_to_str(int ocp)
{
    switch(ocp) 
    {
        case RPL_OCP_OF0:
          return "OF0";

        case RPL_OCP_MRHOF:
          return "MRHOF";
          
        default:
          return "Unknown";
    }
}