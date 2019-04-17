////////////////////////
// galiot (2018/2019) //
////////////////////////

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
 */

/**
 * \file
 *         A simple web server forwarding page generation to a protothread
 * \author
 *         Adam Dunkels <adam@sics.se>
 *         Niclas Finne <nfi@sics.se>
 *         Joakim Eriksson <joakime@sics.se>
 */

// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// MODIFIED BY galiot (2018/2019) ////////////////////////////////////////////////
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// BASED ON /examples/rpl-border-router/http-simple.c ////////////////////////////
// TAKING INTO CONSIDERATION CODE BY: Agus Kurniawan (2018) "Practical Contiki-NG"
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

#include "contiki.h"
#include "contiki-net.h"

#include <stdio.h>
#include <string.h>

#include "httpd-simple.h"
#define webserver_log_file(...)
#define webserver_log(...)

#ifndef WEBSERVER_CONF_CFS_CONNS
#define CONNS UIP_TCP_CONNS
#else /* WEBSERVER_CONF_CFS_CONNS */
#define CONNS WEBSERVER_CONF_CFS_CONNS
#endif /* WEBSERVER_CONF_CFS_CONNS */

//   URLCONV: URL to filename conversion 
// - prepends wwwroot prefix, 
// - normalizes path by removing "/./",
// - interprets "/../" and calculates path accordingly
// - resulting path is always absolute
// - replaces "%AB" notation with characters
// - strips "#fragment" and "?query" from end
// - replaces multiple slashes with a single one
// - rejects non-ASCII characters

#ifndef WEBSERVER_CONF_CFS_URLCONV
#define URLCONV 0                               
#else /* WEBSERVER_CONF_CFS_URLCONV */
#define URLCONV WEBSERVER_CONF_CFS_URLCONV
#endif /* WEBSERVER_CONF_CFS_URLCONV */

#define STATE_WAITING 0
#define STATE_OUTPUT  1

MEMB(conns, struct httpd_state, CONNS);

#define ISO_nl      0x0a
#define ISO_space   0x20
#define ISO_period  0x2e
#define ISO_slash   0x2f

int uri = 0;

// $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

static const char *NOT_FOUND = "<html><body bgcolor=\"white\"><center><h1>404 - file not found</h1></center></body></html>";

// $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

static PT_THREAD(send_string(struct httpd_state *s, const char *str))
{
    PSOCK_BEGIN(&s->sout);

    // PSOCK_SEND(&s->sout, (uint8_t *)str, strlen(str))
    SEND_STRING(&s->sout, str);

    PSOCK_END(&s->sout);
}

// $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

const char http_content_type_html[] = "Content-type: text/html\r\n\r\n";            // not really needed, as our server services only packets with Content-type: application/json or 200/404 messages
const char http_content_type_json[] = "Content-type: application/json\r\n\r\n";

// this process always sends two headers, 
// one with 200 OK/404 NOT FOUND and 
// one that declares the content type as application/json

