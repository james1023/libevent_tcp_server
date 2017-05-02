#ifndef IBASE_H
#define IBASE_H

#include "i_base_c.h"
#include <memory.h>


#ifdef __cplusplus
extern "C" {
#endif // __cplusplus 

typedef struct _BOMID {
    unsigned long  Data1;
    unsigned short Data2;
    unsigned short Data3;
    unsigned char Data4[8];
} BOMID;

#define REFBOMID const BOMID &

inline int IsEqualBOMID(REFBOMID rguid1, REFBOMID rguid2)
{
	return !memcmp(&rguid1, &rguid2, sizeof(BOMID));
}

class IBase
{
public:
	virtual BASE_ERR QueryInterface(__b_in REFBOMID riid, __b_out void **ppv) = 0;
	virtual void Release() = 0;
};


#ifdef __cplusplus
}
#endif // __cplusplus

#endif	// IBASE_H
