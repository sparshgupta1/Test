/******************************************************************************
   Header file for Stimulus Data Manager (SDM) Data Types.

  Company:
    Microchip Technology Inc.
	
  File Name:
    sdm_datatype.h
	
  Summary:
    This file aggregates all of the SDM data types declarations.
	
  Description:
    SDM Data Types Header
	  
  Remarks:
                              
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

#ifndef _SDM_DATA_TYPES_H
#define _SDM_DATA_TYPES_H
// *****************************************************************************
// *****************************************************************************
// Section: Included SDM Module Headers Files
// *****************************************************************************
// *****************************************************************************
#include "tm_tester_local.h"
#include "system/common/sys_module.h"

// *****************************************************************************
// *****************************************************************************
// Section: Macro Definitions
// *****************************************************************************
// *****************************************************************************
#ifndef MAX_NUM_STIMULUS_TASKS
    #define MAX_NUM_STIMULUS_TASKS         2
#endif
// *****************************************************************************
// *****************************************************************************
//Section: Type Definitions
// *****************************************************************************
// *****************************************************************************
/*******************************************************************************
 * SDM Error Codes

  Summary:
    SDM Error Code enumeration

  Description:
    This enumeration defines the valid SDM Error Codes.
*******************************************************************************/
typedef enum
{
    SDM_SUCCESS,

    SDM_FAILURE,
    
    SDM_INVALID_TC_CONFIG_ID,
            
    SDM_INVALID_TC_CONFIG,
      
    SDM_INVALID_TC_DATA_ID,
    
    SDM_INVALID_TC_SCENARIO_ID,
            
    SDM_INVALID_TC_DATA,

    SDM_INVALID_TC_CALLBACK,
            
    SDM_NO_CONFIG,
    
    SDM_TEST_IN_PROGRESS,
            
} SDM_ERROR_CODES;

/*******************************************************************************
 * Application states

  Summary:
    Application states enumeration

  Description:
    This enumeration defines the valid application states.  These states
    determine the behavior of the application at various times.
*******************************************************************************/

typedef enum
{
    /* In this state, the SDM initialize its data structures */
    SDM_INIT,
            
    /* The SDM waits for the trigger from Tester */
    SDM_IDLE,            

    /* In this state, the SDM initializes the requested peripheral */
    SDM_PERIPHERAL_INIT,
           
    /* In this state, SDM Triggers Peripheral Driver Tx/Rx Call */  
    SDM_STIMULUS_START,
    
    /* In this state, SDM updates the result of the Test to Tester */ 
    SDM_STIMULUS_END,
            
    /* De-Initialize the Peripheral */
    SDM_PERIPHERAL_DEINIT,            
            
    /* This state indicates an error has occurred. */
    SDM_ERROR,
            
} SDM_STATES;

/*******************************************************************************
 * SDM Operation Event

  Summary:
    Different SDM Events enumeration

  Description:
    This enumeration defines the valid stimulus events.  These events
    determine which operation has completed successfully.
*******************************************************************************/
typedef enum
{
    /* Tester Config Request */
    SDM_CONFIG_REQUEST,
            
    /* Tester Stimulus Request */
    SDM_STIMULUS_REQUEST,
    
    /* SDM Config Complete  */
    SDM_STIMULUS_CONFIG_COMPLETE,
            
    /* SDM Config Complete  */
    SDM_STIMULUS_IN_PROGRESS,
            
    /* There was an error while processing the buffer transfer request. */
    SDM_STIMULUS_ERROR,
            
    SDM_UNKNOWN_REQUEST,
            
} SDM_STIMULUS_EVENT;

/*******************************************************************************
 * SDM Driver Event

  Summary:
    Different SDM Driver Events enumeration

  Description:
    This enumeration defines the valid driver events.  These events
    determine which stimulus operation has completed successfully.
*******************************************************************************/
typedef enum
{
    /* SDM Config Complete  */
    SDM_DRV_TASK_IN_PROGRESS,
    
    /* Stimulus Complete Flag */
    SDM_DRV_STIMULUS_COMPLETE,
            
    /* All data from or to the buffer was transferred successfully. */
    SDM_DRV_SEND_COMPLETE,

    /* All data from or to the buffer was Received successfully. */
    SDM_DRV_RECEIVE_COMPLETE,
            
    /* There was an error while processing the buffer transfer request. */
    SDM_DRV_ERROR,
            
} SDM_DRV_CALLBACK;


/* SDM Call Back to Test Manager */
typedef void ( *SDM_CALLBACK ) ( SDM_STIMULUS_EVENT sdmEvent, bool bResult);

//typedef void ( *DRV_CALLBACK ) ( SDM_DRV_CALLBACK sdmCallback, bool bResult );
typedef void ( *DRV_CALLBACK ) ( void );

