/*************************************************************************
Test Manager Interface Header Definitions

  Company:
    Microchip Technology Inc.
	
  File Name:
    test_manager_if.h
	
  Summary:
    This file aggregates all of the Test Manger interface headers.
	
  Description:
    Test Manger Interface Header
    This file aggregates all of the Test Manger interface headers so that
    module (tester/fut) code only needs to include this one single header to obtain
    prototypes and definitions for all the Test Manger interfaces.
	  
  Remarks:
                              
  *************************************************************************/
  
#ifndef _TEST_MANAGER_IF_H
#define _TEST_MANAGER_IF_H

// *****************************************************************************
// *****************************************************************************
// Section: Included FTMP Module Headers Files
// *****************************************************************************
// *****************************************************************************

#include <xc.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include <sys/attribs.h>

#include "ftmp_if.h"
#include "ftmp_common.h"
#include "handler/ftmp_handler.h"
#include "data_class/data_class.h"

// *****************************************************************************
// *****************************************************************************
// Section: Defines
// *****************************************************************************
// *****************************************************************************

/* Test Manager FTMP Send Message result */
typedef enum{
    
    TM_FAILURE = 0,
    TM_SUCCESS,
    TM_UNKNOWN
}TM_STATUS;

/* Test Manager FTMP Send Message delivery receipt */
typedef enum
{
    TM_ACK = 0,
    TM_NAK,
    TM_WAIT,
    TM_ERROR
}TM_RECEIPT;

/* Test Manager Log Result ENUM */
typedef enum{
    TM_PASS = 0,
    TM_FAIL,
    TM_TESTER
}TM_LOG_RESULT;

typedef struct
{
   uint16_t test_scenario;
   uint8_t test_case_id;
   uint8_t test_data_len;
   CLASS_DATA_ITEMS* test_data;   
}TM_TEST_INFO;

/* FTMP System Initialize & Task routines */
void TM_FUT_Init(void);
void TM_FUT_Task(void);

/* Returns true if the connection between FUT and Tester is established.
*/
bool TM_IsConnectionEstablished(void);

/* Returns delivery note from Tester for the message sent .
*/
TM_RECEIPT TM_GetResponseStatus(void);

/* Transmits the Log result to Tester 

* result - Test case result decided by the FUT
* returns the message successfully sent or not.
*/
bool TM_LogResulttoTester(TM_LOG_RESULT result);

/* Transmits the Test Case Information to Tester 

* info - Test Scenario index, Test case id & data items
* returns the message successfully added or not.
*/
bool TM_SendTestCaseInfo(TM_TEST_INFO info);

/* Transmits the FTMP Command Message 

* command     - FTMP Command
* returns the message successfully sent or not.
*/
TM_STATUS TM_SendFTMPCommand(FTMP_COMMAND_CLASS command);

/* Transmits the FTMP Data Class Message 

* Class         - FTMP Class
* index_start   - FTMP Index start id associated with class
* index_end     - FTMP Index end id associated with class
* returns the message successfully sent or not.
*/
TM_STATUS TM_SendFTMPDataClass(FTMP_CLASS_NAMES class,
                                    int index_start, int index_end);

/* Transmits the FTMP Extended Data Class Message 

* Class             - FTMP Class
* index_start       - FTMP Index start id associated with class
* index_end         - FTMP Index end id associated with class
* sub_index_start   - FTMP Index sub start id associated with index_start
* sub_index_end     - FTMP Index sub end id associated with index_end
* returns the message successfully sent or not.
*/
TM_STATUS TM_SendFTMPExtDataClass(FTMP_CLASS_NAMES class, \
                    int index_start,int index_end, int sub_index_start, \
                    int sub_index_end);

/* Adds the FTMP Peripheral Command Message 

* index     - FTMP Peripheral Command
* sub_index - Peripheral sub index
* returns the message successfully added or not.
*/
TM_STATUS TM_SendFTMPPeripheralClass(uint16_t index, uint8_t sub_index);

/* Sets the FTMP Multi Class Packet to active
*/
void TM_FTMPMultiClassSelect(void);

/* Sets the FTMP Multi Class Packet to de-active
*/
void TM_FTMPMultiClassDeSelect(void);

/* Test Manager call back routine invoked by FTMP task upon receiving reply 

* ins_ptr - pointer to application specific data. This can be NULL.
* request_data_ptr - Pointer to the FTMP PDU to transmit.
* response_data_ptr - Pointer to the FTMP response packet.

*/
void TM_Callback( void *ins_ptr,FTMPApdu *request_data_ptr,\
                                      FTMPApdu *response_data_ptr);

#endif // _TEST_MANAGER_IF_H
/*******************************************************************************
 End of File
*/
