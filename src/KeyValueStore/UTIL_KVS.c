/**
* @file           UTIL_KVS.c
*
* @brief          Kev Value Storage - Implementation
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


/****************************** SYSTEM INCLUDES *******************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/****************************** PRIVATE INCLUDES ******************************/
#include "UTIL_KVS.h"
/******************************* PROJECT INCLUDES *****************************/

/******************************* DRIVER INCLUDES ******************************/

/******************************* LIBRARY INCLUDES *****************************/

/******************************** LOCAL DATA **********************************/

struct KvsStore_s
{
   KVSpair *pairs;
   KVScompare *compare;
   size_t length;
   size_t space;
};

static const size_t KVS_pair_size = sizeof(KVSpair);

static const size_t KVS_store_size = sizeof(KVSstore);

/******************************** LOCAL VARIABLES *****************************/



/**************************** LOCAL FUNCTION PROTOTYPES ***********************/

static void     KVS_RemovePair(KVSstore *pStore, KVSpair *pair);
static int      KVS_ComparePointers(const char *a, const char *b);
static KVSpair* KVS_Search(KVSstore *pStore, KVSkey *pKey, int exact);
static KVSpair* KVS_get_pair(KVSstore *pStore, KVSkey *pKey);
static void     KVS_AbortIfNull(void *pPointer, const char *pMessage);
static void     KVS_ResizePairs(KVSstore *pStore, size_t amount);
static size_t   KVS_GetPairIndex(KVSstore *pStore, KVSpair *pair);
static size_t   KVS_GetBytesFromPair(KVSstore *pStore, KVSpair *pair);

/************************* PUBLIC FUNCTION IMPLEMENTATION *********************/



/**
*
* @brief          Create a new key-value store.
*
* @param[in]      compare    - A function to compare keys. If the store will only contain string keys,
                               use strcmp, or use NULL for the default behavior of comparing memory
                               addresses, or use a custom function matching the signature of strcmp.
*
* @retval         A pointer to the store.
*
*
* @preConditions  NA
* @criticalRes    NA
* @faultHandling  NA
* @varInit        NA
* @selfDiag       NA
* @memory         NA
* @boundary       NA
*
******************************************************************************/
KVSstore *KVS_Create(KVScompare compare)
{
   KVSstore *pStore = malloc(KVS_store_size);
   KVS_AbortIfNull(pStore, "out of memory");
   pStore->pairs = NULL;
   pStore->length = 0;
   pStore->space = 0;
   if (compare)
   {
      pStore->compare = compare;
   }
   else
   {
      pStore->compare = KVS_ComparePointers;
   }
   KVS_ResizePairs(pStore, 0);
   return pStore;
}

/**
*
* @brief          Destroy a key-value store.
*
* @param[in]      pStore   - A pointer to the store.
*
* @retval         None
*
*
* @preConditions  NA
* @criticalRes    NA
* @faultHandling  NA
* @varInit        NA
* @selfDiag       NA
* @memory         NA
* @boundary       NA
*
******************************************************************************/
void KVS_Destroy(KVSstore *pStore)
{
    if (!pStore)
    {
        return;
    }
    if (pStore->pairs)
    {
        free(pStore->pairs);
    }
    free(pStore);
}

/**
*
* @brief          Sets a value.
*
* @param[in]      pStore   - A pointer to the store.
* @param[in]      pkey     - identification key
* @param[in]      pValue   - value to be associated with the key
*
* @retval         None
*
*
* @preConditions  NA
* @criticalRes    NA
* @faultHandling  NA
* @varInit        NA
* @selfDiag       NA
* @memory         NA
* @boundary       NA
*
******************************************************************************/
int KVS_Put(KVSstore *pStore, KVSkey *pKey, void *pValue)
{
   int retVal = 0;

   KVSpair *pair = KVS_get_pair(pStore, pKey);
   if (pair)
   {
      pair->pValue = pValue;
   }
   else
   {
      retVal = -1;
   }

   return retVal;
}

/**
*
* @brief          Retrieve a value.
*
* @param[in]      pStore   - A pointer to the store.
* @param[in]      pKey     - A key used to retrieve the value.
*
* @retval         None
*
*
* @preConditions  NA
* @criticalRes    NA
* @faultHandling  NA
* @varInit        NA
* @selfDiag       NA
* @memory         NA
* @boundary       NA
*
******************************************************************************/
KVSvalue *KVS_Get(KVSstore *pStore, KVSkey *pKey)
{
    KVSpair *pair = KVS_get_pair(pStore, pKey);

    return pair ? pair->pValue : NULL;
}


/**
*
* @brief          Remove a value from the store.
*
* @param[in]      pStore   - A pointer to the store.
* @param[in]      pKey     - A key identifying the value to be removed.
*
* @retval         None
*
*
* @preConditions  NA
* @criticalRes    NA
* @faultHandling  NA
* @varInit        NA
* @selfDiag       NA
* @memory         NA
* @boundary       NA
*
******************************************************************************/
void KVS_Remove(KVSstore *pStore, KVSkey *pKey)
{
   KVSpair *pair = KVS_get_pair(pStore, pKey);

   if (pair)
   {
      KVS_RemovePair(pStore, pair);
   }
}

