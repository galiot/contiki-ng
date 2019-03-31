#include "oar-debug.h"




// ====================================================================================================================
// contiki-ng Energest

#if (ENERGEST_CONF_ON)

    static unsigned long oar_debug_to_seconds(uint64_t time)
    {
        return (unsigned long)(time / ENERGEST_SECOND);
    }

    // ------------------------------------------------------------------------

    void oar_debug_energest(unsigned long int system_time)
    {
        energest_flush();       // Update all energest times.

        printf("\n");

        printf("[%8lu] DEBUG > ENERGY >                                                                              CPU: %lu \n",    system_time, oar_debug_to_seconds(energest_type_time(ENERGEST_TYPE_CPU)));
        printf("[%8lu] DEBUG > ENERGY >                                                                              LPM: %lu \n",    system_time, oar_debug_to_seconds(energest_type_time(ENERGEST_TYPE_LPM)));
        printf("[%8lu] DEBUG > ENERGY >                                                                         DEEP LPM: %lu \n",    system_time, oar_debug_to_seconds(energest_type_time(ENERGEST_TYPE_DEEP_LPM)));
        printf("[%8lu] DEBUG > ENERGY >                                                                       TOTAL TIME: %lu \n",    system_time, oar_debug_to_seconds(ENERGEST_GET_TOTAL_TIME()));
        printf("[%8lu] DEBUG > ENERGY >                                                                     RADIO LISTEN: %lu \n",    system_time, oar_debug_to_seconds(energest_type_time(ENERGEST_TYPE_LISTEN)));
        printf("[%8lu] DEBUG > ENERGY >                                                                   RADIO TRANSMIT: %lu \n",    system_time, oar_debug_to_seconds(energest_type_time(ENERGEST_TYPE_TRANSMIT)));
        printf("[%8lu] DEBUG > ENERGY >                                                                        RADIO OFF: %lu \n",    system_time, oar_debug_to_seconds(ENERGEST_GET_TOTAL_TIME() - energest_type_time(ENERGEST_TYPE_TRANSMIT) - energest_type_time(ENERGEST_TYPE_LISTEN)));
        
}

#endif /* (ENERGEST_CONF_ON) */

// ====================================================================================================================
// uIP TCP/IP statistics

