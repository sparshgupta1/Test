/*******************************************************************************
  Stimulus Data Manager (SDM) Task Routine Header File.

  Company:
    Microchip Technology Inc.

  File Name:
    sdm_if.h

  Summary:
    This header file provides prototypes and definitions for the SDM Task.

  Description:
    This header file provides function prototypes for the SDM Task Routine.  
*******************************************************************************/
// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2013-2015 released Microchip Technology Inc.  All rights reserved.

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
// DOM-IGNORE-END

#ifndef _SDM_TASKS_H
#define _SDM_TASKS_H
// *****************************************************************************
// *****************************************************************************
// Section: Include Files
// *****************************************************************************
// *****************************************************************************
#include "tm_tester_local.h"
#include "sdm_datatypes.h"

// *****************************************************************************
// *****************************************************************************
// Section: Macro Definitions
// *****************************************************************************
// *****************************************************************************
#ifndef SDM_TIMEOUT_PERIOD_MS
    #define SDM_TIMEOUT_PERIOD_MS         500
#endif

// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Routines
// *****************************************************************************
// *****************************************************************************
/* These routines are called by drivers when certain events occur.
*/
/*******************************************************************************
  Function:
    void SDM_EventHandler(SDM_STIMULUS_EVENT event);

  Summary:
    SDM Event Handler

  Description:
    This SDM event handler will be called after receiving the request from
    Tester Manager.

  Precondition:
    None.

  Parameters:
    None.

  Returns:
    None.

  Example:
    <code>
    SDM_EventHandler(SDM_STIMULUS_REQUEST);
    </code>

  Remarks:
    This routine must be called from SYS_Tasks() routine.
 */
void SDM_EventHandler(SDM_STIMULUS_EVENT event);

/*******************************************************************************
  Function:
    void SDM_DriverCallback(SDM_DRV_CALLBACK event, bool bResult);

  Summary:
    SDM Callback Handler

  Description:
    The SDM Callback handler will be called once stimulus completes.

  Precondition:
    None.

  Parameters:
    None.

  Returns:
    None.

  Example:
    <code>
    SDM_DriverCallback(SDM_DRV_STIMULUS_COMPLETE, true);
    </code>

  Remarks:
    This routine must be called from SYS_Tasks() routine.
 */
//void SDM_DriverCallback(SDM_DRV_CALLBACK event, bool bResult);
void SDM_DriverCallback(void);

// *****************************************************************************
// *****************************************************************************
// Section: Interface Function Definitions
// *****************************************************************************
// *****************************************************************************
/*******************************************************************************
  Function:
    void SDM_Initialize ( void )

  Summary:
     SDM initialization routine.

  Description:
    This function initializes the SDM.  It places the SDM in its initial state. 

  Precondition:
    All other system initialization routines should be called before calling
    this routine (in "SYS_Initialize").

  Parameters:
    None.

  Returns:
    None.

  Example:
    <code>
    SDM_Initialize();
    </code>

  Remarks:
    This routine must be called from the SYS_Initialize function.
*/
/*
void SDM_Interface_Initialize(SDM_TC_CONFIG_OBJ *ConfigObj,SDM_TC_OBJ *TestObj);
*/
void SDM_Initialize(void);


/*******************************************************************************
  Function:
    void SDM_Task ( void )

  Summary:
    SDM tasks function

  Description:
    This routine is the SDM tasks function.  It defines the SDM state machine 
    and interface logic.

  Precondition:
    The SDM initialization-SDM_Initialize should be called before calling this.

  Parameters:
    None.

  Returns:
    None.

  Example:
    <code>
    SDM_Task();
    </code>

  Remarks:
    This routine must be called from SYS_Tasks() routine.
 */
void SDM_Task(void);

#endif /* END SDM_TASKS_H */