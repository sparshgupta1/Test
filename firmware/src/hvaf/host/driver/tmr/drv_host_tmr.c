/*******************************************************************************
  Tester Framework Application 
  
  File Name:
    drv_host_tmr.c

  Summary:
 

  Description:

 ******************************************************************************/


// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2012 released Microchip Technology Inc.  All rights reserved.

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
 ******************************************************************************/
// DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: Included Files 
// *****************************************************************************
// *****************************************************************************
#include "drv_host_tmr.h"

// *****************************************************************************
// *****************************************************************************
// Section: Variable Declaration
// *****************************************************************************
// *****************************************************************************

HOST_CALLBACK tmr_callback;
uint16_t g_delay;

/******************************************************************************
  Function:
    void DRV_HOST_TMR_Initialize(void)

  Description:

*/
void DRV_HOST_TMR_Initialize(TMR_MODULE_ID tmr_id)
{
    /* Init HOST Communication Timer */
    HOST_TIMER_INIT();

    /* Set Period for 1ms timeout */
    HOST_TIMER_PERIOD_SET(0x138);

    /* Clear the Timer INT */
    HOST_TIMER_INT_CLEAR();
}

/******************************************************************************
  Function:
    void DRV_HOST_TMR_Start(uint16_t delay, HOST_CALLBACK callback)

  Description:

*/
void DRV_HOST_TMR_Start(uint16_t delay, HOST_CALLBACK callback)
{
    /* Assing the args*/
    tmr_callback = callback;
    g_delay = delay;

    /* Check delay period is valid */
    if(delay != 0)
    {
        HOST_TIMER_START();
    }
    else
    {
        (*tmr_callback)();
    }
}

/******************************************************************************
  Function:
    void DRV_HOST_TMR_Stop(void)

  Description:

*/
void DRV_HOST_TMR_Stop(void)
{
    g_delay = 0;

    HOST_TIMER_STOP();
}

/******************************************************************************
  Function:
    void __ISR(HOST_TIMER_VECTOR) HOST_TMR_INTHandler(void)

  Description:

*/
void __ISR(HOST_TIMER_VECTOR) HOST_TMR_INTHandler(void)
{
    /* Clear Timer Interrupt Flag */
    HOST_TIMER_INT_CLEAR();

    /* Decrement the Timer Counter */
    g_delay--;

    /* Check if the timer counter reaches zero */
    if(g_delay <= 0)
    {
        /* Stop the timer */
        HOST_TIMER_STOP();

        /* Call back function will be triggered */
        (*tmr_callback)();
    }
}

/*******************************************************************************
 End of File
 */
