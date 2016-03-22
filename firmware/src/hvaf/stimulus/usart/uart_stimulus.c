/*******************************************************************************
 Tester Firmware

  File Name:
    stimulus_comm.c

  Summary:
    

  Description:
    This file contains the USB DEVICE CDC Basic Demo main function.
 *******************************************************************************/


// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2012 released Microchip Technology Inc.  All rights reserved.

//Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED �AS IS� WITHOUT WARRANTY OF ANY KIND,
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

#include "uart_stimulus.h"
#include "tm_tester_local.h"
#include "tm_tester_if.h"

// *****************************************************************************
// *****************************************************************************
// Section: File Scope Variables
// *****************************************************************************
// *****************************************************************************

extern TM_TEST_CASE_INFO TestCaseInfo;
extern STIMULUS_DATA        stimulusList[];
static DRV_USART_CONFIG_INIT *configData;
static STIMULUS_BUFFER_OBJ   gStimulusBuffObj;
static size_t                sizeTotal;

void STIMULUS_USART_DRV_Reset(void)
{
    gStimulusBuffObj.nBytesReceived = 0;
    gStimulusBuffObj.nBytesTransmitted = 0;
    gStimulusBuffObj.nBytestoReceive = 0;
    gStimulusBuffObj.nBytestoTransmit = 0;
    gStimulusBuffObj.pRxBuffer = NULL;
    gStimulusBuffObj.pTxBuffer = NULL;
    
}
SYS_MODULE_OBJ STIMULUS_USART_DRV_Initialize(const SYS_MODULE_INDEX index,
                                       const SYS_MODULE_INIT * const init )
{
    /* Get the USART COnfig Data */
    configData = (DRV_USART_CONFIG_INIT *)init;
    /* Initialize USART */
    PLIB_USART_BaudRateSet(configData->usartId, SYS_CLK_PeripheralFrequencyGet(CLK_BUS_PERIPHERAL_1), configData->baudRate);
    PLIB_USART_HandshakeModeSelect(configData->usartId, USART_HANDSHAKE_MODE_FLOW_CONTROL);
    PLIB_USART_OperationModeSelect(configData->usartId, USART_ENABLE_TX_RX_USED);
    PLIB_USART_LineControlModeSelect(configData->usartId, configData->lineControl);
    PLIB_USART_TransmitterEnable(configData->usartId);
    PLIB_USART_TransmitterInterruptModeSelect(configData->usartId, USART_TRANSMIT_FIFO_NOT_FULL);
    PLIB_USART_ReceiverEnable(configData->usartId);
    PLIB_USART_ReceiverInterruptModeSelect(configData->usartId, configData->rxIntMode);
    /* Initialize interrupts */
    /* Note: TX interrupt must be enabled when data is ready to be transmitted */
    /* The following code can be used to enable TX Interrupt */
    /* PLIB_INT_SourceEnable(INT_ID_0, INT_SOURCE_USART_1_TRANSMIT); */
    PLIB_INT_SourceEnable(INT_ID_0, INT_SOURCE_USART_1_RECEIVE);
    PLIB_INT_SourceEnable(INT_ID_0, INT_SOURCE_USART_1_ERROR);
    PLIB_INT_VectorPrioritySet(INT_ID_0, INT_VECTOR_UART1, INT_PRIORITY_LEVEL1);
    PLIB_INT_VectorSubPrioritySet(INT_ID_0, INT_VECTOR_UART1, INT_SUBPRIORITY_LEVEL0);
    
    PLIB_USART_Enable(configData->usartId);
}

void STIMULUS_USART_DRV_TransmitStart(TM_TEST_CASE_INFO *pTCObj, DRV_CALLBACK Callback)
{
    /*gStimulusBuffObj.pTxBuffer = stimulusList[pTCObj->iTestScenario].list[pTCObj->iTestCaseID].buffer;
    gStimulusBuffObj.nBytestoTransmit = strlen(gStimulusBuffObj.pTxBuffer);*/
    gStimulusBuffObj.pTxBuffer = pTCObj->ModulesID[0].BufferPtr;
    gStimulusBuffObj.nBytestoTransmit = pTCObj->ModulesID[0].length;
    
    gStimulusBuffObj.Scenario = STIMULUS_TRANSMIT;
    gStimulusBuffObj.iTestCaseID = pTCObj->TestCaseID;
    sizeTotal = gStimulusBuffObj.nBytestoTransmit;
    
    gStimulusBuffObj.nBytesReceived = 0;
    gStimulusBuffObj.nBytesTransmitted = 0;
    
    STIMULUS_Callback = Callback;
    Console_Usart_Write_String("Data Tx");
    Console_Usart_Write_Data(gStimulusBuffObj.pTxBuffer,gStimulusBuffObj.nBytestoTransmit);
    PLIB_USART_TransmitterEnable(pTCObj->ModulesID[0].InstanceID);
    PLIB_INT_SourceEnable(INT_ID_0, INT_SOURCE_USART_1_TRANSMIT);
}

