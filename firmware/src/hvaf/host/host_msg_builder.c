/*******************************************************************************
  Tester Framework Application 
  
  File Name:
    host_msg_builder.c

  Summary:
 

  Description:

 ******************************************************************************/


// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2012 released Microchip Technology Inc.  All rights reserved.

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
 ******************************************************************************/
// DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: Included Files 
// *****************************************************************************
// *****************************************************************************
#include "host_msg_builder.h"
#include "host_msg_handler.h"
#include "host_msg_response.h"

#define MAX_TX_BUFFER_SIZE 3

// *****************************************************************************
// *****************************************************************************
// Section: Function Declaration
// *****************************************************************************
// *****************************************************************************

bool HOST_COMM_SendMessage(HOST_MSG_TYPES type, HOST_RECEIPT_TYPES receipt,
                                             uint8_t* data, uint16_t data_size);
void HOST_COMM_ResetTransmitBuffer(void);

// *****************************************************************************
// *****************************************************************************
// Section: Global Variable Declaration
// *****************************************************************************
// *****************************************************************************
static HOST_MSG  host_tx_msg_queue[MAX_TX_BUFFER_SIZE];
static HOST_MSG* tx_push_msg_index = &host_tx_msg_queue[0];
static HOST_MSG* tx_pop_msg_index  = &host_tx_msg_queue[0];

static uint8_t host_tx_queue_count = 0;

static uint8_t  host_tx_msg_buf[sizeof(HOST_MSG)];
static uint16_t host_tx_msg_len = 0;

static HOST_MSG_HEADER tx_receipt_msg;
static uint8_t g_receipt_to_send = false;

static bool is_waiting_for_response = false;
static bool is_transmit_complete = true;

// *****************************************************************************
// *****************************************************************************
// Section: Function Definitions
// *****************************************************************************
// *****************************************************************************

/******************************************************************************
  Function:
    uint8_t HOST_COMM_SendMessage(HOST_MSG_TYPES type, HOST_RECEIPT_TYPES receipt,
                                             uint8_t* data, uint16_t data_size

  Description:

*/
bool HOST_COMM_SendMessage(HOST_MSG_TYPES type, HOST_RECEIPT_TYPES receipt,
                                             uint8_t* data, uint16_t data_size)
{
    /* Check if push pointer is full */
    if((host_tx_queue_count > MAX_TX_BUFFER_SIZE))
    {
        return false;
    }

    /* Add SOF & Tester Address*/
    tx_push_msg_index->m_header.start_of_packet = HOST_START_OF_PACKET_ID;
    tx_push_msg_index->m_header.info.tester_address = HOST_COMM_GetTesterAddress();

    /* Add Receipt -> New Msg/ACK/NAK/BUSY */
    tx_push_msg_index->m_header.info.host_receipt = receipt;
    tx_push_msg_index->m_header.info.res =0;

    /* Add Message Type */
    tx_push_msg_index->m_header.msg_type = type;

    /* Check if data unit to be sent */
    if(data_size == 0)
    {
        /* Since no data available, length is zero*/
        tx_push_msg_index->m_header.length = 0;
    }
    else
    {
        /* Add Length */
        tx_push_msg_index->m_header.length = data_size;

        /* Add Data to the trasmit buffer */
        memcpy(&tx_push_msg_index->m_data.data[0], data, data_size);

        /* Add Checksum */
        tx_push_msg_index->m_crc = HOST_COMM_Calculate_CRC(tx_push_msg_index->m_data.data, data_size);
    }

    tx_push_msg_index->m_eop = HOST_END_OF_PACKET_ID;

    /* Inc the push pointer */
    if(tx_push_msg_index == &host_tx_msg_queue[MAX_TX_BUFFER_SIZE-1])
    {
        tx_push_msg_index = &host_tx_msg_queue[0];
    }
    else
    {
        tx_push_msg_index++;
    }
    host_tx_queue_count++;

    return true;
}

void HOST_COMM_SendReceipt(HOST_MSG_TYPES type, HOST_RECEIPT_TYPES reply_receipt)
{
    g_receipt_to_send = true;

    tx_receipt_msg.start_of_packet = HOST_START_OF_PACKET_ID;
    tx_receipt_msg.info.tester_address = HOST_COMM_GetTesterAddress();
    tx_receipt_msg.info.host_receipt = reply_receipt;
    tx_receipt_msg.info.res =0;
    tx_receipt_msg.length = 0;
    tx_receipt_msg.msg_type = type;
}

