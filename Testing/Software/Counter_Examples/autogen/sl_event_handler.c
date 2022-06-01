#include "sl_event_handler.h"

#include "em_chip.h"
#include "sl_device_init_hfxo.h"
#include "pa_conversions_efr32.h"
#include "sl_rail_util_pti.h"
#include "sl_rail_util_rssi.h"
#include "sl_rail_util_init.h"
#include "sl_cycle_counter.h"
#include "gpiointerrupt.h"
#include "sl_iostream_init_eusart_instances.h"
#include "sl_simple_button_instances.h"
#include "sl_simple_led_instances.h"
#include "sl_iostream_init_instances.h"

void sl_platform_init(void)
{
  CHIP_Init();
  sl_device_init_hfxo();
}

void sl_driver_init(void)
{
  sl_cycle_counter_enable();
  GPIOINT_Init();
  sl_simple_button_init_instances();
  sl_simple_led_init_instances();
}

void sl_service_init(void)
{
  sl_iostream_init_instances();
}

void sl_stack_init(void)
{
  sl_rail_util_pa_init();
  sl_rail_util_pti_init();
  sl_rail_util_rssi_init();
  sl_rail_util_init();
}

void sl_internal_app_init(void)
{
}

void sl_platform_process_action(void)
{
}

void sl_service_process_action(void)
{
}

void sl_stack_process_action(void)
{
}

void sl_internal_app_process_action(void)
{
}

void sl_iostream_init_instances(void)
{
  sl_iostream_eusart_init_instances();
}

