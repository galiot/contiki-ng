#ifndef OAR_STR_H
#define OAR_STR_H

#if ROUTING_CONF_RPL_LITE
    #include "net/routing/rpl-lite/rpl.h"
#elif ROUTING_CONF_RPL_CLASSIC
    #include "net/routing/rpl-classic/rpl.h"
#endif

const char *oar_ds6_nbr_state_to_str(uint8_t state);
const char *oar_rpl_state_to_str(enum rpl_dag_state state);
const char *oar_rpl_mop_to_str(int mop);
const char *oar_rpl_ocp_to_str(int ocp);






#endif  /* OAR_STR_H */