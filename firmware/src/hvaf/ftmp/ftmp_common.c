/*******************************************************************************
  FTMP Master/Slave Appplication Protocol Common Functions Implementation

  Company:
    Microchip Technology Inc.

  File Name:
    ftmp_common.c

  Summary:
    FTMP Master/Slave Appplication Protocol Common Functions Implementation

  Description:

	
*******************************************************************************/


// *****************************************************************************
// *****************************************************************************
// Section: Include Files
// *****************************************************************************
// *****************************************************************************
#include "ftmp_common.h"
#include "ftmp_timer.h"

// *****************************************************************************
// *****************************************************************************
// Section: File Scope Variables
// *****************************************************************************
// *****************************************************************************

uint8_t FTMP_SharedDataBuffer[FTMP_STATIC_BUFFER_SIZE];

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

bool FTMP_Allocate_Memory(uint16_t length, uint8_t** buf_ptr)
{
    static uint16_t buf_pos = 0;

    if(buf_pos <= FTMP_STATIC_BUFFER_SIZE)
    {
        *buf_ptr = &FTMP_SharedDataBuffer[buf_pos];
        buf_pos += length+1;

        return true;
    }
    else
    {
        return false;
    }
}

uint16_t FTMP_CalculateCRC(uint8_t* data, uint16_t size)
{
    uint16_t loop;
    uint16_t crc_temp = 0;
    uint16_t crc =0;

    /* Calculate Modular Sum*/
    for(loop= 0; loop < size; loop++)
    {
       crc_temp += data[loop];
    }

    /* 2's Complement */
    crc = (~crc_temp) + 1;

    return crc;
}

bool FTMP_CheckCRC(uint8_t* data, uint16_t size)
{
    uint16_t r_crc = 0;
    uint16_t calc_crc = 0;
    uint16_t  crc_len = (size - sizeof(uint16_t));

    /* Copy received CRC*/
    memcpy(&r_crc, data+crc_len, sizeof(uint16_t));

    /* Calculate CRC for received packtet */
    calc_crc = 0;
    calc_crc = FTMP_CalculateCRC(data, crc_len);

    /* Check CRC */
    if(r_crc == calc_crc)
    {
        return true;
    }
    else
    {
        return false;
    }
}

uint32_t FTMP_ClearandGetTimerTick(void)
{
    FTMP_TimerClearTick();

    return FTMP_TimerGetTick();
}

uint32_t FTMP_GetTimerTick(void)
{
    return FTMP_TimerGetTick();
}


bool FTMP_CheckTimerExpiry(uint16_t delayms, uint32_t prev_time)
{
    uint32_t current_timer;

    current_timer = FTMP_TimerGetTick();

    if(((current_timer - prev_time)) >= delayms)
    {
        return true;
    }
    else
    {
        return false;
    }
}
