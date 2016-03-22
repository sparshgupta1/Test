/*******************************************************************************
  Test Manager (FUT/TESTER) Implementation

  Company:
    Microchip Technology Inc.

  File Name:
    test_manager.c

  Summary:
    Test Manager (FUT/TESTER) Implementation

  Description:

	
*******************************************************************************/


// *****************************************************************************
// *****************************************************************************
// Section: Include Files
// *****************************************************************************
// *****************************************************************************
#include "tm_tester_local.h"
#include "sdm_datatypes.h"
#include "data_class/data_class.h"
#include <sys/appio.h>

#define MAX_NO_OF_TEST_SCENARIO 10 //need to define TBD
#define MAX_NO_OF_TEST_CASE 10 //need to define TBD
FTMPApdu req_data_ptr;
FTMPApdu res_data_ptr;
char LogString[50];

FTMP_DATA_UNIT reqDataunit[5];
FTMP_DATA_UNIT resDataunit[5];
unsigned int CurPkt,PrevPkt;
TM_TEST_CASE_INFO TestCaseInfo;
SDM_TC_CONFIG_OBJ  gSDMConfigObj;
static int TestCaseIndex = 0;
// *****************************************************************************
// *****************************************************************************
// Section: File Scope Variables
// *****************************************************************************
// *****************************************************************************

typedef struct
{
    uint8_t is_tm_request_to_send;
    bool isClass;
    FTMP_IO_OPERATION op;
    FTMP_DRV_CALLBACK ftmpcallback;  
}FTMP_PACKET_DATA;

typedef struct
{
    FTMPApdu* ftmp_rx_data;
}FTMP_CALLBACK_DATA;

static TM_SYS_DATA stTMSysData;
static FTMP_PACKET_DATA ftmpData;
static FTMP_CALLBACK_DATA callbackdata;
static TM_TC_RESULT TestResultTable[100] = {2}; //TBD Need to put the result.
static int packet_counter = 0;
// *****************************************************************************
// *****************************************************************************
// Section: File Scope Functions
// *****************************************************************************
// *****************************************************************************
TM_STATUS TM_SendFTMPCommand(FTMP_COMMAND_CLASS command);
static bool TMSendFTMPPacket(bool isClassData, FTMP_IO_OPERATION operation,
                                FTMP_DRV_CALLBACK callback);
static TM_STATES TMSendConnectionRequest(void);
static void TMWaitforRequest(void);
static void TMProcessRequest(void);
static void TMClearFTMPHandlerBuffer(void);
static void TMChangeState(TM_STATES);
static TM_STATES TMGetCurrentState(void);

static TM_STATUS TM_IsConnectionEstablished(void);
static TM_STATUS processCommandClass(FTMP_DATA_UNIT *);	
static TM_STATUS processConnectRequest(void);	
static TM_STATUS processSOT(void); 
static TM_STATUS processEOT(void); 
static TM_STATUS processStimulusReq(void); 
static TM_STATUS processLogResult(FTMP_DATA_UNIT *); 
static TM_STATUS processInstanceId(FTMP_DATA_UNIT *);
static TM_STATUS processTestCaseID(FTMP_DATA_UNIT *);
static TM_STATUS processConfigChange(FTMP_DATA_UNIT *);
static TM_STATUS processDataClass(FTMP_DATA_UNIT*);
static void clearTestCaseInfo(void);

// *****************************************************************************
// *****************************************************************************
// Section: Interface Function Definitions
// *****************************************************************************
// *****************************************************************************

void TM_Tester_Init(void)
{
    int i = 0;
    /* Initialize FTMP Communication */
    FTMP_SysInit();
    req_data_ptr.data_unit = (FTMP_DATA_UNIT*)&reqDataunit[0];
    res_data_ptr.data_unit = (FTMP_DATA_UNIT*)&resDataunit[0];
    
    /*SDM initialize*/
    SDM_Interface_Initialize();
    
    /* Initialize Test Manager system Variables */
    stTMSysData.state = TM_STATE_INIT;
    stTMSysData.is_connected = false;
    FTMP_HandlerRegister(&req_data_ptr, TM_RecvCallback);  
	clearTestCaseInfo();
	TestCaseInfo.Config = false;
    for(i=0;i<100;i++)
    {
        TestResultTable[i] = 2;
    }
}

