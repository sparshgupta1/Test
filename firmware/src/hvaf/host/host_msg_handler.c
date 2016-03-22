/*******************************************************************************
  Tester Framework Application 
  
  File Name:
    host_msg_handler.c

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
#include "host_msg_handler.h"
#include "host_msg_response.h"
#include "host_msg_builder.h"

// *****************************************************************************
// *****************************************************************************
// Section: Macros
// *****************************************************************************
// *****************************************************************************
#define MAX_NO_OF_HOST_EVENTS 20

// *****************************************************************************
// *****************************************************************************
// Section: File Local Function Declaration
// *****************************************************************************
// *****************************************************************************

void HOST_COMM_ProcessMessage(void);
void HOST_COMM_DecodeMessage(void);
void HOST_COMM_HandleReceipt(HOST_MSG* msg);
void HOST_COMM_HandleMessage(HOST_MSG * msg);
void HOST_COMM_IdleState(void);
void HOST_COMM_CloseCommEvent(void);
void HOST_COMM_AbortTestEvent(void);
void HOST_COMM_TesterConfig(HOST_MSG * msg);
void HOST_COMM_StatusCheck(void);
void HOST_COMM_AbortCommand(void);
void HOST_COMM_OpenCommunication(void);
void HOST_COMM_CloseCommunication(void);
bool HOST_COMM_ValidateCRC(HOST_MSG *msg);
void HOST_COMM_ClearReceiptFlags(void);

// *****************************************************************************
// *****************************************************************************
// Section: Extern Function Declaration
// *****************************************************************************
// *****************************************************************************
bool HOST_COMM_IsConnected(void);
bool HOS_COMM_GetTestConfigData(TEST_CONFIG_DATA* tsconfig_data);

uint16_t test_scenarios_info[100];

TS_INFO* ts_data = (TS_INFO *)&test_scenarios_info[0];

// *****************************************************************************
// *****************************************************************************
// Section: File Global Variables Declaration
// *****************************************************************************
// *****************************************************************************
static HOST_EVENT g_host_event_buffer[MAX_NO_OF_HOST_EVENTS];

typedef struct
{
    uint8_t event_in_ptr;
    uint8_t event_out_ptr;
    uint8_t resp_nak_counter;
    uint8_t resp_busy_counter;
    uint8_t resp_delay_limit_counter;

    uint8_t is_resp_delay_elapsed;
    
}HOST_SYSDATA;

static bool is_host_connected = false;
static bool is_test_config_rcvd = false;
static TESTER_STATUS t_status = TESTER_IDLE;
static HOST_SYSDATA st_host_data;
static uint16_t total_no_of_ts = 0;

static HOST_TEST_CONFIG host_config;

/*********************** EVENT TABLE MAP **************************************/
HOST_COMM_EVENT_HANDLER g_event_handler[E_MAX_EVENTS] =
{
    /*Event*/               /* Action*/
    {NO_EVENTS,             HOST_COMM_IdleState},
    {E_MSG_RCVD,            HOST_COMM_DecodeMessage},
    {E_MSG_TRANSMIT,        HOST_COMM_TXSetup},
    {E_MSG_PROCESSED,       HOST_COMM_RX_Ready},
    {E_IDLE,                HOST_COMM_ProcessMessage},
    {E_ABORT,               HOST_COMM_AbortTestEvent},
    {E_CLOSE,               HOST_COMM_CloseCommEvent},
};

// *****************************************************************************
// *****************************************************************************
// Section: Function Definitions
// *****************************************************************************
// *****************************************************************************

/******************************************************************************
  Function:
    void HOST_COMM_Initialize(void)

  Description:

*/
void HOST_COMM_Initialize(void)
{
    /* Initialize UART, System Variable etc here */
#ifdef _HOST_COMM_UART
    DRV_HOST_USART_Initialize();
#endif

    /* Initialize TMR Service */
    DRV_HOST_TMR_Initialize(TMR_ID_4);

    /* HOST Module Varaibles */
    {
        st_host_data.event_in_ptr = 0;
        st_host_data.event_out_ptr = 0;
        
        HOST_COMM_ClearReceiptFlags();
        
        memset(&g_host_event_buffer, NO_EVENTS, MAX_NO_OF_HOST_EVENTS);
    }
}

/******************************************************************************
  Function:
    void HOST_COMM_Tasks(void)

  Description:

*/
void HOST_COMM_Tasks(void)
{
    HOST_EVENT local_events = NO_EVENTS;

    /* Get Host comm events if any */
    local_events = HOST_COMM_GetEvent();

    /* Process all the events */
    if(local_events != NO_EVENTS)
    {
        /* Action call based on events*/
        if(g_event_handler[local_events].Action != NULL)
        {
            g_event_handler[local_events].Action();
        }
    }
}

