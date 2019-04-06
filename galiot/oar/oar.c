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

// #include "os/lib/heapmem.h"
#include "httpd-simple.h"

// <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><
// <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><
// <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><
// <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><

#include "project-conf.h"           // for vscode intellisense (make recipe includes it either way)
#include "oar-debug.h"

#if (OAR_CONF_JSON_TYPE == 0)
    #include "oar-json-quantized.h"
#endif

#if (OAR_CONF_JSON_TYPE == 1)
    #include "oar-json-extended.h"
#endif

#if (OAR_CONF_JSON_TYPE == 2)
    #include "oar-json-compact.h"
#endif

#if (OAR_CONF_JSON_TYPE == 3)
    #include "oar-json-micro.h"
#endif

#if (OAR_CONF_JSON_TYPE == 4)
    #include "oar-json-tiny.h"
#endif

#include "oar-crypt.h"

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
PROCESS(webserver_process, "webserver process");
PROCESS(oar_moor_process, "oar moor process");

#if (OAR_CONF_DEBUG_FUNCTIONALITY)

    #if (OAR_CONF_JSON == 1) 
        #if (OAR_CONF_JSON_TYPE == 0)

            int quantum_id = 0;
        
        #endif    
    #endif

    AUTOSTART_PROCESSES(&oar_debug_process, &oar_dev_process);

#endif // (OAR_CONF_DEBUG_FUNCTIONALITY)

#if (OAR_CONF_MOOR_FUNCTIONALITY)

    #if (OAR_CONF_JSON == 1) 
        #if (OAR_CONF_JSON_TYPE == 0)

            int quantum_id = 0;
        
        #endif    
    #endif

    AUTOSTART_PROCESSES(&oar_moor_process);

#endif // (OAR_CONF_MOOR_FUNCTIONALITY)

// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::


















// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// os/net/ipv6/psock.h MACROS ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// The structure that holds the state of a buffer.
// The structure has no user-visible elements, 
// but is used through the functions provided by the library.
//
// struct psock_buf 
// {
//     uint8_t *ptr;
//     unsigned short left;
// };

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// The representation of a protosocket.
// The protosocket structrure is an opaque structure with no user-visible elements.
//
// struct psock 
// {
//     struct pt pt, psockpt;  /* Protothreads - one that's using the psock functions, and one that runs inside the psock functions.    */
//     const uint8_t *sendptr; /* Pointer to the next data to be sent.                                                                  */
//     uint8_t *readptr;       /* Pointer to the next data to be read.                                                                  */
//     uint8_t *bufptr;        /* Pointer to the buffer used for buffering incoming data.                                               */
//     uint16_t sendlen;       /* The number of bytes left to be sent.                                                                  */
//     uint16_t readlen;       /* The number of bytes left to be read.                                                                  */
//     struct psock_buf buf;   /* The structure holding the state of the input buffer.                                                  */
//     unsigned int bufsize;   /* The size of the input buffer.                                                                         */
//     unsigned char state;    /* The state of the protosocket.                                                                         */
// };

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// Start the protosocket protothread in a function.
//
// This macro starts the protothread associated with the protosocket 
// and must come before other protosocket calls in the function it is used.
//
//
// #define PSOCK_BEGIN(psock) PT_BEGIN(&((psock)->pt)) PT_THREAD(psock_send(struct psock *psock, const uint8_t *buf, unsigned int len)); // psock (struct psock *): A pointer to the protosocket to be started.

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// Send data.
//
// This macro sends data over a protosocket. 
// The protosocket protothread blocks UNTIL (all data has been sent) 
// AND (is known to have been received by the remote end of the TCP connection).
//
// #define PSOCK_SEND(psock, data, datalen) PT_WAIT_THREAD(&((psock)->pt), psock_send(psock, data, datalen)) // datalen (unsigned int): The length of the data that is to be sent.

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// Declare the end of a protosocket's protothread.
//
// This macro is used for declaring that the protosocket's protothread ends. 
// It must always be used together with a matching PSOCK_BEGIN() macro.
// 
// #define PSOCK_END(psock) PT_END(&((psock)->pt)) // psock (struct psock *): A pointer to the protosocket.





// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ./httpd-simple.h MACROS //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// #define SEND_STRING(s, str) PSOCK_SEND(s, (uint8_t *)str, strlen(str))

// struct httpd_state 
// {
//     struct timer timer;
//     struct psock sin, sout;
//     struct pt outputpt;
//     char inputbuf[HTTPD_PATHLEN + 24];
//     char filename[HTTPD_PATHLEN];
//     httpd_simple_script_t script;
//     char state;
// };

// typedef char (*httpd_simple_script_t)        struct httpd_state (*s);
//                                          --> 
// now the string httpd_simple_script_t[]   -->  struct httpd_state s[]                            


























// #!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!
// #!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!
// #!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!
// #!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!

/*---------------------------------------------------------------------------*/
// 

