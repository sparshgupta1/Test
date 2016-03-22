/*******************************************************************************
  FTMP SPI Master/Slave usart driver Implementation

  Company:
    Microchip Technology Inc.

  File Name:
    ftmp_drv_usart.c

  Summary:
    FTMP SPI Master/Slave usart driver Implementation.

  Description:

	
*******************************************************************************/


// *****************************************************************************
// *****************************************************************************
// Section: Include Files
// *****************************************************************************
// *****************************************************************************
#include "ftmp_drv_usart.h"
#include "peripheral/usart/plib_usart.h"
#include "peripheral/int/plib_int.h"


// *****************************************************************************
// *****************************************************************************
// Section: File Scope Variables
// *****************************************************************************
// *****************************************************************************


// *****************************************************************************
// *****************************************************************************
// Section: File Scope Functions
// *****************************************************************************
// *****************************************************************************


// *****************************************************************************
// *****************************************************************************
// Section: Driver Interface Function Definitions
// *****************************************************************************
// *****************************************************************************

/* USART driver init routine */
void FTMP_DRV_USARTInit(void)
{
    PLIB_USART_Disable(FTMP_USART_ID);
    
    PLIB_USART_LineControlModeSelect(FTMP_USART_ID, USART_8N1);
    PLIB_USART_ReceiverEnable(FTMP_USART_ID);
    PLIB_USART_TransmitterInterruptModeSelect(FTMP_USART_ID, USART_TRANSMIT_FIFO_NOT_FULL);
    PLIB_USART_ReceiverInterruptModeSelect(FTMP_USART_ID, USART_RECEIVE_FIFO_ONE_CHAR);
    PLIB_INT_SourceEnable(INT_ID_0, FTMP_USART_INTERRUPT_RX_SOURCE);
    PLIB_INT_SourceEnable(INT_ID_0, FTMP_USART_INTERRUPT_TX_SOURCE);
    
#ifdef __PIC32MX__
    PLIB_INT_VectorPrioritySet(INT_ID_0, FTMP_USART_INTERRUPT_VECTOR, FTMP_USART_INTERRUPT_PRIORITY);
    PLIB_INT_VectorSubPrioritySet(INT_ID_0, FTMP_USART_INTERRUPT_VECTOR, FTMP_USART_INTERRUPT_SUBPRIORITY);
#endif

#ifdef __PIC32MZ__
    PLIB_INT_VectorPrioritySet(INT_ID_0, FTMP_USART_TX_INTERRUPT_VECTOR, FTMP_USART_TX_INTERRUPT_PRIORITY);
    PLIB_INT_VectorSubPrioritySet(INT_ID_0, FTMP_USART_TX_INTERRUPT_VECTOR, FTMP_USART_TX_INTERRUPT_SUBPRIORITY);
    PLIB_INT_VectorPrioritySet(INT_ID_0, FTMP_USART_RX_INTERRUPT_VECTOR, FTMP_USART_RX_INTERRUPT_PRIORITY);
    PLIB_INT_VectorSubPrioritySet(INT_ID_0, FTMP_USART_RX_INTERRUPT_VECTOR, FTMP_USART_RX_INTERRUPT_SUBPRIORITY);    
#endif  
    
    PLIB_USART_BaudRateSet(FTMP_USART_ID, SYS_CLOCK_FREQUENCY, FTMP_USART_BAUD_RATE);
    
    PLIB_USART_Enable(FTMP_USART_ID);   
}

/* USART deinit routine */
void FTMP_DRV_USARTDeInit(void)
{
    PLIB_USART_TransmitterDisable(FTMP_USART_ID);
    PLIB_USART_ReceiverDisable(FTMP_USART_ID);
    PLIB_INT_SourceDisable(INT_ID_0, FTMP_USART_INTERRUPT_RX_SOURCE);
    PLIB_INT_SourceDisable(INT_ID_0, FTMP_USART_INTERRUPT_TX_SOURCE);
    PLIB_USART_Disable(FTMP_USART_ID);
}

/* USART peripheral functionalities */
void FTMP_DRV_USARTTransmitByte(uint8_t byte)
{
    PLIB_USART_TransmitterByteSend(FTMP_USART_ID, byte);
}

void FTMP_DRV_USARTTransmitEnable(void)
{
    PLIB_USART_TransmitterEnable(FTMP_USART_ID);
}

void FTMP_DRV_USARTTransmitDisable(void)
{
    PLIB_USART_TransmitterDisable(FTMP_USART_ID);
}

#ifdef __PIC32MX__

/* Interrupt Routine */
void __ISR(_UART_2_VECTOR) FTMP_UART2_InterruptHandler(void)
{
    if(PLIB_INT_SourceFlagGet(INT_ID_0, FTMP_USART_INTERRUPT_RX_SOURCE))
    {
        /* Clear the RX Interrupt */
        PLIB_INT_SourceFlagClear(INT_ID_0, FTMP_USART_INTERRUPT_RX_SOURCE);

        if(PLIB_USART_ReceiverDataIsAvailable(FTMP_USART_ID))
        {
            FTMP_DRV_ReceiveTask(PLIB_USART_ReceiverByteReceive(FTMP_USART_ID));
        }
    }
    else if(PLIB_INT_SourceFlagGet(INT_ID_0, FTMP_USART_INTERRUPT_TX_SOURCE))
    {
        if((PLIB_USART_TransmitterIsEmpty(FTMP_USART_ID)))
        {     
            /* Transmit Task */
            FTMP_DRV_TransmitTask();
        }

        /* Clear the TX Interrupt */
        PLIB_INT_SourceFlagClear(INT_ID_0, FTMP_USART_INTERRUPT_TX_SOURCE);
    }
}

#endif

#ifdef __PIC32MZ__
/* Interrupt Routine */
void __ISR(_UART2_RX_VECTOR) FTMP_UART2_RX_InterruptHandler(void)
{
    if(PLIB_INT_SourceFlagGet(INT_ID_0, FTMP_USART_INTERRUPT_RX_SOURCE))
    {
        /* Clear the RX Interrupt */
        PLIB_INT_SourceFlagClear(INT_ID_0, FTMP_USART_INTERRUPT_RX_SOURCE);

        if(PLIB_USART_ReceiverDataIsAvailable(FTMP_USART_ID))
        {
            FTMP_DRV_ReceiveTask(PLIB_USART_ReceiverByteReceive(FTMP_USART_ID));
        }
    }
}

void __ISR(_UART2_TX_VECTOR) FTMP_UART2_TX_InterruptHandler(void)
{
    if(PLIB_INT_SourceFlagGet(INT_ID_0, FTMP_USART_INTERRUPT_TX_SOURCE))
    {
        if((PLIB_USART_TransmitterIsEmpty(FTMP_USART_ID)))
        {     
            /* Transmit Task */
            FTMP_DRV_TransmitTask();
        }

        /* Clear the TX Interrupt */
        PLIB_INT_SourceFlagClear(INT_ID_0, FTMP_USART_INTERRUPT_TX_SOURCE);
    }
}

#endif
