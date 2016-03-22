/*************************************************************************
FUT Tester Message Protocol (FTMP) Configuration Header Definitions

  Company:
    Microchip Technology Inc.
	
  File Name:
    ftmp_cnf.h
	
  Summary:
    This file aggregates all of the FTMP Configurations.
	
  Description:
    FTMP Configuration Header

	  
  Remarks:
                              
  *************************************************************************/
  
#ifndef _FTMP_CNF_H
#define _FTMP_CNF_H

// *****************************************************************************
// *****************************************************************************
// Configurations
// *****************************************************************************
// *****************************************************************************

/* FTMP driver uses the driver type selected here as a physical medium */
/* FTMP will include the files accordingly*/
#define __USART_CH__                //__USART_CH__ | __SPI_CH__

/* FTMP driver channel mode (driver also will be configured based on this */
#define __FUT__                    //__FUT__ | __TESTER__

/* System clock frequency - Based on this FTMP Communication will work */
#define SYS_CLOCK_FREQUENCY                 80000000

/* FTMP Control Communication Mode configurations */
/* Either PIC32MX or PIC32MZ configuration parameters will be enabled */

/* For MX Configuration */
#ifdef __PIC32MX__
#define FTMP_USART_ID                       USART_ID_2
#define FTMP_USART_BAUD_RATE                9600
#define FTMP_USART_INTERRUPT_VECTOR         INT_VECTOR_UART2
#define FTMP_USART_INTERRUPT_RX_SOURCE      INT_SOURCE_USART_2_RECEIVE
#define FTMP_USART_INTERRUPT_TX_SOURCE      INT_SOURCE_USART_2_TRANSMIT
#define FTMP_USART_INTERRUPT_PRIORITY       INT_PRIORITY_LEVEL2
#define FTMP_USART_INTERRUPT_SUBPRIORITY    INT_SUBPRIORITY_LEVEL0
#endif

/* For MZ Configuration */
#ifdef __PIC32MZ__
#define FTMP_USART_ID                          USART_ID_2
#define FTMP_USART_BAUD_RATE                   9600
#define FTMP_USART_TX_INTERRUPT_VECTOR         INT_VECTOR_UART2_TX
#define FTMP_USART_RX_INTERRUPT_VECTOR         INT_VECTOR_UART2_RX
#define FTMP_USART_INTERRUPT_RX_SOURCE         INT_SOURCE_USART_2_RECEIVE
#define FTMP_USART_INTERRUPT_TX_SOURCE         INT_SOURCE_USART_2_TRANSMIT
#define FTMP_USART_TX_INTERRUPT_PRIORITY       INT_PRIORITY_LEVEL2
#define FTMP_USART_TX_INTERRUPT_SUBPRIORITY    INT_SUBPRIORITY_LEVEL0
#define FTMP_USART_RX_INTERRUPT_PRIORITY       INT_PRIORITY_LEVEL2
#define FTMP_USART_RX_INTERRUPT_SUBPRIORITY    INT_SUBPRIORITY_LEVEL0
#endif

/* FTMP shall use this timer peripheral for handling the tasks */
#define FTMP_TMR_TICK_NUM                   TMR_ID_2
#define FTMP_TIMER_INTERRUPT_SOURCE         INT_SOURCE_TIMER_2
#define FTMP_TIMER_CLOCK_SOURCE             TMR_CLOCK_SOURCE_PERIPHERAL_CLOCK
#define FTMP_TIMER_CLOCK_PRESCALER          TMR_PRESCALE_VALUE_256
#define FTMP_TIMER_INCREMENT_PERIOD         31250
#define FTMP_TIMER_MS_PER_INCREMENT         100
#define FTMP_TIMER_INTERRUPT_VECTOR         INT_VECTOR_T2
#define FTMP_TIMER_INTERRUPT_PRIORITY       INT_PRIORITY_LEVEL3
#define FTMP_TIMER_INTERRUPT_SUBPRIORITY    INT_SUBPRIORITY_LEVEL0

/* Define the FTMP model i.e big endian or little endian */
/* All the data transfers will be based on this */
#define FTMP_STORAGE                LO_HI               //LO_HI | HI_LO

/* FTMP buffer count (in num of bytes) */
#define FTMP_STATIC_BUFFER_SIZE     1024

/* FTMP response timer tick (in ms)
 * Should be equal or greater than FTMP task if called in timer/rtos */
#define FTMP_MSG_RES_WAIT_TIMER     3000

/* FTMP busy wait timer tick (in ms) */
#define FTMP_BUSY_STAUS_WAIT_TIME   5000

/* FTMP Communication break Timer (in ms) */
#define FTMP_COM_BREAK_WAIT_TIME    300

/* Retry Message count for re-transmission */
#define FTMP_MSG_MAX_RETRY_COUNT    3

/* Tester COM Channel Number - Always associated with FTMP_DRV_TYPE */
#define FTMP_TESTER_COM_CH          CH_1

/* Mention number of Stimulus channels */
/* Stimulus Channels will be assigned based on next available channels */
#define FTMP_NO_OF_STIMULUS_CH      0

/* Holds FTMP Maximum data units */
#define FTMP_MAX_DATA_UNIT          5

#endif // _FTMP_CNF_H
/*******************************************************************************
 End of File
*/

