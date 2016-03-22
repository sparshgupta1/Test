/*******************************************************************************
  Application Header
  
  File Name:
    test_app.h

  Summary:
    SDCARD FAT Single Disk application definitions 

  Description:
    This file contains the SDCARD FAT Single Disk demo application definitions.
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

#ifndef _USART_STIMULUS_H
#define _USART_STIMULUS_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include "peripheral/usart/plib_usart.h"
#include "peripheral/int/plib_int.h"
#include "system/common/sys_common.h"
#include "stimulus_data.h"
#include "../../test_manager/tm_tester_local.h"

// *****************************************************************************
// *****************************************************************************
// Section: Macro Definitions
// *****************************************************************************
// *****************************************************************************
#define MAX_BUFF_SIZE 512



typedef enum
{
    /* This indicates stimulus is in transmit mode */
    STIMULUS_TRANSMIT,
    /* This indicates stimulus is in receive mode */
    STIMULUS_RECEIVE,
            
} STIMULUS_SCENARIO;

// *****************************************************************************
// *****************************************************************************
// Section: Type Definitions
// *****************************************************************************
// *****************************************************************************
typedef struct
{
    /* Identifies USART hardware module (PLIB-level) ID. */
    USART_MODULE_ID                 usartId;
    
    /* Identifies the Operation mode of the USART driver. */
    USART_TRANSMIT_INTR_MODE        mode; 
   
    /* The initial USART line control settings.*/
    USART_LINECONTROL_MODE          lineControl;
    
    /* The USART Transmit Interrupt Mode */
    USART_TRANSMIT_INTR_MODE        txIntMode;
    
    /* The USART Receive  Interrupt Mode */
    USART_RECEIVE_INTR_MODE         rxIntMode;
   
    /* Baud Rate value to be used, if not using auto baud.*/
    uint32_t                        baudRate; 
    
    /* Interrupt source ID for the transmitter interrupt.*/
    INT_SOURCE                      interruptTransmit;
    
    /* Interrupt source ID for the receiver interrupt.*/
    INT_SOURCE                      interruptReceive;

}DRV_USART_CONFIG_INIT;

typedef struct _stimulus_buffer_obj
{
    uint32_t iTestScenario;
    
    uint32_t iTestCaseID;
    
    STIMULUS_SCENARIO Scenario;
    
    /* Pointer to the stimulus data from the table  - Transmit */
    char *pTxBuffer;

    /* Pointer to the stimulus data from the table  - Receive */
    char *pRxBuffer;
    
    /* Total number of bytes to be Transmitted */
    size_t nBytestoTransmit;
    
    /* Total number of bytes to Receive */
    size_t nBytestoReceive;
    
    /* Number of bytes to be Transmitted */
    size_t nBytesTransmitted;
    
    /* Number of bytes Received */
    size_t nBytesReceived;
    
} STIMULUS_BUFFER_OBJ;

uint8_t rxStimulusBuff[MAX_BUFF_SIZE];

/*******************************************************************************
  Function:
    void STIMULUS_USART_DRV_Initialize ( void )

  Summary:
     HVAF Stimulus Driver initialization routine

  Description:
    This routine initializes the requested stimulus.  This function opens
    the necessary drivers and initializes .

  Precondition:
    All other system initialization routines should be called before calling
    this routine (in "SYS_Initialize").

  Parameters:
    None.

  Returns:
    None.

  Example:
    <code>
    STIMULUS_USART_DRV_Initialize();
    </code>

  Remarks:
    This routine must be called by the Stimulus Data Manager.
*/
SYS_MODULE_OBJ STIMULUS_USART_DRV_Initialize( const SYS_MODULE_INDEX index,
                                        const SYS_MODULE_INIT * const init );

/*******************************************************************************
  Function:
    void STIMULUS_USART_DRV_ReceiveStart ( void )

  Summary:
     HVAF Stimulus Driver receive start routine

  Description:
    This routine enables the receiver module of requested instance of USART 
    peripheral.

  Precondition:
    STIMULUS_USART_DRV_Initialize API must be called prior to calling this API.

  Parameters:
    Pointer to SDM_TC_OBJ structure and call back routine.

  Returns:
    None.

  Example:
    <code>
    STIMULUS_USART_DRV_ReceiveStart();
    </code>

  Remarks:
    This routine must be called by the Stimulus Data Manager.
*/
void STIMULUS_USART_DRV_ReceiveStart(TM_TEST_CASE_INFO *Obj, DRV_CALLBACK Callback);