void TM_Tester_Task(void)
{
    switch(stTMSysData.state)
    {
        case TM_STATE_INIT:
        {
            Console_Usart_Write_String("Init");
            TMChangeState(TM_STATE_CONNECT_WAIT);
            break;       
        }
        case TM_STATE_CONNECT_WAIT:
        {           
            /* Check TM is waiting for request */
            TMWaitforRequest();
            /* Check if FUT-Tester is already got connected */
            if(stTMSysData.is_connected)
            {  
                /* Connection already established, Moving back to Idle State */
                TMChangeState(TM_STATE_IDLE_LOOP);
            }
            break;
        }
        case TM_STATE_IDLE_LOOP:
        {                
            /* Check TM is waiting for request */
            TMWaitforRequest();
            break;
        }        
        case TM_STATE_BUSY:
        {
            TMWaitforRequest();
            break;
        }
        case TM_STATE_ERROR:
        {
            while(1);
            
            break;
        }            
    }
}

static void TMWaitforRequest(void)
{
    if(stTMSysData.is_request_rcvd)
    {
        /* Decode the request from FUT */
        TMProcessRequest();
                        
        /* Clear the flags */
        stTMSysData.is_request_rcvd = false;
    }
}

static void TMProcessRequest(void)
{
    	FTMP_DATA_UNIT *rx_data = (FTMP_DATA_UNIT *)callbackdata.ftmp_rx_data->data_unit;
    	FTMP_DATA_UNIT *tmpData;
      	TM_STATUS Status;	
        do{
	        tmpData = rx_data;
            _APPO = (unsigned int)rx_data->uDI.all;
            CurPkt = (unsigned int)rx_data->uDI.all;
            if(TMGetCurrentState()== TM_STATE_BUSY)
            {
                Status = TM_FAILURE;
                break;
            }
            if(PrevPkt == CurPkt)
            {
                Status = TM_SUCCESS;
                break;
            }
        	//for each DataUnits, parse the Data
        	//Process all Data classes A,B,C,D,E,F 
        	else if (tmpData->uDI.cl <= CLASS_F) 
       		{
                Status = processDataClass(tmpData);
        	}
        	else if (tmpData->uDI.cl == CLASS_G) //Test case info packet
            {
                Status = processTestCaseID(tmpData);
            }
            else if (tmpData->uDI.cl == CLASS_H) //Peripheral id,instance id 
            {
                if(tmpData->uDI.index_start!=tmpData->uDI.index_end)
                {
                    Status = TM_FAILURE;
                    break;
                }
                Status = processInstanceId(tmpData);
            }
            else if(tmpData->uDI.cl == CLASS_I)
        	{
                if(tmpData->uDI.index_start!=tmpData->uDI.index_end)
                {
                    Status = TM_FAILURE;
                    break;
                }
		
                Status = processCommandClass(tmpData);	
            		
    		}
            else if (tmpData->uDI.cl == CLASS_J) //Configuration change request
            {
                if(tmpData->uDI.index_start!=tmpData->uDI.index_end)
                {
                    Status = TM_FAILURE;
                    break;
                }
                Status = processConfigChange(tmpData);
            }
        	else //any other type --Need to check Class K
        	{
			//TBD
        	}
            if(stTMSysData.is_connected != true)
            {
                Status = TM_FAILURE;
                break;
            }
        	rx_data = rx_data->next_data_unit_ptr;
            PrevPkt = CurPkt;
    	}while( (tmpData->next_data_unit_ptr != NULL) && (tmpData->uDI.is_next_class != false) );
    
	if(Status == TM_SUCCESS)
	{
    	if(TM_SUCCESS == TM_SendFTMPCommand(FTMP_HNDLR_ACK))
		{
			Status = true;
		}
		else
		{
			Status = false;
		}
	}
	else if(Status == TM_FAILURE)
	{
    	if(TM_SUCCESS == TM_SendFTMPCommand(FTMP_HNDLR_BUSY))
		{
			Status = true;
		}
		else
		{
			Status = false;
		}
	}
    else
    { // if TM_UNSUPPORTED
        if(TM_SUCCESS == TM_SendFTMPCommand(FTMP_HNDLR_SEQ_BREAK))
		{
			Status = true;
		}
		else
		{
			Status = false;
		}    
    
    }

}