/* SDM Event Handler */
typedef void ( *SDM_EVENT ) ( SDM_STIMULUS_EVENT sdmEvent );

/*******************************************************************************
  Function:
    SYS_MODULE_OBJ TEST_<MODULE>_Initialize) (
                        const SYS_MODULE_INDEX index,
                        const SYS_MODULE_INIT * const init )

  Summary:
    Pointer to a routine that initializes a test module.

  Description:
    This data type is a pointer to a routine that initializes a test module.

  Precondition:
    The system and harness initialization must have been completed before
    the harness state machine will call the initialization routine for any 
    tests.

  Parameters:
    index           - Identifier for the test instance to be initialized

    init            - Pointer to the data structure containing any data
                      necessary to initialize the test. This pointer may
                      be null if no data is required and default initialization
                      is to be used.

  Returns:
    A handle to the instance of the test module that was initialized.  This
    handle is a necessary parameter to all of the other harness level routines
    for this test.

  Remarks:
    This function will only be called once per test instance when the harness
    is ready to initialize the test instance.
*/

typedef SYS_MODULE_INITIALIZE_ROUTINE   TEST_MODULE_INITIALIZE_ROUTINE;


/*******************************************************************************
  Function:
    void TEST_<MODULE>_Tasks ( SYS_MODULE_OBJ object, unsigned int index )

  Summary:
    Pointer to a routine that performs the tasks necessary to maintain the state
    machine of a test module system module.

  Description:
    This data type is a pointer to a routine that performs the tasks necessary
    to maintain the state machine of a test module module.

  Precondition:
    The system and harness initialization must have been completed and the 
    test's initialization routine called before the harness will call any of the 
    test's tasks routines.

  Parameters:
    object          - Handle to the test instance object
    
    index           - Index identifying which tasks function is being called.
                      This index can be used to identify if a single task 
                      function is called from a different tasks context.

  Returns:
    None.

  Example:
    None.

  Remarks:
    A test module can have one or more (up to TEST_HARNESS_MAX_NUM_TASKS)
    tasks functions.
*/

typedef void (* TEST_MODULE_TASKS_ROUTINE) ( SYS_MODULE_OBJ object, 
                                             uint32_t index );


/*******************************************************************************
  Function:
    SYS_STATUS TEST_<MODULE>_Status (  SYS_MODULE_OBJ object )

  Summary:
    Pointer to a routine that gets the current status of a test module.

  Description:
    This data type is a pointer to a routine that gets the current status of a
    test module.

  Precondition:
    The system and harness initialization must have (and will be) completed and 
    the test module's initialization routine will have been called before the 
    harness will call the status routine for a test.

  Parameters:
    object          - Handle to the module instance

  Returns:
    One of the possible status codes from SYS_STATUS, extended to include:
    
    SYS_STATUS_TEST_COMPLETED - Indicates the test has completed.

  Example:
    None.

  Remarks:
    A test's status operation can be used to determine when the test is busy or
    has completed as well as to obtain general status of the test.
    
    If the status operation returns SYS_STATUS_BUSY, the previous operation
    has not yet completed. Once the status operation returns SYS_STATUS_READY,
    any previous operations have completed.

    The value of SYS_STATUS_ERROR is negative (-1). A module may define
    module-specific error values of less or equal SYS_STATUS_ERROR_EXTENDED
    (-10).

    The status function must NEVER block.

    If the status operation returns an error value the test has failed.
*/

typedef SYS_MODULE_STATUS_ROUTINE   TEST_MODULE_STATUS_ROUTINE;


/*******************************************************************************
  Function:
    bool TEST_<MODULE>_Start (  SYS_MODULE_INDEX index )
    
  Summary:
    Pointer to a routine that starts the test module.
	
  Description:
    This is a pointer to a routine that starts the test application.
	
  Conditions:
    The test harness application and the test application must have been 
    initialized and "running" (i.e., the test applications tasks function must
    be called from the test harness's state machine).
	
  Input:
    object  -  Object handle to the module instance
	
  Return:
    true    - If the test module is successfully able to start testing.
    
    false   - If the test module is unable to start testing.
	
  Example:
    None.
	
  Remarks:
    Each test module's "Start" function is called via a pointer to begin
    running the test contained in that module.
*/

typedef void (* TEST_MODULE_START_FUNCTION) (TM_TEST_CASE_INFO *object, 
                                                      DRV_CALLBACK drvCallback);

