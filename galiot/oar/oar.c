/*
 * Copyleft (!c) 2019, Hellenic Open University - http://www.eap.gr
 * No rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the Institute nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 * 
 * This file is NOT part of the Contiki operating system.
 */

/*---------------------------------------------------------------------------*/

/**
 * \file
 *          A simple restful backend, just for acquiring, 
 *          printing and sending a couple of mote statistics.
 * 
 * \author
 *          Nikos "galiot" Saridakis <galiot@runbox.com>
 */

/*---------------------------------------------------------------------------*/
















#include "contiki.h"                // main include file for OS-specific modules
#include "lib/heapmem.h"

#include "net/ipv6/uip.h"
#include "net/ipv6/uiplib.h"
#include "net/ipv6/uip-icmp6.h"
#include "net/ipv6/uip-ds6.h"

#if ROUTING_CONF_RPL_LITE
    #include "net/routing/rpl-lite/rpl.h"
#elif ROUTING_CONF_RPL_CLASSIC
    #include "net/routing/rpl-classic/rpl.h"
#endif

#include "net/routing/routing.h"    // for NETSTACK_ROUTING

// <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><
// <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><
// <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><
// <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><

#include "project-conf.h"           // for vscode intellisense (make recipe includes it either way)
#include "oar-debug.h"

// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

#include <stdio.h>                  // for prinntf()
#include <stdlib.h>
#include <string.h>
#include <math.h>

// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

#include "sys/energest.h"
#include "net/ipv6/uip.h"

// -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-

                                    // Texas Instruments CC2650 LaunchPad enabales the following dev I/0:

#include "dev/leds.h"               // leds     (2):    LEDS_LED1, LEDS_LED2 (access both: LEDS_ALL)
#include "dev/button-hal.h"         // buttons  (2):    button_hal_get_by_index(0), button_hal_get_by_index(1)    

// <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><
// <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><
// <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><
// <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><

















// |$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|
// |$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|

