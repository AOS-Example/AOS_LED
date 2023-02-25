#ifndef LED_CUSTOM_SHIM_H_
#define LED_CUSTOM_SHIM_H_

#include "led_custom_hal.h"

static inline int led_hal_open(const struct hw_module_t *module,
							led_device_t **device);
static inline int led_hal_close(led_device_t* device);

#endif