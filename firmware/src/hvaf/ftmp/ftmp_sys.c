/*******************************************************************************
  FTMP Master/Slave Appplication Protocol Implementation

  Company:
    Microchip Technology Inc.

  File Name:
    ftmp_sys.c

  Summary:
    FTMP Master/Slave Appplication Protocol Implementation

  Description:

	
*******************************************************************************/


// *****************************************************************************
// *****************************************************************************
// Section: Include Files
// *****************************************************************************
// *****************************************************************************

#include "ftmp_if.h"
#include "ftmp_common.h"
#include "bus/ftmp_drv_if.h"

#define FTMP_PACKET_HEADER_LEN      4
#define FTMP_SOP_LOC                0   //save start delimiter in array location
#define FTMP_INFO_LOC               1   //save tester info
#define FTMP_INFO_CLASS_BITLOC      4
#define FTMP_INFO_INTENT_BITLOC     5
#define FTMP_LENGTH_LOC             2   //save packet length

// *****************************************************************************
// *****************************************************************************
// Section: File Scope Variables
// *****************************************************************************
// *****************************************************************************
/* Enum definition for FTMP States */
typedef enum
{
   FTMP_STATE_IDLE = 0,
   FTMP_STATE_WAITING_FOR_RESPONSE,
   FTMP_STATE_READY_TO_TRANSMIT_RESPONSE,
   FTMP_STATE_ERROR

}FTMP_STATES;

/* Enum definitions for Transmission staus */
typedef enum
{
    FTMP_TX_STATUS_READY =0,
    FTMP_TX_STATUS_WAIT_FOR_RESPONSE,
    FTMP_TX_STATUS_ERROR
}FTMP_TX_STATUS;

/* Enum definitions for reception status */
typedef enum
{
    FTMP_RX_STATUS_RECEIVED_OK = 0,
    FTMP_RX_STATUS_RECEIVED_NOT_OK,
    FTMP_RX_STATUS_PENDING
}FTMP_RX_STATUS;

/* FTMP system variables */
typedef struct
{
    /* FTMP States */
    FTMP_STATES state;
    /* TX status enum */
    FTMP_TX_STATUS tx_status;
    /* FTMP TX request pointer */
    FTMPApdu* tx_req_ptr;
    /* FTMP TX response pointer */
    FTMPApdu* tx_res_ptr;
    /* FTMP TX buffer - Allocated from FTMP driver */
    FTMPBuffer st_ftmp_tx_buf;
    /* FTMP RX response pointer */
    FTMPApdu* rx_req_ptr;
    /* TX response time counter*/
    uint32_t tx_res_load_timer;
    /* Response time counter*/
    uint32_t rx_res_load_timer;
    /* Response timer expiry status */
    bool is_rx_res_sent;
    /* Tester waiting for response */
    bool is_waiting_to_send_response;
    /* Retry Counter*/
    uint8_t tx_retry_msg_counter;
    /* Enable retry counter */
    bool is_retry_counter_enabled;
}FTMP_SYS_VARS;

static FTMP_SYS_VARS st_ftmp_sys_vars;

/* Callback registered during send */
FTMP_DRV_CALLBACK tx_callback;

/* Callback registered by handler to receive*/
FTMP_DRV_CALLBACK rx_callback;

/* Local FTMP application data pointers */
uint8_t local_apdu_buf[sizeof(FTMP_DATA_ITEMS)];
FTMPApdu local_apdu_ptr;
FTMP_DATA_UNIT* local_du_ptr = (FTMP_DATA_UNIT *)&local_apdu_buf[0];


FTMP_ERROR_CODE error_code = FTMP_NO_ERROR;

// *****************************************************************************
// *****************************************************************************
// Section: File Scope Functions
// *****************************************************************************
// *****************************************************************************