#if (UIP_CONF_STATISTICS)

    void oar_debug_stats_ip(unsigned long int system_time)
    {
        printf("[%8lu] DEBUG >  STATS >          (ip.recv) >                            received packets at the IP layer: %lu\n",       system_time, uip_stat.ip.recv);
        printf("[%8lu] DEBUG >  STATS >          (ip.sent) >                                sent packets at the IP layer: %lu\n",       system_time, uip_stat.ip.sent);
        printf("[%8lu] DEBUG >  STATS >     (ip.forwarded) >                           forwarded packets at the IP layer: %lu\n",       system_time, uip_stat.ip.forwarded);
        printf("[%8lu] DEBUG >  STATS >          (ip.drop) >                             dropped packets at the IP layer: %lu\n",       system_time, uip_stat.ip.drop);
        printf("[%8lu] DEBUG >  STATS >        (ip.vhlerr) >    packets dropped due to wrong IP version or header length: %lu\n",       system_time, uip_stat.ip.vhlerr);
        printf("[%8lu] DEBUG >  STATS >      (ip.hblenerr) >           packets dropped due to wrong IP length, high byte: %lu\n",       system_time, uip_stat.ip.hblenerr);
        printf("[%8lu] DEBUG >  STATS >      (ip.lblenerr) >            packets dropped due to wrong IP length, low byte: %lu\n",       system_time, uip_stat.ip.lblenerr);
        printf("[%8lu] DEBUG >  STATS >       (ip.fragerr) >              packets dropped because they were IP fragments: %lu\n",       system_time, uip_stat.ip.fragerr);
        printf("[%8lu] DEBUG >  STATS >        (ip.chkerr) >                   packets dropped due to IP checksum errors: %lu\n",       system_time, uip_stat.ip.chkerr);
        printf("[%8lu] DEBUG >  STATS >      (ip.protoerr) > packets dropped because they were neither ICMP, UDP nor TCP: %lu\n",       system_time, uip_stat.ip.protoerr);                  
    }

    // ----------------------------------------------------------------------------
    
    void oar_debug_stats_icmp(unsigned long int system_time)
    {
        printf("[%8lu] DEBUG >  STATS >        (icmp.recv) >                                       received ICMP packets: %lu\n",   system_time, uip_stat.icmp.recv);
        printf("[%8lu] DEBUG >  STATS >        (icmp.sent) >                                           sent ICMP packets: %lu\n",   system_time, uip_stat.icmp.sent);
        printf("[%8lu] DEBUG >  STATS >        (icmp.drop) >                                        dropped ICMP packets: %lu\n",   system_time, uip_stat.icmp.drop);
        printf("[%8lu] DEBUG >  STATS >     (icmp.typeerr) >                              ICMP packets with a wrong type: %lu\n",   system_time, uip_stat.icmp.typeerr);
        printf("[%8lu] DEBUG >  STATS >      (icmp.chkerr) >                            ICMP packets with a bad checksum: %lu\n",   system_time, uip_stat.icmp.chkerr);
    
    }

    // ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

    #if (UIP_TCP)
    
        void oar_debug_stats_tcp(unsigned long int system_time)
        {
            printf("[%8lu] DEBUG >  STATS >         (tcp.recv) >                                       received TCP segments: %lu\n",   system_time, uip_stat.tcp.recv);     
            printf("[%8lu] DEBUG >  STATS >         (tcp.sent) >                                           sent TCP segments: %lu\n",   system_time, uip_stat.tcp.sent);    
            printf("[%8lu] DEBUG >  STATS >         (tcp.drop) >                                        dropped TCP segments: %lu\n",   system_time, uip_stat.tcp.drop);    
            printf("[%8lu] DEBUG >  STATS >       (tcp.chkerr) >                            TCP segments with a bad checksum: %lu\n",   system_time, uip_stat.tcp.chkerr);  
            printf("[%8lu] DEBUG >  STATS >       (tcp.ackerr) >                          TCP segments with a bad ACK number: %lu\n",   system_time, uip_stat.tcp.ackerr);  
            printf("[%8lu] DEBUG >  STATS >          (tcp.rst) >                           received TCP RST (reset) segments: %lu\n",   system_time, uip_stat.tcp.rst);   
            printf("[%8lu] DEBUG >  STATS >       (tcp.rexmit) >                                  retransmitted TCP segments: %lu\n",   system_time, uip_stat.tcp.rexmit); 
            printf("[%8lu] DEBUG >  STATS >      (tcp.syndrop) >     dropped SYNs because too few connections were available: %lu\n",   system_time, uip_stat.tcp.syndrop);
            printf("[%8lu] DEBUG >  STATS >       (tcp.synrst) >                     SYNs for closed ports, triggering a RST: %lu\n",   system_time, uip_stat.tcp.synrst); 
        }

    #endif /* (UIP_TCP) */

    // ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

    #if (UIP_UDP)
    
        void oar_debug_stats_udp(unsigned long int system_time)
        {
            printf("[%8lu] DEBUG >  STATS >         (udp.drop) >                                        dropped UDP segments: %lu\n",   system_time, uip_stat.udp.drop);   
            printf("[%8lu] DEBUG >  STATS >         (udp.recv) >                                       received UDP segments: %lu\n",   system_time, uip_stat.udp.recv);   
            printf("[%8lu] DEBUG >  STATS >         (udp.sent) >                                           sent UDP segments: %lu\n",   system_time, uip_stat.udp.sent);   
            printf("[%8lu] DEBUG >  STATS >       (udp.chkerr) >                            UDP segments with a bad checksum: %lu\n",   system_time, uip_stat.udp.chkerr);
        }

    #endif /* (UIP_UDP) */

    // ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    
    void oar_debug_stats_nd6(unsigned long int system_time)
    {
        printf("[%8lu] DEBUG >  STATS >         (nd6.drop) >                                         dropped ND6 packets: %lu\n", system_time, uip_stat.nd6.drop);
        printf("[%8lu] DEBUG >  STATS >         (nd6.recv) >                                         dropped ND6 packets: %lu\n", system_time, uip_stat.nd6.recv);
        printf("[%8lu] DEBUG >  STATS >         (nd6.sent) >                                         dropped ND6 packets: %lu\n", system_time, uip_stat.nd6.sent);
    }

