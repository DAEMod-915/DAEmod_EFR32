/***************************************************************************//**
 * @file
 * @brief app_process.c
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
#include "sl_component_catalog.h"
#include "rail.h"
#include "sl_simple_led.h"
#include "sl_simple_led_instances.h"
#include "../segmentlcd/inc/sl_segmentlcd.h"
#include "FreeRTOS.h"
#include "task.h"
#if defined(SL_CATALOG_KERNEL_PRESENT)
#include "app_task_init.h"
#endif
// -----------------------------------------------------------------------------
//                              Macros and Typedefs
// -----------------------------------------------------------------------------
#define PAYLOAD_LENGTH 16

// -----------------------------------------------------------------------------
//                          Static Function Declarations
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
//                                Global Variables
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
//                                Static Variables
// -----------------------------------------------------------------------------
static const uint8_t payload[PAYLOAD_LENGTH] = {PAYLOAD_LENGTH-1, 0x4B, 0x44, 0x39, 0x4C, 0x53, 0x56, 0x5f,
     0x45, 0x43, 0x45, 0x34, 0x39, 0x39, 0x31, 0x33};

static volatile bool send_packet = false;
static uint8_t rx_buffer[256];
// -----------------------------------------------------------------------------
//                          Public Function Definitions
// -----------------------------------------------------------------------------
/******************************************************************************
 * Application state machine, called infinitely
 *****************************************************************************/
void app_process_action(RAIL_Handle_t rail_handle)
{
  (void) rail_handle;


  ///////////////////////////////////////////////////////////////////////////
if(1){
  vTaskDelay(10);
    send_packet = false;
    RAIL_WriteTxFifo(rail_handle, payload, PAYLOAD_LENGTH, false);
    RAIL_Status_t status = RAIL_StartTx(rail_handle, 0, RAIL_TX_OPTIONS_DEFAULT, NULL);
    if ( status != RAIL_STATUS_NO_ERROR ) {
      sl_led_toggle(&sl_led_led0);
    }
  }
if(0){
  RAIL_RxPacketHandle_t packet_handle;
  RAIL_RxPacketInfo_t packet_info;
  packet_handle = RAIL_GetRxPacketInfo(rail_handle, RAIL_RX_PACKET_HANDLE_OLDEST_COMPLETE, &packet_info);
  if ( packet_handle != RAIL_RX_PACKET_HANDLE_INVALID ){
    RAIL_RxPacketDetails_t packet_details;
    RAIL_CopyRxPacket(rx_buffer, &packet_info);
    RAIL_GetRxPacketDetails(rail_handle, packet_handle, &packet_details);
    RAIL_ReleaseRxPacket(rail_handle, packet_handle);
    printf("RX");
    for(int i=0; i < packet_info.packetBytes; i++){
      printf(" 0x%02X", rx_buffer[i]);
    }
    printf("; RSSI=%d dBm\n", packet_details.rssi);
  }
  }
}

/******************************************************************************
 * RAIL callback, called if a RAIL event occurs
 *****************************************************************************/
void sl_rail_util_on_event(RAIL_Handle_t rail_handle, RAIL_Events_t events)
{
  (void) rail_handle;
  (void) events;

  ///////////////////////////////////////////////////////////////////////////
  if ( events & RAIL_EVENTS_TX_COMPLETION ) {
    if ( events & RAIL_EVENT_TX_PACKET_SENT ) {
     // sl_led_toggle(&sl_led_led0);
    } else {
      //sl_led_toggle(&sl_led_led1); //all other events in RAIL_EVENTS_TX_COMPLETION are errors
    }
  }
  if ( events & RAIL_EVENTS_RX_COMPLETION ) {
    if ( events & RAIL_EVENT_RX_PACKET_RECEIVED ) {
      RAIL_HoldRxPacket(rail_handle);
    sl_led_turn_off(&sl_led_led0);
    } else {
      sl_led_turn_on(&sl_led_led0); //all other events in RAIL_EVENTS_RX_COMPLETION are errors
    }
  }
  if ( events & RAIL_EVENT_CAL_NEEDED ) {
    RAIL_Calibrate(rail_handle, NULL, RAIL_CAL_ALL_PENDING);
  }

  ///////////////////////////////////////////////////////////////////////////

#if defined(SL_CATALOG_KERNEL_PRESENT)
  app_task_notify();
#endif
}

// -----------------------------------------------------------------------------
//                          Static Function Definitions
// -----------------------------------------------------------------------------
