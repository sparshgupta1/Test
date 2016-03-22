/*******************************************************************************
  FTMP Master/Slave driver Implementation

  Company:
    Microchip Technology Inc.

  File Name:
    ftmp_drv.c

  Summary:
    FTMP Master/Slave driver Implementation.

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

// *****************************************************************************
// *****************************************************************************
// Section: File Scope Variables
// *****************************************************************************
// *****************************************************************************
/* Enum definition for FTMP driver reception states */
typedef enum{

    FTMP_DRV_RX_HEADER_BYTE = 0,
    FTMP_DRV_RX_INFO_BYTE,
    FTMP_DRV_RX_NUM_BYTES,
    FTMP_DRV_RX_RECEVING_DATA_BYTES,
    FTMP_DRV_RX_IDLE

}FTMP_DRV_STATE;


/* FTMP driver local variables */
static FTMP_DRV_STATE drv_state = FTMP_DRV_RX_IDLE;
static bool is_msg_rcv_complete;
static uint16_t bytes_rcv_in_idle = 0;

/* FTMP tx & rx buffer */
FTMPBuffer drv_tx_buffer[FTMP_NO_OF_STIMULUS_CH+1]; /* Tester + Stimulus */
FTMPBuffer drv_rx_buffer[FTMP_NO_OF_STIMULUS_CH+1]; /* Tester + Stimulus */

static TESTER_CHANNELS channel_index = 0;

static uint16_t t_count =0;
static uint8_t is_active = false;
static uint32_t current_timer = 0;

// *****************************************************************************
// *****************************************************************************
// Section: File Scope Functions
// *****************************************************************************
// *****************************************************************************

void FTMP_DRV_ResetRxState(void);
void FTMP_DRV_TransmitSetup(void);

// *****************************************************************************
// *****************************************************************************
// Section: Driver Interface Function Definitions
// *****************************************************************************
// *****************************************************************************

void FTMP_DRV_Initialize(void)
{
    uint8_t* rx_buf_ptr;
    uint8_t count =0;
    
#if defined(__SPI_CH__)

    #if defined(__FUT__)
        /* Initialize SPI Driver - Master */
        FTMP_DRV_SPIMasterInit();
    #else (FTMP_DRV_MODE == TESTER)
        /* Initialize SPI Driver  - Slave */
        FTMP_DRV_SPISlaveInit();
    #endif

#else
        /* Initialize USART Driver */
        FTMP_DRV_USARTInit();
#endif

    for(count=0; count < (FTMP_NO_OF_STIMULUS_CH+1); count++)
    {
        /* Allocate memory */
        FTMP_Allocate_Memory(FTMP_BUFFER_SIZE, &rx_buf_ptr);

        /* Allocate Memory for RX buffer */
        drv_rx_buffer[count].buffer = rx_buf_ptr;
    }
        
    is_msg_rcv_complete = false;
    
    FTMP_DRV_ResetRxState();
    
}

void FTMP_DRV_DeInitialize()
{
#if defined(__SPI_CH__)

    #if (__FUT__)
        /* DeInitialize SPI Driver - Master */
        FTMP_DRV_SPIMasterDeInit();
    #else
        /* DeInitialize SPI Driver  - Slave */
        FTMP_DRV_SPISlaveDeInit();
    #endif

#else
       /* DeInitialize USART driver */
        FTMP_DRV_USARTDeInit();
#endif
}

/* This function should be called to save the transmit data */
void FTMP_DRV_SaveToBuffer(TESTER_CHANNELS channel, FTMPBuffer tx_buf)
{
    /* Get the buffer pointers */
    drv_tx_buffer[channel].buffer =  tx_buf.buffer;
    drv_tx_buffer[channel].buf_size = (uint8_t) tx_buf.buf_size;
    t_count = 0;

    /* Set/Enable Receive State */
    FTMP_DRV_ResetRxState();

    /* Transmit Setup */
    FTMP_DRV_TransmitSetup();
}

/* Transmit Setup for FTMP communication */
void FTMP_DRV_TransmitSetup(void)
{   
    FTMP_DRV_TransmitEnable();
}

/* This function should be called in driver tx interrupt routine (ISR) */
void FTMP_DRV_TransmitTask(void)
{
    uint8_t channel = (uint8_t) FTMP_DRV_GetCommChannel();

    if((drv_tx_buffer[channel].buffer!= NULL) && (drv_tx_buffer[channel].buf_size >0 ))
    {
        FTMP_DRV_SendTxByte(drv_tx_buffer[channel].buffer[t_count++]);
        drv_tx_buffer[channel].buf_size--;
    }
    else
    {
        t_count = 0;
        FTMP_DRV_TransmitDisable();
    }
}

