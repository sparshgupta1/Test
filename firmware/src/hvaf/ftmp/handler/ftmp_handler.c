/*******************************************************************************
  FTMP Handler Implementation

  Company:
    Microchip Technology Inc.

  File Name:
    ftmp_handler.c

  Summary:
    FTMP handler Implementation.

  Description:

	
*******************************************************************************/


// *****************************************************************************
// *****************************************************************************
// Section: Include Files
// *****************************************************************************
// *****************************************************************************
#include "../ftmp_if.h"
#include "../bus/ftmp_drv_if.h"
#include "ftmp_handler.h"

// *****************************************************************************
// *****************************************************************************
// Section: File Scope Variables
// *****************************************************************************
// *****************************************************************************
    
#define DATA_UNIT_LEN       0x08 //default data unit length.
//FTMP_DATA_UNIT *DataUnitHeader; //head pointer to the packet.
uint8_t NumDataUints; //Number of Data units in a packet
//bool SUCCESS_FLAG;
uint8_t SDM_Stimulus_Interface[20]; //Interface b/w SDM & FTMP Handler for stimulus req
//bool FLAG_SDM;
uint8_t *SDM_Test_Config_Data ; // Pointer to test configuration data.

//#if defined (__FUT__)
FTMPApdu TxPacket,RxPacket;
FTMP_DATA_UNIT TxDataUnits[FTMP_MAX_DATA_UNIT];
FTMP_DATA_UNIT RxDataUnits[FTMP_MAX_DATA_UNIT];
//#endif

/*handler callback function pointer*/
FTMP_DRV_CALLBACK HandleCallbackPtr;
// *****************************************************************************
// *****************************************************************************
// Section: File Scope Functions
#if defined (__TESTER__)
bool CONNECT_STATUS;
void TesterFormRawDataPacket(void);
void TesterProcessRxData(FTMPApdu *);
// *****************************************************************************
// *****************************************************************************
void TesterFormRawDataPacket()
{
    if(NumDataUints >= FTMP_MAX_DATA_UNIT)
    {
        return;
    }
    //Need to assign SDM data to Data unit
    //TxDataUnits[NumDataUints] = SDM_Test_Config_Data;
    NumDataUints++;
}
/*******************************************************************************
  Function:
    void ProcessRxData(FTMPApdu *RxPacket)

  Summary:
    Processes the packet data which is received.

  Description:
    Processes the packet data which is received.

  Precondition:
    Packet should be containing a valid packet.

  Parameters:
    FTMPApdu structure pointer - packet pointer

  Returns:
    none.

  Remarks:
    Currently this function is used in Tester, to process the response.
*/

void TesterProcessRxData(FTMPApdu *RxPacket)
{
    FTMP_DATA_UNIT *DataUnit = (FTMP_DATA_UNIT*)RxPacket->data_unit;
    FTMP_DATA_UNIT *tmpData;
    int index = 0;
    bool status = false;

    do{
        tmpData = DataUnit;
        //Need to process all commands /like Ack/nak/busy/test config.
        if(tmpData->uDI.cl == CLASS_I)
        {
            if((tmpData->uDI.index_start == FTMP_HNDLR_CONNECT_REQUEST)&& \
                (tmpData->uDI.index_end == FTMP_HNDLR_CONNECT_REQUEST))
            {
                   CONNECT_STATUS = true;
            }
            else if((tmpData->uDI.index_start == FTMP_HNDLR_GET_TEST_CONFIG)&& \
                (tmpData->uDI.index_end == FTMP_HNDLR_GET_TEST_CONFIG))
            {
                TesterFormRawDataPacket();
                FTMP_HNDLR_SendBuffer(true,FTMP_WRITE_OP,0x00,NULL);

            }
            else
            {
                 //skip rest of the commands.
            }
        }
        //for each DataUnits, parse the Data
        //Data class A,B,C,D,E,F & class K -log
        else if ((tmpData->uDI.cl <= CLASS_F) ||(tmpData->uDI.cl == CLASS_F))
        {//No processing is done here. just update SDM interface.
            SDM_Stimulus_Interface[index] = (uint8_t )tmpData->uDI.all;
        }
        else //any other type
        {

        }
        DataUnit = DataUnit->next_data_unit_ptr;
    }while( (tmpData->next_data_unit_ptr != NULL) && (tmpData->uDI.is_next_class != false) );
    //check with Balajee to finalise on the interface.
    /* if(FLAG_SDM!=true)
    {
        FLAG_SDM = true;
    }*/
}


