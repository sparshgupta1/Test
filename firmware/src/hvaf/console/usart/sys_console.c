/*******************************************************************************
  SYS UART CONSOLE Support Layer
  
  File Name:
    sys_console_uart.c

  Summary:
    SYS UART CONSOLE Support Layer

  Description:
    This file contains the SYS UART CONSOLE support layer logic.
 *******************************************************************************/


// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2014 released Microchip Technology Inc.  All rights reserved.

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
// DOM-IGNORE-END


// *****************************************************************************
// *****************************************************************************
// Section: Included Files 
// *****************************************************************************
// *****************************************************************************

#include "sys_console.h"
#include "system_definitions.h"

// *****************************************************************************
// *****************************************************************************
// Section: Global Functions
// *****************************************************************************
// *****************************************************************************

void Console_Usart_Init()
{
    /* Initialize USART */
    PLIB_USART_BaudRateSet(USART_CONSOLE_PORT, SYS_CLK_PeripheralFrequencyGet(CLK_BUS_PERIPHERAL_1), USART_CONSOLE_BAUD_RATE);
    PLIB_USART_HandshakeModeSelect(USART_CONSOLE_PORT, USART_HANDSHAKE_MODE_FLOW_CONTROL);
    PLIB_USART_OperationModeSelect(USART_CONSOLE_PORT, USART_ENABLE_TX_RX_USED);
    PLIB_USART_LineControlModeSelect(USART_CONSOLE_PORT, USART_8N1);
    PLIB_USART_TransmitterEnable(USART_CONSOLE_PORT);
    PLIB_USART_TransmitterInterruptModeSelect(USART_CONSOLE_PORT, USART_TRANSMIT_FIFO_NOT_FULL);
    PLIB_USART_ReceiverEnable(USART_CONSOLE_PORT);    
    PLIB_USART_Enable(USART_CONSOLE_PORT);
}

bool Console_Usart_Write_String(char *pData)
{
    if(*pData == '\0')
    {
        return false;
    }

    /* Write a character at a time, only if transmitter is empty */
    while (*pData != '\0')
    {
        while(!PLIB_USART_TransmitterIsEmpty(USART_CONSOLE_PORT));
        /* Send character */
        PLIB_USART_TransmitterByteSend(USART_CONSOLE_PORT, *pData);

        /* Increment to address of next character */
        pData++;

    }
    PLIB_USART_TransmitterByteSend(USART_CONSOLE_PORT, '\r');
    PLIB_USART_TransmitterByteSend(USART_CONSOLE_PORT, '\n');
    return false;
}

bool Console_Usart_Write_Data(char *pData, size_t length)
{
    if((length == 0) || (pData == NULL))
    {
        return false;
    }

    /* Write a character at a time, only if transmitter is empty */
    while(length-- > 0)
    {
        while(!PLIB_USART_TransmitterIsEmpty(USART_CONSOLE_PORT));
        /* Send character */
        PLIB_USART_TransmitterByteSend(USART_CONSOLE_PORT, *pData);

        /* Increment to address of next character */
        pData++;
    }
    PLIB_USART_TransmitterByteSend(USART_CONSOLE_PORT, '\r');
    PLIB_USART_TransmitterByteSend(USART_CONSOLE_PORT, '\n');
    return false;
}


/*******************************************************************************
 End of File
 */