FTMP_STATES FTMPMasterIdle(void);
FTMP_STATES FTMPSlaveIdle(void);
FTMP_STATES FTMPWaitforResponse(void);
FTMP_STATES FTMPReadytoTransmitResponse(void);
FTMP_RX_STATUS FTMP_MasterCheckforResponse(void);
bool FTMP_Validate_DataItems(FTMPApdu* apdu_ptr);
bool FTMP_Validate_MessagePacket(FTMPApdu* apdu_ptr);
bool FTMP_Validate_DataLength(FTMPApdu* apdu_ptr);
void FTMP_AddHeader(FTMPApdu* apdu_ptr);
void FTMP_AddDataUnit(FTMPApdu* apdu_ptr);
void FTMP_AddCRC(uint8_t* data, uint16_t size);
bool FTMP_ProcessRxMessage(FTMPBuffer *rx_buf_ptr, FTMPApdu* apdu_ptr);
void FTMP_InterpreteData(uint8_t* data, uint16_t size, FTMPApdu* apdu_ptr);
bool FTMPMessageReTransmit(void);
bool FTMP_CheckHeader(uint8_t* data, uint16_t size, FTMPApdu* apdu_ptr);
void FTMP_ResetBuffers(FTMPBuffer* bufptr);

void FTMP_AddtoTransmitBuffer( void *ins_ptr, FTMPApdu* request_data_ptr,
                                         FTMP_DRV_CALLBACK callback);

FTMP_RETURN_CODE FTMPSendPackettoSlave( void *ins_ptr,
                                        FTMPApdu* request_data_ptr,
                                        FTMPApdu* response_data_ptr,
                                        FTMP_DRV_CALLBACK callback);

FTMP_RETURN_CODE FTMPSendPackettoMaster( void *ins_ptr,
                                        FTMPApdu* request_data_ptr,
                                        FTMPApdu* response_data_ptr,
                                        FTMP_DRV_CALLBACK callback);


// *****************************************************************************
// *****************************************************************************
// Section: Interface Function Definitions
// *****************************************************************************
// *****************************************************************************

void FTMP_SysInit(void)
{
    uint8_t* buf_ptr;
    
    /* Initialize FTMP driver */
    FTMP_DRV_Initialize();

    /* Set the Communication Channel (Default) - Tester will connected to CH_1*/
    FTMP_DRV_SetCommChannel(CH_1);

    /* Init timer driver - Timer Tick will be used by FTMP */
    FTMP_TimerInit();

    /* Allocate memory */
    FTMP_Allocate_Memory(FTMP_BUFFER_SIZE, &buf_ptr);

    /* Initialize all the system variables*/
    tx_callback = NULL;
    st_ftmp_sys_vars.tx_status = FTMP_TX_STATUS_READY;

    /* Allocate Memory for Transmit buffer */
    st_ftmp_sys_vars.st_ftmp_tx_buf.buffer = buf_ptr;

    /* FTMP state initialize */
    st_ftmp_sys_vars.state = FTMP_STATE_IDLE;

    /* Initialize other variables */
    st_ftmp_sys_vars.tx_res_load_timer = 0;
    st_ftmp_sys_vars.rx_res_load_timer = 0;
    st_ftmp_sys_vars.is_rx_res_sent = false;
    st_ftmp_sys_vars.tx_retry_msg_counter = 0;
    st_ftmp_sys_vars.tx_req_ptr = NULL;
    st_ftmp_sys_vars.rx_req_ptr = NULL;
    st_ftmp_sys_vars.is_rx_res_sent = false;
    st_ftmp_sys_vars.is_waiting_to_send_response = false;
    st_ftmp_sys_vars.is_retry_counter_enabled = false;
}

void FTMP_SysTask(void)
{
    switch(st_ftmp_sys_vars.state)
    {
        case FTMP_STATE_IDLE:
        {
            
#if defined (__FUT__)
            /* Wait here to check for any Incoming */
            st_ftmp_sys_vars.state = FTMPMasterIdle();
#else
            /* Wait here to send */
            st_ftmp_sys_vars.state = FTMPSlaveIdle();
#endif
            break;
        }
        case FTMP_STATE_WAITING_FOR_RESPONSE:
        {
            /* This state will be applicable only for master; Slave will not
             wait for response */
            st_ftmp_sys_vars.state = FTMPWaitforResponse();
            break;
        }
        case FTMP_STATE_READY_TO_TRANSMIT_RESPONSE:
        {
            /* Once the incoming packet is successful; reponse should be sent */
            st_ftmp_sys_vars.state = FTMPReadytoTransmitResponse();
            break;
        }
        case FTMP_STATE_ERROR:
        {
            /* Error State - FTMP Communication will be down */
            error_code = FTMP_ERROR;
            break;
        }
    }
}