/*******************************************************************************
  Function:
   void FTMP_HNDLR_RecvCallback( void *ins_ptr,FTMPApdu *RxPacket,FTMPApdu *TxPacket)

  Summary:
    Call back fucntion when a packet receives.

  Description:
    Callback function implementation for Tester. this gets called from FTMP.

  Precondition:
    none.

  Parameters:
        * ins_ptr - Instance pointer.
        * FTMPApdu structure pointer - RX packet pointer.
        * FTMPApdu structure pointer - TX packet pointer.

  Returns:
    none.

  Remarks:
    This function is used in Tester only.
*/
void Tester_FTMP_HNDLR_RecvCallback( void *ins_ptr,FTMPApdu *RxPacket,FTMPApdu *TxPacket)
{
    bool status = false;
    status = FTMP_HNDLR_AddCommandClassToBuffer(FTMP_HNDLR_ACK);
    if (status == true)
    {
        status = FTMP_HNDLR_SendBuffer(true,FTMP_WRITE_OP,0x00,NULL);
    }
    //process the received data
    TesterProcessRxData(RxPacket);
}
#endif //Only for Tester
// *****************************************************************************
// *****************************************************************************
/*******************************************************************************
  Function:
    void FTMP_HNDLR_Initialize(void)

  Summary:
    Init function for FTMP Handler.

  Description:
    Initializes the FTMP handler.

  Precondition:
    none.

  Parameters:
    none.

  Returns:
    none.

  Remarks:

 */


/*******************************************************************************
  Function:
    bool FTMP_HNDLR_AddCommandClassToBuffer(FTMP_COMMAND_CLASS command)

  Summary:
    Add a command class data unit to Tx buffer.

  Description:
    Add a command class data unit to Tx buffer.

  Precondition:
    none.

  Parameters:
    FTMP_COMMAND_CLASS - Command type enum.

  Returns:
    returns TRUE if the operation succeeds. Else false.

  Remarks:

 */
bool FTMP_HNDLR_AddCommandClassToBuffer(FTMP_COMMAND_CLASS command)
{
    if(NumDataUints >= FTMP_MAX_DATA_UNIT)
    {
        return false;
    }
    TxDataUnits[NumDataUints].next_data_unit_ptr = NULL;
    TxDataUnits[NumDataUints].uDI.is_next_class= 0; //no next class
    TxDataUnits[NumDataUints].uDI.is_sub_index = 0; //no sub index
    TxDataUnits[NumDataUints].uDI.sub_index_start = 0;
    TxDataUnits[NumDataUints].uDI.sub_index_end = 0;
    TxDataUnits[NumDataUints].uDI.cl = CLASS_I;
    TxDataUnits[NumDataUints].uDI.index_start = command;
    TxDataUnits[NumDataUints].uDI.index_end = command;
    if(NumDataUints>0)
    {
        TxDataUnits[NumDataUints-1].next_data_unit_ptr = &TxDataUnits[NumDataUints];
        TxDataUnits[NumDataUints-1].uDI.is_next_class = 1;
    }
    NumDataUints++;
    return true;
}
/*******************************************************************************
  Function:
    bool FTMP_HNDLR_AddDataClassToBuffer(FTMP_CLASS_NAMES cl,int index_start, \
                                                       int index_end)

  Summary:
    Add a Data class data unit to Tx buffer.

  Description:
    Add a Data class data unit to Tx buffer.

  Precondition:
    none.

  Parameters:
    FTMP_COMMAND_CLASS - Class type enum.
    int  - Start index.
    int  - End index

  Returns:
    returns TRUE if the operation succeeds. Else false.

  Remarks:

 */

