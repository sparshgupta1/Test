/*******************************************************************************
  MPLAB Harmony Tester Sample Stimulus Data File

  File Name:
    sample_stimulus_data.c

  Summary:
    This file contains sample stimulus data.

  Description:
	
 *******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2013-2015 released Microchip Technology Inc.  All rights reserved.

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
#include "peripheral/usart/plib_usart.h"
#include "uart_stimulus.h"
#include "stimulus_data.h"

// *****************************************************************************
// *****************************************************************************
// Section: Sample Configuration Data
// *****************************************************************************
// *****************************************************************************

/* Stimulus Configuration List  */

const DRV_USART_CONFIG_INIT drvUSARTInitData =
{
    .usartId            = USART_ID_1,
    .mode               = USART_TRANSMIT_FIFO_NOT_FULL,
    .lineControl        = USART_8N1,
    .txIntMode          = USART_TRANSMIT_FIFO_IDLE,
    .rxIntMode          = USART_RECEIVE_FIFO_ONE_CHAR,
    .baudRate           = 9600, 
    .interruptTransmit  = INT_SOURCE_USART_1_TRANSMIT,
    .interruptReceive   = INT_SOURCE_USART_1_RECEIVE,
};

STIMULUS_CONFIG_DATA testConfig[] = 
{
    { 
        .name       = "Test Configuration 1",
        .ConfigData = (SYS_MODULE_INIT *) &drvUSARTInitData,  
    }
};

// *****************************************************************************
// *****************************************************************************
// Section: Sample Stimulus Data
// *****************************************************************************
// *****************************************************************************
// *****************************************************************************
/* Array of Stimulus

   This is an array of structures that provide  stimulus data necessary for the
   SDM to run a test.  
*/

STIMULUS_DATA stimulusList[] =
{
    {
        .name       	= "USART Receive Functional Test",
        .initialize     = STIMULUS_USART_DRV_Initialize,
        .start          = STIMULUS_USART_DRV_ReceiveStart,
        .task           = {NULL, NULL},
        .verify         = STIMULUS_USART_DRV_DataVerify,
        .reset          = STIMULUS_USART_DRV_Reset,
        .status         = NULL,
    },
    
    {
        .name       	= "USART Transmit Functional Test",
        .initialize     = STIMULUS_USART_DRV_Initialize,
        .start          = STIMULUS_USART_DRV_TransmitStart,
        .task           = {NULL, NULL},
        .verify         = STIMULUS_USART_DRV_DataVerify,
        .reset          = STIMULUS_USART_DRV_Reset,                
        .status         = NULL,
    },    
};

/* Test Harness Initialization Structure */
static const STIMULUS_INIT_DATA stimulusData =
{
    .totalScenarios  = sizeof(stimulusList) / sizeof(STIMULUS_DATA),
    .totalConfigs    = sizeof(testConfig) / sizeof(STIMULUS_CONFIG_DATA),
    .tests           = stimulusList,
    .config          = testConfig
};

void STIMULUS_GetTestsStat(STIMULUS_INIT_DATA *pstimulusDataObj)
{
    /* Copy Test statistics data */
    pstimulusDataObj->totalScenarios  = stimulusData.totalScenarios;
    //pstimulusDataObj->totalTestCases  = stimulusData.totalTestCases;
    pstimulusDataObj->totalConfigs    = stimulusData.totalConfigs;
    pstimulusDataObj->tests           = stimulusData.tests;
    pstimulusDataObj->config          = stimulusData.config;
}
/*******************************************************************************
 End of File
*/

