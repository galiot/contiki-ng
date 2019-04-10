///////////////////////////////////////////////////////////////////////////////
// contiki-ng restful mote monitoring backend /////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// Coded by: galiot (2018/2019) ///////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////// 
















#include "contiki.h"                // main include file for OS-specific modules

#include "net/ipv6/uiplib.h"
#include "net/ipv6/uip-icmp6.h"
#include "net/ipv6/uip-ds6.h"

#if ROUTING_CONF_RPL_LITE
    #include "net/routing/rpl-lite/rpl.h"
#elif ROUTING_CONF_RPL_CLASSIC
    #include "net/routing/rpl-classic/rpl.h"
#endif

#include "net/routing/routing.h"    // for NETSTACK_ROUTING


#include "sys/energest.h"           // for lightweight, software-based energy estimation for resource-constrained IoT devices
#include "net/ipv6/uip.h"           // for structure holding the TCP/IP statistics (that are gathered if UIP_STATISTICS is set to 1)
#include "lib/heapmem.h"            // heap memory module that has been used on a variety of hardware platforms and with different applications

// -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-

                                    // Texas Instruments CC2650 LaunchPad enabales the following dev I/0:

#include "dev/leds.h"               // leds     (2):    LEDS_LED1, LEDS_LED2 (access both: LEDS_ALL)
#include "dev/button-hal.h"         // buttons  (2):    button_hal_get_by_index(0), button_hal_get_by_index(1)    

// ~:~:~:~:~:~:~:~:~:~:~:~:~:~:~:~:~:~:~:~:~:~:~:~:~:~:~:~:~:~:~:~:~:~:~:~:~:~:~:~:~:~:~:~:~:~:~:~:~:~:~:~:~:~:~:~:~:~:~:~:~:~:~:~:~:~:~

#include "project-conf.h"           // for vscode intellisense (make recipe includes it either way)

#include "oar-debug.h"              // for debugging energest, uip statistics and routing values. Prints periodicaly on UART, serial console.
#include "httpd-simple.h"           // modified rpl-border-router simple http server, modified to serve headers with application/json content type

#if (OAR_CONF_JSON_TYPE == 0)
    #include "oar-json.h"           // for quantized JSON construction, abbreviated and fine-tuned for sending through tcp/ip stack, encrypted and base64 encoding, memory guarded
#endif

#if (OAR_CONF_JSON_TYPE == 1)
    #include "oar-json-extended.h"  // 1st attemp in JSON construction, verbose, non-discretizable and too large for encryption, encoding and/or sending through tcp/ip stack (debugging only)
#endif

#if (OAR_CONF_JSON_TYPE == 2)
    #include "oar-json-compact.h"   // 2nd attemp in JSON construction fewer sections but still non-discretizable and too large for encryption, encoding and/or sending through tcp/ip stack (debugging only)
#endif

#if (OAR_CONF_JSON_TYPE == 3)
    #include "oar-json-micro.h"     // 3nd attemp in JSON construction, now abbreviated but still non-discretizable and too large for encryption, encoding and/or sending through tcp/ip stack (debugging only)
#endif

#if (OAR_CONF_JSON_TYPE == 4)
    #include "oar-json-tiny.h"      // 4th attemp in JSON construction, fewer sections and abbreviated, dicretizable and in part cabable for encryption and sending some parts of it through tcp/ip stack. Still, too large the base64 33% overhead encoding (debugging only)
#endif

#include "oar-crypt.h"              // for modified XOR encryption
#include "oar-base64.h"             // for modified base64 encoding
#include "oar-hash.h"               // for modified sdbm hashing

// ---<|>---<|>---<|>---<|>---<|>---<|>---<|>---<|>---<|>---<|>---<|>---<|>---<|>---<|>---<|>---<|>---<|>---<|>---<|>---<|>---<|>---<|>-

#include <stdio.h>                  // for prinntf(), sprintf(), snprintf() etc. 
#include <stdlib.h>                 // for heap memory managment, by malloc(), realloc() and free()




char oar_json_lladdr[UIPLIB_IPV6_MAX_STR_LEN]; // holds link local address, created by: oar_json_lladdr_to_str() [oar_json.h]


