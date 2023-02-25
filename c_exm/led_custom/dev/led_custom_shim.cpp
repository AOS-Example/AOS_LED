#include <log/log.h>
#include "/dev/led_custom_shim.h"

int led_increase_light()
{
	ALOGD("---%s() called", __func__);
	return 0;
}

int led_decrese_light()
{
	ALOGD("---%s() called", __func__);
}