FTMP_STATES FTMPMasterIdle(void)
{
    FTMP_STATES new_state = FTMP_STATE_IDLE;

    /* Check for TX status; any previous message is transmitted & waiting */
    if(st_ftmp_sys_vars.tx_status == FTMP_TX_STATUS_WAIT_FOR_RESPONSE)
    {
        /* Load currrent timer */
        st_ftmp_sys_vars.tx_res_load_timer = FTMP_GetTimerTick();
        
        new_state = FTMP_STATE_WAITING_FOR_RESPONSE;
    }
    else
    {
        st_ftmp_sys_vars.tx_status = FTMP_TX_STATUS_READY;
        new_state = FTMP_STATE_IDLE;
    }
    
    return new_state;   
}

FTMP_STATES FTMPSlaveIdle(void)
{
    FTMP_STATES new_state = FTMP_STATE_IDLE;
    FTMPBuffer* rx_buf_ptr = NULL;

    /* Check if an entire message is ready/received*/
    rx_buf_ptr = FTMP_DRV_ReceiveData(FTMP_DRV_GetCommChannel());

    if(rx_buf_ptr != NULL)
    {
        /* Process the received message */
        if(true == FTMP_ProcessRxMessage(rx_buf_ptr,
                                         st_ftmp_sys_vars.rx_req_ptr))
        {
            /* Move to next state */
            new_state = FTMP_STATE_READY_TO_TRANSMIT_RESPONSE;
            
            /* Load the timer tick */
            st_ftmp_sys_vars.rx_res_load_timer = FTMP_GetTimerTick();

            /* Reset the FTMP state & response timer flag*/
            st_ftmp_sys_vars.is_rx_res_sent = false;

            /* Waiting for response */
            st_ftmp_sys_vars.is_waiting_to_send_response = true;
            
            /* Call back to FTMP handler + request pointer (No response) */
            if(rx_callback != NULL)
            {
               rx_callback(NULL, (FTMPApdu *)st_ftmp_sys_vars.rx_req_ptr, NULL);
            }

        }
        else
        {
            /* Reponse timer has expired; Now FTMP will send NAK status*/
            /* No Callback is required to assign */

            FTMP_ResetAPDU( (FTMPApdu *) &local_apdu_ptr);

            local_apdu_ptr.header.is_class_data = true;
            local_apdu_ptr.header.io_operation = FTMP_NO_OP;
            local_apdu_ptr.header.num_bytes = sizeof(local_apdu_buf) + 2; //with crc

            /* Add data units for sending busy status */
            local_du_ptr->uDI.cl = CLASS_I;
            local_du_ptr->uDI.index_start = 5;
            local_du_ptr->uDI.index_end = 5;
            local_du_ptr->uDI.is_next_class = 0;
            local_du_ptr->uDI.is_sub_index = 0;
            local_du_ptr->next_data_unit_ptr = NULL;

            local_apdu_ptr.data_unit = (FTMP_DATA_UNIT *) local_du_ptr;

            /* Transmit NAK status */
            FTMP_AddtoTransmitBuffer(NULL, (FTMPApdu *) &local_apdu_ptr, NULL);
        }
    }
    
    return new_state;
}

FTMP_STATES FTMPWaitforResponse(void)
{
    FTMP_STATES new_state = FTMP_STATE_WAITING_FOR_RESPONSE;
    FTMP_RX_STATUS status;

    /* Check if Master is waiting for response & it got back */
    status = FTMP_MasterCheckforResponse();

    /* Response received and Ok*/
    if(status == FTMP_RX_STATUS_RECEIVED_OK)
    {
        st_ftmp_sys_vars.tx_retry_msg_counter = 0;
        new_state = FTMP_STATE_IDLE;
        st_ftmp_sys_vars.tx_status = FTMP_TX_STATUS_READY;
    }
    /* Failed to receive proper message  - ( Retry/Resend )*/
    else if(status == FTMP_RX_STATUS_RECEIVED_NOT_OK)
    {
        if(!FTMPMessageReTransmit())
        {
            /* Retry counter reached max; no more communication is possible */
            new_state = FTMP_STATE_ERROR;
            st_ftmp_sys_vars.tx_status = FTMP_TX_STATUS_ERROR;
        }
        else
        {
            st_ftmp_sys_vars.tx_status = FTMP_STATE_WAITING_FOR_RESPONSE;
        }
    }
    /* Still reponse is pending - yet to receive */
    else
    {
        /* Check res timer expired */
        if(FTMP_CheckTimerExpiry(FTMP_MSG_RES_WAIT_TIMER, st_ftmp_sys_vars.tx_res_load_timer))
        {
            if(!FTMPMessageReTransmit())
            {
                /* Retry counter reached max; no more communication is possible */
                new_state = FTMP_STATE_ERROR;
                st_ftmp_sys_vars.tx_status = FTMP_TX_STATUS_ERROR;
            }
            else
            {
                /* Load new timer tick */
                st_ftmp_sys_vars.tx_res_load_timer = FTMP_GetTimerTick();
                new_state = FTMP_STATE_WAITING_FOR_RESPONSE;
            }
        }
        else
        {
            new_state = FTMP_STATE_WAITING_FOR_RESPONSE;
        }
    }
    
    return new_state;

}

