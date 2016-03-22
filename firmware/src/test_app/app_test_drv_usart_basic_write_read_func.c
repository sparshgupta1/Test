/*******************************************************************************
  MPLAB Harmony Application Source File
  
  Company:
    Microchip Technology Inc.
  
  File Name:
   app_test_drv_usart_basic_write_read_func.c

  Summary:
    This file contains the source code for the MPLAB Harmony USART driver
    module's test.

  Description:
    This file contains the source code for the MPLAB Harmony application.  It 
    implements the logic of the test application's state machine.
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


// *****************************************************************************
// *****************************************************************************
// Section: Included Files 
// *****************************************************************************
// *****************************************************************************

#include "test_app/app_test_drv_usart_basic_write_read_func.h"


// *****************************************************************************
// *****************************************************************************
// Section: Local Definitions
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Test Application states

  Summary:
    Test application states enumeration

  Description:
    This enumeration defines the valid timer driver test application states.  These 
    states determine the behavior of the test at various times.
*/

typedef enum
{
    /* Wait for FTMP Communication line to be opened */
    APP_TEST_DRV_USART_FUNC_CONNECT_WAIT=0,
            
    /* Initialize the module under test, but do not start testing. */
    APP_TEST_DRV_USART_FUNC_STATE_INIT,

    /* Wait for start signal from the test harness. */
    APP_TEST_DRV_USART_FUNC_STATE_INIT_WAIT,
            
    /* Send start of config change message to Tester */
    APP_TEST_DRV_USART_FUNC_STATE_SEND_CONFIG,
            
    /* Wait for response for config message from Tester */
    APP_TEST_DRV_USART_FUNC_STATE_CONFIG_WAIT,            
            
    /* Send start of test message to Tester */
    APP_TEST_DRV_USART_FUNC_STATE_SEND_SOT,
            
    /* Wait for response for SOT from Tester */
    APP_TEST_DRV_USART_FUNC_STATE_SOT_WAIT,
      
    /* Send test case info message to Tester */
    APP_TEST_DRV_USART_FUNC_STATE_SEND_TEST_INFO,
            
    /* Wait for response for Test Case Info from Tester */        
    APP_TEST_DRV_USART_FUNC_STATE_TEST_INFO_WAIT,  
            
    /* Send Stimulus request to Tester*/
    APP_TEST_DRV_USART_FUNC_STATE_STIMULUS_REQUEST,   
            
    /* Wait for stimulus response from Tester */        
    APP_TEST_DRV_USART_FUNC_STATE_STIMULUS_WAIT,            

    /* Check drv_usart modules for initial data. */
    APP_TEST_DRV_USART_FUNC_STATE_PERFORM_TEST,               

    /* Check drv_usart module transfer status*/
    APP_TEST_DRV_USART_FUNC_STATE_CHECK_STATUS,
            
    /* Log test result. */
    APP_TEST_DRV_USART_FUNC_STATE_COMPLETED_LOG_RESULT,
            
    /* Wait for Log result command response */
    APP_TEST_DRV_USART_STATE_WAIT_FOR_LOG_RESULT,
            
    /* Test sequence Completed. */
    APP_TEST_DRV_USART_FUNC_STATE_SEND_EOT,
            
    /* Wait for EOT response from Tester  */
    APP_TEST_DRV_USART_FUNC_STATE_EOT_WAIT, 
            
    /* APP USART driver Error State */
    APP_TEST_DRV_USART_FUNC_STATE_ERROR,            

    /* Test sequence Completeded. */
    APP_TEST_DRV_USART_FUNC_STATE_COMPLETED,             

    /* App Does Nothing */
    APP_TEST_DRV_USART_FUNC_STATE_IDLE

} APP_DRV_USART_TEST_FUNC_STATES;


// *****************************************************************************
/* Sample Module Test Data

  Summary:
    Holds the application's data related to an individual drv_tmr module 
    instance.

  Description:
    This structure holds the application's data related to an individual drv_tmr 
    module instance.
 */

typedef struct _app_drv_usart_module_data
{
    /* Pointer to TMR driver's Init Data Structure. */
    DRV_USART_INIT *initData;
    

} DRV_USART_MODULE_TEST_DATA;


// *****************************************************************************
/* TMR Driver Test Application Data

  Summary:
    Holds test application data

  Description:
    This structure holds the application's data.
 */

typedef struct
{
    /* The application's current state */
    APP_DRV_USART_TEST_FUNC_STATES  state;

    /* The application's current status. */
    SYS_STATUS                      status;

    /* Flag indicating that the drv_tmr module test is running. */
    bool                            running;
    
    /* USART Driver Module Instance Data */
    DRV_USART_MODULE_TEST_DATA      module[DRV_USART_INSTANCES_NUMBER];
    
    /* Application driver handle */
    DRV_HANDLE                      handle;   
    
    /* USART driver Test cases */
    TS_DRV_USART_BASIC_WR           *usartBasicWRTCs;    

} DRV_USART_TEST_DATA;

