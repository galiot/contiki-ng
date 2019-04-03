#include <stdio.h>
#include <string.h>

#include "project-conf.h"   // provides the key, for example {'K', 'C', 'Q'}

/* **********************************************************************************************************************************************************
 * XOR encryption (or Exclusive-OR encryption) is a common method of encrypting text into a format that cannot be trivially cracked by the average person.  * 
 * XOR encryption is great for storing things like game save data, and other data types that are stored locally on a users computer,                        *
 * that while not a big deal if they are tampered with, you would like to deter people from doing so.                                                       *
 * XOR encryption is also used often as a part of more complex encryption algorithms.                                                                       *
 *                                                                                                                                                          *
 * based on code written by @kylewbanks (Oct 10, 2013).                                                                                                                  *
 * **********************************************************************************************************************************************************/

void oar_crypt(char *input, char *output) 
{                           
    // char key[] = {OAR_CRYPT_KEY_1, OAR_CRYPT_KEY_2, OAR_CRYPT_KEY_3};   //Can be any chars, and any size array, original example: // char key[] = {'K', 'C', 'Q'};  
	
    char key[] = {'K', 'C', 'Q'};  
    int i;
	
    for(i = 0; i < strlen(input); i++) 
    {
		output[i] = input[i] ^ key[i % (sizeof(key)/sizeof(char))];
	}

    output[strlen(input)] = '\0';           // output string needs to be explicitly ended for the encrypted string size to be equal to the unecrypted, reducing security (helps debugging though) 
}