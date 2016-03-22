/*******************************************************************************
  Data Class Framework header file.

  Company:
    Microchip Technology Inc.

  File Name:
    data_class.h

  Summary:
    Framework to generate requested Class Data.

  Description:
    The framework implementated in this file, exposes APIs to Test Application
    to generate the differnet class data, append the test data as and when
    required and clear the data buffer.
*******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) <year> released Microchip Technology Inc.  All rights reserved.

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
// DOM-IGNORE-END

#ifndef _DATA_CLASS_H
#define	_DATA_CLASS_H

#include <xc.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "data_class/data_class_types.h"
#include "data_class/data_class_A.h"
#include "data_class/data_class_B.h"
#include "data_class/data_class_C.h"
#include "data_class/data_class_D.h"
#include "data_class/data_class_H.h"

// *****************************************************************************
// *****************************************************************************
// Section: Configuration Options
// *****************************************************************************
// *****************************************************************************


// *****************************************************************************
// *****************************************************************************
// Section: Type Definitions
// *****************************************************************************
// *****************************************************************************

typedef enum
{
    /* Data class error */
    DC_ERROR = 0,

    /* Data class success*/
    DC_SUCCESS
            
}DC_STATUS_CODES;

typedef struct
{
    /* Data class Name */
    DATA_CLASS className;

    /* Class start index */
    uint16_t startIndex;

    /* Class end index */
    uint16_t endIndex;

    /* Class sub index start */
    uint8_t subIndexStart;

    /* Class sub index end */
    uint8_t subIndexEnd;
    
}CLASS_DATA_ITEMS;

// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/* 
 * Function returns the data buffer for the requested class 
 * 
 * clData - Data class details 
 * data_ptr - Data buffer pointer
 * ptrNumOfBytes - Number of bytes in buffer pointer
 *  
 */
DC_STATUS_CODES DC_GetClassData(CLASS_DATA_ITEMS clData, char **dataPtr, uint32_t *ptrNumOfBytes);

#endif	/* _DATA_CLASS_H */

