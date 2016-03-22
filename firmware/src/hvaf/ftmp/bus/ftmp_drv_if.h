/*************************************************************************
FUT Tester Message Protocol (FTMP) Driver Interface Header Definitions

  Company:
    Microchip Technology Inc.
	
  File Name:
    ftmp_drv_if.h
	
  Summary:
    This file aggregates all of the FTMP driver interface headers.
	
  Description:
    FTMP Interface Header
    This file aggregates all of the FTMP driver interface headers so that
    module (tester/fut) code only needs to include this one single header to obtain
    prototypes and definitions for all the FTMP interfaces.
	  
  Remarks:
                              
  *************************************************************************/
  
#ifndef _FTMP_DRV_IF_H
#define _FTMP_DRV_IF_H

// *****************************************************************************
// *****************************************************************************
// Section: Included FTMP Module Headers Files
// *****************************************************************************
// *****************************************************************************
#include "ftmp_common.h"

#if defined (__SPI_CH__)
    #include "bus/ftmp_drv_spi/ftmp_drv_spi.h"
#else
    #include "bus/ftmp_drv_usart/ftmp_drv_usart.h"
#endif

#define FTMP_DRV_TransmitEnable()           FTMP_DRV_USARTTransmitEnable()
#define FTMP_DRV_TransmitDisable()          FTMP_DRV_USARTTransmitDisable()
#define FTMP_DRV_SendTxByte(data)           FTMP_DRV_USARTTransmitByte(data)

/* Enum definition for tester channel */
typedef enum
{
   CH_1 = 0,
   CH_2,
   CH_3,
   CH_4,
   CH_5,
   CH_6,
   CH_7,
   CH_8,
   CH_9,
   CH_10,
   CH_11,
   CH_12,
   CH_13,
   CH_14,
   CH_15,
   MAX_CHANNELS
}TESTER_CHANNELS;

/* FTMP Driver Initialize */
/* This function will be called in the FTMP layer; based on the configuration
 * driver will be initialized accordingly */
void FTMP_DRV_Initialize(void);	

/* FTMP driver de-initialize */
void FTMP_DRV_DeInitialize(void);

/* This function shall be called to transmit data; it actually saves to buffer
 and transmit in the FTMP driver transmit task */
void FTMP_DRV_SaveToBuffer(TESTER_CHANNELS channel, FTMPBuffer tx_buf);

/* FTMP driver TX & RX task; shall be called in ISR or in a loop */
void FTMP_DRV_TransmitTask(void);
void FTMP_DRV_ReceiveTask(uint8_t rx_byte);

/* This function shall give a valid pointer if message is received completely */
extern FTMPBuffer* FTMP_DRV_ReceiveData(TESTER_CHANNELS channel);

/* This function shall set the communication channel; Used only by master*/
void FTMP_DRV_SetCommChannel(TESTER_CHANNELS channel);

/* Function to get the communication channel */
TESTER_CHANNELS FTMP_DRV_GetCommChannel(void);

/* RX buffer (extern variable)
 Received message will be avaiable in this buffer */
extern FTMPBuffer drv_rx_buffer[FTMP_NO_OF_STIMULUS_CH+1];

#endif // _FTMP_DRV_IF_H
/*******************************************************************************
 End of File
*/

