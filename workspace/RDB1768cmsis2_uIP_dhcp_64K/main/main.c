/*
 * Copyright (c) 2001, Adam Dunkels.
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
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *      This product includes software developed by Adam Dunkels.
 * 4. The name of the author may not be used to endorse or promote
 *    products derived from this software without specific prior
 *    written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * This file is part of the uIP TCP/IP stack.
 *
 * $Id: main.c,v 1.16 2006/06/11 21:55:03 adam Exp $
 *
 */

/**********************************************************************
 * Modifications by Code Red Technologies for RDB1768 development board
 **********************************************************************/


#include "LPC17xx.h"
#include <string.h>
#include "lpc17xx_emac.h"

#include "timer.h"
#include "uip.h"
#include "uip_arp.h"
#include "tapdev.h"

#if defined ( _RDB1768_ )
// Code Red - RDB1768 LCD library
#include "lcd.h"
#endif

struct uip_eth_addr mymac = { {MYMAC_1, MYMAC_2, MYMAC_3, MYMAC_4, MYMAC_5, MYMAC_6} } ;
char ipstring [20];

#define BUF ((struct uip_eth_hdr *)&uip_buf[0])

/*--------------------------- uip_log ---------------------------------*/

void uip_log(char *m)
{
  //printf("uIP log message: %s\n", m);
}

/*--------------------------- main ---------------------------------*/

int main(void)
{
	unsigned int i;
	uip_ipaddr_t ipaddr;	/* local IP address */
	struct timer periodic_timer, arp_timer;

#if defined ( _RDB1768_ )
// Code Red : RDB1768 LCD code
	// Initialize the ST7637 LCD Controller/driver for use
	LCDdriver_initialisation();

	// Reset the "terminal" window to be displayed on the RDB1768's LCD
	LCD_ResetTerminal(COLOR_YELLOW);

	LCD_PrintString2Terminal ("uIP TCP/IP Stack\n", LCD_TERMINAL_NoNL,COLOR_BLUE, COLOR_YELLOW);
	LCD_PrintString2Terminal ("Webserver\n", LCD_TERMINAL_NoNL,COLOR_BLUE, COLOR_YELLOW);
	LCD_PrintString2Terminal ("- Initializing\n", LCD_TERMINAL_NoNL,COLOR_BLUE, COLOR_YELLOW);
#endif

	// clock init
	clock_init();
	// two timers for tcp/ip
	timer_set(&periodic_timer, CLOCK_SECOND / 2); /* 0.5s */
	timer_set(&arp_timer, CLOCK_SECOND * 10);	/* 10s */
	
	// ethernet init
	tapdev_init();

	// Initialize the uIP TCP/IP stack.
	uip_init();

    uip_ipaddr(ipaddr, 0, 0, 0, 0);
    uip_sethostaddr(ipaddr);
    uip_ipaddr(ipaddr, 0, 0, 0, 0);
    uip_setnetmask(ipaddr);

	uip_setethaddr (mymac);

	// Start DHCP to get IP address
	dhcpc_init(&mymac,6 );

	 dhcpc_request();

	// Initialize the HTTP server, listen to port 80.
	httpd_init();

	while(1)
	{
 	/* receive packet and put in uip_buf */
		uip_len = tapdev_read(uip_buf);
    	if(uip_len > 0)		/* received packet */
    	{ 
      		if(BUF->type == htons(UIP_ETHTYPE_IP))	/* IP packet */
      		{
	      		uip_arp_ipin();	
	      		uip_input();
	      		/* If the above function invocation resulted in data that
	         		should be sent out on the network, the global variable
	         		uip_len is set to a value > 0. */
 
	      		if(uip_len > 0)
        		{
	      			uip_arp_out();
	        		tapdev_send(uip_buf,uip_len);
	      		}
      		}
	      	else if(BUF->type == htons(UIP_ETHTYPE_ARP))	/*ARP packet */
	      	{
	        	uip_arp_arpin();
		      	/* If the above function invocation resulted in data that
		         	should be sent out on the network, the global variable
		         	uip_len is set to a value > 0. */
		      	if(uip_len > 0)
	        	{
		        	tapdev_send(uip_buf,uip_len);	/* ARP ack*/
		      	}
	      	}
    	}
    	else if(timer_expired(&periodic_timer))	/* no packet but periodic_timer time out (0.5s)*/
    	{
      		timer_reset(&periodic_timer);
	  
      		for(i = 0; i < UIP_CONNS; i++)
      		{
      			uip_periodic(i);
		        /* If the above function invocation resulted in data that
		           should be sent out on the network, the global variable
		           uip_len is set to a value > 0. */
		        if(uip_len > 0)
		        {
		          uip_arp_out();
		          tapdev_send(uip_buf,uip_len);
		        }
      		}
#if UIP_UDP
			for(i = 0; i < UIP_UDP_CONNS; i++) {
				uip_udp_periodic(i);
				/* If the above function invocation resulted in data that
				   should be sent out on the network, the global variable
				   uip_len is set to a value > 0. */
				if(uip_len > 0) {
				  uip_arp_out();
// CodeRed - mod'ed to compile
// 			  tapdev_send();
				  tapdev_send(uip_buf,uip_len);
				}
			}
#endif /* UIP_UDP */
	     	/* Call the ARP timer function every 10 seconds. */
			if(timer_expired(&arp_timer))
			{
				timer_reset(&arp_timer);
				uip_arp_timer();
			}
    	}
	}
}
