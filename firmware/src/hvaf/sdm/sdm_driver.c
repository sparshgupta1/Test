
/*******************************************************************************
  Implementation of Stimulus Data Manager (SDM) driver on Tester Side.

  Company:
    Microchip Technology Inc.

  File Name:
    sdm_driver.c

  Summary:
    Implementation of Stimulus Data Manager (SDM) driver on Tester Side.

  Description:

	
*******************************************************************************/

// *****************************************************************************
// *****************************************************************************
// Section: Include Files
// *****************************************************************************
// *****************************************************************************
#include "sdm_driver.h"
#include "tm_tester_local.h"
#include "stimulus_data.h"
#include "uart_stimulus.h"

// *****************************************************************************
// *****************************************************************************
// Section: File Scope Variables
// *****************************************************************************
// *****************************************************************************
extern STIMULUS_CONFIG_DATA testConfig[];
extern STIMULUS_DATA        stimulusList[];
extern STIMULUS_TEST_LIST testCaseList1[];
// *****************************************************************************
// *****************************************************************************
// Section: File Scope Functions
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
// *****************************************************************************
// Section: Interface Function Definitions
// *****************************************************************************
// *****************************************************************************
/*******************************************************************************
  Function:
    bool SDM_STIMULUS_Initialize ( uint32_t )

  Summary:
    Initializes the board, services, drivers, application and other modules.

  Remarks:
    See prototype in system/common/sys_module.h.
 */

void SDM_STIMULUS_Initialize ( uint32_t iConfigID )
{ 
    if(stimulusList[iConfigID].initialize != NULL)
    {
        /* SDM calls Peripheral Initialize */
        stimulusList[iConfigID].initialize(testConfig[iConfigID].instance,
                                          (testConfig[iConfigID].ConfigData));    
    }
}

/*******************************************************************************
  Function: void SDM_STIMULUS_Start(TM_TEST_CASE_INFO *tcSDMObj, 
                                    DRV_CALLBACK drvCallBack)

  Summary:
    Start the test case operation.

  Description:
    This routine starts the Transmit/Receive stimulus.

  Remarks:
    Refer to sdm_driver.h for usage information.

*/
void SDM_STIMULUS_Start(TM_TEST_CASE_INFO *tcSDMObj, DRV_CALLBACK drvCallBack)
{
    if(stimulusList[tcSDMObj->ScenarioID].start != NULL)
    {
        /* SDM calls Peripheral Receive */
        stimulusList[tcSDMObj->ScenarioID].start(tcSDMObj, drvCallBack);
    }
}


/*******************************************************************************
  Function: void SDM_STIMULUS_Verify(TM_TEST_CASE_INFO *tcSDMObj)

  Summary:
    Verify the test case operation.

  Description:
    This routine verify the Transmit/Receive operations.

  Remarks:
    Refer to sdm_driver.h for usage information.

*/
TM_TC_RESULT SDM_STIMULUS_Verify(TM_TEST_CASE_INFO *tcSDMObj)
{
    if(stimulusList[tcSDMObj->ScenarioID].verify != NULL)
    {
        /* SDM calls Peripheral Verify Routine */
        return(stimulusList[tcSDMObj->ScenarioID].verify());
    }
}

/*******************************************************************************
  Function: void SDM_STIMULUS_Reset(TM_TEST_CASE_INFO *tcSDMObj)

  Summary:
    Resets the module under test.

  Description:
    This routine resets the stimulus required for the module under test.

  Remarks:
    Refer to sdm_driver.h for usage information.

*/
void SDM_STIMULUS_Reset(TM_TEST_CASE_INFO *tcSDMObj)
{
    if(stimulusList[tcSDMObj->ScenarioID].reset != NULL)
    {
        /* SDM calls Peripheral Reset Routine */
        stimulusList[tcSDMObj->ScenarioID].reset();
    }
}