/*******************************************************************************
  Test Manager (FUT/TESTER) Implementation

  Company:
    Microchip Technology Inc.

  File Name:
    test_manager.c

  Summary:
    Test Manager (FUT/TESTER) Implementation

  Description:

	
*******************************************************************************/


// *****************************************************************************
// *****************************************************************************
// Section: Include Files
// *****************************************************************************
// *****************************************************************************

#include "tm_fut_local.h"
#include "test/test_harness.h"

// *****************************************************************************
// *****************************************************************************
// Section: File Scope Variables
// *****************************************************************************
// *****************************************************************************

static TM_SYS_DATA stTMSysData;
static FTMP_PACKET_DATA ftmpData;
static FTMP_CALLBACK_DATA callbackdata;
static uint32_t current_busy_timer;
static uint8_t busy_time_counter;
static uint8_t ftmpMultiPacketSelect;
static uint8_t isErrorModeActive;

// *****************************************************************************
// *****************************************************************************
// Section: File Scope Functions
// *****************************************************************************
// *****************************************************************************

static bool TMSendFTMPPacket(bool isClassData, FTMP_IO_OPERATION operation,
                                FTMP_DRV_CALLBACK callback);
static TM_STATES TMSendConnectionRequest(void);
static TM_STATES TMWaitforResponse(void);
static TM_STATES TMDecodeCallbackResponse(void);
static TM_STATES TMRetryFTMPMessagePacket(void);
static void TMClearFTMPHandlerBuffer(void);
static void TMCallResponseFunc(uint16_t id, TM_RECEIPT receipt);
static void TMConnectionRequestResFunc(TM_RECEIPT receipt);

static TM_FUT_MSG_TABLE msg_table[] = {
    
    /* index */          /* rFunction */
    {   0,               &TMConnectionRequestResFunc  },
    
};

static uint16_t msg_table_len = sizeof(msg_table)/sizeof(TM_FUT_MSG_TABLE);

// *****************************************************************************
// *****************************************************************************
// Section: Interface Function Definitions
// *****************************************************************************
// *****************************************************************************

/* FTMP System Initialize & Task routines */
void TM_FUT_Init(void)
{
    
    /* Initialize FTMP Communication */
    FTMP_SysInit();
      
    /* Initialize Test Manager system Variables */
    stTMSysData.state = TM_STATE_INIT;
    stTMSysData.is_connected = false;
    busy_time_counter = 0;
    current_busy_timer = 0;
    ftmpMultiPacketSelect = false;
    isErrorModeActive = false;
    
}

void TM_FUT_Task(void)
{
    switch(stTMSysData.state)
    {
        case TM_STATE_INIT:
        {
            /* Test Task, Test Manager Initialization to be done here */
            TEST_PlatformReady();
            
            stTMSysData.state = TM_STATE_CONNECT;
            break;       
        }
        case TM_STATE_CONNECT:
        {           
            /* Check if FUT-Tester is already got connected */
            if(!stTMSysData.is_connected)
            {  
                /* Send Connection Request Command */
                stTMSysData.state = TMSendConnectionRequest();
            }
            else
            {
                /* Connection already established, Moving back to Idle State */
                stTMSysData.state = TM_STATE_IDLE;
            }
            break;
        }
        case TM_STATE_IDLE:
        {                
            /* Response not received; Get error status from FTMP */
            if(FTMP_GetErrorCode() == FTMP_NO_ERROR) 
            {
                /* Check TM is waiting for response */
                stTMSysData.state = TMWaitforResponse();
            }
            else
            {
                stTMSysData.state = TM_STATE_ERROR;
            }           
            break;
        }        
        case TM_STATE_BUSY:
        {
            /* Wait for defined timeout to retry FTMP request again */                 
            if(busy_time_counter < FTMP_MSG_MAX_RETRY_COUNT)
            {
                stTMSysData.state = TMRetryFTMPMessagePacket();
            }
            else
            {
                /* Maximum retry counts reached */
                stTMSysData.rx_result = TM_ERROR;
                stTMSysData.state = TM_STATE_IDLE; 
            }
            break;
        }
        case TM_STATE_ERROR:
        {
            isErrorModeActive = true;
            stTMSysData.rx_result = TM_ERROR;
            break;
        }            
    }
}

/* This function shall be called in TM Idle state to check for response
 * returns new state for TM Task
 */