bool FTMP_HNDLR_AddDataClassToBuffer(FTMP_CLASS_NAMES cl,int index_start, \
                                                       int index_end)
{
    if(NumDataUints >= FTMP_MAX_DATA_UNIT)
    {
        return false;
    }
    TxDataUnits[NumDataUints].next_data_unit_ptr = NULL;
    TxDataUnits[NumDataUints].uDI.is_next_class= 0; //no next class
    TxDataUnits[NumDataUints].uDI.is_sub_index = 0; //no sub index
    TxDataUnits[NumDataUints].uDI.sub_index_start = 0;
    TxDataUnits[NumDataUints].uDI.sub_index_end = 0;
    TxDataUnits[NumDataUints].uDI.cl = cl; //Need to decide
    TxDataUnits[NumDataUints].uDI.index_start = index_start;
    TxDataUnits[NumDataUints].uDI.index_end = index_end;
    if(NumDataUints>0)
    {
        TxDataUnits[NumDataUints-1].next_data_unit_ptr = &TxDataUnits[NumDataUints];
        TxDataUnits[NumDataUints-1].uDI.is_next_class = 1;
    }
    NumDataUints++;
    return true;

}
/*******************************************************************************
  Function:
    bool FTMP_HNDLR_AddExtDataClassToBuffer(FTMP_CLASS_NAMES cl, \
                    int index_start,int index_end, int sub_index_start, \
                    int sub_index_end)

  Summary:
    Add an Extended Data class data unit to Tx buffer.

  Description:
    Add an Extended Data class data unit to Tx buffer.

  Precondition:
    none.

  Parameters:
    FTMP_COMMAND_CLASS - Class type enum.
    int  - Start index.
    int  - End index
    int  - Sub index start value.
    int  - Sub index End value

  Returns:
    returns TRUE if the operation succeeds. Else false.

  Remarks:

 */
bool FTMP_HNDLR_AddExtDataClassToBuffer(FTMP_CLASS_NAMES cl, \
                    int index_start,int index_end, int sub_index_start, \
                    int sub_index_end)
{
    if(NumDataUints >= FTMP_MAX_DATA_UNIT)
    {
        return false;
    }
    TxDataUnits[NumDataUints].next_data_unit_ptr = NULL;
    TxDataUnits[NumDataUints].uDI.is_next_class= 0; //no next class
    TxDataUnits[NumDataUints].uDI.is_sub_index = 1; //no sub index
    TxDataUnits[NumDataUints].uDI.sub_index_start = sub_index_start;
    TxDataUnits[NumDataUints].uDI.sub_index_end = sub_index_end;
    TxDataUnits[NumDataUints].uDI.cl = cl; //Need to decide
    TxDataUnits[NumDataUints].uDI.index_start = index_start;
    TxDataUnits[NumDataUints].uDI.index_end = index_end;
    if(NumDataUints>0)
    {
        TxDataUnits[NumDataUints-1].next_data_unit_ptr = &TxDataUnits[NumDataUints];
        TxDataUnits[NumDataUints-1].uDI.is_next_class = 1;
    }
    NumDataUints++;
    return true;

}
/*******************************************************************************
  Function:
    bool FTMP_HNDLR_AddPeripheralClassToBuffer(FTMP_PERIPHERAL_CLASS pl)

  Summary:
    Add a Peripheral class data unit to Tx buffer.

  Description:
    Add a Peripheral Data class data unit to Tx buffer.

  Precondition:
    none.

  Parameters:
    FTMP_PERIPHRAL_CLASS - Peripheral Class type enum.

  Returns:
    returns TRUE if the operation succeeds. Else false.

  Remarks:

 */
