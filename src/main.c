/**
* @file           Task.cpp
*
* @brief          Command line config file interface - Implementation
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
* @addtogroup TASK_MAIN
* @{
* @file
*/


/****************************** SYSTEM INCLUDES *******************************/
#include <stdio.h>
#include <string.h>

/****************************** PRIVATE INCLUDES ******************************/

/******************************* PROJECT INCLUDES *****************************/
#include "ArgumentProcess/UTIL_ArgumentProcess.h"
#include "KeyValueStore/UTIL_KVS.h"
#include "FileParser/UTIL_FileParser.h"
/******************************* DRIVER INCLUDES ******************************/

/******************************* LIBRARY INCLUDES *****************************/

/******************************** LOCAL DATA **********************************/


/******************************** LOCAL VARIABLES *****************************/


/******************************** LOCAL MACROS ********************************/
#define SYS_VAL_MAX_SIZE   100u

/**************************** LOCAL FUNCTION PROTOTYPES ***********************/

static void SYS_DumpTable(KVSstore *pStore);
static void SYS_StoreDefault(KVSstore *pStore);

/************************* PUBLIC FUNCTION IMPLEMENTATION *********************/


int main(int argc, char *argv[])
{
   AP_CMD_t cmd;
   KVSstore *store;
   char *pValue;
   char value[SYS_VAL_MAX_SIZE];

   if (argc >= 2)
   {
      /* Parse the command from received arguments */
      cmd = AP_ParseCommand((uint8_t) argc, argv[1]);

      /* Generate a warning if the command is not valid */
      if (cmd == UTIL_CMD_MAX)
      {
         fprintf(stdout, "\rInput argument not recognized. Not a valid command.");
      }
      else
      {
         /* Initialize the key value table */
         store = KVS_Create(strcmp);

         /* Load the text file and store values in the table */
         if (FP_LoadKvs(store) == 0)
         {
            switch (cmd)
            {
               case AP_CMD_GET:
               /* Get the value corresponding to the key and display if it is valid */
               pValue = (char*) KVS_Get(store, argv[2]);

               if (pValue != NULL)
               {
                  fprintf(stdout, "%s\n", pValue);
               }
               else
               {
                  fprintf(stdout, "Unable to find the indicated key\n");
               }
               break;

               case AP_CMD_SET:
               /* Parse the payload. It permits us to receive a longer argument with spaces and special characters */
               if ( AP_ParsePayload(argc, argv, value) == 0)
               {
                  /* Subsitute the existing value with requested input */
                  if (KVS_Put(store, argv[2], (void*) value) == 0)
                  {
                     /* Save the table in the text file */
                     FP_SaveKvs(store);
                     fprintf(stdout, "OK\n");
                  }
                  else
                  {
                     fprintf(stdout, "Unable to find the indicated key\n");
                  }
               }
               else
               {
                  fprintf(stdout, "Invalid payload\n");
               }
               break;

               case AP_CMD_DELETE:
                  /* Writes NULL in place of value in the requested Key */
                  if (KVS_Put(store, argv[2], NULL) != 0)
                  {
                     /* Display a warning if the key was not found */
                     fprintf(stdout, "Unable to find the indicated key\n");
                  }
                  else
                  {
                    fprintf(stdout, "OK\n");
                    FP_SaveKvs(store);
                  }
               break;

               case AP_CMD_ADD:

                  pValue = (char*) KVS_Get(store, argv[2]);

                  /* Check if requested key already exists */
                  if (pValue != NULL)
                  {
                     fprintf(stdout, "The key already exists\n");
                  }
                  else
                  {
                     /* Parse the payload and insert a new key-value pair  */
                     if ( AP_ParsePayload(argc, argv, value) == 0)
                     {
                        KVS_CreatePair(store, argv[2], (void*) value);
                        FP_SaveKvs(store);
                        fprintf(stdout, "OK\n");
                     }
                     else
                     {
                       fprintf(stdout, "Invalid payload\n");
                     }
                  }

               break;

               case AP_CMD_REMOVE_KEY:
                  pValue = (char*) KVS_Get(store, argv[2]);

                 /* If the key exists, delete it from the table */
                 if (pValue != NULL)
                 {
                    KVS_Remove(store, argv[2]);
                    fprintf(stdout, "OK\n");
                    FP_SaveKvs(store);
                 }
                 else
                 {
                    fprintf(stdout, "Unable to find the indicated key\n");
                 }
               break;

               case AP_CMD_LIST:
                  /* Dump the key-value table on stdout */
                  SYS_DumpTable(store);
                  break;

               default:
               /* Call an exception here */
               break;
            }
         }
         else
         {
           SYS_StoreDefault(store);
         }
      }
   }
   else
   {
      fprintf(stdout, "Not Enough arguments\n");
   }
}

/************************* LOCAL FUNCTION IMPLEMENTATION *********************/


/**
*
* @brief          Dump the key-value table to stdout
*
*
* @param[in]      store    - A pointer to the store.
*
* @retval         None
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
static void SYS_DumpTable(KVSstore *pStore)
{
   KVSpair *pPair = NULL;
   int index = 0;

   fprintf(stdout, "\r\n*****************************************\r\n");
   fprintf(stdout, "*****************************************\r\n\r\n");
   while ((pPair = KVS_Pair(pStore, index++)) != NULL)
   {
      fprintf(stdout, "%s -> %s\r\n", (char*)pPair->pKey, (char*)pPair->pValue);
   }
   fprintf(stdout, "\r\n*****************************************\r\n");
   fprintf(stdout, "*****************************************\r\n");
}


/**
*
* @brief          Write default dummy values in the text file
*
*
* @param[in]      store    - A pointer to the store.
*
* @retval         None
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
static void SYS_StoreDefault(KVSstore *pStore)
{
   KVS_CreatePair(pStore, "Manufacturer",   (KVSvalue*)"Clay");
   KVS_CreatePair(pStore, "DeviceCategory", (KVSvalue*)"Access Control");
   KVS_CreatePair(pStore, "Contact",        (KVSvalue*)"Prins Hendrikkade 164C 1011 TB Amsterdam, NL");
   KVS_CreatePair(pStore, "Phone",          (KVSvalue*)"+31 203 034 280");
   KVS_CreatePair(pStore, "Info",           (KVSvalue*)"Salto Group");
   FP_SaveKvs(pStore);
}


/** @} */
/****************** END OF FILE ***************************************************************************************/