FTMP_STATES FTMPReadytoTransmitResponse(void)
{
    FTMP_STATES new_state = FTMP_STATE_READY_TO_TRANSMIT_RESPONSE;

    if(st_ftmp_sys_vars.is_waiting_to_send_response)
    {
        /* Time counter will increment based on the FTMP task running status */
        if(FTMP_CheckTimerExpiry(FTMP_MSG_RES_WAIT_TIMER, st_ftmp_sys_vars.rx_res_load_timer))
        {
            /* Reponse timer has expired; Now FTMP will send busy status*/
            /* No Callback is required to assign */

            FTMP_ResetAPDU( (FTMPApdu *) &local_apdu_ptr);

            local_apdu_ptr.header.is_class_data = true;
            local_apdu_ptr.header.io_operation = FTMP_NO_OP;
            local_apdu_ptr.header.num_bytes = sizeof(local_apdu_buf) + 2; //with crc

            /* Add data units for sending busy status */
            local_du_ptr->uDI.cl = CLASS_I;
            local_du_ptr->uDI.index_start = 3;
            local_du_ptr->uDI.index_end = 3;
            local_du_ptr->uDI.is_next_class = 0;
            local_du_ptr->uDI.is_sub_index = 0;
            local_du_ptr->next_data_unit_ptr = NULL;

            local_apdu_ptr.data_unit = (FTMP_DATA_UNIT *) local_du_ptr;

            /* Transmit busy status */
            FTMP_AddtoTransmitBuffer(NULL, (FTMPApdu *) &local_apdu_ptr, NULL);

            /* set the reponse timer flag */
            st_ftmp_sys_vars.is_rx_res_sent = true;

            new_state = FTMP_STATE_IDLE;
        }
    }
    else
    {
        new_state = FTMP_STATE_IDLE;
    }
    
    return new_state;   
}

FTMP_RX_STATUS FTMP_MasterCheckforResponse(void)
{
    FTMPBuffer* rx_buf_ptr = NULL;
    FTMP_RX_STATUS status;

    /* Check if an entire message is ready/received*/
    rx_buf_ptr = FTMP_DRV_ReceiveData(FTMP_DRV_GetCommChannel());

    if(rx_buf_ptr != NULL)
    {
        /* Process the received message */
        if(true == FTMP_ProcessRxMessage(rx_buf_ptr, st_ftmp_sys_vars.tx_res_ptr))
        {
            status = FTMP_RX_STATUS_RECEIVED_OK;
            
            if(tx_callback != NULL)
            {
                /* Call back to FTMP handler with request pointer */
                tx_callback(NULL, st_ftmp_sys_vars.tx_req_ptr,(FTMPApdu *)st_ftmp_sys_vars.tx_res_ptr);
            }
        }
        else
        {
            status = FTMP_RX_STATUS_RECEIVED_NOT_OK;
        }
    }
    else
    {
        status = FTMP_RX_STATUS_PENDING;
    }

    return status;
}

void FTMP_HandlerRegister(FTMPApdu* apdu_rx_ptr, FTMP_DRV_CALLBACK callback)
{
    
    /* Load Callback and FTMP application data unit pointer */
    rx_callback = callback;
    st_ftmp_sys_vars.rx_req_ptr = apdu_rx_ptr;
    
}

/* Transmits the requested FTMP PDU. A call-back function can be specified.

* ins_ptr - pointer to application specific data. This can be NULL.
* request_data_ptr -  Pointer to the FTMP PDU to transmit.
* response_data_ptr - Pointer to the FTMP response PDU.
* callback - Function that should be called when a response is ready

* returns the status of the request.
*/