#endif /* (UIP_CONF_STATISTICS) */

// ====================================================================================================================
// contiki-ng Shell (gets)

#if (NETSTACK_CONF_WITH_IPV6)

    void oar_debug_ipaddr_to_str(char *output, const uip_ipaddr_t *ipaddr) 
    {
        char buf[UIPLIB_IPV6_MAX_STR_LEN];                                      // UIPLIB_IPV6_MAX_STR_LEN == 40
        
        memset(output, 0, sizeof(output));                                      // initialization of outpout string
        uiplib_ipaddr_snprint(buf, sizeof(buf), ipaddr);                        // function that creates string from ipaddr

        strcpy(output, buf);                                                    // cannot return string, local scope
    }

#endif // (NETSTACK_CONF_WITH_IPV6)

// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

void oar_debug_lladdr_to_str(char *output, const linkaddr_t *lladdr) 
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

#if (NETSTACK_CONF_WITH_IPV6)

    // function that provides context for ds6 neighbor state
    const char *oar_debug_ds6_nbr_state_to_str(uint8_t state)
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

#endif // (NETSTACK_CONF_WITH_IPV6)

// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

#if (ROUTING_CONF_RPL_LITE)

    // function that provides context for RPL directed acyclic graph (DAG) state
    const char *oar_debug_rpl_state_to_str(enum rpl_dag_state state)
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
    const char *oar_debug_rpl_mop_to_str(int mop)
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
    const char *oar_debug_rpl_ocp_to_str(int ocp)
    {
        switch(ocp) 
        {
            case RPL_OCP_OF0: return "OF0";
            case RPL_OCP_MRHOF: return "MRHOF";
            default: return "Unknown";
        }
    }

#endif // (ROUTING_CONF_RPL_LITE)

// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