// ----------------------------------------------------------------------------
    // function that sequentially prints a char set times /////////////////////////
    // ----------------------------------------------------------------------------
    void console_seq_print(char symbol, int times)
    {
        for (int i = 0; i < times; i++)
        {
            printf("%c", symbol);
        }

        printf("\n");
    }

    // ----------------------------------------------------------------------------
    // function that initializes (empties) the json string ////////////////////////
    // and sends just the pckt section with error appended //////////////////////// 
    // ----------------------------------------------------------------------------

    // {
    //     "pckt": {
    //         "vld": false,
    //         "err": {
    //             "cd": 111,
    //             "txt": "JSON TYPE NOT SUITABLE FOR TCP/IP STACK: EXTENDED"
    //         }
    //     },
    //     "id": {
    //         "sT": 23,
    //         "adr": "0012.4b00.0f83.b601",
    //         "cd": "RED"
    //     },
    //     "hash": "2350848843"
    // }
    
    void oar_json_error_construct(char *buf, int valid, char *error_text, int error_code)
    {
        
        char str[256];

        // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        // SECTION START pckt{} ////////////////////////////////
        // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        sprintf(str, "{"                    ); strcpy(buf, str);
        sprintf(str, "\"" "pckt" "\"" ":"   ); strcat(buf, str);
        sprintf(str, "{"                    ); strcat(buf, str);
        // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        
            sprintf(str, "\"" "vld" "\"" ":" "%s" ,valid ? "true" : "false"); strcat(buf, str);

            // ?????????????????????????????????
            sprintf(str, ","); strcat(buf, str);
            // ?????????????????????????????????

            if (valid)
            {
                sprintf(str,        "\"" "err"  "\"" ":"        "null"                  ); strcat(buf, str);
            }
            else
            {
                // -/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-
                // SUBSECTION START pckt{} > error{} ///////////////////
                // -/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-
                sprintf(str, "\"" "err" "\"" ":"    ); strcat(buf, str);
                sprintf(str, "{"                    ); strcat(buf, str);
                // -/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-

                    sprintf(str,    "\"" "cd"   "\"" ":"        "%d"        ,error_code ); strcat(buf, str);    sprintf(str, ","); strcat(buf, str);
                    sprintf(str,    "\"" "txt"  "\"" ":" "\""   "%s" "\""   ,error_text ); strcat(buf, str);    

                // -/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/
                sprintf(str, "}"); strcat(buf, str); //
                // -/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/
                // SUBSECTION END pckt{} > error{} ////
                // -/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/
            }

        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        sprintf(str, "}"); strcat(buf, str);
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // SECTION END pckt{} //////////////
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

        // ?????????????????????????????????
        sprintf(str, ","); strcat(buf, str);
        // ?????????????????????????????????

        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // SECTION START id{} //////////////////////////////////
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        sprintf(str, "\"" "id" "\"" ":" ); strcat(buf, str); ///
        sprintf(str, "{"                ); strcat(buf, str); ///
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        
            // ttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttt
            sprintf(str,    "\"" "sT"       "\"" ":"            "%lu"                       ,clock_seconds()  ); strcat(buf, str);  sprintf(str, ","); strcat(buf, str);
            // ttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttt

            #if (OAR_CONF_JSON_TYPE == 0)

                oar_json_lladdr_to_str(oar_json_lladdr, &linkaddr_node_addr);

            #endif // (OAR_CONF_JSON_TYPE == 0)
            #if (OAR_CONF_JSON_TYPE == 1)

                oar_json_extended_lladdr_to_str(oar_json_lladdr, &linkaddr_node_addr);

            #endif // (OAR_CONF_JSON_TYPE == 1)
            #if (OAR_CONF_JSON_TYPE == 2)

                oar_json_compact_lladdr_to_str(oar_json_lladdr, &linkaddr_node_addr);

            #endif // (OAR_CONF_JSON_TYPE == 2)
            #if (OAR_CONF_JSON_TYPE == 3)

                oar_json_micro_lladdr_to_str(oar_json_lladdr, &linkaddr_node_addr);

            #endif // (OAR_CONF_JSON_TYPE == 3)
            #if (OAR_CONF_JSON_TYPE == 4)

                oar_json_tiny_lladdr_to_str(oar_json_lladdr, &linkaddr_node_addr);

            #endif // (OAR_CONF_JSON_TYPE == 4)
            
            sprintf(str,    "\"" "adr"      "\"" ":" "\""    "%s"                   "\""    ,oar_json_lladdr    ); strcat(buf, str);  sprintf(str, ","); strcat(buf, str);
            sprintf(str,    "\"" "cd"       "\"" ":" "\""    OAR_CONF_MOTE_COLOR    "\""                        ); strcat(buf, str);
        
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        sprintf(str, "}" ); strcat(buf, str); //
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // SECTION END id{} ////////////////////
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

        // ?????????????????????????????????
        sprintf(str, ","); strcat(buf, str);
        // ?????????????????????????????????

        sprintf(str,        "\"" "hash"     "\"" ":" "\""    "%u"                   "\""    ,oar_sdbm(buf)    ); strcat(buf, str);
        
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        sprintf(str, "}" ); strcat(buf, str); //
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    }

    








// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
// GLOBAL DECLARATIONS /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

// (doc) A process is first declared at the top of a source file.
// (doc) The PROCESS() macro takes two arguments:   
// (doc) // one is the variable with which we identify the process, 
// (doc) // and the other is the name of the process. 
// (doc) On the second line, we tell Contiki-NG that this process should be automatically started directly after the system has booted up. 
// (doc) Multiple processes can be specified here by separating them with commas. 