FTMP_RETURN_CODE FTMPSendPacket( void *ins_ptr, FTMPApdu* request_data_ptr,
                                 FTMPApdu* response_data_ptr, FTMP_DRV_CALLBACK callback)
{
#if defined (__FUT__)

    return FTMPSendPackettoSlave(NULL, request_data_ptr, response_data_ptr,
                                    callback);
#else

    return FTMPSendPackettoMaster(NULL, request_data_ptr, response_data_ptr,
                                    callback);
#endif
}

FTMP_RETURN_CODE FTMPSendPackettoSlave( void *ins_ptr, FTMPApdu* request_data_ptr,
                                 FTMPApdu* response_data_ptr, FTMP_DRV_CALLBACK callback)
{
    FTMP_RETURN_CODE error_code;
    uint8_t t_addr = request_data_ptr->header.tester_address;

    if(st_ftmp_sys_vars.tx_status == FTMP_TX_STATUS_READY)
    {
        if( request_data_ptr != NULL )
        {
            if(FTMP_Validate_MessagePacket(request_data_ptr) == true)
            {
                /* Set the Communication Channel */
                FTMP_DRV_SetCommChannel((TESTER_CHANNELS)t_addr);
                
                /* Assign request & response pointers to local system var */
                st_ftmp_sys_vars.tx_req_ptr = request_data_ptr;
                st_ftmp_sys_vars.tx_res_ptr = response_data_ptr;

                /* Set the tx_status as waiting for response */
                st_ftmp_sys_vars.tx_status = FTMP_TX_STATUS_WAIT_FOR_RESPONSE;
                st_ftmp_sys_vars.tx_retry_msg_counter = 0;
                
                /* Add to transmit buffer - One message at a time */
                FTMP_AddtoTransmitBuffer(ins_ptr, request_data_ptr, callback);

                error_code =  FTMP_RETURN_CODE_OK;
            }
            else
            {
                /* Data units are not valid */
                error_code =  FTMP_RETURN_CODE_DATA_UNIT_NOT_VALID;
            }
        }
        else
        {
            error_code =  FTMP_RETURN_CODE_DATA_UNIT_NOT_VALID;
        }
    }
    else if(st_ftmp_sys_vars.tx_status == FTMP_TX_STATUS_WAIT_FOR_RESPONSE)
    {
        error_code = FTMP_RETURN_CODE_NO_ROOM_FOR_DATA;
    }
    else
    {
         error_code = FTMP_RETURN_CODE_COMM_CHANNEL_FAILURE;
    }


    return error_code;
}

FTMP_RETURN_CODE FTMPSendPackettoMaster( void *ins_ptr, FTMPApdu* request_data_ptr,
                                 FTMPApdu* response_data_ptr, FTMP_DRV_CALLBACK callback)
{
    FTMP_RETURN_CODE error_code;

    if( st_ftmp_sys_vars.is_rx_res_sent)
    {
        error_code = FTMP_RETURN_CODE_RESP_TOO_LATE;

        /* Reset the FTMP state & response timer flag*/
        st_ftmp_sys_vars.is_rx_res_sent = false;
        st_ftmp_sys_vars.is_waiting_to_send_response = false;
    }
    else
    {
        if( response_data_ptr != NULL )
        {
            if(FTMP_Validate_MessagePacket(response_data_ptr) == true)
            {
                /* Assign request & response pointers to local system var */
                st_ftmp_sys_vars.tx_req_ptr = request_data_ptr;
                st_ftmp_sys_vars.tx_res_ptr = response_data_ptr;

                /* Set that response has sent */
                st_ftmp_sys_vars.is_rx_res_sent = false;
                st_ftmp_sys_vars.is_waiting_to_send_response = false;

                /* Add to transmit buffer - One message at a time */
                FTMP_AddtoTransmitBuffer(ins_ptr, response_data_ptr, callback);

                error_code =  FTMP_RETURN_CODE_OK;
            }
            else
            {
                error_code =  FTMP_RETURN_CODE_DATA_UNIT_NOT_VALID;
            }
        }
        else
        {
            error_code =  FTMP_RETURN_CODE_DATA_UNIT_NOT_VALID;
        }
    }

    return error_code;
}

