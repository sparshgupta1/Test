/*************************************************************************
Test Manager Local Header Interface Header Definitions

  Company:
    Microchip Technology Inc.
	
  File Name:
    test_manager_local.h
	
  Summary:
    This file aggregates all of the Test Manager Local Headers.
	
  Description:
    FTMP Interface Header
    This file aggregates all of the Test Manager Local Header so that
    module (tester/fut) code only needs to include this one single header to obtain
    prototypes and definitions for all the Test Manager Local Header interfaces.
	  
  Remarks:
                              
  *************************************************************************/
  
#ifndef _TEST_MANAGER_LOCAL_H
#define _TEST_MANAGER_LOCAL_H

// *****************************************************************************
// *****************************************************************************
// Section: Included FTMP Module Headers Files
// *****************************************************************************
// *****************************************************************************

#include "tm_tester_if.h"
#define MAX_NO_MODULES     3 //maximum number of buffers for one testcase;
// *****************************************************************************
// *****************************************************************************
// Section: Defines
// *****************************************************************************
// *****************************************************************************
typedef enum{
	TM_FAILURE = 0,
	TM_SUCCESS,
	TM_UNSUPPORTED,
	TM_ERROR
}TM_STATUS;
/* Enum definition for Test Manager States */
typedef enum
{
    
   TM_STATE_INIT = 0,
   TM_STATE_CONNECT_WAIT,
   TM_STATE_IDLE_LOOP,           
   TM_STATE_BUSY,
   TM_STATE_ERROR

}TM_STATES;

typedef enum
{
   TM_TC_PASS = 0,
   TM_TC_FAIL,
   TM_TC_UNTESTED,           
}TM_TC_RESULT;

typedef struct{
    
    /* Test Manager Task State Enumeration */
    TM_STATES state;
    
    /* Flag to check the FUT & Tester COMM status */
    bool is_connected;
    
    /* TM waiting for requests */
    //bool is_waiting_for_request;
    
    /* Flag to check requests callback status */
    bool is_request_rcvd;
    
    /* Request callback data */
//    TM_RX_RESULT rx_result;
    
}TM_SYS_DATA;

typedef struct{
    /* ID for current Peripheral*/
	uint8_t PeripheralID; 

    /* ID for current instance of the peripheral*/
	uint8_t InstanceID; 

    /*length of the buffer*/
    uint32_t length;
    
    /*pointer to buffer*/
    char *BufferPtr;
}TM_MODULE;
typedef struct{
	/* Configuration/Scenario for the current test case*/
	uint8_t Config; 
	
    /* ID for the current test Scenario*/
	uint16_t ScenarioID; 

	/* ID for the current test case*/
	uint8_t TestCaseID; 

	/* Buffer information in current test. Currently only 3 supported*/
	TM_MODULE ModulesID[MAX_NO_MODULES]; 
    uint8_t BufferIndex;
	/* start of Test for the current test case*/
	bool SOT;

	/* End of Test for the current test case*/
	bool EOT;
	
	/* Log Test result for the current test case*/
	bool Log_result;

    /*Result of the test case */
    TM_TC_RESULT TCResult;
}TM_TEST_CASE_INFO;

#endif // _TEST_MANAGER_LOCAL_H
/*******************************************************************************
 End of File
*/