PROCESS(oar_debug_process, "oar debug process");                    // process for printing on console
PROCESS(webserver_process, "webserver process");
PROCESS(oar_buoy_process, "oar buoy process");

#if (OAR_CONF_DEBUG_FUNCTIONALITY)

    #if (OAR_CONF_JSON == 1) 


            int counter = 0; // type 0 json is quantized, it's structured to be sent in pieces (so that they fit inside a tcp/ip packet). This variable is the piece index.
        
  
    #endif

    AUTOSTART_PROCESSES(&oar_debug_process);

#endif // (OAR_CONF_DEBUG_FUNCTIONALITY)

#if (OAR_CONF_BUOY_FUNCTIONALITY)

    int counter = 0; // type 0 json is quantized, it's structured to be sent in pieces (so that they fit inside a tcp/ip packet). This variable is the piece index.

    
    
    

    AUTOSTART_PROCESSES(&oar_buoy_process);

#endif // (OAR_CONF_BUOY_FUNCTIONALITY)
















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
// now the string httpd_simple_script_t[]   --> struct httpd_state s[]                            
















// #!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#
// BUOY ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// #!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#

static PT_THREAD(generate_routes(struct httpd_state *s))
{
    char buffer[OAR_CONF_BUOY_BUFFER_SIZE];
    char error_json[255];

    PSOCK_BEGIN(&s->sout); // Start the protosocket protothread in a function.
    
    #if (OAR_CONF_DEV)

        leds_single_on(LEDS_LED1);
    
    #endif // (OAR_CONF_DEV)

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

    printf("\n");

    printf("[OAR] > "); console_seq_print('=', 72);
    printf("[OAR] > ITERATION: %d ", counter); console_seq_print('/', 58);
    printf("[OAR] > "); console_seq_print('=', 72);

    // ================================================================================================================================================================
    // JSON ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // ================================================================================================================================================================
            
    #if (OAR_CONF_JSON)

        // ------------------------------------------------------------------------------------------------------------------------
        // JSON ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // ------------------------------------------------------------------------------------------------------------------------

        #if (OAR_CONF_JSON_TYPE == 0) // use the quantized json (./oar-json-quantized.h) [project-conf.h]
                    
            char *oar_json_buf = (char *)malloc((OAR_CONF_JSON_BUF_SIZE+1)*sizeof(char)); // allocate OAR_CONF_JSON_BUF_SIZE + 1 character size (*+1 for '\0' character) in heap memory for storing oar_json_buf > char *oar_json_buf = (char *)heapmem_alloc((OAR_CONF_JSON_BUF_SIZE+1)*sizeof(char)); (for platform specific os/lib/heapmem.h)

            if (oar_json_buf == NULL) // if heap memory couldn't be allocated for oar_json_buf...
            {
                printf("\n");

                // printf("[OAR] > "); console_seq_print('-', 70);
                printf("[OAR] > HEAP MEMORY EXHAUSTED > JSON BUFFER ALLOCATION OF (%u + 1) CHARACTERS NOT POSSIBLE\n", OAR_CONF_JSON_BUF_SIZE);
                // printf("[OAR] > "); console_seq_print('-', 70);

                printf("\n");

                oar_json_error_construct(error_json, 0, "EXHAUSTED HEAP MEMORY: JSON BUFFER ALLOCATION NOT POSSIBLE", 900);
                
                // $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
                printf("[OAR] > "); console_seq_print(':', 29); ////
                printf("[OAR] > STAGING > ALLOCATION ERROR JSON\n");
                printf("[OAR] > "); console_seq_print(':', 29); ////
                // $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
                strcpy(buffer, error_json); ////////////////////////
                // $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
            }
            else
            {
                printf("\n");

                // printf("[OAR] > "); console_seq_print('-', 5);
                printf("[OAR] > JSON:\n");
                // printf("[OAR] > "); console_seq_print('-', 5);

                printf("\n");
                
                oar_json_construct(oar_json_buf, counter % 23); // construct oar_json_buf (function found in ./oar_json_micro.h)
                oar_json_print(oar_json_buf); // print oar_json_buf (function found in ./oar_json_micro.h)

                printf("\n");
                
                // printf("[OAR] > "); console_seq_print('-', 16);
                printf("[OAR] > JSON LENGTH: %d\n", strlen(oar_json_buf));
                // printf("[OAR] > "); console_seq_print('-', 16);

                printf("\n");

                // $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
                printf("[OAR] > "); console_seq_print('+', 26); ////////////
                printf("[OAR] > STAGING > JSON, QUANTUM %2d\n", counter);
                printf("[OAR] > "); console_seq_print('+', 26); ////////////
                // $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
                strcpy(buffer, oar_json_buf); //////////////////////////////
                // $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
            }

            free(oar_json_buf); // release the memory allocated for oar_json_buf > heapmem_free(oar_json_buf); (for platform specific os/lib/heapmem.h)
        
        #endif // (OAR_CONF_JSON_TYPE == 0)

        // ------------------------------------------------------------------------------------------------------------------------
        // EXTENDED JSON //////////////////////////////////////////////////////////////////////////////////////////////////////////
        // ------------------------------------------------------------------------------------------------------------------------

        #if (OAR_CONF_JSON_TYPE == 1) // use the extended json (./oar-json-extended.h) [project-conf.h]

            printf("\n");

            // printf("[OAR] > "); console_seq_print('-', 43);
            printf("[OAR] > EXTENDED JSON NOT SUITABLE FOR TCP/IP STACK\n");
            // printf("[OAR] > "); console_seq_print('-', 43);

            oar_json_error_construct(error_json, 0, "JSON TYPE NOT SUITABLE FOR TCP/IP STACK: EXTENDED", 111);

            printf("\n");

            // $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
            printf("[OAR] > "); console_seq_print(':', 40); //
            printf("[OAR] > STAGING > EXTENDED JSON ERROR\n");
            printf("[OAR] > "); console_seq_print(':', 40); //
            // $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
            strcpy(buffer, error_json); //////////////////////
            // $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
            
        #endif // (OAR_CONF_JSON_TYPE == 1)

        // ------------------------------------------------------------------------------------------------------------------------
        // COMPACT JSON ///////////////////////////////////////////////////////////////////////////////////////////////////////////
        // ------------------------------------------------------------------------------------------------------------------------

        #if (OAR_CONF_JSON_TYPE == 2) // use the compact json (./oar-json-compact.h) [project-conf.h]

            printf("\n");

            // printf("[OAR] > "); console_seq_print('-', 42);
            printf("[OAR] > COMPACT JSON NOT SUITABLE FOR TCP/IP STACK\n");
            // printf("[OAR] > "); console_seq_print('-', 42);

            oar_json_error_construct(error_json, 0, "JSON TYPE NOT SUITABLE FOR TCP/IP STACK: COMPACT", 222);

            printf("\n");

            // $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
            printf("[OAR] > "); console_seq_print(':', 28); ////
            printf("[OAR] > STAGING > COMPACT JSON ERROR\n"); //
            printf("[OAR] > "); console_seq_print(':', 28); ////
            // $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
            strcpy(buffer, error_json); ////////////////////////
            // $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

        #endif // (OAR_CONF_JSON_TYPE == 2)

        // ------------------------------------------------------------------------------------------------------------------------
        // MICRO JSON /////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // ------------------------------------------------------------------------------------------------------------------------

        #if (OAR_CONF_JSON_TYPE == 3) // use the compact json (./oar-json-compact.h) [project-conf.h]

            printf("\n");

            // printf("[OAR] > "); console_seq_print('-', 40);
            printf("[OAR] > MICRO JSON NOT SUITABLE FOR TCP/IP STACK\n");
            // printf("[OAR] > "); console_seq_print('-', 40);

            oar_json_error_construct(error_json, 0, "JSON TYPE NOT SUITABLE FOR TCP/IP STACK: MICRO", 333);

            printf("\n");

            // $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
            printf("[OAR] > "); console_seq_print(':', 26);
            printf("[OAR] > STAGING > MICRO JSON ERROR\n");
            printf("[OAR] > "); console_seq_print(':', 26);
            // $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
            strcpy(buffer, error_json); ///////////////////
            // $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

        #endif // (OAR_CONF_JSON_TYPE == 3)

        // ------------------------------------------------------------------------------------------------------------------------
        // TINY JSON //////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // ------------------------------------------------------------------------------------------------------------------------
    
        #if (OAR_CONF_JSON_TYPE == 4) // use the tiny json (./oar-json-tiny.h) [project-conf.h]
                    
            printf("\n");

            // printf("[OAR] > "); console_seq_print('-', 42);
            printf("[OAR] > TINY JSON NOT RECOMMENDED FOR TCP/IP STACK\n");
            // printf("[OAR] > "); console_seq_print('-', 42);

            oar_json_error_construct(error_json, 0, "JSON TYPE NOT RECOMMENDED FOR TCP/IP STACK: TINY", 444);

            printf("\n");

            // $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
            printf("[OAR] > "); console_seq_print(':', 25); //
            printf("[OAR] > STAGING > TINY JSON ERROR\n"); ///
            printf("[OAR] > "); console_seq_print(':', 25); //
            // $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
            strcpy(buffer, error_json); //////////////////////
            // $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
            
        #endif // (OAR_CONF_JSON_TYPE == 4)

    #else // (OAR_CONF_JSON)

        printf("\n");

        // printf("[OAR] > "); console_seq_print('-', 30);
        printf("[OAR] > JSON FUNCTIONALITY NOT ENABLED\n");
        // printf("[OAR] > "); console_seq_print('-', 30);

        oar_json_error_construct(error_json, 0, "JSON FUNCTIONALITY NOT ENABLED", 999);

        printf("\n");
        
        // $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
        printf("[OAR] > "); console_seq_print(':', 29); ///////
        printf("[OAR] > STAGING > JSON FUNCTIONALITY ERROR\n");
        printf("[OAR] > "); console_seq_print(':', 29); ///////
        // $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
        strcpy(buffer, error_json); ///////////////////////////
        // $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

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




    printf("\n");

    printf("[OAR] > "); console_seq_print('-', 72);

    // <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><
    // XOR ENCRYPTION / DECRYPTION ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><

    #if (OAR_CONF_CRYPT) // if encryption functionality is enabled... [project-conf.h]

        char *encrypted_oar_json = (char *)malloc((OAR_CONF_CRYPT_BUFFER_SIZE+1)*sizeof(char)); // allocate OAR_CONF_CRYPT_BUFFER_SIZE + 1 character size (*+1 for '\0' character) in heap memory for storing decrypted_oar_json > char *encrypted_oar_json = (char *)heapmem_alloc((OAR_CONF_CRYPT_BUFFER_SIZE+1)*sizeof(char)); (for platform specific os/lib/heapmem.h)
        
        if (encrypted_oar_json == NULL) // if heap memory couldn't be allocated for encrypted_oar_json...
        {
            printf("\n");

            // printf("[OAR] > "); console_seq_print('~', 83);
            printf("[OAR] > HEAP MEMORY EXHAUSTED > ENCRYPTION BUFFER ALLOCATION OF (%u + 1) CHARACTERS NOT POSSIBLE\n", OAR_CONF_CRYPT_BUFFER_SIZE);
            // printf("[OAR] > "); console_seq_print('~', 83);

            oar_json_error_construct(error_json, 0, "EXHAUSTED HEAP MEMORY: ENCRYPTION BUFFER ALLOCATION NOT POSSIBLE", 901);

            printf("\n");

            // $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
            printf("[OAR] > "); console_seq_print(':', 40); ///////////////
            printf("[OAR] > STAGING > ENCRYPTION ALLOCATION ERROR JSON\n");
            printf("[OAR] > "); console_seq_print(':', 40); ///////////////
            // $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
            strcpy(buffer, error_json); ///////////////////////////////////
            // $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
        }
        else // if heap memory could be allocated for decrypted_oar_json...
        {
            oar_crypt(encrypted_oar_json, buffer); // encrypt oar_json_buf and store it in encrypted_oar_json (function found in oar-crypt.h)
            
            printf("\n");

            // printf("[OAR] > "); console_seq_print('~', 15);
            printf("[OAR] > ENCRYPTED JSON:\n");
            // printf("[OAR] > "); console_seq_print('~', 15);

            printf("\n");
            
            printf("%s\n", encrypted_oar_json); 
            
            printf("\n");

            // printf("[OAR] > "); console_seq_print('~', 29);
            printf("[OAR] > LENGTH OF ENCRYPTED JSON: %d\n", strlen(encrypted_oar_json));
            // printf("[OAR] > "); console_seq_print('~', 29);

            printf("\n");

            // $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
            printf("[OAR] > "); console_seq_print('+', 24); //
            printf("[OAR] > STAGING > ENCRYPTED JSON\n"); ////
            printf("[OAR] > "); console_seq_print('+', 24); //
            // $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
            strcpy(buffer, encrypted_oar_json); //////////////
            // $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

            // :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
            // DECRYPTION //////////////////////////////////////////////////////////////////////////////////////////////
            // :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
            
            #if (OAR_CONF_CRYPT_DECRYPT)

                char *decrypted_oar_json = (char *)malloc((OAR_CONF_CRYPT_BUFFER_SIZE+1)*sizeof(char)); // allocate OAR_CONF_CRYPT_BUFFER_SIZE + 1 character size (*+1 for '\0' character) in heap memory for storing decrypted_oar_json > char *decrypted_oar_json = (char *)heapmem_alloc((OAR_CONF_CRYPT_BUFFER_SIZE+1)*sizeof(char)); (for platform specific os/lib/heapmem.h)
                
                if (decrypted_oar_json == NULL) // if heap memory couldn't be allocated for decrypted_oar_json...
                {
                    printf("\n");

                    // printf("[OAR] > "); console_seq_print('~', 83);
                    printf("[OAR] > HEAP MEMORY EXHAUSTED > DECRYPTION BUFFER ALLOCATION OF (%u + 1) CHARACTERS NOT POSSIBLE\n", OAR_CONF_CRYPT_BUFFER_SIZE);
                    // printf("[OAR] > "); console_seq_print('~', 83);
                }
                else // if heap memory could be allocated for decrypted_oar_json...
                {
                    oar_crypt(decrypted_oar_json, encrypted_oar_json); // decrypt encrypted_oar_json and store it in decrypted_oar_json (function found in oar-crypt.h)
                    
                    printf("\n");

                    // printf("[OAR] > "); console_seq_print('~', 15);
                    printf("[OAR] > DECRYPTED JSON:\n");
                    // printf("[OAR] > "); console_seq_print('~', 15);

                    printf("\n");
                    
                    printf("%s\n", decrypted_oar_json); 
                    
                    printf("\n");

                    // printf("[OAR] > "); console_seq_print('~', 29);
                    printf("[OAR] > LENGTH OF DECRYPTED JSON: %d\n", strlen(decrypted_oar_json));
                    // printf("[OAR] > "); console_seq_print('~', 29);
                }

                free(decrypted_oar_json);   // release the memory allocated for decrypted_oar_json > heapmem_free(decrypted_oar_json); (for platform specific os/lib/heapmem.h) 

            #endif // (OAR_CONF_CRYPT_DECRYPT)

            free(encrypted_oar_json);   // release the memory allocated for encrypted_oar_json > heapmem_free(encrypted_oar_json); (for platform specific os/lib/heapmem.h)
        }
        
    #else // (OAR_CONF_CRYPT)

        printf("\n");

        // printf("[OAR] > "); console_seq_print('~', 37);
        printf("[OAR] > ENCRYPTION FUNCTIONALITY NOT ENABLED:\n");
        // printf("[OAR] > "); console_seq_print('~', 37);    

    #endif // (OAR_CONF_CRYPT)




        // JJJJJJJJJJ
        // JJJJJJJJJJ
        // JJJJJJJJJJ
        // JJJJJJJJJJ
        // JJJJJJJJJJ
        // JJJJJJJJJJ
        // JJJJJJJJJJ
        // JJJJJJJJJJ
        // JJJJJJJJJJ
        



    printf("\n");
    
    printf("[OAR] > "); console_seq_print('-', 72);
    
    // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    // BASE64 ENCODING ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    
    #if (OAR_CONF_BASE64_ENCODING)

        char *oar_base64_encoded_json = (char *)malloc((OAR_CONF_BASE64_ENCODING_BUFFER_SIZE+1)*sizeof(char)); // allocate OAR_CONF_BASE64_ENCODING_BUF_SIZE + 1 character size (*+1 for '\0' character) in heap memory for encoding oar_json_buf > char *oar_base64_endcoded = (char *)heapmem_alloc((OAR_CONF_JSON_BUF_SIZE+1)*sizeof(char)); (for platform specific os/lib/heapmem.h)

        if (oar_base64_encoded_json == NULL)
        {
            printf("\n");

            // printf("[OAR] > "); console_seq_print('~', 83);
            printf("[OAR] > HEAP MEMORY EXHAUSTED > BASE64 ENCODING BUFFER ALLOCATION OF (%u + 1) CHARACTERS NOT POSSIBLE\n", OAR_CONF_BASE64_ENCODING_BUFFER_SIZE);
            // printf("[OAR] > "); console_seq_print('~', 83);

            oar_json_error_construct(error_json, 0, "EXHAUSTED HEAP MEMORY: BASE64 ENCODING BUFFER ALLOCATION NOT POSSIBLE", 902);

            printf("\n");

            // $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
            printf("[OAR] > "); console_seq_print(':', 40); ////////////////////
            printf("[OAR] > STAGING > BASE64 ENCODING ALLOCATION ERROR JSON\n");
            printf("[OAR] > "); console_seq_print(':', 40); ////////////////////
            // $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
            strcpy(buffer, error_json); ////////////////////////////////////////
            // $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
        
        }
        else
        {
            oar_base64_encode(buffer, oar_base64_encoded_json, strlen(buffer));
            
            printf("\n");

            // printf("[OAR] > "); console_seq_print('~', 20);
            printf("[OAR] > BASE64 ENCODED JSON:\n");
            // printf("[OAR] > "); console_seq_print('~', 20);

            printf("\n");
            
            printf("%s\n", oar_base64_encoded_json); 
            
            printf("\n");

            // printf("[OAR] > "); console_seq_print('*', 34);
            printf("[OAR] > LENGTH OF BASE64 ENCODED JSON: %d\n", strlen(oar_base64_encoded_json));
            // printf("[OAR] > "); console_seq_print('*', 34);

            printf("\n");

            // $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
            printf("[OAR] > "); console_seq_print('+', 30); //
            printf("[OAR] > STAGING > BASE64 ENCODING JSON\n");
            printf("[OAR] > "); console_seq_print('+', 30); //
            // $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
            strcpy(buffer, oar_base64_encoded_json); /////////
            // $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
        }

        free(oar_base64_encoded_json);

    #else // (OAR_CONF_BASE64_ENCODING)

        printf("\n");

        // printf("[OAR] > "); console_seq_print('~', 42);
        printf("[OAR] > BASE64 ENCODING FUNCTIONALITY NOT ENABLED:\n");
        // printf("[OAR] > "); console_seq_print('~', 42);  

    #endif // (OAR_CONF_BASE64_ENCODING)




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

    
    

    if (strlen(buffer) > OAR_CONF_BUOY_MAX_PAYLOAD_LENGTH)
    {
        printf("\n");

        console_seq_print('|', 81);
        printf("ABORT SENDING JSON: PAYLOAD LENGHT %d > %d > ECONNRESET/ETIMEDOUT ERRORS POSSIBLE\n", strlen(buffer), OAR_CONF_BUOY_MAX_PAYLOAD_LENGTH);

        oar_json_error_construct(error_json, 0, "JSON PAYLOAD EXCEEDS TCP/IP STABILITY", 999);

        printf("\n");

        // $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
        printf("[OAR] > "); console_seq_print(':', 47); //////
        printf("[OAR] > STAGING > PAYLOAD SIZE ERROR JSON\n");
        printf("[OAR] > "); console_seq_print(':', 47); //////
        // $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
        strcpy(buffer, error_json); //////////////////////////
        // $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

        #if (OAR_CONF_CRYPT)

            strcpy(error_json, buffer);
            oar_crypt(buffer, error_json);

            // $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
            printf("[OAR] > "); console_seq_print(':', 47); ////////////////
            printf("[OAR] > STAGING > PAYLOAD SIZE ERROR ENCRYPTED JSON\n"); 
            printf("[OAR] > "); console_seq_print(':', 47); ////////////////
            // $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
            strcpy(buffer, error_json); ////////////////////////////////////
            // $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

        #endif // (OAR_CONF_CRYPT)

        #if (OAR_CONF_BASE64_ENCODING)

            strcpy(error_json, buffer);
            oar_base64_encode(error_json, buffer, strlen(error_json));

            // $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
            printf("[OAR] > "); console_seq_print(':', 47); /////////////////////
            printf("[OAR] > STAGING > PAYLOAD SIZE ERROR BASE64 ENCODED JSON\n");
            printf("[OAR] > "); console_seq_print(':', 47); /////////////////////
            // $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
            strcpy(buffer, error_json); /////////////////////////////////////////
            // $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

        #endif // (OAR_CONF_BASE64_ENCODING)

        SEND_STRING(&s->sout, buffer); // PSOCK_SEND(&s->sout, (uint8_t *)buffer, strlen(buffer)) > Send data.
    }
    else
    {
        printf("\n"); 
        
        printf("[OAR] > "); console_seq_print('|', 12);
        printf("[OAR] > SENDING JSON\n");
        printf("[OAR] > "); console_seq_print('|', 12);

        SEND_STRING(&s->sout, buffer); // PSOCK_SEND(&s->sout, (uint8_t *)buffer, strlen(buffer)) > Send data.
    }

    counter++; counter %= 2399; // icrease the counter, reset if == 2399

    #if (OAR_CONF_DEV)

        leds_single_off(LEDS_LED1);

    #endif // (OAR_CONF_DEV)
    
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

PROCESS_THREAD(oar_buoy_process, ev, data)
{
    PROCESS_BEGIN();

        PROCESS_NAME(webserver_process);
        process_start(&webserver_process, NULL);

        #if (OAR_CONF_DEV)

            leds_single_on(LEDS_LED2);
        
        #endif // (OAR_CONF_DEV)

        printf("\n");
        
        printf("[OAR] > "); console_seq_print('-', 20);
        printf("[OAR] > BUOY PROCESS STARTED\n");
        printf("[OAR] > "); console_seq_print('-', 20);

        // (doc) A process that has yielded can be polled by an external process or module by calling process_poll(). 
                // (doc) To poll a process declared with the variable test_proc, one can call process_poll(&test_proc);.
                // (doc) The polled process will be scheduled immediately, and a PROCESS_EVENT_POLL event will be delivered to it.
                
                process_poll(&oar_debug_process);

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
                
                #if (OAR_CONF_BUOY_FUNCTIONALITY)
                
                    // (doc) PROCESS_YIELD() will yield control back to the scheduler without expecting to be scheduled again shortly thereafter. 
                    // (doc) Instead, it will wait for an incoming event, similar to PROCESS_WAIT_EVENT_UNTIL(), but without a required condition argument. 
                    // (doc) A process that has yielded can be polled by an external process or module by calling process_poll(). 
                    // (doc) To poll a process declared with the variable test_proc, one can call process_poll(&test_proc);. 
                    // (doc) The polled process will be scheduled immediately, and a PROCESS_EVENT_POLL event will be delivered to it.
                    
                    // PROCESS_YIELD();
                
                 #endif // (OAR_CONF_BUOY_FUNCTIONALITY)

                
                
                
                // ================================================================================================================================================================
                // JSON ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                // ================================================================================================================================================================
                
                #if (OAR_CONF_JSON)

                    // ------------------------------------------------------------------------------------------------------------------------
                    // JSON /////////////////////////////////////////////////////////////////////////////////////////////////////////
                    // ------------------------------------------------------------------------------------------------------------------------

                    #if (OAR_CONF_JSON_TYPE == 0) // use the tiny json (./oar-json-tiny.h) [project-conf.h]
                        
                        char *oar_json_buf = (char *)malloc((OAR_CONF_JSON_BUF_SIZE+1)*sizeof(char)); // allocate OAR_CONF_JSON_BUF_SIZE + 1 character size (*+1 for '\0' character) in heap memory for storing oar_json_buf > char *oar_json_buf = (char *)heapmem_alloc((OAR_CONF_JSON_BUF_SIZE+1)*sizeof(char)); (for platform specific os/lib/heapmem.h)

                        if (oar_json_buf == NULL) // if heap memory couldn't be allocated for oar_json_buf...
                        {
                            printf("OUT OF HEAP MEMORY > CANNOT ALLOCATE (%u + 1) CHARACTERS FOR JSON\n", OAR_CONF_JSON_BUF_SIZE);
                            
                            free(oar_json_buf);   // release the memory allocated for encrypted_oar_json > heapmem_free(encrypted_oar_json); (for platform specific os/lib/heapmem.h)
                        }
                        else
                        {
                            oar_json_construct(oar_json_buf, counter % 23); // construct oar_json_buf (function found in ./oar_json_micro.h)
                            oar_json_print(oar_json_buf); // print oar_json_buf (function found in ./oar_json_micro.h)
                            
                            printf("\n"); printf("length of quantized json: %d\n", strlen(oar_json_buf));

                            counter++;
                            counter %= 2399;

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
                                    oar_crypt(encrypted_oar_json, oar_json_buf); // encrypt oar_json_buf and store it in encrypted_oar_json (function found in oar-crypt.h)
                                    
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
                                            oar_crypt(decrypted_oar_json, encrypted_oar_json); // decrypt encrypted_oar_json and store it in decrypted_oar_json (function found in oar-crypt.h)
    
                                            printf("%s\n", decrypted_oar_json); printf("\n"); 
                                            printf("length of decrypted: %d\n", strlen(decrypted_oar_json));

                                            free(encrypted_oar_json);   // release the memory allocated for encrypted_oar_json > heapmem_free(encrypted_oar_json); (for platform specific os/lib/heapmem.h)
                                            free(decrypted_oar_json);   // release the memory allocated for decrypted_oar_json > heapmem_free(decrypted_oar_json); (for platform specific os/lib/heapmem.h)
                                        }

                                    #endif // (OAR_CONF_CRYPT_DECRYPT)

                                }
                                
                            #endif // (OAR_CONF_CRYPT)

                            free(oar_json_buf); // release the memory allocated for oar_json_buf > heapmem_free(oar_json_buf); (for platform specific os/lib/heapmem.h)
                            
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
                                    oar_crypt(encrypted_oar_json, oar_json_extended_buf); // encrypt oar_json_extended_buf and store it in encrypted_oar_json (function found in oar-crypt.h)
                                    
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
                                            oar_crypt(decrypted_oar_json, encrypted_oar_json); // decrypt encrypted_oar_json and store it in decrypted_oar_json (function found in oar-crypt.h)
    
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
                                    oar_crypt(encrypted_oar_json, oar_json_compact_buf); // encrypt oar_json_compact_buf and store it in encrypted_oar_json (function found in oar-crypt.h)
                                    
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
                                            oar_crypt(decrypted_oar_json, encrypted_oar_json); // decrypt encrypted_oar_json and store it in decrypted_oar_json (function found in oar-crypt.h)
    
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
                                    oar_crypt(encrypted_oar_json, oar_json_micro_buf); // encrypt oar_json_micro_buf and store it in encrypted_oar_json (function found in oar-crypt.h)
                                    
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
                                            oar_crypt(decrypted_oar_json, encrypted_oar_json); // decrypt encrypted_oar_json and store it in decrypted_oar_json (function found in oar-crypt.h)
    
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
                                    oar_crypt(encrypted_oar_json, oar_json_tiny_buf); // encrypt oar_json_tiny_buf and store it in encrypted_oar_json (function found in oar-crypt.h)
                                    
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
                                            oar_crypt(decrypted_oar_json, encrypted_oar_json); // decrypt encrypted_oar_json and store it in decrypted_oar_json (function found in oar-crypt.h)
    
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