static TM_STATES TMWaitforResponse(void)
{
    TM_STATES state;
    
    /* Check if TM is waiting for response */
    if(stTMSysData.is_waiting_for_response)
    {       
        if(stTMSysData.is_response_rcvd)
        {
            /* Decode the response from Tester */
            state = TMDecodeCallbackResponse();
                        
            /* Clear the flags */
            stTMSysData.is_response_rcvd = false;
            stTMSysData.is_waiting_for_response = false;
        }
        else
        {
            state = TM_STATE_IDLE;
        }
    }
    else
    {
        state =  TM_STATE_IDLE;
    }
    
    return state;
}

/* This function shall be called in TM Connect state to send connection 
 * request message to tester 
 * returns new state for TM Task
 */
static TM_STATES TMSendConnectionRequest(void)
{  
    TM_STATES state;
    
    /* Send Connection Request Command */
    if(TM_SUCCESS == TM_SendFTMPCommand(FTMP_HNDLR_CONNECT_REQUEST))
    {
        /* Command Successfully sent to Tester */
       state = TM_STATE_IDLE;
    }
    else
    {
        /* Command not accepted */
       state = TM_STATE_BUSY;

       /* Get current time tick */
       current_busy_timer = FTMP_TimerGetTick();
    }
    
    return state;  
}

/* This function shall be called in TM Busy State to retry the failed message 
 * returns new state for TM Task
 */
static TM_STATES TMRetryFTMPMessagePacket(void)
{
    TM_STATES state = TM_STATE_BUSY;
    
    /* Delay routine and then change the state */
    if(FTMP_CheckTimerExpiry(FTMP_BUSY_STAUS_WAIT_TIME, current_busy_timer))
    {
        /* Retry the same packet, FTMP handler holds the buffer */
        if(TMSendFTMPPacket(ftmpData.isClass, 
                                    ftmpData.op, ftmpData.ftmpcallback))
        {
            /* Increment the busy counter */
            busy_time_counter++;
            
            state = TM_STATE_IDLE;
        }
        else
        {
            state = TM_STATE_BUSY;
        }
    }

    return state;
}

/* This function shall be called in TM Idle state to decode the response 
 * returns new state for TM Task 
 */
static TM_STATES TMDecodeCallbackResponse(void)
{
    TM_STATES new_state;
    
    FTMP_DATA_UNIT *tx_data = (FTMP_DATA_UNIT *)callbackdata.ftmp_tx_data->data_unit;
    FTMP_DATA_UNIT *rx_data = (FTMP_DATA_UNIT *)callbackdata.ftmp_rx_data->data_unit;
    
    /* Check if it class data */
    if(callbackdata.ftmp_rx_data->header.is_class_data == true)
    {   
        if( (rx_data->uDI.index_start == FTMP_HNDLR_ACK) &&
                (rx_data->uDI.index_end == FTMP_HNDLR_ACK))
        {                
            /* It's ACK from Tester */
            stTMSysData.rx_result = TM_ACK;
            new_state = TM_STATE_IDLE;
        }            
        else if((rx_data->uDI.index_start == FTMP_HNDLR_NAK) && \
                (rx_data->uDI.index_end == FTMP_HNDLR_NAK))
        {
            /* It's NAK from Tester */
            stTMSysData.rx_result = TM_NAK;
            new_state = TM_STATE_ERROR;
        }
        else if((rx_data->uDI.index_start == FTMP_HNDLR_BUSY) && \
                (rx_data->uDI.index_end == FTMP_HNDLR_BUSY))
        {
            
            /* Get current time tick */
            current_busy_timer = FTMP_TimerGetTick(); 
            
            /* It's BUSY response from Tester */
            stTMSysData.rx_result = TM_WAIT;
            new_state = TM_STATE_BUSY;
        }
        else
        {
           /* Unexpected Response */
           stTMSysData.rx_result = TM_ERROR;
           new_state = TM_STATE_IDLE;
        }   
    }
    else
    {
        /* Raw data to be decoded */
        new_state = TM_STATE_IDLE;
    } 
    
    /* Reset busy counter */
    if(new_state != TM_STATE_BUSY)
    {
        busy_time_counter =0;
    }
    
    /* Response function call */
    TMCallResponseFunc(tx_data->uDI.index_start, stTMSysData.rx_result);
    
    return new_state;    
}

/* Transmits FTMP Packet
 * isClassData  - Is it class or raw message to be sent
 * operation    - Is it WR/RD operation
 * callback     - Function to be invoked upon receiving response from Tester
 * returns FTMP message successfully sent or not
 */