/******************************************************************************
  Function:
    void HOST_COMM_PutEvent(HOST_EVENT event)

  Description:

*/
void HOST_COMM_PutEvent(HOST_EVENT event)
{
    /* Check if g_event_in_ptr is greater than MAX_NO_OF_HOST_EVENTS handled */
    if(st_host_data.event_in_ptr >= MAX_NO_OF_HOST_EVENTS)
    {
        /* Reinitilize*/
        st_host_data.event_in_ptr =0;
    }

    /* Add the event in the Event buffer */
    g_host_event_buffer[st_host_data.event_in_ptr++] = event;
    
}

/******************************************************************************
  Function:
    HOST_EVENT HOST_COMM_GetEvent(void)

  Description:

*/HOST_EVENT HOST_COMM_GetEvent(void)
{
    HOST_EVENT event;

    /* Check if event in and event out are diff. */
    if(st_host_data.event_in_ptr != st_host_data.event_out_ptr)
    {
        /* Check if the event out pointer reached full */
        if(st_host_data.event_out_ptr >= MAX_NO_OF_HOST_EVENTS)
        {
            /* Reinitialize */
            st_host_data.event_out_ptr = 0;
        }

        /* Get the FIFO event from the event buffer */
        event = g_host_event_buffer[st_host_data.event_out_ptr++];
    }
    else
    {
        event = E_IDLE;
    }

    return event;
}

/******************************************************************************
  Function:
    void HOST_COMM_ProcessMessage(void)

  Description:

*/
void HOST_COMM_ProcessMessage(void)
{
    /* If not Waiting for Response, Send New/Reply Message to HOST */
    if(!HOST_COMM_IsWaitingforReponse())
    {
        if((!HOST_COMM_IsTransmitQueueEmpty()) && (HOST_COMM_IsTransmitCompleted()))
        {
            /* Clear all the flags */
            HOST_COMM_ClearTransmitStatusFlag();
            HOST_COMM_ClearResponseWaitFlag();
            
            st_host_data.is_resp_delay_elapsed = false;

            /* Add Message to TX Buffer */
            HOST_COMM_AddTransmitBuffer();
        }
    }
    /* Either receipt sent by host is ignored or time out */
    else
    {
        /* Waiting for response */
        if(st_host_data.is_resp_delay_elapsed)
        {
            HOST_COMM_ClearResponseWaitFlag();

            /* Increment NAK Counter */
            if(st_host_data.resp_delay_limit_counter++ >HOST_MAX_RETRY_COUNT)
            {
                /* handle error-case here */
            }
        }
    }
}

/******************************************************************************
  Function:
    void HOST_COMM_DecodeMessage(void)

  Description:

*/
void HOST_COMM_DecodeMessage(void)
{
    HOST_MSG* rx_msg;

    HOST_RECEIPT_TYPES receipt;
    uint16_t length;
    HOST_MSG_TYPES type;

    /* Get the Received Message */
    rx_msg = HOST_COMM_GetReceivedMessage();

    /* Get Receipt type and length */
    receipt = rx_msg->m_header.info.host_receipt;
    length  = rx_msg->m_header.length;
    type    = rx_msg->m_header.msg_type;

    /* Check if End of Packet */
    if(rx_msg->m_eop == HOST_END_OF_PACKET_ID)
    {
        /* Check if is is a new message or response from Host */
        if(receipt == HOST_NEW_MESSAGE)
        {
            /* Data unit is valid or not */
            if(length != 0)
            {
                /* Check the HOST Message Checksum */
                if(HOST_COMM_ValidateCRC(rx_msg))
                {
                    HOST_COMM_HandleMessage(rx_msg);
                }
                else
                {
                    /* CRC Failed */
                    HOST_COMM_SendReceipt(type, HOST_NAK);
                }
            }
            /* CRC Ignored */
            else
            {
                HOST_COMM_HandleMessage(rx_msg);
            }
        }
        /* Its a response from host, Checksum verification is ignored */
        else
        {
            HOST_COMM_HandleReceipt(rx_msg);
        }
    }
    else
    {
        /* END of Packet Mismatch */
        HOST_COMM_SendReceipt(type, HOST_NAK);
    }

    /* Put Event for MSG Processed Signal */
    HOST_COMM_PutEvent(E_MSG_PROCESSED);
}