void STIMULUS_USART_DRV_ReceiveStart(TM_TEST_CASE_INFO *pTCObj, DRV_CALLBACK Callback)
{
    /*gStimulusBuffObj.pRxBuffer = stimulusList[pTCObj->iTestScenario].list[pTCObj->iTestCaseID].buffer;
    gStimulusBuffObj.nBytestoReceive = strlen(gStimulusBuffObj.pRxBuffer);*/
    gStimulusBuffObj.pRxBuffer = pTCObj->ModulesID[0].BufferPtr;
    gStimulusBuffObj.nBytestoReceive = pTCObj->ModulesID[0].length;
    
    gStimulusBuffObj.Scenario = STIMULUS_RECEIVE;
    gStimulusBuffObj.iTestCaseID = pTCObj->TestCaseID;
    
    gStimulusBuffObj.nBytesReceived = 0;
    STIMULUS_Callback = Callback;
    Console_Usart_Write_String("Data Rx Expected");
    Console_Usart_Write_Data(pTCObj->ModulesID[0].BufferPtr,pTCObj->ModulesID[0].length);
    PLIB_USART_ReceiverEnable(pTCObj->ModulesID[0].InstanceID);
}

TM_TC_RESULT STIMULUS_USART_DRV_DataVerify()
{    
    int i = 0;
    TM_TC_RESULT Status = TM_TC_FAIL;
    char *pBuffer = gStimulusBuffObj.pRxBuffer;
    
    switch(gStimulusBuffObj.Scenario)
    {
        case STIMULUS_RECEIVE:
        {
            for(i=0; i<gStimulusBuffObj.nBytesReceived; i++, pBuffer++)
            {
                if(rxStimulusBuff[i] == *pBuffer)
                {
                    Status =  TM_TC_PASS;
                }
                else
                {
                    Status =  TM_TC_FAIL;
                    break;
                }
            }
        }
        break;
        
        case STIMULUS_TRANSMIT:
        {
            if(gStimulusBuffObj.nBytestoTransmit == gStimulusBuffObj.nBytesTransmitted)
            {
                Status = TM_TC_PASS;
            }
            else
            {
                Status = TM_TC_FAIL;
            }
        }
        break;
    }
    return Status;
}

bool STIMULUS_USART_DRV_PutCharacter(const char character)
{
    /* Check if buffer is empty for a new transmission */
    if(PLIB_USART_TransmitterIsEmpty(configData->usartId))
    {
        /* Send character */
        PLIB_USART_TransmitterByteSend(configData->usartId, character);
        return true;
    }
    else
    {
        return false;
    }
}

void STIMULUS_USART_DRV_ReceiveTask()
{    
    /* Make sure receive buffer has data available */
    if (PLIB_USART_ReceiverDataIsAvailable(configData->usartId))
    {
        if(gStimulusBuffObj.nBytesReceived < gStimulusBuffObj.nBytestoReceive)
        {
            /* Get the data from the buffer */
            rxStimulusBuff[gStimulusBuffObj.nBytesReceived] = PLIB_USART_ReceiverByteReceive(configData->usartId);
            gStimulusBuffObj.nBytesReceived++;
        }
        else
        {
            
        }
        if(gStimulusBuffObj.nBytesReceived == gStimulusBuffObj.nBytestoReceive)
        {
            Console_Usart_Write_String("Data Rx:");
            Console_Usart_Write_Data(&rxStimulusBuff[0],gStimulusBuffObj.nBytesReceived);
            TestCaseInfo.TCResult = TM_TC_PASS;
            STIMULUS_Callback();
        }
        else
        {
            
        }
    }
    else
    {
        
    }
    if(!PLIB_USART_TransmitterIsEmpty(configData->usartId))
    {
        /* Send character */
        PLIB_USART_TransmitterByteSend(configData->usartId, *gStimulusBuffObj.pTxBuffer);
        gStimulusBuffObj.pTxBuffer++;
    }
    else
    {
        
    }
}

void STIMULUS_USART_DRV_TransmitTask()
{
    if(sizeTotal > 0)
    {
        STIMULUS_USART_DRV_PutCharacter(gStimulusBuffObj.pTxBuffer[gStimulusBuffObj.nBytesTransmitted]);
        sizeTotal--;
        gStimulusBuffObj.nBytesTransmitted++;
    }
    else
    {
        PLIB_USART_TransmitterDisable(configData->usartId);
        TestCaseInfo.TCResult = TM_TC_PASS;
        STIMULUS_Callback();
    }
}

/*******************************************************************************
 End of File
*/