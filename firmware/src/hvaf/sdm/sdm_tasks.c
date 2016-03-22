/*******************************************************************************
  Implementation of Stimulus Data Manager (SDM) on Tester Side.

  Company:
    Microchip Technology Inc.

  File Name:
    tester_sdm.c

  Summary:
    This file contains the Implementation of SDM Task.

  Description:
    This file has the implementation of SDM state machine.
 
*******************************************************************************/

// *****************************************************************************
// *****************************************************************************
// Section: Include Files
// *****************************************************************************
// *****************************************************************************
#include "sdm_if.h"
#include "sdm_tasks.h"
#include "stimulus_data.h"
// *****************************************************************************
// *****************************************************************************
// Section: File Scope Variables
// *****************************************************************************
// *****************************************************************************

/* Internal Interface Variables */
SDM_OBJ            gSDMObj;

/* Test Case Info */
extern TM_TEST_CASE_INFO TestCaseInfo;
// *****************************************************************************
// *****************************************************************************
// Section: File Scope Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function: void SDM_EventHandler(SDM_STIMULUS_EVENT event)

  Summary:
    Event Handler for SDM.

  Description:
    This routine handles the events from SDM Interface.

  Remarks:
    Refer to sdm_tasks.h for usage information.

*/
void SDM_EventHandler(SDM_STIMULUS_EVENT event)
{
    switch(event)
    {
        case SDM_CONFIG_REQUEST:
        {
            gSDMObj.bConfigRequest = true;
            break;
        }
        case SDM_STIMULUS_REQUEST:
        {
            gSDMObj.bStimulusRequest = true;
            break;
        }
        default:
        {
            gSDMObj.bStimulusRequest = false;
            break;
        }
    }
}

/*******************************************************************************
  Function: void SDM_DriverCallback(SDM_DRV_CALLBACK event, bool bResult)

  Summary:
    Callback Handler for SDM.

  Description:
    This routine handles the callback from SDM task.

  Remarks:
    Refer to sdm_tasks.h for usage information.

*/
//void SDM_DriverCallback(SDM_DRV_CALLBACK event, bool bResult)
void SDM_DriverCallback()
{
    /* Set the flag indicating completing of stimulus */
    gSDMObj.bStimulusComplete = true;
}

/*******************************************************************************
  Function: void SDM_Initialize(void)

  Summary:
    Initialize the SDM data structures.

  Description:
    This routine initializes the SDM data structures and state.

  Remarks:
    Refer to sdm_tasks.h for usage information.

*/
void SDM_Initialize()
{    
    /*Initialize SDM Data Structures */
    gSDMObj.bConfigRequest      = false;
    gSDMObj.bStimulusRequest    = false;
    gSDMObj.bConfigComplete     = false;
    gSDMObj.bStimulusInProgress = false;
    gSDMObj.bStimulusComplete   = false;

    /* Register the event handler between SDM Interface & SDM Task */
    gSDMObj.sdmEvent            = SDM_EventHandler;
    /* Initialize SDM Timer */
    gSDMObj.sdmTimer            = NULL;
    
    /* Get Test Statistics */
    STIMULUS_GetTestsStat(&gSDMObj.sdmStimulusData);
    
    /* Get Test Details */
    //gSDMTestObj.iTotalScenarios = sdmStimulusData.totalScenarios;
    //gSDMTestObj.iTotalTestCases = sdmStimulusData.totalTestCases;
    //gSDMTestObj.iTotalConfigs   = sdmStimulusData.totalConfigs;
}

