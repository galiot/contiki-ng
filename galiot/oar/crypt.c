#include <stdio.h>
#include <string.h>

void oar_crypt(char *input, char *output) 
{                           
    // char key[] = {OAR_CRYPT_KEY_1, OAR_CRYPT_KEY_2, OAR_CRYPT_KEY_3};   //Can be any chars, and any size array, original example: // char key[] = {'K', 'C', 'Q'};  
	
   
    char key[] = {'z'};



    int i;
	
    printf("char is: %c\n", (key[0]+200));
    
    for(i = 0; i < strlen(input); i++) 
    {
        output[i] = input[i] ^ (30+key[i % (sizeof(key)/sizeof(char))]);
	}

    output[strlen(input)] = '\0';           // output string needs to be explicitly ended for the encrypted string size to be equal to the unecrypted, reducing security (helps debugging though) 
}

int main()

{
    char input[100] = {"abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ.:\"{}"};
    char en[100];
    char de[100];

    printf("in: %s\n", input);
    printf("%lu\n", strlen(input));
    oar_crypt(input, en);
    printf("en: %s\n", en);
    printf("%lu\n", strlen(en));
    oar_crypt(en, de);
    printf("de: %s\n", de);
    printf("%lu\n", strlen(de));

}