// &^&^&^&^&^&^&^&^&^&^&^&^&^&^&^&^&^&^&^&^&^&^&^&^&^&^&^&^&^&^&^&^&^&^&^&^&^&^&^&^&^&^&^&^&^&^&^&^&^&^&^&^&^&^&^&^&^&^&^&^&^&^&^&^&^&^&
#if (OAR_DEBUG_SHELL)





    // XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
    #if NETSTACK_CONF_WITH_IPV6

        void oar_ipaddr_to_str(char *output, const uip_ipaddr_t *ipaddr) 
        {
            char buf[UIPLIB_IPV6_MAX_STR_LEN];
            memset(output, 0, sizeof(output));

            uiplib_ipaddr_snprint(buf, sizeof(buf), ipaddr);

            strcpy(output, buf);
        }
        
        // -----------------------------------------------------------------------------------------------------------------------------

        // static const char *ds6_nbr_state_to_str(uint8_t state)
        // {
        //     switch(state) 
        //     {
        //         case NBR_INCOMPLETE:
        //             return "Incomplete";

        //         case NBR_REACHABLE:
        //             return "Reachable";

        //         case NBR_STALE:
        //             return "Stale";

        //         case NBR_DELAY:
        //             return "Delay";

        //         case NBR_PROBE:
        //             return "Probe";

        //         default:
        //             return "Unknown";
        //     }
        // }

    #endif  /* NETSTACK_CONF_WITH_IPV6 */
    // XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX




    void oar_lladdr_to_str(char *output, const linkaddr_t *lladdr) 
    {
        char buf[5];
        memset(output, 0, sizeof(output));
    
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
    
    
    
    
    // [][][][][][][][][][][][]][][][][][][][][][][][][][][][][][][][][][][][]
    #if ROUTING_CONF_RPL_LITE
    
        // static const char *rpl_state_to_str(enum rpl_dag_state state)
        // {
        //     switch(state) 
        //     {
        //         case DAG_INITIALIZED:
        //             return "Initialized";
        
        //         case DAG_JOINED:
        //             return "Joined";
        
        //         case DAG_REACHABLE:
        //             return "Reachable";
        
        //         case DAG_POISONING:
        //             return "Poisoning";
        
        //         default:
        //             return "Unknown";
        //     }
        // }
        
        // // -----------------------------------------------------------------------------------------------------------------------------
        
        // static const char *rpl_mop_to_str(int mop)
        // {
        //     switch(mop) 
        //     {
        //         case RPL_MOP_NO_DOWNWARD_ROUTES:
        //             return "No downward routes";
        
        //         case RPL_MOP_NON_STORING:
        //             return "Non-storing";
        
        //         case RPL_MOP_STORING_NO_MULTICAST:
        //             return "Storing";
        
        //         case RPL_MOP_STORING_MULTICAST:
        //             return "Storing+multicast";
        
        //         default:
        //             return "Unknown";
        //     }
        // }
        
        // // -----------------------------------------------------------------------------------------------------------------------------
        
        // static const char *rpl_ocp_to_str(int ocp)
        // {
        //     switch(ocp) 
        //     {
        //         case RPL_OCP_OF0:
        //         return "OF0";
        
        //         case RPL_OCP_MRHOF:
        //         return "MRHOF";
                
        //         default:
        //         return "Unknown";
        //     }
        // }
        
    #endif  /* ROUTING_CONF_RPL_LITE */
    // [][][][][][][][][][][][]][][][][][][][][][][][][][][][][][][][][][][][]




#endif  /* (OAR_DEBUG_SHELL) */
// &^&^&^&^&^&^&^&^&^&^&^&^&^&^&^&^&^&^&^&^&^&^&^&^&^&^&^&^&^&^&^&^&^&^&^&^&^&^&^&^&^&^&^&^&^&^&^&^&^&^&^&^&^&^&^&^&^&^&^&^&^&^&^&^&^&^&

    







// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#if (OAR_DEBUG_ENERGEST)
    // static unsigned long to_seconds(uint64_t time)
    // {
    //     return (unsigned long)(time / ENERGEST_SECOND);
    // }
#endif  /* OAR_DEBUG_ENERGEST */
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%



// |$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|
// |$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|
















// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

// (doc) A process is first declared at the top of a source file.
// (doc) The PROCESS() macro takes two arguments:   
// (doc)    one is the variable with which we identify the process, 
// (doc)    and the other is the name of the process. 
// (doc) On the second line, we tell Contiki-NG that this process should be automatically started directly after the system has booted up. 
// (doc) Multiple processes can be specified here by separating them with commas. 


PROCESS(oar_debug_process, "oar debug process");                    // process for printing on console
PROCESS(oar_dev_process, "oar dev process");                        // process for testing dev I/O

AUTOSTART_PROCESSES(&oar_debug_process, &oar_dev_process);          

// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
















PROCESS_THREAD(oar_debug_process, ev, data)
{   
    
    #if !(OAR_DEBUG)

        // (doc) A process can be stopped in three ways:
        // (doc)    The process implicitly exits by allowing the PROCESS_END() statement to be reached and executed.
        // (doc)    The process explicitly exits by calling PROCESS_EXIT() in the PROCESS_THREAD body.
        // (doc)    Another process kills the process by calling process_exit().
        // (doc) After stopping a process, it can be restarted from the beginning by calling process_start().

        PROCESS_EXIT();

    #else      /* OAR_DEBUG */




        // ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
            
            static struct etimer debug_timer;                       // An event-timer variable. Note that this variable must be static in order to preserve the value across yielding.
            // unsigned long int debug_system_time = clock_seconds(); 

            // char oar_ipaddr[UIPLIB_IPV6_MAX_STR_LEN];
            // char oar_lladdr[UIPLIB_IPV6_MAX_STR_LEN];     

        // ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
            
            



        PROCESS_BEGIN();

            etimer_set(&debug_timer, CLOCK_SECOND * OAR_DEBUG_INTERVAL);        // Setup a periodic timer that expires after OAR_DEBUG_INTERVAL seconds (trigger this timer after these OAR_DEBUG_INTERVAL seconds have passed).
            
            while(1) {

                    // printf("[%8lu] DEBUG \t > \t hello world \n", debug_system_time);



                    




                    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
                    #if (OAR_DEBUG_ENERGEST)
                    
                        // energest_flush();       // Update all energest times.

                        // printf("\n");

                        // printf("[%8lu] DEBUG > \t ENERGEST > \t CPU:            \t %4lu \n",    debug_system_time, to_seconds(energest_type_time(ENERGEST_TYPE_CPU)));
                        // printf("[%8lu] DEBUG > \t ENERGEST > \t LPM:            \t %4lu \n",    debug_system_time, to_seconds(energest_type_time(ENERGEST_TYPE_LPM)));
                        // printf("[%8lu] DEBUG > \t ENERGEST > \t DEEP LPM:       \t %4lu \n",    debug_system_time, to_seconds(energest_type_time(ENERGEST_TYPE_DEEP_LPM)));
                        // printf("[%8lu] DEBUG > \t ENERGEST > \t TOTAL TIME:     \t %4lu \n",    debug_system_time, to_seconds(ENERGEST_GET_TOTAL_TIME()));

                        // printf("------------------------------------------------------------------------ \n");

                        // printf("[%8lu] DEBUG > \t ENERGEST > \t RADIO LISTEN:   \t %4lu \n",    debug_system_time, to_seconds(energest_type_time(ENERGEST_TYPE_LISTEN)));
                        // printf("[%8lu] DEBUG > \t ENERGEST > \t RADIO TRANSMIT: \t %4lu \n",    debug_system_time, to_seconds(energest_type_time(ENERGEST_TYPE_TRANSMIT)));
                        // printf("[%8lu] DEBUG > \t ENERGEST > \t RADIO OFF:      \t %4lu \n",    debug_system_time, to_seconds(ENERGEST_GET_TOTAL_TIME() - energest_type_time(ENERGEST_TYPE_TRANSMIT) - energest_type_time(ENERGEST_TYPE_LISTEN)));
                        
                        // printf("\n");

                        oar_debug_energest(clock_seconds());

                        printf("\n");

                    #endif  /* OAR_DEBUG_ENERGEST */                                                               
                    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% 




                    // <-%-><-%-><-%-><-%-><-%-><-%-><-%-><-%-><-%-><-%-><-%-><-%-><-%-><-%-><-%-><-%-><-%-><-%-><-%-><-%-><-%-><-%-><-%
                    #if (OAR_DEBUG_STATISTICS)
                    
                        

                        // printf("[%8lu] DEBUG > \t   IP STATS > \t       (ip.recv) %10lu > Number of received packets at the IP layer\n", debug_system_time, uip_stat.ip.recv);
                        // printf("[%8lu] DEBUG > \t   IP STATS > \t       (ip.sent) %10lu > Number of sent packets at the IP layer\n", debug_system_time, uip_stat.ip.sent);
                        // printf("[%8lu] DEBUG > \t   IP STATS > \t  (ip.forwarded) %10lu > Number of forwarded packets at the IP layer\n", debug_system_time, uip_stat.ip.forwarded);
                        // printf("[%8lu] DEBUG > \t   IP STATS > \t       (ip.drop) %10lu > Number of dropped packets at the IP layer\n", debug_system_time, uip_stat.ip.drop);
                        // printf("[%8lu] DEBUG > \t   IP STATS > \t     (ip.vhlerr) %10lu > Number of packets dropped due to wrong IP version or header length\n", debug_system_time, uip_stat.ip.vhlerr);
                        // printf("[%8lu] DEBUG > \t   IP STATS > \t   (ip.hblenerr) %10lu > Number of packets dropped due to wrong IP length, high byte\n", debug_system_time, uip_stat.ip.hblenerr);
                        // printf("[%8lu] DEBUG > \t   IP STATS > \t   (ip.lblenerr) %10lu > Number of packets dropped due to wrong IP length, low byte\n", debug_system_time, uip_stat.ip.lblenerr);
                        // printf("[%8lu] DEBUG > \t   IP STATS > \t    (ip.fragerr) %10lu > Number of packets dropped because they were IP fragments\n", debug_system_time, uip_stat.ip.fragerr);
                        // printf("[%8lu] DEBUG > \t   IP STATS > \t     (ip.chkerr) %10lu > Number of packets dropped due to IP checksum errors\n", debug_system_time, uip_stat.ip.chkerr);
                        // printf("[%8lu] DEBUG > \t   IP STATS > \t   (ip.protoerr) %10lu > Number of packets dropped because they were neither ICMP, UDP nor TCP\n", debug_system_time, uip_stat.ip.protoerr);
                        
                        oar_debug_stats_ip(clock_seconds());

                        printf("------------------------------------------------------------------------------------------------------------------------------------------------------\n");


                        // printf("[%8lu] DEBUG > \t ICMP STATS > \t     (icmp.recv) %10lu > Number of received ICMP packets\n", debug_system_time, uip_stat.icmp.recv);
                        // printf("[%8lu] DEBUG > \t ICMP STATS > \t     (icmp.sent) %10lu > Number of sent ICMP packets\n", debug_system_time, uip_stat.icmp.sent);
                        // printf("[%8lu] DEBUG > \t ICMP STATS > \t     (icmp.drop) %10lu > Number of dropped ICMP packets\n", debug_system_time, uip_stat.icmp.drop);
                        // printf("[%8lu] DEBUG > \t ICMP STATS > \t  (icmp.typeerr) %10lu > Number of ICMP packets with a wrong type\n", debug_system_time, uip_stat.icmp.typeerr);
                        // printf("[%8lu] DEBUG > \t ICMP STATS > \t   (icmp.chkerr) %10lu > Number of ICMP packets with a bad checksum\n", debug_system_time, uip_stat.icmp.chkerr);

                        oar_debug_stats_icmp(clock_seconds());

                        printf("------------------------------------------------------------------------------------------------------------------------------------------------------\n");


                        // ()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()
                        #if UIP_TCP

                            // printf("[%8lu] DEBUG > \t  TCP STATS > \t      (tcp.recv) %10lu > Number of received TCP segments\n", debug_system_time, uip_stat.tcp.recv);
                            // printf("[%8lu] DEBUG > \t  TCP STATS > \t      (tcp.sent) %10lu > Number of sent TCP segments\n", debug_system_time, uip_stat.tcp.sent);
                            // printf("[%8lu] DEBUG > \t  TCP STATS > \t      (tcp.drop) %10lu > Number of dropped TCP segments\n", debug_system_time, uip_stat.tcp.drop);
                            // printf("[%8lu] DEBUG > \t  TCP STATS > \t    (tcp.chkerr) %10lu > Number of TCP segments with a bad checksum\n", debug_system_time, uip_stat.tcp.chkerr);
                            // printf("[%8lu] DEBUG > \t  TCP STATS > \t    (tcp.ackerr) %10lu > Number of TCP segments with a bad ACK number\n", debug_system_time, uip_stat.tcp.ackerr);
                            // printf("[%8lu] DEBUG > \t  TCP STATS > \t       (tcp.rst) %10lu > Number of received TCP RST (reset) segments\n", debug_system_time, uip_stat.tcp.rst);
                            // printf("[%8lu] DEBUG > \t  TCP STATS > \t    (tcp.rexmit) %10lu > Number of retransmitted TCP segments\n", debug_system_time, uip_stat.tcp.rexmit);
                            // printf("[%8lu] DEBUG > \t  TCP STATS > \t   (tcp.syndrop) %10lu > Number of dropped SYNs because too few connections were available\n", debug_system_time, uip_stat.tcp.syndrop);
                            // printf("[%8lu] DEBUG > \t  TCP STATS > \t    (tcp.synrst) %10lu > Number of SYNs for closed ports, triggering a RST\n", debug_system_time, uip_stat.tcp.synrst);

                            oar_debug_stats_tcp(clock_seconds());

                            printf("------------------------------------------------------------------------------------------------------------------------------------------------------\n");
                        
                        #endif  /* UIP_TCP */
                        // ()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()


                        // ()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()
                        #if UIP_UDP

                            // printf("[%8lu] DEBUG > \t  UDP STATS > \t      (udp.drop) %10lu > Number of dropped UDP segments\n", debug_system_time, uip_stat.udp.drop);
                            // printf("[%8lu] DEBUG > \t  UDP STATS > \t      (udp.recv) %10lu > Number of received UDP segments\n", debug_system_time, uip_stat.udp.recv);
                            // printf("[%8lu] DEBUG > \t  UDP STATS > \t      (udp.sent) %10lu > Number of sent UDP segments\n", debug_system_time, uip_stat.udp.sent);
                            // printf("[%8lu] DEBUG > \t  UDP STATS > \t    (udp.chkerr) %10lu > Number of UDP segments with a bad checksum\n", debug_system_time, uip_stat.udp.chkerr);
                            

                            oar_debug_stats_udp(clock_seconds());

                            printf("------------------------------------------------------------------------------------------------------------------------------------------------------\n");

                        #endif  /* UIP_UDP */
                        // ()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()

            
                        // printf("[%8lu] DEBUG > \t  ND6 STATS > \t      (nd6.drop) %10lu > Number of dropped ND6 packets\n", debug_system_time, uip_stat.nd6.drop);
                        // printf("[%8lu] DEBUG > \t  ND6 STATS > \t      (nd6.recv) %10lu > Number of dropped ND6 packets\n", debug_system_time, uip_stat.nd6.recv);
                        // printf("[%8lu] DEBUG > \t  ND6 STATS > \t      (nd6.sent) %10lu > Number of dropped ND6 packets\n", debug_system_time, uip_stat.nd6.sent);

                        oar_debug_stats_nd6(clock_seconds());

                        printf("\n");

                    #endif      /* (OAR_DEBUG_STATISTICS) */
                    // <-%-><-%-><-%-><-%-><-%-><-%-><-%-><-%-><-%-><-%-><-%-><-%-><-%-><-%-><-%-><-%-><-%-><-%-><-%-><-%-><-%-><-%-><-%

                    



                    // $-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$
                    #if (OAR_DEBUG_SHELL)





                        // [][][][][][][][][][][][]][][][][][][][][][][][][][][][][][][][][][][][]
                        #if ROUTING_CONF_RPL_LITE


                            // if(!curr_instance.used || rpl_neighbor_count() == 0) 
                            // {
                            //     printf("[%8lu] DEBUG > \t SHELL > \t      (cmd_rpl_nbr) RPL neighbor (0/%d)\n", debug_system_time, rpl_neighbor_count());
                            // } 
                            // else 
                            // {
                            //     rpl_nbr_t *nbr = nbr_table_head(rpl_neighbors);
                            //     int oar_rpl_neighbor_count = 0;

                            //     while(nbr != NULL) 
                            //     {
                            //         char buf[120];
                            //         oar_rpl_neighbor_count++;
                                    
                            //         rpl_neighbor_snprint(buf, sizeof(buf), nbr);
                            //         printf("[%8lu] DEBUG > \t SHELL > \t      (cmd_rpl_nbr) RPL neighbor %d/%d: %s\n", debug_system_time, oar_rpl_neighbor_count, rpl_neighbor_count(), buf);
                            //         nbr = nbr_table_next(rpl_neighbors, nbr);
                            //     }
                            // }

                            oar_debug_cmd_rpl_nbr(clock_seconds());
                            

                            // ---------------------------------------------------------------------------------------------------------
                            printf("------------------------------------------------------------------------------------------------------------------------------------------------------\n");
                            

                            // if(!curr_instance.used) 
                            // {
                            //     printf("[%8lu] DEBUG > \t SHELL > \t   (cmd_rpl_status) Instance: None\n", debug_system_time);
                            // } 
                            // else 
                            // {
                            //     printf("[%8lu] DEBUG > \t SHELL > \t   (cmd_rpl_status) Instance: %u\n", debug_system_time, curr_instance.instance_id);

                            //     if(NETSTACK_ROUTING.node_is_root()) 
                            //     {
                            //         printf("[%8lu] DEBUG > \t SHELL > \t   (cmd_rpl_status) DAG root\n", debug_system_time);
                            //     } 
                            //     else 
                            //     {
                            //         printf("[%8lu] DEBUG > \t SHELL > \t   (cmd_rpl_status) DAG node\n", debug_system_time);
                            //     }
                                
                            //     printf("[%8lu] DEBUG > \t SHELL > \t   (cmd_rpl_status) DAG: ", debug_system_time);
                            //     oar_ipaddr_to_str(oar_ipaddr, &curr_instance.dag.dag_id); printf("%s", oar_ipaddr);
                            //     printf(", version %u\n", curr_instance.dag.version);

                            //     printf("[%8lu] DEBUG > \t SHELL > \t   (cmd_rpl_status) Prefix: ", debug_system_time);
                            //     oar_debug_ipaddr_to_str(oar_ipaddr, &curr_instance.dag.prefix_info.prefix); printf("%s", oar_ipaddr); 
                            //     printf("/%u\n", curr_instance.dag.prefix_info.length);

                            //     printf("[%8lu] DEBUG > \t SHELL > \t   (cmd_rpl_status) MOP: %s\n", debug_system_time, rpl_mop_to_str(curr_instance.mop));
                            //     printf("[%8lu] DEBUG > \t SHELL > \t   (cmd_rpl_status) OF: %s\n", debug_system_time, rpl_ocp_to_str(curr_instance.of->ocp));
                            //     printf("[%8lu] DEBUG > \t SHELL > \t   (cmd_rpl_status) Hop rank increment: %u\n", debug_system_time, curr_instance.min_hoprankinc);

                            //     printf("[%8lu] DEBUG > \t SHELL > \t   (cmd_rpl_status) Default lifetime: %lu seconds\n", debug_system_time, RPL_LIFETIME(curr_instance.default_lifetime));

                            //     printf("[%8lu] DEBUG > \t SHELL > \t   (cmd_rpl_status) State: %s\n", debug_system_time, rpl_state_to_str(curr_instance.dag.state));
                                
                            //     printf("[%8lu] DEBUG > \t SHELL > \t   (cmd_rpl_status) Preferred parent: ", debug_system_time);
                            //     if(curr_instance.dag.preferred_parent) 
                            //     {
                            //         oar_ipaddr_to_str(oar_ipaddr, rpl_neighbor_get_ipaddr(curr_instance.dag.preferred_parent)); printf("%s", oar_ipaddr);
                            //         printf(" (last DTSN: %u)\n", curr_instance.dag.preferred_parent->dtsn);
                            //     } 
                            //     else 
                            //     {
                            //         printf("None\n");
                            //     }

                            //     printf("[%8lu] DEBUG > \t SHELL > \t   (cmd_rpl_status) Rank: %u\n", debug_system_time, curr_instance.dag.rank);
                                
                            //     printf("[%8lu] DEBUG > \t SHELL > \t   (cmd_rpl_status) Lowest rank: %u (%u)\n", debug_system_time, curr_instance.dag.lowest_rank, curr_instance.max_rankinc);
                                
                            //     printf("[%8lu] DEBUG > \t SHELL > \t   (cmd_rpl_status) DTSN out: %u\n", debug_system_time, curr_instance.dtsn_out);
                                
                            //     printf("[%8lu] DEBUG > \t SHELL > \t   (cmd_rpl_status) DAO sequence: last sent %u, last acked %u\n", debug_system_time, curr_instance.dag.dao_last_seqno, curr_instance.dag.dao_last_acked_seqno);
                                
                            //     printf("[%8lu] DEBUG > \t SHELL > \t   (cmd_rpl_status) Trickle timer: current %u, min %u, max %u, redundancy %u\n", debug_system_time, curr_instance.dag.dio_intcurrent, curr_instance.dio_intmin, curr_instance.dio_intmin + curr_instance.dio_intdoubl, curr_instance.dio_redundancy);

                            // }

                            oar_debug_cmd_rpl_status(clock_seconds());

                            printf("------------------------------------------------------------------------------------------------------------------------------------------------------\n");
                            

                        #endif  /* ROUTING_CONF_RPL_LITE */
                        // [][][][][][][][][][][][]][][][][][][][][][][][][][][][][][][][][][][][]




                        // printf("[%8lu] DEBUG > \t SHELL > \t      (cmd_macaddr) Node MAC address: ", debug_system_time);
                        // oar_lladdr_to_str(oar_lladdr, &linkaddr_node_addr); printf("%s", oar_lladdr);
                        // printf("\n");

                        oar_debug_cmd_macaddr(clock_seconds());





                        // XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
                        #if NETSTACK_CONF_WITH_IPV6

                            printf("------------------------------------------------------------------------------------------------------------------------------------------------------\n");

                            // uint8_t state;

                            // for(int i = 0; i < UIP_DS6_ADDR_NB; i++) 
                            // {
                            //     state = uip_ds6_if.addr_list[i].state;
                            //     if(uip_ds6_if.addr_list[i].isused && (state == ADDR_TENTATIVE || state == ADDR_PREFERRED)) 
                            //     {
                            //         printf("[%8lu] DEBUG > \t SHELL > \t       (cmd_ipaddr) Node IPv6 addresses: ", debug_system_time);
                            //         oar_ipaddr_to_str(oar_ipaddr, &uip_ds6_if.addr_list[i].ipaddr); printf("%s", oar_ipaddr);
                            //         printf("\n");
                            //     }
                            // }

                            oar_debug_cmd_ipaddr(clock_seconds());

                            // ---------------------------------------------------------------------------------------------------------
                            printf("------------------------------------------------------------------------------------------------------------------------------------------------------\n");

                            // uip_ds6_nbr_t *nbr;
                            // int oar_ip_neighbor_count = 0;

                            // nbr = uip_ds6_nbr_head();
                            // if(nbr == NULL) 
                            // {
                            //     printf("[%8lu] DEBUG > \t SHELL > \t (cmd_ip_neighbors) Node IPv6 neighbors: none\n", debug_system_time);
                            // }
                            // else
                            // {
                            //     while(nbr != NULL) 
                            //     {
                            //         oar_ip_neighbor_count++;

                            //         printf("[%8lu] DEBUG > \t SHELL > \t (cmd_ip_neighbors) Node IPv6 neighbor %d: ", debug_system_time, oar_ip_neighbor_count);
                            //         oar_ipaddr_to_str(oar_ipaddr, uip_ds6_nbr_get_ipaddr(nbr)); printf("%s", oar_ipaddr);
                            //         printf(" <-> ");
                            //         oar_lladdr_to_str(oar_lladdr, (linkaddr_t *)uip_ds6_nbr_get_ll(nbr)); printf("%s", oar_lladdr);
                            //         printf(", router %u, state %s ", nbr->isrouter, ds6_nbr_state_to_str(nbr->state));
                            //         printf("\n");

                            //         nbr = uip_ds6_nbr_next(nbr);
                            //     }
                            // }

                            oar_debug_cmd_ip_neighbors(clock_seconds());
                        

                        #endif  /* NETSTACK_CONF_WITH_IPV6 */
                        // XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
                        


                        // TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
                        #if MAC_CONF_WITH_TSCH

                            printf("------------------------------------------------------------------------------------------------------------------------------------------------------\n");

                            // printf("[%8lu] DEBUG > \t SHELL > \t  (cmd_tsch_status) Is coordinator: %u\n", debug_system_time, tsch_is_coordinator);
                            // printf("[%8lu] DEBUG > \t SHELL > \t  (cmd_tsch_status) Is associated: %u\n", tsch_is_associated);
                            
                            // if(tsch_is_associated) 
                            // {
                            //     struct tsch_neighbor *n = tsch_queue_get_time_source();

                            //     printf("[%8lu] DEBUG > \t SHELL > \t  (cmd_tsch_status) PAN ID: 0x%x\n", debug_system_time, frame802154_get_pan_id());
                            //     printf("[%8lu] DEBUG > \t SHELL > \t  (cmd_tsch_status) Is PAN secured: %u\n", debug_system_time, tsch_is_pan_secured);
                            //     printf("[%8lu] DEBUG > \t SHELL > \t  (cmd_tsch_status) Join priority: %u\n", debug_system_time, tsch_join_priority);
                            //     printf("[%8lu] DEBUG > \t SHELL > \t  (cmd_tsch_status) Time source: ", debug_system_time);

                            //     if(n != NULL) 
                            //     {
                            //         oar_lladdr_to_str(oar_lladdr, &n->addr); printf("%s", oar_lladdr);
                            //         printf("\n");
                            //     } 
                            //     else 
                            //     {
                            //         printf("none\n");
                            //     }
                                
                            //     printf("[%8lu] DEBUG > \t SHELL > \t  (cmd_tsch_status) Last synchronized: %lu seconds ago\n", debug_system_time, (clock_time() - tsch_last_sync_time) / CLOCK_SECOND);
                            //     printf("[%8lu] DEBUG > \t SHELL > \t  (cmd_tsch_status) Drift w.r.t. coordinator: %ld ppm\n", debug_system_time, tsch_adaptive_timesync_get_drift_ppm());
                            //     printf("[%8lu] DEBUG > \t SHELL > \t  (cmd_tsch_status) Network uptime: %lu seconds\n", debug_system_time, (unsigned long)(tsch_get_network_uptime_ticks() / CLOCK_SECOND));
                            // }

                            oar_debug_cmd_tsch_status(clock_seconds());


                        #endif  /* MAC_CONF_WITH_TSCH */
                        // TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT




                        // v6v6v6v6v6v6v6v6v6v6v6v6v6v6v6v6v6v6v6v6v6v6v6v6v6v6v6v6v6v6v6v6v6v6v6v
                        #if NETSTACK_CONF_WITH_IPV6

                            
                            printf("------------------------------------------------------------------------------------------------------------------------------------------------------\n");

                            // uip_ds6_defrt_t *default_route;

                            // default_route = uip_ds6_defrt_lookup(uip_ds6_defrt_choose());

                            // if(default_route != NULL) 
                            // {
                            //     printf("[%8lu] DEBUG > \t SHELL > \t       (cmd_routes) Default route: ", debug_system_time);
                            //     oar_ipaddr_to_str(oar_ipaddr, &default_route->ipaddr); printf("%s", oar_ipaddr);
                                
                            //     if(default_route->lifetime.interval != 0) 
                            //     {
                            //         printf(" (lifetime: %lu seconds)\n", (unsigned long)default_route->lifetime.interval);
                            //     } 
                            //     else 
                            //     {
                            //         printf(" (lifetime: infinite)\n");
                            //     }
                            // } 
                            // else 
                            // {
                            //     printf("[%8lu] DEBUG > \t SHELL > \t       (cmd_routes) Default route: None\n", debug_system_time);
                            // }

                            oar_debug_cmd_routes(clock_seconds());



                            // // v6|RPL|v6|RPL|v6|RPL|v6|RPL|v6|RPL|v6|RPL|v6|RPL
                            // #if UIP_CONF_IPV6_RPL


                                // printf("------------------------------------------------------------------------------------------------------------------------------------------------------\n");

                                // if(uip_sr_num_nodes() > 0) 
                                // {
                                //     uip_sr_node_t *link;
                                    
                                //     /* Our routing links */
                                //     printf("[%8lu] DEBUG > \t SHELL > \t       (cmd_routes) Routing links (%u in total):\n", debug_system_time, uip_sr_num_nodes());
                                    
                                //     link = uip_sr_node_head();

                                //     while(link != NULL) 
                                //     {
                                //         char buf[100];
                                        
                                //         uip_sr_link_snprint(buf, sizeof(buf), link);
                                        
                                //         printf("-- %s\n", buf);
                                        
                                //         link = uip_sr_node_next(link);
                                //     }
                                // } 
                                // else 
                                // {
                                //     printf("[%8lu] DEBUG > \t SHELL > \t       (cmd_routes) No routing links\n", debug_system_time);
                                // }


                            // #endif  /* UIP_CONF_IPV6_RPL */
                            // // v6|RPL|v6|RPL|v6|RPL|v6|RPL|v6|RPL|v6|RPL|v6|RPL




                            // // 000000000000000000000000000000000000000000000000
                            // #if (UIP_MAX_ROUTES != 0)

                            
                            // printf("------------------------------------------------------------------------------------------------------------------------------------------------------\n");

                            // if(uip_ds6_route_num_routes() > 0) 
                            // {
                            //     uip_ds6_route_t *route;
                            //     /* Our routing entries */
                            //     printf("[%8lu] DEBUG > \t SHELL > \t       (cmd_routes) Routing entries (%u in total):\n", debug_system_time, uip_ds6_route_num_routes());
                            //     route = uip_ds6_route_head();
                            
                            //     while(route != NULL) 
                            //     {
                            //         printf("-- ");
                            //         oar_ipaddr_to_str(oar_ipaddr, &route->ipaddr); printf("%s", oar_ipaddr);
                            //         printf(" via ");
                            //         oar_ipaddr_to_str(oar_ipaddr, uip_ds6_route_nexthop(route)); printf("%s", oar_ipaddr);

                            //         if((unsigned long)route->state.lifetime != 0xFFFFFFFF) 
                            //         {
                            //             printf(" (lifetime: %lu seconds)\n", (unsigned long)route->state.lifetime);
                            //         } 
                            //         else 
                            //         {
                            //             printf(" (lifetime: infinite)\n");
                            //         }
                              
                            //         route = uip_ds6_route_next(route);
                            //     }
                            // } 
                            // else 
                            // {
                            //     printf("[%8lu] DEBUG > \t SHELL > \t       (cmd_routes) No routing entries\n", debug_system_time);
                            // }


                            // #endif  /* (UIP_MAX_ROUTES != 0) */
                            // // 000000000000000000000000000000000000000000000000



                        #endif  /* NETSTACK_CONF_WITH_IPV6 */
                        // v6v6v6v6v6v6v6v6v6v6v6v6v6v6v6v6v6v6v6v6v6v6v6v6v6v6v6v6v6v6v6v6v6v6v6v

                    
                    printf("\n");
                    printf("\n");




                    #endif      /* (OAR_DEBUG_SHELL) */
                    // $-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$-$











                    // (doc) By calling PROCESS_WAIT_EVENT_UNTIL() in the area separated by the PROCESS_BEGIN() and PROCESS_END() calls, 
                    // (doc) one can yield control to the scheduler, and only resume execution when an event is delivered. 
                    // (doc) A condition is given as an argument to PROCESS_WAIT_EVENT_UNTIL(), 
                    // (doc) and this condition must be fulfilled for the processes to continue execution after the call to PROCESS_WAIT_EVENT_UNTIL(). 
                    // (doc) If the condition is not fulfilled, the process yields control back to the OS until a new event is delivered.
                    
                    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&debug_timer));         // Wait for the periodic timer to expire and then restart the timer.
                    etimer_reset(&debug_timer);

                    // (doc) To voluntarily release control the scheduler, one can call PROCESS_PAUSE(). 
                    // (doc) The scheduler will then deliver any queued events, and then immediately schedule the paused process.

                    // PROCESS_PAUSE();

                    // (doc) A process that has yielded can be polled by an external process or module by calling process_poll(). 
                    // (doc) To poll a process declared with the variable test_proc, one can call process_poll(&test_proc);.
                    // (doc) The polled process will be scheduled immediately, and a PROCESS_EVENT_POLL event will be delivered to it.
                    
                    process_poll(&oar_dev_process);

                
                }

        PROCESS_END();
    
    #endif      /* OAR_DEBUG */
}

    
















