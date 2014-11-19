#ifndef _CACHE_H_
#define _CACHE_H_

#include <stdlib.h>
#include <stdint.h>

typedef uint8_t     Byte;
typedef unsigned    Address;

typedef enum {
    DirectMapped,
    FullyAssoc,
    SetAssoc
} CacheType;

typedef struct {
    Byte            validBit;
    int             addressTag;            
    Byte*           lineContent;
} CacheLine;

typedef struct {
    CacheLine   *cacheContent;
    CacheType   cacheType;
    int         blockNum;
    int         blockByteSize;
} Cache;

typedef enum {
    CM_Success,
    CM_NullPtr_Error
} ErrorCode;

ErrorCode   initDMCache(Cache *dmCache, int blockNum, int blockByteSize);
ErrorCode   initDMCacheL(Cache *dmCache);

inline int  addrIndex(Cache *dmCache, Address addr);
inline int  addrTag(Cache *dmCache, Address addr);

ErrorCode   readDMCache(Cache *dmCache, Address addr, Byte* mem);

#endif
