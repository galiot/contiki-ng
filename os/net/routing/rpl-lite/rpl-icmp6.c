/*
 * Copyright (c) 2010, Swedish Institute of Computer Science.
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
 * \addtogroup rpl-lite
 * @{
 *
 * \file
 *         ICMP6 I/O for RPL control messages.
 *
 * \author Joakim Eriksson <joakime@sics.se>, Nicolas Tsiftes <nvt@sics.se>,
 * Simon Duquennoy <simon.duquennoy@inria.fr>
 * Contributors: Niclas Finne <nfi@sics.se>, Joel Hoglund <joel@sics.se>,
 *               Mathieu Pouillot <m.pouillot@watteco.com>,
 *               George Oikonomou <oikonomou@users.sourceforge.net> (multicast)
 */

#include "net/routing/rpl-lite/rpl.h"
#include "net/ipv6/uip-icmp6.h"
#include "net/packetbuf.h"
#include "lib/random.h"

#include <limits.h>

/* Log configuration */
#include "sys/log.h"
#define LOG_MODULE "RPL"
#define LOG_LEVEL LOG_LEVEL_RPL

/*---------------------------------------------------------------------------*/
#define RPL_DIO_GROUNDED                 0x80
#define RPL_DIO_MOP_SHIFT                3
#define RPL_DIO_MOP_MASK                 0x38
#define RPL_DIO_PREFERENCE_MASK          0x07

/*---------------------------------------------------------------------------*/
static void dis_input(void);
static void dio_input(void);
static void dao_input(void);

/*---------------------------------------------------------------------------*/
/* Initialize RPL ICMPv6 message handlers */
UIP_ICMP6_HANDLER(dis_handler, ICMP6_RPL, RPL_CODE_DIS, dis_input);
UIP_ICMP6_HANDLER(dio_handler, ICMP6_RPL, RPL_CODE_DIO, dio_input);
UIP_ICMP6_HANDLER(dao_handler, ICMP6_RPL, RPL_CODE_DAO, dao_input);

#if RPL_WITH_DAO_ACK
static void dao_ack_input(void);
UIP_ICMP6_HANDLER(dao_ack_handler, ICMP6_RPL, RPL_CODE_DAO_ACK, dao_ack_input);
#endif /* RPL_WITH_DAO_ACK */



















