/*
 * Copyright (c) 2015, Swedish Institute of Computer Science.
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
 */

#ifndef PROJECT_CONF_H_
#define PROJECT_CONF_H_





/*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
/*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
/*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
/* Set maximum debug level on all modules. See os/sys/log-conf.h for
 * a list of supported modules. The different log levels are defined in
 * os/sys/log.h:
 *     LOG_LEVEL_NONE         No log
 *     LOG_LEVEL_ERR          Errors
 *     LOG_LEVEL_WARN         Warnings
 *     LOG_LEVEL_INFO         Basic info
 *     LOG_LEVEL_DBG          Detailled debug
  */
#define LOG_CONF_LEVEL_IPV6                        LOG_LEVEL_NONE
#define LOG_CONF_LEVEL_RPL                         LOG_LEVEL_NONE
#define LOG_CONF_LEVEL_6LOWPAN                     LOG_LEVEL_NONE
#define LOG_CONF_LEVEL_TCPIP                       LOG_LEVEL_NONE
#define LOG_CONF_LEVEL_MAC                         LOG_LEVEL_NONE
#define LOG_CONF_LEVEL_FRAMER                      LOG_LEVEL_NONE
#define LOG_CONF_LEVEL_COAP                        LOG_LEVEL_NONE
#define LOG_CONF_LEVEL_LWM2M                       LOG_LEVEL_NONE
#define LOG_CONF_LEVEL_6TOP                        LOG_LEVEL_NONE
/*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
/*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
/*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/





/*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
/*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
/*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
#define MOTE_COLOR                                                          RED
/*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
/*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
/*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/





/*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
/*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
/*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
/*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
// GALIOT_OUTPUT_CONF specifies if galiot functionality is enabled or not.
/*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
#define GALIOT_CONF_FUNCTIONALITY                                    2
/*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
/*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
/*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
#if GALIOT_CONF_FUNCTIONALITY
  #define GALIOT_FUNCTIONALITY                        GALIOT_CONF_FUNCTIONALITY
#endif /* GALIOT_OUTPUT_CONF */
/*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
/*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
/*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
/*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
//GALIOT_OUTPUT_COUNT_CONF specifies how many snapshots will be stored.
/*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
#define GALIOT_CONF_SNAPSHOT_COUNT                                    2
/*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
/*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
/*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
#if GALIOT_FUNCTIONALITY
  #define GALIOT_SNAPSHOT_COUNT                       GALIOT_CONF_SNAPSHOT_COUNT
#else /* GALIOT_FUNCTIONALITY */
  #define GALIOT_SNAPSHOT_COUNT                                         0
#endif /* GALIOT_FUNCTIONALITY */
/*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
/*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
/*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
/*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
//GALIOT_RPL_NEIGHBOR_ARRY_CONF specifies the maximum number of neighbers
/*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
#define GALIOT_RPL_NEIGHBOR_ARRY_CONF                                 4
/*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
/*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
/*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
#if GALIOT_FUNCTIONALITY
  #define GALIOT_RPL_NEIGHBOR_ARRY                 GALIOT_RPL_NEIGHBOR_ARRY_CONF
#else /* GALIOT_FUNCTIONALITY */
  #define GALIOT_RPL_NEIGHBOR_ARRY                                      0
#endif /* GALIOT_FUNCTIONALITY */
/*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
/*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
/*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/



/*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
/*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
/*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
//  contiki-default-conf.h
/*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
/*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
/*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
//   /* NBR_TABLE_CONF_MAX_NEIGHBORS specifies the maximum number of neighbors
//      that each node will be able to handle. */
//  #ifndef NBR_TABLE_CONF_MAX_NEIGHBORS
//  #define NBR_TABLE_CONF_MAX_NEIGHBORS 16
//  #endif /* NBR_TABLE_CONF_MAX_NEIGHBORS */

