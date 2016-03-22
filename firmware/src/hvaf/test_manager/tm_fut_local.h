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

#include "tm_fut_if.h"

// *****************************************************************************
// *****************************************************************************
// Section: Defines
// *****************************************************************************
// *****************************************************************************

typedef void ( *RT_FUNC_CALL ) ( TM_RECEIPT receipt);

/* Enum definition for Test Manager States */
typedef enum
{
    
   TM_STATE_INIT = 0,
   TM_STATE_CONNECT,
   TM_STATE_IDLE,           
   TM_STATE_BUSY,
   TM_STATE_ERROR

}TM_STATES;

typedef struct{
    
    /* Test Manager Task State Enumeration */
    TM_STATES state;
    
    /* Flag to check the FUT & Tester COMM status */
    bool is_connected;
    
    /* TM waiting for response */
    bool is_waiting_for_response;
    
    /* Flag to check response callback status */
    bool is_response_rcvd;
    
    /* Response callback data */
    TM_RECEIPT rx_result;
    
}TM_SYS_DATA;

/* FTMP Packet details */
typedef struct
{
    bool isClass;
    FTMP_IO_OPERATION op;
    FTMP_DRV_CALLBACK ftmpcallback;  
}FTMP_PACKET_DATA;

typedef struct
{
    FTMPApdu* ftmp_tx_data;
    FTMPApdu* ftmp_rx_data;
}FTMP_CALLBACK_DATA;

typedef struct
{
    uint16_t index;
    RT_FUNC_CALL rfunc;
    
}TM_FUT_MSG_TABLE;

typedef union
{
    uint16_t tests;    
    struct
    {
        uint16_t test_lsb :8;
        uint16_t test_msb :8;
    }stTests; 
}unTest;

typedef union
{
    uint8_t testId;  
    struct
    {
        uint8_t test_id_lsb :4;
        uint8_t test_id_msb :4;
    }stTestcaseId;    
}unTestCaseId;

#endif // _TEST_MANAGER_LOCAL_H
/*******************************************************************************
 End of File
*/