#if GALIOT_FUNCTIONALITY
  /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
  /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
  /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
  // INITIALIZATIONS rpl_timers
  /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
  /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
  /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/

  
  
  
  // rpl_icmp6_update_nbr_table_ERR

  /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
  #if GALIOT_SNAP_RPL_ICMP6_UPDATE_NBR_TABLE
  /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
  
  int galiot_snap_flag_rpl_icmp6_update_nbr_table_ERR = 0;
  int galiot_snap_count_rpl_icmp6_update_nbr_table_ERR = 0;
  int galiot_snap_flag_countOverflow_rpl_icmp6_update_nbr_table_ERR = 0;
    
  struct galiot_snap_struct_rpl_icmp6_update_nbr_table_ERR galiot_snap_rpl_icmp6_update_nbr_table_ERR = { {0}, {" "}, {" "} };

  /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
  #endif /* GALIOT_SNAP_RPL_ICMP6_UPDATE_NBR_TABLE */
  /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/



  // rpl_icmp6_dis_input_WARN

  /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
  #if GALIOT_SNAP_RPL_ICMP6_DIS_INPUT
  /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
  
  int galiot_snap_flag_rpl_icmp6_dis_input_WARN = 0;
  int galiot_snap_count_rpl_icmp6_dis_input_WARN = 0;
  int galiot_snap_flag_countOverflow_rpl_icmp6_dis_input_WARN = 0;
    
  struct galiot_snap_struct_rpl_icmp6_dis_input_WARN galiot_snap_rpl_icmp6_dis_input_WARN = { {0} };

  /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
  #endif /* GALIOT_SNAP_RPL_ICMP6_DIS_INPUT */
  /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/



  // rpl_icmp6_dis_input_INFO

  /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
  #if GALIOT_SNAP_RPL_ICMP6_DIS_INPUT
  /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
  
  int galiot_snap_flag_rpl_icmp6_dis_input_INFO = 0;
  int galiot_snap_count_rpl_icmp6_dis_input_INFO = 0;
  int galiot_snap_flag_countOverflow_rpl_icmp6_dis_input_INFO = 0;
    
  struct galiot_snap_struct_rpl_icmp6_dis_input_INFO galiot_snap_rpl_icmp6_dis_input_INFO = { {0}, {" "} };

  /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
  #endif /* GALIOT_SNAP_RPL_ICMP6_DIS_INPUT */
  /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/



  // rpl_icmp6_dis_output_INFO

  /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
  #if GALIOT_SNAP_RPL_ICMP6_DIS_OUTPUT
  /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
  
  int galiot_snap_flag_rpl_icmp6_dis_output_INFO = 0;
  int galiot_snap_count_rpl_icmp6_dis_output_INFO = 0;
  int galiot_snap_flag_countOverflow_rpl_icmp6_dis_output_INFO = 0;
    
  struct galiot_snap_struct_rpl_icmp6_dis_output_INFO galiot_snap_rpl_icmp6_dis_output_INFO = { {0}, {" "} };

  /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
  #endif /* GALIOT_SNAP_RPL_ICMP6_DIS_OUTPUT */
  /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/



  // rpl_icmp6_dio_input_ERR

  /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
  #if GALIOT_SNAP_RPL_ICMP6_DIO_INPUT
  /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
  
  int galiot_snap_flag_rpl_icmp6_dio_input_ERR = 0;
  int galiot_snap_count_rpl_icmp6_dio_input_ERR = 0;
  int galiot_snap_flag_countOverflow_rpl_icmp6_dio_input_ERR = 0;
    
  struct galiot_snap_struct_rpl_icmp6_dio_input_ERR galiot_snap_rpl_icmp6_dio_input_ERR = { {0} };

  /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
  #endif /* GALIOT_SNAP_RPL_ICMP6_DIO_INPUT */
  /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/



  // rpl_icmp6_dio_input_WARN_option_mc

  /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
  #if GALIOT_SNAP_RPL_ICMP6_DIO_INPUT
  /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
  
  int galiot_snap_flag_rpl_icmp6_dio_input_WARN_option_mc = 0;
  int galiot_snap_count_rpl_icmp6_dio_input_WARN_option_mc = 0;
  int galiot_snap_flag_countOverflow_rpl_icmp6_dio_input_WARN_option_mc = 0;
    
  struct galiot_snap_struct_rpl_icmp6_dio_input_WARN_option_mc galiot_snap_rpl_icmp6_dio_input_WARN_option_mc = { {0}, {0} };

  /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
  #endif /* GALIOT_SNAP_RPL_ICMP6_DIO_INPUT */
  /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/



  // rpl_icmp6_dio_input_WARN_option_mc_else

  /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
  #if GALIOT_SNAP_RPL_ICMP6_DIO_INPUT
  /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
  
  int galiot_snap_flag_rpl_icmp6_dio_input_WARN_option_mc_else = 0;
  int galiot_snap_count_rpl_icmp6_dio_input_WARN_option_mc_else = 0;
  int galiot_snap_flag_countOverflow_rpl_icmp6_dio_input_WARN_option_mc_else = 0;
    
  struct galiot_snap_struct_rpl_icmp6_dio_input_WARN_option_mc_else galiot_snap_rpl_icmp6_dio_input_WARN_option_mc_else = { {0}, {0} };

  /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
  #endif /* GALIOT_SNAP_RPL_ICMP6_DIO_INPUT */
  /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/



  // rpl_icmp6_dio_input_WARN_route

  /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
  #if GALIOT_SNAP_RPL_ICMP6_DIO_INPUT
  /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
  
  int galiot_snap_flag_rpl_icmp6_dio_input_WARN_route = 0;
  int galiot_snap_count_rpl_icmp6_dio_input_WARN_route = 0;
  int galiot_snap_flag_countOverflow_rpl_icmp6_dio_input_WARN_route = 0;
    
  struct galiot_snap_struct_rpl_icmp6_dio_input_WARN_route galiot_snap_rpl_icmp6_dio_input_WARN_route = { {0}, {0} };

  /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
  #endif /* GALIOT_SNAP_RPL_ICMP6_DIO_INPUT */
  /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/



  // rpl_icmp6_dio_input_WARN_route_else

  /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
  #if GALIOT_SNAP_RPL_ICMP6_DIO_INPUT
  /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
  
  int galiot_snap_flag_rpl_icmp6_dio_input_WARN_route_else = 0;
  int galiot_snap_count_rpl_icmp6_dio_input_WARN_route_else = 0;
  int galiot_snap_flag_countOverflow_rpl_icmp6_dio_input_WARN_route_else = 0;
    
  struct galiot_snap_struct_rpl_icmp6_dio_input_WARN_route_else galiot_snap_rpl_icmp6_dio_input_WARN_route_else = { {0}, {0} };

  /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
  #endif /* GALIOT_SNAP_RPL_ICMP6_DIO_INPUT */
  /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/



  // rpl_icmp6_dio_input_WARN_option_DAG

  /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
  #if GALIOT_SNAP_RPL_ICMP6_DIO_INPUT
  /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
  
  int galiot_snap_flag_rpl_icmp6_dio_input_WARN_option_DAG = 0;
  int galiot_snap_count_rpl_icmp6_dio_input_WARN_option_DAG = 0;
  int galiot_snap_flag_countOverflow_rpl_icmp6_dio_input_WARN_option_DAG = 0;
    
  struct galiot_snap_struct_rpl_icmp6_dio_input_WARN_option_DAG galiot_snap_rpl_icmp6_dio_input_WARN_option_DAG = { {0}, {0} };

  /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
  #endif /* GALIOT_SNAP_RPL_ICMP6_DIO_INPUT */
  /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/



  // rpl_icmp6_dio_input_WARN_option_prefix

  /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
  #if GALIOT_SNAP_RPL_ICMP6_DIO_INPUT
  /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
  
  int galiot_snap_flag_rpl_icmp6_dio_input_WARN_option_prefix = 0;
  int galiot_snap_count_rpl_icmp6_dio_input_WARN_option_prefix = 0;
  int galiot_snap_flag_countOverflow_rpl_icmp6_dio_input_WARN_option_prefix = 0;
    
  struct galiot_snap_struct_rpl_icmp6_dio_input_WARN_option_prefix galiot_snap_rpl_icmp6_dio_input_WARN_option_prefix = { {0}, {0} };

  /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
  #endif /* GALIOT_SNAP_RPL_ICMP6_DIO_INPUT */
  /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/



  // rpl_icmp6_dio_input_WARN_default

  /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
  #if GALIOT_SNAP_RPL_ICMP6_DIO_INPUT
  /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
  
  int galiot_snap_flag_rpl_icmp6_dio_input_WARN_default = 0;
  int galiot_snap_count_rpl_icmp6_dio_input_WARN_default = 0;
  int galiot_snap_flag_countOverflow_rpl_icmp6_dio_input_WARN_default = 0;
    
  struct galiot_snap_struct_rpl_icmp6_dio_input_WARN_default galiot_snap_rpl_icmp6_dio_input_WARN_default = { {0}, {0} };

  /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
  #endif /* GALIOT_SNAP_RPL_ICMP6_DIO_INPUT */
  /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/



  // rpl_icmp6_dio_input_INFO

  /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
  #if GALIOT_SNAP_RPL_ICMP6_DIO_INPUT
  /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
  
  int galiot_snap_flag_rpl_icmp6_dio_input_INFO = 0;
  int galiot_snap_count_rpl_icmp6_dio_input_INFO = 0;
  int galiot_snap_flag_countOverflow_rpl_icmp6_dio_input_INFO = 0;
    
  struct galiot_snap_struct_rpl_icmp6_dio_input_INFO galiot_snap_rpl_icmp6_dio_input_INFO = { {0}, {" "}, {" "}, {0}, {" "}, {0}, {0}, {0} };

  /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
  #endif /* GALIOT_SNAP_RPL_ICMP6_DIO_INPUT */
  /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/



  // rpl_icmp6_dio_output_ERR

  /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
  #if GALIOT_SNAP_RPL_ICMP6_DIO_OUTPUT
  /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
  
  int galiot_snap_flag_rpl_icmp6_dio_output_ERR = 0;
  int galiot_snap_count_rpl_icmp6_dio_output_ERR = 0;
  int galiot_snap_flag_countOverflow_rpl_icmp6_dio_output_ERR = 0;
    
  struct galiot_snap_struct_rpl_icmp6_dio_output_ERR galiot_snap_rpl_icmp6_dio_output_ERR = { {0}, {0} };

  /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
  #endif /* GALIOT_SNAP_RPL_ICMP6_DIO_OUTPUT */
  /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/



  // rpl_icmp6_dio_output_INFO

  /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
  #if GALIOT_SNAP_RPL_ICMP6_DIO_OUTPUT
  /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
  
  int galiot_snap_flag_rpl_icmp6_dio_output_INFO = 0;
  int galiot_snap_count_rpl_icmp6_dio_output_INFO = 0;
  int galiot_snap_flag_countOverflow_rpl_icmp6_dio_output_INFO = 0;
    
  struct galiot_snap_struct_rpl_icmp6_dio_output_INFO galiot_snap_rpl_icmp6_dio_output_INFO = { {0}, {" "}, {0}, {" "} };

  /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
  #endif /* GALIOT_SNAP_RPL_ICMP6_DIO_OUTPUT */
  /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/



  // rpl_icmp6_dao_input_ERR_unknown

  /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
  #if GALIOT_SNAP_RPL_ICMP6_DAO_INPUT
  /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
  
  int galiot_snap_flag_rpl_icmp6_dao_input_ERR_unknown = 0;
  int galiot_snap_count_rpl_icmp6_dao_input_ERR_unknown = 0;
  int galiot_snap_flag_countOverflow_rpl_icmp6_dao_input_ERR_unknown = 0;
    
  struct galiot_snap_struct_rpl_icmp6_dao_input_ERR_unknown galiot_snap_rpl_icmp6_dao_input_ERR_unknown = { {0}, {0} };

  /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
  #endif /* GALIOT_SNAP_RPL_ICMP6_DAO_INPUT */
  /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/



  // rpl_icmp6_dao_input_ERR_different

  /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
  #if GALIOT_SNAP_RPL_ICMP6_DAO_INPUT
  /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
  
  int galiot_snap_flag_rpl_icmp6_dao_input_ERR_different = 0;
  int galiot_snap_count_rpl_icmp6_dao_input_ERR_different = 0;
  int galiot_snap_flag_countOverflow_rpl_icmp6_dao_input_ERR_different = 0;
    
  struct galiot_snap_struct_rpl_icmp6_dao_input_ERR_different galiot_snap_rpl_icmp6_dao_input_ERR_different = { {0}, {" "} };

  /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
  #endif /* GALIOT_SNAP_RPL_ICMP6_DAO_INPUT */
  /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/



  // rpl_icmp6_dao_input_INFO

  /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
  #if GALIOT_SNAP_RPL_ICMP6_DAO_INPUT
  /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
  
  int galiot_snap_flag_rpl_icmp6_dao_input_INFO = 0;
  int galiot_snap_count_rpl_icmp6_dao_input_INFO = 0;
  int galiot_snap_flag_countOverflow_rpl_icmp6_dao_input_INFO = 0;
    
  struct galiot_snap_struct_rpl_icmp6_dao_input_INFO galiot_snap_rpl_icmp6_dao_input_INFO = { {0}, {" "}, {" "}, {0}, {0}, {" "}, {0}, {" "} };

  /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
  #endif /* GALIOT_SNAP_RPL_ICMP6_DAO_INPUT */
  /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/




  


  

  /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
  /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
  /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
#endif /* GALIOT_FUNCTIONALITY */





























