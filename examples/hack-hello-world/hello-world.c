/*
 * Copyright (c) 2006, Swedish Institute of Computer Science.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
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
 * This file is part of the Contiki operating system.
 *
 */

/**
 * \file
 *         A very simple Contiki application showing how Contiki programs look
 * \author
 *         Adam Dunkels <adam@sics.se>
 */

/*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
/*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
/*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
// DANGER DANGER DANGER DANGER DANGER DANGER DANGER DANGER DANGER DANGER DANGER
// MAXIMUM NUMBER OF NEIGHBOR IS HARDCODED, CURRENTLY SUPPORTS 4
/*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
// CHECK /os/net/rpl-neighbor.h
// CHECK /os/net/rpl-neighbor.c 
/*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
// char galiot_RPL_nbr_array_ipaddr[4][UIPLIB_IPV6_MAX_STR_LEN];
// char galiot_RPL_nbr_array_ipaddr[4][UIPLIB_IPV6_MAX_STR_LEN] = {"::", "::", "::", "::"}
/*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
/*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
/*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/






#include "contiki.h"

#include <stdio.h> /* For printf() */

/*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
/*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
/*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
#include "os/net/routing/rpl-lite/rpl-neighbor.h"

#include "net/routing/routing.h"
#include "net/ipv6/uip-ds6-nbr.h"
#include "net/ipv6/uip-ds6-route.h"
#include "net/ipv6/uip-sr.h"

#include <string.h>
/*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
/*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
/*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/


/*---------------------------------------------------------------------------*/
PROCESS(hello_world_process, "Hello world process");
AUTOSTART_PROCESSES(&hello_world_process);
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(hello_world_process, ev, data)
{
  static struct etimer timer;
  
  /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
  /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
  /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
  /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
  // this is where we DECLARE local variables
  /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
  /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
  /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
  /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
  int galiot_ipv6_nbr_count = 0;
  /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
  /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
  /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
  /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/

  static uip_ds6_nbr_t *nbr;
  
  /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
  /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
  /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
  /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
  // στο σημείο αυτό, έχοντας ήδη κάνει #include "os/net/routing/rpl-lite/rpl-neighbor.h"
  // ορίζουμε string με μέγεθος που ορίζεται στο ίδιο αρχείο.
  //
  // The maxium length of an IPv6 string, including terminating null bytes
  // fd01:0002:0003:0004:0005:0006:0007:0008 => 39 + 1 bytes */
  // #define UIPLIB_IPV6_MAX_STR_LEN 40
  //
  // έπειτα καλούμε τη συνάρτηση uiplib_ipaddr_snprint που τοποθετεί ένα αντικείμενο 
  // τύπου uip_ipaddr_t στο ζητούμενο string.
  /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
  /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
  /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
  char galiot_IPV6_uiplib_ip6addr[UIPLIB_IPV6_MAX_STR_LEN];
  uiplib_ipaddr_snprint(galiot_IPV6_uiplib_ip6addr, sizeof(galiot_IPV6_uiplib_ip6addr), rpl_get_global_address());
  /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
  /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
  /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/

  PROCESS_BEGIN();

  /* Setup a periodic timer that expires after 10 seconds. */
  etimer_set(&timer, CLOCK_SECOND * 10);

  while(1) {
    printf("Hello, world\n");

    
    printf("----------------------------------------------------------------\n");
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    // εκτυπώνουμε το string που ορίσαμε παραπάνω.
    // αργότερα θα μπορούμε να το στείλουμε σαν json.
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    printf("(galiot) >>> IPv6: own address: %s\n", galiot_IPV6_uiplib_ip6addr);   // "nbr: own state, addr "
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    for (nbr = uip_ds6_nbr_head(); nbr != NULL; nbr = uip_ds6_nbr_next(nbr)) {
      galiot_ipv6_nbr_count++;
    }
    printf("(galiot) >>> IPv6: detected neighbors: %d\n", galiot_ipv6_nbr_count);
    galiot_ipv6_nbr_count = 0; // reset the NBR count
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    // this is where we CHECK whether the galiot variables are populated
    // and print accordingly to the console
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    printf("----------------------------------------------------------------\n");
    if (galiot_RPL_populatedFlag == 0) {    // checking the galiot_populated_flag
      printf("(galiot) >>> RPL_nbr: UNPOPULATED\n");
    }
    else {
      printf("(galiot) >>> RPL_nbr: POPULATED\n");
    }
    printf("----------------------------------------------------------------\n");
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    // this is where we PRINT the galiot_RPL_nbr variables
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    printf("(galiot) >>> RPL_nbr: own state, IPv6 unique local address (ULA): %s\n", galiot_RPL_nbr_ownState_addr);
    printf("(galiot) >>> RPL_nbr: own state, DAG state: %s\n", galiot_RPL_nbr_ownState_DAGState);
    /* DAG Mode of Operation (rpl-const.h) */
    // RPL_MOP_NO_DOWNWARD_ROUTES      0
    // RPL_MOP_NON_STORING             1
    // RPL_MOP_STORING_NO_MULTICAST    2
    // RPL_MOP_STORING_MULTICAST       3
    switch (galiot_RPL_nbr_ownState_mop) {
      case 0: printf("(galiot) >>> RPL_nbr: own state, mode of operation: %u (no downward routes)\n", galiot_RPL_nbr_ownState_mop);
              break;
      case 1: printf("(galiot) >>> RPL_nbr: own state, mode of operation: %u (non-storing)\n", galiot_RPL_nbr_ownState_mop);
              break;
      case 2: printf("(galiot) >>> RPL_nbr: own state, mode of operation: %u [storing (no multicast)]\n", galiot_RPL_nbr_ownState_mop);
              break;
      case 3: printf("(galiot) >>> RPL_nbr: own state, mode of operation: %u [storing (multicast)]\n", galiot_RPL_nbr_ownState_mop);
              break;
      default: printf("(galiot) >>> RPL_nbr: own state, mode of operation: %u (UNKNOWN)\n", galiot_RPL_nbr_ownState_mop);
    }
    // Objective Code Point (OCP) (https://www.iana.org/assignments/rpl/rpl.xhtml#ocp)
    // 0	A basic Objective Function that relies only on the objects that are defined in [RFC6550].	[RFC6552]
    // 1	Minimum Rank with Hysteresis Objective Function (MRHOF) [RFC6719]
    switch (galiot_RPL_nbr_ownState_ocp) {
      case 0: printf("(galiot) >>> RPL_nbr: own state, objective code point: %u (basic)\n", galiot_RPL_nbr_ownState_ocp);
              break;
      case 1: printf("(galiot) >>> RPL_nbr: own state, objective code point: %u (MRHOF)\n", galiot_RPL_nbr_ownState_ocp);
              break;
      default: printf("(galiot) >>> RPL_nbr: own state, objective code point: %u (UNKNOWN)\n", galiot_RPL_nbr_ownState_ocp);
    }
    // The current rank
    switch (galiot_RPL_nbr_ownState_rank) {
      case 65535: printf("(galiot) >>> RPL_nbr: own state, rank: %u (UNKNOWN)\n", galiot_RPL_nbr_ownState_rank);
                  break;
      default: printf("(galiot) >>> RPL_nbr: own state, rank: %u\n", galiot_RPL_nbr_ownState_rank);
    }
    // The maximum rank (rpl-neigbor.c)
    switch (galiot_RPL_nbr_ownState_rank) {
      case 2147483647: printf("(galiot) >>> RPL_nbr: own state, max rank: %u (UNKNOWN)\n", galiot_RPL_nbr_ownState_maxRank);
           break;
      case 65535: printf("(galiot) >>> RPL_nbr: own state, max rank: %u (infinite)\n", galiot_RPL_nbr_ownState_maxRank);
           break;
      default: printf("(galiot) >>> RPL_nbr: own state, max rank: %u\n", galiot_RPL_nbr_ownState_maxRank);
    }
    // current DIO interval (rpl-types.h)
    switch (galiot_RPL_nbr_ownState_DIOInt) {
      case 65535: printf("(galiot) >>> RPL_nbr: own state, current DIO interval: %u (UNKNOWN)\n", galiot_RPL_nbr_ownState_DIOInt);
                  break;
      default: printf("(galiot) >>> RPL_nbr: own state, current DIO interval: %u\n", galiot_RPL_nbr_ownState_DIOInt);
    }
    // returns the number of nodes in the RPL neighbor table
    switch (galiot_RPL_nbr_ownState_nbrCount) {
      case 65535: printf("(galiot) >>> RPL_nbr: own state, number of nodes in the RPL neighbor table: %u (UNKNOWN)\n", galiot_RPL_nbr_ownState_nbrCount);
                  break;
      default: printf("(galiot) >>> RPL_nbr: own state, number of nodes in the RPL neighbor table: %u\n", galiot_RPL_nbr_ownState_nbrCount);
    }
    // polulation trigger
    printf("(galiot) >>> RPL_nbr: own state, RTL neighbor table population trigger: %s\n", galiot_RPL_nbr_ownState_lastTrigger);

    printf("----------------------------------------------------------------\n");
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    if (galiot_RPL_nbr_array_index == 0) 
    {
      printf("(galiot) >>> RPL_nbr: (NO NEIGHBORS FOUND, SEARCHING...)\n");
    }
    else 
    {
      for (int i = 0; i <= galiot_RPL_nbr_array_index; i++)
      {
        printf("(galiot) >>> RPL_nbr: NEIGHBOR %d / %d, IPv6 link-local address: %s\n", i+1, galiot_RPL_nbr_array_index+1, galiot_RPL_nbr_array_ipaddr[i]);
      }
      
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/

      

    } 



    printf("----------------------------------------------------------------\n");
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    // this is where we PRINT the galiot_RPL variables
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    // Get the RPL's best guess on if we are reachable via have downward route or not.
    // return 1 if we are reachable, 0 otherwise.
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    if (rpl_is_reachable() == 1) {
      printf("(galiot) >>> RPL: reachable mote\n");
    }
    else {
      printf("(galiot) >>> RPL: reachable mote\n");
    }  
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    // Tells whether we are DAG root or not
    // return 1 if we are dag root, 0 otherwise
     /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    if (rpl_dag_root_is_root() == 1) {
      printf("(galiot) >>> RPL: DAG-root mote\n");
    }
    else {
      printf("(galiot) >>> RPL: DAG-leaf mote\n");
    }
    printf("----------------------------------------------------------------\n");
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/

    /* Wait for the periodic timer to expire and then restart the timer. */
    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&timer));
    etimer_reset(&timer);
  }

  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
