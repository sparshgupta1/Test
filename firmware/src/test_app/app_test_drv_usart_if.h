/*******************************************************************************
  MPLAB Harmony Usart Driver Functional Test Header File

  Company:
    Microchip Technology Inc.

  File Name:
    app_test_drv_usart_if.h

  Summary:
    This header file provides prototypes and definitions for the test module.

  Description:
    This header file provides function prototypes and data type definitions for
    the test module.
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

#ifndef _TEST_DRV_USART_IF_H
#define _TEST_DRV_USART_IF_H


// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include "system_config.h"
#include "system_definitions.h"
#include "system/debug/sys_debug.h"
#include "driver/usart/drv_usart.h"


#define HVAF_TEST_COMPONENT 	USART
#define HVAF_TEST_LAYER 		DRIVER
#define HVAF_TEST_VERSION		v0.2

// *****************************************************************************
// *****************************************************************************
// Section: Configuration Options
// *****************************************************************************
// *****************************************************************************
/* This section checks settings for drv_usart module functional test configuration 
   options.
*/

/* USART driver dynamic configuration data */
typedef struct{
	
	/* USART Baudrate */
	uint32_t baud;

	/* USART Line Control */
	USART_LINECONTROL_MODE linectrl;
	
	/* USART Handshake Signal */
	USART_HANDSHAKE_MODE handshake;

}DRV_USART_DYN_CONFIG_DATA;



// *****************************************************************************
// *****************************************************************************
// Section: Type Definitions
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Usart Driver Test Initialization Data

  Summary:
    Holds the drv_usart module test's initialization data.

  Description:
    This structure holds the drv_usart module test's initialization data.
 */


#endif /* _TEST_DRV_USART_BASIC_READ_MODULE_H */
/*******************************************************************************
 End of File
 */

