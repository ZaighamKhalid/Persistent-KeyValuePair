/**
* @file           UTIL_KVS.h
*
* @brief          Kev Value Storage - Public interface
*
* @author         Zaigham Khalid
*
* @riskClass      N/A
*
* @moduleID       N/A
*
* @modulePrefix   KVS
*
* @copyright      No CopyRight. Feel free to use (at your own risk)
*
***********************************************************************************************************************/
/**
* @addtogroup UTIL_FILEPARESER
* @{
* @file
*/

#ifndef __UTIL_KVS_H
#define __UTIL_KVS_H

#ifdef __cplusplus
extern "C" {
#endif

/******************************* SYSTEM INCLUDES ******************************/

/******************************* PROJECT INCLUDES *****************************/
#include "../KeyValueStore/UTIL_KVS.h"

/******************************* DRIVER INCLUDES ******************************/

/****************************** LIBRARY INCLUDES ******************************/

/************************* TYPEDEFS, STRUCTURES and UNIONS ********************/

typedef int KVScompare(const char *a, const char *b);

typedef const void KVSkey;

typedef void KVSvalue;

typedef struct {
    KVSkey *pKey;
    KVSvalue *pValue;
} KVSpair;

typedef struct KvsStore_s KVSstore;

/***************************** MACROS DEFINITON *******************************/
#define KVS_SPACE_INCREMENT 8

/************************* EXTERNAL FUNCTION PROTOTYPES ***********************/

KVSstore* KVS_Create(KVScompare *pCompare);
void      KVS_Destroy(KVSstore *pStore);
int       KVS_Put(KVSstore *pStore, KVSkey *pKey, void *pValue);
KVSvalue* KVS_Get(KVSstore *pStore, KVSkey *pKey);
void      KVS_Remove(KVSstore *pStore, KVSkey *pKey);
size_t    KVS_Length(KVSstore *pStore);
KVSpair*  KVS_Pair(KVSstore *pStore, size_t index);
void      KVS_CreatePair(KVSstore *pStore, KVSkey *pKey, KVSvalue *pValue);

#ifdef __cplusplus
}
#endif


#endif  /* __UTIL_KVS_H */
/** @} */
/****************** END OF FILE ***************************************************************************************/