static TM_STATUS processCommandClass(FTMP_DATA_UNIT *tmpData)
{
	TM_STATUS Status;
	if(tmpData->uDI.index_start == FTMP_HNDLR_CONNECT_REQUEST)
        {
		Status = processConnectRequest();	
	}
	else if(tmpData->uDI.index_start == FTMP_HNDLR_GET_TEST_CONFIG)
        {
		//TBD
		/*TesterFormRawDataPacket();
 		FTMP_HNDLR_SendBuffer(true,FTMP_WRITE_OP,0x00,NULL);
		*/
	}
	else if(tmpData->uDI.index_start == FTMP_HNDLR_SOT)
	{
		Status = processSOT(); 
	}
	else if(tmpData->uDI.index_start == FTMP_HNDLR_EOT)
	{
		Status = processEOT();
		//if(Status == TM_SUCCESS)
		{
			clearTestCaseInfo();
		}
	}
	else if(tmpData->uDI.index_start == FTMP_HNDLR_STIM_REQ)
	{
		Status = processStimulusReq();
	}
	else if((tmpData->uDI.index_start == FTMP_HNDLR_PASS) || (tmpData->uDI.index_start == FTMP_HNDLR_FAIL) || (tmpData->uDI.index_start == FTMP_HNDLR_TESTER))
	{	
		Status = processLogResult(tmpData);
	}
	else
	{
		//TBD - any other commands
	}

	return Status;

}	
static TM_STATUS processDataClass(FTMP_DATA_UNIT *tmpData)
{
    TM_STATUS Status;
    CLASS_DATA_ITEMS TMClassInfo;
    DC_STATUS_CODES DataStatus;
    
    TMClassInfo.className = tmpData->uDI.cl;
    TMClassInfo.startIndex = tmpData->uDI.index_start;
    TMClassInfo.endIndex = tmpData->uDI.index_end;
    TMClassInfo.subIndexStart = tmpData->uDI.sub_index_start;
    TMClassInfo.subIndexEnd = tmpData->uDI.sub_index_end;
    
    DataStatus = DC_GetClassData(TMClassInfo,&TestCaseInfo.ModulesID[TestCaseInfo.BufferIndex].BufferPtr ,&TestCaseInfo.ModulesID[TestCaseInfo.BufferIndex].length);
   
    if(DataStatus == DC_SUCCESS)
    {
       // gSDMTestObj.pBuffer = TestCaseInfo.ModulesID[TestCaseInfo.BufferIndex].BufferPtr;
       // gSDMTestObj.iLength = TestCaseInfo.ModulesID[TestCaseInfo.BufferIndex].length;
        Status = TM_SUCCESS;
    }
    else
    {
        Status = TM_FAILURE;
    }
    
    TestCaseInfo.BufferIndex++;
    return Status;
    
}
static TM_STATUS processConnectRequest(void)
{
	stTMSysData.is_connected = true;
    Console_Usart_Write_String("Tester Connected.!");
    return (TM_SUCCESS);
}	
void TM_SDMCallback(void)
{
        TMChangeState(TM_STATE_IDLE_LOOP);
        
}
static TM_STATUS processInstanceId(FTMP_DATA_UNIT *rx_data)
{
    TM_STATUS Status;
    TestCaseInfo.ModulesID[TestCaseInfo.BufferIndex].PeripheralID = rx_data->uDI.index_start;
    TestCaseInfo.ModulesID[TestCaseInfo.BufferIndex] .InstanceID = (rx_data->uDI.sub_index_start<<4) | (rx_data->uDI.sub_index_end) ;
    //gSDMTestObj.iTestPeripheral = TestCaseInfo.ModulesID[TestCaseInfo.BufferIndex].PeripheralID;
    //gSDMTestObj.iTestInstance = TestCaseInfo.ModulesID[TestCaseInfo.BufferIndex] .InstanceID;
    Status = TM_SUCCESS;
    
    return Status;
}
static TM_STATUS processTestCaseID(FTMP_DATA_UNIT *rx_data)
{
	TM_STATUS Status;
    if((TestCaseInfo.SOT == true) && (TestCaseInfo.EOT == false)) 
	{
		TestCaseInfo.ScenarioID = (rx_data->uDI.index_start<<8) | (rx_data->uDI.index_end) ;
		TestCaseInfo.TestCaseID = (rx_data->uDI.sub_index_start<<4) | (rx_data->uDI.sub_index_end) ;
		//gSDMTestObj.iTestScenario = (uint32_t)TestCaseInfo.ScenarioID;
        //gSDMTestObj.iTestCaseID = (uint32_t)TestCaseInfo.TestCaseID;
        Status = TM_SUCCESS;   
        sprintf(LogString, "Scenario: %d Test Case: %d,", 
                    TestCaseInfo.ScenarioID,TestCaseInfo.TestCaseID);
         Console_Usart_Write_String(LogString);
	}
    else
    {
        Status = TM_UNSUPPORTED;
    }
	return Status;
}
static TM_STATUS processConfigChange(FTMP_DATA_UNIT *rx_data)
{
    SDM_ERROR_CODES SDMStatus;
    TM_STATUS Status;
    Console_Usart_Write_String("CNG CONF REQ");
    TestCaseInfo.Config = rx_data->uDI.index_start;
    //gSDMConfigObj.iConfigId = TestCaseInfo.Config;
    SDMStatus = SDM_ConfigStimulus(TestCaseInfo.Config);
    if(SDMStatus == SDM_SUCCESS)
    {
        Status = TM_SUCCESS;
    }
    else
    {
        Status = TM_FAILURE;
    }
    return (Status);
}
static TM_STATUS processSOT(void)
{
	TM_STATUS Status;
	if((TestCaseInfo.EOT == true) && (TestCaseInfo.SOT == false))
	{
		TestCaseInfo.SOT = true;
        TestCaseInfo.EOT = false;
		Status = TM_SUCCESS;
        Console_Usart_Write_String("----SOT----");
	}
    else if((TestCaseInfo.SOT == true))
    {
        Console_Usart_Write_String("--Re SOT---");
        Status = TM_SUCCESS;
    }
    else
    {
        Status = TM_UNSUPPORTED;
    }
	return Status;
}	
static TM_STATUS processEOT(void)
{
	TM_STATUS Status;
	if((TestCaseInfo.SOT == true))
	{
		TestCaseInfo.EOT = true;
		Status = TM_SUCCESS;
        Console_Usart_Write_String("----EOT----\r\n");
  
	}
    else if(TestCaseInfo.EOT == true)
    {
        Console_Usart_Write_String("--Re EOT---");
        Status = TM_SUCCESS;
    }
    else
    {
        Status = TM_UNSUPPORTED;
    }
	return Status;
}	
static TM_STATUS processStimulusReq(void)
{
    SDM_ERROR_CODES SDMStatus;
	TM_STATUS Status;
	if((TestCaseInfo.SOT == true) && (TestCaseInfo.EOT == false))
	{
        Console_Usart_Write_String("STM");
        SDMStatus = SDM_StimulusStart(&TestCaseInfo, TM_SDMCallback);
        if(SDMStatus == SDM_SUCCESS)
        {
             Status = TM_SUCCESS;
             TMChangeState(TM_STATE_BUSY);
        }
        else
        {
            Status = TM_FAILURE;
        }
		
	}
    else
    {
        Status = TM_UNSUPPORTED;
    }
	return Status;
}	
static TM_STATUS processLogResult(FTMP_DATA_UNIT *rx_data)
{
	TM_STATUS Status;
    TM_TC_RESULT Result = TM_TC_UNTESTED;
    

	if(rx_data->uDI.index_start != rx_data->uDI.index_end)
	{
		Status = TM_FAILURE;
	}
    if((TestCaseInfo.SOT == true) && (TestCaseInfo.EOT == false))
    {
        if(rx_data->uDI.index_start == FTMP_HNDLR_TESTER)
        {
            Result = TestCaseInfo.TCResult;
        }
        else
        {
            if(rx_data->uDI.index_start == FTMP_HNDLR_FAIL)
            {
                Result = TM_TC_FAIL;
            }
            else
            {
                Result = TM_TC_PASS;
            }
        }
        TestResultTable[TestCaseIndex] = Result;
        TestCaseIndex++;
        if(Result == TM_TC_PASS)
        {
            sprintf(LogString, "Test Case ID: %d, Result: PASS", 
                    TestCaseInfo.TestCaseID);
        }
        else if(Result == TM_TC_FAIL)
        {
            sprintf(LogString, "Test Case ID: %d, Result: FAIL", 
                    TestCaseInfo.TestCaseID);
        }
        else
        {
            sprintf(LogString, "Test Case ID: %d, Result: FAIL", 
                    TestCaseInfo.TestCaseID);
        }
        Console_Usart_Write_String(LogString);
//        if(TestCaseIndex>=6)
//        {
//            Nop();
//        }
        Status = TM_SUCCESS;
    }
	else
    {
        Status = TM_UNSUPPORTED;
    }
    return Status;
}
static void clearTestCaseInfo(void)
{
    int i = 0;
    for(i=0;i<MAX_NO_MODULES; i++)
    {
        TestCaseInfo.ModulesID[i].PeripheralID = 0;
        TestCaseInfo.ModulesID[i].InstanceID = 0;
        TestCaseInfo.ModulesID[i].BufferPtr = NULL;
        TestCaseInfo.ModulesID[i].length = 0;
    }
    TestCaseInfo.BufferIndex = 0;
    TestCaseInfo.ScenarioID = 0;
	TestCaseInfo.TestCaseID = 0;
	TestCaseInfo.SOT = false;
	TestCaseInfo.EOT = true;
	TestCaseInfo.Log_result = false;
}
/* Transmits FTMP Packet
 * isClassData  - Is it class or raw message to be sent
 * operation    - Is it WR/RD operation
 * callback     - Function to be invoked upon receiving response from Tester
 * returns FTMP message successfully sent or not
 */
