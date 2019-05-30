////////////////////////
// galiot (2018/2019) //
////////////////////////

// this algorithm was created for sdbm (a public-domain reimplementation of ndbm) database library. 
// it was found to do well in scrambling bits, causing better distribution of the keys and fewer splits. 
// it also happens to be a good general hashing function with good distribution. 
// the actual function is hash(i) = hash(i - 1) * 65599 + str[i]; 
// what is included below is the faster version used in gawk. 
// [there is even a faster, duff-device version] 
// the magic constant 65599 was picked out of thin air
// while experimenting with different constants, 
// and turns out to be a prime. 
//
// this is one of the algorithms used in berkeley db (see sleepycat) and elsewhere.
//
// static unsigned long
//     sdbm(str)
//     unsigned char *str;
//     {
//         unsigned long hash = 0;
//         int c;
//
//         while (c = *str++)
//             hash = c + (hash << 6) + (hash << 16) - hash;
//
//         return hash;
//     }
//
// original code by:    http://www.cse.yorku.ca/~oz/hash.html
// modified by:         galiot (2018/2019)

unsigned oar_sdbm(char *str)
{
    unsigned  hash = 0;
    int c;

    while ((c = *str++) != 0)
    {
        hash = c + (hash << 6) + (hash << 16) - hash;
    }

    return hash;
}

// NEED FOR MODIFICATION(s)
//
// Original function used long usnsigned for hash (and function return type).
// Changed to unsinged for memory preservation and cross-compatibility with:
//
// sdbm 1.2.0 (https://www.npmjs.com/package/sdbm) 
// by: sindresorhus (2019)
//
// Improved (made explicit) the condition for while loop to silence 
// "error: suggest parentheses around assignment used as truth value"
// Changed function type from static to global scope.








// #include <stdio.h>
// #include <string.h>
//
// int main()
// {
//     char test[32];
//
//     strcpy(test, "hello world");
//     printf("%u", oar_sdbm(test));
//
//     return 0;
// }