/*******************************************************************************
  Function:
    void STIMULUS_USART_DRV_TransmitStart ( void )

  Summary:
     HVAF Stimulus Driver transmit start routine

  Description:
    This routine enables the transmitter module of requested instance of USART 
    peripheral.

  Precondition:
    STIMULUS_USART_DRV_Initialize API must be called prior to calling this API.

  Parameters:
    Pointer to SDM_TC_OBJ structure and call back routine.

  Returns:
    None.

  Example:
    <code>
    STIMULUS_USART_DRV_TransmitStart();
    </code>

  Remarks:
    This routine must be called by the Stimulus Data Manager.
*/
void STIMULUS_USART_DRV_TransmitStart(TM_TEST_CASE_INFO *pTCObj, DRV_CALLBACK Callback);
/*******************************************************************************
  Function:
    TM_TC_RESULT STIMULUS_Verify ( void )

  Summary:
     HVAF Stimulus Driver data Verification routine

  Description:
    This routine verifies the transmit/receive buffers with the test case buffers
    and returns PASS/FAIL result.

  Precondition:
    STIMULUS_USART_DRV_Initialize API must be called prior to calling this API.

  Parameters:
    None.

  Returns:
    PASS/FAIL result.

  Example:
    <code>
    STIMULUS_Verify();
    </code>

  Remarks:
    This routine must be called by the Stimulus Data Manager.
*/
TM_TC_RESULT STIMULUS_USART_DRV_DataVerify(void);

/*******************************************************************************
  Function:
    void STIMULUS_USART_DRV_ReceiveTask ( void )

  Summary:
     HVAF Stimulus Driver Receive Task

  Description:
    This routine will be called from ISR in case of interrupt model and from 
 *  sys_tasks in case of polling model. This task routine will receive the data
 *  from configured USART module.

  Precondition:
    STIMULUS_USART_DRV_Initialize API must be called prior to calling this API.

  Parameters:
    None.

  Returns:
    None.

  Example:
    <code>
    STIMULUS_USART_DRV_ReceiveTask();
    </code>

  Remarks:
    This routine must be called by the Stimulus Data Manager.
*/
void STIMULUS_USART_DRV_ReceiveTask();

/*******************************************************************************
  Function:
    void STIMULUS_USART_DRV_TransmitTask ( void )

  Summary:
     HVAF Stimulus Driver initialization routine

  Description:
    This routine will be called from ISR in case of interrupt model and from 
 *  sys_tasks in case of polling model. This task routine will transmit the data
 *  to configured USART module.

  Precondition:
    STIMULUS_USART_DRV_Initialize API must be called prior to calling this API.

  Parameters:
    None.

  Returns:
    None.

  Example:
    <code>
    STIMULUS_USART_DRV_TransmitTask();
    </code>

  Remarks:
    This routine must be called by the Stimulus Data Manager.
*/
void STIMULUS_USART_DRV_TransmitTask();

/*******************************************************************************
  Function:
    void STIMULUS_USART_DRV_PutCharacter ( const char character )

  Summary:
     HVAF Stimulus Driver character write

  Description:
    This routine will write one character to the configured UART module.

  Precondition:
    STIMULUS_USART_DRV_Initialize API must be called prior to calling this API.

  Parameters:
    Byte to be transmitted.

  Returns:
    None.

  Example:
    <code>
    STIMULUS_USART_DRV_PutCharacter ( 'A );
    </code>

  Remarks:
    This routine must be called by the Stimulus Data Manager.
*/
bool STIMULUS_USART_DRV_PutCharacter(const char character);

/*******************************************************************************
  Function:
    DRV_CALLBACK STIMULUS_Callback

  Summary:
     HVAF Stimulus Driver Callback function pointer

  Description:
    This is the callback function to Stimulus Data Manager. 
 * Call back will be given after data transfer is complete.

  Precondition:
    None.

  Parameters:
    Byte to be transmitted.

  Returns:
    None.

  Example:
    <code>
    STIMULUS_Callback;
    </code>

  Remarks:
    This routine must be called by the Stimulus Data Manager.
*/
DRV_CALLBACK STIMULUS_Callback;

/*******************************************************************************
  Function:
    void STIMULUS_USART_DRV_Reset ( void )

  Summary:
     HVAF Stimulus Driver reset function.

  Description:
    This routine will reset UART module counter and buffer pointers.

  Precondition:
    None.

  Parameters:
    None.

  Returns:
    None.

  Example:
    <code>
    STIMULUS_USART_DRV_Reset();
    </code>

  Remarks:
    This routine must be called by the Stimulus Data Manager.
*/
void STIMULUS_USART_DRV_Reset(void);
#endif /* _USART_STIMULUS_HEADER_H */

/*******************************************************************************
 End of File
*/