//static
PT_THREAD(generate_routes(struct httpd_state *s))
{
    char buff[OAR_CONF_MOOR_BUFFER_SIZE];

    PSOCK_BEGIN(&s->sout); // Start the protosocket protothread in a function.

    // JJJJJJJJJJ
    // JJJJJJJJJJ
    // JJJJJJJJJJ
    // JJJJJJJJJJ
    // JJJJJJJJJJ
    // JJJJJJJJJJ
    // JJJJJJJJJJ
    // JJJJJJJJJJ
    // JJJJJJJJJJ
    // JJJJJJJJJJ

    // ================================================================================================================================================================
    // JSON ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // ================================================================================================================================================================
            
    #if (OAR_CONF_JSON)

        // ------------------------------------------------------------------------------------------------------------------------
        // QUANTIZED JSON /////////////////////////////////////////////////////////////////////////////////////////////////////////
        // ------------------------------------------------------------------------------------------------------------------------

        #if (OAR_CONF_JSON_TYPE == 0) // use the quantized json (./oar-json-quantized.h) [project-conf.h]
                    
            char *oar_json_quantized_buf = (char *)malloc((OAR_CONF_JSON_QUANTIZED_BUF_SIZE+1)*sizeof(char)); // allocate OAR_CONF_JSON_QUANTIZED_BUF_SIZE + 1 character size (*+1 for '\0' character) in heap memory for storing oar_json_quantized_buf > char *oar_json_quantized_buf = (char *)heapmem_alloc((OAR_CONF_JSON_QUANTIZED_BUF_SIZE+1)*sizeof(char)); (for platform specific os/lib/heapmem.h)

            if (oar_json_quantized_buf == NULL) // if heap memory couldn't be allocated for oar_json_quantized_buf...
            {
                printf("OUT OF HEAP MEMORY > CANNOT ALLOCATE (%u + 1) CHARACTERS FOR QUANTIZED JSON\n", OAR_CONF_JSON_QUANTIZED_BUF_SIZE);

                // $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
                printf("STAGING ERROR JSON\n"); printf("\n"); //////////////////////////////////////////////////////////
                // $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
                strcpy(buff, "{ \" error \" : \" OUT OF HEAP MEMORY FOR QUANTIZED JSON ALLOCASTION \" }");
                // $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
                
                free(oar_json_quantized_buf);   // release the memory allocated for encrypted_oar_json > heapmem_free(encrypted_oar_json); (for platform specific os/lib/heapmem.h)
            }
            else
            {
                oar_json_quantized_construct(oar_json_quantized_buf, quantum_id % 11); // construct oar_json_quantized_buf (function found in ./oar_json_micro.h)
                oar_json_quantized_print(oar_json_quantized_buf); // print oar_json_quantized_buf (function found in ./oar_json_micro.h)
                
                printf("\n"); printf("length of quantized json: %d\n", strlen(oar_json_quantized_buf));

                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                // ENCRYPTION / DECRYPTION ////////////////////////////////////////////////////////
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

                #if (OAR_CONF_CRYPT) // if encryption functionality is enabled... [project-conf.h]

                    char *encrypted_oar_json = (char *)malloc((OAR_CONF_CRYPT_BUFFER_SIZE+1)*sizeof(char)); // allocate OAR_CONF_CRYPT_BUFFER_SIZE + 1 character size (*+1 for '\0' character) in heap memory for storing decrypted_oar_json > char *encrypted_oar_json = (char *)heapmem_alloc((OAR_CONF_CRYPT_BUFFER_SIZE+1)*sizeof(char)); (for platform specific os/lib/heapmem.h)

                    printf("\n");
                    
                    if (encrypted_oar_json == NULL) // if heap memory couldn't be allocated for encrypted_oar_json...
                    {
                        printf("OUT OF HEAP MEMORY > CANNOT ALLOCATE (%u + 1) CHARACTERS FOR ENCRYPTION\n", OAR_CONF_CRYPT_BUFFER_SIZE);

                        // $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
                        printf("STAGING ERROR JSON\n"); printf("\n"); ////////////////////////////////////////////
                        // $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
                        strcpy(buff, "{ \" error \" : \" OUT OF HEAP MEMORY FOR ENCRYPTED JSON ALLOCASTION \" }");
                        // $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
                    
                        free(encrypted_oar_json);   // release the memory allocated for encrypted_oar_json > heapmem_free(encrypted_oar_json); (for platform specific os/lib/heapmem.h)
                    }
                    else // // if heap memory could be allocated for decrypted_oar_json...
                    {
                        oar_crypt(oar_json_quantized_buf, encrypted_oar_json); // encrypt oar_json_quantized_buf and store it in encrypted_oar_json (function found in oar-crypt.h)
                        
                        printf("%s\n", encrypted_oar_json); printf("\n");
                        printf("length of encrypted: %d\n", strlen(encrypted_oar_json)); printf("\n");

                        // $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
                        printf("STAGING ENCRYPTED QUANTIZED JSON, QUANTUM: %d\n", quantum_id);  printf("\n");
                        // $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
                        strcpy(buff, encrypted_oar_json); ///////////////////////////////////////////////////
                        // $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

                        // ::::::::::::::::::::::::::::::::::::::::::::::::::
                        // DECRYPTION ///////////////////////////////////////
                        // ::::::::::::::::::::::::::::::::::::::::::::::::::
                        
                        #if (OAR_CONF_CRYPT_DECRYPT)

                            char *decrypted_oar_json = (char *)malloc((OAR_CONF_CRYPT_BUFFER_SIZE+1)*sizeof(char)); // allocate OAR_CONF_CRYPT_BUFFER_SIZE + 1 character size (*+1 for '\0' character) in heap memory for storing decrypted_oar_json > char *decrypted_oar_json = (char *)heapmem_alloc((OAR_CONF_CRYPT_BUFFER_SIZE+1)*sizeof(char)); (for platform specific os/lib/heapmem.h)

                            printf("\n");
                            
                            if (decrypted_oar_json == NULL) // if heap memory couldn't be allocated for decrypted_oar_json...
                            {
                                printf("OUT OF HEAP MEMORY > CANNOT ALLOCATE (%u + 1) CHARACTERS FOR DECRYPTION\n", OAR_CONF_CRYPT_BUFFER_SIZE);

                                free(encrypted_oar_json);   // release the memory allocated for encrypted_oar_json > heapmem_free(encrypted_oar_json); (for platform specific os/lib/heapmem.h)
                                free(decrypted_oar_json);   // release the memory allocated for decrypted_oar_json > heapmem_free(decrypted_oar_json); (for platform specific os/lib/heapmem.h) 
                            }
                            else // if heap memory could be allocated for decrypted_oar_json...
                            {
                                oar_crypt(encrypted_oar_json, decrypted_oar_json); // decrypt encrypted_oar_json and store it in decrypted_oar_json (function found in oar-crypt.h)

                                printf("%s\n", decrypted_oar_json); printf("\n"); 
                                printf("length of decrypted: %d\n", strlen(decrypted_oar_json));

                                free(encrypted_oar_json);   // release the memory allocated for encrypted_oar_json > heapmem_free(encrypted_oar_json); (for platform specific os/lib/heapmem.h)
                                free(decrypted_oar_json);   // release the memory allocated for decrypted_oar_json > heapmem_free(decrypted_oar_json); (for platform specific os/lib/heapmem.h)
                            }

                        #endif // (OAR_CONF_CRYPT_DECRYPT)
                    }
                    
                #else // (OAR_CONF_CRYPT)

                    // $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
                    printf("STAGING QUANTIZED JSON, QUANTUM: %d\n", quantum_id); printf("\n");
                    // $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
                    strcpy(buff, oar_json_quantized_buf); ////////////////////////////////////
                    // $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

                #endif // (OAR_CONF_CRYPT)

                free(oar_json_quantized_buf); // release the memory allocated for oar_json_quantized_buf > heapmem_free(oar_json_quantized_buf); (for platform specific os/lib/heapmem.h)
                
                quantum_id++;
                quantum_id %= 10999;
            }
                
        #endif // (OAR_CONF_JSON_TYPE == 0)

        // ------------------------------------------------------------------------------------------------------------------------
        // EXTENDED JSON /////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // ------------------------------------------------------------------------------------------------------------------------

        #if (OAR_CONF_JSON_TYPE == 1) // use the extended json (./oar-json-extended.h) [project-conf.h]

            printf("EXTENDED JSON TOO LARGE FOR SENDING - PLEASE CHOOSE OTHER TYPE IN project-conf.h\n", OAR_CONF_CRYPT_BUFFER_SIZE);
            
            // $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
            printf("STAGING ERROR JSON\n"); printf("\n"); ////////
            // $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
            strcpy(buff, "{ \" error \" : \" EXTENDED JSON \" }");
            // $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

        #endif // (OAR_CONF_JSON_TYPE == 1)

        // ------------------------------------------------------------------------------------------------------------------------
        // COMPACT JSON /////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // ------------------------------------------------------------------------------------------------------------------------

        #if (OAR_CONF_JSON_TYPE == 2) // use the compact json (./oar-json-compact.h) [project-conf.h]

            printf("COMPACT JSON TOO LARGE FOR SENDING - PLEASE CHOOSE OTHER TYPE IN project-conf.h\n", OAR_CONF_CRYPT_BUFFER_SIZE);
            
            // $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
            printf("STAGING ERROR JSON\n"); printf("\n"); ///////
            // $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
            strcpy(buff, "{ \" error \" : \" COMPACT JSON \" }");
            // $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

        #endif // (OAR_CONF_JSON_TYPE == 2)

        // ------------------------------------------------------------------------------------------------------------------------
        // MICRO JSON /////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // ------------------------------------------------------------------------------------------------------------------------

        #if (OAR_CONF_JSON_TYPE == 3) // use the compact json (./oar-json-compact.h) [project-conf.h]

            printf("MICRO JSON TOO LARGE FOR SENDING - PLEASE CHOOSE OTHER TYPE IN project-conf.h\n", OAR_CONF_CRYPT_BUFFER_SIZE);
            
            // $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
            printf("STAGING ERROR JSON\n"); printf("\n"); ///////
            // $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
            strcpy(buff, "{ \" error \" : \" MICRO JSON \" }");
            // $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

        #endif // (OAR_CONF_JSON_TYPE == 3)

        // ------------------------------------------------------------------------------------------------------------------------
        // TINY JSON /////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // ------------------------------------------------------------------------------------------------------------------------
    
        #if (OAR_CONF_JSON_TYPE == 4) // use the tiny json (./oar-json-tiny.h) [project-conf.h]
                    
            char *oar_json_tiny_buf = (char *)malloc((OAR_CONF_JSON_TINY_BUF_SIZE+1)*sizeof(char)); // allocate OAR_CONF_JSON_TINY_BUF_SIZE + 1 character size (*+1 for '\0' character) in heap memory for storing oar_json_tiny_buf > char *oar_json_tiny_buf = (char *)heapmem_alloc((OAR_CONF_JSON_TINY_BUF_SIZE+1)*sizeof(char)); (for platform specific os/lib/heapmem.h)

            if (oar_json_tiny_buf == NULL) // if heap memory couldn't be allocated for oar_json_tiny_buf...
            {
                printf("OUT OF HEAP MEMORY > CANNOT ALLOCATE (%u + 1) CHARACTERS FOR EXTENDED JSON\n", OAR_CONF_JSON_TINY_BUF_SIZE);

                // $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
                printf("STAGING ERROR JSON\n"); printf("\n"); ///////////////////////////////////////
                // $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
                strcpy(buff, "{ \" error \" : \" OUT OF HEAP MEMORY FOR TINY JSON ALLOCASTION \" }");
                // $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
                
                free(oar_json_tiny_buf);   // release the memory allocated for encrypted_oar_json > heapmem_free(encrypted_oar_json); (for platform specific os/lib/heapmem.h)
            }
            else
            {
                oar_json_tiny_construct(oar_json_tiny_buf); // construct oar_json_tiny_buf (function found in ./oar_json_micro.h)
                oar_json_tiny_print(oar_json_tiny_buf); // print oar_json_tiny_buf (function found in ./oar_json_micro.h)
                
                printf("\n"); printf("length of tiny json: %d\n", strlen(oar_json_tiny_buf));

                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                // ENCRYPTION / DECRYPTION ////////////////////////////////////////////////////////
                // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

                #if (OAR_CONF_CRYPT) // if encryption functionality is enabled... [project-conf.h]

                    char *encrypted_oar_json = (char *)malloc((OAR_CONF_CRYPT_BUFFER_SIZE+1)*sizeof(char)); // allocate OAR_CONF_CRYPT_BUFFER_SIZE + 1 character size (*+1 for '\0' character) in heap memory for storing decrypted_oar_json > char *encrypted_oar_json = (char *)heapmem_alloc((OAR_CONF_CRYPT_BUFFER_SIZE+1)*sizeof(char)); (for platform specific os/lib/heapmem.h)

                    printf("\n");
                    
                    if (encrypted_oar_json == NULL) // if heap memory couldn't be allocated for encrypted_oar_json...
                    {
                        printf("OUT OF HEAP MEMORY > CANNOT ALLOCATE (%u + 1) CHARACTERS FOR ENCRYPTION\n", OAR_CONF_CRYPT_BUFFER_SIZE);

                        // $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
                        printf("STAGING ERROR JSON\n"); printf("\n"); ////////////////////////////////////////////
                        // $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
                        strcpy(buff, "{ \" error \" : \" OUT OF HEAP MEMORY FOR ENCRYPTED JSON ALLOCASTION \" }");
                        // $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
                    
                        free(encrypted_oar_json);   // release the memory allocated for encrypted_oar_json > heapmem_free(encrypted_oar_json); (for platform specific os/lib/heapmem.h)
                    }
                    else // // if heap memory could be allocated for decrypted_oar_json...
                    {
                        oar_crypt(oar_json_tiny_buf, encrypted_oar_json); // encrypt oar_json_tiny_buf and store it in encrypted_oar_json (function found in oar-crypt.h)
                        
                        printf("%s\n", encrypted_oar_json); printf("\n");
                        printf("length of encrypted: %d\n", strlen(encrypted_oar_json)); printf("\n");

                        // $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
                        printf("STAGING ENCRYPTED QUANTIZED JSON, QUANTUM: %d\n", quantum_id);  printf("\n");
                        // $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
                        strcpy(buff, encrypted_oar_json); ///////////////////////////////////////////////////
                        // $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

                        // ::::::::::::::::::::::::::::::::::::::::::::::::::
                        // DECRYPTION ///////////////////////////////////////
                        // ::::::::::::::::::::::::::::::::::::::::::::::::::
                        
                        #if (OAR_CONF_CRYPT_DECRYPT)

                            char *decrypted_oar_json = (char *)malloc((OAR_CONF_CRYPT_BUFFER_SIZE+1)*sizeof(char)); // allocate OAR_CONF_CRYPT_BUFFER_SIZE + 1 character size (*+1 for '\0' character) in heap memory for storing decrypted_oar_json > char *decrypted_oar_json = (char *)heapmem_alloc((OAR_CONF_CRYPT_BUFFER_SIZE+1)*sizeof(char)); (for platform specific os/lib/heapmem.h)

                            printf("\n");
                            
                            if (decrypted_oar_json == NULL) // if heap memory couldn't be allocated for decrypted_oar_json...
                            {
                                printf("OUT OF HEAP MEMORY > CANNOT ALLOCATE (%u + 1) CHARACTERS FOR DECRYPTION\n", OAR_CONF_CRYPT_BUFFER_SIZE);

                                free(encrypted_oar_json);   // release the memory allocated for encrypted_oar_json > heapmem_free(encrypted_oar_json); (for platform specific os/lib/heapmem.h)
                                free(decrypted_oar_json);   // release the memory allocated for decrypted_oar_json > heapmem_free(decrypted_oar_json); (for platform specific os/lib/heapmem.h) 
                            }
                            else // if heap memory could be allocated for decrypted_oar_json...
                            {
                                oar_crypt(encrypted_oar_json, decrypted_oar_json); // decrypt encrypted_oar_json and store it in decrypted_oar_json (function found in oar-crypt.h)

                                printf("%s\n", decrypted_oar_json); printf("\n"); 
                                printf("length of decrypted: %d\n", strlen(decrypted_oar_json));

                                free(encrypted_oar_json);   // release the memory allocated for encrypted_oar_json > heapmem_free(encrypted_oar_json); (for platform specific os/lib/heapmem.h)
                                free(decrypted_oar_json);   // release the memory allocated for decrypted_oar_json > heapmem_free(decrypted_oar_json); (for platform specific os/lib/heapmem.h)
                            }

                        #endif // (OAR_CONF_CRYPT_DECRYPT)

                    }
                    
                    #else // (OAR_CONF_CRYPT)

                    // $$$$$$$$$$$$$$$$$$$$$$$$$$$$$
                    printf("STAGING TINY JSON"); printf("\n"); ///
                    // $$$$$$$$$$$$$$$$$$$$$$$$$$$$$
                    strcpy(buff, oar_json_tiny_buf);
                    // $$$$$$$$$$$$$$$$$$$$$$$$$$$$$

                #endif // (OAR_CONF_CRYPT)

                free(oar_json_tiny_buf); // release the memory allocated for oar_json_tiny_buf > heapmem_free(oar_json_tiny_buf); (for platform specific os/lib/heapmem.h)
            }
            
        #endif // (OAR_CONF_JSON_TYPE == 4)

    #else // (OAR_CONF_JSON)

        // $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
        printf("STAGING NULL JSON\n"); printf("\n"); ////
        // $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
        strcpy(buff, "\" JSON \" : null "); /////////////
        // $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

    #endif // (OAR_CONF_JSON)

    // JJJJJJJJJJ
    // JJJJJJJJJJ
    // JJJJJJJJJJ
    // JJJJJJJJJJ
    // JJJJJJJJJJ
    // JJJJJJJJJJ
    // JJJJJJJJJJ
    // JJJJJJJJJJ
    // JJJJJJJJJJ
    // JJJJJJJJJJ

    if (strlen(buff) > OAR_CONF_MOOR_MAX_PAYLOAD_LENGTH)
    {
        printf("\n"); 
        printf("ABORT SENDING JSON\n");
        printf("PAYLOAD LENGHT %d > %d\n", strlen(buff), OAR_CONF_MOOR_MAX_PAYLOAD_LENGTH);
        printf("ECONNRESET/ETIMEDOUT ERRORS POSSIBLE\n");
        SEND_STRING(&s->sout, "{ \" error \" : \" MAXIMUM POSSIBLE PAYLOAD LEGTH EXCEEDED \" }"); // PSOCK_SEND(&s->sout, (uint8_t *)buff, strlen(buff)) > Send data.
    }
    else
    {
        printf("\n"); printf("SENDING JSON\n");
        SEND_STRING(&s->sout, buff); // PSOCK_SEND(&s->sout, (uint8_t *)buff, strlen(buff)) > Send data.
    }
    
    PSOCK_END(&s->sout); // Declare the end of a protosocket's protothread.
}

