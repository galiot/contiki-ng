/*
 * Copyright (c) 2009, Swedish Institute of Computer Science.
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
 */

/**
 * \addtogroup rpl-lite
 * @{
 *
 * \file
 *         ContikiRPL, an implementation of RPL: IPv6 Routing Protocol
 *         for Low-Power and Lossy Networks (IETF RFC 6550)
 *
 * \author Joakim Eriksson <joakime@sics.se>, Nicolas Tsiftes <nvt@sics.se>
 *  Simon Duquennoy <simon.duquennoy@inria.fr>
 */

#include "net/routing/rpl-lite/rpl.h"
#include "net/routing/routing.h"

/* Log configuration */
#include "sys/log.h"
#define LOG_MODULE "RPL"
#define LOG_LEVEL LOG_LEVEL_RPL





#if GALIOT_FUNCTIONALITY
  /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
  /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
  /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
  // INITIALIZATIONS rpl
  /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
  /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
  /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/

  // rpl_link_callback
  
  int galiot_snap_flag_rpl_link_callback = 0;                 // whether rpl_link_callback snap data have been populated
  int galiot_snap_count_rpl_link_callback = 0;                // how many times rpl_link_callback snap data have been offered
  int galiot_snap_flag_countOverflow_rpl_link_callback = 0;  // whether rpl_link_callback snap data have been offered 604 times at least once

  struct galiot_snap_struct_rpl_link_callback galiot_snap_rpl_link_callback = { {0}, {" "}, {0}, {0}, {0} };
  
  // rpl_reset_prefix

  int galiot_snap_flag_rpl_reset_prefix = 0;
  int galiot_snap_count_rpl_reset_prefix = 0;
  int galiot_snap_flag_countOverflow_rpl_reset_prefix = 0;

  struct galiot_snap_struct_rpl_reset_prefix galiot_snap_rpl_reset_prefix = { {0}, {" "} };

  // rpl_set_prefix_from_addr

  int galiot_snap_flag_rpl_set_prefix_from_addr = 0;
  int galiot_snap_count_rpl_set_prefix_from_addr = 0;
  int galiot_snap_flag_countOverflow_rpl_set_prefix_from_addr = 0;

  struct galiot_snap_struct_rpl_set_prefix_from_addr galiot_snap_rpl_set_prefix_from_addr = { {0}, {" "} };

  // init

  int galiot_snap_flag_init = 0;
  int galiot_snap_count_init = 0;
  int galiot_snap_flag_countOverflow_init = 0;

  struct galiot_snap_struct_init galiot_snap_init = { {0} };

  /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
  /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
  /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
#endif /* GALIOT_FUNCTIONALITY */




uip_ipaddr_t rpl_multicast_addr;
static uint8_t rpl_leaf_only = RPL_DEFAULT_LEAF_ONLY;

