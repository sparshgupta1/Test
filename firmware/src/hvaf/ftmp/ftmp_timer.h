/*************************************************************************
FUT Tester Message Protocol (FTMP) Timer Interface Header Definitions

  Company:
    Microchip Technology Inc.
	
  File Name:
    ftmp_timer.h
	
  Summary:
    This file aggregates all of the FTMP Timer interface headers.
	
  Description:
    FTMP Interface Common Header
	  
  Remarks:
                              
  *************************************************************************/
  
#ifndef _FTMP_TIMER_H
#define _FTMP_TIMER_H

// *****************************************************************************
// *****************************************************************************
// Section: Included FTMP Module Headers Files
// *****************************************************************************
// *****************************************************************************

#include "ftmp_if.h"

/* Initialize Timer Instance */
void FTMP_TimerInit(void);

/* Clear Timer Counter */
void FTMP_TimerClearTick(void);

/* Get the current timer counter (time tick)*/
uint32_t FTMP_TimerGetTick(void);

/* Stop timer */
void FTMP_TimerDeInit(void);


#endif // _FTMP_TIMER_H
/*******************************************************************************
 End of File
*/

