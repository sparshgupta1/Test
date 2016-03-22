/*************************************************************************
  FTMP SPI Master/Slave driver Implementation Header

  Company:
    Microchip Technology Inc.

  File Name:
    ftmp_drv_spi.h

  Summary:
    FTMP SPI Master/Slave driver Implementation Header.

  Description:
                              
  *************************************************************************/
  
#ifndef _FTMP_DRV_SPI_H
#define _FTMP_DRV_SPI_H

// *****************************************************************************
// *****************************************************************************
// Section: Included FTMP SPI Module Headers Files
// *****************************************************************************
// *****************************************************************************

#define FTMP_DRV_SendTxByte(channel, data) //FTMP_DRV_SPI_TX_BYTE(channel, data)

void FTMP_DRV_SPIMasterInit(void);

void FTMP_DRV_SPISlaveInit(void);

void FTMP_DRV_SPIMasterDeInit(void);

void FTMP_DRV_SPISlaveDeInit(void);


#endif // _FTMP_DRV_SPI_H
/*******************************************************************************
 End of File
*/