/******************************************************************************
  Function:
    void HOST_COMM_Handle_Receipt(void)

  Description:

*/
void HOST_COMM_HandleReceipt(HOST_MSG* msg)
{
    HOST_RECEIPT_TYPES host_receipt;
    HOST_MSG_TYPES msg_type;

    host_receipt = msg->m_header.info.host_receipt;
    msg_type = msg->m_header.msg_type;

    /* Check is it right response */
    if((HOST_COMM_IsWaitingforReponse()) &&(!st_host_data.is_resp_delay_elapsed))
    {
        /* Stop the Timer */
        DRV_HOST_TMR_Stop();
        
        if(msg_type == HOST_COMM_GetPreviousMessageType())
        {
            /* Clear the response wait status */
            HOST_COMM_ClearResponseWaitFlag();

            st_host_data.is_resp_delay_elapsed = false;

            /* ACK Received*/
            switch(host_receipt)
            {
                case HOST_ACK:
                {
                    /* Clear the TX buffer for next MSG Transmission */
                    HOST_COMM_ClearTransmitBufQueue();

                    /* Reset Receipt Flags */
                    HOST_COMM_ClearReceiptFlags();
                    break;
                }
                case HOST_NAK:
                {
                    if(st_host_data.resp_nak_counter++ > HOST_MAX_RETRY_COUNT)
                    {
                        /* Handle HOST NAK Signal more than MAX attempts */
                    }
                    break;
                }
                case HOST_BUSY:
                {
                    if(st_host_data.resp_busy_counter++ > HOST_MAX_RETRY_COUNT)
                    {
                        /* Handle HOST Busy Signal more than MAX attempts */
                    }
                    break;
                }
            }
        }
    }
}

/******************************************************************************
  Function:
    void HOST_COMM_Handle_Message(void)
 
  Description:

*/
void HOST_COMM_HandleMessage(HOST_MSG * msg)
{
    HOST_MSG_TYPES type = msg->m_header.msg_type;

    /* Based on Message type, data will be processed */
    switch(type)
    {
        /* OPEN COMMUNICAITON MESSAGE TYPE */
        case OPEN_COMMUNICATION:
        {
            HOST_COMM_OpenCommunication();
            break;
        }
        /* TESTER CONFIG MESSAGE TYPE */
        case TESTER_CONFIG:
        {
            HOST_COMM_TesterConfig(msg);
            break;
        }
        /* STATUS CHECK MESSAGE TYPE */
        case STATUS_CHECK:
        {
            HOST_COMM_StatusCheck();
            break;
        }
        /* ABORT COMMAND MESSAGE TYPE */
        case ABORT_COMMAND:
        {
            HOST_COMM_AbortCommand();
            break;
        }
        case CLOSE_COMMUNICATION:
        {
            HOST_COMM_CloseCommunication();
        }
        /* UNKNOWN MESSAGE TYPE */
        default:
        {
            HOST_COMM_SendReceipt(type, HOST_NAK);
            break;
        }
    }
    
}

/******************************************************************************
  Function:
    void HOST_COMM_AbortTestEvent(void)

  Description:

*/
void HOST_COMM_AbortTestEvent(void)
{
    HOST_COMM_ABORT_CALL();
}

/******************************************************************************
  Function:
    void HOST_COMM_CloseCommEvent(void)

  Description:

*/
void HOST_COMM_CloseCommEvent(void)
{
    HOST_COMM_CLOSE_CALL();
}

/******************************************************************************
  Function:
    void HOST_COMM_OpenCommunication(void)

  Description:

*/
void HOST_COMM_OpenCommunication(void)
{
    /* Set the Connection request status */
    is_host_connected = true;

    /* Send Ack back to host client */
    HOST_COMM_SendReceipt(OPEN_COMMUNICATION, HOST_ACK);
}

/******************************************************************************
  Function:
    void HOST_COMM_IsConnected(void)

  Description:

*/
bool HOST_COMM_IsConnected(void)
{
    return is_host_connected;
}

/******************************************************************************
  Function:
    void HOST_COMM_TesterConfig(void)

  Description:

*/
void HOST_COMM_TesterConfig(HOST_MSG * msg)
{
    /* Length */
    uint16_t len = msg->m_header.length;

    /* Data Pointer */
    uint8_t* data_ptr = &msg->m_data.data[0];
    
    /* Add PING Duration Data, Execution_ctrl configurations */
    host_config.all = *data_ptr++;
    
    /* Later the TC's ids to be added */
    memcpy(&total_no_of_ts, data_ptr, sizeof(uint16_t));
    data_ptr += sizeof(uint16_t);

    if(total_no_of_ts !=0 && (host_config.exec_ctrl))
    {
        /* Copy Test Case Information */
        memcpy(ts_data, data_ptr, (len - 3));
    }

    /* Set the Test Config Flag */
    is_test_config_rcvd = true;

    /* Send Receipt to HOST */
    HOST_COMM_SendReceipt(g_host_rx_msg.m_header.msg_type, HOST_ACK);
}