#if (ROUTING_CONF_RPL_LITE)

    void oar_debug_cmd_rpl_nbr(unsigned long int system_time)
    {
        if(!curr_instance.used || rpl_neighbor_count() == 0) 
        {
            printf("[%8lu] DEBUG >   INFO >      (cmd_rpl_nbr) >                                                RPL neighbor: (0/%d)\n",         system_time, rpl_neighbor_count());
        } 
        else 
        {
            rpl_nbr_t *nbr = nbr_table_head(rpl_neighbors);
            int oar_rpl_neighbor_count = 0;
    
            while(nbr != NULL) 
            {
                char buf[120];
                oar_rpl_neighbor_count++;
                
                rpl_neighbor_snprint(buf, sizeof(buf), nbr);
                printf("[%8lu] DEBUG >   INFO >      (cmd_rpl_nbr) >                                            RPL neighbor %d/%d: %s\n",  system_time, oar_rpl_neighbor_count, rpl_neighbor_count(), buf);
                nbr = nbr_table_next(rpl_neighbors, nbr);
            }
        }
    }

    // ----------------------------------------------------------------------------

    void oar_debug_cmd_rpl_status(unsigned long int system_time)
    {
        if(!curr_instance.used) 
        {
            printf("[%8lu] DEBUG >   INFO >   (cmd_rpl_status) >                                                    Instance: None\n", system_time);
        } 
        else 
        {
            printf("[%8lu] DEBUG >   INFO >   (cmd_rpl_status) >                                                    Instance: %u\n", system_time, curr_instance.instance_id);

            if(NETSTACK_ROUTING.node_is_root()) 
            {
                printf("[%8lu] DEBUG >   INFO >   (cmd_rpl_status) >                                                         DAG: root\n", system_time);
            } 
            else 
            {
                printf("[%8lu] DEBUG >   INFO >   (cmd_rpl_status) >                                                         DAG: node\n", system_time);
            }
            
            printf("[%8lu] DEBUG >   INFO >   (cmd_rpl_status) >                                                         DAG: ", system_time);
                oar_debug_ipaddr_to_str(oar_debug_ipaddr, &curr_instance.dag.dag_id); printf("%s", oar_debug_ipaddr);
                printf(", version %u\n", curr_instance.dag.version);

            printf("[%8lu] DEBUG >   INFO >   (cmd_rpl_status) >                                                      Prefix: ", system_time);
                oar_debug_ipaddr_to_str(oar_debug_ipaddr, &curr_instance.dag.prefix_info.prefix); printf("%s", oar_debug_ipaddr); 
                printf("/%u\n", curr_instance.dag.prefix_info.length);

            printf("[%8lu] DEBUG >   INFO >   (cmd_rpl_status) >                                                         MOP: %s\n", system_time, oar_debug_rpl_mop_to_str(curr_instance.mop));
            printf("[%8lu] DEBUG >   INFO >   (cmd_rpl_status) >                                                          OF: %s\n", system_time, oar_debug_rpl_ocp_to_str(curr_instance.of->ocp));
            printf("[%8lu] DEBUG >   INFO >   (cmd_rpl_status) >                                          Hop rank increment: %u\n", system_time, curr_instance.min_hoprankinc);
            printf("[%8lu] DEBUG >   INFO >   (cmd_rpl_status) >                                            Default lifetime: %lu seconds\n", system_time, RPL_LIFETIME(curr_instance.default_lifetime));
            printf("[%8lu] DEBUG >   INFO >   (cmd_rpl_status) >                                                       State: %s\n", system_time, oar_debug_rpl_state_to_str(curr_instance.dag.state));
        
            printf("[%8lu] DEBUG >   INFO >   (cmd_rpl_status) >                                            Preferred parent: ", system_time);
            if(curr_instance.dag.preferred_parent) 
            {
                oar_debug_ipaddr_to_str(oar_debug_ipaddr, rpl_neighbor_get_ipaddr(curr_instance.dag.preferred_parent)); printf("%s", oar_debug_ipaddr);
                printf(" (last DTSN: %u)\n", curr_instance.dag.preferred_parent->dtsn);
            } 
            else 
            {
                printf("None\n");
            }

            printf("[%8lu] DEBUG >   INFO >   (cmd_rpl_status) >                                                        Rank: %u\n", system_time, curr_instance.dag.rank);
            printf("[%8lu] DEBUG >   INFO >   (cmd_rpl_status) >                                                 Lowest rank: %u (%u)\n", system_time, curr_instance.dag.lowest_rank, curr_instance.max_rankinc);
            printf("[%8lu] DEBUG >   INFO >   (cmd_rpl_status) >                                                    DTSN out: %u\n", system_time, curr_instance.dtsn_out);
            printf("[%8lu] DEBUG >   INFO >   (cmd_rpl_status) >                                                DAO sequence: last sent %u, last acked %u\n", system_time, curr_instance.dag.dao_last_seqno, curr_instance.dag.dao_last_acked_seqno);
            printf("[%8lu] DEBUG >   INFO >   (cmd_rpl_status) >                                               Trickle timer: current %u, min %u, max %u, redundancy %u\n", system_time, curr_instance.dag.dio_intcurrent, curr_instance.dio_intmin, curr_instance.dio_intmin + curr_instance.dio_intdoubl, curr_instance.dio_redundancy);

        }
    }

#endif // (ROUTING_CONF_RPL_LITE)

// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

void oar_debug_cmd_macaddr(unsigned long int system_time)
{
    printf("[%8lu] DEBUG >   INFO >      (cmd_macaddr) >                                            Node MAC address: ", system_time);
        oar_debug_lladdr_to_str(oar_debug_lladdr, &linkaddr_node_addr); printf("%s", oar_debug_lladdr);
        printf("\n");
}

// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

#if NETSTACK_CONF_WITH_IPV6

    void oar_debug_cmd_ipaddr(unsigned long int system_time)
    {
        uint8_t state;

        for(int i = 0; i < UIP_DS6_ADDR_NB; i++) 
        {
            state = uip_ds6_if.addr_list[i].state;
            if(uip_ds6_if.addr_list[i].isused && (state == ADDR_TENTATIVE || state == ADDR_PREFERRED)) 
            {
                printf("[%8lu] DEBUG >   INFO >       (cmd_ipaddr) >                                         Node IPv6 addresses: ", system_time);
                    oar_debug_ipaddr_to_str(oar_debug_ipaddr, &uip_ds6_if.addr_list[i].ipaddr); printf("%s", oar_debug_ipaddr);
                    printf("\n");
            }
        }
    }

    // ----------------------------------------------------------------------------

    void oar_debug_cmd_ip_neighbors(unsigned long int system_time)
    {
        uip_ds6_nbr_t *nbr;
        int oar_ip_neighbor_count = 0;

        nbr = uip_ds6_nbr_head();
        if(nbr == NULL) 
        {
            printf("[%8lu] DEBUG >   INFO > (cmd_ip_neighbors) >                                         Node IPv6 neighbors: none\n", system_time);
        }
        else
        {
            while(nbr != NULL) 
            {
                oar_ip_neighbor_count++;

                printf("[%8lu] DEBUG >   INFO > (cmd_ip_neighbors) >                                        Node IPv6 neighbor %d: ", system_time, oar_ip_neighbor_count);
                    oar_debug_ipaddr_to_str(oar_debug_ipaddr, uip_ds6_nbr_get_ipaddr(nbr)); printf("%s", oar_debug_ipaddr);
                    printf(" <-> ");
                    oar_debug_lladdr_to_str(oar_debug_lladdr, (linkaddr_t *)uip_ds6_nbr_get_ll(nbr)); printf("%s", oar_debug_lladdr);
                    printf(", router %u, state %s ", nbr->isrouter, oar_debug_ds6_nbr_state_to_str(nbr->state));
                    printf("\n");

                nbr = uip_ds6_nbr_next(nbr);
            }
        }
    }

#endif // (NETSTACK_CONF_WITH_IPV6)

// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

#if MAC_CONF_WITH_TSCH

    void oar_debug_cmd_tsch_status(unsigned long int system_time)
    {
        printf("[%8lu] DEBUG >   INFO >  (cmd_tsch_status) >                                              Is coordinator: %u\n", system_time, tsch_is_coordinator);
        printf("[%8lu] DEBUG >   INFO >  (cmd_tsch_status) >                                               Is associated: %u\n", system_time, tsch_is_associated);
                            
        if(tsch_is_associated) 
        {
            struct tsch_neighbor *n = tsch_queue_get_time_source();

            printf("[%8lu] DEBUG >   INFO >  (cmd_tsch_status) >                                                  PAN ID: 0x%x\n", system_time, frame802154_get_pan_id());
            printf("[%8lu] DEBUG >   INFO >  (cmd_tsch_status) >                                          Is PAN secured: %u\n", system_time, tsch_is_pan_secured);
            printf("[%8lu] DEBUG >   INFO >  (cmd_tsch_status) >                                           Join priority: %u\n", system_time, tsch_join_priority);
            
            printf("[%8lu] DEBUG >   INFO >  (cmd_tsch_status) >                                             Time source: ", system_time);
            if(n != NULL) 
            {
                oar_debug_lladdr_to_str(oar_debug_lladdr, &n->addr); printf("%s", oar_debug_lladdr);
                printf("\n");
            } 
            else 
            {
                printf("none\n");
            }
            
            printf("[%8lu] DEBUG >   INFO >  (cmd_tsch_status) >                                          Last synchronized: %lu seconds ago\n", system_time, (clock_time() - tsch_last_sync_time) / CLOCK_SECOND);
            printf("[%8lu] DEBUG >   INFO >  (cmd_tsch_status) >                                   Drift w.r.t. coordinator: %ld ppm\n", system_time, tsch_adaptive_timesync_get_drift_ppm());
            printf("[%8lu] DEBUG >   INFO >  (cmd_tsch_status) >                                             Network uptime: %lu seconds\n", system_time, (unsigned long)(tsch_get_network_uptime_ticks() / CLOCK_SECOND));
        }
    }