static PT_THREAD(send_headers(struct httpd_state *s, const char *statushdr))
{
    // char *ptr;

    PSOCK_BEGIN(&s->sout);

    /****************************************************************/
    /*                                                              */
    /*  ptr = strrchr(s->filename, ISO_period);                     */
    /*                                                              */
    /*  if(ptr == NULL)                                             */
    /*  {                                                           */
    /*      s->ptr = http_content_type_plain;                       */
    /*  }                                                           */
    /*  else                                                        */
    /*  {                                                           */
    /*      if(strcmp(http_html, ptr) == 0)                         */
    /*      {                                                       */
    /*          s->ptr = http_content_type_html;                    */
    /*      }                                                       */
    /*      else                                                    */
    /*      {                                                       */
    /*          if(strcmp(http_css, ptr) == 0)                      */
    /*          {                                                   */
    /*              s->ptr = http_content_type_css;                 */
    /*          }                                                   */
    /*          else                                                */
    /*          {                                                   */
    /*              if(strcmp(http_png, ptr) == 0)                  */
    /*              {                                               */
    /*                  s->ptr = http_content_type_png;             */
    /*              }                                               */
    /*              else                                            */
    /*              {                                               */
    /*                  if(strcmp(http_gif, ptr) == 0)              */
    /*                  {                                           */
    /*                      s->ptr = http_content_type_gif;         */
    /*                  }                                           */
    /*                  else                                        */
    /*                  {                                           */
    /*                      if(strcmp(http_jpg, ptr) == 0)          */
    /*                      {                                       */
    /*                          s->ptr = http_content_type_jpg;     */    
    /*                      }                                       */
    /*                      else                                    */
    /*                      {                                       */                                
    /*                          s->ptr = http_content_type_binary;  */      
    /*                      }                                       */
    /*                  }                                           */
    /*              }                                               */
    /*          }                                                   */
    /*      }                                                       */
    /*  }                                                           */
    /*                                                              */
    /*  SEND_STRING(&s->sout, s->ptr);                              */
    /*                                                              */
    /****************************************************************/             
    
    // in case a packet with a 200 OK        header needs to be sent (in this case, statusdr <-- http_header_200[] = {"HTTP/1.0 404 Not found\r\nServer: moor\r\nConnection: close\r\n"})
    // in case a packet with a 404 NOT FOUND header needs to be sent (in this case, statusdr <-- http_header_200[] = {"HTTP/1.0 200 OK\r\nServer: moor\r\nConnection: close\r\n"})
    SEND_STRING(&s->sout, statushdr);   
                                        
    // the header content type application/json is sent
    SEND_STRING(&s->sout, http_content_type_json);

    PSOCK_END(&s->sout);
}

// $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

const char http_header_200[] = "HTTP/1.0 200 OK\r\nServer: moor\r\nConnection: close\r\n";
const char http_header_404[] = "HTTP/1.0 404 Not found\r\nServer: moor\r\nConnection: close\r\n";

// $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

// -------------------------------------------------------------------------------------------------
// this process gets the "generate_routes" process from ./oar.c and:
//
// sets the *s.string (s is a pointer to a struct http_state) to NULL
// populates the *s.string with the binary represantation of buff (./oar.c), our message (json)
// if it can't find the generate_routes message, sends a header http_header_404 (see above)
// else it halts until the send_headrs thread sent the http_header_200 header

// checks if the struct http_state s is allocated (otherwise the pointer to it *s would be NULL)
// -------------------------------------------------------------------------------------------------

static PT_THREAD(handle_output(struct httpd_state *s))
{
    PT_BEGIN(&s->outputpt);

        s->script = NULL;
        s->script = httpd_simple_get_script(&s->filename[1]); // (return generate_routes) [./oar.c]
        
        if(s->script == NULL) 
        {
                strncpy(s->filename, "/notfound.html", sizeof(s->filename));

                PT_WAIT_THREAD(&s->outputpt, send_headers(s, http_header_404));
                PT_WAIT_THREAD(&s->outputpt, send_string(s, NOT_FOUND));
                
                uip_close();
                
                webserver_log_file(&uip_conn->ripaddr, "404 - not found");
                
                PT_EXIT(&s->outputpt);
        } 
        else 
        {
                PT_WAIT_THREAD(&s->outputpt, send_headers(s, http_header_200));
                PT_WAIT_THREAD(&s->outputpt, s->script(s));
        }
        
        s->script = NULL;
        
        PSOCK_CLOSE(&s->sout);

    PT_END(&s->outputpt);
}

// $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

// -------------------------------------------------------------------------------------------------
// this process reads the GET message that tis received by the mote.
// actually, it just reads the first part "GET /endpoint " and stores this endpoint in *s.filename
//
// usally, a GET message will ask for a file, for exapmple "GET /index.html "
// so this function makes sure that the *s.filename will contain afterwards the "index.html" string
//
// this is crucial for handling output, as we have to make sure that the file requested
// is actually found - an 404 NOT FOUND header should be sent otherwise
// -------------------------------------------------------------------------------------------------

