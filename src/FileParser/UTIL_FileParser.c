/**
* @file           UTIL_FileParser.c
*
* @brief          File Parser - Implementation
*
* @author         Zaigham Khalid
*
* @riskClass      N/A
*
* @moduleID       N/A
*
* @modulePrefix   FP
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
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
/****************************** PRIVATE INCLUDES ******************************/
#include "UTIL_FileParser.h"

/******************************* PROJECT INCLUDES *****************************/

/******************************* DRIVER INCLUDES ******************************/

/******************************* LIBRARY INCLUDES *****************************/

/******************************** LOCAL DATA **********************************/

static const char lKeyPrefix[]   = ".K: ";
static const char lValuePrefix[] = ".V: ";

/******************************** LOCAL VARIABLES *****************************/

/******************************** LOCAL MACROS *******************************/
#define FP_FILENAME     "config.txt"

/**************************** LOCAL FUNCTION PROTOTYPES ***********************/


/************************* PUBLIC FUNCTION IMPLEMENTATION *********************/

/**
*
* @brief       Save the contents of key value table in the text file
*
*
* @param[in]   store    - A pointer to the store.
*
* @retval      error Code - 0 in case of Success
*                         - -1 in case of failure
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
int8_t FP_SaveKvs( KVSstore *pStore )
{
    FILE *pFileName;
    KVSpair *p;
    int8_t retVal = 0;
    uint16_t index = 0;

    pFileName = fopen(FP_FILENAME, "w+");

    if (pFileName != NULL)
    {
       while ((p = KVS_Pair(pStore, index++)))
       {
          fprintf(pFileName, "%s%s\n",lKeyPrefix, (char *)p->pKey);
          fprintf(pFileName, "%s%s\n",lValuePrefix, (char *)p->pValue);
       }

       fclose(pFileName);
       retVal = 0;
    }
    else
    {
       perror("error: ");
       retVal = -1;
    }

    return retVal;
}


/**
*
* @brief       Load the contents of the text file in the key value table
*
*
* @param[in]   store    - A pointer to the store.
*
* @retval      error Code - 0 in case of Success
*                         - -1 in case of failure
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
int8_t FP_LoadKvs( KVSstore *store )
{
   FILE *pFileName;

   static char stackKeys[FP_FILE_MAX_SIZE];
   static char stackValues[FP_FILE_MAX_SIZE];

   uint16_t indexKey   = 0u;
   uint16_t indexValue = 0u;
   uint16_t keySize    = 0u;
   uint16_t valueSize  = 0u;
   int8_t retVal = -1;

   char key[50];
   char value[50];

   pFileName = fopen(FP_FILENAME, "r");

   if (pFileName != NULL)
   {
      while (fscanf(pFileName, "%[^\n]", key) != EOF)
      {
         fgetc(pFileName);

          if (strlen(key) > sizeof(lKeyPrefix))
          {
             if (strncmp(key, lKeyPrefix, strlen(lKeyPrefix) - 1) == 0u)
             {
                if (fscanf(pFileName, "%[^\n]", value) != EOF)
                {
                   fgetc(pFileName);

                   if (strlen(value) > strlen(lValuePrefix))
                   {
                      if (strncmp(value, lValuePrefix, strlen(lValuePrefix) - 1) == 0u)
                      {
                         keySize = strlen(key) - strlen(lKeyPrefix);
                         valueSize = strlen(value) - strlen(lValuePrefix);

                         if (((indexKey + keySize)    >= FP_FILE_MAX_SIZE - 1) ||
                           ((indexValue + valueSize) >= FP_FILE_MAX_SIZE - 1))
                         {
                           break;
                         }

                         memcpy((void*)&stackKeys[indexKey],     (void*)&key[strlen(lKeyPrefix) ],   keySize);
                         memcpy((void*)&stackValues[indexValue], (void*)&value[strlen(lValuePrefix)], valueSize);

                         KVS_CreatePair(store, &stackKeys[indexKey], (KVSvalue*)&stackValues[indexValue]);
                         indexKey += keySize ;
                         indexValue += valueSize;

                         stackKeys[indexKey++]     = 0;
                         stackValues[indexValue++] = 0;
                         retVal = 0;
                      }
                   }
                }
             }
         }
      }

      fclose(pFileName);
   }
   else
   {
      perror("error: ");
      retVal = -1;
   }


   return retVal;
}



/** @} */
/****************** END OF FILE ***************************************************************************************/
