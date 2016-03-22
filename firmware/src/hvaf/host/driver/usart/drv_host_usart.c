/*******************************************************************************
  Tester Framework Application 
  
  File Name:
    drv_host_usart.c

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
#include "drv_host_usart.h"
#include "host_msg_builder.h"

// *****************************************************************************
// *****************************************************************************
// Section: Extern Function Declaration
// *****************************************************************************
// *****************************************************************************
void DRV_HOST_USART_Initialize(void);
void DRV_HOST_Transmit_Byte(uint8_t byte);
void DRV_HOST_TX_Disable(void);
void DRV_HOST_TX_Enable(void);
void DRV_HOST_USART_DeInitialize(void);

/******************************************************************************
  Function:
    void DRV_HOST_USART_Initialize(void

  Description:

*/
void DRV_HOST_USART_Initialize(void)
{
    /* Set HOST UART baud rate */
    HOST_UART_BAUD_SET(9600);

    /* HOST UART Initialize */
    HOST_UART_INIT();
}

/******************************************************************************
  Function:
    void DRV_HOST_USART_DeInitialize(void)

  Description:

*/
void DRV_HOST_USART_DeInitialize(void)
{
    /* HOST UART De-Initialize */
    HOST_UART_DEINIT();
}


/******************************************************************************
  Function:
    void DRV_HOST_Transmit_Byte(uint8_t byte)

  Description:

*/
void DRV_HOST_Transmit_Byte(uint8_t byte)
{
    HOST_UART_TX_BUFFER(byte);
}

/******************************************************************************
  Function:
    void DRV_HOST_TX_Enable(void)

  Description:

*/
void DRV_HOST_TX_Enable(void)
{
    HOST_UART_STATUS_TX_ENABLE_BIT();
}

/******************************************************************************
  Function:
    void DRV_HOST_TX_Disable(void)

  Description:

*/
void DRV_HOST_TX_Disable(void)
{
    HOST_UART_STATUS_TX_DISABLE_BIT();
}

/******************************************************************************
  Function:
    void __ISR(HOST_UART_VECTOR) HOST_UART_INTHandler(void)

  Description:

*/
void __ISR(HOST_UART_VECTOR) HOST_UART_INTHandler(void)
{
    if(HOST_UART_RX_INTERRUPT_FLAG_STATUS_BIT)
    {

        HOST_COMM_SaveRXbyte(HOST_UART_RX_BUFFER);

        /* Clear the RX Interrupt */
        HOST_UART_RX_INTERRUPT_FLAG_STATUS_BIT = 0;
    }
    else if(HOST_UART_TX_INTERRUPT_FLAG_STATUS_BIT)
    {
        while(HOST_UART_TX_SHIFT_REG_STATUS == 0);

        HOST_COMM_SendTXbyte();

        /* Clear the TX Interrupt */
        HOST_UART_TX_INTERRUPT_FLAG_STATUS_BIT = 0;
    }
}



/*******************************************************************************
 End of File
 */
