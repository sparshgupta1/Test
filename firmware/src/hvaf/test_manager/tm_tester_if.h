/*************************************************************************
Test Manager Interface Header Definitions

  Company:
    Microchip Technology Inc.
	
  File Name:
    test_manager_if.h
	
  Summary:
    This file aggregates all of the Test Manger interface headers.
	
  Description:
    Test Manger Interface Header
    This file aggregates all of the Test Manger interface headers so that
    module (tester/fut) code only needs to include this one single header to obtain
    prototypes and definitions for all the Test Manger interfaces.
	  
  Remarks:
                              
  *************************************************************************/
  
#ifndef _TEST_MANAGER_IF_H
#define _TEST_MANAGER_IF_H

// *****************************************************************************
// *****************************************************************************
// Section: Included FTMP Module Headers Files
// *****************************************************************************
// *****************************************************************************

#include <xc.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include <sys/attribs.h>
#include "ftmp_if.h"
#include "ftmp_common.h"
#include "handler/ftmp_handler.h"
#include "sys_console.h"
// *****************************************************************************
// *****************************************************************************
// Section: Defines
// *****************************************************************************
// *****************************************************************************

void TM_Tester_Init(void);
void TM_Tester_Task(void);
void TM_RecvCallback( void *ins_ptr,FTMPApdu *request_data_ptr,\
                                      FTMPApdu *response_data_ptr);
void TM_SDMCallback(void);

#endif // _TEST_MANAGER_IF_H
/*******************************************************************************
 End of File
*/