/******************************************************************************
  Function:
 void HOST_COMM_Add_To_Transmit_Buffer(void)

  Description:

*/
void HOST_COMM_AddTransmitBuffer(void)
{
    uint16_t loop = 0;
    uint16_t len = 0;

    /* Clear the TX Buffer */
    HOST_COMM_ResetTransmitBuffer();

    /* Check if receipt to be sent */
    if(g_receipt_to_send)
    {
        /* Add Packet Header to transmit buffer */
        host_tx_msg_len = 0;

        host_tx_msg_buf[host_tx_msg_len++] = tx_receipt_msg.start_of_packet;
        host_tx_msg_buf[host_tx_msg_len++] = tx_receipt_msg.info.all;
        host_tx_msg_buf[host_tx_msg_len++] = 0;
        host_tx_msg_buf[host_tx_msg_len++] = 0;
        host_tx_msg_buf[host_tx_msg_len++] = tx_receipt_msg.msg_type;
        host_tx_msg_buf[host_tx_msg_len++] = HOST_END_OF_PACKET_ID;
    }
    /* Normal Message */
    else
    {
        host_tx_msg_len = 0;
        len = (tx_pop_msg_index->m_header.length);

        /* Add Packet Header to transmit buffer */
        host_tx_msg_buf[host_tx_msg_len++] = tx_pop_msg_index->m_header.start_of_packet;
        host_tx_msg_buf[host_tx_msg_len++] = tx_pop_msg_index->m_header.info.all;
        host_tx_msg_buf[host_tx_msg_len++] = (uint8_t)tx_pop_msg_index->m_header.length;
        host_tx_msg_buf[host_tx_msg_len++] = (uint8_t)(tx_pop_msg_index->m_header.length >> 8);
        host_tx_msg_buf[host_tx_msg_len++] = tx_pop_msg_index->m_header.msg_type;

        /* Add Data unit & Checksum */
        if(tx_pop_msg_index->m_header.length != 0)
        {
            /* Add data to transmit buffer */
            for(loop=0; loop < len; loop++)
            {
                host_tx_msg_buf[host_tx_msg_len++] = tx_pop_msg_index->m_data.data[loop];
            }

            /* Add Checksum to TX buffer */
            host_tx_msg_buf[host_tx_msg_len++] = (uint8_t)tx_pop_msg_index->m_crc;
            host_tx_msg_buf[host_tx_msg_len++] = (uint8_t)(tx_pop_msg_index->m_crc >> 8);
        }

        /* Add EOP */
        host_tx_msg_buf[host_tx_msg_len++] = tx_pop_msg_index->m_eop;

        /* Set Waiting for response flag */
        is_waiting_for_response = true;
    }

    /* Transmit the TX buffer */
    HOST_COMM_PutEvent(E_MSG_TRANSMIT);
}

bool HOST_COMM_IsWaitingforReponse(void)
{
    return is_waiting_for_response;
}

void HOST_COMM_ClearResponseWaitFlag(void)
{
    is_waiting_for_response = false;
}

HOST_MSG_TYPES HOST_COMM_GetPreviousMessageType(void)
{
    return tx_pop_msg_index->m_header.msg_type;
}

bool HOST_COMM_IsTransmitCompleted(void)
{
    return is_transmit_complete;
}

void HOST_COMM_ClearTransmitStatusFlag(void)
{
    is_transmit_complete = false;
}

/******************************************************************************
  Function:
 bool HOST_COMM_IsTransmitQueueEmpty(void)

  Description:

*/
bool HOST_COMM_IsTransmitQueueEmpty(void)
{
    /* Check anything to transmit */
    if((host_tx_queue_count != 0) ||(g_receipt_to_send))
    {
        return false;
    }
    else
    {
        return true;
    }
}

/******************************************************************************
  Function:
 void HOST_COMM_ClearTransmitBufQueue(void)

  Description:

*/
void HOST_COMM_ClearTransmitBufQueue(void)
{
    if(host_tx_queue_count != 0)
    {
        /* Check the pointer status */
        if(tx_pop_msg_index++ == &host_tx_msg_queue[MAX_TX_BUFFER_SIZE-1])
        {
            tx_pop_msg_index = &host_tx_msg_queue[0];
        }

        /* Decrement the counter */
        host_tx_queue_count--;
    }
}

/******************************************************************************
  Function:
 void HOST_COMM_ResetTransmitBuffer(void)

  Description:

*/
void HOST_COMM_ResetTransmitBuffer(void)
{
    memset(&host_tx_msg_buf[0], 0, sizeof(host_tx_msg_buf));
}

/******************************************************************************
  Function:
 void HOST_COMM_TXSetup(void)

  Description:

*/
void HOST_COMM_TXSetup(void)
{
    /* Set the flag to in-progress */
    is_transmit_complete = false;
    
    /* Enable the HOST UART TX */
    DRV_HOST_TX_Enable();

    /* Start 1st byte transmision here, next bytes will be transferred in INT */
    HOST_COMM_SendTXbyte();
}

/******************************************************************************
  Function:
 void HOST_COMM_SendTXbyte(void)

  Description:

*/
void HOST_COMM_SendTXbyte(void)
{
    static uint16_t count =0;
    
    /* Check the message length */
    if(count < host_tx_msg_len)
    {
        /* Transmit byte */
        DRV_HOST_Transmit_Byte(host_tx_msg_buf[count++]);
    }
    /* Full Message is transmitted */
    else
    {
        /* Disable HOST UART TX*/
        DRV_HOST_TX_Disable();
        /* Reset the MSG Length Counter */
        host_tx_msg_len = 0;
        count = 0;
        
        /* MSG Send Complete Flag */
        is_transmit_complete = true;

        /* Check the receipt flag */
        if(!g_receipt_to_send)
        {
            /* Set the Timer to check the response */
            DRV_HOST_TMR_Start(HOST_RESP_DELAY, HOST_COMM_TMRCallback);
        }
        else
        {
            g_receipt_to_send = false;
        }
    }
} 

/* */
/*******************************************************************************
 End of File
 */