// *****************************************************************************
// *****************************************************************************
// Section: Interface Function Definitions
// *****************************************************************************
// *****************************************************************************
/*******************************************************************************
  Function: void SDM_Task()

  Summary:
    SDM Tasks.

  Description:
    This routine runs the SDM tasks and maintain the SDM state machine.

  Remarks:
    Refer to sdm_tasks.h for usage information.

*/
void SDM_Task()
{
    /*bool bConfigStatus = false;*/
   
    switch(gSDMObj.sdmState)
    {
        case SDM_INIT:
        {
            /* Initialize SDM local objects */
            SDM_Initialize();
            
            /* Move the SDM to IDLE state
               where it waits for request from Tester */
            gSDMObj.sdmState = SDM_IDLE;
            break;
        }
        
        case SDM_IDLE:
        {
            if(!gSDMObj.bStimulusInProgress)
            {
                /* SDM Waiting in Idle state to get the TC Data */
                if(gSDMObj.bConfigRequest)
                {
                    /* Move the SDM to the Peripheral Initialize */
                    gSDMObj.sdmState = SDM_PERIPHERAL_INIT;
                    gSDMObj.bConfigRequest = false;
                }
                else if(gSDMObj.bStimulusRequest)
                {
                    /* Move the SDM to Start Stimulus */
                    gSDMObj.sdmState = SDM_STIMULUS_START;
                    gSDMObj.bStimulusRequest = false;
                }
                else
                {
                    /* Move the SDM to IDLE State */
                    gSDMObj.sdmState = SDM_IDLE;
                }
            }
            else
            {
                /* Handling unexpected requests from tester During the Stimulus */
                if(gSDMObj.bConfigRequest)
                {
                    gSDMObj.callbackConfig(SDM_STIMULUS_IN_PROGRESS, false);
                }
                else if(gSDMObj.bStimulusRequest)
                {
                    //gSDMObj.callbackStimulus(SDM_STIMULUS_IN_PROGRESS, false);
                    TestCaseInfo.TCResult = TM_TC_FAIL;
                    gSDMObj.callbackStimulus();
                }
                else
                {
                   // gSDMObj.callbackStimulus(SDM_UNKNOWN_REQUEST, false);
                    TestCaseInfo.TCResult = TM_TC_FAIL;
                    gSDMObj.callbackStimulus();
                }
            }
            break;
        }
        
        case SDM_PERIPHERAL_INIT:
        {
             /*
             * Initialize the Requested Peripheral through SDM Driver Init call.
             */
            //bConfigStatus = SDM_STIMULUS_Initialize(TestCaseInfo.Config);
            SDM_STIMULUS_Initialize(TestCaseInfo.Config);
            
            /* Once the Driver is initialized, move SDM to IDLE state */
            gSDMObj.sdmState        = SDM_IDLE;
            gSDMObj.bConfigComplete = true;
            /*Send callback to Tester, if required in the future */
            /*
            gSDMObj.callbackConfig(SDM_STIMULUS_CONFIG_COMPLETE, bConfigStatus);
             */
            break;
        }
        
        case SDM_STIMULUS_START:
        {
            gSDMObj.bStimulusInProgress = true;
            /* Copy the Test Case data and Read the Data from Table
             * Call SDM Driver Routine for Stimulus
             */
            SDM_STIMULUS_Start(&TestCaseInfo, SDM_DriverCallback);
            
            /* Set the flat to indicate stimulus is in-progress */
            gSDMObj.bStimulusInProgress = true;
            /* Move to END state and wait for the Stimulus Complete */
            gSDMObj.sdmState = SDM_STIMULUS_END;
            /* Get the Timer Tick */
            gSDMObj.sdmTimer = FTMP_GetTimerTick();
            break;
        }
        
        case SDM_STIMULUS_END:
        {
            /*Wait for Stimulus to end */
            if(gSDMObj.bStimulusComplete)
            {
                /*Once stimulus is done,check the result */
                TestCaseInfo.TCResult = SDM_STIMULUS_Verify(&TestCaseInfo);
                
                /* Send the callback to Tester with Test Case Result */
                // gSDMObj.callbackStimulus(SDM_DRV_STIMULUS_COMPLETE, TestCaseInfo.TCResult);
                 gSDMObj.callbackStimulus();
                 
                /* Reset all flags */
                gSDMObj.bStimulusInProgress = false;
                gSDMObj.bStimulusRequest    = false;
                gSDMObj.bStimulusComplete   = false;
                
                /* Move SDM back to Idle state */
                gSDMObj.sdmState = SDM_IDLE;
            }
            else
            {
                /*Check Timer,if it has expired, declare the test as untested*/
                if(FTMP_CheckTimerExpiry(SDM_TIMEOUT_PERIOD_MS, gSDMObj.sdmTimer))
                {
                    /* Reset Stimulus */
                    SDM_STIMULUS_Reset(&TestCaseInfo);
                    
                    /* Set the test result as UNTESTED */
                    TestCaseInfo.TCResult = TM_TC_UNTESTED;
                    
                    /* Send the Call-back to Test Manager */
                    gSDMObj.callbackStimulus();
                    /* Reset SDM Flags */
                    gSDMObj.bStimulusInProgress = false;
                    gSDMObj.bStimulusRequest    = false;
                    gSDMObj.bStimulusComplete   = false;
                    gSDMObj.sdmTimer            = NULL;
                    gSDMObj.sdmState = SDM_IDLE;
                }
            }
            break;
        }
        
        case SDM_PERIPHERAL_DEINIT:
        {
            /* If required, de-init the stimulus */
            gSDMObj.bConfigRequest  = false;
            gSDMObj.bConfigComplete = false;
            break;
        }
       
        case SDM_ERROR:
        {
            break;
        }
    }   
}





