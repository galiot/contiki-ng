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










// (-)-ENERGEST-(-)-ENERGEST-(-)-ENERGEST-(-)-ENERGEST-(-)-ENERGEST-(-)-ENERGEST-(-)-ENERGEST-(-)
// (-)-ENERGEST-(-)-ENERGEST-(-)-ENERGEST-(-)-ENERGEST-(-)-ENERGEST-(-)-ENERGEST-(-)-ENERGEST-(-)
// (-)-ENERGEST-(-)-ENERGEST-(-)-ENERGEST-(-)-ENERGEST-(-)-ENERGEST-(-)-ENERGEST-(-)-ENERGEST-(-)

#define ENERGEST_CONF_ON 1

// (-)-ENERGEST-(-)-ENERGEST-(-)-ENERGEST-(-)-ENERGEST-(-)-ENERGEST-(-)-ENERGEST-(-)-ENERGEST-(-)
// (-)-ENERGEST-(-)-ENERGEST-(-)-ENERGEST-(-)-ENERGEST-(-)-ENERGEST-(-)-ENERGEST-(-)-ENERGEST-(-)
// (-)-ENERGEST-(-)-ENERGEST-(-)-ENERGEST-(-)-ENERGEST-(-)-ENERGEST-(-)-ENERGEST-(-)-ENERGEST-(-)








// {}CONF{}CONF{}CONF{}CONF{}CONF{}CONF{}CONF{}CONF{}CONF{}CONF{}CONF{}CONF{}CONF{}CONF{}CONF{}CONF{}CONF{}
// {}CONF{}CONF{}CONF{}CONF{}CONF{}CONF{}CONF{}CONF{}CONF{}CONF{}CONF{}CONF{}CONF{}CONF{}CONF{}CONF{}CONF{}
// {}CONF{}CONF{}CONF{}CONF{}CONF{}CONF{}CONF{}CONF{}CONF{}CONF{}CONF{}CONF{}CONF{}CONF{}CONF{}CONF{}CONF{}

// enable/disable oar functionality, across the board
#define OAR_CONF_FUNCTIONALITY                                              1

// enable/disable console print for debug purposes
#define OAR_CONF_DEBUG                                                      1

// enable/disable JSON creation
#define OAR_CONF_JSON                                                       1

/*---------------------------------------------------------------------------*/

#if OAR_CONF_FUNCTIONALITY
    #define OAR_FUNCTIONALITY                           OAR_CONF_FUNCTIONALITY
#else   /*  OAR_CONF_FUNCTIONALITY  */
    #define OAR_FUNCTIONALITY                                               0 
#endif  /*  OAR_CONF_FUNCTIONALITY  */               

#if OAR_CONF_DEBUG
    #define OAR_DEBUG                                           OAR_CONF_DEBUG
#else   /*  OAR_CONF_DEBUG  */
    #define OAR_DEBUG                                                       0 
#endif  /*  OAR_CONF_DEBUG  */               

#if OAR_CONF_JSON
    #define OAR_JSON                                            OAR_CONF_JSON
#else   /*  OAR_CONF_DEBUG  */
    #define OAR_JSON                                                        0 
#endif  /*  OAR_CONF_DEBUG  */

// {}CONF{}CONF{}CONF{}CONF{}CONF{}CONF{}CONF{}CONF{}CONF{}CONF{}CONF{}CONF{}CONF{}CONF{}CONF{}CONF{}CONF{}
// {}CONF{}CONF{}CONF{}CONF{}CONF{}CONF{}CONF{}CONF{}CONF{}CONF{}CONF{}CONF{}CONF{}CONF{}CONF{}CONF{}CONF{}
// {}CONF{}CONF{}CONF{}CONF{}CONF{}CONF{}CONF{}CONF{}CONF{}CONF{}CONF{}CONF{}CONF{}CONF{}CONF{}CONF{}CONF{}











// <>DEBUG<>DEBUG<>DEBUG<>DEBUG<>DEBUG<>DEBUG<>DEBUG<>DEBUG<>DEBUG<>DEBUG<>DEBUG<>DEBUG<>DEBUG<>DEBUG<>DEBUG<>DEBUG<>
// <>DEBUG<>DEBUG<>DEBUG<>DEBUG<>DEBUG<>DEBUG<>DEBUG<>DEBUG<>DEBUG<>DEBUG<>DEBUG<>DEBUG<>DEBUG<>DEBUG<>DEBUG<>DEBUG<>
// <>DEBUG<>DEBUG<>DEBUG<>DEBUG<>DEBUG<>DEBUG<>DEBUG<>DEBUG<>DEBUG<>DEBUG<>DEBUG<>DEBUG<>DEBUG<>DEBUG<>DEBUG<>DEBUG<>

#if (OAR_DEBUG)

    /*---------------------------------------------------------------------------*/
    /*---------------------------------------------------------------------------*/
    /*---------------------------------------------------------------------------*/
    
    // set the frequency in seconds for printing to console 
    #define OAR_CONF_DEBUG_INTERVAL                                              3      // (SECONDS)

    // enable/disable the energest debugging (printing energest values)
    #define OAR_CONF_DEBUG_ENERGEST                                              1 



    /*---------------------------------------------------------------------------*/

    #if OAR_CONF_DEBUG_INTERVAL
        #define OAR_DEBUG_INTERVAL                          OAR_CONF_DEBUG_INTERVAL
    #else   /*  OAR_CONF_DEBUG_ENERGEST  */
        #define OAR_DEBUG_INTERVAL                                              10 
    #endif  /*  OAR_CONF_DEBUG_ENERGEST  */

    #if OAR_CONF_DEBUG_ENERGEST
        #define OAR_DEBUG_ENERGEST                          OAR_CONF_DEBUG_ENERGEST
    #else   /*  OAR_CONF_DEBUG_ENERGEST  */
        #define OAR_ENERGEST                                                     0 
    #endif  /*  OAR_CONF_DEBUG_ENERGEST  */

    /*---------------------------------------------------------------------------*/
    /*---------------------------------------------------------------------------*/
    /*---------------------------------------------------------------------------*/

#endif  /*  OAR_DEBUG   */

// <>DEBUG<>DEBUG<>DEBUG<>DEBUG<>DEBUG<>DEBUG<>DEBUG<>DEBUG<>DEBUG<>DEBUG<>DEBUG<>DEBUG<>DEBUG<>DEBUG<>DEBUG<>DEBUG<>
// <>DEBUG<>DEBUG<>DEBUG<>DEBUG<>DEBUG<>DEBUG<>DEBUG<>DEBUG<>DEBUG<>DEBUG<>DEBUG<>DEBUG<>DEBUG<>DEBUG<>DEBUG<>DEBUG<>
// <>DEBUG<>DEBUG<>DEBUG<>DEBUG<>DEBUG<>DEBUG<>DEBUG<>DEBUG<>DEBUG<>DEBUG<>DEBUG<>DEBUG<>DEBUG<>DEBUG<>DEBUG<>DEBUG<>






















#endif      /*  PROJECT_CONF_H_ */
