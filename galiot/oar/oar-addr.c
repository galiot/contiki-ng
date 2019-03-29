// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

#include "oar-addr.h"


void oar_ipaddr_to_str(char *output, const uip_ipaddr_t *ipaddr) 
{
    char buf[UIPLIB_IPV6_MAX_STR_LEN];
    uiplib_ipaddr_snprint(buf, sizeof(buf), ipaddr);

    strcpy(output, buf);
}

void oar_lladdr_to_str(char *output, const linkaddr_t *lladdr) 
{
    char buf[5]; 
    if (lladdr == NULL)
    {
        strcpy(output, "(NULL LL addr");
    }
    else
    {
        unsigned int i;
        for (i = 0; i < LINKADDR_SIZE; i++)
        {
            if (i > 0 && i % 2 == 0)
            {
                strcat(output, ".");
            }
            
            
            sprintf(buf, "%02x", lladdr->u8[i]);
            strcat(output, buf);
        }
    }
}