/******************************************************************************
  Function:
    bool HOST_COMM_GetTestConfigData(TEST_CONFIG_DATA* config)

  Description:

*/

bool HOST_COMM_GetTestConfigData(TEST_CONFIG_DATA* config)
{
    if(is_test_config_rcvd)
    {
        /* Copy the information */
        config->total_ts_count = total_no_of_ts;
        config->is_tester_controlled = host_config.exec_ctrl;

        config->info = ts_data;
        return true;
    }
    else
    {
        config = NULL;
        return false;
    }
}

/******************************************************************************
  Function:
    void HOST_COMM_StatusCheck(void)

  Description:

*/
void HOST_COMM_StatusCheck(void)
{
    /* Check and send the receipt */
    if(TESTER_BUSY == t_status)
    {
        HOST_COMM_SendReceipt(g_host_rx_msg.m_header.msg_type, HOST_BUSY);
    }
    else if(TESTER_IDLE == t_status)
    {
        HOST_COMM_SendReceipt(g_host_rx_msg.m_header.msg_type, HOST_ACK);
    }
    else
    {
        HOST_COMM_SendReceipt(g_host_rx_msg.m_header.msg_type, HOST_NAK);
    }  
}

/******************************************************************************
  Function:
    void HOST_COMM_UpdateTesterStatus(TESTER_STATUS status)

  Description:

*/
void HOST_COMM_UpdateTesterStatus(TESTER_STATUS status)
{
    t_status = status;
}

/******************************************************************************
  Function:
    void HOST_COMM_AbortCommand(void)

  Description:

*/
void HOST_COMM_AbortCommand(void)
{
    HOST_COMM_SendReceipt(g_host_rx_msg.m_header.msg_type, HOST_ACK);

    /* Put Event for ABORT Signal */
    HOST_COMM_PutEvent(E_ABORT);
}

/******************************************************************************
  Function:
    void HOST_COMM_CloseCommunication(void)

  Description:

*/
void HOST_COMM_CloseCommunication(void)
{
    is_host_connected = false;

    /* Put Event for ABORT Signal */
    HOST_COMM_PutEvent(E_CLOSE);
}

/******************************************************************************
  Function:
    void HOST_COMM_IDLE_State(void)

  Description:

*/
void HOST_COMM_IdleState(void)
{
    Nop();
}

/******************************************************************************
  Function:
    void HOST_COMM_ClearReceiptFlags(void)

  Description:

*/
void HOST_COMM_ClearReceiptFlags(void)
{
    st_host_data.resp_nak_counter =0;
    st_host_data.resp_busy_counter =0;
    st_host_data.resp_delay_limit_counter = 0;
    st_host_data.is_resp_delay_elapsed = 0;
}
/******************************************************************************
  Function:
    void HOST_COMM_TMRCallback(void)

  Description:

*/
void HOST_COMM_TMRCallback(void)
{
    st_host_data.is_resp_delay_elapsed = true;
}

/******************************************************************************
  Function:
    bool HOST_COMM_ValidateCRC(HOST_MSG rx_msg)

  Description:

*/
bool HOST_COMM_ValidateCRC(HOST_MSG *msg)
{
    uint16_t cal_crc_cal = 0;
    uint16_t host_crc_val = msg->m_crc;

    /* Calculate the CRC for received data units*/
    cal_crc_cal = HOST_COMM_Calculate_CRC(msg->m_data.data, (msg->m_header.length));

    /* Compare the received crc value and calculate crc*/
    if(cal_crc_cal == host_crc_val)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/******************************************************************************
  Function:
    uint16_t HOST_COMM_Calculate_CRC(uint8_t* data, uint16_t data_size)

  Description:

*/
uint16_t HOST_COMM_Calculate_CRC(uint8_t* data, uint16_t data_size)
{
    uint16_t loop;
    uint16_t crc_temp = 0;
    uint16_t crc =0;

    /* Calculate Modular Sum*/
    for(loop= 0; loop < data_size; loop++)
    {
       crc_temp += data[loop];
    }

    /* 2's Complement */
    crc = (~crc_temp) + 1;

    return crc;
}

/*******************************************************************************
 End of File
 */
