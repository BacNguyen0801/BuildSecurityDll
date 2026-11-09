#pragma once

/*
 * STARTER INTERFACE ONLY.
 *
 * Before using this DLL with CANoe, compare/replace this file with the exact
 * KeyGenAlgoInterfaceEx.h delivered with your installed CANoe 17 sample:
 *
 *   C:\Users\Public\Documents\Vector\CANoe\Sample Configurations 17.x.x\
 *   CAN\Diagnostics\UDSSystem\SecurityAccess\Sources\
 *   KeyGenDll_GenerateKeyEx\
 *
 * Vector's header is authoritative for ABI, enum values, export decoration,
 * calling convention and parameter types. Do not assume this starter header
 * is a substitute for the installed Vector header.
 */

#ifdef _WIN32
  #ifdef SECUREACCESSKEYS_EXPORTS
    #define KEYGENALGO_API extern "C" __declspec(dllexport)
  #else
    #define KEYGENALGO_API extern "C" __declspec(dllimport)
  #endif
#else
  #define KEYGENALGO_API extern "C"
#endif

enum VKeyGenResultEx
{
    KGRE_Ok = 0,
    KGRE_UnspecifiedError = -1,
    KGRE_SecurityLevelInvalid = -84,
    KGRE_BufferToSmall = -86
};

KEYGENALGO_API VKeyGenResultEx GenerateKeyEx(
    const unsigned char* iSeedArray,
    unsigned int iSeedArraySize,
    const unsigned int iSecurityLevel,
    const char* iVariant,
    unsigned char* ioKeyArray,
    unsigned int iKeyArraySize,
    unsigned int& oSize
);