const char http_get[] = "GET ";

// const char http_index_html[] = "/index.html"; 

const char http_index_html[] = "/"; // our backend will send GETs to /

// <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
// ENDPOINTS ////////////////////////////////////////////////////////////////////////////////////////
// <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

// const char http_endpoint_01[] = "/1" ;
// const char http_endpoint_02[] = "/2" ;
// const char http_endpoint_03[] = "/3" ;
// const char http_endpoint_04[] = "/4" ;
// const char http_endpoint_05[] = "/5" ;
// const char http_endpoint_06[] = "/6" ;
// const char http_endpoint_07[] = "/7" ;
// const char http_endpoint_08[] = "/8" ;
// const char http_endpoint_09[] = "/9" ;
// const char http_endpoint_10[] = "/10";
// const char http_endpoint_11[] = "/11";
// const char http_endpoint_12[] = "/12";
// const char http_endpoint_13[] = "/13";
// const char http_endpoint_14[] = "/14";
// const char http_endpoint_15[] = "/15";
// const char http_endpoint_16[] = "/16";
// const char http_endpoint_17[] = "/17";
// const char http_endpoint_18[] = "/18";
// const char http_endpoint_19[] = "/19";
// const char http_endpoint_20[] = "/20";
// const char http_endpoint_21[] = "/21";
// const char http_endpoint_22[] = "/22";