#endif // (MAC_CONF_WITH_TSCH)

// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

#if (NETSTACK_CONF_WITH_IPV6)

    void oar_debug_cmd_routes(unsigned long int system_time)
    {
        uip_ds6_defrt_t *default_route;

        default_route = uip_ds6_defrt_lookup(uip_ds6_defrt_choose());

        if(default_route != NULL) 
        {
            printf("[%8lu] DEBUG >   INFO >       (cmd_routes) >                                               Default route: ", system_time);
                oar_debug_ipaddr_to_str(oar_debug_ipaddr, &default_route->ipaddr); printf("%s", oar_debug_ipaddr);
                if(default_route->lifetime.interval != 0) 
                {
                    printf(" (lifetime: %lu seconds)\n", (unsigned long)default_route->lifetime.interval);
                } 
                else 
                {
                    printf(" (lifetime: infinite)\n");
                }
        } 
        else 
        {
            printf("[%8lu] DEBUG >   INFO >       (cmd_routes) >                                               Default route: None\n", system_time);
        }

        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

        #if (UIP_CONF_IPV6_RPL)

            if(uip_sr_num_nodes() > 0) 
            {
                uip_sr_node_t *link;
                
                /* Our routing links */
                printf("[%8lu] DEBUG >   INFO >       (cmd_routes) >                                  Routing links (%u in total):\n", system_time, uip_sr_num_nodes());
                
                link = uip_sr_node_head();

                while(link != NULL) 
                {
                    char buf[100];
                    
                    uip_sr_link_snprint(buf, sizeof(buf), link);
                    
                    printf("-- %s\n", buf);
                    
                    link = uip_sr_node_next(link);
                }
            } 
            else 
            {
                printf("[%8lu] DEBUG >   INFO >       (cmd_routes) >                                               Routing links: None\n", system_time);
            }

        #endif // (UIP_CONF_IPV6_RPL)

        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

        #if (UIP_MAX_ROUTES != 0)

            if(uip_ds6_route_num_routes() > 0) 
            {
                uip_ds6_route_t *route;                             // Our routing entries
                
                printf("[%8lu] DEBUG >   INFO >       (cmd_routes) >                                Routing entries (%u in total):\n", system_time, uip_ds6_route_num_routes());
                
                route = uip_ds6_route_head();
                while(route != NULL) 
                {
                    printf("-- ");
                    oar_debug_ipaddr_to_str(oar_debug_ipaddr, &route->ipaddr); printf("%s", oar_debug_ipaddr);
                    printf(" via ");
                    oar_debug_ipaddr_to_str(oar_debug_ipaddr, uip_ds6_route_nexthop(route)); printf("%s", oar_debug_ipaddr);

                    if((unsigned long)route->state.lifetime != 0xFFFFFFFF) 
                    {
                        printf(" (lifetime: %lu seconds)\n", (unsigned long)route->state.lifetime);
                    } 
                    else 
                    {
                        printf(" (lifetime: infinite)\n");
                    }
                
                    route = uip_ds6_route_next(route);
                }
            } 
            else 
            {
                printf("[%8lu] DEBUG >   INFO >       (cmd_routes) >                                            Routing entries: None\n", system_time);
            }

        #endif // (UIP_MAX_ROUTES != 0)
    }

#endif // (NETSTACK_CONF_WITH_IPV6)

// ====================================================================================================================
// dash Style

void oar_debug_(char dash, int times) 
{
    for (int i = 0; i < times; i++)
    {
        printf("%c", dash);
    }
    
    printf("\n");    
}

















