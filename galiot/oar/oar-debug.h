#ifndef OAR_DEBUG_H_
#define OAR_DEBUG_H_

#include "net/ipv6/uip.h"
#include "net/ipv6/uiplib.h"
#include "net/ipv6/uip-icmp6.h"
#include "net/ipv6/uip-ds6.h"

#if ROUTING_CONF_RPL_LITE
    #include "net/routing/rpl-lite/rpl.h"
#elif ROUTING_CONF_RPL_CLASSIC
    #include "net/routing/rpl-classic/rpl.h"
#endif

#include "net/routing/routing.h"

#include <stdio.h>                  
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "sys/energest.h"
#include "net/ipv6/uip.h"

char oar_debug_ipaddr[UIPLIB_IPV6_MAX_STR_LEN];
char oar_debug_lladdr[UIPLIB_IPV6_MAX_STR_LEN];

void oar_debug_(char dash, int times);

// ==========================================================================================
// Energest /////////////////////////////////////////////////////////////////////////////////
// ==========================================================================================

#if (ENERGEST_CONF_ON)

    // static unsigned long to_seconds(uint64_t time);
    void oar_debug_energy(unsigned long int system_time);

#endif // (ENERGEST_CONF_ON)

// ==========================================================================================
// uIP TCP/IP Statistics ////////////////////////////////////////////////////////////////////
// ==========================================================================================

#if (UIP_CONF_STATISTICS)

    void oar_debug_statistics_ip(unsigned long int system_time);
    void oar_debug_statistics_icmp(unsigned long int system_time);

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    #if (UIP_TCP)

        void oar_debug_statistics_tcp(unsigned long int system_time);

    #endif // (UIP_TCP)
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    #if (UIP_UDP)

        void oar_debug_statistics_udp(unsigned long int system_time);

    #endif // (UIP_UDP)
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    void oar_debug_statistics_nd6(unsigned long int system_time);

#endif // (UIP_CONF_STATISTICS)

// ==========================================================================================
// contiki-ng Shell (get CMDs) //////////////////////////////////////////////////////////////
// ==========================================================================================

#if (ROUTING_CONF_RPL_LITE)

    void oar_debug_net_rpl_nbr(unsigned long int system_time);
    void oar_debug_net_rpl_status(unsigned long int system_time);

#endif // (ROUTING_CONF_RPL_LITE)
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void oar_debug_net_macaddr(unsigned long int system_time);

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#if (NETSTACK_CONF_WITH_IPV6)

    void oar_debug_net_ipaddr(unsigned long int system_time);
    void oar_debug_net_ip_neighbors(unsigned long int system_time);

#endif // (NETSTACK_CONF_WITH_IPV6)
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#if (MAC_CONF_WITH_TSCH)

    void oar_debug_net_tsch_status(unsigned long int system_time);

#endif // (MAC_CONF_WITH_TSCH)
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#if (NETSTACK_CONF_WITH_IPV6)

    void oar_debug_net_routes(unsigned long int system_time);

#endif // (NETSTACK_CONF_WITH_IPV6)

#endif // (OAR_DEBUG_H_)