static PT_THREAD(handle_input(struct httpd_state *s))
{
    PSOCK_BEGIN(&s->sin); // Start the protosocket protothread in a function.
    
    PSOCK_READTO(&s->sin, ISO_space); // read date up to first ISO_space

    if(strncmp(s->inputbuf, http_get, 4) != 0)  // if not the next 4 characters are not "GET "... (notice the space after the GET) 
    {
        PSOCK_CLOSE_EXIT(&s->sin); // close a protosocket and exit the protosocket's protothread.
    }
    
    PSOCK_READTO(&s->sin, ISO_space); // move to the next ISO_space

    if(s->inputbuf[0] != ISO_slash) // if not an ISO_slash is not the first character received... (so the date received should begin with "GET /endpoint/ ...")
    {
        PSOCK_CLOSE_EXIT(&s->sin); // close a protosocket and exit the protosocket's protothread.
    }

    #if URLCONV
    
        s->inputbuf[PSOCK_DATALEN(&s->sin) - 1] = 0;
        urlconv_tofilename(s->filename, s->inputbuf, sizeof(s->filename));

    #else /* URLCONV */

        printf("\n");
        printf("[OAR] > [NUKE] > </></></></></></></></></></></></></></></></></></></></></>< \n");
        printf("[OAR] > [NUKE] > GET %.3s ::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n", s->inputbuf);
        printf("[OAR] > [NUKE] > </></></></></></></></></></></></></></></></></></></></></>< \n");
        printf("[OAR] > [NUKE] > URI[0]: %c ::::::::::::::::::::::::::::::::::::::::::::::::::::::\n", s->inputbuf[0]);
        printf("[OAR] > [NUKE] > URI[1]: %c ::::::::::::::::::::::::::::::::::::::::::::::::::::::\n", s->inputbuf[1]);
        printf("[OAR] > [NUKE] > URI[2]: %c ::::::::::::::::::::::::::::::::::::::::::::::::::::::\n", s->inputbuf[2]);
        printf("[OAR] > [NUKE] > </></></></></></></></></></></></></></></></></></></></></>< \n");

        if (s->inputbuf[1] != ISO_space) { uri = 0; uri += ( (int) s->inputbuf[1] - '0'); }
        if (s->inputbuf[2] != ISO_space) { uri = 0; uri += (((int) s->inputbuf[1] - '0') * 10) + ((int) s->inputbuf[2] - '0'); }

        if (uri < 0) { uri = 0; } // in case client sends 'GET /' then ((int) (' ' - '0') == -124)

        // if (strncmp(s->inputbuf, http_endpoint_01, (sizeof(http_endpoint_01) - 1) == 0)) { printf("[OAR] > JSON %u", 1 ); }
        // if (strncmp(s->inputbuf, http_endpoint_02, (sizeof(http_endpoint_02) - 1) == 0)) { printf("[OAR] > JSON %u", 2 ); }
        // if (strncmp(s->inputbuf, http_endpoint_03, (sizeof(http_endpoint_03) - 1) == 0)) { printf("[OAR] > JSON %u", 3 ); }
        // if (strncmp(s->inputbuf, http_endpoint_04, (sizeof(http_endpoint_04) - 1) == 0)) { printf("[OAR] > JSON %u", 4 ); }
        // if (strncmp(s->inputbuf, http_endpoint_05, (sizeof(http_endpoint_05) - 1) == 0)) { printf("[OAR] > JSON %u", 5 ); }
        // if (strncmp(s->inputbuf, http_endpoint_06, (sizeof(http_endpoint_06) - 1) == 0)) { printf("[OAR] > JSON %u", 6 ); }
        // if (strncmp(s->inputbuf, http_endpoint_07, (sizeof(http_endpoint_07) - 1) == 0)) { printf("[OAR] > JSON %u", 7 ); }
        // if (strncmp(s->inputbuf, http_endpoint_08, (sizeof(http_endpoint_08) - 1) == 0)) { printf("[OAR] > JSON %u", 8 ); }
        // if (strncmp(s->inputbuf, http_endpoint_09, (sizeof(http_endpoint_09) - 1) == 0)) { printf("[OAR] > JSON %u", 9 ); }
        // if (strncmp(s->inputbuf, http_endpoint_10, (sizeof(http_endpoint_10) - 1) == 0)) { printf("[OAR] > JSON %u", 10); }
        // if (strncmp(s->inputbuf, http_endpoint_11, (sizeof(http_endpoint_11) - 1) == 0)) { printf("[OAR] > JSON %u", 11); }
        // if (strncmp(s->inputbuf, http_endpoint_12, (sizeof(http_endpoint_12) - 1) == 0)) { printf("[OAR] > JSON %u", 12); }
        // if (strncmp(s->inputbuf, http_endpoint_13, (sizeof(http_endpoint_13) - 1) == 0)) { printf("[OAR] > JSON %u", 13); }
        // if (strncmp(s->inputbuf, http_endpoint_14, (sizeof(http_endpoint_14) - 1) == 0)) { printf("[OAR] > JSON %u", 14); }
        // if (strncmp(s->inputbuf, http_endpoint_15, (sizeof(http_endpoint_15) - 1) == 0)) { printf("[OAR] > JSON %u", 15); }
        // if (strncmp(s->inputbuf, http_endpoint_16, (sizeof(http_endpoint_16) - 1) == 0)) { printf("[OAR] > JSON %u", 16); }
        // if (strncmp(s->inputbuf, http_endpoint_17, (sizeof(http_endpoint_17) - 1) == 0)) { printf("[OAR] > JSON %u", 17); }
        // if (strncmp(s->inputbuf, http_endpoint_18, (sizeof(http_endpoint_18) - 1) == 0)) { printf("[OAR] > JSON %u", 18); }
        // if (strncmp(s->inputbuf, http_endpoint_19, (sizeof(http_endpoint_19) - 1) == 0)) { printf("[OAR] > JSON %u", 19); }
        // if (strncmp(s->inputbuf, http_endpoint_20, (sizeof(http_endpoint_20) - 1) == 0)) { printf("[OAR] > JSON %u", 20); }
        // if (strncmp(s->inputbuf, http_endpoint_20, (sizeof(http_endpoint_21) - 1) == 0)) { printf("[OAR] > JSON %u", 21); }
        // if (strncmp(s->inputbuf, http_endpoint_20, (sizeof(http_endpoint_22) - 1) == 0)) { printf("[OAR] > JSON %u", 22); }
        
        if(s->inputbuf[1] == ISO_space) // if the second character after the second ISO_space is ISO_space (so the data received is "GET / ...")
        {
            strncpy(s->filename, http_index_html, sizeof(s->filename)); // copy "/" to *s.filename
        } 
        else // if the second character after the second ISO_space is NOT ISO_space...
        {
            s->inputbuf[PSOCK_DATALEN(&s->sin) - 1] = 0; // get to the end of the data until the second ISO_space (to index the length of *s.sin - 1, so to the end of  "GET /endpoint/ ")
            strncpy(s->filename, s->inputbuf, sizeof(s->filename)); // and don't just copy the http_index_html (a "/"), but copy the whole "/endpoint/")
        }

    #endif /* URLCONV */

    webserver_log_file(&uip_conn->ripaddr, s->filename);

    s->state = STATE_OUTPUT;

    while(1) 
    {
        PSOCK_READTO(&s->sin, ISO_nl); // our json will have no ISO_nl (new line) characters, so don't take any action

        #if 0
        
            if(strncmp(s->inputbuf, http_referer, 8) == 0) 
            {
                s->inputbuf[PSOCK_DATALEN(&s->sin) - 2] = 0;
                webserver_log(s->inputbuf);
            }
        
        #endif
    }

    

    PSOCK_END(&s->sin); // Start the protosocket protothread in a function.
}

