
#include <stdio.h>
#include "cache.h"

ErrorCode initDMCacheL(Cache *dmCache) {
    int i;

    dmCache->cacheContent = (CacheLine *) 
        malloc(sizeof(CacheLine) * dmCache->blockNum);

    for (i = 0; i < dmCache->blockNum; i++) {
        CacheLine* cacheLine = &dmCache->cacheContent[i]; 
        cacheLine->validBit     = 0;
        cacheLine->addressTag   = 0;
        cacheLine->lineContent  = (Byte*) 
            malloc(sizeof(Byte) * dmCache->blockByteSize);
    }

    return CM_Success;
}

ErrorCode initDMCache(Cache *dmCache, int blockNum, int blockByteSize) {
    if (dmCache == NULL) 
        return CM_NullPtr_Error;

    dmCache->cacheType      = DirectMapped;
    dmCache->blockNum       = blockNum;
    dmCache->blockByteSize  = blockByteSize;
        
    initDMCacheL(dmCache); 

    return CM_Success;
}

int addrIndex(Cache *dmCache, Address addr) {
    int idxMask = ((dmCache->blockNum)-1) << 2;
    int idx     = (idxMask & addr) >> 2;
    return idx;
}

int addrTag(Cache *dmCache, Address addr) {
    int idxMask = ((dmCache->blockNum)-1)<<2;
    int tagMask = ~(idxMask | 3);

    // silly code:
    int i;
    int tag     = (tagMask & addr); 
    for (i = 0; i < 32; i++) 
        if (!(tag & 1))
            tag >>= 1;
    return tag;
}

ErrorCode readDMCache(Cache *dmCache, Address addr, Byte* mem) {
    int idx = addrIndex(dmCache, addr);
    int tag = addrTag(dmCache, addr);

    CacheLine *line = &dmCache->cacheContent[idx];
    if (!line->validBit || tag != line->addressTag) { 
        printf("addr: %x idx: %d tag: %d miss\n", addr, idx, tag);
        
        // will be replaced by a function
        line->addressTag = tag;
        line->validBit   = 1;
    }
    else 
        printf("addr: %x idx: %d tag: %d hit\n", addr, idx, tag);

    return CM_Success;
}
