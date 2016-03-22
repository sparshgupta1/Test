/*************************************************************************
  FTMP SPI Master/Slave USART driver Implementation Header

  Company:
    Microchip Technology Inc.

  File Name:
    ftmp_drv_usart.h

  Summary:
    FTMP SPI Master/Slave USART driver Implementation Header.

  Description:
                              
  *************************************************************************/
  
#ifndef _FTMP_DRV_USART_H
#define _FTMP_DRV_USART_H

// *****************************************************************************
// *****************************************************************************
// Section: Included FTMP USART Module Headers Files
// *****************************************************************************
// *****************************************************************************

#include "ftmp_if.h"

void FTMP_DRV_USARTInit(void);

void FTMP_DRV_USARTDeInit(void);

void FTMP_DRV_USARTTransmitEnable();

void FTMP_DRV_USARTTransmitDisable();

void FTMP_DRV_USARTTransmitByte(uint8_t byte);



#endif // _FTMP_DRV_USART_H
/*******************************************************************************
 End of File
*/

