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

#include "contiki.h"

#include <stdio.h> /* For printf() */





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
/*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
/*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
/*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
// #include "os/net/routing/rpl-lite/rpl-dag-root.h"
// #include "os/net/routing/rpl-lite/rpl-ext-header.h"
// #include "os/net/routing/rpl-lite/rpl-icmp6.h"
#include "os/net/routing/rpl-lite/galiot_rpl-mrhof.h"
#include "os/net/routing/rpl-lite/galiot_rpl-nbr-policy.h"
#include "os/net/routing/rpl-lite/rpl-neighbor.h"
#include "os/net/routing/rpl-lite/galiot_rpl-of0.h"
#include "os/net/routing/rpl-lite/rpl.h"
/*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
/*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
/*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
#include "net/routing/routing.h"
#include "net/ipv6/uip-ds6-nbr.h"
#include "net/ipv6/uip-ds6-route.h"
#include "net/ipv6/uip-sr.h"
/*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
/*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
/*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
#include <string.h>
/*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
/*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
/*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/





/*---------------------------------------------------------------------------*/
PROCESS(hello_world_process, "Hello world process");
AUTOSTART_PROCESSES(&hello_world_process);
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(hello_world_process, ev, data)
{
  static struct etimer timer;

  



  /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
  /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
  /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
  // this is where we DECLARE local variables
  /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
  /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
  /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
  int galiot_ipv6_nbr_count = 0;
  /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
  /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
  /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
  




  static uip_ds6_nbr_t *nbr;
  
  



  /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
  /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
  /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
  // στο σημείο αυτό, έχοντας ήδη κάνει #include "os/net/routing/rpl-lite/rpl-neighbor.h"
  // ορίζουμε string με μέγεθος που ορίζεται στο ίδιο αρχείο.
  /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
  // The maxium length of an IPv6 string, including terminating null bytes
  // fd01:0002:0003:0004:0005:0006:0007:0008 => 39 + 1 bytes */
  // #define UIPLIB_IPV6_MAX_STR_LEN 40
  /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
  // έπειτα καλούμε τη συνάρτηση uiplib_ipaddr_snprint που τοποθετεί ένα αντικείμενο 
  // τύπου uip_ipaddr_t στο ζητούμενο string.
  /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
  /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
  /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
  char galiot_IPV6_uiplib_ip6addr[UIPLIB_IPV6_MAX_STR_LEN];
  uiplib_ipaddr_snprint(galiot_IPV6_uiplib_ip6addr, sizeof(galiot_IPV6_uiplib_ip6addr), rpl_get_global_address());
  /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
  /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
  /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/





  PROCESS_BEGIN();

  /* Setup a periodic timer that expires after 10 seconds. */
  etimer_set(&timer, CLOCK_SECOND * 10);

  while(1) {
    printf("Hello, world\n");
    




    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    //printf("\n");
    //printf("<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>\n");
    //printf("\n");
    printf("(galiot) >>> SYSTEM TIME: %lu\n", clock_seconds());
    //printf("\n");
    //printf("<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>\n");
    //printf("\n");
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    




    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    #ifdef GALIOT_FUNCTIONALITY
      printf("(galiot) >>> GALIOT FUNCTIONALITY: ENABLED\n");
      printf("(galiot) >>> GALIOT SNAPSHOT COUNT: %d\n", GALIOT_SNAPSHOT_COUNT);
      printf("----------------------------------------------------------------\n");
      printf("(galiot) >>> GALIOT RPL NEIGHBOR_ARRY MAXIMUM SIZE: %d\n", GALIOT_RPL_NEIGHBOR_ARRY);

      //printf("\n");
      //printf("================================================================================================================================\n");
      //printf("\n");
    #else
      printf(">>> GALIOT FUNCTIONALITY: DISABLED\n");
      //printf("\n");
      //printf("================================================================================================================================\n");
      //printf("\n");
    #endif /* GALIOT_FUNCTIONALITY */
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/


















    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    #ifdef GALIOT_FUNCTIONALITY
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      // /os/net/routing/rpl-lite/rpl-dag-root.c
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/

      
      //printf("\n");
      printf("(galiot) >>> rpl-dag-root\n");
      //printf("\n");

      

      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      // rpl_dag_root_print_links_INFO_links_ON
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #if GALIOT_SNAP_RPL_DAG_ROOT_PRINT_LINKS
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/

      if (galiot_snap_flag_rpl_dag_root_print_links_INFO_links_ON == 0)
      {
        //printf("\n");
        //printf("\n");
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        printf("(galiot) >>> [%10lu] >>> rpl_dag_root >>> rpl_dag_root_print_links (INFO): OFF\n", clock_seconds());
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        //printf("\n");
      }
      else
      {
        printf("(galiot) >>> [%10lu] >>> rpl_dag_root >>> rpl_dag_root_print_links (INFO): ON\n", clock_seconds());
        printf("(galiot) >>> [%10lu] >>> rpl_dag_root >>> rpl_dag_root_print_links (INFO): SNAPS: %d\n", clock_seconds(), galiot_snap_count_rpl_dag_root_print_links_INFO_links_ON);
        
        if (galiot_snap_flag_countOverflow_rpl_dag_root_print_links_INFO_links_ON == 1)
        {
          printf("(galiot) >>> [%10lu] >>> rpl_dag_root >>> rpl_dag_root_print_links (INFO): OVERFLOW\n", clock_seconds());
        }
        
        printf("----------------------------------------------------------------\n");
      }
        
      for (int i = 0; i < GALIOT_SNAPSHOT_COUNT; i++)
      {
        printf("(galiot) >>> [%10lu] >>> rpl_dag_root >>> rpl_dag_root_print_links (INFO) >>> [%10lu] LAST_SNAP[%d]\n", clock_seconds(), galiot_snap_rpl_dag_root_print_links_INFO_links_ON.system_time[i], i);
        printf("(galiot) >>> [%10lu] >>> rpl_dag_root >>> rpl_dag_root_print_links (INFO): ROOTING LINKS: %d\n", clock_seconds(), galiot_snap_rpl_dag_root_print_links_INFO_links_ON.routing_links_count_int[i]);
        printf("(galiot) >>> [%10lu] >>> rpl_dag_root >>> rpl_dag_root_print_links (INFO): TOTAL LINKS: %s\n", clock_seconds(), galiot_snap_rpl_dag_root_print_links_INFO_links_ON.total_links_str[i]);
        printf("----------------------------------------------------------------\n");
        
        for (int k = 0; k < galiot_snap_rpl_dag_root_print_links_INFO_links_ON.populated_links_int[i]; k++)
        {
          printf("(galiot) >>> [%10lu] >>> rpl_dag_root >>> rpl_dag_root_print_links (INFO): LINK %d / %d : %s\n", clock_seconds(), k, galiot_snap_rpl_dag_root_print_links_INFO_links_ON.populated_links_int[i], galiot_snap_rpl_dag_root_print_links_INFO_links_ON.link_str[i][k]);
          printf("----------------------------------------------------------------\n");
        }
        
      }
      
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #endif /* GALIOT_SNAP_RPL_DAG_ROOT_PRINT_LINKS */
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/



      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      // rpl_dag_root_print_links_INFO_links_OFF
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #if GALIOT_SNAP_RPL_DAG_ROOT_PRINT_LINKS
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/

      if (galiot_snap_flag_rpl_dag_root_print_links_INFO_links_OFF == 0)
      {
        //printf("\n");
        //printf("\n");
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        printf("(galiot) >>> [%10lu] >>> rpl_dag_root >>> rpl_dag_root_print_links (INFO): OFF\n", clock_seconds());
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        //printf("\n");
      }
      else
      {
        printf("(galiot) >>> [%10lu] >>> rpl_dag_root >>> rpl_dag_root_print_links (INFO): ON\n", clock_seconds());
        printf("(galiot) >>> [%10lu] >>> rpl_dag_root >>> rpl_dag_root_print_links (INFO): SNAPS: %d\n", clock_seconds(), galiot_snap_count_rpl_dag_root_print_links_INFO_links_OFF);
        
        if (galiot_snap_flag_countOverflow_rpl_dag_root_print_links_INFO_links_OFF == 1)
        {
          printf("(galiot) >>> [%10lu] >>> rpl_dag_root >>> rpl_dag_root_print_links (INFO): OVERFLOW\n", clock_seconds());
        }
        
        printf("----------------------------------------------------------------\n");
      }
        
      for (int i = 0; i < GALIOT_SNAPSHOT_COUNT; i++)
      {
        printf("(galiot) >>> [%10lu] >>> rpl_dag_root >>> rpl_dag_root_print_links (INFO) >>> [%10lu] LAST_SNAP[%d]\n", clock_seconds(), galiot_snap_rpl_dag_root_print_links_INFO_links_OFF.system_time[i], i);
        printf("(galiot) >>> [%10lu] >>> rpl_dag_root >>> rpl_dag_root_print_links (INFO): NO ROUTING LINKS\n", clock_seconds());
        printf("----------------------------------------------------------------\n");
        
      }
      
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #endif /* GALIOT_SNAP_RPL_DAG_ROOT_PRINT_LINKS */
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/





      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      // rpl_dag_root_set_global_address_INFO
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #if GALIOT_SNAP_RPL_DAG_ROOT_SET_GLOBAL_ADDRESS
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/

      if (galiot_snap_flag_rpl_dag_root_set_global_address_INFO == 0)
      {
        //printf("\n");
        //printf("\n");
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        printf("(galiot) >>> [%10lu] >>> rpl_dag_root >>> set_global_address (INFO): OFF\n", clock_seconds());
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        //printf("\n");
      }
      else
      {
        printf("(galiot) >>> [%10lu] >>> rpl_dag_root >>> set_global_address (INFO): ON\n", clock_seconds());
        printf("(galiot) >>> [%10lu] >>> rpl_dag_root >>> set_global_address (INFO): SNAPS: %d\n", clock_seconds(), galiot_snap_count_rpl_dag_root_set_global_address_INFO);
        
        if (galiot_snap_flag_countOverflow_rpl_dag_root_set_global_address_INFO == 1)
        {
          printf("(galiot) >>> [%10lu] >>> rpl_dag_root >>> set_global_address (INFO): OVERFLOW\n", clock_seconds());
        }
        
        printf("----------------------------------------------------------------\n");
      }
        
      for (int i = 0; i < GALIOT_SNAPSHOT_COUNT; i++)
      {
        printf("(galiot) >>> [%10lu] >>> rpl_dag_root >>> set_global_address (INFO) >>> [%10lu] LAST_SNAP[%d]\n", clock_seconds(), galiot_snap_rpl_dag_root_set_global_address_INFO.system_time[i], i);
        printf("(galiot) >>> [%10lu] >>> rpl_dag_root >>> set_global_address (INFO): NO ROUTING LINKS\n", clock_seconds());
        printf("----------------------------------------------------------------\n");

        for (int k = 0; k < galiot_snap_rpl_dag_root_set_global_address_INFO.populated_addresses_int[i]; k++)
        {
          printf("(galiot) >>> [%10lu] >>> rpl_dag_root >>> rpl_dag_root_print_links (INFO): IPv6 ADDRESS %d / %d : %s\n", clock_seconds(), k, galiot_snap_rpl_dag_root_set_global_address_INFO.populated_addresses_int[i], galiot_snap_rpl_dag_root_set_global_address_INFO.address_6ADDR[i][k]);
          printf("----------------------------------------------------------------\n");
        }
        
      }
      
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #endif /* GALIOT_SNAP_RPL_DAG_ROOT_SET_GLOBAL_ADDRESS */
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/



      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      // rpl_dag_root_start_INFO
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #if GALIOT_SNAP_RPL_DAG_ROOT_START
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/

      if (galiot_snap_flag_rpl_dag_root_start_INFO == 0)
      {
        //printf("\n");
        //printf("\n");
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        printf("(galiot) >>> [%10lu] >>> rpl_dag_root >>> rpl_dag_root_start (INFO): OFF\n", clock_seconds());
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        //printf("\n");
      }
      else
      {
        printf("(galiot) >>> [%10lu] >>> rpl_dag_root >>> rpl_dag_root_start (INFO): ON\n", clock_seconds());
        printf("(galiot) >>> [%10lu] >>> rpl_dag_root >>> rpl_dag_root_start (INFO): SNAPS: %d\n", clock_seconds(), galiot_snap_count_rpl_dag_root_start_INFO);
        
        if (galiot_snap_flag_countOverflow_rpl_dag_root_start_INFO == 1)
        {
          printf("(galiot) >>> [%10lu] >>> rpl_dag_root >>> rpl_dag_root_start (INFO): OVERFLOW\n", clock_seconds());
        }
        
        printf("----------------------------------------------------------------\n");
      }
        
      for (int i = 0; i < GALIOT_SNAPSHOT_COUNT; i++)
      {
        printf("(galiot) >>> [%10lu] >>> rpl_dag_root >>> rpl_dag_root_start (INFO) >>> [%10lu] LAST_SNAP[%d]\n", clock_seconds(), galiot_snap_rpl_dag_root_start_INFO.system_time[i], i);
        printf("(galiot) >>> [%10lu] >>> rpl_dag_root >>> rpl_dag_root_start (INFO): CREATED A NEW RPL DAG\n", clock_seconds());
        printf("----------------------------------------------------------------\n");
        
      }
      
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #endif /* GALIOT_SNAP_RPL_DAG_ROOT_START */
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/



      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      // rpl_dag_root_start_ERR
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #if GALIOT_SNAP_RPL_DAG_ROOT_START
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/

      if (galiot_snap_flag_rpl_dag_root_start_ERR == 0)
      {
        //printf("\n");
        //printf("\n");
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        printf("(galiot) >>> [%10lu] >>> rpl_dag_root >>> rpl_dag_root_start (ERR): OFF\n", clock_seconds());
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        //printf("\n");
      }
      else
      {
        printf("(galiot) >>> [%10lu] >>> rpl_dag_root >>> rpl_dag_root_start (ERR): ON\n", clock_seconds());
        printf("(galiot) >>> [%10lu] >>> rpl_dag_root >>> rpl_dag_root_start (ERR): SNAPS: %d\n", clock_seconds(), galiot_snap_count_rpl_dag_root_start_ERR);
        
        if (galiot_snap_flag_countOverflow_rpl_dag_root_start_ERR == 1)
        {
          printf("(galiot) >>> [%10lu] >>> rpl_dag_root >>> rpl_dag_root_start (ERR): OVERFLOW\n", clock_seconds());
        }
        
        printf("----------------------------------------------------------------\n");
      }
        
      for (int i = 0; i < GALIOT_SNAPSHOT_COUNT; i++)
      {
        printf("(galiot) >>> [%10lu] >>> rpl_dag_root >>> rpl_dag_root_start (ERR) >>> [%10lu] LAST_SNAP[%d]\n", clock_seconds(), galiot_snap_rpl_dag_root_start_ERR.system_time[i], i);
        printf("(galiot) >>> [%10lu] >>> rpl_dag_root >>> rpl_dag_root_start (ERR): FAILED TO CREATE A NEW RPL DAG\n", clock_seconds());
        printf("----------------------------------------------------------------\n");
        
      }
      
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #endif /* GALIOT_SNAP_RPL_DAG_ROOT_START */
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/



      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    #endif /* GALIOT_FUNCTIONALITY */
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/













































    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    #ifdef GALIOT_FUNCTIONALITY
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      // /os/net/routing/rpl-lite/rpl-dag.c
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/

      
      //printf("\n");
      printf("(galiot) >>> rpl-dag\n");
      //printf("\n");

      

      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      // rpl_dag_leave_INFO
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #if GALIOT_SNAP_RPL_DAG_LEAVE
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/

      if (galiot_snap_flag_rpl_dag_leave_INFO == 0)
      {
        //printf("\n");
        //printf("\n");
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        printf("(galiot) >>> [%10lu] >>> rpl_dag >>> rpl_dag_leave (INFO): OFF\n", clock_seconds());
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        //printf("\n");
      }
      else
      {
        printf("(galiot) >>> [%10lu] >>> rpl_dag >>> rpl_dag_leave (INFO): ON\n", clock_seconds());
        printf("(galiot) >>> [%10lu] >>> rpl_dag >>> rpl_dag_leave (INFO): SNAPS: %d\n", clock_seconds(), galiot_snap_count_rpl_dag_leave_INFO);
        
        if (galiot_snap_flag_countOverflow_rpl_dag_leave_INFO == 1)
        {
          printf("(galiot) >>> [%10lu] >>> rpl_dag >>> rpl_dag_leave (INFO): OVERFLOW\n", clock_seconds());
        }
        
        printf("----------------------------------------------------------------\n");
      }
        
      for (int i = 0; i < GALIOT_SNAPSHOT_COUNT; i++)
      {
        printf("(galiot) >>> [%10lu] >>> rpl_dag >>> rpl_dag_leave (INFO) >>> [%10lu] LAST_SNAP[%d]\n", clock_seconds(), galiot_snap_rpl_dag_leave_INFO.system_time[i], i);
        printf("(galiot) >>> [%10lu] >>> rpl_dag >>> rpl_dag_leave (INFO): LEAVING DAG: %s\n", clock_seconds(), galiot_snap_rpl_dag_leave_INFO.dag_id_6ADDR[i]);
        printf("(galiot) >>> [%10lu] >>> rpl_dag >>> rpl_dag_leave (INFO): INSTANCE: %u\n", clock_seconds(), galiot_snap_rpl_dag_leave_INFO.instance_id[i]);
        printf("----------------------------------------------------------------\n");
        
      }
      
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #endif /* GALIOT_SNAP_RPL_DAG_LEAVE */
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/



      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      // rpl_dag_periodic_WARN_expired
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #if GALIOT_SNAP_RPL_DAG_PERIODIC
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/

      if (galiot_snap_flag_rpl_dag_periodic_WARN_expired == 0)
      {
        //printf("\n");
        //printf("\n");
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        printf("(galiot) >>> [%10lu] >>> rpl_dag >>> rpl_dag_periodic (WARN): OFF\n", clock_seconds());
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        //printf("\n");
      }
      else
      {
        printf("(galiot) >>> [%10lu] >>> rpl_dag >>> rpl_dag_periodic (WARN): ON\n", clock_seconds());
        printf("(galiot) >>> [%10lu] >>> rpl_dag >>> rpl_dag_periodic (WARN): SNAPS: %d\n", clock_seconds(), galiot_snap_count_rpl_dag_periodic_WARN_expired);
        
        if (galiot_snap_flag_countOverflow_rpl_dag_periodic_WARN_expired == 1)
        {
          printf("(galiot) >>> [%10lu] >>> rpl_dag >>> rpl_dag_periodic (WARN): OVERFLOW\n", clock_seconds());
        }
        
        printf("----------------------------------------------------------------\n");
      }
        
      for (int i = 0; i < GALIOT_SNAPSHOT_COUNT; i++)
      {
        printf("(galiot) >>> [%10lu] >>> rpl_dag >>> rpl_dag_periodic (WARN) >>> [%10lu] LAST_SNAP[%d]\n", clock_seconds(), galiot_snap_rpl_dag_periodic_WARN_expired.system_time[i], i);
        printf("(galiot) >>> [%10lu] >>> rpl_dag >>> rpl_dag_periodic (WARN): DAG EXPIRED, POISON AND LEAVE\n", clock_seconds());
        printf("----------------------------------------------------------------\n");
        
      }
      
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #endif /* GALIOT_SNAP_RPL_DAG_PERIODIC */
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/



      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      // rpl_dag_periodic_WARN_expiring
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #if GALIOT_SNAP_RPL_DAG_PERIODIC
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/

      if (galiot_snap_flag_rpl_dag_periodic_WARN_expiring == 0)
      {
        //printf("\n");
        //printf("\n");
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        printf("(galiot) >>> [%10lu] >>> rpl_dag >>> rpl_dag_periodic (WARN): OFF\n", clock_seconds());
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        //printf("\n");
      }
      else
      {
        printf("(galiot) >>> [%10lu] >>> rpl_dag >>> rpl_dag_periodic (WARN): ON\n", clock_seconds());
        printf("(galiot) >>> [%10lu] >>> rpl_dag >>> rpl_dag_periodic (WARN): SNAPS: %d\n", clock_seconds(), galiot_snap_count_rpl_dag_periodic_WARN_expiring);
        
        if (galiot_snap_flag_countOverflow_rpl_dag_periodic_WARN_expiring == 1)
        {
          printf("(galiot) >>> [%10lu] >>> rpl_dag >>> rpl_dag_periodic (WARN): OVERFLOW\n", clock_seconds());
        }
        
        printf("----------------------------------------------------------------\n");
      }
        
      for (int i = 0; i < GALIOT_SNAPSHOT_COUNT; i++)
      {
        printf("(galiot) >>> [%10lu] >>> rpl_dag >>> rpl_dag_periodic (WARN) >>> [%10lu] LAST_SNAP[%d]\n", clock_seconds(), galiot_snap_rpl_dag_periodic_WARN_expiring.system_time[i], i);
        printf("(galiot) >>> [%10lu] >>> rpl_dag >>> rpl_dag_periodic (WARN): SEND DIS TO PREFERRED PARENT, DAG EXPIRING IN (SEC) %lu\n", clock_seconds(), galiot_snap_rpl_dag_periodic_WARN_expiring.dag_lifetime[i]);
        printf("----------------------------------------------------------------\n");
      }
      
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #endif /* GALIOT_SNAP_RPL_DAG_PERIODIC */
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/



      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      // rpl_dag_refresh_routes_WARN
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #if GALIOT_SNAP_RPL_DAG_REFRESH_ROUTES
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/

      if (galiot_snap_flag_rpl_dag_refresh_routes_WARN == 0)
      {
        //printf("\n");
        //printf("\n");
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        printf("(galiot) >>> [%10lu] >>> rpl_dag >>> rpl_refresh_routes (WARN): OFF\n", clock_seconds());
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        //printf("\n");
      }
      else
      {
        printf("(galiot) >>> [%10lu] >>> rpl_dag >>> rpl_refresh_routes (WARN): ON\n", clock_seconds());
        printf("(galiot) >>> [%10lu] >>> rpl_dag >>> rpl_refresh_routes (WARN): SNAPS: %d\n", clock_seconds(), galiot_snap_count_rpl_dag_refresh_routes_WARN);
        
        if (galiot_snap_flag_countOverflow_rpl_dag_refresh_routes_WARN == 1)
        {
          printf("(galiot) >>> [%10lu] >>> rpl_dag >>> rpl_refresh_routes (WARN): OVERFLOW\n", clock_seconds());
        }
        
        printf("----------------------------------------------------------------\n");
      }
        
      for (int i = 0; i < GALIOT_SNAPSHOT_COUNT; i++)
      {
        printf("(galiot) >>> [%10lu] >>> rpl_dag >>> rpl_refresh_routes (WARN) >>> [%10lu] LAST_SNAP[%d]\n", clock_seconds(), galiot_snap_rpl_dag_refresh_routes_WARN.system_time[i], i);
        printf("(galiot) >>> [%10lu] >>> rpl_dag >>> rpl_refresh_routes (WARN): INCREMENTED DTSN, %s\n", clock_seconds(), galiot_snap_rpl_dag_refresh_routes_WARN.str[i]);
         printf("(galiot) >>> [%10lu] >>> rpl_dag >>> rpl_refresh_routes (WARN): CURRENT: %u\n", clock_seconds(), galiot_snap_rpl_dag_refresh_routes_WARN.dtsn_out[i]);
        printf("----------------------------------------------------------------\n");
      }
      
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #endif /* GALIOT_SNAP_RPL_DAG_REFRESH_ROUTES */
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/



      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      // rpl_dag_global_repair_WARN
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #if GALIOT_SNAP_RPL_DAG_GLOBAL_REPAIR
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/

      if (galiot_snap_flag_rpl_dag_global_repair_WARN == 0)
      {
        //printf("\n");
        //printf("\n");
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        printf("(galiot) >>> [%10lu] >>> rpl_dag >>> rpl_global_repair (WARN): OFF\n", clock_seconds());
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        //printf("\n");
      }
      else
      {
        printf("(galiot) >>> [%10lu] >>> rpl_dag >>> rpl_global_repair (WARN): ON\n", clock_seconds());
        printf("(galiot) >>> [%10lu] >>> rpl_dag >>> rpl_global_repair (WARN): SNAPS: %d\n", clock_seconds(), galiot_snap_count_rpl_dag_global_repair_WARN);
        
        if (galiot_snap_flag_countOverflow_rpl_dag_global_repair_WARN == 1)
        {
          printf("(galiot) >>> [%10lu] >>> rpl_dag >>> rpl_global_repair (WARN): OVERFLOW\n", clock_seconds());
        }
        
        printf("----------------------------------------------------------------\n");
      }
        
      for (int i = 0; i < GALIOT_SNAPSHOT_COUNT; i++)
      {
        printf("(galiot) >>> [%10lu] >>> rpl_dag >>> rpl_global_repair (WARN) >>> [%10lu] LAST_SNAP[%d]\n", clock_seconds(), galiot_snap_rpl_dag_global_repair_WARN.system_time[i], i);
        printf("(galiot) >>> [%10lu] >>> rpl_dag >>> rpl_global_repair (WARN): INITIATING GLOBAL REPAIR, %s\n", clock_seconds(), galiot_snap_rpl_dag_global_repair_WARN.str[i]);
        printf("(galiot) >>> [%10lu] >>> rpl_dag >>> rpl_global_repair (WARN): VERSION: %u\n", clock_seconds(), galiot_snap_rpl_dag_global_repair_WARN.dag_version[i]);
        printf("(galiot) >>> [%10lu] >>> rpl_dag >>> rpl_global_repair (WARN): RANK: %u\n", clock_seconds(), galiot_snap_rpl_dag_global_repair_WARN.dag_rank[i]);
        printf("----------------------------------------------------------------\n");
      }
      
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #endif /* GALIOT_SNAP_RPL_DAG_GLOBAL_REPAIR */
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/



      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      // rpl_dag_global_repair_non_root_WARN
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #if GALIOT_SNAP_RPL_DAG_GLOBAL_REPAIR_NON_ROOT
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/

      if (galiot_snap_flag_rpl_dag_global_repair_non_root_WARN == 0)
      {
        //printf("\n");
        //printf("\n");
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        printf("(galiot) >>> [%10lu] >>> rpl_dag >>> global_repair_non_root (WARN): OFF\n", clock_seconds());
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        //printf("\n");
      }
      else
      {
        printf("(galiot) >>> [%10lu] >>> rpl_dag >>> global_repair_non_root (WARN): ON\n", clock_seconds());
        printf("(galiot) >>> [%10lu] >>> rpl_dag >>> global_repair_non_root (WARN): SNAPS: %d\n", clock_seconds(), galiot_snap_count_rpl_dag_global_repair_non_root_WARN);
        
        if (galiot_snap_flag_countOverflow_rpl_dag_global_repair_non_root_WARN == 1)
        {
          printf("(galiot) >>> [%10lu] >>> rpl_dag >>> global_repair_non_root (WARN): OVERFLOW\n", clock_seconds());
        }
        
        printf("----------------------------------------------------------------\n");
      }
        
      for (int i = 0; i < GALIOT_SNAPSHOT_COUNT; i++)
      {
        printf("(galiot) >>> [%10lu] >>> rpl_dag >>> global_repair_non_root (WARN) >>> [%10lu] LAST_SNAP[%d]\n", clock_seconds(), galiot_snap_rpl_dag_global_repair_non_root_WARN.system_time[i], i);
        printf("(galiot) >>> [%10lu] >>> rpl_dag >>> global_repair_non_root (WARN): PARTICIPATING IN GLOBAL REPAIR\n", clock_seconds());
        printf("(galiot) >>> [%10lu] >>> rpl_dag >>> global_repair_non_root (WARN): VERSION: %u\n", clock_seconds(), galiot_snap_rpl_dag_global_repair_non_root_WARN.dag_version[i]);
        printf("(galiot) >>> [%10lu] >>> rpl_dag >>> global_repair_non_root (WARN): RANK: %u\n", clock_seconds(), galiot_snap_rpl_dag_global_repair_non_root_WARN.dag_rank[i]);
        printf("----------------------------------------------------------------\n");
      }
      
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #endif /* GALIOT_SNAP_RPL_DAG_GLOBAL_REPAIR_NON_ROOT */
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/



      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      // rpl_dag_local_repair_WARN
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #if GALIOT_SNAP_RPL_DAG_LOCAL_REPAIR
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/

      if (galiot_snap_flag_rpl_dag_global_repair_non_root_WARN == 0)
      {
        //printf("\n");
        //printf("\n");
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        printf("(galiot) >>> [%10lu] >>> rpl_dag >>> rpl_local_repair (WARN): OFF\n", clock_seconds());
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        //printf("\n");
      }
      else
      {
        printf("(galiot) >>> [%10lu] >>> rpl_dag >>> rpl_local_repair (WARN): ON\n", clock_seconds());
        printf("(galiot) >>> [%10lu] >>> rpl_dag >>> rpl_local_repair (WARN): SNAPS: %d\n", clock_seconds(), galiot_snap_count_rpl_dag_local_repair_WARN);
        
        if (galiot_snap_flag_countOverflow_rpl_dag_local_repair_WARN == 1)
        {
          printf("(galiot) >>> [%10lu] >>> rpl_dag >>> rpl_local_repair (WARN): OVERFLOW\n", clock_seconds());
        }
        
        printf("----------------------------------------------------------------\n");
      }
        
      for (int i = 0; i < GALIOT_SNAPSHOT_COUNT; i++)
      {
        printf("(galiot) >>> [%10lu] >>> rpl_dag >>> rpl_local_repair (WARN) >>> [%10lu] LAST_SNAP[%d]\n", clock_seconds(), galiot_snap_rpl_dag_local_repair_WARN.system_time[i], i);
        printf("(galiot) >>> [%10lu] >>> rpl_dag >>> rpl_local_repair (WARN): LOCAL REPAIR: %s\n", clock_seconds(), galiot_snap_rpl_dag_local_repair_WARN.str[i]);
        printf("----------------------------------------------------------------\n");
      }
      
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #endif /* GALIOT_SNAP_RPL_DAG_GLOBAL_REPAIR_NON_ROOT */
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/



      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      // rpl_dag_update_state_WARN_poison_routes
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #if GALIOT_SNAP_RPL_DAG_UPDATE_STATE
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/

      if (galiot_snap_flag_rpl_dag_update_state_WARN_poison_routes == 0)
      {
        //printf("\n");
        //printf("\n");
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        printf("(galiot) >>> [%10lu] >>> rpl_dag >>> rpl_dag_update_state (WARN): OFF\n", clock_seconds());
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        //printf("\n");
      }
      else
      {
        printf("(galiot) >>> [%10lu] >>> rpl_dag >>> rpl_dag_update_state (WARN): ON\n", clock_seconds());
        printf("(galiot) >>> [%10lu] >>> rpl_dag >>> rpl_dag_update_state (WARN): SNAPS: %d\n", clock_seconds(), galiot_snap_count_rpl_dag_update_state_WARN_poison_routes);
        
        if (galiot_snap_flag_countOverflow_rpl_dag_update_state_WARN_poison_routes == 1)
        {
          printf("(galiot) >>> [%10lu] >>> rpl_dag >>> rpl_dag_update_state (WARN): OVERFLOW\n", clock_seconds());
        }
        
        printf("----------------------------------------------------------------\n");
      }
        
      for (int i = 0; i < GALIOT_SNAPSHOT_COUNT; i++)
      {
        printf("(galiot) >>> [%10lu] >>> rpl_dag >>> rpl_dag_update_state (WARN) >>> [%10lu] LAST_SNAP[%d]\n", clock_seconds(), galiot_snap_rpl_dag_update_state_WARN_poison_routes.system_time[i], i);
        printf("(galiot) >>> [%10lu] >>> rpl_dag >>> rpl_dag_update_state (WARN): POISONING AND LEAVING AFTER A DELAY\n", clock_seconds());
        printf("----------------------------------------------------------------\n");
      }
      
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #endif /* GALIOT_SNAP_RPL_DAG_UPDATE_STATE */
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/



      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      // rpl_dag_update_state_WARN_significant_rank_update
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #if GALIOT_SNAP_RPL_DAG_UPDATE_STATE
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/

      if (galiot_snap_flag_rpl_dag_update_state_WARN_significant_rank_update == 0)
      {
        //printf("\n");
        //printf("\n");
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        printf("(galiot) >>> [%10lu] >>> rpl_dag >>> rpl_dag_update_state (WARN): OFF\n", clock_seconds());
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        //printf("\n");
      }
      else
      {
        printf("(galiot) >>> [%10lu] >>> rpl_dag >>> rpl_dag_update_state (WARN): ON\n", clock_seconds());
        printf("(galiot) >>> [%10lu] >>> rpl_dag >>> rpl_dag_update_state (WARN): SNAPS: %d\n", clock_seconds(), galiot_snap_count_rpl_dag_update_state_WARN_significant_rank_update);
        
        if (galiot_snap_flag_countOverflow_rpl_dag_update_state_WARN_significant_rank_update == 1)
        {
          printf("(galiot) >>> [%10lu] >>> rpl_dag >>> rpl_dag_update_state (WARN): OVERFLOW\n", clock_seconds());
        }
        
        printf("----------------------------------------------------------------\n");
      }
        
      for (int i = 0; i < GALIOT_SNAPSHOT_COUNT; i++)
      {
        printf("(galiot) >>> [%10lu] >>> rpl_dag >>> rpl_dag_update_state (WARN) >>> [%10lu] LAST_SNAP[%d]\n", clock_seconds(), galiot_snap_rpl_dag_update_state_WARN_significant_rank_update.system_time[i], i);
        printf("(galiot) >>> [%10lu] >>> rpl_dag >>> rpl_dag_update_state (WARN): SIGNIFICANT RANK UPDATE, %u --->\n", clock_seconds(), galiot_snap_rpl_dag_update_state_WARN_significant_rank_update.last_advertised_rank[i]);
        printf("(galiot) >>> [%10lu] >>> rpl_dag >>> rpl_dag_update_state (WARN): SIGNIFICANT RANK UPDATE, ---> %u\n", clock_seconds(), galiot_snap_rpl_dag_update_state_WARN_significant_rank_update.rank[i]);
        printf("----------------------------------------------------------------\n");
      }
      
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #endif /* GALIOT_SNAP_RPL_DAG_UPDATE_STATE */
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/




      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      // rpl_dag_update_state_WARN_found_parent
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #if GALIOT_SNAP_RPL_DAG_UPDATE_STATE
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/

      if (galiot_snap_flag_rpl_dag_update_state_WARN_found_parent == 0)
      {
        //printf("\n");
        //printf("\n");
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        printf("(galiot) >>> [%10lu] >>> rpl_dag >>> rpl_dag_update_state (WARN): OFF\n", clock_seconds());
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        //printf("\n");
      }
      else
      {
        printf("(galiot) >>> [%10lu] >>> rpl_dag >>> rpl_dag_update_state (WARN): ON\n", clock_seconds());
        printf("(galiot) >>> [%10lu] >>> rpl_dag >>> rpl_dag_update_state (WARN): SNAPS: %d\n", clock_seconds(), galiot_snap_count_rpl_dag_update_state_WARN_found_parent);
        
        if (galiot_snap_flag_countOverflow_rpl_dag_update_state_WARN_found_parent == 1)
        {
          printf("(galiot) >>> [%10lu] >>> rpl_dag >>> rpl_dag_update_state (WARN): OVERFLOW\n", clock_seconds());
        }
        
        printf("----------------------------------------------------------------\n");
      }
        
      for (int i = 0; i < GALIOT_SNAPSHOT_COUNT; i++)
      {
        printf("(galiot) >>> [%10lu] >>> rpl_dag >>> rpl_dag_update_state (WARN) >>> [%10lu] LAST_SNAP[%d]\n", clock_seconds(), galiot_snap_rpl_dag_update_state_WARN_found_parent.system_time[i], i);
        printf("(galiot) >>> [%10lu] >>> rpl_dag >>> rpl_dag_update_state (WARN): FOUND PARENT: %s\n", clock_seconds(), galiot_snap_rpl_dag_update_state_WARN_found_parent.preferred_parent_6ADDR[i]);
        printf("(galiot) >>> [%10lu] >>> rpl_dag >>> rpl_dag_update_state (WARN): STAYING IN DAG\n", clock_seconds());
        printf("----------------------------------------------------------------\n");
      }
      
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #endif /* GALIOT_SNAP_RPL_DAG_UPDATE_STATE */
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/



      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      // rpl_dag_update_state_WARN_no_parent
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #if GALIOT_SNAP_RPL_DAG_UPDATE_STATE
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/

      if (galiot_snap_flag_rpl_dag_update_state_WARN_no_parent == 0)
      {
        //printf("\n");
        //printf("\n");
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        printf("(galiot) >>> [%10lu] >>> rpl_dag >>> rpl_dag_update_state (WARN): OFF\n", clock_seconds());
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        //printf("\n");
      }
      else
      {
        printf("(galiot) >>> [%10lu] >>> rpl_dag >>> rpl_dag_update_state (WARN): ON\n", clock_seconds());
        printf("(galiot) >>> [%10lu] >>> rpl_dag >>> rpl_dag_update_state (WARN): SNAPS: %d\n", clock_seconds(), galiot_snap_count_rpl_dag_update_state_WARN_no_parent);
        
        if (galiot_snap_flag_countOverflow_rpl_dag_update_state_WARN_no_parent == 1)
        {
          printf("(galiot) >>> [%10lu] >>> rpl_dag >>> rpl_dag_update_state (WARN): OVERFLOW\n", clock_seconds());
        }
        
        printf("----------------------------------------------------------------\n");
      }
        
      for (int i = 0; i < GALIOT_SNAPSHOT_COUNT; i++)
      {
        printf("(galiot) >>> [%10lu] >>> rpl_dag >>> rpl_dag_update_state (WARN) >>> [%10lu] LAST_SNAP[%d]\n", clock_seconds(), galiot_snap_rpl_dag_update_state_WARN_no_parent.system_time[i], i);
        printf("(galiot) >>> [%10lu] >>> rpl_dag >>> rpl_dag_update_state (WARN): NO PARENT, SCHEDULING PERIODIC DIS, WILL LEAVE IF NO PARENT IS FOUND\n", clock_seconds());
        printf("----------------------------------------------------------------\n");
      }
      
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #endif /* GALIOT_SNAP_RPL_DAG_UPDATE_STATE */
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/




      




      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    #endif /* GALIOT_FUNCTIONALITY */
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/





















































    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    #ifdef GALIOT_FUNCTIONALITY
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      // /os/net/routing/rpl-lite/rpl-ext_header.c
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/

      
      //printf("\n");
      printf("(galiot) >>> rpl-ext-header\n");
      //printf("\n");

      

      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      // rpl_ext_header_srh_get_next_hop_DBG
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #if GALIOT_SNAP_RPL_EXT_HEADER_SRH_GET_NEXT_HOP
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/

      if (galiot_snap_flag_rpl_ext_header_srh_get_next_hop_DBG == 0)
      {
        //printf("\n");
        //printf("\n");
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> rpl_ext_header_srh_get_next_hop (DBG): OFF\n", clock_seconds());
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        //printf("\n");
      }
      else
      {
        printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> rpl_ext_header_srh_get_next_hop (DBG): ON\n", clock_seconds());
        printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> rpl_ext_header_srh_get_next_hop (DBG): SNAPS: %d\n", clock_seconds(), galiot_snap_count_rpl_ext_header_srh_get_next_hop_DBG);
        
        if (galiot_snap_flag_countOverflow_rpl_ext_header_srh_get_next_hop_DBG == 1)
        {
          printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> rpl_ext_header_srh_get_next_hop (DBG): OVERFLOW\n", clock_seconds());
        }
        
        printf("----------------------------------------------------------------\n");
      }
        
      for (int i = 0; i < GALIOT_SNAPSHOT_COUNT; i++)
      {
        printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> rpl_ext_header_srh_get_next_hop (DBG) >>> [%10lu] LAST_SNAP[%d]\n", clock_seconds(), galiot_snap_rpl_ext_header_srh_get_next_hop_DBG.system_time[i], i);
        printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> rpl_ext_header_srh_get_next_hop (DBG): NO SRH FOUND\n", clock_seconds());
        printf("----------------------------------------------------------------\n");
        
      }
      
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #endif /* GALIOT_SNAP_RPL_EXT_HEADER_SRH_GET_NEXT_HOP */
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/



      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      // rpl_ext_header_srh_update_INFO_srh_not_found
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #if GALIOT_SNAP_RPL_EXT_HEADER_SRH_UPDATE
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/

      if (galiot_snap_flag_rpl_ext_header_srh_update_INFO_srh_not_found == 0)
      {
        //printf("\n");
        //printf("\n");
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> rpl_ext_header_srh_update (INFO): OFF\n", clock_seconds());
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        //printf("\n");
      }
      else
      {
        printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> rpl_ext_header_srh_update (INFO): ON\n", clock_seconds());
        printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> rpl_ext_header_srh_update (INFO): SNAPS: %d\n", clock_seconds(), galiot_snap_count_rpl_ext_header_srh_update_INFO_srh_not_found);
        
        if (galiot_snap_flag_countOverflow_rpl_ext_header_srh_update_INFO_srh_not_found == 1)
        {
          printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> rpl_ext_header_srh_update (INFO): OVERFLOW\n", clock_seconds());
        }
        
        printf("----------------------------------------------------------------\n");
      }
        
      for (int i = 0; i < GALIOT_SNAPSHOT_COUNT; i++)
      {
        printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> rpl_ext_header_srh_update (INFO) >>> [%10lu] LAST_SNAP[%d]\n", clock_seconds(), galiot_snap_rpl_ext_header_srh_update_INFO_srh_not_found.system_time[i], i);
        printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> rpl_ext_header_srh_update (INFO): SRH NOT FOUND\n", clock_seconds());
        printf("----------------------------------------------------------------\n");
        
      }
      
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #endif /* GALIOT_SNAP_RPL_EXT_HEADER_SRH_UPDATE */
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/



      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      // rpl_ext_header_srh_update_INFO_srh_read
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #if GALIOT_SNAP_RPL_EXT_HEADER_SRH_UPDATE
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/

      if (galiot_snap_flag_rpl_ext_header_srh_update_INFO_srh_read == 0)
      {
        //printf("\n");
        //printf("\n");
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> rpl_ext_header_srh_update (INFO): OFF\n", clock_seconds());
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        //printf("\n");
      }
      else
      {
        printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> rpl_ext_header_srh_update (INFO): ON\n", clock_seconds());
        printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> rpl_ext_header_srh_update (INFO): SNAPS: %d\n", clock_seconds(), galiot_snap_count_rpl_ext_header_srh_update_INFO_srh_read);
        
        if (galiot_snap_flag_countOverflow_rpl_ext_header_srh_update_INFO_srh_read == 1)
        {
          printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> rpl_ext_header_srh_update (INFO): OVERFLOW\n", clock_seconds());
        }
        
        printf("----------------------------------------------------------------\n");
      }
        
      for (int i = 0; i < GALIOT_SNAPSHOT_COUNT; i++)
      {
        printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> rpl_ext_header_srh_update (INFO) >>> [%10lu] LAST_SNAP[%d]\n", clock_seconds(), galiot_snap_rpl_ext_header_srh_update_INFO_srh_read.system_time[i], i);
        printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> rpl_ext_header_srh_update (INFO): READ SRH, PATH LEN: %u\n", clock_seconds(), galiot_snap_rpl_ext_header_srh_update_INFO_srh_read.path_len[i]);
        printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> rpl_ext_header_srh_update (INFO): READ SRH, SEGMENTS LEFT: %u\n", clock_seconds(), galiot_snap_rpl_ext_header_srh_update_INFO_srh_read.segments_left[i]);
        printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> rpl_ext_header_srh_update (INFO): READ SRH, COMPRI: %u\n", clock_seconds(), galiot_snap_rpl_ext_header_srh_update_INFO_srh_read.cmpri[i]);
        printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> rpl_ext_header_srh_update (INFO): READ SRH, COMPRE: %u\n", clock_seconds(), galiot_snap_rpl_ext_header_srh_update_INFO_srh_read.cmpre[i]);
        printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> rpl_ext_header_srh_update (INFO): READ SRH, EXT LEN: %u\n", clock_seconds(), galiot_snap_rpl_ext_header_srh_update_INFO_srh_read.ext_len[i]);
        printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> rpl_ext_header_srh_update (INFO): READ SRH, (PADDING): %u\n", clock_seconds(), galiot_snap_rpl_ext_header_srh_update_INFO_srh_read.padding[i]);
        printf("----------------------------------------------------------------\n");
        
      }
      
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #endif /* GALIOT_SNAP_RPL_EXT_HEADER_SRH_UPDATE */
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/



      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      // rpl_ext_header_srh_update_INFO_update
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #if GALIOT_SNAP_RPL_EXT_HEADER_SRH_UPDATE
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/

      if (galiot_snap_flag_rpl_ext_header_srh_update_INFO_update == 0)
      {
        //printf("\n");
        //printf("\n");
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> rpl_ext_header_srh_update (INFO): OFF\n", clock_seconds());
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        //printf("\n");
      }
      else
      {
        printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> rpl_ext_header_srh_update (INFO): ON\n", clock_seconds());
        printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> rpl_ext_header_srh_update (INFO): SNAPS: %d\n", clock_seconds(), galiot_snap_count_rpl_ext_header_srh_update_INFO_update);
        
        if (galiot_snap_flag_countOverflow_rpl_ext_header_srh_update_INFO_update == 1)
        {
          printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> rpl_ext_header_srh_update (INFO): OVERFLOW\n", clock_seconds());
        }
        
        printf("----------------------------------------------------------------\n");
      }
        
      for (int i = 0; i < GALIOT_SNAPSHOT_COUNT; i++)
      {
        printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> rpl_ext_header_srh_update (INFO) >>> [%10lu] LAST_SNAP[%d]\n", clock_seconds(), galiot_snap_rpl_ext_header_srh_update_INFO_update.system_time[i], i);
        printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> rpl_ext_header_srh_update (INFO): SRH NEXT HOP, (6ADDR): %s\n", clock_seconds(), galiot_snap_rpl_ext_header_srh_update_INFO_update.destipaddr_6ADDR[i]);
        printf("----------------------------------------------------------------\n");
        
      }
      
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #endif /* GALIOT_SNAP_RPL_EXT_HEADER_SRH_UPDATE */
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/



      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      // rpl_ext_header_insert_srh_header_INFO_creating
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #if GALIOT_SNAP_RPL_EXT_HEADER_INSERT_SRH_HEADER
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/

      if (galiot_snap_flag_rpl_ext_header_insert_srh_header_INFO_creating == 0)
      {
        //printf("\n");
        //printf("\n");
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> insert_srh_header (INFO): OFF\n", clock_seconds());
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        //printf("\n");
      }
      else
      {
        printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> insert_srh_header (INFO): ON\n", clock_seconds());
        printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> insert_srh_header (INFO): SNAPS: %d\n", clock_seconds(), galiot_snap_count_rpl_ext_header_insert_srh_header_INFO_creating);
        
        if (galiot_snap_flag_countOverflow_rpl_ext_header_insert_srh_header_INFO_creating == 1)
        {
          printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> insert_srh_header (INFO): OVERFLOW\n", clock_seconds());
        }
        
        printf("----------------------------------------------------------------\n");
      }
        
      for (int i = 0; i < GALIOT_SNAPSHOT_COUNT; i++)
      {
        printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> insert_srh_header (INFO) >>> [%10lu] LAST_SNAP[%d]\n", clock_seconds(), galiot_snap_rpl_ext_header_insert_srh_header_INFO_creating.system_time[i], i);
        printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> insert_srh_header (INFO): SRH CREATING ROUTE SOURCING HEADER WITH DESTINATION, (6ADDR): %s\n", clock_seconds(), galiot_snap_rpl_ext_header_insert_srh_header_INFO_creating.destipaddr_6ADDR[i]);
        printf("----------------------------------------------------------------\n");

        for (int z = 0; z < galiot_snap_rpl_ext_header_insert_srh_header_INFO_creating.hop_count[i]; z++)
        {
          printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> insert_srh_header (ERR): SRH HOP %d / %d, (6ADDR): %s\n", clock_seconds(), z+1, galiot_snap_rpl_ext_header_insert_srh_header_INFO_creating.hop_count[i], galiot_snap_rpl_ext_header_insert_srh_header_INFO_creating.node_6ADDR[i][z]);
          printf("----------------------------------------------------------------\n");
        }
        
        
        printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> insert_srh_header (INFO): SRH, PATH LEN: %u\n", clock_seconds(), galiot_snap_rpl_ext_header_insert_srh_header_INFO_creating.path_len[i]);
        printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> insert_srh_header (INFO): SRH, COMPRI: %u\n", clock_seconds(), galiot_snap_rpl_ext_header_insert_srh_header_INFO_creating.cmpri[i]);
        printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> insert_srh_header (INFO): SRH, COMPRE: %u\n", clock_seconds(), galiot_snap_rpl_ext_header_insert_srh_header_INFO_creating.cmpre[i]);
        printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> insert_srh_header (INFO): SRH, EXT LEN: %u\n", clock_seconds(), galiot_snap_rpl_ext_header_insert_srh_header_INFO_creating.ext_len[i]);
        printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> insert_srh_header (INFO): SRH, (PADDING): %u\n", clock_seconds(), galiot_snap_rpl_ext_header_insert_srh_header_INFO_creating.padding[i]);
        printf("----------------------------------------------------------------\n");


        
      }
      
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #endif /* GALIOT_SNAP_RPL_EXT_HEADER_INSERT_SRH_HEADER */
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/



      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      // rpl_ext_header_insert_srh_header_INFO_dest_not_in_DAG
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #if GALIOT_SNAP_RPL_EXT_HEADER_INSERT_SRH_HEADER
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/

      if (galiot_snap_flag_rpl_ext_header_insert_srh_header_INFO_dest_not_in_DAG == 0)
      {
        //printf("\n");
        //printf("\n");
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> insert_srh_header (INFO): OFF\n", clock_seconds());
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        //printf("\n");
      }
      else
      {
        printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> insert_srh_header (INFO): ON\n", clock_seconds());
        printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> insert_srh_header (INFO): SNAPS: %d\n", clock_seconds(), galiot_snap_count_rpl_ext_header_insert_srh_header_INFO_creating);
        
        if (galiot_snap_flag_countOverflow_rpl_ext_header_insert_srh_header_INFO_dest_not_in_DAG == 1)
        {
          printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> insert_srh_header (INFO): OVERFLOW\n", clock_seconds());
        }
        
        printf("----------------------------------------------------------------\n");
      }
        
      for (int i = 0; i < GALIOT_SNAPSHOT_COUNT; i++)
      {
        printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> insert_srh_header (INFO) >>> [%10lu] LAST_SNAP[%d]\n", clock_seconds(), galiot_snap_rpl_ext_header_insert_srh_header_INFO_dest_not_in_DAG.system_time[i], i);
        printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> insert_srh_header (INFO): SRH DESTINATION NOT IN OUR DAG, SKIP SRH INSERTION\n", clock_seconds());
        printf("----------------------------------------------------------------\n");
        
      }
      
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #endif /* GALIOT_SNAP_RPL_EXT_HEADER_INSERT_SRH_HEADER */
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/



      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      // rpl_ext_header_insert_srh_header_INFO_node_not_found
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #if GALIOT_SNAP_RPL_EXT_HEADER_INSERT_SRH_HEADER
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/

      if (galiot_snap_flag_rpl_ext_header_insert_srh_header_INFO_node_not_found == 0)
      {
        //printf("\n");
        //printf("\n");
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> insert_srh_header (INFO): OFF\n", clock_seconds());
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        //printf("\n");
      }
      else
      {
        printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> insert_srh_header (INFO): ON\n", clock_seconds());
        printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> insert_srh_header (INFO): SNAPS: %d\n", clock_seconds(), galiot_snap_count_rpl_ext_header_insert_srh_header_INFO_node_not_found);
        
        if (galiot_snap_flag_countOverflow_rpl_ext_header_insert_srh_header_INFO_node_not_found == 1)
        {
          printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> insert_srh_header (INFO): OVERFLOW\n", clock_seconds());
        }
        
        printf("----------------------------------------------------------------\n");
      }
        
      for (int i = 0; i < GALIOT_SNAPSHOT_COUNT; i++)
      {
        printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> insert_srh_header (INFO) >>> [%10lu] LAST_SNAP[%d]\n", clock_seconds(), galiot_snap_rpl_ext_header_insert_srh_header_INFO_node_not_found.system_time[i], i);
        printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> insert_srh_header (INFO): SRH NODE NOT FOUND, SKIP SRH INSERTION\n", clock_seconds());
        printf("----------------------------------------------------------------\n");
        
      }
      
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #endif /* GALIOT_SNAP_RPL_EXT_HEADER_INSERT_SRH_HEADER */
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/



      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      // rpl_ext_header_insert_srh_header_ERR_root_node
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #if GALIOT_SNAP_RPL_EXT_HEADER_INSERT_SRH_HEADER
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/

      if (galiot_snap_flag_rpl_ext_header_insert_srh_header_ERR_root_node == 0)
      {
        //printf("\n");
        //printf("\n");
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> insert_srh_header (ERR): OFF\n", clock_seconds());
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        //printf("\n");
      }
      else
      {
        printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> insert_srh_header (ERR): ON\n", clock_seconds());
        printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> insert_srh_header (ERR): SNAPS: %d\n", clock_seconds(), galiot_snap_count_rpl_ext_header_insert_srh_header_ERR_root_node);
        
        if (galiot_snap_flag_countOverflow_rpl_ext_header_insert_srh_header_ERR_root_node == 1)
        {
          printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> insert_srh_header (ERR): OVERFLOW\n", clock_seconds());
        }
        
        printf("----------------------------------------------------------------\n");
      }
        
      for (int i = 0; i < GALIOT_SNAPSHOT_COUNT; i++)
      {
        printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> insert_srh_header (ERR) >>> [%10lu] LAST_SNAP[%d]\n", clock_seconds(), galiot_snap_rpl_ext_header_insert_srh_header_ERR_root_node.system_time[i], i);
        printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> insert_srh_header (ERR): SRH NODE NOT FOUND\n", clock_seconds());
        printf("----------------------------------------------------------------\n");
        
      }
      
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #endif /* GALIOT_SNAP_RPL_EXT_HEADER_INSERT_SRH_HEADER */
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/



      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      // rpl_ext_header_insert_srh_header_ERR_no_path
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #if GALIOT_SNAP_RPL_EXT_HEADER_INSERT_SRH_HEADER
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/

      if (galiot_snap_flag_rpl_ext_header_insert_srh_header_ERR_no_path == 0)
      {
        //printf("\n");
        //printf("\n");
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> insert_srh_header (ERR): OFF\n", clock_seconds());
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        //printf("\n");
      }
      else
      {
        printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> insert_srh_header (ERR): ON\n", clock_seconds());
        printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> insert_srh_header (ERR): SNAPS: %d\n", clock_seconds(), galiot_snap_count_rpl_ext_header_insert_srh_header_ERR_no_path);
        
        if (galiot_snap_flag_countOverflow_rpl_ext_header_insert_srh_header_ERR_no_path == 1)
        {
          printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> insert_srh_header (ERR): OVERFLOW\n", clock_seconds());
        }
        
        printf("----------------------------------------------------------------\n");
      }
        
      for (int i = 0; i < GALIOT_SNAPSHOT_COUNT; i++)
      {
        printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> insert_srh_header (ERR) >>> [%10lu] LAST_SNAP[%d]\n", clock_seconds(), galiot_snap_rpl_ext_header_insert_srh_header_ERR_no_path.system_time[i], i);
        printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> insert_srh_header (ERR): SRH NO PATH FOUND TO DESTINATION\n", clock_seconds());
        printf("----------------------------------------------------------------\n");
        
      }
      
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #endif /* GALIOT_SNAP_RPL_EXT_HEADER_INSERT_SRH_HEADER */
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/



      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      // rpl_ext_header_insert_srh_header_ERR_pckt_too_long
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #if GALIOT_SNAP_RPL_EXT_HEADER_INSERT_SRH_HEADER
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/

      if (galiot_snap_flag_rpl_ext_header_insert_srh_header_ERR_pckt_too_long == 0)
      {
        //printf("\n");
        //printf("\n");
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> insert_srh_header (ERR): OFF\n", clock_seconds());
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        //printf("\n");
      }
      else
      {
        printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> insert_srh_header (ERR): ON\n", clock_seconds());
        printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> insert_srh_header (ERR): SNAPS: %d\n", clock_seconds(), galiot_snap_count_rpl_ext_header_insert_srh_header_ERR_pckt_too_long);
        
        if (galiot_snap_flag_countOverflow_rpl_ext_header_insert_srh_header_ERR_pckt_too_long == 1)
        {
          printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> insert_srh_header (ERR): OVERFLOW\n", clock_seconds());
        }
        
        printf("----------------------------------------------------------------\n");
      }
        
      for (int i = 0; i < GALIOT_SNAPSHOT_COUNT; i++)
      {
        printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> insert_srh_header (ERR) >>> [%10lu] LAST_SNAP[%d]\n", clock_seconds(), galiot_snap_rpl_ext_header_insert_srh_header_ERR_pckt_too_long.system_time[i], i);
        printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> insert_srh_header (ERR): PACKET TOO LONG, IMPOSSIBLE TO ADD SOURCE ROUTING HEADER (%u BYTES)\n", clock_seconds(), galiot_snap_rpl_ext_header_insert_srh_header_ERR_pckt_too_long.ext_len[i]);
        printf("----------------------------------------------------------------\n");
        
      }
      
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #endif /* GALIOT_SNAP_RPL_EXT_HEADER_INSERT_SRH_HEADER */
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/



      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      // rpl_ext_header_hbh_update_ERR_wrong_size
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #if GALIOT_SNAP_RPL_EXT_HEADER_SBH_UPDATE
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/

      if (galiot_snap_flag_rpl_ext_header_hbh_update_ERR_wrong_size == 0)
      {
        //printf("\n");
        //printf("\n");
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> rpl_ext_header_hbh_update (ERR): OFF\n", clock_seconds());
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        //printf("\n");
      }
      else
      {
        printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> rpl_ext_header_hbh_update (ERR): ON\n", clock_seconds());
        printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> rpl_ext_header_hbh_update (ERR): SNAPS: %d\n", clock_seconds(), galiot_snap_count_rpl_ext_header_hbh_update_ERR_wrong_size);
        
        if (galiot_snap_flag_countOverflow_rpl_ext_header_hbh_update_ERR_wrong_size == 1)
        {
          printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> rpl_ext_header_hbh_update (ERR): OVERFLOW\n", clock_seconds());
        }
        
        printf("----------------------------------------------------------------\n");
      }
        
      for (int i = 0; i < GALIOT_SNAPSHOT_COUNT; i++)
      {
        printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> rpl_ext_header_hbh_update (ERR) >>> [%10lu] LAST_SNAP[%d]\n", clock_seconds(), galiot_snap_rpl_ext_header_hbh_update_ERR_wrong_size.system_time[i], i);
        printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> rpl_ext_header_hbh_update (ERR): HOP-BY-HOP EXTENSION HEADER HAS WRONG SIZE OR TYPE\n", clock_seconds());
        printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> rpl_ext_header_hbh_update (ERR): LEN: %u\n", clock_seconds(), galiot_snap_rpl_ext_header_hbh_update_ERR_wrong_size.len[i]);
        printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> rpl_ext_header_hbh_update (ERR): OPT TYPE: %u\n", clock_seconds(), galiot_snap_rpl_ext_header_hbh_update_ERR_wrong_size.opt_type[i]);
        printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> rpl_ext_header_hbh_update (ERR): OPT LEN: %u\n", clock_seconds(), galiot_snap_rpl_ext_header_hbh_update_ERR_wrong_size.opt_len[i]);
        printf("----------------------------------------------------------------\n");
      }
      
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #endif /* GALIOT_SNAP_RPL_EXT_HEADER_SBH_UPDATE */
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/



      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      // rpl_ext_header_hbh_update_ERR_unknown_instance
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #if GALIOT_SNAP_RPL_EXT_HEADER_SBH_UPDATE
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/

      if (galiot_snap_flag_rpl_ext_header_hbh_update_ERR_unknown_instance == 0)
      {
        //printf("\n");
        //printf("\n");
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> rpl_ext_header_hbh_update (ERR): OFF\n", clock_seconds());
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        //printf("\n");
      }
      else
      {
        printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> rpl_ext_header_hbh_update (ERR): ON\n", clock_seconds());
        printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> rpl_ext_header_hbh_update (ERR): SNAPS: %d\n", clock_seconds(), galiot_snap_count_rpl_ext_header_hbh_update_ERR_unknown_instance);
        
        if (galiot_snap_flag_countOverflow_rpl_ext_header_hbh_update_ERR_unknown_instance == 1)
        {
          printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> rpl_ext_header_hbh_update (ERR): OVERFLOW\n", clock_seconds());
        }
        
        printf("----------------------------------------------------------------\n");
      }
        
      for (int i = 0; i < GALIOT_SNAPSHOT_COUNT; i++)
      {
        printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> rpl_ext_header_hbh_update (ERR) >>> [%10lu] LAST_SNAP[%d]\n", clock_seconds(), galiot_snap_rpl_ext_header_hbh_update_ERR_unknown_instance.system_time[i], i);
        printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> rpl_ext_header_hbh_update (ERR): UNKNOWN INSTANCE: %u\n", clock_seconds(), galiot_snap_rpl_ext_header_hbh_update_ERR_unknown_instance.instance[i]);
        printf("----------------------------------------------------------------\n");
      }
      
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #endif /* GALIOT_SNAP_RPL_EXT_HEADER_SBH_UPDATE */
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/



      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      // rpl_ext_header_hbh_update_ERR_forward_error
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #if GALIOT_SNAP_RPL_EXT_HEADER_SBH_UPDATE
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/

      if (galiot_snap_flag_rpl_ext_header_hbh_update_ERR_forward_error == 0)
      {
        //printf("\n");
        //printf("\n");
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> rpl_ext_header_hbh_update (ERR): OFF\n", clock_seconds());
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        //printf("\n");
      }
      else
      {
        printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> rpl_ext_header_hbh_update (ERR): ON\n", clock_seconds());
        printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> rpl_ext_header_hbh_update (ERR): SNAPS: %d\n", clock_seconds(), galiot_snap_count_rpl_ext_header_hbh_update_ERR_forward_error);
        
        if (galiot_snap_flag_countOverflow_rpl_ext_header_hbh_update_ERR_forward_error == 1)
        {
          printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> rpl_ext_header_hbh_update (ERR): OVERFLOW\n", clock_seconds());
        }
        
        printf("----------------------------------------------------------------\n");
      }
        
      for (int i = 0; i < GALIOT_SNAPSHOT_COUNT; i++)
      {
        printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> rpl_ext_header_hbh_update (ERR) >>> [%10lu] LAST_SNAP[%d]\n", clock_seconds(), galiot_snap_rpl_ext_header_hbh_update_ERR_forward_error.system_time[i], i);
        printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> rpl_ext_header_hbh_update (ERR): FORWARD ERROR!\n", clock_seconds());
        printf("----------------------------------------------------------------\n");
      }
      
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #endif /* GALIOT_SNAP_RPL_EXT_HEADER_SBH_UPDATE */
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/




      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      // rpl_ext_header_hbh_update_INFO
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #if GALIOT_SNAP_RPL_EXT_HEADER_SBH_UPDATE
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/

      if (galiot_snap_flag_rpl_ext_header_hbh_update_INFO == 0)
      {
        //printf("\n");
        //printf("\n");
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> rpl_ext_header_hbh_update (INFO): OFF\n", clock_seconds());
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        //printf("\n");
      }
      else
      {
        printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> rpl_ext_header_hbh_update (INFO): ON\n", clock_seconds());
        printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> rpl_ext_header_hbh_update (INFO): SNAPS: %d\n", clock_seconds(), galiot_snap_count_rpl_ext_header_hbh_update_INFO);
        
        if (galiot_snap_flag_countOverflow_rpl_ext_header_hbh_update_INFO == 1)
        {
          printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> rpl_ext_header_hbh_update (INFO): OVERFLOW\n", clock_seconds());
        }
        
        printf("----------------------------------------------------------------\n");
      }
        
      for (int i = 0; i < GALIOT_SNAPSHOT_COUNT; i++)
      {
        printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> rpl_ext_header_hbh_update (INFO) >>> [%10lu] LAST_SNAP[%d]\n", clock_seconds(), galiot_snap_rpl_ext_header_hbh_update_INFO.system_time[i], i);
        printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> rpl_ext_header_hbh_update (INFO): PACKET SENT FROM (6ADDR) ---> %s\n", clock_seconds(), galiot_snap_rpl_ext_header_hbh_update_INFO.srcipaddr_6ADDR[i]);
        printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> rpl_ext_header_hbh_update (INFO): PACKET SENT TO (6ADDR) <--- %s\n", clock_seconds(), galiot_snap_rpl_ext_header_hbh_update_INFO.destipaddr_6ADDR[i]);
        printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> rpl_ext_header_hbh_update (INFO): GOING: %s\n", clock_seconds(), galiot_snap_rpl_ext_header_hbh_update_INFO.going_str[i]);
        printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> rpl_ext_header_hbh_update (INFO): SENDER CLOSER: %d\n", clock_seconds(), galiot_snap_rpl_ext_header_hbh_update_INFO.sender_closer[i]);
        printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> rpl_ext_header_hbh_update (INFO): (SENDER RANK): %d\n", clock_seconds(), galiot_snap_rpl_ext_header_hbh_update_INFO.sender_rank[i]);
        printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> rpl_ext_header_hbh_update (INFO): (DAG RANK): %d\n", clock_seconds(), galiot_snap_rpl_ext_header_hbh_update_INFO.dag_rank[i]);
        printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> rpl_ext_header_hbh_update (INFO): RANK ERROR SIGNALED: %u\n", clock_seconds(), galiot_snap_rpl_ext_header_hbh_update_INFO.rank_error_signaled[i]);
        printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> rpl_ext_header_hbh_update (INFO): LOOP DETECTED: %u\n", clock_seconds(), galiot_snap_rpl_ext_header_hbh_update_INFO.loop_detected[i]);
        printf("----------------------------------------------------------------\n");
      }
      
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #endif /* GALIOT_SNAP_RPL_EXT_HEADER_SBH_UPDATE */
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/



      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      // rpl_ext_header_update_hbh_header_ERR_wrong_size
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #if GALIOT_SNAP_RPL_EXT_HEADER_UPDATE_HBH_HEADER
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/

      if (galiot_snap_flag_rpl_ext_header_update_hbh_header_ERR_wrong_size == 0)
      {
        //printf("\n");
        //printf("\n");
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> update_hbh_header (ERR): OFF\n", clock_seconds());
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        //printf("\n");
      }
      else
      {
        printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> update_hbh_header (ERR): ON\n", clock_seconds());
        printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> update_hbh_header (ERR): SNAPS: %d\n", clock_seconds(), galiot_snap_count_rpl_ext_header_update_hbh_header_ERR_wrong_size);
        
        if (galiot_snap_flag_countOverflow_rpl_ext_header_update_hbh_header_ERR_wrong_size == 1)
        {
          printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> update_hbh_header (ERR): OVERFLOW\n", clock_seconds());
        }
        
        printf("----------------------------------------------------------------\n");
      }
        
      for (int i = 0; i < GALIOT_SNAPSHOT_COUNT; i++)
      {
        printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> update_hbh_header (ERR) >>> [%10lu] LAST_SNAP[%d]\n", clock_seconds(), galiot_snap_rpl_ext_header_update_hbh_header_ERR_wrong_size.system_time[i], i);
        printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> update_hbh_header (ERR): HOP-BY-HOP EXTENSION HEADER HAS WRONG SIZE: %u\n", clock_seconds(), galiot_snap_rpl_ext_header_update_hbh_header_ERR_wrong_size.opt_len[i]);
        printf("----------------------------------------------------------------\n");
      }
      
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #endif /* GALIOT_SNAP_RPL_EXT_HEADER_UPDATE_HBH_HEADER */
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/



      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      // rpl_ext_header_update_hbh_header_ERR_incorrect_distance
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #if GALIOT_SNAP_RPL_EXT_HEADER_UPDATE_HBH_HEADER
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/

      if (galiot_snap_flag_rpl_ext_header_update_hbh_header_ERR_incorrect_distance == 0)
      {
        //printf("\n");
        //printf("\n");
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> rpl_ext_header_hbh_update (ERR): OFF\n", clock_seconds());
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        //printf("\n");
      }
      else
      {
        printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> update_hbh_header (ERR): ON\n", clock_seconds());
        printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> update_hbh_header (ERR): SNAPS: %d\n", clock_seconds(), galiot_snap_count_rpl_ext_header_update_hbh_header_ERR_incorrect_distance);
        
        if (galiot_snap_flag_countOverflow_rpl_ext_header_update_hbh_header_ERR_incorrect_distance == 1)
        {
          printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> update_hbh_header (ERR): OVERFLOW\n", clock_seconds());
        }
        
        printf("----------------------------------------------------------------\n");
      }
        
      for (int i = 0; i < GALIOT_SNAPSHOT_COUNT; i++)
      {
        printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> update_hbh_header (ERR) >>> [%10lu] LAST_SNAP[%d]\n", clock_seconds(), galiot_snap_rpl_ext_header_update_hbh_header_ERR_incorrect_distance.system_time[i], i);
        printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> update_hbh_header (ERR): UNABLE TO ADD/UPDATE HOP-BY-HOP EXTENSION HEADER, INCORRECT DISTANCE\n", clock_seconds());
        printf("----------------------------------------------------------------\n");
      }
      
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #endif /* GALIOT_SNAP_RPL_EXT_HEADER_UPDATE_HBH_HEADER */
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/



      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      // rpl_ext_header_insert_hbh_header_INFO
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #if GALIOT_SNAP_RPL_EXT_HEADER_INSERT_HBH_HEADER
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/

      if (galiot_snap_flag_rpl_ext_header_insert_hbh_header_INFO == 0)
      {
        //printf("\n");
        //printf("\n");
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> insert_hbh_header (INFO): OFF\n", clock_seconds());
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        //printf("\n");
      }
      else
      {
        printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> insert_hbh_header (INFO): ON\n", clock_seconds());
        printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> insert_hbh_header (INFO): SNAPS: %d\n", clock_seconds(), galiot_snap_count_rpl_ext_header_insert_hbh_header_INFO);
        
        if (galiot_snap_flag_countOverflow_rpl_ext_header_insert_hbh_header_INFO == 1)
        {
          printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> insert_hbh_header (INFO): OVERFLOW\n", clock_seconds());
        }
        
        printf("----------------------------------------------------------------\n");
      }
        
      for (int i = 0; i < GALIOT_SNAPSHOT_COUNT; i++)
      {
        printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> insert_hbh_header (INFO) >>> [%10lu] LAST_SNAP[%d]\n", clock_seconds(), galiot_snap_rpl_ext_header_insert_hbh_header_INFO.system_time[i], i);
        printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> insert_hbh_header (INFO): CREATING HOP-BY-HOP OPTION\n", clock_seconds());
        printf("----------------------------------------------------------------\n");
      }
      
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #endif /* GALIOT_SNAP_RPL_EXT_HEADER_INSERT_HBH_HEADER */
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/



      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      // rpl_ext_header_insert_hbh_header_ERR
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #if GALIOT_SNAP_RPL_EXT_HEADER_INSERT_HBH_HEADER
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/

      if (galiot_snap_flag_rpl_ext_header_insert_hbh_header_ERR == 0)
      {
        //printf("\n");
        //printf("\n");
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> insert_hbh_header (ERR): OFF\n", clock_seconds());
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        //printf("\n");
      }
      else
      {
        printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> insert_hbh_header (ERR): ON\n", clock_seconds());
        printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> insert_hbh_header (ERR): SNAPS: %d\n", clock_seconds(), galiot_snap_count_rpl_ext_header_insert_hbh_header_ERR);
        
        if (galiot_snap_flag_countOverflow_rpl_ext_header_insert_hbh_header_ERR == 1)
        {
          printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> insert_hbh_header (ERR): OVERFLOW\n", clock_seconds());
        }
        
        printf("----------------------------------------------------------------\n");
      }
        
      for (int i = 0; i < GALIOT_SNAPSHOT_COUNT; i++)
      {
        printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> insert_hbh_header (ERR) >>> [%10lu] LAST_SNAP[%d]\n", clock_seconds(), galiot_snap_rpl_ext_header_insert_hbh_header_ERR.system_time[i], i);
        printf("(galiot) >>> [%10lu] >>> rpl_ext_header >>> insert_hbh_header (ERR): PACKET TOO LONG, IMPOSSIBLE TO ADD HOP-BY-HOP OPTION\n", clock_seconds());
        printf("----------------------------------------------------------------\n");
      }
      
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #endif /* GALIOT_SNAP_RPL_EXT_HEADER_INSERT_HBH_HEADER */
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/



    




      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    #endif /* GALIOT_FUNCTIONALITY */
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/











  











































    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    #ifdef GALIOT_FUNCTIONALITY
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      // /os/net/routing/rpl-lite/rpl-icmp6.c
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/

      
      //printf("\n");
      printf("(galiot) >>> rpl-icmp6\n");
      //printf("\n");

      

      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      // rpl_icmp6_update_nbr_table_ERR
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #if GALIOT_SNAP_RPL_ICMP6_UPDATE_NBR_TABLE
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/

      if (galiot_snap_flag_rpl_icmp6_update_nbr_table_ERR == 0)
      {
        //printf("\n");
        //printf("\n");
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> rpl_icmp6_update_nbr_table (ERR): OFF\n", clock_seconds());
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        //printf("\n");
      }
      else
      {
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> rpl_icmp6_update_nbr_table (ERR): ON\n", clock_seconds());
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> rpl_icmp6_update_nbr_table (ERR): SNAPS: %d\n", clock_seconds(), galiot_snap_count_rpl_icmp6_update_nbr_table_ERR);
        
        if (galiot_snap_flag_countOverflow_rpl_icmp6_update_nbr_table_ERR == 1)
        {
          printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> rpl_icmp6_update_nbr_table (ERR): OVERFLOW\n", clock_seconds());
        }
        
        printf("----------------------------------------------------------------\n");
      }
        
      for (int i = 0; i < GALIOT_SNAPSHOT_COUNT; i++)
      {
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> rpl_icmp6_update_nbr_table (ERR) >>> [%10lu] LAST_SNAP[%d]\n", clock_seconds(), galiot_snap_rpl_icmp6_update_nbr_table_ERR.system_time[i], i);
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> rpl_icmp6_update_nbr_table (ERR): COULD NOT ADD NEIGHBOR TO CASHE (6ADDR): %s\n", clock_seconds(), galiot_snap_rpl_icmp6_update_nbr_table_ERR.from_6addr[i]);
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> rpl_icmp6_update_nbr_table (ERR): (PACKETBUF ADDR): %s\n", clock_seconds(), galiot_snap_rpl_icmp6_update_nbr_table_ERR.packetbuf_lladdr[i]);

        printf("----------------------------------------------------------------\n");
      }
      
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #endif /* GALIOT_SNAP_RPL_ICMP6_UPDATE_NBR_TABLE */
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/



      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      // rpl_icmp6_dis_input_WARN
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #if GALIOT_SNAP_RPL_ICMP6_DIS_INPUT
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/

      if (galiot_snap_flag_rpl_icmp6_dis_input_WARN == 0)
      {
        //printf("\n");
        //printf("\n");
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> dis_input (WARN): OFF\n", clock_seconds());
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        //printf("\n");
      }
      else
      {
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> dis_input (WARN): ON\n", clock_seconds());
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> dis_input (WARN): SNAPS: %d\n", clock_seconds(), galiot_snap_count_rpl_icmp6_dis_input_WARN);
        
        if (galiot_snap_flag_countOverflow_rpl_icmp6_dis_input_WARN == 1)
        {
          printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> dis_input (WARN): OVERFLOW\n", clock_seconds());
        }
        
        printf("----------------------------------------------------------------\n");
      }
        
      for (int i = 0; i < GALIOT_SNAPSHOT_COUNT; i++)
      {
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> dis_input (WARN) >>> [%10lu] LAST_SNAP[%d]\n", clock_seconds(), galiot_snap_rpl_icmp6_dis_input_WARN.system_time[i], i);
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> dis_input (WARN): NOT IN AN INSTANCE YET, DISCARD \n", clock_seconds());

        printf("----------------------------------------------------------------\n");
      }
      
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #endif /* GALIOT_SNAP_RPL_ICMP6_DIS_INPUT */
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/



      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      // rpl_icmp6_dis_input_INFO
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #if GALIOT_SNAP_RPL_ICMP6_DIS_INPUT
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/

      if (galiot_snap_flag_rpl_icmp6_dis_input_INFO == 0)
      {
        //printf("\n");
        //printf("\n");
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> dis_input (INFO): OFF\n", clock_seconds());
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        //printf("\n");
      }
      else
      {
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> dis_input (INFO): ON\n", clock_seconds());
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> dis_input (INFO): SNAPS: %d\n", clock_seconds(), galiot_snap_count_rpl_icmp6_dis_input_INFO);
        
        if (galiot_snap_flag_countOverflow_rpl_icmp6_dis_input_INFO == 1)
        {
          printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> dis_input (INFO): OVERFLOW\n", clock_seconds());
        }
        
        printf("----------------------------------------------------------------\n");
      }
        
      for (int i = 0; i < GALIOT_SNAPSHOT_COUNT; i++)
      {
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> dis_input (INFO) >>> [%10lu] LAST_SNAP[%d]\n", clock_seconds(), galiot_snap_rpl_icmp6_dis_input_INFO.system_time[i], i);
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> dis_input (INFO): RECEIVED A DIS FROM (6ADDR): %s\n", clock_seconds(), galiot_snap_rpl_icmp6_dis_input_INFO.DIS_from_6addr[i]);
        printf("----------------------------------------------------------------\n");
      }
      
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #endif /* GALIOT_SNAP_RPL_ICMP6_DIS_INPUT */
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/



      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      // rpl_icmp6_dis_output_INFO
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #if GALIOT_SNAP_RPL_ICMP6_DIS_OUTPUT
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/

      if (galiot_snap_flag_rpl_icmp6_dis_output_INFO == 0)
      {
        //printf("\n");
        //printf("\n");
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> rpl_icmp6_dis_output (INFO): OFF\n", clock_seconds());
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        //printf("\n");
      }
      else
      {
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> rpl_icmp6_dis_output (INFO): ON\n", clock_seconds());
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> rpl_icmp6_dis_output (INFO): SNAPS: %d\n", clock_seconds(), galiot_snap_count_rpl_icmp6_dis_output_INFO);
        
        if (galiot_snap_flag_countOverflow_rpl_icmp6_dis_output_INFO == 1)
        {
          printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> rpl_icmp6_dis_output (INFO): OVERFLOW\n", clock_seconds());
        }
        
        printf("----------------------------------------------------------------\n");
      }
        
      for (int i = 0; i < GALIOT_SNAPSHOT_COUNT; i++)
      {
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> rpl_icmp6_dis_output (INFO) >>> [%10lu] LAST_SNAP[%d]\n", clock_seconds(), galiot_snap_rpl_icmp6_dis_output_INFO.system_time[i], i);
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> rpl_icmp6_dis_output (INFO): SENDING A DIS TO (6ADDR): %s\n", clock_seconds(), galiot_snap_rpl_icmp6_dis_output_INFO.DIS_to_6addr[i]);
        printf("----------------------------------------------------------------\n");
      }
      
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #endif /* GALIOT_SNAP_RPL_ICMP6_DIS_OUTPUT */
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/



      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      // rpl_icmp6_dio_input_ERR
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #if GALIOT_SNAP_RPL_ICMP6_DIO_INPUT
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/

      if (galiot_snap_flag_rpl_icmp6_dio_input_ERR == 0)
      {
        //printf("\n");
        //printf("\n");
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> dio_input (ERR): OFF\n", clock_seconds());
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        //printf("\n");
      }
      else
      {
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> dio_input (ERR): ON\n", clock_seconds());
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> dio_input (ERR): SNAPS: %d\n", clock_seconds(), galiot_snap_count_rpl_icmp6_dio_input_ERR);
        
        if (galiot_snap_flag_countOverflow_rpl_icmp6_dio_input_ERR == 1)
        {
          printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> dio_input (ERR): OVERFLOW\n", clock_seconds());
        }
        
        printf("----------------------------------------------------------------\n");
      }
        
      for (int i = 0; i < GALIOT_SNAPSHOT_COUNT; i++)
      {
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> dio_input (ERR) >>> [%10lu] LAST_SNAP[%d]\n", clock_seconds(), galiot_snap_rpl_icmp6_dio_input_ERR.system_time[i], i);
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> dio_input (ERR): MALFORMED PACKET, DISCARD:\n", clock_seconds());
        printf("----------------------------------------------------------------\n");
      }
      
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #endif /* GALIOT_SNAP_RPL_ICMP6_DIO_INPUT */
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/



      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      // rpl_icmp6_dio_input_WARN_option_mc
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #if GALIOT_SNAP_RPL_ICMP6_DIO_INPUT
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/

      if (galiot_snap_flag_rpl_icmp6_dio_input_WARN_option_mc == 0)
      {
        //printf("\n");
        //printf("\n");
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> dio_input (WARN): OFF\n", clock_seconds());
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        //printf("\n");
      }
      else
      {
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> dio_input (WARN): ON\n", clock_seconds());
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> dio_input (WARN): SNAPS: %d\n", clock_seconds(), galiot_snap_count_rpl_icmp6_dio_input_WARN_option_mc);
        
        if (galiot_snap_flag_countOverflow_rpl_icmp6_dio_input_WARN_option_mc == 1)
        {
          printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> dio_input (WARN): OVERFLOW\n", clock_seconds());
        }
        
        printf("----------------------------------------------------------------\n");
      }
        
      for (int i = 0; i < GALIOT_SNAPSHOT_COUNT; i++)
      {
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> dio_input (WARN) >>> [%10lu] LAST_SNAP[%d]\n", clock_seconds(), galiot_snap_rpl_icmp6_dio_input_WARN_option_mc.system_time[i], i);
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> dio_input (WARN): INVALID DAG METRIC CONTAINER, LEN: %u, DISCARD\n", clock_seconds(), galiot_snap_rpl_icmp6_dio_input_WARN_option_mc.len[i]);
        printf("----------------------------------------------------------------\n");
      }
      
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #endif /* GALIOT_SNAP_RPL_ICMP6_DIO_INPUT */
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/



      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      // rpl_icmp6_dio_input_WARN_option_mc_else
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #if GALIOT_SNAP_RPL_ICMP6_DIO_INPUT
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/

      if (galiot_snap_flag_rpl_icmp6_dio_input_WARN_option_mc_else == 0)
      {
        //printf("\n");
        //printf("\n");
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> dio_input (WARN): OFF\n", clock_seconds());
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        //printf("\n");
      }
      else
      {
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> dio_input (WARN): ON\n", clock_seconds());
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> dio_input (WARN): SNAPS: %d\n", clock_seconds(), galiot_snap_count_rpl_icmp6_dio_input_WARN_option_mc_else);
        
        if (galiot_snap_flag_countOverflow_rpl_icmp6_dio_input_WARN_option_mc_else == 1)
        {
          printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> dio_input (WARN): OVERFLOW\n", clock_seconds());
        }
        
        printf("----------------------------------------------------------------\n");
      }
        
      for (int i = 0; i < GALIOT_SNAPSHOT_COUNT; i++)
      {
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> dio_input (WARN) >>> [%10lu] LAST_SNAP[%d]\n", clock_seconds(), galiot_snap_rpl_icmp6_dio_input_WARN_option_mc_else.system_time[i], i);
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> dio_input (WARN): UNSUPPORTED DAG METRIC CONTAINER, TYPE: %u, DISCARD\n", clock_seconds(), galiot_snap_rpl_icmp6_dio_input_WARN_option_mc_else.type[i]);
        printf("----------------------------------------------------------------\n");
      }
      
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #endif /* GALIOT_SNAP_RPL_ICMP6_DIO_INPUT */
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/



      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      // rpl_icmp6_dio_input_WARN_route
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #if GALIOT_SNAP_RPL_ICMP6_DIO_INPUT
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/

      if (galiot_snap_flag_rpl_icmp6_dio_input_WARN_route == 0)
      {
        //printf("\n");
        //printf("\n");
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> dio_input (WARN): OFF\n", clock_seconds());
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        //printf("\n");
      }
      else
      {
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> dio_input (WARN): ON\n", clock_seconds());
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> dio_input (WARN): SNAPS: %d\n", clock_seconds(), galiot_snap_count_rpl_icmp6_dio_input_WARN_route);
        
        if (galiot_snap_flag_countOverflow_rpl_icmp6_dio_input_WARN_route == 1)
        {
          printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> dio_input (WARN): OVERFLOW\n", clock_seconds());
        }
        
        printf("----------------------------------------------------------------\n");
      }
        
      for (int i = 0; i < GALIOT_SNAPSHOT_COUNT; i++)
      {
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> dio_input (WARN) >>> [%10lu] LAST_SNAP[%d]\n", clock_seconds(), galiot_snap_rpl_icmp6_dio_input_WARN_route.system_time[i], i);
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> dio_input (WARN): INVALID DESTINATION PREFIX OPTION, LEN: %u, DISCARD\n", clock_seconds(), galiot_snap_rpl_icmp6_dio_input_WARN_route.len[i]);
        printf("----------------------------------------------------------------\n");
      }
      
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #endif /* GALIOT_SNAP_RPL_ICMP6_DIO_INPUT */
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/



      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      // rpl_icmp6_dio_input_WARN_route_else
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #if GALIOT_SNAP_RPL_ICMP6_DIO_INPUT
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/

      if (galiot_snap_flag_rpl_icmp6_dio_input_WARN_route_else == 0)
      {
        //printf("\n");
        //printf("\n");
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> dio_input (WARN): OFF\n", clock_seconds());
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        //printf("\n");
      }
      else
      {
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> dio_input (WARN): ON\n", clock_seconds());
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> dio_input (WARN): SNAPS: %d\n", clock_seconds(), galiot_snap_count_rpl_icmp6_dio_input_WARN_route_else);
        
        if (galiot_snap_flag_countOverflow_rpl_icmp6_dio_input_WARN_route_else == 1)
        {
          printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> dio_input (WARN): OVERFLOW\n", clock_seconds());
        }
        
        printf("----------------------------------------------------------------\n");
      }
        
      for (int i = 0; i < GALIOT_SNAPSHOT_COUNT; i++)
      {
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> dio_input (WARN) >>> [%10lu] LAST_SNAP[%d]\n", clock_seconds(), galiot_snap_rpl_icmp6_dio_input_WARN_route_else.system_time[i], i);
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> dio_input (WARN): INVALID ROUTE INFO OPTION, LEN: %u, DISCARD\n", clock_seconds(), galiot_snap_rpl_icmp6_dio_input_WARN_route_else.len[i]);
        printf("----------------------------------------------------------------\n");
      }
      
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #endif /* GALIOT_SNAP_RPL_ICMP6_DIO_INPUT */
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/



      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      // rpl_icmp6_dio_input_WARN_option_DAG
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #if GALIOT_SNAP_RPL_ICMP6_DIO_INPUT
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/

      if (galiot_snap_flag_rpl_icmp6_dio_input_WARN_option_DAG == 0)
      {
        //printf("\n");
        //printf("\n");
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> dio_input (WARN): OFF\n", clock_seconds());
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        //printf("\n");
      }
      else
      {
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> dio_input (WARN): ON\n", clock_seconds());
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> dio_input (WARN): SNAPS: %d\n", clock_seconds(), galiot_snap_count_rpl_icmp6_dio_input_WARN_option_DAG);
        
        if (galiot_snap_flag_countOverflow_rpl_icmp6_dio_input_WARN_option_DAG == 1)
        {
          printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> dio_input (WARN): OVERFLOW\n", clock_seconds());
        }
        
        printf("----------------------------------------------------------------\n");
      }
        
      for (int i = 0; i < GALIOT_SNAPSHOT_COUNT; i++)
      {
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> dio_input (WARN) >>> [%10lu] LAST_SNAP[%d]\n", clock_seconds(), galiot_snap_rpl_icmp6_dio_input_WARN_option_DAG.system_time[i], i);
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> dio_input (WARN): INVALID DAG CONFIGURATION OPTION, LEN: %u, DISCARD\n", clock_seconds(), galiot_snap_rpl_icmp6_dio_input_WARN_option_DAG.len[i]);
        printf("----------------------------------------------------------------\n");
      }
      
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #endif /* GALIOT_SNAP_RPL_ICMP6_DIO_INPUT */
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/



      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      // rpl_icmp6_dio_input_WARN_option_prefix
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #if GALIOT_SNAP_RPL_ICMP6_DIO_INPUT
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/

      if (galiot_snap_flag_rpl_icmp6_dio_input_WARN_option_prefix == 0)
      {
        //printf("\n");
        //printf("\n");
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> dio_input (WARN): OFF\n", clock_seconds());
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        //printf("\n");
      }
      else
      {
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> dio_input (WARN): ON\n", clock_seconds());
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> dio_input (WARN): SNAPS: %d\n", clock_seconds(), galiot_snap_count_rpl_icmp6_dio_input_WARN_option_prefix);
        
        if (galiot_snap_flag_countOverflow_rpl_icmp6_dio_input_WARN_option_prefix == 1)
        {
          printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> dio_input (WARN): OVERFLOW\n", clock_seconds());
        }
        
        printf("----------------------------------------------------------------\n");
      }
        
      for (int i = 0; i < GALIOT_SNAPSHOT_COUNT; i++)
      {
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> dio_input (WARN) >>> [%10lu] LAST_SNAP[%d]\n", clock_seconds(), galiot_snap_rpl_icmp6_dio_input_WARN_option_prefix.system_time[i], i);
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> dio_input (WARN): INVALID DAG PREFIX INFO, LEN: %u, DISCARD\n", clock_seconds(), galiot_snap_rpl_icmp6_dio_input_WARN_option_prefix.len[i]);
        printf("----------------------------------------------------------------\n");
      }
      
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #endif /* GALIOT_SNAP_RPL_ICMP6_DIO_INPUT */
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/



      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      // rpl_icmp6_dio_input_WARN_default
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #if GALIOT_SNAP_RPL_ICMP6_DIO_INPUT
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/

      if (galiot_snap_flag_rpl_icmp6_dio_input_WARN_default == 0)
      {
        //printf("\n");
        //printf("\n");
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> dio_input (WARN): OFF\n", clock_seconds());
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        //printf("\n");
      }
      else
      {
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> dio_input (WARN): ON\n", clock_seconds());
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> dio_input (WARN): SNAPS: %d\n", clock_seconds(), galiot_snap_count_rpl_icmp6_dio_input_WARN_default);
        
        if (galiot_snap_flag_countOverflow_rpl_icmp6_dio_input_WARN_default == 1)
        {
          printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> dio_input (WARN): OVERFLOW\n", clock_seconds());
        }
        
        printf("----------------------------------------------------------------\n");
      }
        
      for (int i = 0; i < GALIOT_SNAPSHOT_COUNT; i++)
      {
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> dio_input (WARN) >>> [%10lu] LAST_SNAP[%d]\n", clock_seconds(), galiot_snap_rpl_icmp6_dio_input_WARN_default.system_time[i], i);
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> dio_input (WARN): UNSUPPORTED IN DIO, SUBOPTION TYPE: %u, DISCARD\n", clock_seconds(), galiot_snap_rpl_icmp6_dio_input_WARN_default.type[i]);
        printf("----------------------------------------------------------------\n");
      }
      
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #endif /* GALIOT_SNAP_RPL_ICMP6_DIO_INPUT */
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/



      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      // rpl_icmp6_dio_input_INFO
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #if GALIOT_SNAP_RPL_ICMP6_DIO_INPUT
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/

      if (galiot_snap_flag_rpl_icmp6_dio_input_INFO == 0)
      {
        //printf("\n");
        //printf("\n");
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> dio_input (INFO): OFF\n", clock_seconds());
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        //printf("\n");
      }
      else
      {
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> dio_input (INFO): ON\n", clock_seconds());
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> dio_input (INFO): SNAPS: %d\n", clock_seconds(), galiot_snap_count_rpl_icmp6_dio_input_INFO);
        
        if (galiot_snap_flag_countOverflow_rpl_icmp6_dio_input_INFO == 1)
        {
          printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> dio_input (INFO): OVERFLOW\n", clock_seconds());
        }
        
        printf("----------------------------------------------------------------\n");
      }
        
      for (int i = 0; i < GALIOT_SNAPSHOT_COUNT; i++)
      {
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> dio_input (INFO) >>> [%10lu] LAST_SNAP[%d]\n", clock_seconds(), galiot_snap_rpl_icmp6_dio_input_INFO.system_time[i], i);
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> dio_input (INFO): RECEIVED A %s-DIO\n", clock_seconds(), galiot_snap_rpl_icmp6_dio_input_INFO.DIO_type[i]);
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> dio_input (INFO): FROM (6ADDR): %s\n", clock_seconds(), galiot_snap_rpl_icmp6_dio_input_INFO.DIO_from_6ADDR[i]);
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> dio_input (INFO): INSTANCE_ID: %u\n", clock_seconds(), galiot_snap_rpl_icmp6_dio_input_INFO.instance_id[i]);
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> dio_input (INFO): DAG-ID %s (6ADDR): \n", clock_seconds(), galiot_snap_rpl_icmp6_dio_input_INFO.DAG_id_6ADDR[i]);
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> dio_input (INFO): VERSION: %u\n", clock_seconds(), galiot_snap_rpl_icmp6_dio_input_INFO.version[i]);
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> dio_input (INFO): DTSN: %u\n", clock_seconds(), galiot_snap_rpl_icmp6_dio_input_INFO.dtsn[i]);
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> dio_input (INFO): RANK: %u\n", clock_seconds(), galiot_snap_rpl_icmp6_dio_input_INFO.rank[i]);
        printf("----------------------------------------------------------------\n");
      }
      
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #endif /* GALIOT_SNAP_RPL_ICMP6_DIO_INPUT */
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/



      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      // rpl_icmp6_dio_output_ERR
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #if GALIOT_SNAP_RPL_ICMP6_DIO_OUTPUT
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/

      if (galiot_snap_flag_rpl_icmp6_dio_output_ERR == 0)
      {
        //printf("\n");
        //printf("\n");
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> rpl_icmp6_dio_output (ERR): OFF\n", clock_seconds());
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        //printf("\n");
      }
      else
      {
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> rpl_icmp6_dio_output (ERR): ON\n", clock_seconds());
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> rpl_icmp6_dio_output (ERR): SNAPS: %d\n", clock_seconds(), galiot_snap_count_rpl_icmp6_dio_output_ERR);
        
        if (galiot_snap_flag_countOverflow_rpl_icmp6_dio_output_ERR == 1)
        {
          printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> rpl_icmp6_dio_output (ERR): OVERFLOW\n", clock_seconds());
        }
        
        printf("----------------------------------------------------------------\n");
      }
        
      for (int i = 0; i < GALIOT_SNAPSHOT_COUNT; i++)
      {
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> rpl_icmp6_dio_output (ERR) >>> [%10lu] LAST_SNAP[%d]\n", clock_seconds(), galiot_snap_rpl_icmp6_dio_output_ERR.system_time[i], i);
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> rpl_icmp6_dio_output (ERR): UNABLE TO SEND DIO BECAUSE OF UNSUPPORTED DAG MC, TYPE %u\n", clock_seconds(), galiot_snap_rpl_icmp6_dio_output_ERR.mc_type[i]);
        printf("----------------------------------------------------------------\n");
      }
      
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #endif /* GALIOT_SNAP_RPL_ICMP6_DIO_OUTPUT */
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/



      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      // rpl_icmp6_dio_output_INFO
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #if GALIOT_SNAP_RPL_ICMP6_DIO_OUTPUT
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/

      if (galiot_snap_flag_rpl_icmp6_dio_output_INFO == 0)
      {
        //printf("\n");
        //printf("\n");
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> rpl_icmp6_dio_output (INFO): OFF\n", clock_seconds());
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        //printf("\n");
      }
      else
      {
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> rpl_icmp6_dio_output (INFO): ON\n", clock_seconds());
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> rpl_icmp6_dio_output (INFO): SNAPS: %d\n", clock_seconds(), galiot_snap_count_rpl_icmp6_dio_output_INFO);
        
        if (galiot_snap_flag_countOverflow_rpl_icmp6_dio_output_INFO == 1)
        {
          printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> rpl_icmp6_dio_output (INFO): OVERFLOW\n", clock_seconds());
        }
        
        printf("----------------------------------------------------------------\n");
      }
        
      for (int i = 0; i < GALIOT_SNAPSHOT_COUNT; i++)
      {
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> rpl_icmp6_dio_output (INFO) >>> [%10lu] LAST_SNAP[%d]\n", clock_seconds(), galiot_snap_rpl_icmp6_dio_output_INFO.system_time[i], i);
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> rpl_icmp6_dio_output (INFO): SENDING A %s-DIO\n", clock_seconds(), galiot_snap_rpl_icmp6_dio_output_INFO.DIO_type[i]);
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> rpl_icmp6_dio_output (INFO): RANK: %u\n", clock_seconds(), galiot_snap_rpl_icmp6_dio_output_INFO.DIO_rank[i]);
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> rpl_icmp6_dio_output (INFO): TO (6ADDR): %s\n", clock_seconds(), galiot_snap_rpl_icmp6_dio_output_INFO.to_6ADDR[i]);
        printf("----------------------------------------------------------------\n");
      }
      
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #endif /* GALIOT_SNAP_RPL_ICMP6_DIO_OUTPUT */
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/



      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      // rpl_icmp6_dao_input_ERR_unknown
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #if GALIOT_SNAP_RPL_ICMP6_DAO_INPUT
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/

      if (galiot_snap_flag_rpl_icmp6_dao_input_ERR_unknown == 0)
      {
        //printf("\n");
        //printf("\n");
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> dao_input (ERR): OFF\n", clock_seconds());
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        //printf("\n");
      }
      else
      {
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> dao_input (ERR): ON\n", clock_seconds());
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> dao_input (ERR): SNAPS: %d\n", clock_seconds(), galiot_snap_count_rpl_icmp6_dao_input_ERR_unknown);
        
        if (galiot_snap_flag_countOverflow_rpl_icmp6_dao_input_ERR_unknown == 1)
        {
          printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> dao_input (ERR): OVERFLOW\n", clock_seconds());
        }
        
        printf("----------------------------------------------------------------\n");
      }
        
      for (int i = 0; i < GALIOT_SNAPSHOT_COUNT; i++)
      {
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> dao_input (ERR) >>> [%10lu] LAST_SNAP[%d]\n", clock_seconds(), galiot_snap_rpl_icmp6_dao_input_ERR_unknown.system_time[i], i);
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> dao_input (ERR): UNKNOWN RPL INSTANCE: %u, DISCARD\n", clock_seconds(), galiot_snap_rpl_icmp6_dao_input_ERR_unknown.instance_id[i]);
        printf("----------------------------------------------------------------\n");
      }
      
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #endif /* GALIOT_SNAP_RPL_ICMP6_DAO_INPUT */
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/



      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      // rpl_icmp6_dao_input_ERR_different
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #if GALIOT_SNAP_RPL_ICMP6_DAO_INPUT
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/

      if (galiot_snap_flag_rpl_icmp6_dao_input_ERR_different == 0)
      {
        //printf("\n");
        //printf("\n");
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> dao_input (ERR): OFF\n", clock_seconds());
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        //printf("\n");
      }
      else
      {
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> dao_input (ERR): ON\n", clock_seconds());
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> dao_input (ERR): SNAPS: %d\n", clock_seconds(), galiot_snap_count_rpl_icmp6_dao_input_ERR_different);
        
        if (galiot_snap_flag_countOverflow_rpl_icmp6_dao_input_ERR_different == 1)
        {
          printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> dao_input (ERR): OVERFLOW\n", clock_seconds());
        }
        
        printf("----------------------------------------------------------------\n");
      }
        
      for (int i = 0; i < GALIOT_SNAPSHOT_COUNT; i++)
      {
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> dao_input (ERR) >>> [%10lu] LAST_SNAP[%d]\n", clock_seconds(), galiot_snap_rpl_icmp6_dao_input_ERR_different.system_time[i], i);
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> dao_input (ERR): DIFFERENT DAG ID: %s, DISCARD\n", clock_seconds(), galiot_snap_rpl_icmp6_dao_input_ERR_different.DAG_id_6ADDR[i]);
        printf("----------------------------------------------------------------\n");
      }
      
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #endif /* GALIOT_SNAP_RPL_ICMP6_DAO_INPUT */
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/



      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      // rpl_icmp6_dao_input_INFO
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #if GALIOT_SNAP_RPL_ICMP6_DAO_INPUT
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/

      if (galiot_snap_flag_rpl_icmp6_dao_input_INFO == 0)
      {
        //printf("\n");
        //printf("\n");
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> dao_input (INFO): OFF\n", clock_seconds());
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        //printf("\n");
      }
      else
      {
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> dao_input (INFO): ON\n", clock_seconds());
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> dao_input (INFO): SNAPS: %d\n", clock_seconds(), galiot_snap_count_rpl_icmp6_dao_input_INFO);
        
        if (galiot_snap_flag_countOverflow_rpl_icmp6_dao_input_INFO == 1)
        {
          printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> dao_input (INFO): OVERFLOW\n", clock_seconds());
        }
        
        printf("----------------------------------------------------------------\n");
      }
        
      for (int i = 0; i < GALIOT_SNAPSHOT_COUNT; i++)
      {
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> dao_input (INFO) >>> [%10lu] LAST_SNAP[%d]\n", clock_seconds(), galiot_snap_rpl_icmp6_dao_input_INFO.system_time[i], i);
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> dao_input (INFO): RECEIVED A %s-DAO\n", clock_seconds(), galiot_snap_rpl_icmp6_dao_input_INFO.DAO_type[i]);
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> dao_input (INFO): FROM (6ADDR): %s\n", clock_seconds(), galiot_snap_rpl_icmp6_dao_input_INFO.from_6ADDR[i]);
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> dao_input (INFO): SEQNO: %u\n", clock_seconds(), galiot_snap_rpl_icmp6_dao_input_INFO.seqno[i]);
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> dao_input (INFO): LIFETIME: %u\n", clock_seconds(), galiot_snap_rpl_icmp6_dao_input_INFO.lifetime[i]);
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> dao_input (INFO): PREFIX (6ADDR): %s\n", clock_seconds(), galiot_snap_rpl_icmp6_dao_input_INFO.prefix_6ADDR[i]);
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> dao_input (INFO): PREFIX LENGTH: %u\n", clock_seconds(), galiot_snap_rpl_icmp6_dao_input_INFO.length[i]);
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> dao_input (INFO): PARENT (6ADDR): %s\n", clock_seconds(), galiot_snap_rpl_icmp6_dao_input_INFO.parent_6ADDR[i]);
        printf("----------------------------------------------------------------\n");
      }
      
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #endif /* GALIOT_SNAP_RPL_ICMP6_DAO_INPUT */
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/



      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      // rpl_icmp6_dao_output_WARN_not_in_instance
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #if GALIOT_SNAP_RPL_ICMP6_DAO_OUTPUT
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/

      if (galiot_snap_flag_rpl_icmp6_dao_output_WARN_not_in_instance == 0)
      {
        //printf("\n");
        //printf("\n");
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> rpl_icmp6_dao_output (WARN): OFF\n", clock_seconds());
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        //printf("\n");
      }
      else
      {
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> rpl_icmp6_dao_output (WARN): ON\n", clock_seconds());
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> rpl_icmp6_dao_output (WARN): SNAPS: %d\n", clock_seconds(), galiot_snap_count_rpl_icmp6_dao_output_WARN_not_in_instance);
        
        if (galiot_snap_flag_countOverflow_rpl_icmp6_dao_output_WARN_not_in_instance == 1)
        {
          printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> rpl_icmp6_dao_output (WARN): OVERFLOW\n", clock_seconds());
        }
        
        printf("----------------------------------------------------------------\n");
      }
        
      for (int i = 0; i < GALIOT_SNAPSHOT_COUNT; i++)
      {
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> rpl_icmp6_dao_output (WARN) >>> [%10lu] LAST_SNAP[%d]\n", clock_seconds(), galiot_snap_rpl_icmp6_dao_output_WARN_not_in_instance.system_time[i], i);
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> rpl_icmp6_dao_output (WARN): NOT IN AN INSTANCE, SKIP SENDING DAO\n", clock_seconds());
        printf("----------------------------------------------------------------\n");
      }
      
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #endif /* GALIOT_SNAP_RPL_ICMP6_DAO_OUTPUT */
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/



      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      // rpl_icmp6_dao_output_WARN_no_preferred_parent
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #if GALIOT_SNAP_RPL_ICMP6_DAO_OUTPUT
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/

      if (galiot_snap_flag_rpl_icmp6_dao_output_WARN_no_preferred_parent == 0)
      {
        //printf("\n");
        //printf("\n");
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> rpl_icmp6_dao_output (WARN): OFF\n", clock_seconds());
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        //printf("\n");
      }
      else
      {
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> rpl_icmp6_dao_output (WARN): ON\n", clock_seconds());
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> rpl_icmp6_dao_output (WARN): SNAPS: %d\n", clock_seconds(), galiot_snap_count_rpl_icmp6_dao_output_WARN_no_preferred_parent);
        
        if (galiot_snap_flag_countOverflow_rpl_icmp6_dao_output_WARN_no_preferred_parent == 1)
        {
          printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> rpl_icmp6_dao_output (WARN): OVERFLOW\n", clock_seconds());
        }
        
        printf("----------------------------------------------------------------\n");
      }
        
      for (int i = 0; i < GALIOT_SNAPSHOT_COUNT; i++)
      {
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> rpl_icmp6_dao_output (WARN) >>> [%10lu] LAST_SNAP[%d]\n", clock_seconds(), galiot_snap_rpl_icmp6_dao_output_WARN_no_preferred_parent.system_time[i], i);
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> rpl_icmp6_dao_output (WARN): NO PREFERRED PARENT, SKIP SENDING DAO\n", clock_seconds());
        printf("----------------------------------------------------------------\n");
      }
      
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #endif /* GALIOT_SNAP_RPL_ICMP6_DAO_OUTPUT */
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/



      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      // rpl_icmp6_dao_output_WARN_node_not_ready
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #if GALIOT_SNAP_RPL_ICMP6_DAO_OUTPUT
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/

      if (galiot_snap_flag_rpl_icmp6_dao_output_WARN_node_not_ready == 0)
      {
        //printf("\n");
        //printf("\n");
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> rpl_icmp6_dao_output (WARN): OFF\n", clock_seconds());
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        //printf("\n");
      }
      else
      {
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> rpl_icmp6_dao_output (WARN): ON\n", clock_seconds());
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> rpl_icmp6_dao_output (WARN): SNAPS: %d\n", clock_seconds(), galiot_snap_count_rpl_icmp6_dao_output_WARN_no_preferred_parent);
        
        if (galiot_snap_flag_countOverflow_rpl_icmp6_dao_output_WARN_node_not_ready == 1)
        {
          printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> rpl_icmp6_dao_output (WARN): OVERFLOW\n", clock_seconds());
        }
        
        printf("----------------------------------------------------------------\n");
      }
        
      for (int i = 0; i < GALIOT_SNAPSHOT_COUNT; i++)
      {
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> rpl_icmp6_dao_output (WARN) >>> [%10lu] LAST_SNAP[%d]\n", clock_seconds(), galiot_snap_rpl_icmp6_dao_output_WARN_node_not_ready.system_time[i], i);
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> rpl_icmp6_dao_output (WARN): NODE NOT READY TO SEND A DAO\n", clock_seconds());
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> rpl_icmp6_dao_output (WARN): PREFIX (6ADDR): %s\n", clock_seconds(), galiot_snap_rpl_icmp6_dao_output_WARN_node_not_ready.prefix_6ADDR[i]);
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> rpl_icmp6_dao_output (WARN): PARENT (6ADDR): %s\n", clock_seconds(), galiot_snap_rpl_icmp6_dao_output_WARN_node_not_ready.parent_6ADDR[i]);
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> rpl_icmp6_dao_output (WARN): MOP: %u\n", clock_seconds(), galiot_snap_rpl_icmp6_dao_output_WARN_node_not_ready.mop[i]);
        printf("----------------------------------------------------------------\n");
      }
      
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #endif /* GALIOT_SNAP_RPL_ICMP6_DAO_OUTPUT */
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/



      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      // rpl_icmp6_dao_output_INFO
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #if GALIOT_SNAP_RPL_ICMP6_DAO_OUTPUT
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/

      if (galiot_snap_flag_rpl_icmp6_dao_output_INFO == 0)
      {
        //printf("\n");
        //printf("\n");
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> rpl_icmp6_dao_output (INFO): OFF\n", clock_seconds());
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        //printf("\n");
      }
      else
      {
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> rpl_icmp6_dao_output (INFO): ON\n", clock_seconds());
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> rpl_icmp6_dao_output (INFO): SNAPS: %d\n", clock_seconds(), galiot_snap_count_rpl_icmp6_dao_output_INFO);
        
        if (galiot_snap_flag_countOverflow_rpl_icmp6_dao_output_INFO == 1)
        {
          printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> rpl_icmp6_dao_output (INFO): OVERFLOW\n", clock_seconds());
        }
        
        printf("----------------------------------------------------------------\n");
      }
        
      for (int i = 0; i < GALIOT_SNAPSHOT_COUNT; i++)
      {
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> rpl_icmp6_dao_output (INFO) >>> [%10lu] LAST_SNAP[%d]\n", clock_seconds(), galiot_snap_rpl_icmp6_dao_output_INFO.system_time[i], i);
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> rpl_icmp6_dao_output (INFO): SENDING A %s-DAO\n", clock_seconds(), galiot_snap_rpl_icmp6_dao_output_INFO.DAG_type[i]);
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> rpl_icmp6_dao_output (INFO): SEQNO: %u\n", clock_seconds(), galiot_snap_rpl_icmp6_dao_output_INFO.seqno[i]);
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> rpl_icmp6_dao_output (INFO): TX COUNT: %u\n", clock_seconds(), galiot_snap_rpl_icmp6_dao_output_INFO.tx_count[i]);
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> rpl_icmp6_dao_output (INFO): LIFETIME: %u\n", clock_seconds(), galiot_snap_rpl_icmp6_dao_output_INFO.lifetime[i]);
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> rpl_icmp6_dao_output (INFO): PREFIX (6ADDR): %s\n", clock_seconds(), galiot_snap_rpl_icmp6_dao_output_INFO.prefix_6ADDR[i]);
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> rpl_icmp6_dao_output (INFO): TO (6ADDR): %s\n", clock_seconds(), galiot_snap_rpl_icmp6_dao_output_INFO.to_6ADDR[i]);
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> rpl_icmp6_dao_output (INFO): PARENT (6ADDR): %s\n", clock_seconds(), galiot_snap_rpl_icmp6_dao_output_INFO.parent_6ADDR[i]);
        printf("----------------------------------------------------------------\n");
      }
      
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #endif /* GALIOT_SNAP_RPL_ICMP6_DAO_OUTPUT */
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/



      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      // rpl_icmp6_dao_ack_input_ERR
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #if GALIOT_SNAP_RPL_ICMP6_DAO_ACK_INPUT
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/

      if (galiot_snap_flag_rpl_icmp6_dao_ack_input_ERR == 0)
      {
        //printf("\n");
        //printf("\n");
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> dao_ack_input (ERR): OFF\n", clock_seconds());
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        //printf("\n");
      }
      else
      {
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> dao_ack_input (ERR): ON\n", clock_seconds());
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> dao_ack_input (ERR): SNAPS: %d\n", clock_seconds(), galiot_snap_count_rpl_icmp6_dao_ack_input_ERR);
        
        if (galiot_snap_flag_countOverflow_rpl_icmp6_dao_ack_input_ERR == 1)
        {
          printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> dao_ack_input (ERR): OVERFLOW\n", clock_seconds());
        }
        
        printf("----------------------------------------------------------------\n");
      }
        
      for (int i = 0; i < GALIOT_SNAPSHOT_COUNT; i++)
      {
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> dao_ack_input (ERR) >>> [%10lu] LAST_SNAP[%d]\n", clock_seconds(), galiot_snap_rpl_icmp6_dao_ack_input_ERR.system_time[i], i);
        printf("----------------------------------------------------------------\n");
      }
      
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #endif /* GALIOT_SNAP_RPL_ICMP6_DAO_ACK_INPUT */
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/



      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      // rpl_icmp6_dao_ack_input_INFO
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #if GALIOT_SNAP_RPL_ICMP6_DAO_ACK_INPUT
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/

      if (galiot_snap_flag_rpl_icmp6_dao_ack_input_INFO == 0)
      {
        //printf("\n");
        //printf("\n");
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> dao_ack_input (INFO): OFF\n", clock_seconds());
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        //printf("\n");
      }
      else
      {
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> dao_ack_input (INFO): ON\n", clock_seconds());
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> dao_ack_input (INFO): SNAPS: %d\n", clock_seconds(), galiot_snap_count_rpl_icmp6_dao_ack_input_INFO);
        
        if (galiot_snap_flag_countOverflow_rpl_icmp6_dao_ack_input_INFO == 1)
        {
          printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> dao_ack_input (INFO): OVERFLOW\n", clock_seconds());
        }
        
        printf("----------------------------------------------------------------\n");
      }
        
      for (int i = 0; i < GALIOT_SNAPSHOT_COUNT; i++)
      {
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> dao_ack_input (INFO) >>> [%10lu] LAST_SNAP[%d]\n", clock_seconds(), galiot_snap_rpl_icmp6_dao_ack_input_INFO.system_time[i], i);
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> dao_ack_input (INFO): RECEIVED A DAO-%s\n", clock_seconds(), galiot_snap_rpl_icmp6_dao_ack_input_INFO.DAO_response[i]);
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> dao_ack_input (INFO): SEQUENCE: %d\n", clock_seconds(), galiot_snap_rpl_icmp6_dao_ack_input_INFO.sequence[i]);
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> dao_ack_input (INFO): DAO LAST SEQNO (%d, %d)\n", clock_seconds(), galiot_snap_rpl_icmp6_dao_ack_input_INFO.dao_last_seqno1[i], galiot_snap_rpl_icmp6_dao_ack_input_INFO.dao_last_seqno2[i]);
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> dao_ack_input (INFO): STATUS: %d\n", clock_seconds(), galiot_snap_rpl_icmp6_dao_ack_input_INFO.status[i]);
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> dao_ack_input (INFO): FROM (6ADDR): %s\n", clock_seconds(), galiot_snap_rpl_icmp6_dao_ack_input_INFO.from_6ADDR[i]);
        printf("----------------------------------------------------------------\n");
      }
      
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #endif /* GALIOT_SNAP_RPL_ICMP6_DAO_ACK_INPUT */
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/



      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      // rpl_icmp6_dao_ack_output_INFO
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #if GALIOT_SNAP_RPL_ICMP6_DAO_ACK_OUTPUT
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/

      if (galiot_snap_flag_rpl_icmp6_dao_ack_output_INFO == 0)
      {
        //printf("\n");
        //printf("\n");
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> rpl_icmp6_dao_ack_output (INFO): OFF\n", clock_seconds());
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        //printf("\n");
      }
      else
      {
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> rpl_icmp6_dao_ack_output (INFO): ON\n", clock_seconds());
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> rpl_icmp6_dao_ack_output (INFO): SNAPS: %d\n", clock_seconds(), galiot_snap_count_rpl_icmp6_dao_ack_output_INFO);
        
        if (galiot_snap_flag_countOverflow_rpl_icmp6_dao_ack_output_INFO == 1)
        {
          printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> rpl_icmp6_dao_ack_output (INFO): OVERFLOW\n", clock_seconds());
        }
        
        printf("----------------------------------------------------------------\n");
      }
        
      for (int i = 0; i < GALIOT_SNAPSHOT_COUNT; i++)
      {
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> rpl_icmp6_dao_ack_output (INFO) >>> [%10lu] LAST_SNAP[%d]\n", clock_seconds(), galiot_snap_rpl_icmp6_dao_ack_output_INFO.system_time[i], i);
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> rpl_icmp6_dao_ack_output (INFO): SENDING A DAO-%s\n", clock_seconds(), galiot_snap_rpl_icmp6_dao_ack_output_INFO.DAO_response[i]);
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> rpl_icmp6_dao_ack_output (INFO): SEQNO: %d\n", clock_seconds(), galiot_snap_rpl_icmp6_dao_ack_output_INFO.seqno[i]);
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> rpl_icmp6_dao_ack_output (INFO): TO (6ADDR): %s\n", clock_seconds(), galiot_snap_rpl_icmp6_dao_ack_output_INFO.to_6ADDR[i]);
        printf("(galiot) >>> [%10lu] >>> rpl_icmp6 >>> rpl_icmp6_dao_ack_output (INFO): STATUS: %d\n", clock_seconds(), galiot_snap_rpl_icmp6_dao_ack_output_INFO.status[i]);
        printf("----------------------------------------------------------------\n");
      }
      
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #endif /* GALIOT_SNAP_RPL_ICMP6_DAO_ACK_OUTPUT */
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/



      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    #endif /* GALIOT_FUNCTIONALITY */
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/




























    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    #ifdef GALIOT_FUNCTIONALITY
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      // /os/net/routing/rpl-lite/rpl-mrhof.c
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/

      
      //printf("\n");
      printf("(galiot) >>> rpl-mrhof\n");
      //printf("\n");


      
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      // rpl_mrhof_reset_INFO
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #if GALIOT_SNAP_RPL_MRHOF_RESET
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/

      if (galiot_snap_flag_rpl_mrhof_reset_INFO == 0)
      {
        //printf("\n");
        //printf("\n");
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        printf("(galiot) >>> [%10lu] >>> rpl_mrhof >>> reset (INFO): OFF\n", clock_seconds());
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        //printf("\n");
      }
      else
      {
        printf("(galiot) >>> [%10lu] >>> rpl_mrhof >>> reset (INFO): ON\n", clock_seconds());
        printf("(galiot) >>> [%10lu] >>> rpl_mrhof >>> reset (INFO): SNAPS: %d\n", clock_seconds(), galiot_snap_count_rpl_mrhof_reset_INFO);
        
        if (galiot_snap_flag_countOverflow_rpl_mrhof_reset_INFO == 1)
        {
          printf("(galiot) >>> [%10lu] >>> rpl_mrhof >>> reset (INFO): OVERFLOW\n", clock_seconds());
        }
        
        printf("----------------------------------------------------------------\n");
      }
        
      for (int i = 0; i < GALIOT_SNAPSHOT_COUNT; i++)
      {
        printf("(galiot) >>> [%10lu] >>> rpl_mrhof >>> reset (INFO) >>> [%10lu] LAST_SNAP[%d]\n", clock_seconds(), galiot_snap_rpl_mrhof_reset_INFO.system_time[i], i);
        printf("(galiot) >>> [%10lu] >>> rpl_mrhof >>> reset (INFO): RESET MRHOF\n", clock_seconds());
        printf("----------------------------------------------------------------\n");
      }
      
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #endif /* GALIOT_SNAP_RPL_MRHOF_RESET */
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/



      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      // rpl_mrhof_update_metric_container_WARN_used
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #if GALIOT_SNAP_RPL_MRHOF_UPDATE_METRIC_CONTAINER
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/

      if (galiot_snap_flag_rpl_mrhof_update_metric_container_WARN_used == 0)
      {
        //printf("\n");
        //printf("\n");
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        printf("(galiot) >>> [%10lu] >>> rpl_mrhof >>> update_metric_container (WARN): OFF\n", clock_seconds());
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        //printf("\n");
      }
      else
      {
        printf("(galiot) >>> [%10lu] >>> rpl_mrhof >>> update_metric_container (WARN): ON\n", clock_seconds());
        printf("(galiot) >>> [%10lu] >>> rpl_mrhof >>> update_metric_container (WARN): SNAPS: %d\n", clock_seconds(), galiot_snap_count_rpl_mrhof_update_metric_container_WARN_used);
        
        if (galiot_snap_flag_countOverflow_rpl_mrhof_update_metric_container_WARN_used == 1)
        {
          printf("(galiot) >>> [%10lu] >>> rpl_mrhof >>> update_metric_container (WARN): OVERFLOW\n", clock_seconds());
        }
        
        printf("----------------------------------------------------------------\n");
      }
        
      for (int i = 0; i < GALIOT_SNAPSHOT_COUNT; i++)
      {
        printf("(galiot) >>> [%10lu] >>> rpl_mrhof >>> update_metric_container (WARN) >>> [%10lu] LAST_SNAP[%d]\n", clock_seconds(), galiot_snap_rpl_mrhof_update_metric_container_WARN_used.system_time[i], i);
        printf("(galiot) >>> [%10lu] >>> rpl_mrhof >>> update_metric_container (WARN): CANNOT UPDATE THE METRIC CONTAINER WHEN NOT JOINED\n", clock_seconds());
        printf("----------------------------------------------------------------\n");
      }
      
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #endif /* GALIOT_SNAP_RPL_MRHOF_UPDATE_METRIC_CONTAINER */
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/


      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      // rpl_mrhof_update_metric_container_WARN_mc_type
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #if GALIOT_SNAP_RPL_MRHOF_UPDATE_METRIC_CONTAINER
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/

      if (galiot_snap_flag_rpl_mrhof_update_metric_container_WARN_mc_type == 0)
      {
        //printf("\n");
        //printf("\n");
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        printf("(galiot) >>> [%10lu] >>> rpl_mrhof >>> update_metric_container (WARN): OFF\n", clock_seconds());
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        //printf("\n");
      }
      else
      {
        printf("(galiot) >>> [%10lu] >>> rpl_mrhof >>> update_metric_container (WARN): ON\n", clock_seconds());
        printf("(galiot) >>> [%10lu] >>> rpl_mrhof >>> update_metric_container (WARN): SNAPS: %d\n", clock_seconds(), galiot_snap_count_rpl_mrhof_update_metric_container_WARN_mc_type);
        
        if (galiot_snap_flag_countOverflow_rpl_mrhof_update_metric_container_WARN_mc_type == 1)
        {
          printf("(galiot) >>> [%10lu] >>> rpl_mrhof >>> update_metric_container (WARN): OVERFLOW\n", clock_seconds());
        }
        
        printf("----------------------------------------------------------------\n");
      }
        
      for (int i = 0; i < GALIOT_SNAPSHOT_COUNT; i++)
      {
        printf("(galiot) >>> [%10lu] >>> rpl_mrhof >>> update_metric_container (WARN) >>> [%10lu] LAST_SNAP[%d]\n", clock_seconds(), galiot_snap_rpl_mrhof_update_metric_container_WARN_mc_type.system_time[i], i);
        printf("(galiot) >>> [%10lu] >>> rpl_mrhof >>> update_metric_container (WARN): NON SUPPORTED MC:%u\n", clock_seconds(), galiot_snap_rpl_mrhof_update_metric_container_WARN_mc_type.mc_type[i]);
        printf("----------------------------------------------------------------\n");
      }
      
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #endif /* GALIOT_SNAP_RPL_MRHOF_UPDATE_METRIC_CONTAINER */
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/


      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    #endif /* GALIOT_FUNCTIONALITY */
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/























    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    #ifdef GALIOT_FUNCTIONALITY
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      // /os/net/routing/rpl-lite/rpl-nbr-policy.c
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/

      
      //printf("\n");
      printf("(galiot) >>> rpl-nbr-policy\n");
      //printf("\n");


      
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      // rpl_nbr_policy_find_removable_dio_WARN
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #if GALIOT_SNAP_RPL_NBR_POLICY_FIND_REMOVABLE_DIO
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/

      if (galiot_snap_flag_rpl_nbr_policy_find_removable_dio_WARN == 0)
      {
        //printf("\n");
        //printf("\n");
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        printf("(galiot) >>> [%10lu] >>> rpl_nbr_policy >>> find_removable_dio (WARN): OFF\n", clock_seconds());
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        //printf("\n");
      }
      else
      {
        printf("(galiot) >>> [%10lu] >>> rpl_nbr_policy >>> find_removable_dio (WARN): ON\n", clock_seconds());
        printf("(galiot) >>> [%10lu] >>> rpl_nbr_policy >>> find_removable_dio (WARN): SNAPS: %d\n", clock_seconds(), galiot_snap_count_rpl_nbr_policy_find_removable_dio_WARN);
        
        if (galiot_snap_flag_countOverflow_rpl_nbr_policy_find_removable_dio_WARN == 1)
        {
          printf("(galiot) >>> [%10lu] >>> rpl_nbr_policy >>> find_removable_dio (WARN): OVERFLOW\n", clock_seconds());
        }
        
        printf("----------------------------------------------------------------\n");
      }
        
      for (int i = 0; i < GALIOT_SNAPSHOT_COUNT; i++)
      {
        printf("(galiot) >>> [%10lu] >>> rpl_nbr_policy >>> find_removable_dio (WARN) >>> [%10lu] LAST_SNAP[%d]\n", clock_seconds(), galiot_snap_rpl_nbr_policy_find_removable_dio_WARN.system_time[i], i);
        printf("(galiot) >>> [%10lu] >>> rpl_nbr_policy >>> find_removable_dio (WARN): DID NOT FIND INSTANCE ID: %d\n", clock_seconds(), galiot_snap_rpl_nbr_policy_find_removable_dio_WARN.instance_ID[i]);
        printf("----------------------------------------------------------------\n");
      }
      
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #endif /* GALIOT_SNAP_RPL_NBR_POLICY_FIND_REMOVABLE_DIO */
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/


      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    #endif /* GALIOT_FUNCTIONALITY */
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/


























    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    #ifdef GALIOT_FUNCTIONALITY
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      // /os/net/routing/rpl-lite/rpl-neighbor.c
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/

      
      //printf("\n");
      printf("(galiot) >>> rpl-neighbor\n");
      //printf("\n");


      
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      // rpl_neighbor_print_list_INFO_ownState
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #if GALIOT_SNAP_RPL_NEIGHBOR_PRINT_LIST_OWNSTATE
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/

      if (galiot_snap_flag_rpl_neighbor_print_list_INFO_ownState == 0)
      {
        //printf("\n");
        //printf("\n");
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        printf("(galiot) >>> [%10lu] >>> rpl-neighbor >>> rpl_neighbor_print_list (INFO) own state: OFF\n", clock_seconds());
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        //printf("\n");
      }
      else
      {
        printf("(galiot) >>> [%10lu] >>> rpl-neighbor >>> rpl_neighbor_print_list (INFO) own state: ON\n", clock_seconds());
        printf("(galiot) >>> [%10lu] >>> rpl-neighbor >>> rpl_neighbor_print_list (INFO) own state: SNAPS: %d\n", clock_seconds(), galiot_snap_count_rpl_neighbor_print_list_INFO_ownState);
        
        if (galiot_snap_flag_countOverflow_rpl_neighbor_print_list_INFO_ownState == 1)
        {
          printf("(galiot) >>> [%10lu] >>> rpl-neighbor >>> rpl_neighbor_print_list (INFO) own state: OVERFLOW\n", clock_seconds());
        }
        
        printf("----------------------------------------------------------------\n");
      }
        
      for (int i = 0; i < GALIOT_SNAPSHOT_COUNT; i++)
      {
        printf("(galiot) >>> [%10lu] >>> rpl-neighbor >>> rpl_neighbor_print_list (INFO) own state >>> [%10lu] LAST_SNAP[%d]\n", clock_seconds(), galiot_snap_rpl_neighbor_print_list_INFO_ownState.system_time[i], i);
        printf("(galiot) >>> [%10lu] >>> rpl-neighbor >>> rpl_neighbor_print_list (INFO) own state: ADDR: %s\n", clock_seconds(), galiot_snap_rpl_neighbor_print_list_INFO_ownState.addr[i]);
        printf("(galiot) >>> [%10lu] >>> rpl-neighbor >>> rpl_neighbor_print_list (INFO) own state: DAG STATE: %s\n", clock_seconds(), galiot_snap_rpl_neighbor_print_list_INFO_ownState.DAG_state[i]);
        printf("(galiot) >>> [%10lu] >>> rpl-neighbor >>> rpl_neighbor_print_list (INFO) own state: MOP: %u\n", clock_seconds(), galiot_snap_rpl_neighbor_print_list_INFO_ownState.MOP[i]);
        printf("(galiot) >>> [%10lu] >>> rpl-neighbor >>> rpl_neighbor_print_list (INFO) own state: OCP: %u\n", clock_seconds(), galiot_snap_rpl_neighbor_print_list_INFO_ownState.OCP[i]);
        printf("(galiot) >>> [%10lu] >>> rpl-neighbor >>> rpl_neighbor_print_list (INFO) own state: RANK: %u\n", clock_seconds(), galiot_snap_rpl_neighbor_print_list_INFO_ownState.rank[i]);
        printf("(galiot) >>> [%10lu] >>> rpl-neighbor >>> rpl_neighbor_print_list (INFO) own state: MAX RANK: %u\n", clock_seconds(), galiot_snap_rpl_neighbor_print_list_INFO_ownState.max_rank[i]);
        printf("(galiot) >>> [%10lu] >>> rpl-neighbor >>> rpl_neighbor_print_list (INFO) own state: DIOINT: DIOINT: %u\n", clock_seconds(), galiot_snap_rpl_neighbor_print_list_INFO_ownState.dioint[i]);
        printf("(galiot) >>> [%10lu] >>> rpl-neighbor >>> rpl_neighbor_print_list (INFO) own state: NBR COUNT: %u\n", clock_seconds(), galiot_snap_rpl_neighbor_print_list_INFO_ownState.nbr_count[i]);
        printf("(galiot) >>> [%10lu] >>> rpl-neighbor >>> rpl_neighbor_print_list (INFO) own state: TRIGGER: %s\n", clock_seconds(), galiot_snap_rpl_neighbor_print_list_INFO_ownState.trigger[i]);
        printf("----------------------------------------------------------------\n");
      }
      
      // DAG Mode of Operation (rpl-const.h)
      // RPL_MOP_NO_DOWNWARD_ROUTES      0
      // RPL_MOP_NON_STORING             1
      // RPL_MOP_STORING_NO_MULTICAST    2
      // RPL_MOP_STORING_MULTICAST       3

      // Objective Code Point (OCP) (https://www.iana.org/assignments/rpl/rpl.xhtml#ocp)
      // 0	A basic Objective Function that relies only on the objects that are defined in [RFC6550].	[RFC6552]
      // 1	Minimum Rank with Hysteresis Objective Function (MRHOF) [RFC6719]

      // The current rank
      // The maximum rank (rpl-neigbor.c)
      // current DIO interval (rpl-types.h)
      // returns the number of nodes in the RPL neighbor table
      // data fill explanation (why the data have been acquired)

      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #endif /* GALIOT_SNAP_RPL_NEIGHBOR_PRINT_LIST_OWNSTATE */
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/



      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      // rpl_neighbor_print_list_DBG_nbr
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #if GALIOT_SNAP_RPL_NEIGHBOR_PRINT_LIST_NBR
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/

      for (int j = 0; j <= galiot_arrayIndex_rpl_neighbor; j++)
      {
        
        if (galiot_snap_flag_rpl_neighbor_print_list_DBG_nbr[j] == 0)
        {
          //printf("\n");
          //printf("\n");
          //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
          printf("(galiot) >>> [%10lu] >>> rpl-neighbor >>> rpl_neighbor_print_list (DBG) nbr %d/%d: OFF\n", clock_seconds(), j+1, galiot_arrayIndex_rpl_neighbor+1);
          //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
          //printf("\n");
        }
        else
        {
          printf("(galiot) >>> [%10lu] >>> rpl-neighbor >>> rpl_neighbor_print_list (DBG) nbr %d/%d: ON\n", clock_seconds(), j+1, galiot_arrayIndex_rpl_neighbor+1);
          printf("(galiot) >>> [%10lu] >>> rpl-neighbor >>> rpl_neighbor_print_list (DBG) nbr %d/%d: SNAPS: %d\n", clock_seconds(), j+1, galiot_arrayIndex_rpl_neighbor+1, galiot_snap_count_rpl_neighbor_print_list_DBG_nbr[j]);
        
          if (galiot_snap_flag_countOverflow_rpl_neighbor_print_list_DBG_nbr[j] == 1)
          {
            printf("(galiot) >>> [%10lu] >>> rpl-neighbor >>> rpl_neighbor_print_list (DBG) nbr %d/%d: OVERFLOW\n", clock_seconds(), j+1, galiot_arrayIndex_rpl_neighbor+1);
          }
        
          //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
          //printf("\n");
        }

        for (int i = 0; i < GALIOT_SNAPSHOT_COUNT; i++)
        {
          printf("(galiot) >>> [%10lu] >>> rpl-neighbor >>> rpl_neighbor_print_list (DBG) nbr %d/%d: >>> [%10lu] LAST_SNAP[%d]\n", clock_seconds(), j+1, galiot_arrayIndex_rpl_neighbor+1, galiot_snap_rpl_neighbor_print_list_DBG_nbr[j].system_time[i], i);
          printf("(galiot) >>> [%10lu] >>> rpl-neighbor >>> rpl_neighbor_print_list (DBG) nbr %d/%d: IPv6 LINK LOCAL ADDRESS: %s\n", clock_seconds(), j+1, galiot_arrayIndex_rpl_neighbor+1,galiot_snap_rpl_neighbor_print_list_DBG_nbr[j].lladdr[i]);
          printf("(galiot) >>> [%10lu] >>> rpl-neighbor >>> rpl_neighbor_print_list (DBG) nbr %d/%d: RANK: %u\n", clock_seconds(), j+1, galiot_arrayIndex_rpl_neighbor+1, galiot_snap_rpl_neighbor_print_list_DBG_nbr[j].rank[i]);
          printf("(galiot) >>> [%10lu] >>> rpl-neighbor >>> rpl_neighbor_print_list (DBG) nbr %d/%d: LINK METRIC: %u\n", clock_seconds(), j+1, galiot_arrayIndex_rpl_neighbor+1, galiot_snap_rpl_neighbor_print_list_DBG_nbr[j].statsFreshness[i]);
          printf("(galiot) >>> [%10lu] >>> rpl-neighbor >>> rpl_neighbor_print_list (DBG) nbr %d/%d: RANK IF GIVEN PARENT SELECTED AS PREFERED: %u\n", clock_seconds(), j+1, galiot_arrayIndex_rpl_neighbor+1, galiot_snap_rpl_neighbor_print_list_DBG_nbr[j].rankIfParent[i]);
          printf("(galiot) >>> [%10lu] >>> rpl-neighbor >>> rpl_neighbor_print_list (DBG) nbr %d/%d: FRESHNESS OF THE STATISTICS: %u\n", clock_seconds(), j+1, galiot_arrayIndex_rpl_neighbor+1, galiot_snap_rpl_neighbor_print_list_DBG_nbr[j].statsFreshness[i]);
          printf("(galiot) >>> [%10lu] >>> rpl-neighbor >>> rpl_neighbor_print_list (DBG) nbr %d/%d: RANK IF CONFIGURED ROOT RANK: %c\n", clock_seconds(), j+1, galiot_arrayIndex_rpl_neighbor+1, galiot_snap_rpl_neighbor_print_list_DBG_nbr[j].rankRoot[i]);
          printf("(galiot) >>> [%10lu] >>> rpl-neighbor >>> rpl_neighbor_print_list (DBG) nbr %d/%d: BEST PARENT: %c\n", clock_seconds(), j+1, galiot_arrayIndex_rpl_neighbor+1, galiot_snap_rpl_neighbor_print_list_DBG_nbr[j].bestParent[i]);
          printf("(galiot) >>> [%10lu] >>> rpl-neighbor >>> rpl_neighbor_print_list (DBG) nbr %d/%d: ACCEPTABLE RANK IF GIVEN PARENT SELECTED AS PREFERED && PARENT CAPABLE: %c\n", clock_seconds(), j+1, galiot_arrayIndex_rpl_neighbor+1, galiot_snap_rpl_neighbor_print_list_DBG_nbr[j].acceptableRankAndParent[i]);
          printf("(galiot) >>> [%10lu] >>> rpl-neighbor >>> rpl_neighbor_print_list (DBG) nbr %d/%d: STATISTICS IS FRESH: %c\n", clock_seconds(), j+1, galiot_arrayIndex_rpl_neighbor+1, galiot_snap_rpl_neighbor_print_list_DBG_nbr[j].statsIsFresh[i]);
          printf("(galiot) >>> [%10lu] >>> rpl-neighbor >>> rpl_neighbor_print_list (DBG) nbr %d/%d: LAST TX TIMESTAMP (MINUTES): %u\n", clock_seconds(), j+1, galiot_arrayIndex_rpl_neighbor+1, galiot_snap_rpl_neighbor_print_list_DBG_nbr[j].lastTx[i]);
          printf("----------------------------------------------------------------\n");
        }

        // Returns a neighbor's link metric (return The link metric if any, 0xffff otherwise)
        // Returns our rank if selecting a given parent as preferred parent (return The resulting rank if any, RPL_INFINITE_RANK otherwise)
        // Freshness of the statistics
        // is the neighbors rank equal to ROOT_RANK
        // is the neighbor the best parent
        // (acceptable_rank(rpl_neighbor_rank_via_nbr(nbr)) && rpl_neighbor_is_acceptable_parent(nbr) ? a : ' '
        // link stats are fresh
        // Last Tx timestamp
      }

      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #endif /* GALIOT_SNAP_RPL_NEIGHBOR_PRINT_LIST_NBR */
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/



      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      // rpl_neighbor_set_preferred_parent
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #if GALIOT_SNAP_RPL_NEIGHBOR_SET_PREFERED_PARENT
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/

      if (galiot_snap_flag_rpl_neighbor_set_preferred_parent_INFO == 0)
      {
        //printf("\n");
        //printf("\n");
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        printf("(galiot) >>> [%10lu] >>> rpl-neighbor >>> rpl_neighbor_set_preferred_parent (INFO): OFF\n", clock_seconds());
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        //printf("\n");
      }
      else
      {
        printf("(galiot) >>> [%10lu] >>> rpl-neighbor >>> rpl_neighbor_set_preferred_parent (INFO): ON\n", clock_seconds());
        printf("(galiot) >>> [%10lu] >>> rpl-neighbor >>> rpl_neighbor_set_preferred_parent (INFO): SNAPS: %d\n", clock_seconds(), galiot_snap_count_rpl_neighbor_set_preferred_parent_INFO);
        
        if (galiot_snap_flag_countOverflow_rpl_neighbor_set_preferred_parent_INFO == 1)
        {
          printf("(galiot) >>> [%10lu] >>> rpl-neighbor >>> rpl_neighbor_set_preferred_parent (INFO): OVERFLOW\n", clock_seconds());
        }
        
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        //printf("\n");
      }

      for (int i = 0; i < GALIOT_SNAPSHOT_COUNT; i++)
      {
        printf("(galiot) >>> [%10lu] >>> rpl-neighbor >>> rpl_neighbor_set_preferred_parent (INFO) >>> [%10lu] LAST_SNAP[%d]\n", clock_seconds(), galiot_snap_rpl_neighbor_set_preferred_parent_INFO.system_time[i], i);
        printf("(galiot) >>> [%10lu] >>> rpl-neighbor >>> rpl_neighbor_set_preferred_parent (INFO): PAREMT SWITCH FROM ---> %s\n", clock_seconds(), galiot_snap_rpl_neighbor_set_preferred_parent_INFO.lastParentSwitch_from[i]);
        printf("(galiot) >>> [%10lu] >>> rpl-neighbor >>> rpl_neighbor_set_preferred_parent (INFO): PARENT SWITCH   TO <--- %s\n", clock_seconds(), galiot_snap_rpl_neighbor_set_preferred_parent_INFO.lastParentSwitch_to[i]);
        printf("----------------------------------------------------------------\n");
      }

      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #endif /* GALIOT_SNAP_RPL_NEIGHBOR_SET_PREFERED_PARENT */
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      
      
      
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      // rpl_neighbor_remove_all
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #if GALIOT_SNAP_RPL_NEIGHBOR_REMOVE_ALL
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/

      if (galiot_snap_flag_rpl_neighbor_remove_all_INFO == 0)
      {
        //printf("\n");
        //printf("\n");
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        printf("(galiot) >>> [%10lu] >>> rpl-neighbor >>> rpl_neighbor_remove_all (INFO): OFF\n", clock_seconds());
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        //printf("\n");
      }
      else
      {
        printf("(galiot) >>> [%10lu] >>> rpl-neighbor >>> rpl_neighbor_remove_all (INFO): ON\n", clock_seconds());
        printf("(galiot) >>> [%10lu] >>> rpl-neighbor >>> rpl_neighbor_remove_all (INFO): SNAPS: %d\n", clock_seconds(), galiot_snap_count_rpl_neighbor_remove_all_INFO);
        
        if (galiot_snap_flag_countOverflow_rpl_neighbor_remove_all_INFO == 1)
        {
          printf("(galiot) >>> [%10lu] >>> rpl-neighbor >>> rpl_neighbor_remove_all (INFO): OVERFLOW\n", clock_seconds());
        }
        
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        //printf("\n");
      }

      for (int i = 0; i < GALIOT_SNAPSHOT_COUNT; i++)
      {
        printf("(galiot) >>> [%10lu] >>> rpl-neighbor >>> rpl_neighbor_remove_all (INFO) >>> [%10lu] LAST_SNAP[%d]\n", clock_seconds(), galiot_snap_rpl_neighbor_remove_all_INFO.system_time[i], i);
        printf("(galiot) >>> [%10lu] >>> rpl-neighbor >>> rpl_neighbor_remove_all (INFO): REMOVING ALL NEIGHBORS\n", clock_seconds());
        printf("----------------------------------------------------------------\n");
      }

      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #endif /* GALIOT_SNAP_RPL_NEIGHBOR_REMOVE_ALL */
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      
      
      
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      // rpl_neighbor_select_best
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #if GALIOT_SNAP_RPL_NEIGHBOR_SELECT_BEST
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/

      if (galiot_snap_flag_rpl_neighbor_select_best_INFO == 0)
      {
        //printf("\n");
        //printf("\n");
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        printf("(galiot) >>> [%10lu] >>> rpl-neighbor >>> rpl_neighbor_select_best (INFO): OFF\n", clock_seconds());
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        //printf("\n");
      }
      else
      {
        printf("(galiot) >>> [%10lu] >>> rpl-neighbor >>> rpl_neighbor_select_best (INFO): ON\n", clock_seconds());
        printf("(galiot) >>> [%10lu] >>> rpl-neighbor >>> rpl_neighbor_select_best (INFO): SNAPS: %d\n", clock_seconds(), galiot_snap_count_rpl_neighbor_select_best_INFO);
        
        if (galiot_snap_flag_countOverflow_rpl_neighbor_select_best_INFO == 1)
        {
          printf("(galiot) >>> [%10lu] >>> rpl-neighbor >>> rpl_neighbor_select_best (INFO): OVERFLOW\n", clock_seconds());
        }
        
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        //printf("\n");
      }

      for (int i = 0; i < GALIOT_SNAPSHOT_COUNT; i++)
      {
        printf("(galiot) >>> [%10lu] >>> rpl-neighbor >>> rpl_neighbor_select_best (INFO) >>> [%10lu] LAST_SNAP[%d]\n", clock_seconds(), galiot_snap_rpl_neighbor_select_best_INFO.system_time[i], i);
        printf("(galiot) >>> [%10lu] >>> rpl-neighbor >>> rpl_neighbor_select_best (INFO): BEST PARENT NOT FRESH, SCHEDULE URGENT PROBING TO <--- %s\n", clock_seconds(), galiot_snap_rpl_neighbor_select_best_INFO.scheduleUrgentProbing_to[i]);
        printf("----------------------------------------------------------------\n");
      }

      // best parent is not fresh, schedule urgent probing to ADDR

      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #endif /* GALIOT_SNAP_RPL_NEIGHBOR_SELECT_BEST */
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/





      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    #endif /* GALIOT_FUNCTIONALITY */
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    


















    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    #ifdef GALIOT_FUNCTIONALITY
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      // /os/net/routing/rpl-lite/rpl-of0.c
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/

      
      //printf("\n");
      printf("(galiot) >>> rpl-of0\n");
      //printf("\n");


      
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      // rpl_of0_reset_INFO
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #if GALIOT_SNAP_RPL_OF0
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/

      if (galiot_snap_flag_rpl_of0_reset_INFO == 0)
      {
        //printf("\n");
        //printf("\n");
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        printf("(galiot) >>> [%10lu] >>> rpl_of0 >>> reset (INFO): OFF\n", clock_seconds());
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        //printf("\n");
      }
      else
      {
        printf("(galiot) >>> [%10lu] >>> rpl_of0 >>> reset (INFO): ON\n", clock_seconds());
        printf("(galiot) >>> [%10lu] >>> rpl_of0 >>> reset (INFO): SNAPS: %d\n", clock_seconds(), galiot_snap_count_rpl_of0_reset_INFO);
        
        if (galiot_snap_flag_countOverflow_rpl_of0_reset_INFO == 1)
        {
          printf("(galiot) >>> [%10lu] >>> rpl_of0 >>> reset (INFO): OVERFLOW\n", clock_seconds());
        }
        
        printf("----------------------------------------------------------------\n");
      }
        
      for (int i = 0; i < GALIOT_SNAPSHOT_COUNT; i++)
      {
        printf("(galiot) >>> [%10lu] >>> rpl_of0 >>> reset (INFO) >>> [%10lu] LAST_SNAP[%d]\n", clock_seconds(), galiot_snap_rpl_of0_reset_INFO.system_time[i], i);
        printf("(galiot) >>> [%10lu] >>> rpl_of0 >>> reset (INFO): RESET OF0\n", clock_seconds());
        printf("----------------------------------------------------------------\n");
      }
      
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #endif /* GALIOT_SNAP_RPL_OF0 */
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/


      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    #endif /* GALIOT_FUNCTIONALITY */
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/





















    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    #ifdef GALIOT_FUNCTIONALITY
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      // /os/net/routing/rpl-lite/rpl-timers.c
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/

      
      //printf("\n");
      printf("(galiot) >>> rpl-timers\n");
      //printf("\n");


      
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      // rpl_timers_dio_reset_INFO
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #if GALIOT_SNAP_RPL_TIMERS_DIO_RESET
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/

      if (galiot_snap_flag_rpl_timers_dio_reset_INFO == 0)
      {
        //printf("\n");
        //printf("\n");
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        printf("(galiot) >>> [%10lu] >>> rpl_timers >>> rpl_timers_dio_reset (INFO): OFF\n", clock_seconds());
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        //printf("\n");
      }
      else
      {
        printf("(galiot) >>> [%10lu] >>> rpl_timers >>> rpl_timers_dio_reset (INFO): ON\n", clock_seconds());
        printf("(galiot) >>> [%10lu] >>> rpl_timers >>> rpl_timers_dio_reset (INFO): SNAPS: %d\n", clock_seconds(), galiot_snap_count_rpl_timers_dio_reset_INFO);
        
        if (galiot_snap_flag_countOverflow_rpl_timers_dio_reset_INFO == 1)
        {
          printf("(galiot) >>> [%10lu] >>> rpl_timers >>> rpl_timers_dio_reset (INFO): OVERFLOW\n", clock_seconds());
        }
        
        printf("----------------------------------------------------------------\n");
      }
        
      for (int i = 0; i < GALIOT_SNAPSHOT_COUNT; i++)
      {
        printf("(galiot) >>> [%10lu] >>> rpl_timers >>> rpl_timers_dio_reset (INFO) >>> [%10lu] LAST_SNAP[%d]\n", clock_seconds(), galiot_snap_rpl_timers_dio_reset_INFO.system_time[i], i);
        printf("(galiot) >>> [%10lu] >>> rpl_timers >>> rpl_timers_dio_reset (INFO): TRIGGER: %s\n", clock_seconds(), galiot_snap_rpl_timers_dio_reset_INFO.trigger[i]);
        printf("----------------------------------------------------------------\n");
      }
      
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #endif /* GALIOT_SNAP_RPL_TIMERS_DIO_RESET */
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/


      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      // rpl_timers_handle_dio_timer_INFO
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #if GALIOT_SNAP_RPL_TIMERS_HANDLE_DIO_TIMER
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/

      if (galiot_snap_flag_rpl_timers_dio_reset_INFO == 0)
      {
        //printf("\n");
        //printf("\n");
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        printf("(galiot) >>> [%10lu] >>> rpl_timers >>> handle_dio_timer (INFO): OFF\n", clock_seconds());
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        //printf("\n");
      }
      else
      {
        printf("(galiot) >>> [%10lu] >>> rpl_timers >>> handle_dio_timer (INFO): ON\n", clock_seconds());
        printf("(galiot) >>> [%10lu] >>> rpl_timers >>> handle_dio_timer (INFO): SNAPS: %d\n", clock_seconds(), galiot_snap_count_rpl_timers_handle_dio_timer_INFO);
        
        if (galiot_snap_flag_countOverflow_rpl_timers_handle_dio_timer_INFO == 1)
        {
          printf("(galiot) >>> [%10lu] >>> rpl_timers >>> handle_dio_timer (INFO): OVERFLOW\n", clock_seconds());
        }
        
        printf("----------------------------------------------------------------\n");
      }
        
      for (int i = 0; i < GALIOT_SNAPSHOT_COUNT; i++)
      {
        printf("(galiot) >>> [%10lu] >>> rpl_timers >>> handle_dio_timer (INFO) >>> [%10lu] LAST_SNAP[%d]\n", clock_seconds(), galiot_snap_rpl_timers_handle_dio_timer_INFO.system_time[i], i);
        printf("(galiot) >>> [%10lu] >>> rpl_timers >>> handle_dio_timer (INFO): TRIGGER DAO UPDATES WITH A DTSN INCREMENT: %u\n", clock_seconds(), galiot_snap_rpl_timers_handle_dio_timer_INFO.DAO_updates_with_DSTN_increment[i]);
        printf("----------------------------------------------------------------\n");
      }
      
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #endif /* GALIOT_SNAP_RPL_TIMERS_HANDLE_DIO_TIMER */
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/



      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      // rpl_timers_handle_probing_timer_INFO_if
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #if GALIOT_SNAP_RPL_TIMERS_HANDLE_DIO_TIMER
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/

      if (galiot_snap_flag_rpl_timers_handle_probing_timer_INFO_if == 0)
      {
        //printf("\n");
        //printf("\n");
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        printf("(galiot) >>> [%10lu] >>> rpl_timers >>> handle_probing_timer (INFO): OFF\n", clock_seconds());
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        //printf("\n");
      }
      else
      {
        printf("(galiot) >>> [%10lu] >>> rpl_timers >>> handle_probing_timer (INFO): ON\n", clock_seconds());
        printf("(galiot) >>> [%10lu] >>> rpl_timers >>> handle_probing_timer (INFO): SNAPS: %d\n", clock_seconds(), galiot_snap_count_rpl_timers_handle_probing_timer_INFO_if);
        
        if (galiot_snap_flag_countOverflow_rpl_timers_handle_probing_timer_INFO_if == 1)
        {
          printf("(galiot) >>> [%10lu] >>> rpl_timers >>> handle_probing_timer (INFO): OVERFLOW\n", clock_seconds());
        }
        
        printf("----------------------------------------------------------------\n");
      }
        
      for (int i = 0; i < GALIOT_SNAPSHOT_COUNT; i++)
      {
        printf("(galiot) >>> [%10lu] >>> rpl_timers >>> handle_probing_timer (INFO) >>> [%10lu] LAST_SNAP[%d]\n", clock_seconds(), galiot_snap_rpl_timers_handle_probing_timer_INFO_if.system_time[i], i);
        printf("(galiot) >>> [%10lu] >>> rpl_timers >>> handle_probing_timer (INFO): PROBING: %s\n", clock_seconds(), galiot_snap_rpl_timers_handle_probing_timer_INFO_if.probing_ipaddr[i]);
        printf("(galiot) >>> [%10lu] >>> rpl_timers >>> handle_probing_timer (INFO): URGENT: %s\n", clock_seconds(), galiot_snap_rpl_timers_handle_probing_timer_INFO_if.urgent[i]);
        printf("(galiot) >>> [%10lu] >>> rpl_timers >>> handle_probing_timer (INFO): TIME (MINUTES AGO): %u\n", clock_seconds(), galiot_snap_rpl_timers_handle_probing_timer_INFO_if.last_tx[i]);

        printf("----------------------------------------------------------------\n");
      }
      
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #endif /* GALIOT_SNAP_RPL_TIMERS_HANDLE_DIO_TIMER */
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/



      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      // rpl_timers_handle_probing_timer_INFO_else
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #if GALIOT_SNAP_RPL_TIMERS_HANDLE_DIO_TIMER
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/

      if (galiot_snap_flag_rpl_timers_handle_probing_timer_INFO_else == 0)
      {
        //printf("\n");
        //printf("\n");
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        printf("(galiot) >>> [%10lu] >>> rpl_timers >>> handle_probing_timer (INFO): OFF\n", clock_seconds());
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        //printf("\n");
      }
      else
      {
        printf("(galiot) >>> [%10lu] >>> rpl_timers >>> handle_probing_timer (INFO): ON\n", clock_seconds());
        printf("(galiot) >>> [%10lu] >>> rpl_timers >>> handle_probing_timer (INFO): SNAPS: %d\n", clock_seconds(), galiot_snap_count_rpl_timers_handle_probing_timer_INFO_else);
        
        if (galiot_snap_flag_countOverflow_rpl_timers_handle_probing_timer_INFO_else == 1)
        {
          printf("(galiot) >>> [%10lu] >>> rpl_timers >>> handle_probing_timer (INFO): OVERFLOW\n", clock_seconds());
        }
        
        printf("----------------------------------------------------------------\n");
      }
        
      for (int i = 0; i < GALIOT_SNAPSHOT_COUNT; i++)
      {
        printf("(galiot) >>> [%10lu] >>> rpl_timers >>> handle_probing_timer (INFO) >>> [%10lu] LAST_SNAP[%d]\n", clock_seconds(), galiot_snap_rpl_timers_handle_probing_timer_INFO_else.system_time[i], i);
        printf("(galiot) >>> [%10lu] >>> rpl_timers >>> handle_probing_timer (INFO) >>> NO NEIGHBOR NEEDS PROBING\n", clock_seconds());
        printf("----------------------------------------------------------------\n");
      }
      
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #endif /* GALIOT_SNAP_RPL_TIMERS_HANDLE_DIO_TIMER */
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/








      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    #endif /* GALIOT_FUNCTIONALITY */
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/























    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    #ifdef GALIOT_FUNCTIONALITY
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      // /os/net/routing/rpl-lite/rpl.c
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/

      
      printf("\n");
      printf("(galiot) >>> rpl.c\n");

      
      
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      // rpl_link_callback_INFO
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #if GALIOT_SNAP_RPL_LINK_CALLBACK
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/

      if (galiot_snap_flag_rpl_link_callback_INFO == 0)
      {
        //printf("\n");
        //printf("\n");
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        printf("(galiot) [%10lu] >>> rpl >>> rpl_link_callback (INFO): OFF\n", clock_seconds());
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        //printf("\n");
      }
      else
      {
        printf("(galiot) >>> [%10lu] >>> rpl >>> rpl_link_callback (INFO): ON\n", clock_seconds());
        printf("(galiot) >>> [%10lu] >>> rpl >>> rpl_link_callback (INFO): SNAPS: %d\n", clock_seconds(), galiot_snap_count_rpl_link_callback_INFO);
        
        if (galiot_snap_flag_countOverflow_rpl_link_callback_INFO == 1)
        {
          printf("(galiot) >>> [%10lu] >>> rpl >>> rpl_link_callback (INFO): OVERFLOW\n", clock_seconds());
        }
        
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        //printf("\n");
      }
        
      for (int i = 0; i < GALIOT_SNAPSHOT_COUNT; i++)
      {
        printf("(galiot) >>> [%10lu] >>> rpl >>> rpl_link_callback (INFO) >>> [%10lu] LAST_SNAP[%d]\n", clock_seconds(), galiot_snap_rpl_link_callback_INFO.system_time[i], i);
        printf("(galiot) >>> [%10lu] >>> rpl >>> rpl_link_callback (INFO): PACKET SENT TO: %s\n", clock_seconds(), galiot_snap_rpl_link_callback_INFO.packet_sent_to[i]);
        printf("(galiot) >>> [%10lu] >>> rpl >>> rpl_link_callback (INFO): STATUS: %u\n", clock_seconds(), galiot_snap_rpl_link_callback_INFO.status[i]);
        printf("(galiot) >>> [%10lu] >>> rpl >>> rpl_link_callback (INFO): TX: %u\n", clock_seconds(), galiot_snap_rpl_link_callback_INFO.tx[i]);
        printf("(galiot) >>> [%10lu] >>> rpl >>> rpl_link_callback (INFO): NEW LINK METRIC: %u\n", clock_seconds(), galiot_snap_rpl_link_callback_INFO.new_link_metric[i]);
        printf("----------------------------------------------------------------\n");
      }
      
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #endif /* GALIOT_SNAP_RPL_LINK_CALLBACK */
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      
      
      
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      // rpl_reset_prefix_INFO
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #if GALIOT_SNAP_RPL_RESET_PREFIX
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/

      if (galiot_snap_flag_rpl_reset_prefix_INFO == 0)
      {
        //printf("\n");
        //printf("\n");
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        printf("(galiot) >>> [%10lu] >>> rpl >>> rpl_reset_prefix (INFO): OFF\n", clock_seconds());
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        //printf("\n");
      }
      else
      {
        //printf("\n");
        printf("(galiot) >>> [%10lu] >>> rpl >>> rpl_reset_prefix (INFO): ON\n", clock_seconds());
        printf("(galiot) >>> [%10lu] >>> rpl >>> rpl_reset_prefix (INFO): SNAPS: %d\n", clock_seconds(), galiot_snap_count_rpl_reset_prefix_INFO);
        
        if (galiot_snap_flag_countOverflow_rpl_reset_prefix_INFO == 1)
        {
          printf("(galiot) >>> [%10lu] >>> rpl >>> rpl_reset_prefix (INFO): OVERFLOW\n", clock_seconds());
        }
        
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        //printf("\n");
      }

      for (int i = 0; i < GALIOT_SNAPSHOT_COUNT; i++)
      {
        printf("(galiot) >>> [%10lu] >>> rpl >>> rpl_reset_prefix (INFO) >>> [%10lu] LAST_SNAP[%d]\n", clock_seconds(), galiot_snap_rpl_reset_prefix_INFO.system_time[i], i);
        printf("(galiot) >>> [%10lu] >>> rpl >>> rpl_reset_prefix (INFO): REMOVING GLOBAL IP ADDRESS: %s\n", clock_seconds(), galiot_snap_rpl_reset_prefix_INFO.removing_global_IP_address[i]);
        printf("----------------------------------------------------------------\n");
      }

      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #endif /* GALIOT_SNAP_RPL_RESET_PREFIX */
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      
      
      
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      // rpl_set_prefix_from_addr_WARNING
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #if GALIOT_SNAP_RPL_SET_PREFIX_FROM_ADDR
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/

      if (galiot_snap_flag_rpl_set_prefix_from_addr_WARNING == 0)
      {
        //printf("\n");
        //printf("\n");
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        printf("(galiot) >>> [%10lu] >>> rpl >>> rpl_set_prefix_from_addr (WARNING): OFF\n", clock_seconds());
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        //printf("\n");
      }
      else
      {
        printf("\n");
        printf("(galiot) >>> [%10lu] >>> rpl >>> rpl_set_prefix_from_addr (WARNING): ON\n", clock_seconds());
        printf("(galiot) >>> [%10lu] >>> rpl >>> rpl_set_prefix_from_addr (WARNING): SNAPS: %d\n", clock_seconds(), galiot_snap_count_rpl_set_prefix_from_addr_WARNING);
        
        if (galiot_snap_flag_countOverflow_rpl_set_prefix_from_addr_WARNING == 1)
        {
          printf("(galiot) >>> [%10lu] >>> rpl >>> rpl_set_prefix_from_addr (WARNING): OVERFLOW\n", clock_seconds());
        }
        
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        //printf("\n");
      }

      for (int i = 0; i < GALIOT_SNAPSHOT_COUNT; i++)
      {
        printf("(galiot) >>> [%10lu] >>> rpl >>> rpl_set_prefix_from_addr (WARNING) >>> [%10lu] LAST_SNAP[%d]\n", clock_seconds(), galiot_snap_rpl_set_prefix_from_addr_WARNING.system_time[i], i);
        printf("(galiot) >>> [%10lu] >>> rpl >>> rpl_set_prefix_from_addr (WARNING): PREFIX NOT INCLUDED, NOT SUPPORTED OR INVALID\n", clock_seconds());
        //printf("----------------------------------------------------------------\n");
      }
      
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      // rpl_set_prefix_from_addr_INFO
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/

      if (galiot_snap_flag_rpl_set_prefix_from_addr_INFO == 0)
      {
        //printf("\n");
        //printf("\n");
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        printf("(galiot) >>> [%10lu] >>> rpl >>> rpl_set_prefix_from_addr (INFO): OFF\n", clock_seconds());
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        //printf("\n");
      }
      else
      {
        printf("\n");
        printf("(galiot) >>> [%10lu] >>> rpl >>> rpl_set_prefix_from_addr (INFO): ON\n", clock_seconds());
        printf("(galiot) >>> [%10lu] >>> rpl >>> rpl_set_prefix_from_addr (INFO): SNAPS: %d\n", clock_seconds(), galiot_snap_count_rpl_set_prefix_from_addr_INFO);
        
        if (galiot_snap_flag_countOverflow_rpl_set_prefix_from_addr_INFO == 1)
        {
          printf("(galiot) >>> [%10lu] >>> rpl >>> rpl_set_prefix_from_addr (INFO): OVERFLOW\n", clock_seconds());
        }
        
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        //printf("\n");
      }

      for (int i = 0; i < GALIOT_SNAPSHOT_COUNT; i++)
      {
        printf("(galiot) >>> [%10lu] >>> rpl >>> rpl_set_prefix_from_addr (INFO) >>> [%10lu] LAST_SNAP[%d]\n", clock_seconds(), galiot_snap_rpl_set_prefix_from_addr_INFO.system_time[i], i);
        printf("(galiot) >>> [%10lu] >>> rpl >>> rpl_set_prefix_from_addr (INFO): ADDING GLOBAL IP ADDRESS: %s\n", clock_seconds(), galiot_snap_rpl_set_prefix_from_addr_INFO.adding_global_IP_address[i]);
        printf("----------------------------------------------------------------\n");
      }

      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #endif /* GALIOT_SNAP_RPL_SET_PREFIX_FROM_ADDR */
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/

      
      
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      // init
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #if GALIOT_SNAP_RPL_INIT
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/

      if (galiot_snap_flag_init_INFO == 0)
      {
        //printf("\n");
        //printf("\n");
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        printf("(galiot) >>> [%10lu] >>> rpl >>> init (INFO): OFF\n", clock_seconds());
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        //printf("\n");
      }
      else
      {
        //printf("\n");
        //printf("\n");
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        printf("(galiot) >>> [%10lu] >>> rpl >>> init (INFO): ON\n", clock_seconds());
        printf("(galiot) >>> [%10lu] >>> rpl >>> init (INFO): SNAPS: %d\n", clock_seconds(), galiot_snap_count_init_INFO);
        
        if (galiot_snap_flag_countOverflow_init_INFO == 1)
        {
          printf("(galiot) >>> [%10lu] >>> rpl >>> init (INFO): OVERFLOW\n", clock_seconds());
        }
        
        //printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
        //printf("\n");
      }

      for (int i = 0; i < GALIOT_SNAPSHOT_COUNT; i++)
      {
        printf("(galiot) >>> [%10lu] >>> rpl >>> init (INFO) >>> [%10lu] LAST_SNAP[%d]\n", clock_seconds(), galiot_snap_init_INFO.system_time[i], i);
        printf("(galiot) >>> [%10lu] >>> rpl >>> init (INFO): INITIALIZING\n", clock_seconds());
        printf("----------------------------------------------------------------\n");
      }

      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #endif /* GALIOT_SNAP_RPL_INIT */
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/



      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    #endif /* GALIOT_FUNCTIONALITY */
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    


    
    
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    // εκτυπώνουμε το string που ορίσαμε παραπάνω.
    // αργότερα θα μπορούμε να το στείλουμε σαν json.
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    printf("\n");
    printf("================================================================\n");
    printf("\n");
    printf("(galiot) >>> IPv6: own address: %s\n", galiot_IPV6_uiplib_ip6addr);   // "nbr: own state, addr "
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    for (nbr = uip_ds6_nbr_head(); nbr != NULL; nbr = uip_ds6_nbr_next(nbr)) 
    {
      galiot_ipv6_nbr_count++;
    }
    printf("(galiot) >>> IPv6: detected neighbors: %d\n", galiot_ipv6_nbr_count);
    galiot_ipv6_nbr_count = 0; // reset the NBR count
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    

   
    

    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    // this is where we PRINT the galiot_RPL variables
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    // Get the RPL's best guess on if we are reachable via have downward route or not.
    // return 1 if we are reachable, 0 otherwise.
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    if (rpl_is_reachable() == 1) 
    {
      printf("(galiot) >>> RPL: reachable mote\n");
    }
    else 
    {
      printf("(galiot) >>> RPL: reachable mote\n");
    }  
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    // Tells whether we are DAG root or not
    // return 1 if we are dag root, 0 otherwise
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    if (rpl_dag_root_is_root() == 1) 
    {
      printf("(galiot) >>> RPL: DAG-root mote\n");
    }
    else 
    {
      printf("(galiot) >>> RPL: DAG-leaf mote\n");
    }
    printf("\n");
    printf("================================================================\n");
    printf("\n");  
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/



    

    /* Wait for the periodic timer to expire and then restart the timer. */
    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&timer));
    etimer_reset(&timer);
  }

  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
