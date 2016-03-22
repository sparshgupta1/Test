  /*******************************************************************************
  Application Header
  
  File Name:
    host_msg_builder.h

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

#ifndef _HOST_COMM_BUILDER_H_
#define _HOST_COMM_BUILDER_H_

#include "host_common.h"

// *****************************************************************************
// *****************************************************************************
// Section: Type Definitions
// *****************************************************************************
// *****************************************************************************
// *****************************************************************************


// *****************************************************************************
// *****************************************************************************
// Section: Functions
// *****************************************************************************
// *****************************************************************************
void HOST_COMM_SendReceipt(HOST_MSG_TYPES type,
                                    HOST_RECEIPT_TYPES reply_receipt);

void HOST_COMM_TXSetup(void);
void HOST_COMM_SendTXbyte(void);
void HOST_COMM_ClearTransmitBufQueue(void);
void HOST_COMM_AddTransmitBuffer(void);
bool HOST_COMM_IsTransmitQueueEmpty(void);
bool HOST_COMM_IsWaitingforReponse(void);
void HOST_COMM_ClearResponseWaitFlag(void);
HOST_MSG_TYPES HOST_COMM_GetPreviousMessageType(void);
bool HOST_COMM_IsTransmitCompleted(void);
void HOST_COMM_ClearTransmitStatusFlag(void);

#endif /* _HOST_COMM_BUILDER_H_ */

/*******************************************************************************
 End of File
*/

