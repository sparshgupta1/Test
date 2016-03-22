/*******************************************************************************
  FTMP Master/Slave Appplication Protocol Timer Functions Implementation

  Company:
    Microchip Technology Inc.

  File Name:
    ftmp_timer.c

  Summary:
    FTMP Master/Slave Appplication Protocol Timer Functions Implementation

  Description:

	
*******************************************************************************/


// *****************************************************************************
// *****************************************************************************
// Section: Include Files
// *****************************************************************************
// *****************************************************************************

#include "ftmp_timer.h"
#include "peripheral/tmr/plib_tmr.h"
#include "peripheral/int/plib_int.h"

// *****************************************************************************
// *****************************************************************************
// Section: File Scope Variables
// *****************************************************************************
// *****************************************************************************

static uint32_t ftmp_timer_inc =0;


// *****************************************************************************
// *****************************************************************************
// Section: File Scope Functions
// *****************************************************************************
// *****************************************************************************

void FTMP_TimerIncrement ( void );

// *****************************************************************************
// *****************************************************************************
// Section: Interface Function Definitions
// *****************************************************************************
// *****************************************************************************

void FTMP_TimerInit(void)
{   
    /* Disable Timer 2 */
    PLIB_TMR_Stop(FTMP_TMR_TICK_NUM);

    PLIB_TMR_ClockSourceSelect(FTMP_TMR_TICK_NUM, FTMP_TIMER_CLOCK_SOURCE);
    PLIB_TMR_PrescaleSelect(FTMP_TMR_TICK_NUM, FTMP_TIMER_CLOCK_PRESCALER);
    PLIB_TMR_Mode16BitEnable(FTMP_TMR_TICK_NUM);
    PLIB_TMR_Counter16BitClear(FTMP_TMR_TICK_NUM);
    PLIB_TMR_Period16BitSet(FTMP_TMR_TICK_NUM, FTMP_TIMER_INCREMENT_PERIOD);
    
    PLIB_INT_VectorPrioritySet(INT_ID_0, FTMP_TIMER_INTERRUPT_VECTOR, FTMP_TIMER_INTERRUPT_PRIORITY);
    PLIB_INT_VectorSubPrioritySet(INT_ID_0, FTMP_TIMER_INTERRUPT_VECTOR, FTMP_TIMER_INTERRUPT_SUBPRIORITY);
    PLIB_INT_SourceEnable(INT_ID_0, INT_SOURCE_TIMER_2);
    
    PLIB_TMR_Counter16BitClear(FTMP_TMR_TICK_NUM);
    
    /* Start Timer 2 */
    PLIB_TMR_Start(FTMP_TMR_TICK_NUM); 
}

void FTMP_TimerIncrement ( void )
{
    ftmp_timer_inc += FTMP_TIMER_MS_PER_INCREMENT;
}

void FTMP_TimerClearTick(void)
{
    /* Clear the timer increment value */
    ftmp_timer_inc = 0;
}

uint32_t FTMP_TimerGetTick(void)
{
    return ftmp_timer_inc;
}

void FTMP_TimerDeInit(void)
{
    /* Disable Timer 2 */
    PLIB_TMR_Stop(FTMP_TMR_TICK_NUM);
}

void __ISR(_TIMER_2_VECTOR) _FTMP_Timer_ISR(void)
{
    FTMP_TimerIncrement();
    PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_TIMER_2);
}
