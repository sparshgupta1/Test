  /*******************************************************************************
  Application Header
  
  File Name:
    host_interface.h

  Summary:


  Description:

 *******************************************************************************/

//DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2011-2012 released Microchip Technology Inc.  All rights reserved.

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
//DOM-IGNORE-END

#ifndef _HOST_IF_H_
#define _HOST_IF_H_

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#include <xc.h>
#include <sys/attribs.h>

// *****************************************************************************
// *****************************************************************************
// Section: Defines
// *****************************************************************************
// *****************************************************************************

#define HOST_MAX_RETRY_COUNT        5
#define HOST_RESP_DELAY             1000
#define MAX_DATA_UNIT_LENGTH        256

#define HOST_COMM_CLOSE_CALL()            // legal C statement
#define HOST_COMM_ABORT_CALL()            // legal C statement

// *****************************************************************************
// *****************************************************************************
// Section: Type Definitions
// *****************************************************************************
// *****************************************************************************

typedef enum
{
    OPEN_COMMUNICATION =0,
    TESTER_CONFIG,
    LOG_RESULT,
    END_OF_TEST,
    STATUS_CHECK,
    ABORT_COMMAND,
    CLOSE_COMMUNICATION,
    RAW_MESSAGE,
    MAX_MSG_TYPE
}HOST_MSG_TYPES;

typedef enum
{
    HOST_NEW_MESSAGE =0,
    HOST_ACK,
    HOST_NAK,
    HOST_BUSY
}HOST_RECEIPT_TYPES;

typedef enum
{
    TESTER_IDLE=0,
    TESTER_BUSY
}TESTER_STATUS;

typedef struct
{
    uint16_t  ts_id;
    uint16_t  tc_count;
    uint16_t* tc_id;
}TS_INFO;

typedef struct
{
    bool is_tester_controlled;
    uint16_t total_ts_count;
    TS_INFO* info;
}TEST_CONFIG_DATA;

/* HOST Communication Init & Task */
void HOST_COMM_Initialize(void);
void HOST_COMM_Tasks(void);

extern bool HOST_COMM_SendMessage(HOST_MSG_TYPES type, HOST_RECEIPT_TYPES receipt,
                                             uint8_t* data, uint16_t data_size);

extern bool HOST_COMM_IsConnected(void);
extern bool HOST_COMM_GetTestConfigData(TEST_CONFIG_DATA* config);

extern void HOST_COMM_UpdateTesterStatus(TESTER_STATUS status);

extern uint16_t test_scenarios_info[100];

#endif /* _HOST_IF_H_ */

/*******************************************************************************
 End of File
*/

