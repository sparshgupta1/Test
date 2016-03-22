/*******************************************************************************
  HVAF Stimulus Data Manager (SDM) Driver Header

  File Name:
    sdm_driver.h

  Summary:
    SDM Driver Header which has interface declaration for Stimulus functions.

  Description:
    SDM Driver interfaces allows tester to provide stimulus functions to SDM.

  Remarks:
    
    Created with MPLAB Harmony Version 1.06
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

#ifndef SDM_DRIVER_H
#define	SDM_DRIVER_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
/*  This section Includes other headers */
#include "sdm_datatypes.h"
#include "tm_tester_local.h"

// *****************************************************************************
// *****************************************************************************
// Section: Macro Definitions
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
// *****************************************************************************
// Section: Type Definitions
// *****************************************************************************
// *****************************************************************************
// *****************************************************************************



void SDM_STIMULUS_Initialize ( uint32_t iConfigID );

void SDM_STIMULUS_Start( TM_TEST_CASE_INFO *tcSDMObj, DRV_CALLBACK drvCallBack );

TM_TC_RESULT SDM_STIMULUS_Verify(TM_TEST_CASE_INFO *tcSDMObj);

void SDM_STIMULUS_Reset(TM_TEST_CASE_INFO *tcSDMObj);



#endif	/* SDM_DRIVER_H */

