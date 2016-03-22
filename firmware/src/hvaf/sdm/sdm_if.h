/*******************************************************************************
  Stimulus Data Manager (SDM) Interface Header File.

  Company:
    Microchip Technology Inc.

  File Name:
    sdm_if.h

  Summary:
    This header file provides prototypes and definitions for the SDM Interface.

  Description:
    This header file provides function prototypes for the SDM interface.  
*******************************************************************************/

//DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2013-2014 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
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

#ifndef _SDM_IF_H
#define _SDM_IF_H

// *****************************************************************************
// *****************************************************************************
// Section: Included SDM Module Headers Files
// *****************************************************************************
// *****************************************************************************
#include "tm_tester_local.h"
#include "sdm_datatypes.h"

// *****************************************************************************
// *****************************************************************************
// Section: Macro Definitions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void SDM_Interface_Initialize ( void )

  Summary:
     SDM interface initialization routine.

  Description:
    This function initializes the SDM Interface.  It places the SDM in its
    initial state and prepares it to run so that its SDM_Tasks function 
    can be called.

  Precondition:
    This initialization routine should be called in "SYS_Initialize".

  Parameters:
    None.

  Returns:
    None.

  Example:
    <code>
    SDM_Interface_Initialize();
    </code>

  Remarks:
    This routine must be called from the SYS_Initialize function.
*/
void SDM_Interface_Initialize(void);

/*******************************************************************************
  Function:
    SDM_ERROR_CODES SDM_ConfigStimulus(uint8_t ConfigID)

  Summary:
     SDM interface routine for test manager.

  Description:
    SDM interface routine for test manager to pass configuration request.

  Precondition:
    The initialization routine "SDM_Interface_Initialize" should be called 
    before calling this API.

  Parameters:
    ConfigID        - Configuration Index of the predefined table.
    
  Returns:
    SDM_ERROR_CODES - Error Code.

  Example:
    <code>
    SDM_ConfigStimulus(ConfigID);
    </code>

  Remarks:
    None.
*/
SDM_ERROR_CODES SDM_ConfigStimulus(uint8_t ConfigID);


/*******************************************************************************
  Function:
    SDM_ERROR_CODES SDM_StimulusStart(TM_TEST_CASE_INFO,  DRV_CALLBACK)

  Summary:
     SDM interface routine for test manager.

  Description:
    SDM interface routine for test manager to pass stimulus request.

  Precondition:
    The initialization routine "SDM_Interface_Initialize" should be called 
    before calling this API.

  Parameters:
    pObj         - Pointer to Test Case Object.

    DRV_CALLBACK - Callback function received from Test Manager.
 
  Returns:
    SDM_ERROR_CODES - Error Code.

  Example:
    <code>
    SDM_StimulusStart(pObj, TesterCallback);
    </code>

  Remarks:
    None.
*/
SDM_ERROR_CODES SDM_StimulusStart(TM_TEST_CASE_INFO *pObj, 
                                  DRV_CALLBACK TesterCallback);

#endif // _SDM_IF_H
/*******************************************************************************
 End of File
*/

