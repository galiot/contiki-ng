#include "oar-itoa.h"


const char *itoa_d(int input)
{
    int length = snprintf( NULL, 0, "%d", input );
    char* str = malloc( length + 1 );
    
    snprintf(str, length + 1, "%d", input );
    return str;
    
    // free(str);  
}

// int str_length(int input)
// {
//     int length = snprintf( NULL, 0, "%d", input );
//     return length;
// }