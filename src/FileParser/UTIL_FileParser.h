/**
* @file           UTIL_FileParser.h
*
* @brief          File Parser - Public interface
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

#ifndef __UTIL_FILEPARSER_H
#define __UTIL_FILEPARSER_H

#ifdef __cplusplus
extern "C" {
#endif

/******************************* SYSTEM INCLUDES ******************************/

/******************************* PROJECT INCLUDES *****************************/
#include "../KeyValueStore/UTIL_KVS.h"

/******************************* DRIVER INCLUDES ******************************/

/****************************** LIBRARY INCLUDES ******************************/

/************************* TYPEDEFS, STRUCTURES and UNIONS ********************/


/**************************** MACRO DEFINITIONS  *****************************/
#define FP_FILE_MAX_SIZE  4096u

/************************* EXTERNAL FUNCTION PROTOTYPES ***********************/
int8_t FP_SaveKvs( KVSstore *pStore );
int8_t FP_LoadKvs( KVSstore *store );

#ifdef __cplusplus
}
#endif


#endif  /* __UTIL_FILEPARSER_H */
/** @} */
/****************** END OF FILE ***************************************************************************************/
