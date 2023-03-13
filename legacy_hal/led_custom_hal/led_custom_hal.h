#ifndef LED_CUSTOM_HAL_
#define LED_CUSTOM_HAL_

#include <hardware/hardware.h>

#define LED_CUSTOM_MODULE_ID "led_hal"

typedef struct led_module {
	struct hw_module_t common; 
} led_module_t;

typdef struct led_device_t {
	struct hw_device_t common;
	int (*control)(int enable);
} led_device_t;

static inline int led_hal_open(const struct hw_module_t *module,
							led_device_t **device)
{
	return module->methods->open(module, NULL, TO_HW_DEVICE_T_OPEN(device));
}

static inline int led_hal_close(led_device_t* device) {
	return device->common.close(&device->common);
}

#endif