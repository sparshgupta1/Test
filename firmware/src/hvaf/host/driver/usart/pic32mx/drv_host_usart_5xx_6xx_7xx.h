  /*******************************************************************************
  Application Header
  
  File Name:
    drv_usart_5xx_6xx_7xx.h

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

#ifndef _DRV_USART_5XX_6XX_7XX_H_
#define _DRV_USART_5XX_6XX_7XX_H_

// *****************************************************************************
// *****************************************************************************
// Section: Defines
// *****************************************************************************
// *****************************************************************************
/* UART Init Settings */

#define HOST_UART_BAUD_SET(baud)   PLIB_USART_BaudRateSet(USART_ID_2, 80000000, baud);

#define HOST_UART_INIT()                                           \
{                                                                   \
    PLIB_USART_LineControlModeSelect(USART_ID_2, USART_8N1);        \
    PLIB_USART_TransmitterEnable(USART_ID_2);                       \
    PLIB_USART_ReceiverEnable(USART_ID_2);                          \
    PLIB_USART_ReceiverInterruptModeSelect(USART_ID_2, USART_RECEIVE_FIFO_ONE_CHAR);    \
    PLIB_INT_SourceEnable(INT_ID_0, INT_SOURCE_USART_2_RECEIVE);    \
    PLIB_INT_SourceEnable(INT_ID_0, INT_SOURCE_USART_2_TRANSMIT);    \
    PLIB_INT_VectorPrioritySet(INT_ID_0, INT_VECTOR_UART2, INT_PRIORITY_LEVEL2);    \
    PLIB_INT_VectorSubPrioritySet(INT_ID_0, INT_VECTOR_UART2, INT_SUBPRIORITY_LEVEL0);  \
    PLIB_USART_Enable(USART_ID_2);                                  \
}

#define HOST_UART_DEINIT()                                          \
{                                                                   \
    PLIB_USART_TransmitterDisable(USART_ID_2);                      \
    PLIB_USART_ReceiverDisable(USART_ID_2);                         \
    PLIB_INT_SourceDisable(INT_ID_0, INT_SOURCE_USART_2_RECEIVE);    \
    PLIB_INT_SourceDisable(INT_ID_0, INT_SOURCE_USART_2_TRANSMIT);   \
    PLIB_USART_Disable(USART_ID_2);                                 \
}

/* Buffers */
#define HOST_UART_RX_BUFFER                             PLIB_USART_ReceiverByteReceive(USART_ID_2)
#define HOST_UART_TX_BUFFER(byte)                       PLIB_USART_TransmitterByteSend(USART_ID_2, byte)

#define HOST_UART_STATUS_TX_ENABLE_BIT()                PLIB_USART_TransmitterEnable(USART_ID_2)
#define HOST_UART_STATUS_TX_DISABLE_BIT()               PLIB_USART_TransmitterDisable(USART_ID_2)
#define HOST_UART_STATUS_RX_ENABLE_BIT()                PLIB_USART_ReceiverEnable(USART_ID_2)
#define HOST_UART_STATUS_RX_DISABLE_BIT()               PLIB_USART_ReceiverDisable(USART_ID_2)

/* UART Interrupt Settings*/
#define HOST_UART_RX_INTERRUPT_FLAG_STATUS_BIT          IFS1bits.U2RXIF
#define HOST_UART_TX_INTERRUPT_FLAG_STATUS_BIT          IFS1bits.U2TXIF
#define HOST_UART_RX_INTERRPUT_CONTROL_BIT              IEC1bits.U2RXIE
#define HOST_UART_TX_INTERRPUT_CONTROL_BIT              IEC1bits.U2TXIE
#define HOST_UART_TX_SHIFT_REG_STATUS                   U2STAbits.TRMT
#define HOST_UART_VECTOR                                _UART_2_VECTOR

#endif /* _DRV_USART_5XX_6XX_7XX_H_ */

/*******************************************************************************
 End of File
*/

