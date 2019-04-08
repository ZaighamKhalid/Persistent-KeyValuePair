/**
* @file           UTIL_ArgumentProcess.c
*
* @brief          File Parser - Implementation
*
* @author         Zaigham Khalid
*
* @riskClass      N/A
*
* @moduleID       N/A
*
* @modulePrefix   AP
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
#include <string.h>

/****************************** PRIVATE INCLUDES ******************************/
#include "UTIL_ArgumentProcess.h"

/******************************* PROJECT INCLUDES *****************************/

/******************************* DRIVER INCLUDES ******************************/

/******************************* LIBRARY INCLUDES *****************************/

/******************************** LOCAL DATA **********************************/

static const AP_CmdTable_t lCmdTable[UTIL_CMD_MAX] =
{
   {.cmd = "GET",    .identifier = AP_CMD_GET,        .minimumArgs = 3u, .maximumArgs = 3u  },
   {.cmd = "SET",    .identifier = AP_CMD_SET,        .minimumArgs = 4u, .maximumArgs = 255u},
   {.cmd = "DELETE", .identifier = AP_CMD_DELETE,     .minimumArgs = 3u, .maximumArgs = 3u  },
   {.cmd = "ADD",    .identifier = AP_CMD_ADD,        .minimumArgs = 4u, .maximumArgs = 255u},
   {.cmd = "REMKEY", .identifier = AP_CMD_REMOVE_KEY, .minimumArgs = 3u, .maximumArgs = 3u  },
   {.cmd = "LIST",   .identifier = AP_CMD_LIST,       .minimumArgs = 2u, .maximumArgs = 2u  }
};

/******************************** LOCAL VARIABLES *****************************/


/**************************** LOCAL FUNCTION PROTOTYPES ***********************/


/************************* PUBLIC FUNCTION IMPLEMENTATION *********************/

/**
*
* @brief          Parse the command from In-line argument
*
*
* @param[in]      argc     - Number of arguments
* @param[in]      pCmd     - Pointer to the command string
*
* @retval         - Evaluated command
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
AP_CMD_t AP_ParseCommand(uint8_t argc, const char *pCmd)
{
   AP_CMD_t retVal = UTIL_CMD_MAX;
   uint8_t index;

   for (index = 0; index < UTIL_CMD_MAX; index++)
   {
      if (strcmp(pCmd, lCmdTable[index].cmd) == 0u)
      {
    	 if ((argc >= lCmdTable[index].minimumArgs) &&
    	     (argc <= lCmdTable[index].maximumArgs))
    	 {
            retVal = lCmdTable[index].identifier;
    	 }

         break;
      }
   }

   return retVal;
}


/**
*
* @brief          Parse the payload from in-line arguments
*
*
* @param[in]      argc     - Number of arguments
* @param[in]      argv     - Pointer to the string array
*
* @retval         error Code - 0 in case of Success
*                            - -1 in case of failure
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
int8_t AP_ParsePayload(uint8_t argc, char* argv[], char *pStr)
{
	uint8_t index;
	uint8_t strPointer = 0;
	int8_t retVal = -1;

	for (index = 3u; index < argc; index++)
	{
	   strncpy(&pStr[strPointer], argv[index], strlen(argv[index]));
	   strPointer += strlen(argv[index]) - 1 ;
	   pStr[++strPointer] = ' ';
	   strPointer++;

	   retVal = 0;
	}

	pStr[strPointer] = 0;

	return retVal;
}



/** @} */
/****************** END OF FILE ***************************************************************************************/
