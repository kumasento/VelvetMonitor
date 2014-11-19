#include <stdio.h>
#include <stdlib.h>

#include "cache.h"

#define MAXSIZE     2048
#define BYTEMASK    255

int main() {
    Cache *cache = (Cache *) malloc(sizeof(Cache));
    
    int blockNum        = 1024;
    int blockByteSize   = 1;
    initDMCache(cache, blockNum, blockByteSize);

    uint8_t srcData[MAXSIZE];
    int i, j;
    for (i = 0; i < MAXSIZE; i++) 
        srcData[i] = (uint8_t) (i & BYTEMASK);
    
    for (j = 0; j < 10; j++)
        for (i = 0; i < 10; i++) 
            readDMCache(cache, (i<<2), srcData);

    return 0;
}
