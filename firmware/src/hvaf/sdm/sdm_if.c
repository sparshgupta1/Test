/*******************************************************************************
  Implementation of Stimulus Data Manager (SDM) on Tester Side.

  Company:
    Microchip Technology Inc.

  File Name:
    tester_sdm.c

  Summary:
    This file contains the Implementation of SDM on Tester Side.

  Description:

	
*******************************************************************************/

// *****************************************************************************
// *****************************************************************************
// Section: Include Files
// *****************************************************************************
// *****************************************************************************
#include "tm_tester_local.h"
#include "sdm_if.h"
//#include "sdm_tasks.h"

//#include "../stimulus/usart/stimulus_data.h"
// *****************************************************************************
// *****************************************************************************
// Section: File Scope Variables
// *****************************************************************************
// *****************************************************************************
/* SDM Object */
extern SDM_OBJ gSDMObj;

// *****************************************************************************
// *****************************************************************************
// Section: File Scope Functions
// *****************************************************************************
// *****************************************************************************
/*******************************************************************************
  Function: SDM_ERROR_CODES SDM_IsConfigDataValid(uint8_t ConfigID)

  Summary:
    Checks the validity of configuration index.

  Description:
    This routine checks the configuration index passed from the Test Manager.

  Remarks:
    Refer to sdm_if.h for usage information.

*/
SDM_ERROR_CODES SDM_IsConfigDataValid(uint8_t ConfigID)
{
    /* Set status to valid */
    SDM_ERROR_CODES status = SDM_SUCCESS;
    
    /* Check the requested Configuration Index */
    if( ConfigID > gSDMObj.sdmStimulusData.totalConfigs)
    {
        /* Invalid TC config index */
        status = SDM_INVALID_TC_CONFIG_ID;
    }
    
    return(status);
}
/*******************************************************************************
  Function: SDM_ERROR_CODES SDM_IsTestDataValid(uint8_t ConfigID)

  Summary:
    Checks the validity of test case details.

  Description:
    This routine checks the test case details passed from the Test Manager.

  Remarks:
    Refer to sdm_if.h for usage information.

*/
SDM_ERROR_CODES SDM_IsTestDataValid(TM_TEST_CASE_INFO *Obj, 
                                    DRV_CALLBACK TesterCallback)
{
    /* Set status to valid */
    SDM_ERROR_CODES status = SDM_SUCCESS;
     
    if(Obj == NULL)
    {
        /* Invalid TC Data */
        status = SDM_INVALID_TC_DATA;
    }
    
    if(TesterCallback == NULL)
    {
        /* Invalid TC Data */
        status = SDM_INVALID_TC_CALLBACK;
    }
    
    /* Check the requested Configuration Index */
    if(Obj->ScenarioID > gSDMObj.sdmStimulusData.totalScenarios)
    {
        /* Invalid TC Scenario index */
        status = SDM_INVALID_TC_SCENARIO_ID;
    }
    /*else if(Obj->iTestCaseID > gSDMTestObj.iTotalTestCases)
    {
        // Invalid TC  index
        status = SDM_INVALID_TC_DATA_ID;
    }*/
    
    return(status);
}


// *****************************************************************************
// *****************************************************************************
// Section: Interface Function Definitions
// *****************************************************************************
// *****************************************************************************
/*******************************************************************************
  Function: void SDM_Interface_Initialize(void)

  Summary:
    Performs the necessary actions to initialize the SDM Interface.

  Description:
    This routine performs the necessary actions to initialize the SDM Interface.

  Remarks:
    Refer to sdm_if.h for usage information.

*/
void SDM_Interface_Initialize(void)
{
    /* Initialize the SDM Flag and state */
    gSDMObj.callbackConfig   = NULL;
    gSDMObj.callbackStimulus = NULL;
    gSDMObj.sdmState         = SDM_INIT;
}

/*******************************************************************************
  Function: SDM_ERROR_CODES SDM_ConfigStimulus(uint8_t ConfigID)

  Summary:
    Receives the configuration index.

  Description:
    This routine receives the configuration index from the Test Manager.

  Remarks:
    Refer to sdm_if.h for usage information.

*/
SDM_ERROR_CODES SDM_ConfigStimulus(uint8_t ConfigID)
{
    /* Initialize the initial status */
    SDM_ERROR_CODES status = SDM_SUCCESS;

    /* Check the validity of Test Config Data */
    status = SDM_IsConfigDataValid(ConfigID);
    
    if(status == SDM_SUCCESS)
    {
        /* Get the Configuration ID Details */
        //sdmStimulusData.iConfigId  = ConfigID;
        
        /* Set the flag to indicate configuration request from Tester */
        gSDMObj.sdmEvent(SDM_CONFIG_REQUEST);
    }
    
    return(status);
}
/*******************************************************************************
  Function: SDM_ERROR_CODES SDM_StimulusStart(TM_TEST_CASE_INFO *Obj, 
                                              DRV_CALLBACK TesterCallback)

  Summary:
    Receives the Test case details.

  Description:
    This routine receives the test case details from the Test Manager.

  Remarks:
    Refer to sdm_if.h for usage information.

*/
SDM_ERROR_CODES SDM_StimulusStart(TM_TEST_CASE_INFO *Obj, 
                                  DRV_CALLBACK TesterCallback)
{
     /* Initialize the initial status */
    SDM_ERROR_CODES status = SDM_SUCCESS;
    
    if(gSDMObj.bStimulusInProgress == false)
    {
        if(gSDMObj.bConfigComplete)
        {
            /* Check the validity of Test Data */
            status = SDM_IsTestDataValid(Obj, TesterCallback);
        }
        else
        {
            /* Set the flag for Peripheral not Configured */
            status = SDM_NO_CONFIG;
        }

        if(status == SDM_SUCCESS)
        {
            /* Get the copy of Test Case Details */
            /* gSDMTestObj.iTestCaseID   = Obj->iTestCaseID;
            gSDMTestObj.iTestScenario = Obj->iTestScenario;
            gSDMTestObj.iTestPeripheral = Obj->iTestPeripheral;
            gSDMTestObj.iTestInstance = Obj->iTestInstance;
            gSDMTestObj.pBuffer = Obj->pBuffer;
            gSDMTestObj.iLength = Obj->iLength;
            */
            /* Register the Tester Callback */
            gSDMObj.callbackStimulus = TesterCallback;
            /* Set the flag to indicate request from Tester */
            gSDMObj.sdmEvent(SDM_STIMULUS_REQUEST);
        }
    }
    else
    {
        status = SDM_TEST_IN_PROGRESS;
    }
    
    /* return status */
    return(status);
}





