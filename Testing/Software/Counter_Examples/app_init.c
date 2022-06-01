/***************************************************************************//**
 * @file
 * @brief app_init.c
 *******************************************************************************
 * # License
 * <b>Copyright 2018 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * SPDX-License-Identifier: Zlib
 *
 * The licensor of this software is Silicon Laboratories Inc.
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 ******************************************************************************/

// -----------------------------------------------------------------------------
//                                   Includes
// -----------------------------------------------------------------------------
#include "sl_rail_util_init.h"
#include "sl_led.h"
#include "sl_simple_led_instances.h"
#include <em_lcd.h>
#include "../segmentlcd/inc/sl_segmentlcd.h"

// -----------------------------------------------------------------------------
//                              Macros and Typedefs
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
//                          Static Function Declarations
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
//                                Global Variables
// -----------------------------------------------------------------------------
#define BUFFER_LENGTH 256
// -----------------------------------------------------------------------------
//                                Static Variables
// -----------------------------------------------------------------------------
static uint8_t tx_buffer[BUFFER_LENGTH];
// -----------------------------------------------------------------------------
//                          Public Function Definitions
// -----------------------------------------------------------------------------
/******************************************************************************
 * The function is used for some basic initialization related to the app.
 *****************************************************************************/
RAIL_Handle_t app_init(void)
{
  // Get RAIL handle, used later by the application
  RAIL_Handle_t rail_handle = sl_rail_util_get_handle(SL_RAIL_UTIL_HANDLE_INST0);
  //
  RAIL_SetTxFifo(rail_handle, tx_buffer, 0, BUFFER_LENGTH);

  RAIL_ConfigEvents(rail_handle, RAIL_EVENTS_ALL,
                     RAIL_EVENTS_TX_COMPLETION | RAIL_EVENTS_RX_COMPLETION |
                     RAIL_EVENT_CAL_NEEDED);
  RAIL_Status_t status = RAIL_StartRx(rail_handle, 0, NULL);
  if ( status != RAIL_STATUS_NO_ERROR ){
    sl_led_toggle(&sl_led_led0);
  }
  //////////////////////////////////////////////////////////////////////////////
  // Put your application init code here!                                    //
  // This is called once during start-up.                                    //
  SegmentLCD_Init(true);
  SegmentLCD_Number(55);
  /////////////////////////////////////////////////////////////////////////////
  return rail_handle;
}

// -----------------------------------------------------------------------------
//                          Static Function Definitions
// -----------------------------------------------------------------------------
