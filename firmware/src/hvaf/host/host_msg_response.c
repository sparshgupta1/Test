/*******************************************************************************
  Tester Framework Application 
  
  File Name:
    host_msg_response.c

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
#include "host_msg_response.h"
#include "host_msg_handler.h"

// *****************************************************************************
// *****************************************************************************
// Section: Local Variable Declaration
// *****************************************************************************
// *****************************************************************************

typedef enum
{
   HOST_RX_MSG_SOF =0,
   HOST_RX_MSG_INFO,
   HOST_RX_MSG_GET_LENGTH,
   HOST_RX_MSG_GET_TYPE,
   HOST_RX_MSG_DATA_RECEVING,
   HOST_RX_MSG_CRC,
   HOST_RX_MSG_EOP,
   HOST_RX_MSG_IDLE
}HOST_DECODER_STATES;

static HOST_DECODER_STATES rx_decoder_state = HOST_RX_MSG_SOF;
static uint8_t is_first_call = false;

// *****************************************************************************
// *****************************************************************************
// Section: Extern Variable Declaration
// *****************************************************************************
// *****************************************************************************

HOST_MSG g_host_rx_msg;
static uint8_t t_addr = 0;

// *****************************************************************************
// *****************************************************************************
// Section: Function Definitions
// *****************************************************************************
// *****************************************************************************

/******************************************************************************
  Function:
    void HOST_COMM_SaveRXbyte(uint8_t rx_byte)

  Description:

*/
void HOST_COMM_SaveRXbyte(uint8_t rx_byte)
{
    static uint8_t length_lsb_rcvd = false;
    static uint8_t crc_lsb_rcvd = false;
    static uint16_t count_ptr = 0;

    switch(rx_decoder_state)
    {
        /* Decode SOF */
        case HOST_RX_MSG_SOF:
        {
            /* check if the start of packet has received */
            if(rx_byte == HOST_START_OF_PACKET_ID)
            {
                rx_decoder_state = HOST_RX_MSG_INFO;

                /* Reset the variables */
                length_lsb_rcvd = false;
                crc_lsb_rcvd = false;
                count_ptr = 0;

            }
            /* Discard the byte rcvd, Wait for SOF */
            else
            {
                rx_decoder_state = HOST_RX_MSG_SOF;
            }
            break;
        }
        /* Decode Tester Address, Host Receipt Info */
        case HOST_RX_MSG_INFO:
        {
            g_host_rx_msg.m_header.info.all = rx_byte;

            if(!is_first_call)
            {
                t_addr = g_host_rx_msg.m_header.info.tester_address;
                is_first_call = true;
            }

            rx_decoder_state = HOST_RX_MSG_GET_LENGTH;
            break;
        }
        /* Decode Number of bytes */
        case HOST_RX_MSG_GET_LENGTH:
        {
            if(!length_lsb_rcvd)
            {
                g_host_rx_msg.m_header.length = (rx_byte << 8);
                length_lsb_rcvd = true;

                rx_decoder_state = HOST_RX_MSG_GET_LENGTH;
            }
            else
            {
                g_host_rx_msg.m_header.length |= rx_byte;
                length_lsb_rcvd = false;
                rx_decoder_state = HOST_RX_MSG_GET_TYPE;
            }           
            break;
        }
        /* Decode Message Type */
        case HOST_RX_MSG_GET_TYPE:
        {
            g_host_rx_msg.m_header.msg_type = rx_byte;

            /* Check if the Data Unit to be received */
            if(g_host_rx_msg.m_header.length != 0)
            {
                rx_decoder_state = HOST_RX_MSG_DATA_RECEVING;
            }
            else
            {
                rx_decoder_state = HOST_RX_MSG_EOP;
            }
            break;
        }
        /* Start receving the data unit */
        case HOST_RX_MSG_DATA_RECEVING:
        {
            g_host_rx_msg.m_data.data[count_ptr++] = rx_byte;

            if(count_ptr == (g_host_rx_msg.m_header.length))
            {
                rx_decoder_state = HOST_RX_MSG_CRC;
            }
            else
            {
                rx_decoder_state = HOST_RX_MSG_DATA_RECEVING;
            }
            break;
        }
        /* Start receving the CRC unit */
        case HOST_RX_MSG_CRC:
        {
            if(!crc_lsb_rcvd)
            {
                g_host_rx_msg.m_crc = (rx_byte << 8);
                crc_lsb_rcvd = true;

                rx_decoder_state = HOST_RX_MSG_CRC;
            }
            else
            {
                g_host_rx_msg.m_crc |= rx_byte;
                crc_lsb_rcvd = false;
                rx_decoder_state = HOST_RX_MSG_EOP;
            }
            break;
        }
        case HOST_RX_MSG_EOP:
        {
            /* check if the end of packet has received */
            g_host_rx_msg.m_eop = rx_byte;

            HOST_COMM_PutEvent(E_MSG_RCVD);
            rx_decoder_state = HOST_RX_MSG_IDLE;
            break;
        }
        case HOST_RX_MSG_IDLE:
        {
            /* Reset the variables */
            length_lsb_rcvd = false;
            crc_lsb_rcvd = false;
            count_ptr = 0;
            
            rx_decoder_state = HOST_RX_MSG_IDLE;
            break;
        }
    }
}   

void HOST_COMM_RX_Ready(void)
{
    /* start receiving sof message from host */
    rx_decoder_state = HOST_RX_MSG_SOF;
}


HOST_MSG* HOST_COMM_GetReceivedMessage(void)
{
    return (HOST_MSG*) &g_host_rx_msg;
}


uint8_t HOST_COMM_GetTesterAddress(void)
{
    return t_addr;
}

/*******************************************************************************
 End of File
 */