bool FTMP_HNDLR_AddPeripheralClassToBuffer(FTMP_PERIPHERAL_CLASS pl)
{
    
    if(NumDataUints >= FTMP_MAX_DATA_UNIT)
    {
        return false;
    }
    TxDataUnits[NumDataUints].next_data_unit_ptr = NULL;
    TxDataUnits[NumDataUints].uDI.is_next_class= 0; //no next class
    TxDataUnits[NumDataUints].uDI.cl = CLASS_H; //Need to decide
    TxDataUnits[NumDataUints].uDI.is_sub_index = 1; //sub index available

    /*To find out the index of peripheral class,its (enum/9)*/
    TxDataUnits[NumDataUints].uDI.index_start = (uint8_t)(pl/9);
    TxDataUnits[NumDataUints].uDI.index_end = (uint8_t)(pl/9);
    /*To find the sub index, (enum % 9)*/
    TxDataUnits[NumDataUints].uDI.sub_index_start = (uint8_t)(pl%9);
    TxDataUnits[NumDataUints].uDI.sub_index_end = (uint8_t)(pl%9);
    if(NumDataUints>0)
    {
        TxDataUnits[NumDataUints-1].next_data_unit_ptr = &TxDataUnits[NumDataUints];
        TxDataUnits[NumDataUints-1].uDI.is_next_class = 1;
    }
    NumDataUints++;
    return true;

}
/*******************************************************************************
  Function:
    bool FTMP_HNDLR_SendBuffer(void)

  Summary:
    Sends out the data from Tx buffer.

  Description:
    Sends out the data from Tx buffer.

  Precondition:
    Data unit has to be present

  Parameters:
    none.

  Returns:
    returns TRUE if the operation succeeds. Else false.

  Remarks:

 */

bool FTMP_HNDLR_SendBuffer(bool IsClassData,FTMP_IO_OPERATION FTMP_OP,uint8_t TesterAdd,FTMP_DRV_CALLBACK Handler_Callback)
{
    bool SUCCESS_FLAG;
   
    if(NumDataUints <= 0)
    {
        SUCCESS_FLAG = false;
    }
    else
    {
#if defined (__FUT__)
        HandleCallbackPtr = Handler_Callback;
        TxPacket.header.is_class_data = IsClassData; //Its class data
        TxPacket.header.io_operation = FTMP_OP; //Command/data READ/writes.
        TxPacket.header.tester_address = TesterAdd;
        TxPacket.header.num_bytes = DATA_UNIT_LEN * NumDataUints;
        TxPacket.data_unit = (FTMP_DATA_UNIT *)&TxDataUnits[0];
        RxPacket.data_unit = (FTMP_DATA_UNIT *)&RxDataUnits[0];
#else
        HandleCallbackPtr = NULL;
        RxPacket.header.is_class_data = IsClassData; //Its class data
        RxPacket.header.io_operation = FTMP_OP; //Command/data writes.
        RxPacket.header.tester_address = TesterAdd;
        RxPacket.header.num_bytes = DATA_UNIT_LEN * NumDataUints;
        RxPacket.data_unit = (FTMP_DATA_UNIT *) &TxDataUnits[0];
#endif
        SUCCESS_FLAG = false;
        if( FTMPSendPacket(NULL,&TxPacket,&RxPacket,\
                    HandleCallbackPtr) == FTMP_RETURN_CODE_OK)
        {
            SUCCESS_FLAG = true;
        }
        else
        {
            SUCCESS_FLAG = false;
        }
        //DataUnitHeader = NULL;
        //NumDataUints = 0; //To hold the data for re-send. Explicitly call ClearBuffer for clearing.
    }
    return(SUCCESS_FLAG);
}

void FTMP_HNDLR_ClearBuffer (void)
{
    int i = 0;
    NumDataUints = 0 ; //Resetting the count for buffer.
    for(i=0;i<FTMP_MAX_DATA_UNIT;i++)
    {
        TxDataUnits[i].next_data_unit_ptr = 0;
        TxDataUnits[i].uDI.all = 0;
    }
}