typedef struct{
    
    /* Sub Test Id */
    char* testCaseId;
    
    /* Test Data Information */
    CLASS_DATA_ITEMS data[DRV_USART_INSTANCES_NUMBER];  
    
}DRV_USART_TEST_LIST;

// *****************************************************************************
// *****************************************************************************
// Section: Global Data Definitions
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    This structure should be initialized by the APP_Test<name>Initialize function.
    
    Application strings and buffers are be defined outside this structure.
*/

static DRV_USART_TEST_DATA testDrvUsartFunc;

/*******************************************************************************

 * Test Scenario Name: TS_DRV_USART_BASIC_WRITE_READ

 *  Summary: To test MPLAB Harmony USART dynamic driver basic WR functionality

 * Precondition: Initialize single instance of USART driver and Open a client 
    in Read/Write mode enabled in Interrupt Mode (Bare-Metal)

 * Parameters:
    testCaseId      - Test case name (string)
    
    data            - Test case data structure.
 
*/
TS_DRV_USART_BASIC_WR usartBasicWRTestcase[] =  
{
/*

 * Description: DRV_USART_Read function write and reads given number of 
	bytes from the USART PC Console/Tester.

 * Priority : High
 
 * Testing Type: Functional

*/  
    {
        .testCaseId = "USART Driver Basic WR Test case 1",
        .data = 
        { 
            { 
                .className =  DATACLASS_D, 
                .startIndex = 3, 
                .endIndex = 3, 
                .subIndexStart = 0, 
                .subIndexEnd = 0
            },  
            {
              .className =  DATACLASS_D, 
              .startIndex = 4, 
              .endIndex = 4, 
              .subIndexStart = 0, 
              .subIndexEnd = 0
            }
        },
    },    
};

/* Number of Test Cases */
static uint8_t numberOfTests = sizeof(usartBasicWRTestcase)/sizeof(TS_DRV_USART_BASIC_WR);
static uint8_t subtestId = 0;

static char rbuffer[50];

// *****************************************************************************
// *****************************************************************************
// Section: Application Local Functions
// *****************************************************************************
// *****************************************************************************


// *****************************************************************************
// *****************************************************************************
// Section: Test Interface Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    bool APP_TestDrvUsartBasicWRFuncStart ( SYS_MODULE_OBJ object )
    
  Remarks:
    See prototype in test_drv_tmr_functional.h.
*/

bool APP_TestDrvUsartBasicWRFuncStart ( SYS_MODULE_OBJ object )
{
    DRV_USART_TEST_DATA *pObj = (DRV_USART_TEST_DATA *)object;

    SYS_ASSERT(pObj == &testDrvUsartFunc, "Invalid test object");

    pObj->handle = DRV_USART_Open(0,  DRV_IO_INTENT_READWRITE | DRV_IO_INTENT_NONBLOCKING);

    pObj->running = true;
    
    return true;
}


// *****************************************************************************
// *****************************************************************************
// Section: Test Module System Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    SYS_MODULE_OBJ APP_TestDrvUsartBasicWRFuncInitialize ( const SYS_MODULE_INDEX index,
                                              const SYS_MODULE_INIT * const init )

  Remarks:
    See prototype in test_drv_usart_functional.h.
 */

SYS_MODULE_OBJ APP_TestDrvUsartBasicWRFuncInitialize ( const SYS_MODULE_INDEX index,
                                          const SYS_MODULE_INIT * const init )
{
    int i;
    DRV_USART_TEST_DATA                   *pObj        = &testDrvUsartFunc;
    SYS_MODULE_OBJ                        retvalue    = (SYS_MODULE_OBJ)&testDrvUsartFunc;
    DRV_USART_FUNCTIONAL_TEST_BASIC_WR_INIT_DATA   *initTest    = (DRV_USART_FUNCTIONAL_TEST_BASIC_WR_INIT_DATA *)init;

    SYS_ASSERT(index == 0, "Invalid drv_usart test index");

    /* Place the App state machine in its initial state. */
    pObj->state     = APP_TEST_DRV_USART_FUNC_CONNECT_WAIT;
    pObj->running   = false;

    /* Initialize the drv_tmr module data counters */
    for (i=0; i < DRV_USART_INSTANCES_NUMBER; i++)
    {
        if (NULL != initTest)
        {
            pObj->module[i].initData   = initTest->modulesInitData[i];
            
        }
        else
        {
            SYS_DEBUG_MESSAGE(SYS_ERROR_ERROR, "No initial test data provided.\n");
            retvalue = SYS_MODULE_OBJ_INVALID;
        }
    }
    
    /* Set drv_usart module tst app status. */
    if (SYS_MODULE_OBJ_INVALID == retvalue)
    {
        pObj->status = SYS_STATUS_ERROR;
    }
    else
    {
        pObj->status = SYS_STATUS_READY;
    }

    return (SYS_MODULE_OBJ)retvalue;
}