static bool TMSendFTMPPacket(bool isClassData, FTMP_IO_OPERATION operation,
                                FTMP_DRV_CALLBACK callback)
{     
    /* Copy the details which will be used for retry */
    ftmpData.isClass = isClassData;
    ftmpData.ftmpcallback = NULL;
         
    /* FTMP Handler call to Send Message */
    return FTMP_HNDLR_SendBuffer(isClassData, operation, 0, NULL);
   
}
/* Transmits the FTMP Command Message 

* command     - FTMP Command
* returns the message successfully sent or not.
*/
TM_STATUS TM_SendFTMPCommand(FTMP_COMMAND_CLASS command)
{
    /* Clear the Buffer before adding any fresh request */
    TMClearFTMPHandlerBuffer();
    _APPO = (unsigned int)command;
    /* Add Command Class to FTMP Handler buffer */
    if(FTMP_HNDLR_AddCommandClassToBuffer(command))
    {
        /* Initiate FTMP Packet transmission */
        if(TMSendFTMPPacket(true,FTMP_WRITE_OP, NULL))
        {
            return TM_SUCCESS;
        }
        else
        {
            return TM_FAILURE;
        }
    }
    else
    {
        return TM_FAILURE;
    }
}

void TM_RecvCallback( void *ins_ptr, FTMPApdu *request_data_ptr, FTMPApdu *response_data_ptr)
{         
    /* Request received from FUT */
    stTMSysData.is_request_rcvd = true;

    /* Copy the FTMP RX data */
    callbackdata.ftmp_rx_data = (FTMPApdu *) request_data_ptr;
    packet_counter++;
   // _APPO = packet_counter;
}

TM_STATUS TM_IsConnectionEstablished(void)
{
    return stTMSysData.is_connected;
}

/* Clears FTMP Handler buffers 
*/
static void TMClearFTMPHandlerBuffer(void)
{
    /* Check if it is FTMP Multi Class is active */
    FTMP_HNDLR_ClearBuffer();
}
    
static void TMChangeState(TM_STATES State)
{
    stTMSysData.state = State;
}

static TM_STATES TMGetCurrentState(void)
{
    return stTMSysData.state;
}
