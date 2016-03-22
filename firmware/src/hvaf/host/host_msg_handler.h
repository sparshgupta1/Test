  /*******************************************************************************
  Application Header
  
  File Name:
    host_msg_handler.h

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

#ifndef _HOST_MSG_HANDLER_H_
#define _HOST_MSG_HANDLER_H_

#include "host_common.h"

/* Host Communication Mode */
#ifdef _HOST_COMM_UART
#include "driver/usart/drv_host_usart.h"
#endif

/* Host Timer Driver */
#include "driver/tmr/drv_host_tmr.h"

/* Enum Definition for HOST events */
typedef enum
{
    NO_EVENTS = 0,
    E_MSG_RCVD,
    E_MSG_TRANSMIT,
    E_MSG_PROCESSED,
    E_IDLE,
    E_ABORT,
    E_CLOSE,
    E_MAX_EVENTS        
}HOST_EVENT;

/* Strtuct for Events & Action based host design*/
typedef struct
{
    HOST_EVENT events;
    void (*Action) (void);
}HOST_COMM_EVENT_HANDLER;

// *****************************************************************************
// *****************************************************************************
// Section: Function Definitions 
// *****************************************************************************
// *****************************************************************************

/* HOST Put and Get events interface */
void HOST_COMM_PutEvent(HOST_EVENT event);
HOST_EVENT HOST_COMM_GetEvent(void);

/* Function to calculate CRC */
uint16_t HOST_COMM_Calculate_CRC(uint8_t* data,uint16_t data_size);

/* Timer callback function */
extern void HOST_COMM_TMRCallback(void);

/* HOST Event Handler variables */
extern HOST_COMM_EVENT_HANDLER g_event_handler[E_MAX_EVENTS];

#endif /* _HOST_MSG_HANDLER_H_ */

/*******************************************************************************
 End of File
*/