/*******************************************************************************
  Function:
    SYS_STATUS APP_TestDrvUsartBasicWRFuncStatus (  SYS_MODULE_OBJ object )

  Remarks:
    See prototype in app_test_harness.h.
*/

SYS_STATUS APP_TestDrvUsartBasicWRFuncStatus (  SYS_MODULE_OBJ object )
{
    DRV_USART_CLIENT_STATUS status;

    DRV_USART_TEST_DATA   *pObj = (DRV_USART_TEST_DATA *)object;

    SYS_ASSERT(pObj == &testDrvUsartFunc, "Invalid drv_usart test object");

    status = DRV_USART_ClientStatus(pObj->handle);

    if(DRV_USART_CLIENT_STATUS_READY == status)
    {
        pObj->status = SYS_STATUS_READY;
    }
    else if(DRV_USART_CLIENT_STATUS_BUSY == status)
    {
        pObj->status = SYS_STATUS_BUSY;
    }
    else
    {
        pObj->status = SYS_STATUS_ERROR;
    }
    
    return pObj->status;
}


/******************************************************************************
  Function:
    void APP_TestDrvUsartFuncTasks ( SYS_MODULE_OBJ object, unsigned int index )

  Remarks:
    See prototype in app.h.
 */

void APP_TestDrvUsartBasicFuncTasks1 ( SYS_MODULE_OBJ object, unsigned int index )
{
    static uint32_t len =0;
    uint32_t numBytes = 0;
    uint32_t total = 0;
    TM_TEST_INFO info;
    char* buffer;

    DRV_USART_TEST_DATA   *pObj = (DRV_USART_TEST_DATA *)object;

    SYS_ASSERT(pObj == &testDrvUsartFunc, "Invalid drv_usart test object");

    /* Take state-based actions & transition to other states as needed. */
    pObj->status = SYS_STATUS_BUSY;
    
    switch ( pObj->state )
    {
        /* Wait for FTMP Communication line to be opened */
        case APP_TEST_DRV_USART_FUNC_CONNECT_WAIT:
        {
            /* Wait until connection is established */
            if(TM_IsConnectionEstablished())
            {                
                pObj->state = APP_TEST_DRV_USART_FUNC_STATE_INIT;
            }            
            break;
        }
        
        /* Initialize the module under test, but do not start testing. */
        case APP_TEST_DRV_USART_FUNC_STATE_INIT:
        {
            if (TEST_LibraryInitialize())
            {
                pObj->state     = APP_TEST_DRV_USART_FUNC_STATE_PERFORM_TEST;
            }
            else
            {
                pObj->status    = SYS_STATUS_READY;
                pObj->state     = APP_TEST_DRV_USART_FUNC_STATE_INIT_WAIT;
            }
            break;
        }
    
        /* Wait for start signal from the test harness. */
        case APP_TEST_DRV_USART_FUNC_STATE_INIT_WAIT:
        {
            if (pObj->running)
            {
                pObj->state     = APP_TEST_DRV_USART_FUNC_STATE_SEND_CONFIG;
            }
            break;
        }
        
        case APP_TEST_DRV_USART_FUNC_STATE_SEND_CONFIG:
        {

            break;
        }
        
        case APP_TEST_DRV_USART_FUNC_STATE_CONFIG_WAIT:
        {

		
            break;
        }        
        
        case APP_TEST_DRV_USART_FUNC_STATE_SEND_SOT:
        {

            break;
        }
        
        case APP_TEST_DRV_USART_FUNC_STATE_SOT_WAIT:
        {

            break;
        }        
        
        case APP_TEST_DRV_USART_FUNC_STATE_SEND_TEST_INFO:
        {

            break;
        }
        
        case APP_TEST_DRV_USART_FUNC_STATE_TEST_INFO_WAIT:
        {

            break;
        }
        
        case APP_TEST_DRV_USART_FUNC_STATE_STIMULUS_REQUEST:
        {

            break;            
        }
        
        case APP_TEST_DRV_USART_FUNC_STATE_STIMULUS_WAIT:
        {

            break;
        }        

        /* Check drv_usart modules for initial data. */
        case APP_TEST_DRV_USART_FUNC_STATE_PERFORM_TEST:
        {


            break;
        }
        
        case APP_TEST_DRV_USART_FUNC_STATE_COMPLETED_LOG_RESULT:
        { 
                         
            break;            
        }
        
        case APP_TEST_DRV_USART_STATE_WAIT_FOR_LOG_RESULT:
        {

            break;             
        }
        
        case APP_TEST_DRV_USART_FUNC_STATE_SEND_EOT:
        {

            break;            
        } 
        
        case APP_TEST_DRV_USART_FUNC_STATE_EOT_WAIT:
        {
 
            break;
        }
                
        case APP_TEST_DRV_USART_FUNC_STATE_ERROR:
        {   
            TEST_HasPassedSubtest(false);
            pObj->state = APP_TEST_DRV_USART_FUNC_STATE_COMPLETED;
            
            break;
        }              

        /* Test sequence Completed. */
        case APP_TEST_DRV_USART_FUNC_STATE_COMPLETED:
        {         

            break;
        }
        
        /* Nothing more to do */
        case APP_TEST_DRV_USART_FUNC_STATE_IDLE:
        default:
        {
            break;
        }
    }
}
 
