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
#define LOG_CONF_LEVEL_RPL                         LOG_LEVEL_INFO
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
#define GALIOT_CONF_FUNCTIONALITY                                    1
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
#if GALIOT_FUNCTIONALITY

  #define GALIOT_SNAP_RPL_NEIGHBOR_PRINT_LIST_OWNSTATE_CONF           0
  #define GALIOT_SNAP_RPL_NEIGHBOR_PRINT_LIST_NBR_CONF                0
  #define GALIOT_SNAP_RPL_NEIGHBOR_SET_PREFERRED_PARENT_CONF          0
  #define GALIOT_SNAP_RPL_NEIGHBOR_REMOVE_ALL_CONF                    0
  #define GALIOT_SNAP_RPL_NEIGHBOR_SELECT_BEST_CONF                   0

  #define GALIOT_SNAP_RPL_LINK_CALLBACK_CONF                          0
  #define GALIOT_SNAP_RPL_RESET_PREFIX_CONF                           0
  #define GALIOT_SNAP_RPL_SET_PREFIX_FROM_ADDR_CONF                   0
  #define GALIOT_SNAP_RPL_INIT_CONF                                   0

  /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/

  #if GALIOT_SNAP_RPL_NEIGHBOR_PRINT_LIST_OWNSTATE_CONF
    #define GALIOT_SNAP_RPL_NEIGHBOR_PRINT_LIST_OWNSTATE              GALIOT_SNAP_RPL_NEIGHBOR_PRINT_LIST_OWNSTATE_CONF
  #else
    #define GALIOT_SNAP_RPL_NEIGHBOR_PRINT_LIST_OWNSTATE              0
  #endif

  #if GALIOT_SNAP_RPL_NEIGHBOR_PRINT_LIST_NBR_CONF
    #define GALIOT_SNAP_RPL_NEIGHBOR_PRINT_LIST_NBR                   GALIOT_SNAP_RPL_NEIGHBOR_PRINT_LIST_NBR_CONF
  #else
    #define GALIOT_SNAP_RPL_NEIGHBOR_PRINT_LIST_NBR                   0
  #endif

  #if GALIOT_SNAP_RPL_NEIGHBOR_SET_PREFERRED_PARENT_CONF
    #define GALIOT_SNAP_RPL_NEIGHBOR_SET_PREFERRED_PARENT             GALIOT_SNAP_RPL_NEIGHBOR_SET_PREFERRED_PARENT_CONF
  #else
    #define GALIOT_SNAP_RPL_NEIGHBOR_SET_PREFERRED_PARENT             0
  #endif

  #if GALIOT_SNAP_RPL_NEIGHBOR_REMOVE_ALL_CONF
    #define GALIOT_SNAP_RPL_NEIGHBOR_REMOVE_ALL                       GALIOT_SNAP_RPL_NEIGHBOR_REMOVE_ALL_CONF
  #else
    #define GALIOT_SNAP_RPL_NEIGHBOR_REMOVE_ALL                       0
  #endif

  #if GALIOT_SNAP_RPL_NEIGHBOR_SELECT_BEST_CONF
    #define GALIOT_SNAP_RPL_NEIGHBOR_SELECT_BEST                      GALIOT_SNAP_RPL_NEIGHBOR_SELECT_BEST_CONF
  #else
    #define GALIOT_SNAP_RPL_NEIGHBOR_SELECT_BEST                      0
  #endif

  /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/

  #if GALIOT_SNAP_RPL_LINK_CALLBACK_CONF
    #define GALIOT_SNAP_RPL_LINK_CALLBACK                             GALIOT_SNAP_RPL_LINK_CALLBACK_CONF
  #else
    #define GALIOT_SNAP_RPL_LINK_CALLBACK                             0
  #endif

  #if GALIOT_SNAP_RPL_RESET_PREFIX_CONF   
    #define GALIOT_SNAP_RPL_RESET_PREFIX                              GALIOT_SNAP_RPL_RESET_PREFIX_CONF   
  #else
    #define GALIOT_SNAP_RPL_RESET_PREFIX                              0
  #endif

  #if GALIOT_SNAP_RPL_SET_PREFIX_FROM_ADDR_CONF
    #define GALIOT_SNAP_RPL_SET_PREFIX_FROM_ADDR                      GALIOT_SNAP_RPL_SET_PREFIX_FROM_ADDR_CONF
  #else
    #define GALIOT_SNAP_RPL_SET_PREFIX_FROM_ADDR                      0
  #endif

  #if GALIOT_SNAP_RPL_INIT_CONF 
    #define GALIOT_SNAP_RPL_INIT                                      GALIOT_SNAP_RPL_INIT_CONF 
  #else
    #define GALIOT_SNAP_RPL_INIT                                      0
  #endif

#endif /* GALIOT_FUNCTIONALITY */
/*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
/*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
/*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/







#endif /* PROJECT_CONF_H_ */
