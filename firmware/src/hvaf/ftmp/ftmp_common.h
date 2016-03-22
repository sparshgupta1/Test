/*************************************************************************
FUT Tester Message Protocol (FTMP) Common Interface Header Definitions

  Company:
    Microchip Technology Inc.
	
  File Name:
    ftmp_common.h
	
  Summary:
    This file aggregates all of the FTMP common interface headers.
	
  Description:
    FTMP Interface Common Header
	  
  Remarks:
                              
  *************************************************************************/
  
#ifndef _FTMP_COMMON_H
#define _FTMP_COMMON_H

// *****************************************************************************
// *****************************************************************************
// Section: Included FTMP Module Headers Files
// *****************************************************************************
// *****************************************************************************

#include "ftmp_if.h"

/* Fucntion to Calculate CRC */
uint16_t FTMP_CalculateCRC(uint8_t* data, uint16_t size);

/* Function to Check CRC */
bool FTMP_CheckCRC(uint8_t* data, uint16_t size);

/* This function allocates global buffer for data sharing */
bool FTMP_Allocate_Memory(uint16_t length, uint8_t** buf_ptr);

/* Timer driver Init routine */
void FTMP_TimerInit(void);

/* Get timer tick - It's a free running timer */
uint32_t FTMP_GetTimerTick(void);

/* Clear and Get Timer Tick */
uint32_t FTMP_ClearandGetTimerTick(void);

/* Get Timer Tick */
uint32_t FTMP_GetTimerTick(void);

/* Check the Timer expiry status */
bool FTMP_CheckTimerExpiry(uint16_t delayms, uint32_t prev_time);

/* Data Buffer */
extern uint8_t FTMP_SharedDataBuffer[FTMP_STATIC_BUFFER_SIZE];

#endif // _FTMP_COMMON_H
/*******************************************************************************
 End of File
*/