/*---------------------------------------------------------------------------*/
static uint32_t
get32(uint8_t *buffer, int pos)
{
  return ((uint32_t)buffer[pos] << 24 | (uint32_t)buffer[pos + 1] << 16 |
          (uint32_t)buffer[pos + 2] << 8 | buffer[pos + 3]);
}
/*---------------------------------------------------------------------------*/
static void
set32(uint8_t *buffer, int pos, uint32_t value)
{
  buffer[pos++] = value >> 24;
  buffer[pos++] = (value >> 16) & 0xff;
  buffer[pos++] = (value >> 8) & 0xff;
  buffer[pos++] = value & 0xff;
}
/*---------------------------------------------------------------------------*/
static uint16_t
get16(uint8_t *buffer, int pos)
{
  return (uint16_t)buffer[pos] << 8 | buffer[pos + 1];
}
/*---------------------------------------------------------------------------*/
static void
set16(uint8_t *buffer, int pos, uint16_t value)
{
  buffer[pos++] = value >> 8;
  buffer[pos++] = value & 0xff;
}
/*---------------------------------------------------------------------------*/
uip_ds6_nbr_t *
rpl_icmp6_update_nbr_table(uip_ipaddr_t *from, nbr_table_reason_t reason, void *data)
{
  uip_ds6_nbr_t *nbr;

  if((nbr = uip_ds6_nbr_lookup(from)) == NULL) {
    if((nbr = uip_ds6_nbr_add(from, (uip_lladdr_t *)
                              packetbuf_addr(PACKETBUF_ADDR_SENDER),
                              0, NBR_REACHABLE, reason, data)) == NULL) {
      LOG_ERR("could not add neighbor to cache ");
      LOG_ERR_6ADDR(from);
      LOG_ERR_(", ");
      LOG_ERR_LLADDR(packetbuf_addr(PACKETBUF_ADDR_SENDER));
      LOG_ERR_("\n");





      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      // SNAP: rpl_icmp6_update_nbr_table_ERR
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      #if GALIOT_FUNCTIONALITY

        /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
        #if GALIOT_SNAP_RPL_ICMP6_UPDATE_NBR_TABLE
        /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/

        /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
        char galiot_lladdr_str[40];
        char galiot_lladdr_buf[2];

        if((packetbuf_addr(PACKETBUF_ADDR_SENDER)) == NULL)
        {
         strcpy(galiot_lladdr_str, "(NULL addr)");
        }
        else
        {
         for(unsigned int i = 0; i < LINKADDR_SIZE; i++) 
         {
           if(i > 0 && i % 2 == 0) 
           {
             strcat(galiot_lladdr_str, ".");
           }
           sprintf(galiot_lladdr_buf, "%02x", (packetbuf_addr(PACKETBUF_ADDR_SENDER))->u8[i]);
           strcat(galiot_lladdr_str, galiot_lladdr_buf);
         }
        }
        /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/

        /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
        galiot_snap_flag_rpl_icmp6_update_nbr_table_ERR = 1;
        galiot_snap_count_rpl_icmp6_update_nbr_table_ERR++;
      
        if (galiot_snap_count_rpl_icmp6_update_nbr_table_ERR == 604)  
        {
          galiot_snap_flag_countOverflow_rpl_icmp6_update_nbr_table_ERR = 1;
          galiot_snap_count_rpl_icmp6_update_nbr_table_ERR = 1;
        }
        /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      
        /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
        int galiot_snap_index = (galiot_snap_count_rpl_icmp6_update_nbr_table_ERR - 1) % GALIOT_SNAPSHOT_COUNT;
      
        galiot_snap_rpl_icmp6_update_nbr_table_ERR.system_time[galiot_snap_index] = clock_seconds();
        uiplib_ipaddr_snprint(galiot_snap_rpl_icmp6_update_nbr_table_ERR.from_6addr[galiot_snap_index], sizeof(galiot_snap_rpl_icmp6_update_nbr_table_ERR.from_6addr[galiot_snap_index]), from);
        strcpy(galiot_snap_rpl_icmp6_update_nbr_table_ERR.packetbuf_lladdr[galiot_snap_index], galiot_lladdr_str);
        /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/

        /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
        #endif /* GALIOT_SNAP_RPL_ICMP6_UPDATE_NBR_TABLE */
        /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/

      #endif /* GALIOT_FUNCTIONALITY */
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/





    }
  }

  return nbr;
}
/*---------------------------------------------------------------------------*/
static void
dis_input(void)
{
  if(!curr_instance.used) {
    LOG_WARN("dis_input: not in an instance yet, discard\n");





    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    // SNAP: rpl_icmp6_dis_input_WARN
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    #if GALIOT_FUNCTIONALITY

      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #if GALIOT_SNAP_RPL_ICMP6_DIS_INPUT
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/

      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      galiot_snap_flag_rpl_icmp6_dis_input_WARN = 1;
      galiot_snap_count_rpl_icmp6_dis_input_WARN++;
      
      if (galiot_snap_count_rpl_icmp6_dis_input_WARN == 604)  
      {
        galiot_snap_flag_countOverflow_rpl_icmp6_dis_input_WARN = 1;
        galiot_snap_count_rpl_icmp6_dis_input_WARN = 1;
      }
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      int galiot_snap_index = (galiot_snap_count_rpl_icmp6_dis_input_WARN - 1) % GALIOT_SNAPSHOT_COUNT;
      
      galiot_snap_rpl_icmp6_dis_input_WARN.system_time[galiot_snap_index] = clock_seconds();
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/

      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #endif /* GALIOT_SNAP_RPL_ICMP6_DIS_INPUT */
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/

    #endif /* GALIOT_FUNCTIONALITY */
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/





    goto discard;
  }

  LOG_INFO("received a DIS from ");
  LOG_INFO_6ADDR(&UIP_IP_BUF->srcipaddr);
  LOG_INFO_("\n");





  /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
  /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
  /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
  // SNAP: rpl_icmp6_dis_input_INFO
  /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
  /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
  /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
  #if GALIOT_FUNCTIONALITY

    /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
    #if GALIOT_SNAP_RPL_ICMP6_DIS_INPUT
    /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/

    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    galiot_snap_flag_rpl_icmp6_dis_input_INFO = 1;
    galiot_snap_count_rpl_icmp6_dis_input_INFO++;
    
    if (galiot_snap_count_rpl_icmp6_dis_input_INFO == 604)  
    {
      galiot_snap_flag_countOverflow_rpl_icmp6_dis_input_INFO = 1;
      galiot_snap_count_rpl_icmp6_dis_input_INFO = 1;
    }
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    int galiot_snap_index = (galiot_snap_count_rpl_icmp6_dis_input_INFO - 1) % GALIOT_SNAPSHOT_COUNT;
    
    galiot_snap_rpl_icmp6_dis_input_INFO.system_time[galiot_snap_index] = clock_seconds();
    uiplib_ipaddr_snprint(galiot_snap_rpl_icmp6_dis_input_INFO.DIS_from_6addr[galiot_snap_index], sizeof(galiot_snap_rpl_icmp6_dis_input_INFO.DIS_from_6addr[galiot_snap_index]), &UIP_IP_BUF->srcipaddr);
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/

    /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
    #endif /* GALIOT_SNAP_RPL_ICMP6_DIS_INPUT */
    /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/

  #endif /* GALIOT_FUNCTIONALITY */
  /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
  /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
  /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/





  rpl_process_dis(&UIP_IP_BUF->srcipaddr, uip_is_addr_mcast(&UIP_IP_BUF->destipaddr));

  discard:
    uipbuf_clear();
}
/*---------------------------------------------------------------------------*/
void
rpl_icmp6_dis_output(uip_ipaddr_t *addr)
{
  unsigned char *buffer;

  /* Make sure we're up-to-date before sending data out */
  rpl_dag_update_state();

  buffer = UIP_ICMP_PAYLOAD;
  buffer[0] = buffer[1] = 0;

  if(addr == NULL) {
    addr = &rpl_multicast_addr;
  }

  LOG_INFO("sending a DIS to ");
  LOG_INFO_6ADDR(addr);
  LOG_INFO_("\n");





  /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
  /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
  /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
  // SNAP: rpl_icmp6_dis_output_INFO
  /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
  /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
  /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
  #if GALIOT_FUNCTIONALITY

    /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
    #if GALIOT_SNAP_RPL_ICMP6_DIS_OUTPUT
    /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/

    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    galiot_snap_flag_rpl_icmp6_dis_output_INFO = 1;
    galiot_snap_count_rpl_icmp6_dis_output_INFO++;
    
    if (galiot_snap_count_rpl_icmp6_dis_output_INFO == 604)  
    {
      galiot_snap_flag_countOverflow_rpl_icmp6_dis_output_INFO = 1;
      galiot_snap_count_rpl_icmp6_dis_output_INFO = 1;
    }
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    int galiot_snap_index = (galiot_snap_count_rpl_icmp6_dis_output_INFO - 1) % GALIOT_SNAPSHOT_COUNT;
    
    galiot_snap_rpl_icmp6_dis_output_INFO.system_time[galiot_snap_index] = clock_seconds();
    uiplib_ipaddr_snprint(galiot_snap_rpl_icmp6_dis_output_INFO.DIS_to_6addr[galiot_snap_index], sizeof(galiot_snap_rpl_icmp6_dis_output_INFO.DIS_to_6addr[galiot_snap_index]), addr);
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/

    /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
    #endif /* GALIOT_SNAP_RPL_ICMP6_DIS_OUTPUT */
    /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/

  #endif /* GALIOT_FUNCTIONALITY */
  /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
  /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
  /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/





  uip_icmp6_send(addr, ICMP6_RPL, RPL_CODE_DIS, 2);
}
/*---------------------------------------------------------------------------*/
static void
dio_input(void)
{
  unsigned char *buffer;
  uint8_t buffer_length;
  rpl_dio_t dio;
  uint8_t subopt_type;
  int i;
  int len;
  uip_ipaddr_t from;

  memset(&dio, 0, sizeof(dio));

  /* Set default values in case the DIO configuration option is missing. */
  dio.dag_intdoubl = RPL_DIO_INTERVAL_DOUBLINGS;
  dio.dag_intmin = RPL_DIO_INTERVAL_MIN;
  dio.dag_redund = RPL_DIO_REDUNDANCY;
  dio.dag_min_hoprankinc = RPL_MIN_HOPRANKINC;
  dio.dag_max_rankinc = RPL_MAX_RANKINC;
  dio.ocp = RPL_OF_OCP;
  dio.default_lifetime = RPL_DEFAULT_LIFETIME;
  dio.lifetime_unit = RPL_DEFAULT_LIFETIME_UNIT;

  uip_ipaddr_copy(&from, &UIP_IP_BUF->srcipaddr);

  buffer_length = uip_len - uip_l3_icmp_hdr_len;

  /* Process the DIO base option. */
  i = 0;
  buffer = UIP_ICMP_PAYLOAD;

  dio.instance_id = buffer[i++];
  dio.version = buffer[i++];
  dio.rank = get16(buffer, i);
  i += 2;

  dio.grounded = buffer[i] & RPL_DIO_GROUNDED;
  dio.mop = (buffer[i]& RPL_DIO_MOP_MASK) >> RPL_DIO_MOP_SHIFT;
  dio.preference = buffer[i++] & RPL_DIO_PREFERENCE_MASK;

  dio.dtsn = buffer[i++];
  /* two reserved bytes */
  i += 2;

  memcpy(&dio.dag_id, buffer + i, sizeof(dio.dag_id));
  i += sizeof(dio.dag_id);

  /* Check if there are any DIO suboptions. */
  for(; i < buffer_length; i += len) {
    subopt_type = buffer[i];
    if(subopt_type == RPL_OPTION_PAD1) {
      len = 1;
    } else {
      /* Suboption with a two-byte header + payload */
      len = 2 + buffer[i + 1];
    }

    if(len + i > buffer_length) {
      LOG_ERR("dio_input: malformed packet, discard\n");





      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      // SNAP: rpl_icmp6_dio_input_ERR
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      #if GALIOT_FUNCTIONALITY

        /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
        #if GALIOT_SNAP_RPL_ICMP6_DIO_INPUT
        /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/

        /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
        galiot_snap_flag_rpl_icmp6_dio_input_ERR = 1;
        galiot_snap_count_rpl_icmp6_dio_input_ERR++;

        if (galiot_snap_count_rpl_icmp6_dio_input_ERR == 604)  
        {
          galiot_snap_flag_countOverflow_rpl_icmp6_dio_input_ERR = 1;
          galiot_snap_count_rpl_icmp6_dio_input_ERR = 1;
        }
        /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/

        /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
        int galiot_snap_index = (galiot_snap_count_rpl_icmp6_dio_input_ERR - 1) % GALIOT_SNAPSHOT_COUNT;

        galiot_snap_rpl_icmp6_dio_input_ERR.system_time[galiot_snap_index] = clock_seconds();
        /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/

        /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
        #endif /* GALIOT_SNAP_RPL_ICMP6_DIO_INPUT */
        /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/

      #endif /* GALIOT_FUNCTIONALITY */
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/






      goto discard;
    }

    switch(subopt_type) {
      case RPL_OPTION_DAG_METRIC_CONTAINER:
        if(len < 6) {
          LOG_WARN("dio_input: invalid DAG MC, len %u, discard\n", len);





          /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
          /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
          /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
          // SNAP: rpl_icmp6_dio_input_WARN_option_mc
          /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
          /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
          /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
          #if GALIOT_FUNCTIONALITY

            /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
            #if GALIOT_SNAP_RPL_ICMP6_DIO_INPUT
            /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/

            /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
            galiot_snap_flag_rpl_icmp6_dio_input_WARN_option_mc = 1;
            galiot_snap_count_rpl_icmp6_dio_input_WARN_option_mc++;

            if (galiot_snap_count_rpl_icmp6_dio_input_WARN_option_mc == 604)  
            {
              galiot_snap_flag_countOverflow_rpl_icmp6_dio_input_WARN_option_mc = 1;
              galiot_snap_count_rpl_icmp6_dio_input_WARN_option_mc = 1;
            }
            /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/

            /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
            int galiot_snap_index = (galiot_snap_count_rpl_icmp6_dio_input_WARN_option_mc - 1) % GALIOT_SNAPSHOT_COUNT;

            galiot_snap_rpl_icmp6_dio_input_WARN_option_mc.system_time[galiot_snap_index] = clock_seconds();
            galiot_snap_rpl_icmp6_dio_input_WARN_option_mc.len[galiot_snap_index] = len;
            /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/

            /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
            #endif /* GALIOT_SNAP_RPL_ICMP6_DIO_INPUT */
            /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/

          #endif /* GALIOT_FUNCTIONALITY */
          /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
          /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
          /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/






          goto discard;
        }
        dio.mc.type = buffer[i + 2];
        dio.mc.flags = buffer[i + 3] << 1;
        dio.mc.flags |= buffer[i + 4] >> 7;
        dio.mc.aggr = (buffer[i + 4] >> 4) & 0x3;
        dio.mc.prec = buffer[i + 4] & 0xf;
        dio.mc.length = buffer[i + 5];

        if(dio.mc.type == RPL_DAG_MC_NONE) {
          /* No metric container: do nothing */
        } else if(dio.mc.type == RPL_DAG_MC_ETX) {
          dio.mc.obj.etx = get16(buffer, i + 6);
        } else if(dio.mc.type == RPL_DAG_MC_ENERGY) {
          dio.mc.obj.energy.flags = buffer[i + 6];
          dio.mc.obj.energy.energy_est = buffer[i + 7];
        } else {
          LOG_WARN("dio_input: unsupported DAG MC type %u, discard\n", (unsigned)dio.mc.type);





          /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
          /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
          /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
          // SNAP: rpl_icmp6_dio_input_WARN_option_mc_else
          /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
          /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
          /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
          #if GALIOT_FUNCTIONALITY

            /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
            #if GALIOT_SNAP_RPL_ICMP6_DIO_INPUT
            /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/

            /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
            galiot_snap_flag_rpl_icmp6_dio_input_WARN_option_mc_else = 1;
            galiot_snap_count_rpl_icmp6_dio_input_WARN_option_mc_else++;

            if (galiot_snap_count_rpl_icmp6_dio_input_WARN_option_mc_else == 604)  
            {
              galiot_snap_flag_countOverflow_rpl_icmp6_dio_input_WARN_option_mc_else = 1;
              galiot_snap_count_rpl_icmp6_dio_input_WARN_option_mc_else = 1;
            }
            /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/

            /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
            int galiot_snap_index = (galiot_snap_count_rpl_icmp6_dio_input_WARN_option_mc_else - 1) % GALIOT_SNAPSHOT_COUNT;

            galiot_snap_rpl_icmp6_dio_input_WARN_option_mc_else.system_time[galiot_snap_index] = clock_seconds();
            galiot_snap_rpl_icmp6_dio_input_WARN_option_mc_else.type[galiot_snap_index] = (unsigned)dio.mc.type;
            /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/

            /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
            #endif /* GALIOT_SNAP_RPL_ICMP6_DIO_INPUT */
            /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/

          #endif /* GALIOT_FUNCTIONALITY */
          /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
          /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
          /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/





          goto discard;
        }
        break;
      case RPL_OPTION_ROUTE_INFO:
        if(len < 9) {
          LOG_WARN("dio_input: invalid destination prefix option, len %u, discard\n", len);





          /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
          /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
          /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
          // SNAP: rpl_icmp6_dio_input_WARN_route
          /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
          /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
          /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
          #if GALIOT_FUNCTIONALITY

            /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
            #if GALIOT_SNAP_RPL_ICMP6_DIO_INPUT
            /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/

            /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
            galiot_snap_flag_rpl_icmp6_dio_input_WARN_route = 1;
            galiot_snap_count_rpl_icmp6_dio_input_WARN_route++;

            if (galiot_snap_count_rpl_icmp6_dio_input_WARN_route == 604)  
            {
              galiot_snap_flag_countOverflow_rpl_icmp6_dio_input_WARN_route = 1;
              galiot_snap_count_rpl_icmp6_dio_input_WARN_route = 1;
            }
            /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/

            /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
            int galiot_snap_index = (galiot_snap_count_rpl_icmp6_dio_input_WARN_route - 1) % GALIOT_SNAPSHOT_COUNT;

            galiot_snap_rpl_icmp6_dio_input_WARN_route.system_time[galiot_snap_index] = clock_seconds();
            galiot_snap_rpl_icmp6_dio_input_WARN_route.len[galiot_snap_index] = len;
            /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/

            /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
            #endif /* GALIOT_SNAP_RPL_ICMP6_DIO_INPUT */
            /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/

          #endif /* GALIOT_FUNCTIONALITY */
          /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
          /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
          /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/





          goto discard;
        }

        /* The flags field includes the preference value. */
        dio.destination_prefix.length = buffer[i + 2];
        dio.destination_prefix.flags = buffer[i + 3];
        dio.destination_prefix.lifetime = get32(buffer, i + 4);

        if(((dio.destination_prefix.length + 7) / 8) + 8 <= len &&
           dio.destination_prefix.length <= 128) {
          memcpy(&dio.destination_prefix.prefix, &buffer[i + 8],
                 (dio.destination_prefix.length + 7) / 8);
        } else {
          LOG_WARN("dio_input: invalid route info option, len %u, discard\n", len);





          /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
          /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
          /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
          // SNAP: rpl_icmp6_dio_input_WARN_route_else
          /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
          /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
          /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
          #if GALIOT_FUNCTIONALITY

            /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
            #if GALIOT_SNAP_RPL_ICMP6_DIO_INPUT
            /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/

            /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
            galiot_snap_flag_rpl_icmp6_dio_input_WARN_route_else = 1;
            galiot_snap_count_rpl_icmp6_dio_input_WARN_route_else++;

            if (galiot_snap_count_rpl_icmp6_dio_input_WARN_route_else == 604)  
            {
              galiot_snap_flag_countOverflow_rpl_icmp6_dio_input_WARN_route_else = 1;
              galiot_snap_count_rpl_icmp6_dio_input_WARN_route_else = 1;
            }
            /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/

            /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
            int galiot_snap_index = (galiot_snap_count_rpl_icmp6_dio_input_WARN_route_else - 1) % GALIOT_SNAPSHOT_COUNT;

            galiot_snap_rpl_icmp6_dio_input_WARN_route_else.system_time[galiot_snap_index] = clock_seconds();
            galiot_snap_rpl_icmp6_dio_input_WARN_route_else.len[galiot_snap_index] = len;
            /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/

            /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
            #endif /* GALIOT_SNAP_RPL_ICMP6_DIO_INPUT */
            /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/

          #endif /* GALIOT_FUNCTIONALITY */
          /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
          /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
          /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/





          goto discard;
        }

        break;
      case RPL_OPTION_DAG_CONF:
        if(len != 16) {
          LOG_WARN("dio_input: invalid DAG configuration option, len %u, discard\n", len);





          /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
          /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
          /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
          // SNAP: rpl_icmp6_dio_input_WARN_option_DAG
          /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
          /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
          /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
          #if GALIOT_FUNCTIONALITY

            /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
            #if GALIOT_SNAP_RPL_ICMP6_DIO_INPUT
            /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/

            /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
            galiot_snap_flag_rpl_icmp6_dio_input_WARN_option_DAG = 1;
            galiot_snap_count_rpl_icmp6_dio_input_WARN_option_DAG++;

            if (galiot_snap_count_rpl_icmp6_dio_input_WARN_option_DAG == 604)  
            {
              galiot_snap_flag_countOverflow_rpl_icmp6_dio_input_WARN_option_DAG = 1;
              galiot_snap_count_rpl_icmp6_dio_input_WARN_option_DAG = 1;
            }
            /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/

            /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
            int galiot_snap_index = (galiot_snap_count_rpl_icmp6_dio_input_WARN_option_DAG - 1) % GALIOT_SNAPSHOT_COUNT;

            galiot_snap_rpl_icmp6_dio_input_WARN_option_DAG.system_time[galiot_snap_index] = clock_seconds();
            galiot_snap_rpl_icmp6_dio_input_WARN_option_DAG.len[galiot_snap_index] = len;
            /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/

            /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
            #endif /* GALIOT_SNAP_RPL_ICMP6_DIO_INPUT */
            /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/

          #endif /* GALIOT_FUNCTIONALITY */
          /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
          /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
          /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/





          goto discard;
        }

        /* Path control field not yet implemented - at i + 2 */
        dio.dag_intdoubl = buffer[i + 3];
        dio.dag_intmin = buffer[i + 4];
        dio.dag_redund = buffer[i + 5];
        dio.dag_max_rankinc = get16(buffer, i + 6);
        dio.dag_min_hoprankinc = get16(buffer, i + 8);
        dio.ocp = get16(buffer, i + 10);
        /* buffer + 12 is reserved */
        dio.default_lifetime = buffer[i + 13];
        dio.lifetime_unit = get16(buffer, i + 14);
        break;
      case RPL_OPTION_PREFIX_INFO:
        if(len != 32) {
          LOG_WARN("dio_input: invalid DAG prefix info, len %u, discard\n", len);





          /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
          /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
          /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
          // SNAP: rpl_icmp6_dio_input_WARN_option_prefix
          /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
          /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
          /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
          #if GALIOT_FUNCTIONALITY

            /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
            #if GALIOT_SNAP_RPL_ICMP6_DIO_INPUT
            /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/

            /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
            galiot_snap_flag_rpl_icmp6_dio_input_WARN_option_prefix = 1;
            galiot_snap_count_rpl_icmp6_dio_input_WARN_option_prefix++;

            if (galiot_snap_count_rpl_icmp6_dio_input_WARN_option_prefix == 604)  
            {
              galiot_snap_flag_countOverflow_rpl_icmp6_dio_input_WARN_option_prefix = 1;
              galiot_snap_count_rpl_icmp6_dio_input_WARN_option_prefix = 1;
            }
            /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/

            /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
            int galiot_snap_index = (galiot_snap_count_rpl_icmp6_dio_input_WARN_option_prefix - 1) % GALIOT_SNAPSHOT_COUNT;

            galiot_snap_rpl_icmp6_dio_input_WARN_option_prefix.system_time[galiot_snap_index] = clock_seconds();
            galiot_snap_rpl_icmp6_dio_input_WARN_option_prefix.len[galiot_snap_index] = len;
            /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/

            /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
            #endif /* GALIOT_SNAP_RPL_ICMP6_DIO_INPUT */
            /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/

          #endif /* GALIOT_FUNCTIONALITY */
          /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
          /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
          /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/





          goto discard;
        }
        dio.prefix_info.length = buffer[i + 2];
        dio.prefix_info.flags = buffer[i + 3];
        /* valid lifetime is ingnored for now - at i + 4 */
        /* preferred lifetime stored in lifetime */
        dio.prefix_info.lifetime = get32(buffer, i + 8);
        /* 32-bit reserved at i + 12 */
        memcpy(&dio.prefix_info.prefix, &buffer[i + 16], 16);
        break;
      default:
        LOG_WARN("dio_input: unsupported suboption type in DIO: %u, discard\n", (unsigned)subopt_type);





        /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
        /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
        /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
        // SNAP: rpl_icmp6_dio_input_WARN_default
        /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
        /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
        /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
        #if GALIOT_FUNCTIONALITY

          /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
          #if GALIOT_SNAP_RPL_ICMP6_DIO_INPUT
          /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/

          /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
          galiot_snap_flag_rpl_icmp6_dio_input_WARN_default = 1;
          galiot_snap_count_rpl_icmp6_dio_input_WARN_default++;

          if (galiot_snap_count_rpl_icmp6_dio_input_WARN_default == 604)  
          {
            galiot_snap_flag_countOverflow_rpl_icmp6_dio_input_WARN_default = 1;
            galiot_snap_count_rpl_icmp6_dio_input_WARN_default = 1;
          }
          /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/

          /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
          int galiot_snap_index = (galiot_snap_count_rpl_icmp6_dio_input_WARN_default - 1) % GALIOT_SNAPSHOT_COUNT;

          galiot_snap_rpl_icmp6_dio_input_WARN_default.system_time[galiot_snap_index] = clock_seconds();
          galiot_snap_rpl_icmp6_dio_input_WARN_default.type[galiot_snap_index] = (unsigned)subopt_type;
          /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/

          /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
          #endif /* GALIOT_SNAP_RPL_ICMP6_DIO_INPUT */
          /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/

        #endif /* GALIOT_FUNCTIONALITY */
        /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
        /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
        /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/





        goto discard;
    }
  }

  LOG_INFO("received a %s-DIO from ",
      uip_is_addr_mcast(&UIP_IP_BUF->destipaddr) ? "multicast" : "unicast");
  LOG_INFO_6ADDR(&from);
  LOG_INFO_(", instance_id %u, DAG ID ", (unsigned)dio.instance_id);
  LOG_INFO_6ADDR(&dio.dag_id);
  LOG_INFO_(", version %u, dtsn %u, rank %u\n",
         (unsigned)dio.version,
         (unsigned)dio.dtsn,
         (unsigned)dio.rank);





  /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
  /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
  /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
  // SNAP: rpl_icmp6_dio_input_INFO
  /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
  /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
  /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
  #if GALIOT_FUNCTIONALITY

    /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
    #if GALIOT_SNAP_RPL_ICMP6_DIO_INPUT
    /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/

    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    galiot_snap_flag_rpl_icmp6_dio_input_INFO = 1;
    galiot_snap_count_rpl_icmp6_dio_input_INFO++;
    
    if (galiot_snap_count_rpl_icmp6_dio_input_INFO == 604)  
    {
      galiot_snap_flag_countOverflow_rpl_icmp6_dio_input_INFO = 1;
      galiot_snap_count_rpl_icmp6_dio_input_INFO = 1;
    }
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    int galiot_snap_index = (galiot_snap_count_rpl_icmp6_dio_input_INFO - 1) % GALIOT_SNAPSHOT_COUNT;
    
    galiot_snap_rpl_icmp6_dio_input_INFO.system_time[galiot_snap_index] = clock_seconds();
    strcpy(galiot_snap_rpl_icmp6_dio_input_INFO.DIO_type[galiot_snap_index], uip_is_addr_mcast(&UIP_IP_BUF->destipaddr) ? "multicast" : "unicast");
    uiplib_ipaddr_snprint(galiot_snap_rpl_icmp6_dio_input_INFO.DIO_from_6ADDR[galiot_snap_index], sizeof(galiot_snap_rpl_icmp6_dio_input_INFO.DIO_from_6ADDR[galiot_snap_index]), &from);
    galiot_snap_rpl_icmp6_dio_input_INFO.instance_id[galiot_snap_index] = (unsigned)dio.instance_id;
    uiplib_ipaddr_snprint(galiot_snap_rpl_icmp6_dio_input_INFO.DAG_id_6ADDR[galiot_snap_index], sizeof(galiot_snap_rpl_icmp6_dio_input_INFO.DAG_id_6ADDR[galiot_snap_index]), &dio.dag_id);
    galiot_snap_rpl_icmp6_dio_input_INFO.version[galiot_snap_index] = (unsigned)dio.version;
    galiot_snap_rpl_icmp6_dio_input_INFO.dtsn[galiot_snap_index] = (unsigned)dio.dtsn;
    galiot_snap_rpl_icmp6_dio_input_INFO.rank[galiot_snap_index] = (unsigned)dio.rank;
    
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/

    /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
    #endif /* GALIOT_SNAP_RPL_ICMP6_DIO_INPUT */
    /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/

  #endif /* GALIOT_FUNCTIONALITY */
  /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
  /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
  /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/














  rpl_process_dio(&from, &dio);

discard:
  uipbuf_clear();
}
/*---------------------------------------------------------------------------*/
void
rpl_icmp6_dio_output(uip_ipaddr_t *uc_addr)
{
  unsigned char *buffer;
  int pos;
  uip_ipaddr_t *addr = uc_addr;

  /* Make sure we're up-to-date before sending data out */
  rpl_dag_update_state();

  if(rpl_get_leaf_only()) {
    /* In leaf mode, we only send DIO messages as unicasts in response to
       unicast DIS messages. */
    if(uc_addr == NULL) {
      /* Do not send multicast DIO in leaf mode */
      return;
    }
  }

  /* DAG Information Object */
  pos = 0;

  buffer = UIP_ICMP_PAYLOAD;
  buffer[pos++] = curr_instance.instance_id;
  buffer[pos++] = curr_instance.dag.version;

  if(rpl_get_leaf_only()) {
    set16(buffer, pos, RPL_INFINITE_RANK);
  } else {
    set16(buffer, pos, curr_instance.dag.rank);
  }
  pos += 2;

  buffer[pos] = 0;
  if(curr_instance.dag.grounded) {
    buffer[pos] |= RPL_DIO_GROUNDED;
  }

  buffer[pos] |= curr_instance.mop << RPL_DIO_MOP_SHIFT;
  buffer[pos] |= curr_instance.dag.preference & RPL_DIO_PREFERENCE_MASK;
  pos++;

  buffer[pos++] = curr_instance.dtsn_out;

  /* reserved 2 bytes */
  buffer[pos++] = 0; /* flags */
  buffer[pos++] = 0; /* reserved */

  memcpy(buffer + pos, &curr_instance.dag.dag_id, sizeof(curr_instance.dag.dag_id));
  pos += 16;

  if(!rpl_get_leaf_only()) {
    if(curr_instance.mc.type != RPL_DAG_MC_NONE) {
      buffer[pos++] = RPL_OPTION_DAG_METRIC_CONTAINER;
      buffer[pos++] = 6;
      buffer[pos++] = curr_instance.mc.type;
      buffer[pos++] = curr_instance.mc.flags >> 1;
      buffer[pos] = (curr_instance.mc.flags & 1) << 7;
      buffer[pos++] |= (curr_instance.mc.aggr << 4) | curr_instance.mc.prec;
      if(curr_instance.mc.type == RPL_DAG_MC_ETX) {
        buffer[pos++] = 2;
        set16(buffer, pos, curr_instance.mc.obj.etx);
        pos += 2;
      } else if(curr_instance.mc.type == RPL_DAG_MC_ENERGY) {
        buffer[pos++] = 2;
        buffer[pos++] = curr_instance.mc.obj.energy.flags;
        buffer[pos++] = curr_instance.mc.obj.energy.energy_est;
      } else {
        LOG_ERR("unable to send DIO because of unsupported DAG MC type %u\n",
               (unsigned)curr_instance.mc.type);

        


        /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
        /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
        /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
        // SNAP: rpl_icmp6_dio_output_ERR
        /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
        /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
        /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
        #if GALIOT_FUNCTIONALITY

          /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
          #if GALIOT_SNAP_RPL_ICMP6_DIO_OUTPUT
          /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/

          /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
          galiot_snap_flag_rpl_icmp6_dio_output_ERR = 1;
          galiot_snap_count_rpl_icmp6_dio_output_ERR++;

          if (galiot_snap_count_rpl_icmp6_dio_output_ERR == 604)  
          {
            galiot_snap_flag_countOverflow_rpl_icmp6_dio_output_ERR = 1;
            galiot_snap_count_rpl_icmp6_dio_output_ERR = 1;
          }
          /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/

          /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
          int galiot_snap_index = (galiot_snap_count_rpl_icmp6_dio_output_ERR - 1) % GALIOT_SNAPSHOT_COUNT;

          galiot_snap_rpl_icmp6_dio_output_ERR.system_time[galiot_snap_index] = clock_seconds();
          galiot_snap_rpl_icmp6_dio_output_ERR.mc_type[galiot_snap_index] = (unsigned)curr_instance.mc.type;
          /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/

          /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
          #endif /* GALIOT_SNAP_RPL_ICMP6_DIO_OUTPUT */
          /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/

        #endif /* GALIOT_FUNCTIONALITY */
        /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
        /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
        /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/






        return;
      }
    }
  }

  /* Always add a DAG configuration option. */
  buffer[pos++] = RPL_OPTION_DAG_CONF;
  buffer[pos++] = 14;
  buffer[pos++] = 0; /* No Auth, PCS = 0 */
  buffer[pos++] = curr_instance.dio_intdoubl;
  buffer[pos++] = curr_instance.dio_intmin;
  buffer[pos++] = curr_instance.dio_redundancy;
  set16(buffer, pos, curr_instance.max_rankinc);
  pos += 2;
  set16(buffer, pos, curr_instance.min_hoprankinc);
  pos += 2;
  /* OCP is in the DAG_CONF option */
  set16(buffer, pos, curr_instance.of->ocp);
  pos += 2;
  buffer[pos++] = 0; /* reserved */
  buffer[pos++] = curr_instance.default_lifetime;
  set16(buffer, pos, curr_instance.lifetime_unit);
  pos += 2;

  /* Check if we have a prefix to send also. */
  if(curr_instance.dag.prefix_info.length > 0) {
    buffer[pos++] = RPL_OPTION_PREFIX_INFO;
    buffer[pos++] = 30; /* always 30 bytes + 2 long */
    buffer[pos++] = curr_instance.dag.prefix_info.length;
    buffer[pos++] = curr_instance.dag.prefix_info.flags;
    set32(buffer, pos, curr_instance.dag.prefix_info.lifetime);
    pos += 4;
    set32(buffer, pos, curr_instance.dag.prefix_info.lifetime);
    pos += 4;
    memset(&buffer[pos], 0, 4);
    pos += 4;
    memcpy(&buffer[pos], &curr_instance.dag.prefix_info.prefix, 16);
    pos += 16;
  }

  if(!rpl_get_leaf_only()) {
    addr = addr != NULL ? addr : &rpl_multicast_addr;
  }

  LOG_INFO("sending a %s-DIO with rank %u to ",
         uc_addr != NULL ? "unicast" : "multicast",
         (unsigned)curr_instance.dag.rank);
  LOG_INFO_6ADDR(addr);
  LOG_INFO_("\n");





  /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
  /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
  /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
  // SNAP: rpl_icmp6_dio_output_INFO
  /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
  /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
  /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
  #if GALIOT_FUNCTIONALITY

    /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
    #if GALIOT_SNAP_RPL_ICMP6_DIO_OUTPUT
    /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/

     /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    galiot_snap_flag_rpl_icmp6_dio_output_INFO = 1;
    galiot_snap_count_rpl_icmp6_dio_output_INFO++;

     if (galiot_snap_count_rpl_icmp6_dio_output_INFO == 604)  
    {
      galiot_snap_flag_countOverflow_rpl_icmp6_dio_output_INFO = 1;
      galiot_snap_count_rpl_icmp6_dio_output_INFO = 1;
    }
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/

     /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    int galiot_snap_index = (galiot_snap_count_rpl_icmp6_dio_output_INFO - 1) % GALIOT_SNAPSHOT_COUNT;

    galiot_snap_rpl_icmp6_dio_output_INFO.system_time[galiot_snap_index] = clock_seconds();
    strcpy(galiot_snap_rpl_icmp6_dio_output_INFO.DIO_type[galiot_snap_index], uc_addr != NULL ? "unicast" : "multicast");
    galiot_snap_rpl_icmp6_dio_output_INFO.DIO_rank[galiot_snap_index] = (unsigned)curr_instance.dag.rank;
    uiplib_ipaddr_snprint(galiot_snap_rpl_icmp6_dio_output_INFO.to_6ADDR[galiot_snap_index], sizeof(galiot_snap_rpl_icmp6_dio_output_INFO.to_6ADDR[galiot_snap_index]), addr);
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/

     /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
    #endif /* GALIOT_SNAP_RPL_ICMP6_DIO_OUTPUT */
    /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/

   #endif /* GALIOT_FUNCTIONALITY */
  /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
  /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
  /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/





  uip_icmp6_send(addr, ICMP6_RPL, RPL_CODE_DIO, pos);
}
/*---------------------------------------------------------------------------*/
static void
dao_input(void)
{
  struct rpl_dao dao;
  uint8_t subopt_type;
  unsigned char *buffer;
  uint8_t buffer_length;
  int pos;
  int len;
  int i;
  uip_ipaddr_t from;

  memset(&dao, 0, sizeof(dao));

  dao.instance_id = UIP_ICMP_PAYLOAD[0];
  if(!curr_instance.used || curr_instance.instance_id != dao.instance_id) {
    LOG_ERR("dao_input: unknown RPL instance %u, discard\n", dao.instance_id);





    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    // SNAP: rpl_icmp6_dao_input_ERR_unknown
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    #if GALIOT_FUNCTIONALITY

       /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #if GALIOT_SNAP_RPL_ICMP6_DAO_INPUT
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/

       /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      galiot_snap_flag_rpl_icmp6_dao_input_ERR_unknown = 1;
      galiot_snap_count_rpl_icmp6_dao_input_ERR_unknown++;

       if (galiot_snap_count_rpl_icmp6_dao_input_ERR_unknown == 604)  
      {
        galiot_snap_flag_countOverflow_rpl_icmp6_dao_input_ERR_unknown = 1;
        galiot_snap_count_rpl_icmp6_dao_input_ERR_unknown = 1;
      }
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/

       /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      int galiot_snap_index = (galiot_snap_count_rpl_icmp6_dao_input_ERR_unknown - 1) % GALIOT_SNAPSHOT_COUNT;

      galiot_snap_rpl_icmp6_dao_input_ERR_unknown.system_time[galiot_snap_index] = clock_seconds();
      galiot_snap_rpl_icmp6_dao_input_ERR_unknown.instance_id[galiot_snap_index] = dao.instance_id;
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/

       /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
      #endif /* GALIOT_SNAP_RPL_ICMP6_DAO_INPUT */
      /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/

     #endif /* GALIOT_FUNCTIONALITY */
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/




   goto discard;
  }

  uip_ipaddr_copy(&from, &UIP_IP_BUF->srcipaddr);
  memset(&dao.parent_addr, 0, 16);

  buffer = UIP_ICMP_PAYLOAD;
  buffer_length = uip_len - uip_l3_icmp_hdr_len;

  pos = 0;
  pos++; /* instance ID */
  dao.lifetime = curr_instance.default_lifetime;
  dao.flags = buffer[pos++];
  pos++; /* reserved */
  dao.sequence = buffer[pos++];

  /* Is the DAG ID present? */
  if(dao.flags & RPL_DAO_D_FLAG) {
    if(memcmp(&curr_instance.dag.dag_id, &buffer[pos], sizeof(curr_instance.dag.dag_id))) {
      LOG_ERR("dao_input: different DAG ID ");
      LOG_ERR_6ADDR((uip_ipaddr_t *)&buffer[pos]);
      LOG_ERR_(", discard\n");




      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      // SNAP: rpl_icmp6_dao_input_ERR_different
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      #if GALIOT_FUNCTIONALITY

         /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
        #if GALIOT_SNAP_RPL_ICMP6_DAO_INPUT
        /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/

         /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
        galiot_snap_flag_rpl_icmp6_dao_input_ERR_different = 1;
        galiot_snap_count_rpl_icmp6_dao_input_ERR_different++;

        if (galiot_snap_count_rpl_icmp6_dao_input_ERR_different == 604)  
        {
          galiot_snap_flag_countOverflow_rpl_icmp6_dao_input_ERR_different = 1;
          galiot_snap_count_rpl_icmp6_dao_input_ERR_different = 1;
        }
        /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/

         /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
        int galiot_snap_index = (galiot_snap_count_rpl_icmp6_dao_input_ERR_different - 1) % GALIOT_SNAPSHOT_COUNT;

        galiot_snap_rpl_icmp6_dao_input_ERR_different.system_time[galiot_snap_index] = clock_seconds();
        uiplib_ipaddr_snprint(galiot_snap_rpl_icmp6_dao_input_ERR_different.DAG_id_6ADDR[galiot_snap_index], sizeof(galiot_snap_rpl_icmp6_dao_input_ERR_different.DAG_id_6ADDR[galiot_snap_index]), (uip_ipaddr_t *)&buffer[pos]);
        /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/

         /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
        #endif /* GALIOT_SNAP_RPL_ICMP6_DAO_INPUT */
        /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/

       #endif /* GALIOT_FUNCTIONALITY */
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
      /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/






      goto discard;
    }
    pos += 16;
  }

  /* Check if there are any RPL options present. */
  for(i = pos; i < buffer_length; i += len) {
    subopt_type = buffer[i];
    if(subopt_type == RPL_OPTION_PAD1) {
      len = 1;
    } else {
      /* The option consists of a two-byte header and a payload. */
      len = 2 + buffer[i + 1];
    }

    switch(subopt_type) {
      case RPL_OPTION_TARGET:
        /* Handle the target option. */
        dao.prefixlen = buffer[i + 3];
        memset(&dao.prefix, 0, sizeof(dao.prefix));
        memcpy(&dao.prefix, buffer + i + 4, (dao.prefixlen + 7) / CHAR_BIT);
        break;
      case RPL_OPTION_TRANSIT:
        /* The path sequence and control are ignored. */
        /*      pathcontrol = buffer[i + 3];
                pathsequence = buffer[i + 4];*/
        dao.lifetime = buffer[i + 5];
        if(len >= 20) {
          memcpy(&dao.parent_addr, buffer + i + 6, 16);
        }
        break;
    }
  }

  /* Destination Advertisement Object */
  LOG_INFO("received a %sDAO from ", dao.lifetime == 0 ? "No-path " : "");
  LOG_INFO_6ADDR(&UIP_IP_BUF->srcipaddr);
  LOG_INFO_(", seqno %u, lifetime %u, prefix ", dao.sequence, dao.lifetime);
  LOG_INFO_6ADDR(&dao.prefix);
  LOG_INFO_(", prefix length %u, parent ", dao.prefixlen);
  LOG_INFO_6ADDR(&dao.parent_addr);
  LOG_INFO_(" \n");





  /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
  /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
  /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
  // SNAP: rpl_icmp6_dao_input_INFO
  /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
  /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
  /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
  #if GALIOT_FUNCTIONALITY

    /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
    #if GALIOT_SNAP_RPL_ICMP6_DAO_INPUT
    /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/

    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    galiot_snap_flag_rpl_icmp6_dao_input_INFO = 1;
    galiot_snap_count_rpl_icmp6_dao_input_INFO++;

    if (galiot_snap_count_rpl_icmp6_dao_input_INFO == 604)  
    {
      galiot_snap_flag_countOverflow_rpl_icmp6_dao_input_INFO = 1;
      galiot_snap_count_rpl_icmp6_dao_input_INFO = 1;
    }
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/

    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
    int galiot_snap_index = (galiot_snap_count_rpl_icmp6_dao_input_INFO - 1) % GALIOT_SNAPSHOT_COUNT;

    galiot_snap_rpl_icmp6_dao_input_INFO.system_time[galiot_snap_index] = clock_seconds();
    strcpy(galiot_snap_rpl_icmp6_dao_input_INFO.DAO_type[galiot_snap_index], dao.lifetime == 0 ? "No-path " : "");
    uiplib_ipaddr_snprint(galiot_snap_rpl_icmp6_dao_input_INFO.from_6ADDR[galiot_snap_index], sizeof(galiot_snap_rpl_icmp6_dao_input_INFO.from_6ADDR[galiot_snap_index]), &UIP_IP_BUF->srcipaddr);
    galiot_snap_rpl_icmp6_dao_input_INFO.seqno[galiot_snap_index] = dao.sequence;
    galiot_snap_rpl_icmp6_dao_input_INFO.lifetime[galiot_snap_index] = dao.lifetime;
    uiplib_ipaddr_snprint(galiot_snap_rpl_icmp6_dao_input_INFO.prefix_6ADDR[galiot_snap_index], sizeof(galiot_snap_rpl_icmp6_dao_input_INFO.prefix_6ADDR[galiot_snap_index]), &dao.prefix);
    galiot_snap_rpl_icmp6_dao_input_INFO.length[galiot_snap_index] = dao.prefixlen;
    uiplib_ipaddr_snprint(galiot_snap_rpl_icmp6_dao_input_INFO.parent_6ADDR[galiot_snap_index], sizeof(galiot_snap_rpl_icmp6_dao_input_INFO.parent_6ADDR[galiot_snap_index]), &dao.parent_addr);
    /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/

    /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/
    #endif /* GALIOT_SNAP_RPL_ICMP6_DAO_INPUT */
    /*|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>|<>*/

  #endif /* GALIOT_FUNCTIONALITY */
  /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
  /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/
  /*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*//*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?--?-|-?-|-?-|-?-*/






  rpl_process_dao(&from, &dao);

  discard:
    uipbuf_clear();
}
/*---------------------------------------------------------------------------*/
void
rpl_icmp6_dao_output(uint8_t lifetime)
{
  unsigned char *buffer;
  uint8_t prefixlen;
  int pos;
  const uip_ipaddr_t *prefix = rpl_get_global_address();
  uip_ipaddr_t *parent_ipaddr = rpl_neighbor_get_ipaddr(curr_instance.dag.preferred_parent);

  /* Make sure we're up-to-date before sending data out */
  rpl_dag_update_state();

  if(!curr_instance.used) {
    LOG_WARN("rpl_icmp6_dao_output: not in an instance, skip sending DAO\n");
    return;
  }

  if(curr_instance.dag.preferred_parent == NULL) {
    LOG_WARN("rpl_icmp6_dao_output: no preferred parent, skip sending DAO\n");
    return;
  }

  if(prefix == NULL || parent_ipaddr == NULL || curr_instance.mop == RPL_MOP_NO_DOWNWARD_ROUTES) {
    LOG_WARN("rpl_icmp6_dao_output: node not ready to send a DAO (prefix %p, parent addr %p, mop %u)\n",
                    prefix, parent_ipaddr, curr_instance.mop);
    return;
  }

  buffer = UIP_ICMP_PAYLOAD;
  pos = 0;

  buffer[pos++] = curr_instance.instance_id;
  buffer[pos] = 0;
#if RPL_WITH_DAO_ACK
  if(lifetime != 0) {
    buffer[pos] |= RPL_DAO_K_FLAG;
  }
#endif /* RPL_WITH_DAO_ACK */
  ++pos;
  buffer[pos++] = 0; /* reserved */
  buffer[pos++] = curr_instance.dag.dao_last_seqno;

  /* create target subopt */
  prefixlen = sizeof(*prefix) * CHAR_BIT;
  buffer[pos++] = RPL_OPTION_TARGET;
  buffer[pos++] = 2 + ((prefixlen + 7) / CHAR_BIT);
  buffer[pos++] = 0; /* reserved */
  buffer[pos++] = prefixlen;
  memcpy(buffer + pos, prefix, (prefixlen + 7) / CHAR_BIT);
  pos += ((prefixlen + 7) / CHAR_BIT);

  /* Create a transit information sub-option. */
  buffer[pos++] = RPL_OPTION_TRANSIT;
  buffer[pos++] = 20;
  buffer[pos++] = 0; /* flags - ignored */
  buffer[pos++] = 0; /* path control - ignored */
  buffer[pos++] = 0; /* path seq - ignored */
  buffer[pos++] = lifetime;

  /* Include parent global IP address */
  memcpy(buffer + pos, &curr_instance.dag.dag_id, 8); /* Prefix */
  pos += 8;
  memcpy(buffer + pos, ((const unsigned char *)parent_ipaddr) + 8, 8); /* Interface identifier */
  pos += 8;

  LOG_INFO("sending a %sDAO seqno %u, tx count %u, lifetime %u, prefix ",
         lifetime == 0 ? "No-path " : "",
         curr_instance.dag.dao_last_seqno, curr_instance.dag.dao_transmissions, lifetime);
  LOG_INFO_6ADDR(prefix);
  LOG_INFO_(" to ");
  LOG_INFO_6ADDR(&curr_instance.dag.dag_id);
  LOG_INFO_(", parent ");
  LOG_INFO_6ADDR(parent_ipaddr);
  LOG_INFO_("\n");

  /* Send DAO to root (IPv6 address is DAG ID) */
  uip_icmp6_send(&curr_instance.dag.dag_id, ICMP6_RPL, RPL_CODE_DAO, pos);
}
#if RPL_WITH_DAO_ACK
/*---------------------------------------------------------------------------*/
static void
dao_ack_input(void)
{
  uint8_t *buffer;
  uint8_t instance_id;
  uint8_t sequence;
  uint8_t status;

  buffer = UIP_ICMP_PAYLOAD;

  instance_id = buffer[0];
  sequence = buffer[2];
  status = buffer[3];

  if(!curr_instance.used || curr_instance.instance_id != instance_id) {
    LOG_ERR("dao_ack_input: unknown instance, discard\n");
    goto discard;
  }

  LOG_INFO("received a DAO-%s with seqno %d (%d %d) and status %d from ",
         status < RPL_DAO_ACK_UNABLE_TO_ACCEPT ? "ACK" : "NACK", sequence,
         curr_instance.dag.dao_last_seqno, curr_instance.dag.dao_last_seqno, status);
  LOG_INFO_6ADDR(&UIP_IP_BUF->srcipaddr);
  LOG_INFO_("\n");

  rpl_process_dao_ack(sequence, status);

  discard:
    uipbuf_clear();
}
/*---------------------------------------------------------------------------*/
void
rpl_icmp6_dao_ack_output(uip_ipaddr_t *dest, uint8_t sequence, uint8_t status)
{
  unsigned char *buffer;

  /* Make sure we're up-to-date before sending data out */
  rpl_dag_update_state();

  buffer = UIP_ICMP_PAYLOAD;
  buffer[0] = curr_instance.instance_id;
  buffer[1] = 0;
  buffer[2] = sequence;
  buffer[3] = status;

  LOG_INFO("sending a DAO-%s seqno %d to ",
          status < RPL_DAO_ACK_UNABLE_TO_ACCEPT ? "ACK" : "NACK", sequence);
  LOG_INFO_6ADDR(dest);
  LOG_INFO_(" with status %d\n", status);

  uip_icmp6_send(dest, ICMP6_RPL, RPL_CODE_DAO_ACK, 4);
}
#endif /* RPL_WITH_DAO_ACK */
/*---------------------------------------------------------------------------*/
void
rpl_icmp6_init()
{
  uip_icmp6_register_input_handler(&dis_handler);
  uip_icmp6_register_input_handler(&dio_handler);
  uip_icmp6_register_input_handler(&dao_handler);
#if RPL_WITH_DAO_ACK
  uip_icmp6_register_input_handler(&dao_ack_handler);
#endif /* RPL_WITH_DAO_ACK */
}
/*---------------------------------------------------------------------------*/

/** @}*/