/* Transmits the requested FTMP Slave. A call-back function can be specified.

* ins_ptr - pointer to application specific data. This can be NULL.
* request_data_ptr - Pointer to the FTMP PDU to transmit.
* master_callback - Function that should be called when a response is ready for the tester

* returns the status of the request.
*/
void FTMP_AddtoTransmitBuffer( void *ins_ptr, FTMPApdu* request_data_ptr,
                                         FTMP_DRV_CALLBACK callback)
{
    (void)ins_ptr;

    /* Reset the buffer */
    FTMP_ResetBuffers(&st_ftmp_sys_vars.st_ftmp_tx_buf);

    /* Add headers */
    FTMP_AddHeader(request_data_ptr);

    /* Check if Data unit is present */
    if(request_data_ptr->header.num_bytes != 0)
    {
        /* Add Data unit */
        FTMP_AddDataUnit(request_data_ptr);

        /* Add CRC */
        FTMP_AddCRC((st_ftmp_sys_vars.st_ftmp_tx_buf.buffer+4),
                    (st_ftmp_sys_vars.st_ftmp_tx_buf.buf_size - 4));
    }

    /* Assign a callback */
    tx_callback = callback;
   
    /* Call to FTMP driver to transmit data */
    FTMP_DRV_SaveToBuffer(FTMP_DRV_GetCommChannel(), st_ftmp_sys_vars.st_ftmp_tx_buf);
}