static bool TMSendFTMPPacket(bool isClassData, FTMP_IO_OPERATION operation,
                                FTMP_DRV_CALLBACK callback)
{  
    /* Check if Multi data packet is active; TM will not send FTMP Packet */
    if(ftmpMultiPacketSelect)
    {
        return true;
    }
    
    /* Copy the details which will be used for retry */
    ftmpData.isClass = isClassData;
    ftmpData.ftmpcallback = callback;
            
    /* FTMP Handler call to Send Message */
    if((!stTMSysData.is_waiting_for_response) && (!isErrorModeActive))
    {
        /* Set the Flag as wait */
        stTMSysData.rx_result = TM_WAIT;
    
        stTMSysData.is_waiting_for_response = true;
        ftmpMultiPacketSelect = false;
        return FTMP_HNDLR_SendBuffer(isClassData, operation, 0, callback);
    }
    else
    {
        return false;
    }
}

/* Sets the FTMP Multi Class Packet to active
*/
void TM_FTMPMultiClassSelect(void)
{
    /* Clear the Buffer before adding any fresh request */
    FTMP_HNDLR_ClearBuffer();   
    
    ftmpMultiPacketSelect = true;
}

/* Sets the FTMP Multi Class Packet to de-active
*/
void TM_FTMPMultiClassDeSelect(void)
{      
    ftmpMultiPacketSelect = false;
}

/* Clears FTMP Handler buffers 
*/
static void TMClearFTMPHandlerBuffer(void)
{
    /* Check if it is FTMP Multi Class is active */
    if(!ftmpMultiPacketSelect)
    {
        FTMP_HNDLR_ClearBuffer();
    }
}

/* Response function call (for specific FTMP message
 */
static void TMCallResponseFunc(uint16_t id, TM_RECEIPT receipt)
{
    uint16_t count;
    
    for(count =0; count <= msg_table_len; count++)
    {
        if(msg_table[count].index == id)
        {
            msg_table[count].rfunc(receipt);      
            break;
        }
    }
}

/* TM Connection request response function 
 */
static void TMConnectionRequestResFunc(TM_RECEIPT receipt)
{
    /* Check if ACK received */
    if(receipt == TM_ACK)
    {
        /* Enable to start FTMP retry counter */
        FTMP_StartRetryCounter();
        
        stTMSysData.is_connected = true;
    }
    else
    {
        stTMSysData.is_connected = false;
    }
}

/* Transmits the FTMP Command Message 

* command     - FTMP Command
* returns the message successfully sent or not.
*/
TM_STATUS TM_SendFTMPCommand(FTMP_COMMAND_CLASS command)
{
    /* Clear the Buffer before adding any fresh request */
    TMClearFTMPHandlerBuffer();
    
    /* Add Command Class to FTMP Handler buffer */
    if(FTMP_HNDLR_AddCommandClassToBuffer(command))
    {
        /* Initiate FTMP Packet transmission */
        if(TMSendFTMPPacket(true, FTMP_WRITE_OP, &TM_Callback))
        {
            return TM_SUCCESS;
        }
        else
        {
            return TM_FAILURE;
        }
    }
    else
    {
        return TM_FAILURE;
    }
}

/* Transmits the FTMP Data Class Message 

* Class         - FTMP Class
* index_start   - FTMP Index start id associated with class
* index_end     - FTMP Index end id associated with class
* returns the message successfully sent or not.
*/
TM_STATUS TM_SendFTMPDataClass(FTMP_CLASS_NAMES class,int index_start, \
                                                       int index_end)
{
    /* Clear the Buffer before adding any fresh request */
    TMClearFTMPHandlerBuffer(); 
    
    /* Add Data Class to FTMP Handler buffer */
    if(FTMP_HNDLR_AddDataClassToBuffer(class, index_start, index_end))
    {
        /* Initiate FTMP Packet transmission */
        if(TMSendFTMPPacket(true, FTMP_WRITE_OP, &TM_Callback))
        {
            return TM_SUCCESS;
        }
        else
        {
            return TM_FAILURE;
        }
    }
    else
    {
        return TM_FAILURE;
    }
}

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
                    int sub_index_end)
{
    /* Clear the Buffer before adding any fresh request */
    TMClearFTMPHandlerBuffer();
    
    /* Add Data Class to FTMP Handler buffer */
    if(FTMP_HNDLR_AddExtDataClassToBuffer(class, index_start, index_end, 
                                            sub_index_start, sub_index_end))
    {
        /* Initiate FTMP Packet transmission */
        if(TMSendFTMPPacket(true, FTMP_WRITE_OP, &TM_Callback))
        {
            return TM_SUCCESS;
        }
        else
        {
            return TM_FAILURE;
        }
    }
    else
    {
        return TM_FAILURE;
    }
}