//    [      36] DEBUG > ENERGY >                                                                              CPU: 10 
//    [      36] DEBUG > ENERGY >                                                                              LPM: 26 
//    [      36] DEBUG > ENERGY >                                                                         DEEP LPM: 0 
//    [      36] DEBUG > ENERGY >                                                                       TOTAL TIME: 36 
//    [      36] DEBUG > ENERGY >                                                                     RADIO LISTEN: 36 
//    [      36] DEBUG > ENERGY >                                                                   RADIO TRANSMIT: 0 
//    [      36] DEBUG > ENERGY >                                                                        RADIO OFF: 0 
//    ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//    [      36] DEBUG >  STATS >          (ip.recv) >                            received packets at the IP layer: 4
//    [      36] DEBUG >  STATS >          (ip.sent) >                                sent packets at the IP layer: 9
//    [      36] DEBUG >  STATS >     (ip.forwarded) >                           forwarded packets at the IP layer: 0
//    [      36] DEBUG >  STATS >          (ip.drop) >                             dropped packets at the IP layer: 0
//    [      36] DEBUG >  STATS >        (ip.vhlerr) >    packets dropped due to wrong IP version or header length: 0
//    [      36] DEBUG >  STATS >      (ip.hblenerr) >           packets dropped due to wrong IP length, high byte: 0
//    [      36] DEBUG >  STATS >      (ip.lblenerr) >            packets dropped due to wrong IP length, low byte: 0
//    [      36] DEBUG >  STATS >       (ip.fragerr) >              packets dropped because they were IP fragments: 0
//    [      36] DEBUG >  STATS >        (ip.chkerr) >                   packets dropped due to IP checksum errors: 0
//    [      36] DEBUG >  STATS >      (ip.protoerr) > packets dropped because they were neither ICMP, UDP nor TCP: 0
//
//    [      36] DEBUG >  STATS >        (icmp.recv) >                                       received ICMP packets: 4
//    [      36] DEBUG >  STATS >        (icmp.sent) >                                           sent ICMP packets: 9
//    [      36] DEBUG >  STATS >        (icmp.drop) >                                        dropped ICMP packets: 0
//    [      36] DEBUG >  STATS >     (icmp.typeerr) >                              ICMP packets with a wrong type: 0
//    [      36] DEBUG >  STATS >      (icmp.chkerr) >                            ICMP packets with a bad checksum: 0
//
//    [      36] DEBUG >  STATS >         (udp.drop) >                                        dropped UDP segments: 0
//    [      36] DEBUG >  STATS >         (udp.recv) >                                       received UDP segments: 0
//    [      36] DEBUG >  STATS >         (udp.sent) >                                           sent UDP segments: 0
//    [      36] DEBUG >  STATS >       (udp.chkerr) >                            UDP segments with a bad checksum: 0
//
//    [      36] DEBUG >  STATS >         (nd6.drop) >                                         dropped ND6 packets: 0
//    [      36] DEBUG >  STATS >         (nd6.recv) >                                         dropped ND6 packets: 0
//    [      36] DEBUG >  STATS >         (nd6.sent) >                                         dropped ND6 packets: 0
//    ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//    [      36] DEBUG >   INFO >      (cmd_rpl_nbr) >                                            RPL neighbor 1/3: fe80::212:4b00:f82:a600  266,   152 =>   418 --  3   a   (last tx 0 min ago)
//    [      36] DEBUG >   INFO >      (cmd_rpl_nbr) >                                            RPL neighbor 2/3: fe80::212:4b00:f82:da03  262,   128 =>   390 --  2   a   (last tx 0 min ago)
//    [      36] DEBUG >   INFO >      (cmd_rpl_nbr) >                                            RPL neighbor 3/3: fe80::212:4b00:f24:8385  128,   128 =>   256 --  5 rbafp (last tx 0 min ago)
//
//    [      36] DEBUG >   INFO >   (cmd_rpl_status) >                                                    Instance: 0
//    [      36] DEBUG >   INFO >   (cmd_rpl_status) >                                                         DAG: node
//    [      36] DEBUG >   INFO >   (cmd_rpl_status) >                                                         DAG: fd00::212:4b00:f24:8385, version 240
//    [      36] DEBUG >   INFO >   (cmd_rpl_status) >                                                      Prefix: fd00::/64
//    [      36] DEBUG >   INFO >   (cmd_rpl_status) >                                                         MOP: Non-storing
//    [      36] DEBUG >   INFO >   (cmd_rpl_status) >                                                          OF: MRHOF
//    [      36] DEBUG >   INFO >   (cmd_rpl_status) >                                          Hop rank increment: 128
//    [      36] DEBUG >   INFO >   (cmd_rpl_status) >                                            Default lifetime: 1800 seconds
//    [      36] DEBUG >   INFO >   (cmd_rpl_status) >                                                       State: Reachable
//    [      36] DEBUG >   INFO >   (cmd_rpl_status) >                                            Preferred parent: fe80::212:4b00:f24:8385 (last DTSN: 240)
//    [      36] DEBUG >   INFO >   (cmd_rpl_status) >                                                        Rank: 256
//    [      36] DEBUG >   INFO >   (cmd_rpl_status) >                                                 Lowest rank: 256 (1024)
//    [      36] DEBUG >   INFO >   (cmd_rpl_status) >                                                    DTSN out: 240
//    [      36] DEBUG >   INFO >   (cmd_rpl_status) >                                                DAO sequence: last sent 241, last acked 241
//    [      36] DEBUG >   INFO >   (cmd_rpl_status) >                                               Trickle timer: current 12, min 12, max 20, redundancy 0
//
//    [      37] DEBUG >   INFO >      (cmd_macaddr) >                                            Node MAC address: 0012.4b00.0f83.b601
//
//    [      37] DEBUG >   INFO >       (cmd_ipaddr) >                                         Node IPv6 addresses: fd00::212:4b00:f83:b601
//    [      37] DEBUG >   INFO >       (cmd_ipaddr) >                                         Node IPv6 addresses: fe80::212:4b00:f83:b601
//
//    [      37] DEBUG >   INFO > (cmd_ip_neighbors) >                                        Node IPv6 neighbor 1: fe80::212:4b00:f82:a600 <-> 0012.4b00.0f82.a600, router 0, state Reachable 
//    [      37] DEBUG >   INFO > (cmd_ip_neighbors) >                                        Node IPv6 neighbor 2: fe80::212:4b00:f82:da03 <-> 0012.4b00.0f82.da03, router 0, state Reachable 
//    [      37] DEBUG >   INFO > (cmd_ip_neighbors) >                                        Node IPv6 neighbor 3: fe80::212:4b00:f24:8385 <-> 0012.4b00.0f24.8385, router 0, state Reachable 
//
//    [      37] DEBUG >   INFO >       (cmd_routes) >                                               Default route: fe80::212:4b00:f24:8385 (lifetime: infinite)
//    [      37] DEBUG >   INFO >       (cmd_routes) >                                               Routing links: None