bool FTMP_Validate_MessagePacket(FTMPApdu* apdu_ptr)
{
    bool is_true = apdu_ptr->header.is_class_data;

    /* If Message transfer is for class objects */
    if(is_true)
    {
        if( FTMP_Validate_DataLength (apdu_ptr) )
        {
            if( FTMP_Validate_DataItems(apdu_ptr) )
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    /* Check raw message */
    else
    {
        /* To be implemented here in case of raw message type */
        return false;
    }
}

bool FTMP_Validate_DataItems(FTMPApdu* apdu_ptr)
{
    FTMP_DATA_UNIT *dataObj;
    FTMP_DATA_UNIT *t_Obj;

    dataObj = (FTMP_DATA_UNIT *)apdu_ptr->data_unit;

    /* Check all the object members are valid */
    do
    {
        t_Obj = dataObj;

        /* Check for Class, Index start & end */
        if( (dataObj->uDI.cl >= CLASS_A) && (dataObj->uDI.cl <= CLASS_END) &&
                (dataObj->uDI.index_start <= dataObj ->uDI.index_end))
        {
            /* Check for Sub index start and end */
            if(dataObj->uDI.is_sub_index)
            {
                if((dataObj->uDI.sub_index_start > dataObj->uDI.sub_index_end))
                {
                    return false;
                }
            }

            /* Check for next class ptr - valid or not */
            if(((dataObj->next_data_unit_ptr == NULL) && (dataObj->uDI.is_next_class == true)) ||
                   ((dataObj->next_data_unit_ptr != NULL) && (dataObj->uDI.is_next_class == false)))
            {
                return false;
            }
        }
        else
        {
            return false;
        }

        /* Increment the data object pointer */
        //dataObj++;
        dataObj = dataObj->next_data_unit_ptr;

    }while(t_Obj->next_data_unit_ptr != NULL);

    return true;
}

bool FTMP_Validate_DataLength(FTMPApdu* apdu_ptr)
{
    FTMP_DATA_UNIT *dataObj;
    FTMP_DATA_UNIT *t_Obj;
    uint16_t aru_len = 0;
    uint16_t calc_len = 0;
    uint16_t total_len = FTMP_BUFFER_SIZE;

    dataObj = (FTMP_DATA_UNIT *)apdu_ptr->data_unit;
    aru_len = (apdu_ptr->header.num_bytes/2);

    if(aru_len <= total_len )
    {
        /* Calculate total length of data units */
        do
        {
            calc_len += 4;
            t_Obj = dataObj;

            //*dataObj++;
            dataObj = dataObj->next_data_unit_ptr;

        }while(t_Obj->next_data_unit_ptr != NULL);

        /* Check the calculated length with stored length */
        if(calc_len == aru_len)
        {
            return true;
        }
        else
        {
            return false;
        }
        
        return false;
    }
}

void FTMP_AddHeader(FTMPApdu* apdu_ptr)
{
    uint8_t t_info = 0;
    uint8_t temp = 0;
    uint16_t length = 0;

    /* Adding Tester Information */
    /* Add Tester Address */
    t_info = (t_info | (apdu_ptr->header.tester_address & 0x0f));
    
    /* Add Class/Raw type */
    temp = apdu_ptr->header.is_class_data;
    t_info = (t_info |(temp << FTMP_INFO_CLASS_BITLOC));

    /* Add IO operation */
    temp = apdu_ptr->header.io_operation;
    t_info = (t_info | (temp << FTMP_INFO_INTENT_BITLOC));

    /* Reset the buffer pointer size */
    st_ftmp_sys_vars.st_ftmp_tx_buf.buf_size = 0;

    /* Add into transmit buffer */
    length = ((apdu_ptr->header.num_bytes)/2) + 2; //Add length for CRC

    st_ftmp_sys_vars.st_ftmp_tx_buf.buffer[st_ftmp_sys_vars.st_ftmp_tx_buf.buf_size++] = FTMP_SOP;
    st_ftmp_sys_vars.st_ftmp_tx_buf.buffer[st_ftmp_sys_vars.st_ftmp_tx_buf.buf_size++] = t_info;

    st_ftmp_sys_vars.st_ftmp_tx_buf.buffer[st_ftmp_sys_vars.st_ftmp_tx_buf.buf_size++] = (uint8_t) (length & 0x00ff);
    st_ftmp_sys_vars.st_ftmp_tx_buf.buffer[st_ftmp_sys_vars.st_ftmp_tx_buf.buf_size++] = (uint8_t) ((length >> 8) & 0x00ff);
}

void FTMP_AddDataUnit(FTMPApdu* apdu_ptr)
{
    FTMP_DATA_UNIT *dataObj;
    FTMP_DATA_UNIT *t_Obj;
    uint32_t t_data;

    bool is_true = apdu_ptr->header.is_class_data;

    /* Add data unit - Class type */
    if(is_true)
    {
        dataObj = (FTMP_DATA_UNIT *)apdu_ptr->data_unit;

        do
        {
            t_data = dataObj->uDI.all;

            /* Copy to transmit buffer */
            memcpy(st_ftmp_sys_vars.st_ftmp_tx_buf.buffer+(st_ftmp_sys_vars.st_ftmp_tx_buf.buf_size), &t_data, sizeof(uint32_t));
            st_ftmp_sys_vars.st_ftmp_tx_buf.buf_size += sizeof(uint32_t);
            
            /* Assign to temp data obj & increment dataObj ptr */
            t_Obj = dataObj;
            //*dataObj++;
            dataObj = dataObj->next_data_unit_ptr;

        }while(t_Obj->next_data_unit_ptr != NULL);
    }
    else
    {
        /* For raw data - To be implemented */
    }
}

bool FTMP_ProcessRxMessage(FTMPBuffer *rx_buf_ptr, FTMPApdu* apdu_ptr)
{
    bool ret_status = false;
    uint8_t* data = (uint8_t *)rx_buf_ptr->buffer;
    uint16_t length = (uint16_t) rx_buf_ptr->buf_size;

    /* Check the pointer */
    if(rx_buf_ptr!= NULL)
    {
        /* Check packet header received */
        if(FTMP_CheckHeader(data, length, apdu_ptr))
        {
            /* Check Packet CRC */
            if(FTMP_CheckCRC(data + FTMP_PACKET_HEADER_LEN, (length - FTMP_PACKET_HEADER_LEN)))
            {
                /* CRC Ok; decode the received packet */
                FTMP_InterpreteData(data, length, apdu_ptr);
                ret_status = true;
            }
        }
    }

    return ret_status;
}

void FTMP_InterpreteData(uint8_t* data, uint16_t size, FTMPApdu* apdu_ptr)
{
    uint8_t cl_table_length = 0;
    uint8_t total_class_table = 0;
    uint8_t loop = 0;
    uint32_t t_data_val;
    FTMP_DATA_UNIT *data_unit_ptr = (FTMP_DATA_UNIT *)apdu_ptr->data_unit;

    uint8_t* r_data_ptr = data + FTMP_PACKET_HEADER_LEN;
    
    /* Class data */
    if(apdu_ptr->header.is_class_data)
    {
        
        /* Get length of cl table */
        cl_table_length = sizeof(FTMP_DATA_ITEMS);

        /* Get the total length of class table received */
        total_class_table = (apdu_ptr->header.num_bytes) / cl_table_length;

        /* Copy the data to rx buffer */
        for(loop = 0; loop < total_class_table; loop++)
        {
            memcpy(&t_data_val, r_data_ptr, cl_table_length);
            data_unit_ptr->uDI.all = t_data_val;
            r_data_ptr += cl_table_length;

            if(loop < (total_class_table - 1))
            {
                //data_unit_ptr->next_data_unit_ptr = data_unit_ptr++;
                data_unit_ptr->next_data_unit_ptr = data_unit_ptr+1; //Added Anuroop
                data_unit_ptr = data_unit_ptr+1;
              
            }
            else
            {
                data_unit_ptr->next_data_unit_ptr = NULL;
            }
        }

        /* Adding next_data_unit_ptr length */
        apdu_ptr->header.num_bytes *= 2;
    }
    /* Raw data - TBI*/
    else
    {

    }
   
}

bool FTMPMessageReTransmit(void)
{
    /* Retry counter willl not be enabled until 1st communication is active */
    if(st_ftmp_sys_vars.is_retry_counter_enabled)
    {
        st_ftmp_sys_vars.tx_retry_msg_counter++;   
    }
    
    /* Check retry counter has reached maximum attempts */
    if(st_ftmp_sys_vars.tx_retry_msg_counter < FTMP_MSG_MAX_RETRY_COUNT)
    {
        /* Add to transmit buffer - Retry Message */
        FTMP_AddtoTransmitBuffer(NULL, st_ftmp_sys_vars.tx_req_ptr, tx_callback);
        return true;
    }
    else
    {
        /* Retry counter reached max; no more communication is possible */
        return false;
    }
}

bool FTMP_CheckHeader(uint8_t* data, uint16_t size, FTMPApdu* apdu_ptr)
{
    uint8_t t_info =0;
    uint16_t num_of_bytes = 0;
    bool ret_status = false;

    /* Minimum 4 bytes of data is required to process with data unit */
    if(size >= FTMP_PACKET_HEADER_LEN )
    {
        /* Check header */
        if(data[FTMP_SOP_LOC] == FTMP_SOP)
        {
            /* Get tester information */
            t_info = data[FTMP_INFO_LOC];

            /* No Check done on tester_address, class data & IO operation  - TBI */
            apdu_ptr->header.tester_address = (uint8_t) (t_info & 0x0f);
            apdu_ptr->header.is_class_data  = (bool) ((t_info >>  FTMP_INFO_CLASS_BITLOC ) & 0x01);
            apdu_ptr->header.io_operation   = (FTMP_IO_OPERATION) ((t_info >>  FTMP_INFO_INTENT_BITLOC ) & 0x02);

            /* Get the length */
            num_of_bytes = (data[FTMP_LENGTH_LOC] & 0x00FF);
            num_of_bytes |= (data[FTMP_LENGTH_LOC + 1] << 8);

            apdu_ptr->header.num_bytes = (num_of_bytes - 2);    //Decrement CRC

            ret_status = true;
        }
    }

    return ret_status;
}

void FTMP_AddCRC(uint8_t* data, uint16_t size)
{
    uint16_t crc;

    /* Calculate CRC */
    crc = FTMP_CalculateCRC(data, size);

    /* Load CRC values in transmit buffer */
    st_ftmp_sys_vars.st_ftmp_tx_buf.buffer[st_ftmp_sys_vars.st_ftmp_tx_buf.buf_size++] = (uint8_t) (crc & 0x00ff);
    st_ftmp_sys_vars.st_ftmp_tx_buf.buffer[st_ftmp_sys_vars.st_ftmp_tx_buf.buf_size++] = (uint8_t) ((crc >> 8) & 0x00ff);
}

void FTMP_ResetAPDU(FTMPApdu* apdu_ptr)
{
    memset(apdu_ptr, 0x00, sizeof(FTMPApdu));
}

void FTMP_ResetBuffers(FTMPBuffer* bufptr)
{
    /* Reset buffer size counter */
    bufptr->buf_size = 0;

    /* Reset the trasmit/receive buffers */
    //memset(bufptr->buffer, 0x00, FTMP_STATIC_BUFFER_SIZE);
}

FTMP_ERROR_CODE FTMP_GetErrorCode(void)
{
    return error_code;
}

void FTMP_StartRetryCounter(void)
{
    st_ftmp_sys_vars.is_retry_counter_enabled = true;
}

