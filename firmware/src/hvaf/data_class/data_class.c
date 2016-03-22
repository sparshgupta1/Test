/*******************************************************************************
  Data Class Framework source file.

  Company:
    Microchip Technology Inc.

  File Name:
    data_class.c

  Summary:
    Framework to generate requested Class Data.

  Description:
    The framework implementated in this file, exposes APIs to Test Application
    to generate the differnet class data, append the test data as and when
    required and clear the data buffer.
*******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2014 released Microchip Technology Inc.  All rights reserved.

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


// *****************************************************************************
// *****************************************************************************
// Section: Includes
// *****************************************************************************
// *****************************************************************************

#include "data_class/data_class.h"

/* 
 * Function returns the data buffer for the requested class 
 * 
 * clData - Data class details 
 * data_ptr - Data buffer pointer
 * ptrNumOfBytes - Number of bytes in buffer pointer
 *  
 */
DC_STATUS_CODES DC_GetClassData(CLASS_DATA_ITEMS clData, char **dataPtr, uint32_t *ptrNumOfBytes)
{
    DATA_CLASS class = clData.className;

    /* Select the case based on data class requested */
    switch(class)
    {
        /* Class A */
        case DATACLASS_A:
        {
            /* Valid index check */
            if(clData.startIndex > clData.endIndex) 
            {
                return DC_ERROR;
            }
            else
            {
                /* Get and pass the class A buffer data and length */
                *dataPtr = (char *) &class_A_data[clData.startIndex];
                *ptrNumOfBytes = ((clData.endIndex - clData.startIndex) + 1);   
            }            
            break;
        }
        /* Class B */
        case DATACLASS_B:
        {
            /* Valid index check */
            if(clData.startIndex > clData.endIndex) 
            {
                return DC_ERROR;
            }
            else
            {
                /* Get and pass the class B buffer data and length */
                *dataPtr = (char *) &class_B_data[clData.startIndex];
                *ptrNumOfBytes = (((clData.endIndex - clData.startIndex) + 1)*2);   
            }               
            break;
        }
        /* Class C */
        case DATACLASS_C:
        {
            /* Valid index check */
            if(clData.startIndex > clData.endIndex) 
            {
                return DC_ERROR;
            }
            else
            {
                /* Get and pass the class C buffer data and length */
                *dataPtr = (char *) &class_C_data[clData.startIndex];
                *ptrNumOfBytes = (((clData.endIndex - clData.startIndex) + 1)*4);   
            }                
            break;
        }
        /* Class D */
        case DATACLASS_D:
        {
            /* Valid index check */
            if(clData.startIndex != clData.endIndex) 
            {
                return DC_ERROR;
            }
            else
            {
                /* Get and pass the class D buffer data and length */
                *dataPtr = (char *) class_D_data[clData.startIndex];
                *ptrNumOfBytes = strlen(class_D_data[clData.startIndex]);   
            }
            break;
        }
        /* Unknown or non implemented class */
        default:
        {
            return DC_ERROR;
            break;
        }
    }
    
    return DC_SUCCESS;
}