/*******************************************************************************
  Function:
    bool TEST_<MODULE>_Verify (  SYS_MODULE_INDEX index )
    
  Summary:
    Pointer to a routine that verify the test module.
	
  Description:
    This is a pointer to a routine that verify the test data.
	
  Conditions:

  Input:
    object  -  Object handle to the module instance
	
  Return:
    TM_TC_PASS   - If the test data matches.
    
    TM_TC_PASS   - If the test data does not matche.
	
  Example:
    None.
	
  Remarks:
    Each test module's "Verify" function is called via a pointer to verify
    the test data.
*/
typedef TM_TC_RESULT (* TEST_MODULE_VERIFY_FUNCTION) (void);

/*******************************************************************************
  Function:
    bool TEST_<MODULE>_Reset (  SYS_MODULE_INDEX index )
    
  Summary:
    Pointer to a routine that reset the test module.
	
  Description:
    This is a pointer to a routine that reset the test data.
	
  Conditions:

  Input:
    object  -  Object handle to the module instance
	
  Return:
    None.
	
  Example:
    None.
	
  Remarks:
    Each test module's "Reset" function is called via a pointer to reset
    the module under test.
*/
typedef void (* TEST_MODULE_RESET_FUNCTION) (void);


/*******************************************************************************
 * SDM STIMULUS Data

  Summary:
    Holds data necessary to send, receive stimulus and run a single test.

  Description:
    This structure holds the data necessary to send, receive stimulus and run 
    a single test.
*******************************************************************************/

typedef struct _stimulus_data
{
    /* Pointer to test name string. */
    char *                          name;
    
    /* Pointer to test's initialize routine. */
    TEST_MODULE_INITIALIZE_ROUTINE  initialize;

    /* Pointer to test's start routine. */
    TEST_MODULE_START_FUNCTION      start;
    
    /* Pointer to test's tasks routine. */
    TEST_MODULE_TASKS_ROUTINE       task[MAX_NUM_STIMULUS_TASKS];

    /* Pointer to test's status routine. */
    TEST_MODULE_STATUS_ROUTINE      status;
    
    /* pointer to verify routine */
    TEST_MODULE_VERIFY_FUNCTION     verify;

    /* pointer to reset routine */
    TEST_MODULE_RESET_FUNCTION      reset;
    
} STIMULUS_DATA;


// *****************************************************************************
/* Configuration Data

  Summary:
    Holds data necessary to parameters to configure and run the stimulus driver.

  Description:
    This structure holds the data necessary to parameters to configure and run the stimulus driver.
*/

typedef struct _stimulus_config_data
{
    /* Pointer to configuration name string. */
    char *                          name;

    /* Module Instance Number */
    SYS_MODULE_INDEX                instance;
    
	/* Stimulus Configuration List */
    SYS_MODULE_INIT                *ConfigData;

} STIMULUS_CONFIG_DATA;

// *****************************************************************************
/* Stimulus Initialization Data

  Summary:
    Holds the Stimulus initialization data.

  Description:
    This structure holds the stimulus initialization data.
*/

typedef struct _stimulus_init_data
{
    /* Pointer to config data array */
    STIMULUS_CONFIG_DATA    *config;
    
    /* Number of Configurations */
    uint32_t                totalConfigs;
    
    /* Number of test cases */
    uint32_t                totalTestCases;
    
    /* Number of Scenarios */
    uint32_t                totalScenarios;

    /* Pointer to test data array. */
    STIMULUS_DATA           *tests;

} STIMULUS_INIT_DATA;



typedef struct  _tester_sdm_obj   
{ 
    /* Test Case Identifier */
    SDM_STATES sdmState;
    
    /* Request for Configuration Received  */
    bool bConfigRequest;
            
    /* Request for Stimulus Received  */
    bool bStimulusRequest;
    
    /* Stimulus Complete */
    bool bConfigComplete;
    
    /* Stimulus is in Progress */
    bool bStimulusInProgress;
    
    /* Stimulus Complete */
    bool bStimulusComplete;
    
    /* SDM Event*/
    SDM_EVENT sdmEvent;
    
    /* SDM Time out Counter */
    uint32_t sdmTimer;

    /* Call back to Tester after configuration */
    SDM_CALLBACK callbackConfig;
    
     /* Call back to Tester after stimulus */
    DRV_CALLBACK callbackStimulus;
    
    /* Test Scenario & Test Case Details */
    STIMULUS_INIT_DATA sdmStimulusData;
    
} SDM_OBJ;


// *****************************************************************************
/* SDM Test COnfiguration Data Object

  Summary:
    This Object is used to pass the configuration from Tester to SDM.

  Description:
    This Object is used to pass the configuration from Tester to SDM.

  Remarks:
    None.
*/
typedef struct _sdm_tc_config_obj 
{ 
    /* Configuration Index */
    uint32_t iConfigId;
    
} SDM_TC_CONFIG_OBJ;



#endif // _SDM_DATA_TYPES_H
/*******************************************************************************
 End of File
*/