/* Adds the FTMP Peripheral Command Message 

* index     - FTMP Peripheral Command
* sub_index - Peripheral sub index
* returns the message successfully added or not.
*/
TM_STATUS TM_SendFTMPPeripheralClass(uint16_t index, uint8_t sub_index)
{
    /* Clear the Buffer before adding any fresh request */
    TMClearFTMPHandlerBuffer();
    
    /* Add Data Class to FTMP Handler buffeFTMP_HNDLR_AddPeripheralClassToBuffer */
    if(TM_SUCCESS == TM_SendFTMPExtDataClass(CLASS_H, index, index, sub_index, sub_index))
    {
        /* Initiate FTMP Packet transmission */
        if(TMSendFTMPPacket(true, FTMP_WRITE_OP, &TM_Callback))
        {
            return TM_SUCCESS;
        }
        else
        {
            return TM_FAILURE;
        }
    }
    else
    {
        return TM_FAILURE;
    }
}

/* Test Manager call back routine invoked by FTMP task upon receiving reply 

* ins_ptr - pointer to application specific data. This can be NULL.
* request_data_ptr - Pointer to the FTMP PDU to transmit.
* response_data_ptr - Pointer to the FTMP response packet.

*/
void TM_Callback( void *ins_ptr, FTMPApdu *request_data_ptr, FTMPApdu *response_data_ptr)
{         
    /* Response received from Tester */
    stTMSysData.is_response_rcvd = true;

    /* Copy the FTMP TX and RX data */
    callbackdata.ftmp_tx_data = request_data_ptr;
    callbackdata.ftmp_rx_data = response_data_ptr;
}

/* Transmits the Log result to Tester 

* result - Test case result decided by the FUT
* returns the message successfully sent or not.
*/
bool TM_LogResulttoTester(TM_LOG_RESULT result)
{
    FTMP_COMMAND_CLASS command;
    
    /* Check for the result and assign appropriate command */
    switch(result)
    {
        case TM_PASS:
        {
            command = FTMP_HNDLR_PASS;
            break;
        }
        case TM_FAIL:
        {
            command = FTMP_HNDLR_FAIL;
            break;
        }
        case TM_TESTER:
        {
            command = FTMP_HNDLR_TESTER;
            break;
        }
    }
    
    /* Send FTMP Command Message */
    if(TM_SUCCESS == TM_SendFTMPCommand(command))
    {
        return true;
    }
    else
    {
        return false;
    }
}

/* Transmits the Test Case Information to Tester 

* info - Test Scenario index, Test case id & data items
* returns the message successfully added or not.
*/
bool TM_SendTestCaseInfo(TM_TEST_INFO info)
{
    unTest test;
    unTestCaseId testCaseId;
    
    uint8_t count;
    
    /* Test Scenario id */
    test.tests = info.test_scenario;
    testCaseId.testId = info.test_case_id;
    
    /* Enable multi packet support */
    TM_FTMPMultiClassSelect();
    
    /* Add FTMP Command Message to send Test Scenario & Test Case Id */
    if(TM_SUCCESS == TM_SendFTMPExtDataClass(CLASS_G, test.stTests.test_msb, 
                                                      test.stTests.test_lsb, 
                                        testCaseId.stTestcaseId.test_id_msb,   
                                        testCaseId.stTestcaseId.test_id_lsb))
    {
        /* Run this loop for test set length */
        for(count =0; count < info.test_data_len; count++)
        {
            /* Add FTMP Peripheral Class */
            if(TM_SUCCESS == TM_SendFTMPPeripheralClass(info.test_data->subIndexStart, 
                                            info.test_data->subIndexEnd))
            {
                /* Add Data Class */
                if(TM_SUCCESS == TM_SendFTMPDataClass(info.test_data->className, 
                                                info.test_data->startIndex,   
                                                info.test_data->endIndex))
                {
                    /* Increment the test_data pointer */
                    *info.test_data++;
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
    }
    else
    {
        return false;
    }
 
    /* Disable multi packet support */
    TM_FTMPMultiClassDeSelect();
    
    /* Initiate FTMP Packet transmission */
    if(TMSendFTMPPacket(true, FTMP_WRITE_OP, &TM_Callback))
    {
        return true;
    }
    else
    {
        return false;
    }    
}

/* Returns true if the connection between FUT and Tester is established.
*/
bool TM_IsConnectionEstablished(void)
{
    return stTMSysData.is_connected;
}

/* Returns delivery note from Tester for the message sent .
*/
TM_RECEIPT TM_GetResponseStatus(void)
{
    return stTMSysData.rx_result;
}
