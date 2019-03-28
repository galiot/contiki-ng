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

// <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><
// <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><
// <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><
// <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><

#include "project-conf.h"           // for vscode intellisense (make recipe includes it either way)

// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

#include <stdio.h>                  // for prinntf()

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
















// |$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|
// |$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|



// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#if (OAR_DEBUG_ENERGEST)
    static unsigned long to_seconds(uint64_t time)
    {
        return (unsigned long)(time / ENERGEST_SECOND);
    }
#endif  /* OAR_DEBUG_ENERGEST */
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%



// |$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|
// |$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|$|
















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

AUTOSTART_PROCESSES(&oar_debug_process, &oar_dev_process);          

// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
















PROCESS_THREAD(oar_debug_process, ev, data)
{   
    
    #if !(OAR_DEBUG)

        // (doc) A process can be stopped in three ways:
        // (doc)    The process implicitly exits by allowing the PROCESS_END() statement to be reached and executed.
        // (doc)    The process explicitly exits by calling PROCESS_EXIT() in the PROCESS_THREAD body.
        // (doc)    Another process kills the process by calling process_exit().
        // (doc) After stopping a process, it can be restarted from the beginning by calling process_start().

        PROCESS_EXIT();

    #else      /* OAR_DEBUG */




        // ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
            
            static struct etimer debug_timer;                       // An event-timer variable. Note that this variable must be static in order to preserve the value across yielding.
            unsigned long int debug_system_time = clock_seconds();        

        // ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
        



        PROCESS_BEGIN();

            etimer_set(&debug_timer, CLOCK_SECOND * OAR_DEBUG_INTERVAL);        // Setup a periodic timer that expires after OAR_DEBUG_INTERVAL seconds (trigger this timer after these OAR_DEBUG_INTERVAL seconds have passed).
            
            while(1) {

                    printf("[%8lu] DEBUG \t > \t hello world \n", debug_system_time);




                    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
                    #if (OAR_DEBUG_ENERGEST)
                    
                        energest_flush();       // Update all energest times.

                        printf("\n");

                        printf("[%8lu] DEBUG > \t ENERGEST > \t CPU:            \t %4lu \n",    debug_system_time,
                                                                                                to_seconds(energest_type_time(ENERGEST_TYPE_CPU)));
                        printf("[%8lu] DEBUG > \t ENERGEST > \t LPM:            \t %4lu \n",    debug_system_time,
                                                                                                to_seconds(energest_type_time(ENERGEST_TYPE_LPM)));
                        printf("[%8lu] DEBUG > \t ENERGEST > \t DEEP LPM:       \t %4lu \n",    debug_system_time,
                                                                                                to_seconds(energest_type_time(ENERGEST_TYPE_DEEP_LPM)));
                        printf("[%8lu] DEBUG > \t ENERGEST > \t TOTAL TIME:     \t %4lu \n",    debug_system_time,
                                                                                                to_seconds(ENERGEST_GET_TOTAL_TIME()));

                        printf("------------------------------------------------------------------------ \n");

                        printf("[%8lu] DEBUG > \t ENERGEST > \t RADIO LISTEN:   \t %4lu \n",    debug_system_time,
                                                                                                to_seconds(energest_type_time(ENERGEST_TYPE_LISTEN)));
                        printf("[%8lu] DEBUG > \t ENERGEST > \t RADIO TRANSMIT: \t %4lu \n",    debug_system_time,
                                                                                                to_seconds(energest_type_time(ENERGEST_TYPE_TRANSMIT)));
                        printf("[%8lu] DEBUG > \t ENERGEST > \t RADIO OFF:      \t %4lu \n",    debug_system_time,
                                                                                                to_seconds(ENERGEST_GET_TOTAL_TIME()
                                                                                                - energest_type_time(ENERGEST_TYPE_TRANSMIT)
                                                                                                - energest_type_time(ENERGEST_TYPE_LISTEN)));
                        
                        printf("\n");

                    #endif  /* OAR_DEBUG_ENERGEST */                                                               
                    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% 




                    // <-%-><-%-><-%-><-%-><-%-><-%-><-%-><-%-><-%-><-%-><-%-><-%-><-%-><-%-><-%-><-%-><-%-><-%-><-%-><-%-><-%-><-%-><-%
                    #if (OAR_DEBUG_STATISTICS)
                    
                        printf("\n");

                        printf("[%8lu] DEBUG > \t   IP > \t       (ip.recv) %10lu > Number of received packets at the IP layer\n", debug_system_time, uip_stat.ip.recv);
                        printf("[%8lu] DEBUG > \t   IP > \t       (ip.sent) %10lu > Number of sent packets at the IP layer\n", debug_system_time, uip_stat.ip.sent);
                        printf("[%8lu] DEBUG > \t   IP > \t  (ip.forwarded) %10lu > Number of forwarded packets at the IP layer\n", debug_system_time, uip_stat.ip.forwarded);
                        printf("[%8lu] DEBUG > \t   IP > \t       (ip.drop) %10lu > Number of dropped packets at the IP layer\n", debug_system_time, uip_stat.ip.drop);
                        printf("[%8lu] DEBUG > \t   IP > \t     (ip.vhlerr) %10lu > Number of packets dropped due to wrong IP version or header length\n", debug_system_time, uip_stat.ip.vhlerr);
                        printf("[%8lu] DEBUG > \t   IP > \t   (ip.hblenerr) %10lu > Number of packets dropped due to wrong IP length, high byte\n", debug_system_time, uip_stat.ip.hblenerr);
                        printf("[%8lu] DEBUG > \t   IP > \t   (ip.lblenerr) %10lu > Number of packets dropped due to wrong IP length, low byte\n", debug_system_time, uip_stat.ip.lblenerr);
                        printf("[%8lu] DEBUG > \t   IP > \t    (ip.fragerr) %10lu > Number of packets dropped because they were IP fragments\n", debug_system_time, uip_stat.ip.fragerr);
                        printf("[%8lu] DEBUG > \t   IP > \t     (ip.chkerr) %10lu > Number of packets dropped due to IP checksum errors\n", debug_system_time, uip_stat.ip.chkerr);
                        printf("[%8lu] DEBUG > \t   IP > \t   (ip.protoerr) %10lu > Number of packets dropped because they were neither ICMP, UDP nor TCP\n", debug_system_time, uip_stat.ip.protoerr);
                        
                        printf("------------------------------------------------------------------------------------------------------------------------------------------------------\n");


                        printf("[%8lu] DEBUG > \t ICMP > \t     (icmp.recv) %10lu > Number of received ICMP packets\n", debug_system_time, uip_stat.icmp.recv);
                        printf("[%8lu] DEBUG > \t ICMP > \t     (icmp.sent) %10lu > Number of sent ICMP packets\n", debug_system_time, uip_stat.icmp.sent);
                        printf("[%8lu] DEBUG > \t ICMP > \t     (icmp.drop) %10lu > Number of dropped ICMP packets\n", debug_system_time, uip_stat.icmp.drop);
                        printf("[%8lu] DEBUG > \t ICMP > \t  (icmp.typeerr) %10lu > Number of ICMP packets with a wrong type\n", debug_system_time, uip_stat.icmp.typeerr);
                        printf("[%8lu] DEBUG > \t ICMP > \t   (icmp.chkerr) %10lu > Number of ICMP packets with a bad checksum\n", debug_system_time, uip_stat.icmp.chkerr);

                        printf("------------------------------------------------------------------------------------------------------------------------------------------------------\n");


                        // ()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()
                        #if UIP_TCP

                            printf("[%8lu] DEBUG > \t  TCP > \t      (tcp.recv) %10lu > Number of received TCP segments\n", debug_system_time, uip_stat.tcp.recv);
                            printf("[%8lu] DEBUG > \t  TCP > \t      (tcp.sent) %10lu > Number of sent TCP segments\n", debug_system_time, uip_stat.tcp.sent);
                            printf("[%8lu] DEBUG > \t  TCP > \t      (tcp.drop) %10lu > Number of dropped TCP segments\n", debug_system_time, uip_stat.tcp.drop);
                            printf("[%8lu] DEBUG > \t  TCP > \t    (tcp.chkerr) %10lu > Number of TCP segments with a bad checksum\n", debug_system_time, uip_stat.tcp.chkerr);
                            printf("[%8lu] DEBUG > \t  TCP > \t    (tcp.ackerr) %10lu > Number of TCP segments with a bad ACK number\n", debug_system_time, uip_stat.tcp.ackerr);
                            printf("[%8lu] DEBUG > \t  TCP > \t       (tcp.rst) %10lu > Number of received TCP RST (reset) segments\n", debug_system_time, uip_stat.tcp.rst);
                            printf("[%8lu] DEBUG > \t  TCP > \t    (tcp.rexmit) %10lu > Number of retransmitted TCP segments\n", debug_system_time, uip_stat.tcp.rexmit);
                            printf("[%8lu] DEBUG > \t  TCP > \t   (tcp.syndrop) %10lu > Number of dropped SYNs because too few connections were available\n", debug_system_time, uip_stat.tcp.syndrop);
                            printf("[%8lu] DEBUG > \t  TCP > \t    (tcp.synrst) %10lu > Number of SYNs for closed ports, triggering a RST\n", debug_system_time, uip_stat.tcp.synrst);

                            printf("------------------------------------------------------------------------------------------------------------------------------------------------------\n");
                        
                        #endif  /* UIP_TCP */
                        // ()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()


                        // ()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()
                        #if UIP_UDP

                            printf("[%8lu] DEBUG > \t  UDP > \t      (udp.drop) %10lu > Number of dropped UDP segments\n", debug_system_time, uip_stat.udp.drop);
                            printf("[%8lu] DEBUG > \t  UDP > \t      (udp.recv) %10lu > Number of received UDP segments\n", debug_system_time, uip_stat.udp.recv);
                            printf("[%8lu] DEBUG > \t  UDP > \t      (udp.sent) %10lu > Number of sent UDP segments\n", debug_system_time, uip_stat.udp.sent);
                            printf("[%8lu] DEBUG > \t  UDP > \t    (udp.chkerr) %10lu > Number of UDP segments with a bad checksum\n", debug_system_time, uip_stat.udp.chkerr);
    
                            printf("------------------------------------------------------------------------------------------------------------------------------------------------------\n");

                        #endif  /* UIP_UDP */
                        // ()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()

            
                        printf("[%8lu] DEBUG > \t  ND6 > \t      (nd6.drop) %10lu > Number of dropped ND6 packets\n", debug_system_time, uip_stat.nd6.drop);
                        printf("[%8lu] DEBUG > \t  ND6 > \t      (nd6.recv) %10lu > Number of dropped ND6 packets\n", debug_system_time, uip_stat.nd6.recv);
                        printf("[%8lu] DEBUG > \t  ND6 > \t      (nd6.sent) %10lu > Number of dropped ND6 packets\n", debug_system_time, uip_stat.nd6.sent);

                        printf("\n");

                    #endif      /* OAR_DEBUG_STATISTICS */
                    // <-%-><-%-><-%-><-%-><-%-><-%-><-%-><-%-><-%-><-%-><-%-><-%-><-%-><-%-><-%-><-%-><-%-><-%-><-%-><-%-><-%-><-%-><-%




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
                    
                    process_poll(&oar_dev_process);

                
                }

        PROCESS_END();
    }

#endif      /* OAR_DEBUG */
















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
        }
    
    #endif  /* OAR_DEV */