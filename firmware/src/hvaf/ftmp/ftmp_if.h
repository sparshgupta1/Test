/*************************************************************************
FUT Tester Message Protocol (FTMP) Interface Header Definitions

  Company:
    Microchip Technology Inc.
	
  File Name:
    ftmp_if.h
	
  Summary:
    This file aggregates all of the FTMP interface headers.
	
  Description:
    FTMP Interface Header
    This file aggregates all of the FTMP interface headers so that
    module (tester/fut) code only needs to include this one single header to obtain
    prototypes and definitions for all the FTMP interfaces.
	  
  Remarks:
                              
  *************************************************************************/
  
#ifndef _FTMP_IF_H
#define _FTMP_IF_H

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

#include "config/ftmp_cnf.h"

// *****************************************************************************
// *****************************************************************************
// Section: Defines
// *****************************************************************************
// *****************************************************************************

/* FTMP Protocol Start of Packet */
#define FTMP_SOP                    0xF0

/* FTMP TX & RX buffer size */
#define FTMP_BUFFER_SIZE            64

/* Enum defining the return codes for FTMP operations */
typedef enum
{
	/* The request was accepted and will be executed */
	FTMP_RETURN_CODE_OK = 0,
	/* The specified channel is not initialized channel*/
	FTMP_RETURN_CODE_CHANNEL_NOT_INITIALIZED,  
	/* The payload data in the request is larger; cannot be handled */    
	FTMP_RETURN_CODE_PAYLOAD_TOO_LARGE,
	/* There in no more room for data. Try again the at later time */
	FTMP_RETURN_CODE_NO_ROOM_FOR_DATA,
	/* The Class ID, Tester address or the APDU specified in the request was not valid */
	FTMP_RETURN_CODE_DATA_UNIT_NOT_VALID,
        /* FTMP Handler has sent response too late - busy signal sent*/
        FTMP_RETURN_CODE_RESP_TOO_LATE,
        /* FTMP Communication channel failure - No more data transfer possible */
        FTMP_RETURN_CODE_COMM_CHANNEL_FAILURE
  
} FTMP_RETURN_CODE;

typedef enum
{
    FTMP_NO_ERROR = 0,
    FTMP_ERROR
}FTMP_ERROR_CODE;

typedef enum
{
	/* No Operation */
	FTMP_NO_OP = 0x0,
	/* FTMP Read Operation */
	FTMP_READ_OP,
	/* FTMP Write Operation */	
	FTMP_WRITE_OP
}FTMP_IO_OPERATION;

typedef enum
{
	/* ***Later*** This enum should be moved out from this file */
	/* Single Byte Class */
	CLASS_A = 0,
	/* 2bytes Class */
	CLASS_B,
	/* 4bytes Class */
	CLASS_C,
	/* String Class */
	CLASS_D,
	/* Multi byte Class (64bytes) */
	CLASS_E,
	/* Multi byte Class /(256bytes) */
	CLASS_F,
	/* Test Case Class */
	CLASS_G,
	/* Peripheral Class */
	CLASS_H,
	/* Command/Control Class */
	CLASS_I,
	/* Test Configuration Class */
	CLASS_J,
	/* Test result Class */
	CLASS_K,
	/* Test Case Selection Class */
	CLASS_L,

        CLASS_END
	
}FTMP_CLASS_NAMES;

typedef struct
{
    uint8_t* buffer;
    uint16_t buf_size;
}FTMPBuffer;

typedef union
{
        struct {
            /* Data Classes - Holds 6 bits */
            FTMP_CLASS_NAMES cl     :6;
            /* This bit should be set if the sub index is present */
            uint8_t is_sub_index    :1;
            /* This bit shall be set if the next class is present */
            uint8_t is_next_class   :1;
            /* Start Index corresponds to class */
            uint16_t index_start    :8;
            /* End Index corresponds to class */
            uint16_t index_end      :8;
            /* Start Sub Index (if is_sub_index is set)*/
            uint8_t sub_index_start :4;
            /* End Sub Index (if is_sub_index is set)*/
            uint8_t sub_index_end   :4;
        };

        struct
        {
           uint32_t all        :32;
        };
}FTMP_DATA_ITEMS;

/* Structure defining a FTMP Header Unit */
typedef struct
{
	/* SOP will be pre-configured */
    uint8_t tester_address;
	/* Class or RAW data bit set */
	bool is_class_data;
	/* FTMP read/write operation intent */
	FTMP_IO_OPERATION io_operation;
	/* Number of bytes */
	uint16_t num_bytes;

} FTMP_PACKET_HEADER;

/* Structure defining a FTMP Data Unit */
typedef struct _FTMP_DATA_UNIT
{
    /* Pointer to next data unit for current request or NULL if no more data */
    struct _FTMP_DATA_UNIT *next_data_unit_ptr;

    FTMP_DATA_ITEMS uDI;

}FTMP_DATA_UNIT;

/* Structure defining a FTMP */
typedef struct
{
    /* FTMP Packet header */
    FTMP_PACKET_HEADER header;
    
    /* FTMP Data Unit */
    void* data_unit;
}FTMPApdu;

typedef void ( *FTMP_DRV_CALLBACK ) ( void *ins_ptr,
                                      FTMPApdu *request_data_ptr,
                                      FTMPApdu *response_data_ptr);

/* FTMP System Initialize & Task routines */
/* FTMP task should be called in a timer interrupt (100ms) */
extern void FTMP_SysInit(void);
extern void FTMP_SysTask(void);

/* This function called once from the handler to register the callback service
 * and pointer to rx data
 * apdu_rx_ptr - FTMP receive message pointer
 * rx_callback - callback when any message is received
 */

void FTMP_HandlerRegister(FTMPApdu* apdu_rx_ptr, FTMP_DRV_CALLBACK callback);

/* Transmits the requested FTMP PDU. A call-back function can be specified. 

* ins_ptr - pointer to application specific data. This can be NULL.
* t_addr - Tester address.
* request_data_ptr - Pointer to the FTMP PDU to transmit.
* callback - Function that should be called when a response is ready for the tester

* returns the status of the request.
*/
extern FTMP_RETURN_CODE FTMPSendPacket( void *ins_ptr,
                                        FTMPApdu* request_data_ptr,
                                        FTMPApdu* response_data_ptr,
                                        FTMP_DRV_CALLBACK callback);

/* Reset the FTMP protocol data units loaded by the applications 
    All data is set to default values and all pointers are set to NULL*/
extern void FTMP_ResetAPDU( FTMPApdu* apdu_ptr );

/* Get FTMP error codes */
FTMP_ERROR_CODE FTMP_GetErrorCode(void);

/* Start FTMP retry counter */
void FTMP_StartRetryCounter(void);

#endif // _FTMP_IF_H
/*******************************************************************************
 End of File
*/
