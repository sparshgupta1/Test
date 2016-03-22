/*******************************************************************************
  MPLAB Harmony Usart Driver Functional Test Header File

  Company:
    Microchip Technology Inc.

  File Name:
    app_test_drv_usart_basic_read_func.h

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

#ifndef _TEST_DRV_USART_BASIC_READ_MODULE_H
#define _TEST_DRV_USART_BASIC_READ_MODULE_H


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
#include "app_test_drv_usart_if.h"
#include "tm_fut_if.h"

// *****************************************************************************
// *****************************************************************************
// Section: Configuration Options
// *****************************************************************************
// *****************************************************************************
/* This section checks settings for drv_usart module functional test configuration 
   options.
*/

#ifndef DRV_USART_INSTANCES_NUMBER
    #error "Number of drv_usart instances to test must be defined."
#endif


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

typedef struct{
    
    /* Sub Test Id*/
    char* testCaseId;

    /* Test Data Information */
    CLASS_DATA_ITEMS data[DRV_USART_INSTANCES_NUMBER];
    
}TS_DRV_USART_BASIC_READ;

typedef struct _drv_usart_module_test_basic_read_init_data
{
    /* Module init structure */
    SYS_MODULE_INIT            sysModule;      
    
    /* Array of Pointers to Drv_usart Module Init Data Structures. */
    DRV_USART_INIT             * modulesInitData[DRV_USART_INSTANCES_NUMBER];
    
    /* USART driver module dynamic configuration data */
    DRV_USART_DYN_CONFIG_DATA  * usartDynConfigData[DRV_USART_INSTANCES_NUMBER];
    
    /* USART driver Test cases */
    TS_DRV_USART_BASIC_READ    * tsUsartBasicRead;

} DRV_USART_FUNCTIONAL_TEST_BASIC_READ_INIT_DATA;


// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    SYS_MODULE_OBJ APP_TestDrvUsartFuncInitialize ( const SYS_MODULE_INDEX index,
                                              const SYS_MODULE_INIT * const init )

  Summary:
     MPLAB Harmony USART driver functional test initialization routine.

  Description:
    This function initializes the Harmony USART driver functional test.  It places the 
    test state machine in its initial state and prepares it to run so that its 
    Tasks function can be called.

  Precondition:
    All other system initialization routines should be called (except 
    APP_Initialize) before calling this routine (in "SYS_Initialize").

  Parameters:
    index           - index indicating module instance.
    
    init            - pointer to module's init data structure

  Returns:
    SYS_MODULE_OBJ  - Handle to sample test module object.

  Example:
    <code>
    APP_TestDrvTmrFuncInitialize();
    </code>

  Remarks:
    For test modules, both of the input parameters are ignored.
*/

SYS_MODULE_OBJ APP_TestDrvUsartBasicReadFuncInitialize ( const SYS_MODULE_INDEX index,
                                          const SYS_MODULE_INIT * const init );


/*******************************************************************************
  Function:
    void APP_TestDrvUsartFuncTasks ( SYS_MODULE_OBJ object, unsigned int index )

  Summary:
    To validate USART dynamic driver basic read functionality using 
    single hardware instance and single client

  Description:
    This routine is the USART driver functional test tasks function.  It
    defines the state machine and core logic of the Sample module test.

  Precondition:
    The system, test and application initialization functions must be called 
    (via "SYS_Initialize") before calling this routine from a system loop.

  Parameters:
    object          - Handle to the module instance.

  Returns:
    None.

  Example:
    <code>
    APP_TasksTestSample();
    </code>

  Remarks:
    For test modules, the object handle is ignored.
 */

void APP_TestDrvUsartBasicReadFuncTasks ( SYS_MODULE_OBJ object, unsigned int index );


/*************************************************************************
  Function:
    bool APP_TestDrvTmrFuncStart (  SYS_MODULE_INDEX index )
    
  Summary:
    Routine that starts the test module.
	
  Description:
    This routine starts the test module.
	
  Conditions:
    The test harness application and this test module must have been 
    initialized and "running" (i.e. the test module's tasks function must
    be called from the appropriate loop).
	
  Input:
    object          - Handle to the module instance.
	
  Return:
    true    - If the test module is successfully able to start testing.
    
    false   - If the test module is unable to start testing.
	
  Example:
    None.
	
  Remarks:
    Each test module's "Start" function is called via a pointer to beging
    running the test contained in that module.
*/

bool APP_TestDrvUsartBasicReadFuncStart ( SYS_MODULE_OBJ object );


/******************************************************************************
   Function:
    SYS_STATUS APP_TestDrvUsartFuncStatus (  SYS_MODULE_OBJ object )

  Summary:
    Gets the current status of the USART driver functional test application.

  Description:
    This function gets the current status of the USART driver test application.

  Precondition:
    None.

  Parameters:
    object          - Handle to the test app instance

  Returns:
    SYS_STATUS_ERROR            - If an error condition has occured.
    
    SYS_STATUS_UNINITIALIZED    - Before the sample test app has been 
                                  initialized.
                                  
    SYS_STATUS_BUSY             - If the sample test app is busy working.
    
    SYS_STATUS_READY            - If the sample test app is ready and 
                                  waiting for the sample module.                                  

  Example:
    None.

  Remarks:
    A module's status operation can be used to determine when any of the
    other module level operations has completed as well as to obtain general
    status of the module.  The value returned by the status routine will be
    checked after calling any of the module operations to find out when they
    have completed.

    If the status operation returns SYS_STATUS_BUSY, the previous operation
    has not yet completed. Once the status operation returns SYS_STATUS_READY,
    any previous operations have completed.

    The value of SYS_STATUS_ERROR is negative (-1). A module may define
    module-specific error values of less or equal SYS_STATUS_ERROR_EXTENDED
    (-10).

    The status function must NEVER block.

    If the status operation returns an error value, the error may be cleared by
    calling the reinitialize operation. If that fails, the deinitialize
    operation will need to be called, followed by the initialize operation to
    return to normal operations.
*/

SYS_STATUS APP_TestDrvUsartBasicReadFuncStatus ( SYS_MODULE_OBJ object );

extern TS_DRV_USART_BASIC_READ usartBasicReadTestcase[];

#endif /* _TEST_DRV_USART_BASIC_READ_MODULE_H */
/*******************************************************************************
 End of File
 */