PROCESS_THREAD(oar_dev_process, ev, data)
{
    
    #if !(OAR_DEV)

        // (doc) A process can be stopped in three ways:
        // (doc)    The process implicitly exits by allowing the PROCESS_END() statement to be reached and executed.
        // (doc)    The process explicitly exits by calling PROCESS_EXIT() in the PROCESS_THREAD body.
        // (doc)    Another process kills the process by calling process_exit().
        // (doc) After stopping a process, it can be restarted from the beginning by calling process_start().

        PROCESS_EXIT();

    #else   /* OAR_DEV */
        
        
        

        // -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
        
        button_hal_button_t *dev_btn;
        unsigned long int dev_system_time = clock_seconds();

        // -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-

  
  

        PROCESS_BEGIN();

            printf("[%8lu] DEV \t > \t device button count: %u.\n", dev_system_time, button_hal_button_count);

            for (int i = 0; i < button_hal_button_count; i++)
            {
                dev_btn = button_hal_get_by_index(i);

                if(dev_btn) 
                {
                    printf("[%8lu] DEV \t > \t %s on pin %u with ID=%d, Logic=%s, Pull=%s\n", dev_system_time, BUTTON_HAL_GET_DESCRIPTION(dev_btn), dev_btn->pin, i, dev_btn->negative_logic ? "Negative" : "Positive", dev_btn->pull == GPIO_HAL_PIN_CFG_PULL_UP ? "Pull Up" : "Pull Down");
                }
            }

            while(1) {

                // (doc) PROCESS_YIELD() will yield control back to the scheduler without expecting to be scheduled again shortly thereafter. 
                // (doc) Instead, it will wait for an incoming event, similar to PROCESS_WAIT_EVENT_UNTIL(), but without a required condition argument. 
                // (doc) A process that has yielded can be polled by an external process or module by calling process_poll(). 
                // (doc) To poll a process declared with the variable test_proc, one can call process_poll(&test_proc);. 
                // (doc) The polled process will be scheduled immediately, and a PROCESS_EVENT_POLL event will be delivered to it.
                
                PROCESS_YIELD();

                // ---------------------------------------------------------------------------------------------------------------------

                // leds_set(LEDS_ALL);
                // leds_off(LEDS_ALL);
                // leds_toggle(LEDS_ALL);
                // leds_on(LEDS_ALL);

                // leds_single_on(LEDS_LED1);
                // leds_single_off(LEDS_LED1);
                // leds_single_toggle(LEDS_LED1);

                // leds_single_on(LEDS_LED2);
                // leds_single_off(LEDS_LED2);
                // leds_single_toggle(LEDS_LED2);


                if (dev_system_time % 2 == 0)       // every even second, as long as oar_dev_process has control  
                {
                    leds_single_on(LEDS_LED1);
                    leds_single_off(LEDS_LED2);
                }
                else                                // every odd second, , as long as oar_dev_process has control
                {
                    leds_single_off(LEDS_LED1);
                    leds_single_on(LEDS_LED2);
                }

                // ---------------------------------------------------------------------------------------------------------------------

                // press button
                
                if(ev == button_hal_press_event) 
                {
                    dev_btn = (button_hal_button_t *)data;
                    printf("[%8lu] DEV \t > \t Press event (%s)\n", dev_system_time, BUTTON_HAL_GET_DESCRIPTION(dev_btn));

                    if(dev_btn == button_hal_get_by_id(BUTTON_HAL_ID_BUTTON_ZERO)) 
                    {
                        printf("[%8lu] DEV \t > \t This was button 0 (press event), on pin %u\n", dev_system_time, dev_btn->pin);
                    }

                    if(dev_btn == button_hal_get_by_id(BUTTON_HAL_ID_BUTTON_ONE)) 
                    {
                        printf("[%8lu] DEV \t > \t This was button 1 (press event), on pin %u\n", dev_system_time, dev_btn->pin);
                    }
                }
                
                // release button

                else if(ev == button_hal_release_event) 
                {
                    dev_btn = (button_hal_button_t *)data;
                    printf("[%8lu] DEV \t > \t Release event (%s)\n", dev_system_time, BUTTON_HAL_GET_DESCRIPTION(dev_btn));

                    if(dev_btn == button_hal_get_by_id(BUTTON_HAL_ID_BUTTON_ZERO)) 
                    {
                        printf("[%8lu] DEV \t > \t This was button 0 (release event), on pin %u\n", dev_system_time, dev_btn->pin);
                    }

                    if(dev_btn == button_hal_get_by_id(BUTTON_HAL_ID_BUTTON_ONE)) 
                    {
                        printf("[%8lu] DEV \t > \t This was button 1 (release event), on pin %u\n", dev_system_time, dev_btn->pin);
                    }
                }
                
                // keep button

                else if(ev == button_hal_periodic_event) 
                {
                    dev_btn = (button_hal_button_t *)data;
                    printf("[%8lu] DEV \t > \t Periodic event, %u seconds (%s)\n", dev_system_time, dev_btn->press_duration_seconds, BUTTON_HAL_GET_DESCRIPTION(dev_btn));

                    if(dev_btn == button_hal_get_by_id(BUTTON_HAL_ID_BUTTON_ZERO)) 
                    {
                        printf("[%8lu] DEV \t > \t This was button 0 (periodic event), on pin %u\n", dev_system_time, dev_btn->pin);
                    }

                    if(dev_btn == button_hal_get_by_id(BUTTON_HAL_ID_BUTTON_ONE)) 
                    {
                        printf("[%8lu] DEV \t > \t This was button 1 (periodic event), on pin %u\n", dev_system_time, dev_btn->pin);
                    }

                    if(dev_btn->press_duration_seconds > 5) 
                    {
                        printf("[%8lu] DEV \t > \t %s pressed for more than 5 secs. Do custom action\n", dev_system_time, BUTTON_HAL_GET_DESCRIPTION(dev_btn));
                    }

                }
                
                // ---------------------------------------------------------------------------------------------------------------------

            }

        PROCESS_END();
        }
    
    #endif  /* OAR_DEV */