void APP_TestDrvUsartBasicFuncTasks2 ( SYS_MODULE_OBJ object, unsigned int index )
{
    static uint32_t len =0;
    uint32_t numBytes = 0;
    uint32_t total = 0;
    TM_TEST_INFO info;
    char* buffer;

    DRV_USART_TEST_DATA   *pObj = (DRV_USART_TEST_DATA *)object;

    SYS_ASSERT(pObj == &testDrvUsartFunc, "Invalid drv_usart test object");

    /* Take state-based actions & transition to other states as needed. */
    pObj->status = SYS_STATUS_BUSY;
    
    switch ( pObj->state )
    {
        /* Wait for FTMP Communication line to be opened */
        case APP_TEST_DRV_USART_FUNC_CONNECT_WAIT:
        {
            /* Wait until connection is established */
            if(TM_IsConnectionEstablished())
            {                
                pObj->state = APP_TEST_DRV_USART_FUNC_STATE_INIT;
            }            
            break;
        }
        
        /* Initialize the module under test, but do not start testing. */
        case APP_TEST_DRV_USART_FUNC_STATE_INIT:
        {
            if (TEST_LibraryInitialize())
            {
                pObj->state     = APP_TEST_DRV_USART_FUNC_STATE_PERFORM_TEST;
            }
            else
            {
                pObj->status    = SYS_STATUS_READY;
                pObj->state     = APP_TEST_DRV_USART_FUNC_STATE_INIT_WAIT;
            }
            break;
        }
    
        /* Wait for start signal from the test harness. */
        case APP_TEST_DRV_USART_FUNC_STATE_INIT_WAIT:
        {
            if (pObj->running)
            {
                pObj->state     = APP_TEST_DRV_USART_FUNC_STATE_SEND_CONFIG;
            }
            break;
        }
        
        case APP_TEST_DRV_USART_FUNC_STATE_SEND_CONFIG:
        {

            break;
        }
        
        case APP_TEST_DRV_USART_FUNC_STATE_CONFIG_WAIT:
        {

		
            break;
        }        
        
        case APP_TEST_DRV_USART_FUNC_STATE_SEND_SOT:
        {

            break;
        }
        
        case APP_TEST_DRV_USART_FUNC_STATE_SOT_WAIT:
        {

            break;
        }        
        
        case APP_TEST_DRV_USART_FUNC_STATE_SEND_TEST_INFO:
        {

            break;
        }
        
        case APP_TEST_DRV_USART_FUNC_STATE_TEST_INFO_WAIT:
        {

            break;
        }
        
        case APP_TEST_DRV_USART_FUNC_STATE_STIMULUS_REQUEST:
        {

            break;            
        }
        
        case APP_TEST_DRV_USART_FUNC_STATE_STIMULUS_WAIT:
        {

            break;
        }        

        /* Check drv_usart modules for initial data. */
        case APP_TEST_DRV_USART_FUNC_STATE_PERFORM_TEST:
        {


            break;
        }
        
        case APP_TEST_DRV_USART_FUNC_STATE_COMPLETED_LOG_RESULT:
        { 
                         
            break;            
        }
        
        case APP_TEST_DRV_USART_STATE_WAIT_FOR_LOG_RESULT:
        {

            break;             
        }
        
        case APP_TEST_DRV_USART_FUNC_STATE_SEND_EOT:
        {

            break;            
        } 
        
        case APP_TEST_DRV_USART_FUNC_STATE_EOT_WAIT:
        {
 
            break;
        }
                
        case APP_TEST_DRV_USART_FUNC_STATE_ERROR:
        {   
            TEST_HasPassedSubtest(false);
            pObj->state = APP_TEST_DRV_USART_FUNC_STATE_COMPLETED;
            
            break;
        }              

        /* Test sequence Completed. */
        case APP_TEST_DRV_USART_FUNC_STATE_COMPLETED:
        {         

            break;
        }
        
        /* Nothing more to do */
        case APP_TEST_DRV_USART_FUNC_STATE_IDLE:
        default:
        {
            break;
        }
    }
}

/*******************************************************************************
 End of File
 */

