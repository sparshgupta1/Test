/*******************************************************************************
  MPLAB Harmony Tester Stimulus Data File

  Company:
    Microchip Technology Inc.

  File Name:
    stimulus_data.h

  Summary:
    This header file provides prototypes and definitions for the stimulus
    data.

  Description:
    This header file provides function prototypes and data type definitions for
    the stimulus data.
*******************************************************************************/

//DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2013-2015 released Microchip Technology Inc.  All rights reserved.

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

#ifndef _STIMULUS_DATA_H
#define _STIMULUS_DATA_H


// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include "system/common/sys_module.h"
#include "sdm_datatypes.h"
#include "system_definitions.h"
#include "tm_tester_local.h"

// *****************************************************************************
// *****************************************************************************
// Section: Type Definitions
// *****************************************************************************
// *****************************************************************************
/* Stimulus for Test cases */
typedef struct
{
    /* Test Case ID */
	uint8_t*   testCaseId;
    
    /* Test Data Buffer */
	uint8_t*	buffer;
    
    /* Number of Bytes to be sent/received */
	uint32_t  iDataSize;
    
}STIMULUS_TEST_LIST;


void STIMULUS_GetTestsStat(STIMULUS_INIT_DATA *pstimulusDataObj);


#endif /* _STIMULUS_DATA_H */
/*******************************************************************************
 End of File
 */

