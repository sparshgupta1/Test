/*************************************************************************
FUT Tester Message Protocol (FTMP) Handler Header Definitions

  Company:
    Microchip Technology Inc.
	
  File Name:
    ftmp_handler.h
	
  Summary:
    This file handles all of the FTMP packets.
	
  Description:
    FTMP packet processing.
    This file processess all of the FTMP packets received from FTMP protocol.

  Remarks:
                              
  *************************************************************************/
  
#ifndef _FTMP_HNDLR_H
#define _FTMP_HNDLR_H

#include "../ftmp_if.h"
#include "../bus/ftmp_drv_if.h"

/* Enum defining the Command class message types of FTMP Handler operations */
typedef enum
{
	/* Send connection request to Tester */
	FTMP_HNDLR_CONNECT_REQUEST = 0,
        FTMP_HNDLR_NOT_READY,
        FTMP_HNDLR_GET_TEST_CONFIG,
        FTMP_HNDLR_BUSY,
        FTMP_HNDLR_ACK,
        FTMP_HNDLR_NAK,
        FTMP_HNDLR_SOT,
        FTMP_HNDLR_TESTER_READ,
        FTMP_HNDLR_TESTER_WRITE,
        FTMP_HNDLR_LOOP_BACK,
        FTMP_HNDLR_LOOP_BACK_NUM_BYTES,
        FTMP_HNDLR_EOT,
        FTMP_HNDLR_ABORT,
        FTMP_HNDLR_LOG_RESULT,
        FTMP_HNDLR_PASS,
        FTMP_HNDLR_FAIL,
        FTMP_HNDLR_TESTER,
        FTMP_HNDLR_STIM_REQ,
        FTMP_HNDLR_SEQ_BREAK,
        FTMP_HNDLR_NO_HB,
        FTMP_HNDLR_HB_1_SEC,
        FTMP_HNDLR_HB_10_SEC,
        FTMP_HNDLR_HB_60_SEC,
        FTMP_HNDLR_HB_5_MIN,
        FTMP_HNDLR_HB_10_MIN,
        FTMP_HNDLR_HB_20_MIN,
        FTMP_HNDLR_HB_30_MIN,
        FTMP_HNDLR_HB_60_MIN,
        FTMP_HNDLR_HB_90_MIN,
        FTMP_HNDLR_HB_120_MIN
} FTMP_COMMAND_CLASS;

/* Enum defining the Peripheral class types of FTMP Handler operations */
typedef enum
{
	/* First ten instances of SPI*/
	FTMP_HNDLR_SPI_1 = 0,
	FTMP_HNDLR_SPI_2,
        FTMP_HNDLR_SPI_3,
        FTMP_HNDLR_SPI_4,
        FTMP_HNDLR_SPI_5,
        FTMP_HNDLR_SPI_6,
        FTMP_HNDLR_SPI_7,        
        FTMP_HNDLR_SPI_8,        
        FTMP_HNDLR_SPI_9,
        FTMP_HNDLR_SPI_10,        
        /*first ten instances of I2C*/
        FTMP_HNDLR_I2C_1,
        FTMP_HNDLR_I2C_2,
        FTMP_HNDLR_I2C_3,
        FTMP_HNDLR_I2C_4,
        FTMP_HNDLR_I2C_5,
        FTMP_HNDLR_I2C_6,
        FTMP_HNDLR_I2C_7,
        FTMP_HNDLR_I2C_8,
        FTMP_HNDLR_I2C_9,
        FTMP_HNDLR_I2C_10

} FTMP_PERIPHERAL_CLASS;

extern FTMPApdu TxPacket,RxPacket;
extern FTMP_DATA_UNIT TxDataUnits[FTMP_MAX_DATA_UNIT];
extern FTMP_DATA_UNIT RxDataUnits[FTMP_MAX_DATA_UNIT];


// *****************************************************************************
// *****************************************************************************
// Section: Included FTMP Handler Module Headers Files
// *****************************************************************************
// *****************************************************************************

extern bool FTMP_HNDLR_AddCommandClassToBuffer(FTMP_COMMAND_CLASS command);
extern bool FTMP_HNDLR_AddDataClassToBuffer(FTMP_CLASS_NAMES cl,int index_start, \
                                                       int index_end);
extern bool FTMP_HNDLR_AddPeripheralClassToBuffer(FTMP_PERIPHERAL_CLASS pl);
extern bool FTMP_HNDLR_AddExtDataClassToBuffer(FTMP_CLASS_NAMES cl, \
                    int index_start,int index_end, int sub_index_start, \
                    int sub_index_end);
//extern bool FTMP_HNDLR_AddGetTestConfigToBuffer(void *TestConfigData);
extern bool FTMP_HNDLR_SendBuffer(bool IsClassData,FTMP_IO_OPERATION FTMP_OP,uint8_t TesterAdd,FTMP_DRV_CALLBACK Handler_Callback);
extern void FTMP_HNDLR_ClearBuffer(void);
// *****************************************************************************
// *****************************************************************************
//Internal functions
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
// *****************************************************************************

#endif // _FTMP_HNDLR_H
/*******************************************************************************
 End of File
*/

