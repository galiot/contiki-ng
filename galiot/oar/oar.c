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

#include "project-conf.h"       // for vscode intellisense

#include "contiki.h"            /* Main include file for OS-specific modules. */
#include <stdio.h>              /* For printf() */



/*---------------------------------------------------------------------------*/

PROCESS(oar_debug_process, "oar debug process");
AUTOSTART_PROCESSES(&oar_debug_process);

/*---------------------------------------------------------------------------*/

PROCESS_THREAD(oar_debug_process, ev, data)
{
    /*  An event-timer variable. Note that this variable must be static
        in order to preserve the value across yielding. */
    static struct etimer debug_timer;

    PROCESS_BEGIN();

    /*<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><*/
    /*<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><*/
    /*<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><*/

    /*  Setup a periodic timer that expires after 10 seconds.   */
    etimer_set(&debug_timer, CLOCK_SECOND * OAR_DEBUG_INTERVAL);      /*  Trigger a timer after 10 seconds.   */
    
    /*<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><*/
    /*<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><*/
    /*<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><*/

    while(1) {
        printf("Hello, world\n");

        /*  Wait for the periodic timer to expire and then restart the timer.   */
        PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&debug_timer));
        etimer_reset(&debug_timer);
    }

    PROCESS_END();
}

/*---------------------------------------------------------------------------*/