/*---------------------------------------------------------------------------*/
int
rpl_lollipop_greater_than(int a, int b)
{
  /* Check if we are comparing an initial value with an old value */
  if(a > RPL_LOLLIPOP_CIRCULAR_REGION && b <= RPL_LOLLIPOP_CIRCULAR_REGION) {
    return (RPL_LOLLIPOP_MAX_VALUE + 1 + b - a) > RPL_LOLLIPOP_SEQUENCE_WINDOWS;
  }
  /* Otherwise check if a > b and comparable => ok, or
     if they have wrapped and are still comparable */
  return (a > b && (a - b) < RPL_LOLLIPOP_SEQUENCE_WINDOWS) ||
    (a < b && (b - a) > (RPL_LOLLIPOP_CIRCULAR_REGION + 1-
			 RPL_LOLLIPOP_SEQUENCE_WINDOWS));
}
/*---------------------------------------------------------------------------*/
const uip_ipaddr_t *
rpl_get_global_address(void)
{
  int i;
  uint8_t state;
  uip_ipaddr_t *ipaddr = NULL;
  uip_ipaddr_t *prefix = NULL;
  uint8_t prefix_length = 0;

  if(curr_instance.used && curr_instance.dag.prefix_info.length != 0) {
    prefix = &curr_instance.dag.prefix_info.prefix;
    prefix_length = curr_instance.dag.prefix_info.length;
  }

  for(i = 0; i < UIP_DS6_ADDR_NB; i++) {
    state = uip_ds6_if.addr_list[i].state;
    if(uip_ds6_if.addr_list[i].isused &&
       state == ADDR_PREFERRED &&
       !uip_is_addr_linklocal(&uip_ds6_if.addr_list[i].ipaddr) &&
       (prefix == NULL || uip_ipaddr_prefixcmp(prefix, &uip_ds6_if.addr_list[i].ipaddr, prefix_length))) {
      ipaddr = &uip_ds6_if.addr_list[i].ipaddr;
    }
  }
  return ipaddr;
}
/*---------------------------------------------------------------------------*/
void
rpl_link_callback(const linkaddr_t *addr, int status, int numtx)
{
  if(curr_instance.used == 1 ) {
    rpl_nbr_t *nbr = rpl_neighbor_get_from_lladdr((uip_lladdr_t *)addr);
    if(nbr != NULL) {
      /* If this is the neighbor we were probing urgently, mark urgent
      probing as done */
      if(curr_instance.dag.urgent_probing_target == nbr) {
        curr_instance.dag.urgent_probing_target = NULL;
      }
      /* Link stats were updated, and we need to update our internal state.
      Updating from here is unsafe; postpone */
      LOG_INFO("packet sent to ");
      LOG_INFO_LLADDR(addr);
      LOG_INFO_(", status %u, tx %u, new link metric %u\n", status, numtx, rpl_neighbor_get_link_metric(nbr));





      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      // SNAP rpl_link_callback
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      #if GALIOT_FUNCTIONALITY
      
        /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
        char addr_str[40];
        char galiot_addr_buf[2];

        if(addr == NULL)
        {
         strcpy(addr_str, "(NULL addr)");
        }
        else
        {
         for(unsigned int i = 0; i < LINKADDR_SIZE; i++) 
         {
           if(i > 0 && i % 2 == 0) 
           {
             strcat(addr_str, ".");
           }
           sprintf(galiot_addr_buf, "%02x", addr->u8[i]);
           strcat(addr_str, galiot_addr_buf);
         }
        }
      
        printf("*** DEBUG: lladdr_str: %s\n", addr_str);
        /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/

        /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
        galiot_snap_flag_rpl_link_callback = 1;
        galiot_snap_count_rpl_link_callback++;

        if (galiot_snap_count_rpl_link_callback == 604)
        {
         galiot_snap_flag_countOverflow_rpl_link_callback = 1;
         galiot_snap_count_rpl_link_callback = 1;
        }
        /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/

        /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
        galiot_snap_rpl_link_callback.system_time[galiot_snap_count_rpl_link_callback % GALIOT_SNAPSHOT_COUNT] = clock_seconds();
        strcpy(galiot_snap_rpl_link_callback.packet_sent_to[galiot_snap_count_rpl_link_callback % GALIOT_SNAPSHOT_COUNT], addr_str);
        galiot_snap_rpl_link_callback.status[galiot_snap_count_rpl_link_callback % GALIOT_SNAPSHOT_COUNT] = status;
        galiot_snap_rpl_link_callback.tx[galiot_snap_count_rpl_link_callback % GALIOT_SNAPSHOT_COUNT] = numtx;
        galiot_snap_rpl_link_callback.new_link_metric[galiot_snap_count_rpl_link_callback % GALIOT_SNAPSHOT_COUNT] = rpl_neighbor_get_link_metric(nbr);

        printf("*** DEBUG: galiot_snap_count_rpl_link_callback: %d\n", galiot_snap_count_rpl_link_callback);
        printf("*** DEBUG: galiot_snap_count_rpl_link_callback mod GALIOT_SNAPSHOT_COUNT: %u\n", galiot_snap_count_rpl_link_callback % GALIOT_SNAPSHOT_COUNT);
        printf("*** DEBUG: system time: %lu\n", galiot_snap_rpl_link_callback.system_time[galiot_snap_count_rpl_link_callback % GALIOT_SNAPSHOT_COUNT]);

        printf("*** DEBUG: packet sent to: %s\n", galiot_snap_rpl_link_callback.packet_sent_to[galiot_snap_count_rpl_link_callback % GALIOT_SNAPSHOT_COUNT]);
        printf("*** DEBUG: status: %u\n", galiot_snap_rpl_link_callback.status[galiot_snap_count_rpl_link_callback % GALIOT_SNAPSHOT_COUNT]);
        printf("*** DEBUG: tx: %u\n", galiot_snap_rpl_link_callback.tx[galiot_snap_count_rpl_link_callback % GALIOT_SNAPSHOT_COUNT]);
        printf("*** DEBUG: new_link_metric: %u\n", galiot_snap_rpl_link_callback.new_link_metric[galiot_snap_count_rpl_link_callback % GALIOT_SNAPSHOT_COUNT]);
        /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      
      

      #endif /* GALIOT_FUNCTIONALITY */
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/





      rpl_timers_schedule_state_update();
    }
  }
}
/*---------------------------------------------------------------------------*/
int
rpl_has_joined(void)
{
  return curr_instance.used && curr_instance.dag.state >= DAG_JOINED;
}
/*---------------------------------------------------------------------------*/
int
rpl_is_reachable(void)
{
  return curr_instance.used && curr_instance.dag.state == DAG_REACHABLE;
}
/*---------------------------------------------------------------------------*/
static void
set_ip_from_prefix(uip_ipaddr_t *ipaddr, rpl_prefix_t *prefix)
{
  memset(ipaddr, 0, sizeof(uip_ipaddr_t));
  memcpy(ipaddr, &prefix->prefix, (prefix->length + 7) / 8);
  uip_ds6_set_addr_iid(ipaddr, &uip_lladdr);
}
/*---------------------------------------------------------------------------*/
void
rpl_reset_prefix(rpl_prefix_t *last_prefix)
{
  uip_ipaddr_t ipaddr;
  uip_ds6_addr_t *rep;
  set_ip_from_prefix(&ipaddr, last_prefix);
  rep = uip_ds6_addr_lookup(&ipaddr);
  if(rep != NULL) {
    LOG_INFO("removing global IP address ");
    LOG_INFO_6ADDR(&ipaddr);
    LOG_INFO_("\n");
    





    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    // SNAP rpl_reset_prefix
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    #if GALIOT_FUNCTIONALITY

      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      galiot_snap_flag_rpl_reset_prefix = 1;
      galiot_snap_count_rpl_reset_prefix++;

      if (galiot_snap_count_rpl_reset_prefix == 604)  
      {
        galiot_snap_flag_countOverflow_rpl_reset_prefix = 1;
        galiot_snap_count_rpl_reset_prefix = 1;
      }
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/

      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      galiot_snap_rpl_reset_prefix.system_time[galiot_snap_count_rpl_reset_prefix % GALIOT_SNAPSHOT_COUNT] = clock_seconds();
      uiplib_ipaddr_snprint(galiot_snap_rpl_reset_prefix.removing_global_IP_address[galiot_snap_count_rpl_reset_prefix % GALIOT_SNAPSHOT_COUNT], sizeof(galiot_snap_rpl_reset_prefix.removing_global_IP_address[galiot_snap_count_rpl_reset_prefix % GALIOT_SNAPSHOT_COUNT]), &ipaddr); 
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      printf("********** DEBUG: rpl_reset_prefix SYSTEM TIME: %lu\n", galiot_snap_rpl_reset_prefix.system_time[galiot_snap_count_rpl_reset_prefix % GALIOT_SNAPSHOT_COUNT]);
      printf("********** DEBUG, rpl_reset_prefix removing %s\n", galiot_snap_rpl_reset_prefix.removing_global_IP_address[galiot_snap_count_rpl_reset_prefix % GALIOT_SNAPSHOT_COUNT]);

    #endif /* GALIOT_FUNCTIONALITY */
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/




    uip_ds6_addr_rm(rep);
  }
  curr_instance.dag.prefix_info.length = 0;
}
/*---------------------------------------------------------------------------*/
int
rpl_set_prefix_from_addr(uip_ipaddr_t *addr, unsigned len, uint8_t flags)
{
  uip_ipaddr_t ipaddr;

  if(addr == NULL || len == 0 || len > 128 || !(flags & UIP_ND6_RA_FLAG_AUTONOMOUS)) {
    LOG_WARN("prefix not included, not-supported or invalid\n");
    return 0;
  }

  /* Try and initialize prefix */
  memset(&curr_instance.dag.prefix_info.prefix, 0, sizeof(rpl_prefix_t));
  memcpy(&curr_instance.dag.prefix_info.prefix, addr, (len + 7) / 8);
  curr_instance.dag.prefix_info.length = len;
  curr_instance.dag.prefix_info.lifetime = RPL_ROUTE_INFINITE_LIFETIME;
  curr_instance.dag.prefix_info.flags = flags;

  /* Add global address if not already there */
  set_ip_from_prefix(&ipaddr, &curr_instance.dag.prefix_info);
  if(uip_ds6_addr_lookup(&ipaddr) == NULL) {
    LOG_INFO("adding global IP address ");
    LOG_INFO_6ADDR(&ipaddr);
    LOG_INFO_("\n");




    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    // SNAP rpl_set_prefix_from_addr
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    #if GALIOT_FUNCTIONALITY

      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      galiot_snap_flag_rpl_set_prefix_from_addr = 1;
      galiot_snap_count_rpl_set_prefix_from_addr++;

      if (galiot_snap_count_rpl_set_prefix_from_addr == 604)  
      {
        galiot_snap_flag_countOverflow_rpl_set_prefix_from_addr = 1;
        galiot_snap_count_rpl_set_prefix_from_addr = 1;
      }
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/

      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      galiot_snap_rpl_set_prefix_from_addr.system_time[galiot_snap_count_rpl_set_prefix_from_addr % GALIOT_SNAPSHOT_COUNT] = clock_seconds();
      uiplib_ipaddr_snprint(galiot_snap_rpl_set_prefix_from_addr.adding_global_IP_address[galiot_snap_count_rpl_set_prefix_from_addr % GALIOT_SNAPSHOT_COUNT], sizeof(galiot_snap_rpl_set_prefix_from_addr.adding_global_IP_address[galiot_snap_count_rpl_set_prefix_from_addr % GALIOT_SNAPSHOT_COUNT]), &ipaddr); 
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      printf("********** DEBUG: rpl_set_prefix_from_addr SYSTEM TIME: %lu\n", galiot_snap_rpl_set_prefix_from_addr.system_time[galiot_snap_count_rpl_set_prefix_from_addr % GALIOT_SNAPSHOT_COUNT]);
      printf("********** DEBUG, rpl_set_prefix_from_addr adding %s\n", galiot_snap_rpl_set_prefix_from_addr.adding_global_IP_address[galiot_snap_count_rpl_set_prefix_from_addr % GALIOT_SNAPSHOT_COUNT]);

    #endif /* GALIOT_FUNCTIONALITY */
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/







    uip_ds6_addr_add(&ipaddr, 0, ADDR_AUTOCONF);
  }
  return 1;
}
/*---------------------------------------------------------------------------*/
int
rpl_set_prefix(rpl_prefix_t *prefix)
{
  if(prefix != NULL && rpl_set_prefix_from_addr(&prefix->prefix, prefix->length, prefix->flags)) {
    curr_instance.dag.prefix_info.lifetime = prefix->lifetime;
    return 1;
  }
  return 0;
}
/*---------------------------------------------------------------------------*/
static void
init(void)
{
  LOG_INFO("initializing\n");




  /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
  /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
  /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
  // SNAP init
  /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
  /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
  /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
  #if GALIOT_FUNCTIONALITY

    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    galiot_snap_flag_init = 1;
    galiot_snap_count_init++;

    if (galiot_snap_count_init == 604)  
    {
      galiot_snap_flag_countOverflow_init = 1;
      galiot_snap_count_init = 1;
    }
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/

    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    galiot_snap_init.system_time[galiot_snap_count_init % GALIOT_SNAPSHOT_COUNT] = clock_seconds();
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/

  #endif /* GALIOT_FUNCTIONALITY */
  /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
  /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
  /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/






  /* Initialize multicast address and register it */
  uip_create_linklocal_rplnodes_mcast(&rpl_multicast_addr);
  uip_ds6_maddr_add(&rpl_multicast_addr);

  rpl_dag_init();
  rpl_neighbor_init();
  rpl_timers_init();
  rpl_icmp6_init();

  uip_sr_init();
}
/*---------------------------------------------------------------------------*/
static int
get_sr_node_ipaddr(uip_ipaddr_t *addr, const uip_sr_node_t *node)
{
  if(addr != NULL && node != NULL) {
    memcpy(addr, &curr_instance.dag.dag_id, 8);
    memcpy(((unsigned char *)addr) + 8, &node->link_identifier, 8);
    return 1;
  } else {
    return 0;
  }
}
/*---------------------------------------------------------------------------*/
static void
neighbor_state_changed(uip_ds6_nbr_t *nbr)
{
  /* Nothing needs be done in non-storing mode */
}
/*---------------------------------------------------------------------------*/
static void
drop_route(uip_ds6_route_t *route)
{
  /* Do nothing. RPL-lite only supports non-storing mode, i.e. no routes */
}
/*---------------------------------------------------------------------------*/
void
rpl_set_leaf_only(uint8_t value)
{
  rpl_leaf_only = value;
}
/*---------------------------------------------------------------------------*/
uint8_t
rpl_get_leaf_only(void)
{
  return rpl_leaf_only;
}
/*---------------------------------------------------------------------------*/
const struct routing_driver rpl_lite_driver = {
  "RPL Lite",
  init,
  rpl_dag_root_set_prefix,
  rpl_dag_root_start,
  rpl_dag_root_is_root,
  rpl_dag_get_root_ipaddr,
  get_sr_node_ipaddr,
  rpl_dag_poison_and_leave,
  rpl_has_joined,
  rpl_is_reachable,
  rpl_global_repair,
  rpl_local_repair,
  rpl_ext_header_remove,
  rpl_ext_header_update,
  rpl_ext_header_hbh_update,
  rpl_ext_header_srh_update,
  rpl_ext_header_srh_get_next_hop,
  rpl_link_callback,
  neighbor_state_changed,
  drop_route,
};
/*---------------------------------------------------------------------------*/

/** @}*/
