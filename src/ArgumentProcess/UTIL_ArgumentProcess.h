/**
* @file           UTIL_ArgumentProcess.h
*
* @brief          Process Arguments - Public interface
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

#ifdef __cplusplus
extern "C" {
#endif

#ifndef __UTIL_ARGUMENTPROCESS_H
#define __UTIL_ARGUMENTPROCESS_H

/******************************* SYSTEM INCLUDES ******************************/
#include <stdint.h>

/******************************* PROJECT INCLUDES *****************************/

/******************************* DRIVER INCLUDES ******************************/

/****************************** LIBRARY INCLUDES ******************************/

/************************* TYPEDEFS, STRUCTURES and UNIONS ********************/

typedef enum
{
   AP_CMD_GET = 0u,
   AP_CMD_SET,
   AP_CMD_DELETE,
   AP_CMD_ADD,
   AP_CMD_REMOVE_KEY,
   AP_CMD_LIST,

   UTIL_CMD_MAX
} AP_CMD_t;


typedef struct
{
   const char* cmd;
   AP_CMD_t identifier;
   uint8_t minimumArgs;
   uint8_t maximumArgs;
} AP_CmdTable_t;

/************************* EXTERNAL FUNCTION PROTOTYPES ***********************/
AP_CMD_t AP_ParseCommand(uint8_t argc, const char *pCmd);
int8_t   AP_ParsePayload(uint8_t argc, char* argv[], char *pStr);

#ifdef __cplusplus
}
#endif


#endif  /* __UTIL_ARGUMENTPROCESS_H */
/** @} */
/****************** END OF FILE ***************************************************************************************/