/* This function should be called in driver rx interrupt routine (ISR) */
/* Reads the rx byte from register and save it */
void FTMP_DRV_ReceiveTask(uint8_t rx_byte)
{
    static uint16_t count = 0;
    static bool is_lsb = true;
    static uint16_t length = 0;
    uint16_t temp;

    uint8_t channel = (uint8_t) FTMP_DRV_GetCommChannel();

    switch(drv_state)
    {
        /* Check for SOP; If not SOP, discard the byte received */
        case FTMP_DRV_RX_HEADER_BYTE:
        {
            if(rx_byte == FTMP_SOP)
            {
                /* Reset buffer counter */
                drv_rx_buffer[channel].buf_size = 0;
                is_lsb = true;
                count = 0;
                is_msg_rcv_complete = false;
                is_active = true;
                
                /* Save rx_byte into the buffer */
                drv_rx_buffer[channel].buffer[drv_rx_buffer[channel].buf_size++] = rx_byte;

                /* Get current timer counter */
                current_timer = FTMP_TimerGetTick();
                
                /* Move to next state */
                drv_state = FTMP_DRV_RX_INFO_BYTE;
            }
            /* Discard the byte received and wait in the same state */
            else
            {
                drv_state = FTMP_DRV_RX_HEADER_BYTE;
            }
            break;
        }
        case FTMP_DRV_RX_INFO_BYTE:
        {
            /* Save rx_byte into the buffer */
            drv_rx_buffer[channel].buffer[drv_rx_buffer[channel].buf_size++] = rx_byte;

            /* Move to next state */
            drv_state = FTMP_DRV_RX_NUM_BYTES;
            break;
        }
        case FTMP_DRV_RX_NUM_BYTES:
        {
            /* Save rx_byte into the buffer */
            drv_rx_buffer[channel].buffer[drv_rx_buffer[channel].buf_size++] = rx_byte;

            /* Check 2 bytes are received as part of byte count */
            if(is_lsb)
            {
                is_lsb = false;

                length =  (rx_byte & 0x00FF);
                
                drv_state = FTMP_DRV_RX_NUM_BYTES;
            }
            else
            {
                temp = rx_byte;
                length |= ((temp << 8) & 0xFF00);
                
                /* Move to next state */
                drv_state = FTMP_DRV_RX_RECEVING_DATA_BYTES;
            }
            
            break;
        }
        case FTMP_DRV_RX_RECEVING_DATA_BYTES:
        {
            /* Save rx_byte into the buffer */
            drv_rx_buffer[channel].buffer[drv_rx_buffer[channel].buf_size++] = rx_byte;

            /* receive untill crc bytes */
            if(++count == length)
            {
                /* Wait here untill the data response is sent */
                is_msg_rcv_complete = true;
                drv_state = FTMP_DRV_RX_IDLE;
            }
            {
                drv_state = FTMP_DRV_RX_RECEVING_DATA_BYTES;
            }
            break;
        }
        case FTMP_DRV_RX_IDLE:
        {
            /* wait here untill the current msg is processed completely */
            /* Discard all the bytes if driver receives */
            /* During transmission FTMP will be in idle mode */

            temp = (uint8_t) rx_byte;
            bytes_rcv_in_idle++;
            
            break;
        }
    }
}

/* This function shall give a valid pointer if complete message is received */
FTMPBuffer* FTMP_DRV_ReceiveData(TESTER_CHANNELS channel)
{
    FTMPBuffer* rx_ptr = NULL;

    /* Check if Receive task is currently processing any bytes and timeout */
    if(is_active && (FTMP_CheckTimerExpiry(FTMP_COM_BREAK_WAIT_TIME, current_timer)))
    {
        FTMP_DRV_ResetRxState();
        is_active = false;
    }
    else
    {
        /* Check if the complete msg is received or not */
        if(is_msg_rcv_complete)
        {
            rx_ptr = (FTMPBuffer *) &drv_rx_buffer[channel];
            is_msg_rcv_complete = false;
            is_active = false;
        }
    }

    return rx_ptr;  
}

/* Set Rx State to receive new message */
void FTMP_DRV_ResetRxState(void)
{
    drv_state = FTMP_DRV_RX_HEADER_BYTE;
}

/* Function sets the channel index */
void FTMP_DRV_SetCommChannel(TESTER_CHANNELS channel)
{
    channel_index = channel;
}

/* Get current communication channel index */
TESTER_CHANNELS FTMP_DRV_GetCommChannel(void)
{
    return channel_index;
}

