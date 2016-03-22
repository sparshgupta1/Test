  /*******************************************************************************
  Application Header
  
  File Name:
    host_common.h

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

#ifndef _HOST_COMMON_H_
#define _HOST_COMMON_H_

#include "host_if.h"
#include "driver/tmr/drv_host_tmr.h"

// *****************************************************************************
// *****************************************************************************
// Section: Defines
// *****************************************************************************
// *****************************************************************************

#define CLK_FREQUENCY           80000000
#define HOST_START_OF_PACKET_ID 0xF0
#define HOST_END_OF_PACKET_ID   0x0F
#define CRC_LENGTH              2

// *****************************************************************************
// *****************************************************************************
// Section: Type Definitions
// *****************************************************************************
// *****************************************************************************

typedef union
{
    uint8_t all;
    
    struct
    {
        uint8_t tester_address          :4;
        HOST_RECEIPT_TYPES host_receipt :2;
        uint8_t res                     :2;
    };
        
}MSG_INFO;

typedef struct
{
    uint8_t start_of_packet;
    MSG_INFO info;
    uint16_t length;
    HOST_MSG_TYPES msg_type;
}HOST_MSG_HEADER;

typedef	struct
{
    uint8_t data[MAX_DATA_UNIT_LENGTH];
}HOST_MSG_DATA_UNIT;

typedef struct
{
    HOST_MSG_HEADER m_header;
    HOST_MSG_DATA_UNIT m_data;
    uint16_t m_crc;
    uint8_t m_eop;
}HOST_MSG;

typedef union
{
    struct
    {
        uint8_t ping_duration : 3;
        uint8_t exec_ctrl     : 1;
        uint8_t res           : 4;
    };
    struct
    {
        uint8_t all           :8;
    };
}HOST_TEST_CONFIG;

#endif /* _HOST_COMM_H_ */

/*******************************************************************************
 End of File
*/

