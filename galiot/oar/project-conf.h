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
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

/*---------------------------------------------------------------------------*/

#ifndef PROJECT_CONF_H_
#define PROJECT_CONF_H_



#define UIP_CONF_TCP 1




/*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?*/
/*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?*/
/*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?*/

/*  Set maximum debug level on all modules. See os/sys/log-conf.h for
 *  a list of supported modules. The different log levels are defined in os/sys/log.h:
 * 
 *      LOG_LEVEL_NONE         No log
 *      LOG_LEVEL_ERR          Errors
 *      LOG_LEVEL_WARN         Warnings
 *      LOG_LEVEL_INFO         Basic info
 *      LOG_LEVEL_DBG          Detailled debug
 */

#define LOG_CONF_LEVEL_IPV6                                     LOG_LEVEL_NONE
#define LOG_CONF_LEVEL_RPL                                      LOG_LEVEL_NONE
#define LOG_CONF_LEVEL_6LOWPAN                                  LOG_LEVEL_NONE
#define LOG_CONF_LEVEL_TCPIP                                    LOG_LEVEL_NONE
#define LOG_CONF_LEVEL_MAC                                      LOG_LEVEL_NONE
#define LOG_CONF_LEVEL_FRAMER                                   LOG_LEVEL_NONE
#define LOG_CONF_LEVEL_COAP                                     LOG_LEVEL_NONE
#define LOG_CONF_LEVEL_LWM2M                                    LOG_LEVEL_NONE
#define LOG_CONF_LEVEL_6TOP                                     LOG_LEVEL_NONE

/*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?*/
/*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?*/
/*|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?-|-?*/

// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

#define ENERGEST_CONF_ON                                                    1
#define UIP_CONF_STATISTICS                                                 1

/* NBR_TABLE_CONF_MAX_NEIGHBORS specifies the maximum number of neighbors
    that each node will be able to handle. */

#define NBR_TABLE_CONF_MAX_NEIGHBORS                                        5
#define UIP_CONF_TCP                                                        1
                                                        
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

#define OAR_CONF_MOTE_COLOR                                                 "RED"               // CODE NAME FOR MOTE

//---------------------------------------------------------------------------

// enable/disable debug functionality, across the board
#define OAR_CONF_DEBUG_FUNCTIONALITY                                        0                   // (ON:1||OFF: 0)

// enable/disable buoy functionality, across the board
#define OAR_CONF_BUOY_FUNCTIONALITY                                         1                   // (ON:1||OFF: 0)

// **************************************************************************
// BUOY CONTSTANTS //////////////////////////////////////////////////////////
// **************************************************************************

// set the buffer size for staging the sending json
#define OAR_CONF_BUOY_BUFFER_SIZE                                           482                 // BYTES *sizeof(char)
                                                                                                // [* 1,33 < (OAR_CONF_BUOY_MAX_PAYLOAD_LENGTH]

// set the maximum payload length for the packets send to unconstrained
#define OAR_CONF_BUOY_MAX_PAYLOAD_LENGTH                                    640                 // BYTES *sizeof(char) 
                                                                                                // [< 643 != ECONNRESET/ETIMEDOUT]

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// DEBUG CONSTANTS //////////////////////////////////////////////////////////
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// enable/disable console print for debug purposes
#define OAR_CONF_DEBUG                                                      1                   // (ON:1||OFF: 0)

// set the frequency in seconds for printing to console 
#define OAR_CONF_DEBUG_INTERVAL                                             3                   // CONSOLE PRINT INTERVAL (SECONDS)

// enable/disable energest timings (printing energest values)
#define OAR_CONF_DEBUG_ENERGY                                               0                   // (ON:1||OFF: 0)

// enable/disable UIP statistics debugging (printing UIP values)
#define OAR_CONF_DEBUG_STATISTICS                                           0                   // (ON:1||OFF: 0)

// enable/disable shell information (printing shell values)
#define OAR_CONF_DEBUG_NETWORK                                              0                   // (ON:1||OFF: 0)

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// JSON CONSTANTS ///////////////////////////////////////////////////////////
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// enable/disable JSON creation
#define OAR_CONF_JSON                                                       1                   // (ON:1||OFF: 0)

// set the JSON type
#define OAR_CONF_JSON_TYPE                                                  0                   // 0: QUANTIZED: || 1: EXTENDED || 2: COMPACT || 3: MICRO || 4: TINY

// ~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~
// OAR_CONF_JSON_TYPE: QUANTIZED ///////////////
// ~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~

#define OAR_CONF_JSON_BUF_SIZE                                              482                 // BYTES *sizeof(char) 
                                                                                                // [== OAR_CONF_BUOY_BUFFER_SIZE -> decryption @ unconstrained backend]

// ~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~
// OAR_CONF_JSON_TYPE: EXTENDED ////////////////
// ~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~

#define OAR_CONF_JSON_EXTENDED_BUF_SIZE                                     5000                // BYTES *sizeof(char) 
                                                                                                // [== OAR_CONF_BUOY_BUFFER_SIZE -> decryption @ unconstrained backend]

// ~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~
// OAR_CONF_JSON_TYPE: COMPACT /////////////////
// ~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~

#define OAR_CONF_JSON_COMPACT_BUF_SIZE                                      2200                // BYTES *sizeof(char) 
                                                                                                // [== OAR_CONF_BUOY_BUFFER_SIZE -> decryption @ unconstrained backend]