//  /* NETSTACK_MAX_ROUTE_ENTRIES specifies the maximum number of entries
//     the routing module will handle. Applies to uIP routing tables if they are
//     used, or to RPL non-storing mode links instead */
//  #ifndef NETSTACK_MAX_ROUTE_ENTRIES
//  #define NETSTACK_MAX_ROUTE_ENTRIES 16
//  #endif /* NETSTACK_MAX_ROUTE_ENTRIES */
/*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
/*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
/*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/










/*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
/* SNAP ?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-|-?-*/
/*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
#if GALIOT_FUNCTIONALITY

  // rpl-dag-root
  #define GALIOT_SNAP_RPL_DAG_ROOT_PRINT_LINKS_CONF                   0
  #define GALIOT_SNAP_RPL_DAG_ROOT_SET_GLOBAL_ADDRESS_CONF            0 
  #define GALIOT_SNAP_RPL_DAG_ROOT_START_CONF                         0

  // rpl-dag
  #define GALIOT_SNAP_RPL_DAG_LEAVE_CONF                              0
  #define GALIOT_SNAP_RPL_DAG_PERIODIC_CONF                           0
  #define GALIOT_SNAP_RPL_DAG_REFRESH_ROUTES_CONF                     0
  #define GALIOT_SNAP_RPL_DAG_GLOBAL_REPAIR_CONF                      0
  #define GALIOT_SNAP_RPL_DAG_GLOBAL_REPAIR_NON_ROOT_CONF             0
  #define GALIOT_SNAP_RPL_DAG_LOCAL_REPAIR_CONF                       0
  #define GALIOT_SNAP_RPL_DAG_UPDATE_STATE_CONF                       0
  #define GALIOT_SNAP_RPL_DAG_UPDATE_NBR_FROM_DIO_CONF                0
  #define GALIOT_SNAP_RPL_DAG_PROCESS_DIO_FROM_CURRENT_DAG_CONF       0
  #define GALIOT_SNAP_RPL_DAG_INIT_DAG_CONF                           0
  #define GALIOT_SNAP_RPL_DAG_PROCESS_DIO_INIT_DAG_CONF               0
  #define GALIOT_SNAP_RPL_DAG_PROCESS_DIO_CONF                        0
  #define GALIOT_SNAP_RPL_DAG_PROCESS_DIS_CONF                        0
  #define GALIOT_SNAP_RPL_DAG_PROCESS_DAO_CONF                        0
  #define GALIOT_SNAP_RPL_DAG_PROCESS_DAO_ACK_CONF                    0
  #define GALIOT_SNAP_RPL_DAG_PROCESS_HBH_CONF                        0
  #define GALIOT_SNAP_RPL_DAG_INIT_ROOT_CONF                          0

  // rpl-ext-header
  #define GALIOT_SNAP_RPL_EXT_HEADER_SRH_GET_NEXT_HOP_CONF            0
  #define GALIOT_SNAP_RPL_EXT_HEADER_SRH_UPDATE_CONF                  0
  #define GALIOT_SNAP_RPL_EXT_HEADER_INSERT_SRH_HEADER_CONF           0
  #define GALIOT_SNAP_RPL_EXT_HEADER_SBH_UPDATE_CONF                  0
  #define GALIOT_SNAP_RPL_EXT_HEADER_UPDATE_HBH_HEADER_CONF           0
  #define GALIOT_SNAP_RPL_EXT_HEADER_INSERT_HBH_HEADER_CONF           0

  // rpl-icmp6
  #define GALIOT_SNAP_RPL_ICMP6_UPDATE_NBR_TABLE_CONF                 0
  #define GALIOT_SNAP_RPL_ICMP6_DIS_INPUT_CONF                        0
  #define GALIOT_SNAP_RPL_ICMP6_DIS_OUTPUT_CONF                       0
  #define GALIOT_SNAP_RPL_ICMP6_DIO_INPUT_CONF                        0
  #define GALIOT_SNAP_RPL_ICMP6_DIO_OUTPUT_CONF                       0
  #define GALIOT_SNAP_RPL_ICMP6_DAO_INPUT_CONF                        0
  #define GALIOT_SNAP_RPL_ICMP6_DAO_OUTPUT_CONF                       0
  #define GALIOT_SNAP_RPL_ICMP6_DAO_ACK_INPUT_CONF                    0
  #define GALIOT_SNAP_RPL_ICMP6_DAO_ACK_OUTPUT_CONF                   0

  // rpl-mrhof
  #define GALIOT_SNAP_RPL_MRHOF_RESET_CONF                            0
  #define GALIOT_SNAP_RPL_MRHOF_UPDATE_METRIC_CONTAINER_CONF          0
  
  // rpl-nbr-policy
  #define GALIOT_SNAP_RPL_NBR_POLICY_FIND_REMOVABLE_DIO_CONF          0
  
  // rpl-neigbor
  #define GALIOT_SNAP_RPL_NEIGHBOR_PRINT_LIST_OWNSTATE_CONF           1
  #define GALIOT_SNAP_RPL_NEIGHBOR_PRINT_LIST_NBR_CONF                1
  #define GALIOT_SNAP_RPL_NEIGHBOR_SET_PREFERRED_PARENT_CONF          0
  #define GALIOT_SNAP_RPL_NEIGHBOR_REMOVE_ALL_CONF                    0
  #define GALIOT_SNAP_RPL_NEIGHBOR_SELECT_BEST_CONF                   0

  // rpl-of0
  #define GALIOT_SNAP_RPL_OF0_CONF                                    0

  // rpl-timers
  #define GALIOT_SNAP_RPL_TIMERS_DIO_RESET_CONF                       0
  #define GALIOT_SNAP_RPL_TIMERS_HANDLE_DIO_TIMER_CONF                0
  #define GALIOT_SNAP_RPL_TIMERS_HANDLE_PROBING_TIMER_CONF            0

  // rpl
  #define GALIOT_SNAP_RPL_LINK_CALLBACK_CONF                          0
  #define GALIOT_SNAP_RPL_RESET_PREFIX_CONF                           0
  #define GALIOT_SNAP_RPL_SET_PREFIX_FROM_ADDR_CONF                   0
  #define GALIOT_SNAP_RPL_INIT_CONF                                   0

  // [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]
  // PRINT [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]
  // [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]

  // rpl-dag-root
  #define GALIOT_PRINT_RPL_DAG_ROOT_PRINT_LINKS_CONF                   0
  #define GALIOT_PRINT_RPL_DAG_ROOT_SET_GLOBAL_ADDRESS_CONF            0 
  #define GALIOT_PRINT_RPL_DAG_ROOT_START_CONF                         0

  // rpl-dag-root
  #define GALIOT_PRINT_RPL_DAG_ROOT_PRINT_LINKS_CONF                   0
  #define GALIOT_PRINT_RPL_DAG_ROOT_SET_GLOBAL_ADDRESS_CONF            0 
  #define GALIOT_PRINT_RPL_DAG_ROOT_START_CONF                         0

  // rpl-dag
  #define GALIOT_PRINT_RPL_DAG_LEAVE_CONF                              0
  #define GALIOT_PRINT_RPL_DAG_PERIODIC_CONF                           0
  #define GALIOT_PRINT_RPL_DAG_REFRESH_ROUTES_CONF                     0
  #define GALIOT_PRINT_RPL_DAG_GLOBAL_REPAIR_CONF                      0
  #define GALIOT_PRINT_RPL_DAG_GLOBAL_REPAIR_NON_ROOT_CONF             0
  #define GALIOT_PRINT_RPL_DAG_LOCAL_REPAIR_CONF                       0
  #define GALIOT_PRINT_RPL_DAG_UPDATE_STATE_CONF                       0
  #define GALIOT_PRINT_RPL_DAG_UPDATE_NBR_FROM_DIO_CONF                0
  #define GALIOT_PRINT_RPL_DAG_PROCESS_DIO_FROM_CURRENT_DAG_CONF       0
  #define GALIOT_PRINT_RPL_DAG_INIT_DAG_CONF                           0
  #define GALIOT_PRINT_RPL_DAG_PROCESS_DIO_INIT_DAG_CONF               0
  #define GALIOT_PRINT_RPL_DAG_PROCESS_DIO_CONF                        0
  #define GALIOT_PRINT_RPL_DAG_PROCESS_DIS_CONF                        0
  #define GALIOT_PRINT_RPL_DAG_PROCESS_DAO_CONF                        0
  #define GALIOT_PRINT_RPL_DAG_PROCESS_DAO_ACK_CONF                    0
  #define GALIOT_PRINT_RPL_DAG_PROCESS_HBH_CONF                        0
  #define GALIOT_PRINT_RPL_DAG_INIT_ROOT_CONF                          0

  // rpl-ext-header
  #define GALIOT_PRINT_RPL_EXT_HEADER_SRH_GET_NEXT_HOP_CONF            0
  #define GALIOT_PRINT_RPL_EXT_HEADER_SRH_UPDATE_CONF                  0
  #define GALIOT_PRINT_RPL_EXT_HEADER_INSERT_SRH_HEADER_CONF           0
  #define GALIOT_PRINT_RPL_EXT_HEADER_SBH_UPDATE_CONF                  0
  #define GALIOT_PRINT_RPL_EXT_HEADER_UPDATE_HBH_HEADER_CONF           0
  #define GALIOT_PRINT_RPL_EXT_HEADER_INSERT_HBH_HEADER_CONF           0

  // rpl-icmp6
  #define GALIOT_PRINT_RPL_ICMP6_UPDATE_NBR_TABLE_CONF                 0
  #define GALIOT_PRINT_RPL_ICMP6_DIS_INPUT_CONF                        0
  #define GALIOT_PRINT_RPL_ICMP6_DIS_OUTPUT_CONF                       0
  #define GALIOT_PRINT_RPL_ICMP6_DIO_INPUT_CONF                        0
  #define GALIOT_PRINT_RPL_ICMP6_DIO_OUTPUT_CONF                       0
  #define GALIOT_PRINT_RPL_ICMP6_DAO_INPUT_CONF                        0
  #define GALIOT_PRINT_RPL_ICMP6_DAO_OUTPUT_CONF                       0
  #define GALIOT_PRINT_RPL_ICMP6_DAO_ACK_INPUT_CONF                    0
  #define GALIOT_PRINT_RPL_ICMP6_DAO_ACK_OUTPUT_CONF                   0

  // rpl-mrhof
  #define GALIOT_PRINT_RPL_MRHOF_RESET_CONF                            0
  #define GALIOT_PRINT_RPL_MRHOF_UPDATE_METRIC_CONTAINER_CONF          0
  
  // rpl-nbr-policy
  #define GALIOT_PRINT_RPL_NBR_POLICY_FIND_REMOVABLE_DIO_CONF          0
  
  // rpl-neigbor
  #define GALIOT_PRINT_RPL_NEIGHBOR_PRINT_LIST_OWNSTATE_CONF           1
  #define GALIOT_PRINT_RPL_NEIGHBOR_PRINT_LIST_NBR_CONF                1
  #define GALIOT_PRINT_RPL_NEIGHBOR_SET_PREFERRED_PARENT_CONF          0
  #define GALIOT_PRINT_RPL_NEIGHBOR_REMOVE_ALL_CONF                    0
  #define GALIOT_PRINT_RPL_NEIGHBOR_SELECT_BEST_CONF                   0

  // rpl-of0
  #define GALIOT_PRINT_RPL_OF0_CONF                                    0

  // rpl-timers
  #define GALIOT_PRINT_RPL_TIMERS_DIO_RESET_CONF                       0
  #define GALIOT_PRINT_RPL_TIMERS_HANDLE_DIO_TIMER_CONF                0
  #define GALIOT_PRINT_RPL_TIMERS_HANDLE_PROBING_TIMER_CONF            0

  // rpl
  #define GALIOT_PRINT_RPL_LINK_CALLBACK_CONF                          0
  #define GALIOT_PRINT_RPL_RESET_PREFIX_CONF                           0
  #define GALIOT_PRINT_RPL_SET_PREFIX_FROM_ADDR_CONF                   0
  #define GALIOT_PRINT_RPL_INIT_CONF                                   0

  // [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]
  
  /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
  /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
  /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/

  #if GALIOT_SNAP_RPL_DAG_ROOT_PRINT_LINKS_CONF 
    #define GALIOT_SNAP_RPL_DAG_ROOT_PRINT_LINKS                      GALIOT_SNAP_RPL_DAG_ROOT_PRINT_LINKS_CONF
    #define GALIOT_PRINT_RPL_DAG_ROOT_PRINT_LINKS                      GALIOT_PRINT_RPL_DAG_ROOT_PRINT_LINKS_CONF 
  #else
    #define GALIOT_SNAP_RPL_DAG_ROOT_PRINT_LINKS                      0
  #endif

  #if GALIOT_SNAP_RPL_DAG_ROOT_SET_GLOBAL_ADDRESS_CONF 
    #define GALIOT_SNAP_RPL_DAG_ROOT_SET_GLOBAL_ADDRESS               GALIOT_SNAP_RPL_DAG_ROOT_SET_GLOBAL_ADDRESS_CONF
    #define GALIOT_PRINT_RPL_DAG_ROOT_SET_GLOBAL_ADDRESS               GALIOT_PRINT_RPL_DAG_ROOT_SET_GLOBAL_ADDRESS_CONF
  #else
    #define GALIOT_SNAP_RPL_DAG_ROOT_SET_GLOBAL_ADDRESS               0
  #endif

  #if GALIOT_SNAP_RPL_DAG_ROOT_START_CONF 
    #define GALIOT_SNAP_RPL_DAG_ROOT_START                            GALIOT_SNAP_RPL_DAG_ROOT_START_CONF
    #define GALIOT_PRINT_RPL_DAG_ROOT_START                            GALIOT_PRINT_RPL_DAG_ROOT_START_CONF
  #else
    #define GALIOT_SNAP_RPL_DAG_ROOT_START                            0
  #endif

  /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/

  #if GALIOT_SNAP_RPL_DAG_LEAVE_CONF 
    #define GALIOT_SNAP_RPL_DAG_LEAVE                                 GALIOT_SNAP_RPL_DAG_LEAVE_CONF
    #define GALIOT_PRINT_RPL_DAG_LEAVE                                 GALIOT_PRINT_RPL_DAG_LEAVE_CONF
  #else
    #define GALIOT_SNAP_RPL_DAG_LEAVE                                 0
  #endif

  #if GALIOT_SNAP_RPL_DAG_PERIODIC_CONF
    #define GALIOT_SNAP_RPL_DAG_PERIODIC                              GALIOT_SNAP_RPL_DAG_PERIODIC_CONF
    #define GALIOT_PRINT_RPL_DAG_PERIODIC                              GALIOT_PRINT_RPL_DAG_PERIODIC_CONF
  #else
    #define GALIOT_SNAP_RPL_DAG_PERIODIC                              0
  #endif

  #if GALIOT_SNAP_RPL_DAG_REFRESH_ROUTES_CONF 
    #define GALIOT_SNAP_RPL_DAG_REFRESH_ROUTES                        GALIOT_SNAP_RPL_DAG_REFRESH_ROUTES_CONF
    #define GALIOT_PRINT_RPL_DAG_REFRESH_ROUTES                        GALIOT_PRINT_RPL_DAG_REFRESH_ROUTES_CONF
  #else
    #define GALIOT_SNAP_RPL_DAG_REFRESH_ROUTES                        0
  #endif

  #if GALIOT_SNAP_RPL_DAG_GLOBAL_REPAIR_CONF
    #define GALIOT_SNAP_RPL_DAG_GLOBAL_REPAIR                         GALIOT_SNAP_RPL_DAG_GLOBAL_REPAIR_CONF
    #define GALIOT_PRINT_RPL_DAG_GLOBAL_REPAIR                         GALIOT_PRINT_RPL_DAG_GLOBAL_REPAIR_CONF
  #else
    #define GALIOT_SNAP_RPL_DAG_GLOBAL_REPAIR                         0
  #endif

  #if GALIOT_SNAP_RPL_DAG_GLOBAL_REPAIR_NON_ROOT_CONF
    #define GALIOT_SNAP_RPL_DAG_GLOBAL_REPAIR_NON_ROOT                GALIOT_SNAP_RPL_DAG_GLOBAL_REPAIR_NON_ROOT_CONF
    #define GALIOT_PRINT_RPL_DAG_GLOBAL_REPAIR_NON_ROOT                GALIOT_PRINT_RPL_DAG_GLOBAL_REPAIR_NON_ROOT_CONF
  #else
    #define GALIOT_SNAP_RPL_DAG_GLOBAL_REPAIR_NON_ROOT                0
  #endif

  #if GALIOT_SNAP_RPL_DAG_LOCAL_REPAIR_CONF
    #define GALIOT_SNAP_RPL_DAG_LOCAL_REPAIR                          GALIOT_SNAP_RPL_DAG_LOCAL_REPAIR_CONF
    #define GALIOT_PRINT_RPL_DAG_LOCAL_REPAIR                          GALIOT_PRINT_RPL_DAG_LOCAL_REPAIR_CONF
  #else
    #define GALIOT_SNAP_RPL_DAG_LOCAL_REPAIR                          0
  #endif

  #if GALIOT_SNAP_RPL_DAG_UPDATE_STATE_CONF
    #define GALIOT_SNAP_RPL_DAG_UPDATE_STATE                          GALIOT_SNAP_RPL_DAG_UPDATE_STATE_CONF
    #define GALIOT_PRINT_RPL_DAG_UPDATE_STATE                          GALIOT_PRINT_RPL_DAG_UPDATE_STATE_CONF
  #else
    #define GALIOT_SNAP_RPL_DAG_UPDATE_STATE                          0
  #endif

  #if GALIOT_SNAP_RPL_DAG_UPDATE_NBR_FROM_DIO_CONF
    #define GALIOT_SNAP_RPL_DAG_UPDATE_NBR_FROM_DIO                   GALIOT_SNAP_RPL_DAG_UPDATE_NBR_FROM_DIO_CONF
    #define GALIOT_PRINT_RPL_DAG_UPDATE_NBR_FROM_DIO                   GALIOT_PRINT_RPL_DAG_UPDATE_NBR_FROM_DIO_CONF
  #else
    #define GALIOT_SNAP_RPL_DAG_UPDATE_NBR_FROM_DIO                   0
  #endif

  #if GALIOT_SNAP_RPL_DAG_PROCESS_DIO_FROM_CURRENT_DAG_CONF
    #define GALIOT_SNAP_RPL_DAG_PROCESS_DIO_FROM_CURRENT_DAG          GALIOT_SNAP_RPL_DAG_PROCESS_DIO_FROM_CURRENT_DAG_CONF
    #define GALIOT_PRINT_RPL_DAG_PROCESS_DIO_FROM_CURRENT_DAG          GALIOT_PRINT_RPL_DAG_PROCESS_DIO_FROM_CURRENT_DAG_CONF
  #else
    #define GALIOT_SNAP_RPL_DAG_PROCESS_DIO_FROM_CURRENT_DAG          0
  #endif

  #if GALIOT_SNAP_RPL_DAG_INIT_DAG_CONF
    #define GALIOT_SNAP_RPL_DAG_INIT_DAG                              GALIOT_SNAP_RPL_DAG_INIT_DAG_CONF
    #define GALIOT_PRINT_RPL_DAG_INIT_DAG                              GALIOT_PRINT_RPL_DAG_INIT_DAG_CONF
  #else
    #define GALIOT_SNAP_RPL_DAG_INIT_DAG                              0
  #endif

  #if GALIOT_SNAP_RPL_DAG_PROCESS_DIO_INIT_DAG_CONF
    #define GALIOT_SNAP_RPL_DAG_PROCESS_DIO_INIT_DAG                  GALIOT_SNAP_RPL_DAG_PROCESS_DIO_INIT_DAG_CONF
    #define GALIOT_PRINT_RPL_DAG_PROCESS_DIO_INIT_DAG                  GALIOT_PRINT_RPL_DAG_PROCESS_DIO_INIT_DAG_CONF
  #else
    #define GALIOT_SNAP_RPL_DAG_PROCESS_DIO_INIT_DAG                  0
  #endif

  #if GALIOT_SNAP_RPL_DAG_PROCESS_DIO_CONF
    #define GALIOT_SNAP_RPL_DAG_PROCESS_DIO                           GALIOT_SNAP_RPL_DAG_PROCESS_DIO_CONF
    #define GALIOT_PRINT_RPL_DAG_PROCESS_DIO                           GALIOT_PRINT_RPL_DAG_PROCESS_DIO_CONF
  #else
    #define GALIOT_SNAP_RPL_DAG_PROCESS_DIO                           0
  #endif

  #if GALIOT_SNAP_RPL_DAG_PROCESS_DIS_CONF
    #define GALIOT_SNAP_RPL_DAG_PROCESS_DIS                           GALIOT_SNAP_RPL_DAG_PROCESS_DIS_CONF
    #define GALIOT_PRINT_RPL_DAG_PROCESS_DIS                           GALIOT_PRINT_RPL_DAG_PROCESS_DIS_CONF
  #else
    #define GALIOT_SNAP_RPL_DAG_PROCESS_DIS                           0
  #endif

  #if GALIOT_SNAP_RPL_DAG_PROCESS_DAO_CONF
    #define GALIOT_SNAP_RPL_DAG_PROCESS_DAO                           GALIOT_SNAP_RPL_DAG_PROCESS_DAO_CONF
    #define GALIOT_PRINT_RPL_DAG_PROCESS_DAO                           GALIOT_PRINT_RPL_DAG_PROCESS_DAO_CONF
  #else
    #define GALIOT_SNAP_RPL_DAG_PROCESS_DAO                           0
  #endif

  #if GALIOT_SNAP_RPL_DAG_PROCESS_DAO_ACK_CONF
    #define GALIOT_SNAP_RPL_DAG_PROCESS_DAO_ACK                       GALIOT_SNAP_RPL_DAG_PROCESS_DAO_ACK_CONF
    #define GALIOT_PRINT_RPL_DAG_PROCESS_DAO_ACK                       GALIOT_PRINT_RPL_DAG_PROCESS_DAO_ACK_CONF
  #else
    #define GALIOT_SNAP_RPL_DAG_PROCESS_DAO_ACK                       0
  #endif

  #if GALIOT_SNAP_RPL_DAG_PROCESS_HBH_CONF
    #define GALIOT_SNAP_RPL_DAG_PROCESS_HBH                           GALIOT_SNAP_RPL_DAG_PROCESS_HBH_CONF
     #define GALIOT_PRINT_RPL_DAG_PROCESS_HBH                           GALIOT_PRINT_RPL_DAG_PROCESS_HBH_CONF
  #else
    #define GALIOT_SNAP_RPL_DAG_PROCESS_HBH                           0
  #endif

  #if GALIOT_SNAP_RPL_DAG_INIT_ROOT_CONF
    #define GALIOT_SNAP_RPL_DAG_INIT_ROOT                             GALIOT_SNAP_RPL_DAG_INIT_ROOT_CONF
    #define GALIOT_PRINT_RPL_DAG_INIT_ROOT                             GALIOT_PRINT_RPL_DAG_INIT_ROOT_CONF
  #else
    #define GALIOT_SNAP_RPL_DAG_INIT_ROOT                             0
  #endif

  /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/

  #if GALIOT_SNAP_RPL_EXT_HEADER_SRH_GET_NEXT_HOP_CONF 
    #define GALIOT_SNAP_RPL_EXT_HEADER_SRH_GET_NEXT_HOP               GALIOT_SNAP_RPL_EXT_HEADER_SRH_GET_NEXT_HOP_CONF
    #define GALIOT_PRINT_RPL_EXT_HEADER_SRH_GET_NEXT_HOP               GALIOT_PRINT_RPL_EXT_HEADER_SRH_GET_NEXT_HOP_CONF
  #else
    #define GALIOT_SNAP_RPL_EXT_HEADER_SRH_GET_NEXT_HOP               0
  #endif

  #if GALIOT_SNAP_RPL_EXT_HEADER_SRH_UPDATE_CONF 
    #define GALIOT_SNAP_RPL_EXT_HEADER_SRH_UPDATE                     GALIOT_SNAP_RPL_EXT_HEADER_SRH_UPDATE_CONF
    #define GALIOT_PRINT_RPL_EXT_HEADER_SRH_UPDATE                     GALIOT_PRINT_RPL_EXT_HEADER_SRH_UPDATE_CONF
  #else
    #define GALIOT_SNAP_RPL_EXT_HEADER_SRH_UPDATE                     0
  #endif

  #if GALIOT_SNAP_RPL_EXT_HEADER_INSERT_SRH_HEADER_CONF
    #define GALIOT_SNAP_RPL_EXT_HEADER_INSERT_SRH_HEADER              GALIOT_SNAP_RPL_EXT_HEADER_INSERT_SRH_HEADER_CONF
    #define GALIOT_PRINT_RPL_EXT_HEADER_INSERT_SRH_HEADER              GALIOT_PRINT_RPL_EXT_HEADER_INSERT_SRH_HEADER_CONF
  #else
    #define GALIOT_SNAP_RPL_EXT_HEADER_INSERT_SRH_HEADER              0
  #endif

  #if GALIOT_SNAP_RPL_EXT_HEADER_SBH_UPDATE_CONF
    #define GALIOT_SNAP_RPL_EXT_HEADER_SBH_UPDATE                     GALIOT_SNAP_RPL_EXT_HEADER_SBH_UPDATE_CONF
    #define GALIOT_PRINT_RPL_EXT_HEADER_SBH_UPDATE                     GALIOT_PRINT_RPL_EXT_HEADER_SBH_UPDATE_CONF
  #else
    #define GALIOT_SNAP_RPL_EXT_HEADER_SBH_UPDATE                     0
  #endif

  #if GALIOT_SNAP_RPL_EXT_HEADER_UPDATE_HBH_HEADER_CONF
    #define GALIOT_SNAP_RPL_EXT_HEADER_UPDATE_HBH_HEADER              GALIOT_SNAP_RPL_EXT_HEADER_UPDATE_HBH_HEADER_CONF
    #define GALIOT_PRINT_RPL_EXT_HEADER_UPDATE_HBH_HEADER              GALIOT_PRINT_RPL_EXT_HEADER_UPDATE_HBH_HEADER_CONF
  #else
    #define GALIOT_SNAP_RPL_EXT_HEADER_UPDATE_HBH_HEADER              0
  #endif

  #if GALIOT_SNAP_RPL_EXT_HEADER_INSERT_HBH_HEADER_CONF
    #define GALIOT_SNAP_RPL_EXT_HEADER_INSERT_HBH_HEADER              GALIOT_SNAP_RPL_EXT_HEADER_INSERT_HBH_HEADER_CONF
    #define GALIOT_PRINT_RPL_EXT_HEADER_INSERT_HBH_HEADER              GALIOT_PRINT_RPL_EXT_HEADER_INSERT_HBH_HEADER_CONF
  #else
    #define GALIOT_SNAP_RPL_EXT_HEADER_INSERT_HBH_HEADER              0
  #endif

  /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/

  #if GALIOT_SNAP_RPL_ICMP6_UPDATE_NBR_TABLE_CONF  
    #define GALIOT_SNAP_RPL_ICMP6_UPDATE_NBR_TABLE                    GALIOT_SNAP_RPL_ICMP6_UPDATE_NBR_TABLE_CONF
    #define GALIOT_PRINT_RPL_ICMP6_UPDATE_NBR_TABLE                    GALIOT_PRINT_RPL_ICMP6_UPDATE_NBR_TABLE_CONF
  #else
    #define GALIOT_SNAP_RPL_ICMP6_UPDATE_NBR_TABLE                    0
  #endif

  #if GALIOT_SNAP_RPL_ICMP6_DIS_INPUT_CONF  
    #define GALIOT_SNAP_RPL_ICMP6_DIS_INPUT                           GALIOT_SNAP_RPL_ICMP6_DIS_INPUT_CONF
    #define GALIOT_PRINT_RPL_ICMP6_DIS_INPUT                           GALIOT_PRINT_RPL_ICMP6_DIS_INPUT_CONF
  #else
    #define GALIOT_SNAP_RPL_ICMP6_DIS_INPUT                           0
  #endif

  #if GALIOT_SNAP_RPL_ICMP6_DIS_OUTPUT_CONF  
    #define GALIOT_SNAP_RPL_ICMP6_DIS_OUTPUT                          GALIOT_SNAP_RPL_ICMP6_DIS_OUTPUT_CONF
    #define GALIOT_PRINT_RPL_ICMP6_DIS_OUTPUT                          GALIOT_PRINT_RPL_ICMP6_DIS_OUTPUT_CONF
  #else
    #define GALIOT_SNAP_RPL_ICMP6_DIS_OUTPUT                          0
  #endif

  #if GALIOT_SNAP_RPL_ICMP6_DIO_INPUT_CONF  
    #define GALIOT_SNAP_RPL_ICMP6_DIO_INPUT                           GALIOT_SNAP_RPL_ICMP6_DIO_INPUT_CONF
    #define GALIOT_PRINT_RPL_ICMP6_DIO_INPUT                           GALIOT_PRINT_RPL_ICMP6_DIO_INPUT_CONF
  #else
    #define GALIOT_SNAP_RPL_ICMP6_DIO_INPUT                           0
  #endif

  #if GALIOT_SNAP_RPL_ICMP6_DIO_OUTPUT_CONF  
    #define GALIOT_SNAP_RPL_ICMP6_DIO_OUTPUT                          GALIOT_SNAP_RPL_ICMP6_DIO_OUTPUT_CONF
    #define GALIOT_PRINT_RPL_ICMP6_DIO_OUTPUT                          GALIOT_PRINT_RPL_ICMP6_DIO_OUTPUT_CONF
  #else
    #define GALIOT_SNAP_RPL_ICMP6_DIO_OUTPUT                          0
  #endif

  #if GALIOT_SNAP_RPL_ICMP6_DAO_INPUT_CONF  
    #define GALIOT_SNAP_RPL_ICMP6_DAO_INPUT                           GALIOT_SNAP_RPL_ICMP6_DAO_INPUT_CONF
    #define GALIOT_PRINT_RPL_ICMP6_DAO_INPUT                           GALIOT_PRINT_RPL_ICMP6_DAO_INPUT_CONF
  #else
    #define GALIOT_SNAP_RPL_ICMP6_DAO_INPUT                           0
  #endif

  #if GALIOT_SNAP_RPL_ICMP6_DAO_OUTPUT_CONF  
    #define GALIOT_SNAP_RPL_ICMP6_DAO_OUTPUT                          GALIOT_SNAP_RPL_ICMP6_DAO_OUTPUT_CONF
    #define GALIOT_PRINT_RPL_ICMP6_DAO_OUTPUT                          GALIOT_PRINT_RPL_ICMP6_DAO_OUTPUT_CONF
  #else
    #define GALIOT_SNAP_RPL_ICMP6_DAO_OUTPUT                          0
  #endif

  #if GALIOT_SNAP_RPL_ICMP6_DAO_ACK_INPUT_CONF 
    #define GALIOT_SNAP_RPL_ICMP6_DAO_ACK_INPUT                       GALIOT_SNAP_RPL_ICMP6_DAO_ACK_INPUT_CONF
    #define GALIOT_PRINT_RPL_ICMP6_DAO_ACK_INPUT                       GALIOT_PRINT_RPL_ICMP6_DAO_ACK_INPUT_CONF
  #else
    #define GALIOT_SNAP_RPL_ICMP6_DAO_ACK_INPUT                       0
  #endif

  #if GALIOT_SNAP_RPL_ICMP6_DAO_ACK_OUTPUT_CONF 
    #define GALIOT_SNAP_RPL_ICMP6_DAO_ACK_OUTPUT                      GALIOT_SNAP_RPL_ICMP6_DAO_ACK_OUTPUT_CONF
    #define GALIOT_PRINT_RPL_ICMP6_DAO_ACK_OUTPUT                      GALIOT_PRINT_RPL_ICMP6_DAO_ACK_OUTPUT_CONF
  #else
    #define GALIOT_SNAP_RPL_ICMP6_DAO_ACK_OUTPUT                      0
  #endif

  /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/

  #if GALIOT_SNAP_RPL_MRHOF_RESET_CONF
    #define GALIOT_SNAP_RPL_MRHOF_RESET                               GALIOT_SNAP_RPL_MRHOF_RESET_CONF
    #define GALIOT_PRINT_RPL_MRHOF_RESET                               GALIOT_PRINT_RPL_MRHOF_RESET_CONF
  #else
    #define GALIOT_SNAP_RPL_MRHOF_RESET                               0
  #endif

  #if GALIOT_SNAP_RPL_MRHOF_UPDATE_METRIC_CONTAINER_CONF  
    #define GALIOT_SNAP_RPL_MRHOF_UPDATE_METRIC_CONTAINER             GALIOT_SNAP_RPL_MRHOF_UPDATE_METRIC_CONTAINER_CONF
    #define GALIOT_PRINT_RPL_MRHOF_UPDATE_METRIC_CONTAINER             GALIOT_PRINT_RPL_MRHOF_UPDATE_METRIC_CONTAINER_CONF
  #else
    #define GALIOT_SNAP_RPL_MRHOF_UPDATE_METRIC_CONTAINER             0
  #endif

  /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/

  #if GALIOT_SNAP_RPL_NBR_POLICY_FIND_REMOVABLE_DIO_CONF
    #define GALIOT_SNAP_RPL_NBR_POLICY_FIND_REMOVABLE_DIO             GALIOT_SNAP_RPL_NBR_POLICY_FIND_REMOVABLE_DIO_CONF
    #define GALIOT_PRINT_RPL_NBR_POLICY_FIND_REMOVABLE_DIO             GALIOT_PRINT_RPL_NBR_POLICY_FIND_REMOVABLE_DIO_CONF
  #else
    #define GALIOT_SNAP_RPL_NBR_POLICY_FIND_REMOVABLE_DIO             0
  #endif

  /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/

  #if GALIOT_SNAP_RPL_NEIGHBOR_PRINT_LIST_OWNSTATE_CONF
    #define GALIOT_SNAP_RPL_NEIGHBOR_PRINT_LIST_OWNSTATE              GALIOT_SNAP_RPL_NEIGHBOR_PRINT_LIST_OWNSTATE_CONF
    #define GALIOT_PRINT_RPL_NEIGHBOR_PRINT_LIST_OWNSTATE              GALIOT_PRINT_RPL_NEIGHBOR_PRINT_LIST_OWNSTATE_CONF
  #else
    #define GALIOT_SNAP_RPL_NEIGHBOR_PRINT_LIST_OWNSTATE              0
  #endif

  #if GALIOT_SNAP_RPL_NEIGHBOR_PRINT_LIST_NBR_CONF
    #define GALIOT_SNAP_RPL_NEIGHBOR_PRINT_LIST_NBR                   GALIOT_SNAP_RPL_NEIGHBOR_PRINT_LIST_NBR_CONF
    #define GALIOT_PRINT_RPL_NEIGHBOR_PRINT_LIST_NBR                   GALIOT_PRINT_RPL_NEIGHBOR_PRINT_LIST_NBR_CONF
  #else
    #define GALIOT_SNAP_RPL_NEIGHBOR_PRINT_LIST_NBR                   0
  #endif

  #if GALIOT_SNAP_RPL_NEIGHBOR_SET_PREFERRED_PARENT_CONF
    #define GALIOT_SNAP_RPL_NEIGHBOR_SET_PREFERRED_PARENT             GALIOT_SNAP_RPL_NEIGHBOR_SET_PREFERRED_PARENT_CONF
    #define GALIOT_PRINT_RPL_NEIGHBOR_SET_PREFERRED_PARENT             GALIOT_PRINT_RPL_NEIGHBOR_SET_PREFERRED_PARENT_CONF
  #else
    #define GALIOT_SNAP_RPL_NEIGHBOR_SET_PREFERRED_PARENT             0
  #endif

  #if GALIOT_SNAP_RPL_NEIGHBOR_REMOVE_ALL_CONF
    #define GALIOT_SNAP_RPL_NEIGHBOR_REMOVE_ALL                       GALIOT_SNAP_RPL_NEIGHBOR_REMOVE_ALL_CONF
    #define GALIOT_PRINT_RPL_NEIGHBOR_REMOVE_ALL                       GALIOT_PRINT_RPL_NEIGHBOR_REMOVE_ALL_CONF
  #else
    #define GALIOT_SNAP_RPL_NEIGHBOR_REMOVE_ALL                       0
  #endif

  #if GALIOT_SNAP_RPL_NEIGHBOR_SELECT_BEST_CONF
    #define GALIOT_SNAP_RPL_NEIGHBOR_SELECT_BEST                      GALIOT_SNAP_RPL_NEIGHBOR_SELECT_BEST_CONF
    #define GALIOT_PRINT_RPL_NEIGHBOR_SELECT_BEST                      GALIOT_PRINT_RPL_NEIGHBOR_SELECT_BEST_CONF
  #else
    #define GALIOT_SNAP_RPL_NEIGHBOR_SELECT_BEST                      0
  #endif

  /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/

  #if GALIOT_SNAP_RPL_OF0_CONF
    #define GALIOT_SNAP_RPL_OF0                                        GALIOT_SNAP_RPL_OF0_CONF
    #define GALIOT_PRINT_RPL_OF0                                        GALIOT_PRINT_RPL_OF0_CONF
  #else
   #define GALIOT_SNAP_RPL_OF0                                         0
  #endif

  /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/

  #if GALIOT_SNAP_RPL_TIMERS_DIO_RESET_CONF
    #define GALIOT_SNAP_RPL_TIMERS_DIO_RESET                          GALIOT_SNAP_RPL_TIMERS_DIO_RESET_CONF
    #define GALIOT_PRINT_RPL_TIMERS_DIO_RESET                          GALIOT_PRINT_RPL_TIMERS_DIO_RESET_CONF
  #else
    #define GALIOT_SNAP_RPL_TIMERS_DIO_RESET                          0
  #endif

  #if GALIOT_SNAP_RPL_TIMERS_HANDLE_DIO_TIMER_CONF
    #define GALIOT_SNAP_RPL_TIMERS_HANDLE_DIO_TIMER                   GALIOT_SNAP_RPL_TIMERS_HANDLE_DIO_TIMER_CONF
    #define GALIOT_PRINT_RPL_TIMERS_HANDLE_DIO_TIMER                   GALIOT_PRINT_RPL_TIMERS_HANDLE_DIO_TIMER_CONF
  #else
    #define GALIOT_SNAP_RPL_TIMERS_HANDLE_DIO_TIMER                   0
  #endif

  #if GALIOT_SNAP_RPL_TIMERS_HANDLE_PROBING_TIMER_CONF
    #define GALIOT_SNAP_RPL_TIMERS_HANDLE_PROBING_TIMER               GALIOT_SNAP_RPL_TIMERS_HANDLE_PROBING_TIMER_CONF
    #define GALIOT_PRINT_RPL_TIMERS_HANDLE_PROBING_TIMER               GALIOT_PRINT_RPL_TIMERS_HANDLE_PROBING_TIMER_CONF
  #else
    #define GALIOT_SNAP_RPL_TIMERS_HANDLE_PROBING_TIMER               0
  #endif

  /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/

  #if GALIOT_SNAP_RPL_LINK_CALLBACK_CONF
    #define GALIOT_SNAP_RPL_LINK_CALLBACK                             GALIOT_SNAP_RPL_LINK_CALLBACK_CONF
    #define GALIOT_PRINT_RPL_LINK_CALLBACK                             GALIOT_PRINT_RPL_LINK_CALLBACK_CONF
  #else
    #define GALIOT_SNAP_RPL_LINK_CALLBACK                             0
  #endif

  #if GALIOT_SNAP_RPL_RESET_PREFIX_CONF   
    #define GALIOT_SNAP_RPL_RESET_PREFIX                              GALIOT_SNAP_RPL_RESET_PREFIX_CONF
    #define GALIOT_PRINT_RPL_RESET_PREFIX                              GALIOT_PRINT_RPL_RESET_PREFIX_CONF   
  #else
    #define GALIOT_SNAP_RPL_RESET_PREFIX                              0
  #endif

  #if GALIOT_SNAP_RPL_SET_PREFIX_FROM_ADDR_CONF
    #define GALIOT_SNAP_RPL_SET_PREFIX_FROM_ADDR                      GALIOT_SNAP_RPL_SET_PREFIX_FROM_ADDR_CONF
    #define GALIOT_PRINT_RPL_SET_PREFIX_FROM_ADDR                      GALIOT_PRINT_RPL_SET_PREFIX_FROM_ADDR_CONF
  #else
    #define GALIOT_SNAP_RPL_SET_PREFIX_FROM_ADDR                      0
  #endif

  #if GALIOT_SNAP_RPL_INIT_CONF 
    #define GALIOT_SNAP_RPL_INIT                                      GALIOT_SNAP_RPL_INIT_CONF 
    #define GALIOT_PRINT_RPL_INIT                                      GALIOT_PRINT_RPL_INIT_CONF 
  #else
    #define GALIOT_SNAP_RPL_INIT                                      0
  #endif

#endif /* GALIOT_FUNCTIONALITY */
/*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
/*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
/*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/








#endif /* PROJECT_CONF_H_ */