/*---------------------------------------------------------------------------*/

PROCESS_THREAD(webserver_process, ev, data)
{
    PROCESS_BEGIN();

        httpd_init();

        while(1) 
        {
            PROCESS_WAIT_EVENT_UNTIL(ev == tcpip_event);
            httpd_appcall(data);
        }


    PROCESS_END();
}
/*---------------------------------------------------------------------------*/

httpd_simple_script_t httpd_simple_get_script(const char *name)
{
    return generate_routes;
}

/*---------------------------------------------------------------------------*/

PROCESS_THREAD(oar_moor_process, ev, data)
{
    PROCESS_BEGIN();

        PROCESS_NAME(webserver_process);
        process_start(&webserver_process, NULL);

        printf("MOOR PROCESS STARTED\n");

    PROCESS_END();
}

// #!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!
// #!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!
// #!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!
// #!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!

















PROCESS_THREAD(oar_debug_process, ev, data)
{   
    #if !(OAR_CONF_DEBUG_FUNCTIONALITY)

        // (doc) A process can be stopped in three ways:
        // (doc)    The process implicitly exits by allowing the PROCESS_END() statement to be reached and executed.
        // (doc)    The process explicitly exits by calling PROCESS_EXIT() in the PROCESS_THREAD body.
        // (doc)    Another process kills the process by calling process_exit().
        // (doc) After stopping a process, it can be restarted from the beginning by calling process_start().

        PROCESS_EXIT();

    #else // !(OAR_CONF_DEBUG_FUNCTIONALITY)

        static struct etimer debug_timer;                       // An event-timer variable. Note that this variable must be static in order to preserve the value across yielding.
        
        PROCESS_BEGIN();

            // char *encrypted_oar_json;
            // char *decrypted_oar_json;
            
            etimer_set(&debug_timer, CLOCK_SECOND * OAR_CONF_DEBUG_INTERVAL);        // Setup a periodic timer that expires after OAR_DEBUG_INTERVAL seconds (trigger this timer after these OAR_DEBUG_INTERVAL seconds have passed).

            while(1) 
            {
                
                // ================================================================================================================================================================
                // JSON ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                // ================================================================================================================================================================
                
                #if (OAR_CONF_JSON)

                    // ------------------------------------------------------------------------------------------------------------------------
                    // QUANTIZED JSON /////////////////////////////////////////////////////////////////////////////////////////////////////////
                    // ------------------------------------------------------------------------------------------------------------------------

                    #if (OAR_CONF_JSON_TYPE == 0) // use the tiny json (./oar-json-tiny.h) [project-conf.h]
                        
                        char *oar_json_quantized_buf = (char *)malloc((OAR_CONF_JSON_QUANTIZED_BUF_SIZE+1)*sizeof(char)); // allocate OAR_CONF_JSON_QUANTIZED_BUF_SIZE + 1 character size (*+1 for '\0' character) in heap memory for storing oar_json_quantized_buf > char *oar_json_quantized_buf = (char *)heapmem_alloc((OAR_CONF_JSON_QUANTIZED_BUF_SIZE+1)*sizeof(char)); (for platform specific os/lib/heapmem.h)

                        if (oar_json_quantized_buf == NULL) // if heap memory couldn't be allocated for oar_json_quantized_buf...
                        {
                            printf("OUT OF HEAP MEMORY > CANNOT ALLOCATE (%u + 1) CHARACTERS FOR QUANTIZED JSON\n", OAR_CONF_JSON_QUANTIZED_BUF_SIZE);
                            
                            free(oar_json_quantized_buf);   // release the memory allocated for encrypted_oar_json > heapmem_free(encrypted_oar_json); (for platform specific os/lib/heapmem.h)
                        }
                        else
                        {
                            oar_json_quantized_construct(oar_json_quantized_buf, quantum_id % 11); // construct oar_json_quantized_buf (function found in ./oar_json_micro.h)
                            oar_json_quantized_print(oar_json_quantized_buf); // print oar_json_quantized_buf (function found in ./oar_json_micro.h)
                            
                            printf("\n"); printf("length of quantized json: %d\n", strlen(oar_json_quantized_buf));

                            quantum_id++;
                            quantum_id %= 10999;

                            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                            // ENCRYPTION / DECRYPTION ////////////////////////////////////////////////////////
                            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

                            #if (OAR_CONF_CRYPT) // if encryption functionality is enabled... [project-conf.h]

                                char *encrypted_oar_json = (char *)malloc((OAR_CONF_CRYPT_BUFFER_SIZE+1)*sizeof(char)); // allocate OAR_CONF_CRYPT_BUFFER_SIZE + 1 character size (*+1 for '\0' character) in heap memory for storing decrypted_oar_json > char *encrypted_oar_json = (char *)heapmem_alloc((OAR_CONF_CRYPT_BUFFER_SIZE+1)*sizeof(char)); (for platform specific os/lib/heapmem.h)

                                printf("\n"); oar_debug_('-', 100); printf("\n");   // print a seperation line > new line and inline '-' 100 times (function found in oar-debug.h)
                                
                                if (encrypted_oar_json == NULL) // if heap memory couldn't be allocated for encrypted_oar_json...
                                {
                                    printf("OUT OF HEAP MEMORY > CANNOT ALLOCATE (%u + 1) CHARACTERS FOR ENCRYPTION\n", OAR_CONF_CRYPT_BUFFER_SIZE);
                                
                                    free(encrypted_oar_json);   // release the memory allocated for encrypted_oar_json > heapmem_free(encrypted_oar_json); (for platform specific os/lib/heapmem.h)
                                }
                                else // // if heap memory could be allocated for decrypted_oar_json...
                                {
                                    oar_crypt(oar_json_quantized_buf, encrypted_oar_json); // encrypt oar_json_quantized_buf and store it in encrypted_oar_json (function found in oar-crypt.h)
                                    
                                    printf("%s\n", encrypted_oar_json); printf("\n");
                                    printf("length of encrypted: %d\n", strlen(encrypted_oar_json)); printf("\n");

                                    // ::::::::::::::::::::::::::::::::::::::::::::::::::
                                    // DECRYPTION ///////////////////////////////////////
                                    // ::::::::::::::::::::::::::::::::::::::::::::::::::
                                    
                                    #if (OAR_CONF_CRYPT_DECRYPT)

                                        char *decrypted_oar_json = (char *)malloc((OAR_CONF_CRYPT_BUFFER_SIZE+1)*sizeof(char)); // allocate OAR_CONF_CRYPT_BUFFER_SIZE + 1 character size (*+1 for '\0' character) in heap memory for storing decrypted_oar_json > char *decrypted_oar_json = (char *)heapmem_alloc((OAR_CONF_CRYPT_BUFFER_SIZE+1)*sizeof(char)); (for platform specific os/lib/heapmem.h)

                                        printf("\n"); oar_debug_('~', 100); // print a seperation line > new line and inline '~' 100 times (function found in oar-debug.h)
                                        
                                        if (decrypted_oar_json == NULL) // if heap memory couldn't be allocated for decrypted_oar_json...
                                        {
                                            printf("OUT OF HEAP MEMORY > CANNOT ALLOCATE (%u + 1) CHARACTERS FOR DECRYPTION\n", OAR_CONF_CRYPT_BUFFER_SIZE);

                                            free(encrypted_oar_json);   // release the memory allocated for encrypted_oar_json > heapmem_free(encrypted_oar_json); (for platform specific os/lib/heapmem.h)
                                            free(decrypted_oar_json);   // release the memory allocated for decrypted_oar_json > heapmem_free(decrypted_oar_json); (for platform specific os/lib/heapmem.h) 
                                        }
                                        else // if heap memory could be allocated for decrypted_oar_json...
                                        {
                                            oar_crypt(encrypted_oar_json, decrypted_oar_json); // decrypt encrypted_oar_json and store it in decrypted_oar_json (function found in oar-crypt.h)
    
                                            printf("%s\n", decrypted_oar_json); printf("\n"); 
                                            printf("length of decrypted: %d\n", strlen(decrypted_oar_json));

                                            free(encrypted_oar_json);   // release the memory allocated for encrypted_oar_json > heapmem_free(encrypted_oar_json); (for platform specific os/lib/heapmem.h)
                                            free(decrypted_oar_json);   // release the memory allocated for decrypted_oar_json > heapmem_free(decrypted_oar_json); (for platform specific os/lib/heapmem.h)
                                        }

                                    #endif // (OAR_CONF_CRYPT_DECRYPT)

                                }
                                
                            #endif // (OAR_CONF_CRYPT)

                            free(oar_json_quantized_buf); // release the memory allocated for oar_json_quantized_buf > heapmem_free(oar_json_quantized_buf); (for platform specific os/lib/heapmem.h)
                            
                        }
                        
                    #endif // (OAR_CONF_JSON_TYPE == 0)

                    // ------------------------------------------------------------------------------------------------------------------------
                    // EXTENDED JSON /////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    // ------------------------------------------------------------------------------------------------------------------------

                    #if (OAR_CONF_JSON_TYPE == 1) // use the extended json (./oar-json-extended.h) [project-conf.h]
                        
                        char *oar_json_extended_buf = (char *)malloc((OAR_CONF_JSON_EXTENDED_BUF_SIZE+1)*sizeof(char)); // allocate OAR_CONF_JSON_EXTENDED_BUF_SIZE + 1 character size (*+1 for '\0' character) in heap memory for storing oar_json_extended_buf > char *oar_json_extended_buf = (char *)heapmem_alloc((OAR_CONF_JSON_EXTENDED_BUF_SIZE+1)*sizeof(char)); (for platform specific os/lib/heapmem.h)

                        if (oar_json_extended_buf == NULL) // if heap memory couldn't be allocated for oar_json_extended_buf...
                        {
                            printf("OUT OF HEAP MEMORY > CANNOT ALLOCATE (%u + 1) CHARACTERS FOR EXTENDED JSON\n", OAR_CONF_JSON_EXTENDED_BUF_SIZE);
                            
                            free(oar_json_extended_buf);   // release the memory allocated for encrypted_oar_json > heapmem_free(encrypted_oar_json); (for platform specific os/lib/heapmem.h)
                        }
                        else
                        {
                            oar_json_extended_construct(oar_json_extended_buf); // construct oar_json_extended_buf (function found in ./oar_json_micro.h)
                            oar_json_extended_print(oar_json_extended_buf); // print oar_json_extended_buf (function found in ./oar_json_micro.h)
                            
                            printf("\n"); printf("length of extended json: %d\n", strlen(oar_json_extended_buf));

                            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                            // ENCRYPTION / DECRYPTION ////////////////////////////////////////////////////////
                            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

                            #if (OAR_CONF_CRYPT) // if encryption functionality is enabled... [project-conf.h]

                                char *encrypted_oar_json = (char *)malloc((OAR_CONF_CRYPT_BUFFER_SIZE+1)*sizeof(char)); // allocate OAR_CONF_CRYPT_BUFFER_SIZE + 1 character size (*+1 for '\0' character) in heap memory for storing decrypted_oar_json > char *encrypted_oar_json = (char *)heapmem_alloc((OAR_CONF_CRYPT_BUFFER_SIZE+1)*sizeof(char)); (for platform specific os/lib/heapmem.h)

                                printf("\n"); oar_debug_('-', 100); printf("\n");   // print a seperation line > new line and inline '-' 100 times (function found in oar-debug.h)
                                
                                if (encrypted_oar_json == NULL) // if heap memory couldn't be allocated for encrypted_oar_json...
                                {
                                    printf("OUT OF HEAP MEMORY > CANNOT ALLOCATE (%u + 1) CHARACTERS FOR ENCRYPTION\n", OAR_CONF_CRYPT_BUFFER_SIZE);
                                
                                    free(encrypted_oar_json);   // release the memory allocated for encrypted_oar_json > heapmem_free(encrypted_oar_json); (for platform specific os/lib/heapmem.h)
                                }
                                else // // if heap memory could be allocated for decrypted_oar_json...
                                {
                                    oar_crypt(oar_json_extended_buf, encrypted_oar_json); // encrypt oar_json_extended_buf and store it in encrypted_oar_json (function found in oar-crypt.h)
                                    
                                    printf("%s\n", encrypted_oar_json); printf("\n");
                                    printf("length of encrypted: %d\n", strlen(encrypted_oar_json)); printf("\n");

                                    // ::::::::::::::::::::::::::::::::::::::::::::::::::
                                    // DECRYPTION ///////////////////////////////////////
                                    // ::::::::::::::::::::::::::::::::::::::::::::::::::
                                    
                                    #if (OAR_CONF_CRYPT_DECRYPT)

                                        char *decrypted_oar_json = (char *)malloc((OAR_CONF_CRYPT_BUFFER_SIZE+1)*sizeof(char)); // allocate OAR_CONF_CRYPT_BUFFER_SIZE + 1 character size (*+1 for '\0' character) in heap memory for storing decrypted_oar_json > char *decrypted_oar_json = (char *)heapmem_alloc((OAR_CONF_CRYPT_BUFFER_SIZE+1)*sizeof(char)); (for platform specific os/lib/heapmem.h)

                                        printf("\n"); oar_debug_('~', 100); // print a seperation line > new line and inline '~' 100 times (function found in oar-debug.h)
                                        
                                        if (decrypted_oar_json == NULL) // if heap memory couldn't be allocated for decrypted_oar_json...
                                        {
                                            printf("OUT OF HEAP MEMORY > CANNOT ALLOCATE (%u + 1) CHARACTERS FOR DECRYPTION\n", OAR_CONF_CRYPT_BUFFER_SIZE);

                                            free(encrypted_oar_json);   // release the memory allocated for encrypted_oar_json > heapmem_free(encrypted_oar_json); (for platform specific os/lib/heapmem.h)
                                            free(decrypted_oar_json);   // release the memory allocated for decrypted_oar_json > heapmem_free(decrypted_oar_json); (for platform specific os/lib/heapmem.h) 
                                        }
                                        else // if heap memory could be allocated for decrypted_oar_json...
                                        {
                                            oar_crypt(encrypted_oar_json, decrypted_oar_json); // decrypt encrypted_oar_json and store it in decrypted_oar_json (function found in oar-crypt.h)
    
                                            printf("%s\n", decrypted_oar_json); printf("\n"); 
                                            printf("length of decrypted: %d\n", strlen(decrypted_oar_json));

                                            free(encrypted_oar_json);   // release the memory allocated for encrypted_oar_json > heapmem_free(encrypted_oar_json); (for platform specific os/lib/heapmem.h)
                                            free(decrypted_oar_json);   // release the memory allocated for decrypted_oar_json > heapmem_free(decrypted_oar_json); (for platform specific os/lib/heapmem.h)
                                        }

                                    #endif // (OAR_CONF_CRYPT_DECRYPT)

                                }
                                
                            #endif // (OAR_CONF_CRYPT)

                            free(oar_json_extended_buf); // release the memory allocated for oar_json_extended_buf > heapmem_free(oar_json_extended_buf); (for platform specific os/lib/heapmem.h)
                        }
                        
                    #endif // (OAR_CONF_JSON_TYPE == 1)

                    // ------------------------------------------------------------------------------------------------------------------------
                    // COMPACT JSON /////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    // ------------------------------------------------------------------------------------------------------------------------

                    #if (OAR_CONF_JSON_TYPE == 2) // use the compact json (./oar-json-compact.h) [project-conf.h]
                        
                        char *oar_json_compact_buf = (char *)malloc((OAR_CONF_JSON_COMPACT_BUF_SIZE+1)*sizeof(char)); // allocate OAR_CONF_JSON_COMPACT_BUF_SIZE + 1 character size (*+1 for '\0' character) in heap memory for storing oar_json_compact_buf > char *oar_json_compact_buf = (char *)heapmem_alloc((OAR_CONF_JSON_COMPACT_BUF_SIZE+1)*sizeof(char)); (for platform specific os/lib/heapmem.h)

                        if (oar_json_compact_buf == NULL) // if heap memory couldn't be allocated for oar_json_compact_buf...
                        {
                            printf("OUT OF HEAP MEMORY > CANNOT ALLOCATE (%u + 1) CHARACTERS FOR COMPACT JSON\n", OAR_CONF_JSON_COMPACT_BUF_SIZE);
                            
                            free(oar_json_compact_buf);   // release the memory allocated for encrypted_oar_json > heapmem_free(encrypted_oar_json); (for platform specific os/lib/heapmem.h)
                        }
                        else
                        {
                            oar_json_compact_construct(oar_json_compact_buf); // construct oar_json_compact_buf (function found in ./oar_json_micro.h)
                            oar_json_compact_print(oar_json_compact_buf); // print oar_json_compact_buf (function found in ./oar_json_micro.h)
                            
                            printf("\n"); printf("length of compact json: %d\n", strlen(oar_json_compact_buf));

                            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                            // ENCRYPTION / DECRYPTION ////////////////////////////////////////////////////////
                            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

                            #if (OAR_CONF_CRYPT) // if encryption functionality is enabled... [project-conf.h]

                                char *encrypted_oar_json = (char *)malloc((OAR_CONF_CRYPT_BUFFER_SIZE+1)*sizeof(char)); // allocate OAR_CONF_CRYPT_BUFFER_SIZE + 1 character size (*+1 for '\0' character) in heap memory for storing decrypted_oar_json > char *encrypted_oar_json = (char *)heapmem_alloc((OAR_CONF_CRYPT_BUFFER_SIZE+1)*sizeof(char)); (for platform specific os/lib/heapmem.h)

                                printf("\n"); oar_debug_('-', 100); printf("\n");   // print a seperation line > new line and inline '-' 100 times (function found in oar-debug.h)
                                
                                if (encrypted_oar_json == NULL) // if heap memory couldn't be allocated for encrypted_oar_json...
                                {
                                    printf("OUT OF HEAP MEMORY > CANNOT ALLOCATE (%u + 1) CHARACTERS FOR ENCRYPTION\n", OAR_CONF_CRYPT_BUFFER_SIZE);
                                
                                    free(encrypted_oar_json);   // release the memory allocated for encrypted_oar_json > heapmem_free(encrypted_oar_json); (for platform specific os/lib/heapmem.h)
                                }
                                else // // if heap memory could be allocated for decrypted_oar_json...
                                {
                                    oar_crypt(oar_json_compact_buf, encrypted_oar_json); // encrypt oar_json_compact_buf and store it in encrypted_oar_json (function found in oar-crypt.h)
                                    
                                    printf("%s\n", encrypted_oar_json); printf("\n");
                                    printf("length of encrypted: %d\n", strlen(encrypted_oar_json)); printf("\n");

                                    // ::::::::::::::::::::::::::::::::::::::::::::::::::
                                    // DECRYPTION ///////////////////////////////////////
                                    // ::::::::::::::::::::::::::::::::::::::::::::::::::
                                    
                                    #if (OAR_CONF_CRYPT_DECRYPT)

                                        char *decrypted_oar_json = (char *)malloc((OAR_CONF_CRYPT_BUFFER_SIZE+1)*sizeof(char)); // allocate OAR_CONF_CRYPT_BUFFER_SIZE + 1 character size (*+1 for '\0' character) in heap memory for storing decrypted_oar_json > char *decrypted_oar_json = (char *)heapmem_alloc((OAR_CONF_CRYPT_BUFFER_SIZE+1)*sizeof(char)); (for platform specific os/lib/heapmem.h)

                                        printf("\n"); oar_debug_('~', 100); // print a seperation line > new line and inline '~' 100 times (function found in oar-debug.h)
                                        
                                        if (decrypted_oar_json == NULL) // if heap memory couldn't be allocated for decrypted_oar_json...
                                        {
                                            printf("OUT OF HEAP MEMORY > CANNOT ALLOCATE (%u + 1) CHARACTERS FOR DECRYPTION\n", OAR_CONF_CRYPT_BUFFER_SIZE);

                                            free(encrypted_oar_json);   // release the memory allocated for encrypted_oar_json > heapmem_free(encrypted_oar_json); (for platform specific os/lib/heapmem.h)
                                            free(decrypted_oar_json);   // release the memory allocated for decrypted_oar_json > heapmem_free(decrypted_oar_json); (for platform specific os/lib/heapmem.h) 
                                        }
                                        else // if heap memory could be allocated for decrypted_oar_json...
                                        {
                                            oar_crypt(encrypted_oar_json, decrypted_oar_json); // decrypt encrypted_oar_json and store it in decrypted_oar_json (function found in oar-crypt.h)
    
                                            printf("%s\n", decrypted_oar_json); printf("\n"); 
                                            printf("length of decrypted: %d\n", strlen(decrypted_oar_json));

                                            free(encrypted_oar_json);   // release the memory allocated for encrypted_oar_json > heapmem_free(encrypted_oar_json); (for platform specific os/lib/heapmem.h)
                                            free(decrypted_oar_json);   // release the memory allocated for decrypted_oar_json > heapmem_free(decrypted_oar_json); (for platform specific os/lib/heapmem.h)
                                        }

                                    #endif // (OAR_CONF_CRYPT_DECRYPT)

                                }
                                
                            #endif // (OAR_CONF_CRYPT)

                            free(oar_json_compact_buf); // release the memory allocated for oar_json_compact_buf > heapmem_free(oar_json_compact_buf); (for platform specific os/lib/heapmem.h)
                        }
                        
                    #endif // (OAR_CONF_JSON_TYPE == 2)

                    // ------------------------------------------------------------------------------------------------------------------------
                    // MICRO JSON /////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    // ------------------------------------------------------------------------------------------------------------------------

                    #if (OAR_CONF_JSON_TYPE == 3) // use the tiny json (./oar-json-tiny.h) [project-conf.h]
                        
                        char *oar_json_micro_buf = (char *)malloc((OAR_CONF_JSON_MICRO_BUF_SIZE+1)*sizeof(char)); // allocate OAR_CONF_JSON_MICRO_BUF_SIZE + 1 character size (*+1 for '\0' character) in heap memory for storing oar_json_micro_buf > char *oar_json_micro_buf = (char *)heapmem_alloc((OAR_CONF_JSON_MICRO_BUF_SIZE+1)*sizeof(char)); (for platform specific os/lib/heapmem.h)

                        if (oar_json_micro_buf == NULL) // if heap memory couldn't be allocated for oar_json_micro_buf...
                        {
                            printf("OUT OF HEAP MEMORY > CANNOT ALLOCATE (%u + 1) CHARACTERS FOR MICRO JSON\n", OAR_CONF_JSON_MICRO_BUF_SIZE);
                            
                            free(oar_json_micro_buf);   // release the memory allocated for encrypted_oar_json > heapmem_free(encrypted_oar_json); (for platform specific os/lib/heapmem.h)
                        }
                        else
                        {
                            oar_json_micro_construct(oar_json_micro_buf); // construct oar_json_micro_buf (function found in ./oar_json_micro.h)
                            oar_json_micro_print(oar_json_micro_buf); // print oar_json_micro_buf (function found in ./oar_json_micro.h)
                            
                            printf("\n"); printf("length of tiny json: %d\n", strlen(oar_json_micro_buf));

                            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                            // ENCRYPTION / DECRYPTION ////////////////////////////////////////////////////////
                            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

                            #if (OAR_CONF_CRYPT) // if encryption functionality is enabled... [project-conf.h]

                                char *encrypted_oar_json = (char *)malloc((OAR_CONF_CRYPT_BUFFER_SIZE+1)*sizeof(char)); // allocate OAR_CONF_CRYPT_BUFFER_SIZE + 1 character size (*+1 for '\0' character) in heap memory for storing decrypted_oar_json > char *encrypted_oar_json = (char *)heapmem_alloc((OAR_CONF_CRYPT_BUFFER_SIZE+1)*sizeof(char)); (for platform specific os/lib/heapmem.h)

                                printf("\n"); oar_debug_('-', 100); printf("\n");   // print a seperation line > new line and inline '-' 100 times (function found in oar-debug.h)
                                
                                if (encrypted_oar_json == NULL) // if heap memory couldn't be allocated for encrypted_oar_json...
                                {
                                    printf("OUT OF HEAP MEMORY > CANNOT ALLOCATE (%u + 1) CHARACTERS FOR ENCRYPTION\n", OAR_CONF_CRYPT_BUFFER_SIZE);
                                
                                    free(encrypted_oar_json);   // release the memory allocated for encrypted_oar_json > heapmem_free(encrypted_oar_json); (for platform specific os/lib/heapmem.h)
                                }
                                else // // if heap memory could be allocated for decrypted_oar_json...
                                {
                                    oar_crypt(oar_json_micro_buf, encrypted_oar_json); // encrypt oar_json_micro_buf and store it in encrypted_oar_json (function found in oar-crypt.h)
                                    
                                    printf("%s\n", encrypted_oar_json); printf("\n");
                                    printf("length of encrypted: %d\n", strlen(encrypted_oar_json)); printf("\n");

                                    // ::::::::::::::::::::::::::::::::::::::::::::::::::
                                    // DECRYPTION ///////////////////////////////////////
                                    // ::::::::::::::::::::::::::::::::::::::::::::::::::
                                    
                                    #if (OAR_CONF_CRYPT_DECRYPT)

                                        char *decrypted_oar_json = (char *)malloc((OAR_CONF_CRYPT_BUFFER_SIZE+1)*sizeof(char)); // allocate OAR_CONF_CRYPT_BUFFER_SIZE + 1 character size (*+1 for '\0' character) in heap memory for storing decrypted_oar_json > char *decrypted_oar_json = (char *)heapmem_alloc((OAR_CONF_CRYPT_BUFFER_SIZE+1)*sizeof(char)); (for platform specific os/lib/heapmem.h)

                                        printf("\n"); oar_debug_('~', 100); // print a seperation line > new line and inline '~' 100 times (function found in oar-debug.h)
                                        
                                        if (decrypted_oar_json == NULL) // if heap memory couldn't be allocated for decrypted_oar_json...
                                        {
                                            printf("OUT OF HEAP MEMORY > CANNOT ALLOCATE (%u + 1) CHARACTERS FOR DECRYPTION\n", OAR_CONF_CRYPT_BUFFER_SIZE);

                                            free(encrypted_oar_json);   // release the memory allocated for encrypted_oar_json > heapmem_free(encrypted_oar_json); (for platform specific os/lib/heapmem.h)
                                            free(decrypted_oar_json);   // release the memory allocated for decrypted_oar_json > heapmem_free(decrypted_oar_json); (for platform specific os/lib/heapmem.h) 
                                        }
                                        else // if heap memory could be allocated for decrypted_oar_json...
                                        {
                                            oar_crypt(encrypted_oar_json, decrypted_oar_json); // decrypt encrypted_oar_json and store it in decrypted_oar_json (function found in oar-crypt.h)
    
                                            printf("%s\n", decrypted_oar_json); printf("\n"); 
                                            printf("length of decrypted: %d\n", strlen(decrypted_oar_json));

                                            free(encrypted_oar_json);   // release the memory allocated for encrypted_oar_json > heapmem_free(encrypted_oar_json); (for platform specific os/lib/heapmem.h)
                                            free(decrypted_oar_json);   // release the memory allocated for decrypted_oar_json > heapmem_free(decrypted_oar_json); (for platform specific os/lib/heapmem.h)
                                        }

                                    #endif // (OAR_CONF_CRYPT_DECRYPT)

                                }
                                
                            #endif // (OAR_CONF_CRYPT)

                            free(oar_json_micro_buf); // release the memory allocated for oar_json_micro_buf > heapmem_free(oar_json_micro_buf); (for platform specific os/lib/heapmem.h)
                        }
                        
                    #endif // (OAR_CONF_JSON_TYPE == 3)

                    // ------------------------------------------------------------------------------------------------------------------------
                    // TINY JSON /////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    // ------------------------------------------------------------------------------------------------------------------------

                    #if (OAR_CONF_JSON_TYPE == 4) // use the tiny json (./oar-json-tiny.h) [project-conf.h]
                        
                        char *oar_json_tiny_buf = (char *)malloc((OAR_CONF_JSON_TINY_BUF_SIZE+1)*sizeof(char)); // allocate OAR_CONF_JSON_TINY_BUF_SIZE + 1 character size (*+1 for '\0' character) in heap memory for storing oar_json_tiny_buf > char *oar_json_tiny_buf = (char *)heapmem_alloc((OAR_CONF_JSON_TINY_BUF_SIZE+1)*sizeof(char)); (for platform specific os/lib/heapmem.h)

                        if (oar_json_tiny_buf == NULL) // if heap memory couldn't be allocated for oar_json_tiny_buf...
                        {
                            printf("OUT OF HEAP MEMORY > CANNOT ALLOCATE (%u + 1) CHARACTERS FOR TINY JSON\n", OAR_CONF_JSON_TINY_BUF_SIZE);
                            
                            free(oar_json_tiny_buf);   // release the memory allocated for encrypted_oar_json > heapmem_free(encrypted_oar_json); (for platform specific os/lib/heapmem.h)
                        }
                        else
                        {
                            oar_json_tiny_construct(oar_json_tiny_buf); // construct oar_json_tiny_buf (function found in ./oar_json_micro.h)
                            oar_json_tiny_print(oar_json_tiny_buf); // print oar_json_tiny_buf (function found in ./oar_json_micro.h)
                            
                            printf("\n"); printf("length of tiny json: %d\n", strlen(oar_json_tiny_buf));

                            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                            // ENCRYPTION / DECRYPTION ////////////////////////////////////////////////////////
                            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

                            #if (OAR_CONF_CRYPT) // if encryption functionality is enabled... [project-conf.h]

                                char *encrypted_oar_json = (char *)malloc((OAR_CONF_CRYPT_BUFFER_SIZE+1)*sizeof(char)); // allocate OAR_CONF_CRYPT_BUFFER_SIZE + 1 character size (*+1 for '\0' character) in heap memory for storing decrypted_oar_json > char *encrypted_oar_json = (char *)heapmem_alloc((OAR_CONF_CRYPT_BUFFER_SIZE+1)*sizeof(char)); (for platform specific os/lib/heapmem.h)

                                printf("\n"); oar_debug_('-', 100); printf("\n");   // print a seperation line > new line and inline '-' 100 times (function found in oar-debug.h)
                                
                                if (encrypted_oar_json == NULL) // if heap memory couldn't be allocated for encrypted_oar_json...
                                {
                                    printf("OUT OF HEAP MEMORY > CANNOT ALLOCATE (%u + 1) CHARACTERS FOR ENCRYPTION\n", OAR_CONF_CRYPT_BUFFER_SIZE);
                                
                                    free(encrypted_oar_json);   // release the memory allocated for encrypted_oar_json > heapmem_free(encrypted_oar_json); (for platform specific os/lib/heapmem.h)
                                }
                                else // // if heap memory could be allocated for decrypted_oar_json...
                                {
                                    oar_crypt(oar_json_tiny_buf, encrypted_oar_json); // encrypt oar_json_tiny_buf and store it in encrypted_oar_json (function found in oar-crypt.h)
                                    
                                    printf("%s\n", encrypted_oar_json); printf("\n");
                                    printf("length of encrypted: %d\n", strlen(encrypted_oar_json)); printf("\n");

                                    // ::::::::::::::::::::::::::::::::::::::::::::::::::
                                    // DECRYPTION ///////////////////////////////////////
                                    // ::::::::::::::::::::::::::::::::::::::::::::::::::
                                    
                                    #if (OAR_CONF_CRYPT_DECRYPT)

                                        char *decrypted_oar_json = (char *)malloc((OAR_CONF_CRYPT_BUFFER_SIZE+1)*sizeof(char)); // allocate OAR_CONF_CRYPT_BUFFER_SIZE + 1 character size (*+1 for '\0' character) in heap memory for storing decrypted_oar_json > char *decrypted_oar_json = (char *)heapmem_alloc((OAR_CONF_CRYPT_BUFFER_SIZE+1)*sizeof(char)); (for platform specific os/lib/heapmem.h)

                                        printf("\n"); oar_debug_('~', 100); // print a seperation line > new line and inline '~' 100 times (function found in oar-debug.h)
                                        
                                        if (decrypted_oar_json == NULL) // if heap memory couldn't be allocated for decrypted_oar_json...
                                        {
                                            printf("OUT OF HEAP MEMORY > CANNOT ALLOCATE (%u + 1) CHARACTERS FOR DECRYPTION\n", OAR_CONF_CRYPT_BUFFER_SIZE);

                                            free(encrypted_oar_json);   // release the memory allocated for encrypted_oar_json > heapmem_free(encrypted_oar_json); (for platform specific os/lib/heapmem.h)
                                            free(decrypted_oar_json);   // release the memory allocated for decrypted_oar_json > heapmem_free(decrypted_oar_json); (for platform specific os/lib/heapmem.h) 
                                        }
                                        else // if heap memory could be allocated for decrypted_oar_json...
                                        {
                                            oar_crypt(encrypted_oar_json, decrypted_oar_json); // decrypt encrypted_oar_json and store it in decrypted_oar_json (function found in oar-crypt.h)
    
                                            printf("%s\n", decrypted_oar_json); printf("\n"); 
                                            printf("length of decrypted: %d\n", strlen(decrypted_oar_json));

                                            free(encrypted_oar_json);   // release the memory allocated for encrypted_oar_json > heapmem_free(encrypted_oar_json); (for platform specific os/lib/heapmem.h)
                                            free(decrypted_oar_json);   // release the memory allocated for decrypted_oar_json > heapmem_free(decrypted_oar_json); (for platform specific os/lib/heapmem.h)
                                        }

                                    #endif // (OAR_CONF_CRYPT_DECRYPT)

                                }
                                
                            #endif // (OAR_CONF_CRYPT)

                            free(oar_json_tiny_buf); // release the memory allocated for oar_json_tiny_buf > heapmem_free(oar_json_tiny_buf); (for platform specific os/lib/heapmem.h)
                        }
                        
                    #endif // (OAR_CONF_JSON_TYPE == 4)

                    printf("\n"); oar_debug_('=', 100); printf("\n");   // print a seperation line > new line and inline '=' 100 times (function found in oar-debug.h)
                
                #endif // (OAR_CONF_JSON)

                // ================================================================================================================================================================
                // DEBUG //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                // ================================================================================================================================================================

                #if (OAR_CONF_DEBUG)

                    // ::::::::::::::::::::::::::::::::::::::::::::::::::
                    // ENERGY CONSUMPTION VALUES ////////////////////////
                    // ::::::::::::::::::::::::::::::::::::::::::::::::::
                
                    #if (OAR_CONF_DEBUG_ENERGY) // print the energy consumption values... [project-conf.h]

                        oar_debug_energy(clock_seconds());                                  // (function found in ./oar-debug.c)
                        oar_debug_('-', 192);                                               // (function found in ./oar-debug.c)

                    #endif // OAR_CONF_DEBUG_ENERGY

                    // ::::::::::::::::::::::::::::::::::::::::::::::::::
                    // UIP STATISTICS ///////////////////////////////////
                    // ::::::::::::::::::::::::::::::::::::::::::::::::::                                                              

                    #if (OAR_CONF_DEBUG_STATISTICS) // print the uip statistics... [project-conf.h]
                        
                        oar_debug_statistics_ip(clock_seconds());           printf("\n");   // (function found in ./oar-debug.c)                                  

                        oar_debug_statistics_icmp(clock_seconds());         printf("\n");   // (function found in ./oar-debug.c) 

                        
                        // -+-+-+-+-+-+-+-+-+-+-+-+--+-+-+-+-+-+-+
                        #if UIP_TCP

                            oar_debug_statistics_tcp(clock_seconds());      printf("\n");   // (function found in ./oar-debug.c)                
                        
                        #endif  /* UIP_TCP */
                        // -+-+-+-+-+-+-+-+-+-+-+-+--+-+-+-+-+-+-+
                        // -+-+-+-+-+-+-+-+-+-+-+-+--+-+-+-+-+-+-+
                        #if UIP_UDP

                            oar_debug_statistics_udp(clock_seconds());      printf("\n");   // (function found in ./oar-debug.c)

                        #endif  /* UIP_UDP */
                        // -+-+-+-+-+-+-+-+-+-+-+-+--+-+-+-+-+-+-+
                    
                        oar_debug_statistics_nd6(clock_seconds());                          // (function found in ./oar-debug.c)
                        oar_debug_('-', 192);                                               // (function found in ./oar-debug.c)

                    #endif // (OAR_CONF_DEBUG_STATISTICS)

                    // ::::::::::::::::::::::::::::::::::::::::::::::::::
                    // NETWORKING INFO //////////////////////////////////
                    // ::::::::::::::::::::::::::::::::::::::::::::::::::  
                    
                    #if (OAR_CONF_DEBUG_NETWORK) // print the networking info... [project-conf.h]

                        // -+-+-+-+-+-+-+-+-+-+-+-+--+-+-+-+-+-+-+
                        #if ROUTING_CONF_RPL_LITE

                            oar_debug_net_rpl_nbr(clock_seconds());         printf("\n");   // (function found in ./oar-debug.c)
                            oar_debug_net_rpl_status(clock_seconds());      printf("\n");   // (function found in ./oar-debug.c)
                            
                        #endif /* ROUTING_CONF_RPL_LITE */
                        // -+-+-+-+-+-+-+-+-+-+-+-+--+-+-+-+-+-+-+

                        oar_debug_net_macaddr(clock_seconds());             printf("\n");   // (function found in ./oar-debug.c)

                        // -+-+-+-+-+-+-+-+-+-+-+-+--+-+-+-+-+-+-+
                        #if NETSTACK_CONF_WITH_IPV6

                            oar_debug_net_ipaddr(clock_seconds());          printf("\n");    // (function found in ./oar-debug.c)
                            oar_debug_net_ip_neighbors(clock_seconds());    printf("\n");    // (function found in ./oar-debug.c)
                            

                        #endif  /* NETSTACK_CONF_WITH_IPV6 */
                        // -+-+-+-+-+-+-+-+-+-+-+-+--+-+-+-+-+-+-+
                        // -+-+-+-+-+-+-+-+-+-+-+-+--+-+-+-+-+-+-+
                        #if MAC_CONF_WITH_TSCH

                            oar_debug_net_tsch_status(clock_seconds());      printf("\n");  // (function found in ./oar-debug.c)

                        #endif  /* MAC_CONF_WITH_TSCH */
                        // -+-+-+-+-+-+-+-+-+-+-+-+--+-+-+-+-+-+-+
                        // -+-+-+-+-+-+-+-+-+-+-+-+--+-+-+-+-+-+-+
                        #if NETSTACK_CONF_WITH_IPV6

                            oar_debug_net_routes(clock_seconds());                          // (function found in ./oar-debug.c)

                        #endif  /* NETSTACK_CONF_WITH_IPV6 */
                        // -+-+-+-+-+-+-+-+-+-+-+-+--+-+-+-+-+-+-+
                    
                        printf("\n");

                    #endif // (OAR_CONF_DEBUG_NETWORK)
                
                #endif //(OAR_CONF_DEBUG)
                    
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
                
                // process_poll(&oar_dev_process);

            }

            

        PROCESS_END();

        //  #if (OAR_CONF_JSON == 1) && (OAR_CONF_CRYPT == 1)

        //         heapmem_free(encrypted_oar_json);
        //         heapmem_free(decrypted_oar_json);

        // #endif // (OAR_CONF_JSON == 1) && (OAR_CONF_CRYPT == 1)
    
    #endif // (OAR_CONF_DEBUG_FUNCTIONALITY)

    
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

        #endif  /* OAR_DEV */
    }
    
    