// ~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~
// OAR_CONF_JSON_TYPE: MICRO ///////////////////
// ~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~

#define OAR_CONF_JSON_MICRO_BUF_SIZE                                        1800                // BYTES *sizeof(char) [== OAR_CONF_BUOY_BUFFER_SIZE -> decryption @ unconstrained backend]

#define OAR_CONF_JSON_MICRO_ID                                              1                   // (ON:1||OFF: 0)
#define OAR_CONF_JSON_MICRO_NRG                                             1                   // (ON:1||OFF: 0)
#define OAR_CONF_JSON_MICRO_STATS                                           1                   // (ON:1||OFF: 0)
#define OAR_CONF_JSON_MICRO_NET                                             1                   // (ON:1||OFF: 0)
#define OAR_CONF_JSON_MICRO_RPL                                             1                   // (ON:1||OFF: 0)

// ~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~
// OAR_CONF_JSON_TYPE: TINY ////////////////////
// ~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~|~

#define OAR_CONF_JSON_TINY_BUF_SIZE                                         1800                // BYTES *sizeof(char)

#define OAR_CONF_JSON_TINY_ID                                               1                   // (ON:1||OFF: 0)
#define OAR_CONF_JSON_TINY_NRG                                              1                   // (ON:1||OFF: 0)
#define OAR_CONF_JSON_TINY_STATS                                            1                   // (ON:1||OFF: 0)
#define OAR_CONF_JSON_TINY_NET                                              1                   // (ON:1||OFF: 0)
#define OAR_CONF_JSON_TINY_RPL                                              1                   // (ON:1||OFF: 0) 
                                                                                                // [== 0 >< BUOY]

// #define OAR_CONF_JSON_TINY_DISCRITIZATION                                0                   // (ON/OF

// #define OAR_CONF_JSON_TINY_DISCRITIZATION_COUNT                          0                   // TOTAL DISCRETE PAR

// #define OAR_CONF_JSON_TINY_DISCRETE_NRG                                  0                   // (ON:1||OFF: 0)
// #define OAR_CONF_JSON_TINY_DISCRETE_STATS                                0                   // (ON:1||OFF: 0)
// #define OAR_CONF_JSON_TINY_DISCRETE_NET                                  0                   // (ON:1||OFF: 0)
// #define OAR_CONF_JSON_TINY_DISCRETE_RPL                                  0                   // (ON:1||OFF: 0)

// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
// ENCRYPTION / DECRYPTION CONSTANTS ////////////////////////////////////////
// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

// enable/disable JSON encryption
#define OAR_CONF_CRYPT                                                      1                   // (ON:1||OFF: 0) 

// set the encryption string size
#define OAR_CONF_CRYPT_BUFFER_SIZE                                          482                // BYTES *sizeof(char) [== OAR_CONF_BUOY_BUFFER_SIZE -> decryption @ unconstrained backend]

// </></></></></></></></></></></></></></></></></></></></></></></></></></></></></></></></></></></></></></></></></></>
// key[] = {'!', '@', '#', '$', '%', '^', '&', '*'} /////////////////////////////////////////// // hardcoded ./galiot/oar-crypt.c
// </></></></></></></></></></></></></></></></></></></></></></></></></></></></></></></></></></></></></></></></></></>

// enable/disable decryption
#define OAR_CONF_CRYPT_DECRYPT                                              1                   // (ON:1||OFF: 0)

// CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
// BASE64 ENCODING //////////////////////////////////////////////////////////
// CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC

// enable/disable base64 encoding
#define OAR_CONF_BASE64_ENCODING                                            1                   // (ON:1||OFF: 0)

// enable/disable base64 encoding
#define OAR_CONF_BASE64_ENCODING_BUF_SIZE                                   640                 // (ON:1||OFF: 0) [> OAR_CONF_BUOY_BUFFER_SIZE * 1.33]

//---------------------------------------------------------------------------

// enable/disable on-board device functionality
// leds, buttons, sensors, etc.
#define OAR_CONF_DEV                                                        1                   // (ON:1||OFF: 0)






// /* UIP_CONF_BUFFER_SIZE specifies how much memory should be reserved
//    for the uIP packet buffer. This sets an upper bound on the largest
//    IP packet that can be received by the system. */
// #ifndef UIP_CONF_BUFFER_SIZE
// #define UIP_CONF_BUFFER_SIZE 1280
// #endif /* UIP_CONF_BUFFER_SIZE */

// /**
//  * The TCP maximum segment size.
//  *
//  * This is should not be to set to more than
//  * UIP_BUFSIZE - UIP_LLH_LEN - UIP_TCPIP_HLEN.
//  */
// #ifdef UIP_CONF_TCP_MSS
// #if UIP_CONF_TCP_MSS > (UIP_BUFSIZE - UIP_LLH_LEN - UIP_TCPIP_HLEN)
// #error UIP_CONF_TCP_MSS is too large for the current UIP_BUFSIZE
// #endif /* UIP_CONF_TCP_MSS > (UIP_BUFSIZE - UIP_LLH_LEN - UIP_TCPIP_HLEN) */
// #define UIP_TCP_MSS     (UIP_CONF_TCP_MSS)
// #else /* UIP_CONF_TCP_MSS */
// #define UIP_TCP_MSS     (UIP_BUFSIZE - UIP_LLH_LEN - UIP_TCPIP_HLEN)
// #endif /* UIP_CONF_TCP_MSS */








#endif      /*  PROJECT_CONF_H_ */