/**
*
* @brief       Get the number of values in a store.
*
* @param[in]   pStore   - A pointer to the store.
*
* @retval      The number of values contained in the store.
*
*
* @preConditions  NA
* @criticalRes    NA
* @faultHandling  NA
* @varInit        NA
* @selfDiag       NA
* @memory         NA
* @boundary       NA
*
******************************************************************************/
size_t KVS_Length(KVSstore *pStore)
{
   if (!pStore)
   {
       return 0;
   }
   return pStore->length;
}


/**
*
* @brief          Get a key-value pair at a given index.
*
* @param[in]      pStore   - A pointer to the store.
* @param[out]     index    - The index of the key-value pair.
*
* @retval         A pointer to the key-value pair, or NULL if the index is out or range.
*
*
* @preConditions  NA
* @criticalRes    NA
* @faultHandling  NA
* @varInit        NA
* @selfDiag       NA
* @memory         NA
* @boundary       NA
*
******************************************************************************/
KVSpair *KVS_Pair(KVSstore *pStore, size_t index)
{
   if ((!pStore) || (index < 0) || (index >= pStore->length))
   {
      return NULL;
   }

   return pStore->pairs + index;
}


/**
*
* @brief          Create a new key-value pair
*
* @param[in]      pStore   - A pointer to the store.
* @param[in]      pkey     - identification key
* @param[in]      pValue   - value to be associated with the key
*
* @retval         None
*
*
* @preConditions  NA
* @criticalRes    NA
* @faultHandling  NA
* @varInit        NA
* @selfDiag       NA
* @memory         NA
* @boundary       NA
*
******************************************************************************/
void KVS_CreatePair(KVSstore *pStore, KVSkey *pKey, KVSvalue *value)
{
   KVSpair *pair;
   if (!pStore)
   {
      return;
   }
   pair = KVS_Search(pStore, pKey, 0);

   if (pair < pStore->pairs + pStore->length)
   {
      size_t bytes = KVS_GetBytesFromPair(pStore, pair);
      memmove(pair + 1, pair, bytes);
   }
   pair->pKey = pKey;
   pair->pValue = value;
   KVS_ResizePairs(pStore, +1);
}


/************************* LOCAL FUNCTION IMPLEMENTATION *********************/

static void KVS_RemovePair(KVSstore *pStore, KVSpair *pair)
{
   if ((!pStore) || (!pair))
   {
      return;
   }
   memmove(pair, pair + 1, KVS_GetBytesFromPair(pStore, pair + 1));
   KVS_ResizePairs(pStore, -1);
}

static int KVS_ComparePointers(const char *a, const char *b)
{
   return a - b;
}

static KVSpair *KVS_Search(KVSstore *pStore, KVSkey *pKey, int exact)
{
   KVSpair *pairs = pStore->pairs;
   size_t lbound = 0;
   size_t rbound = pStore->length;
   while (lbound < rbound)
   {
      size_t index = lbound + ((rbound - lbound) >> 1);
      KVSpair *element = pairs + index;
      int result = pStore->compare(pKey, element->pKey);
      if (result < 0)
      {
          rbound = index;
      }
      else if (result > 0)
      {
          lbound = index + 1;
      }
      else
      {
          return element;
      }
   }
   return exact ? NULL : pairs + lbound;
}

static KVSpair *KVS_get_pair(KVSstore *pStore, KVSkey *pKey)
{
   if ((!pStore) || (!pStore->pairs))
   {
       return NULL;
   }

   return KVS_Search(pStore, pKey, 1);
}

static void KVS_AbortIfNull(void *pPointer, const char *pMessage)
{
   if (pPointer == NULL)
   {
      fprintf(stderr, "%s\n", pMessage);
      exit(-1);
   }
}

static void KVS_ResizePairs(KVSstore *pStore, size_t amount)
{
   if (!pStore)
   {
      return;
   }
   pStore->length += amount;

   if (pStore->space > pStore->length)
   {
      return;
   }
   pStore->space += KVS_SPACE_INCREMENT;
   pStore->pairs = realloc(pStore->pairs, KVS_pair_size * pStore->space);
   KVS_AbortIfNull(pStore->pairs, "out of memory");
}

static size_t KVS_GetPairIndex(KVSstore *pStore, KVSpair *pair)
{
   if ((!pStore) || (!pair))
   {
      return -1;
   }
   return pair - pStore->pairs;
}

static size_t KVS_GetBytesFromPair(KVSstore *pStore, KVSpair *pair)
{
   size_t pair_index;
   if ((!pStore) || (!pair))
   {
      return 0;
   }
   pair_index = KVS_GetPairIndex(pStore, pair);
   return (pStore->length - pair_index) * KVS_pair_size;
}


/** @} */
/****************** END OF FILE ***************************************************************************************/
