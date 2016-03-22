  /*******************************************************************************
  Application Header
  
  File Name:
    drv_host_tmr_5xx_6xx_7xx.h

  Summary:


  Description:

 *******************************************************************************/

//DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2011-2012 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED AS IS WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
 *******************************************************************************/
//DOM-IGNORE-END

#ifndef _DRV_TMR_5XX_6XX_7XX_H_
#define _DRV_TMR_5XX_6XX_7XX_H_

#include "peripheral/peripheral.h"

// *****************************************************************************
// *****************************************************************************
// Section: Defines
// *****************************************************************************
// *****************************************************************************
#define HOST_TIMER_INIT()                                                     \
{                                                                             \
    PLIB_TMR_Stop(TMR_ID_4);                                                  \
    PLIB_TMR_ClockSourceSelect(TMR_ID_4, TMR_CLOCK_SOURCE_PERIPHERAL_CLOCK);  \
    PLIB_TMR_PrescaleSelect(TMR_ID_4, TMR_PRESCALE_VALUE_256);                \
    PLIB_TMR_Counter16BitClear(TMR_ID_4);                                     \
    PLIB_INT_SourceEnable(INT_ID_0, INT_SOURCE_TIMER_4);                      \
    PLIB_INT_VectorPrioritySet(INT_ID_0, INT_VECTOR_T4, INT_PRIORITY_LEVEL2); \
    PLIB_INT_VectorSubPrioritySet(INT_ID_0, INT_VECTOR_T4, INT_SUBPRIORITY_LEVEL0); \
}

#define HOST_TIMER_PERIOD_SET(x)    PLIB_TMR_Period16BitSet(TMR_ID_4, x);
#define HOST_TIMER_INT_CLEAR()      PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_TIMER_4);
#define HOST_TIMER_START()          PLIB_TMR_Start(TMR_ID_4);
#define HOST_TIMER_STOP()           PLIB_TMR_Stop(TMR_ID_4);
#define HOST_TIMER_VECTOR           _TIMER_4_VECTOR

#endif

/*******************************************************************************
 End of File
*/

