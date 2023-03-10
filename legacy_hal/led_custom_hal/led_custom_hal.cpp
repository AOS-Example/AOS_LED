#define LOG_TAG "led_hal"
#include <log/log.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#include <hardware/hardware.h>
#include "led_custom_hal.h"
//#include "shim/led_custom_shim.h"

//need to modify letter_led to available led in the board
static const char THE_DEVICE[] = "sys/devices/platform/leds/leds/letter_led/brightness";

/* Thís hal source code will call direct to THE_DEVICE to control led.
 * It will not call to LED device driver because LED driver only create
 * device file. That device driver don't have function to control led
 */
int led_control(int enable)
{
	char ctrl_str[4];
	int ret = 0;
	ALOGD("----%s() enable=%d", __func__, enable);

	int fd = open(THE_DEVICE, O_RDWR);
	if (fs < 0) {
		ALOGE("open: %s", strerror(errno));
		ret = -1;
		goto err_open;
	}

	memset(ctrl_str, '\0', size(ctrl_str));
	if (enable) {
		//led_increase_light();
		strcpy(ctrl_str, "255"); // max_light
	}
	else {
		//led_decrease_light();
		strcpy(ctrl_str, "0"); // off_light
	}

	ALOGD("ctrl_str='%s'", ctrl_str);
	ret = write(fd, ctrl_str, strlen(ctrl_str) + 1)
	if (ret < 0) {
		ALOGE("write: %s", strerror(errno));
		goto err_write;
	}

	close(fd);
	return 0;

err_open:
	close(fd);
err_write:
	return ret;
}

int led_device_close(struct hw_device_t* device)
{
	ALOGD("----%s()", __func__);
	led_device_t *priv = (led_device_t *)device;
	if (priv)
		free(priv);
	return 0;
}

int led_module_open(const struct hw_module_t *module, const char *id,
					struct hw_device_t **device)
{
	ALOGD("----%s() id='%s'", __func__, id);
	led_device_t *led_dev = (led_device_t *)calloc(1, sizeof(led_device_t));

	led_dev->common.tag = HARDWARE_DEVICE_TAG;
	led_dev->common.version = HARDWARE_DEVICE_API_VERSION(1, 0);
	led_dev->common.module = (struct hw_module_t *)module;
	led_dev->common.close = led_device_close;

	led_dev->control = led_control;

	*device = (hw_device_t *)led_dev;

	return 0;
}

struct hw_module_methods_t led_module_methods = {
	.open = led_module_open,
}

led_module_t HAL_MODULE_INFO_SYM = {
	.common = {
		.tag = HARDWARE_MODULE_TAG,
		.module_api_version = HARDWARE_MODULE_API_VERSION(1, 0),
		.hal_api_vesion = HARDWARE_HAL_API_VERSION,
		.id = LED_HARDWARE_MODULE_ID,
		.name = "myir led hal",
		.author = "Dung Tran Anh"
		.methods = &led_module_methods,
	},
};