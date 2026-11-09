#include "KeyGenAlgoInterfaceEx.h"
#include "SecurityAlgorithm.h"

KEYGENALGO_API VKeyGenResultEx GenerateKeyEx(
    const unsigned char* iSeedArray,
    unsigned int iSeedArraySize,
    const unsigned int iSecurityLevel,
    const char* iVariant,
    unsigned char* ioKeyArray,
    unsigned int iKeyArraySize,
    unsigned int& oSize)
{
    oSize = 0;

    if (iSeedArray == nullptr || ioKeyArray == nullptr)
        return KGRE_UnspecifiedError;

    // Example: support only UDS security level 1 in this starter.
    if (iSecurityLevel != 1)
        return KGRE_SecurityLevelInvalid;

    // The demo algorithm returns one output byte per seed byte.
    if (iKeyArraySize < iSeedArraySize)
        return KGRE_BufferToSmall;

    (void)iVariant; // Use this to distinguish ECU variants if required.

    if (!GenerateSecurityKey(
            iSeedArray, iSeedArraySize,
            ioKeyArray, iKeyArraySize, oSize))
        return KGRE_UnspecifiedError;

    return KGRE_Ok;
}