// $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

static void handle_connection(struct httpd_state *s)
{
    handle_input(s);

    if(s->state == STATE_OUTPUT) 
    {
        handle_output(s);
    }
}

// $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

//  struct httpd_state;
//  typedef char (*httpd_simple_script_t)   (struct httpd_state *s);

//  struct httpd_state 
//  {
//      struct timer timer;
//      struct psock sin, sout;
//      struct pt outputpt;
//      char inputbuf[HTTPD_PATHLEN + 24];
//      //  char outputbuf[UIP_TCP_MSS];
//      char filename[HTTPD_PATHLEN];
//      httpd_simple_script_t script;
//      char state;
//  };

void httpd_appcall(void *state)
{
    struct httpd_state *s = (struct httpd_state *)state;

    if(uip_closed() || uip_aborted() || uip_timedout()) 
    {
            if(s != NULL) 
            {
                s->script = NULL;
                memb_free(&conns, s);
            }
    } 
    else 
    {
        if(uip_connected()) 
        {
            s = (struct httpd_state *)memb_alloc(&conns);

            if(s == NULL) 
            {
                uip_abort();
                webserver_log_file(&uip_conn->ripaddr, "reset (no memory block)");
                return;
            }
            
            tcp_markconn(uip_conn, s);

            PSOCK_INIT(&s->sin, (uint8_t *)s->inputbuf, sizeof(s->inputbuf) - 1);
            PSOCK_INIT(&s->sout, (uint8_t *)s->inputbuf, sizeof(s->inputbuf) - 1);

            PT_INIT(&s->outputpt);

            s->script = NULL;
            s->state = STATE_WAITING;

            timer_set(&s->timer, CLOCK_SECOND * 10);
            
            handle_connection(s);
        } 
        else 
        {
            if(s != NULL)
            {
                if(uip_poll()) 
                {
                    if(timer_expired(&s->timer)) 
                    {
                        uip_abort();
                        s->script = NULL;
                        memb_free(&conns, s);
                        webserver_log_file(&uip_conn->ripaddr, "reset (timeout)");
                    }
                } 
                else 
                {
                    timer_restart(&s->timer);
                }
            
                handle_connection(s);
            } 
            else 
            {
                uip_abort();
            }
        }    
    }
}

// $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

void httpd_init(void)
{

    tcp_listen(UIP_HTONS(80));
    
    memb_init(&conns);

    #if URLCONV

        urlconv_init();

    #endif /* URLCONV */
}
