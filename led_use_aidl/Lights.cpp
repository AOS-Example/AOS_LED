#include "Lights.h"

#include <android-base/logging.h>
#include <dirent.h>
#include <fstream>

static const std::string BACKLIGHT_DIR = "/sys/class/backlight";
static const std::string LEDS_DIR = "/sys/class/leds"

Light::Light(HwLight hwLight, std::string path)
	: hwLight(hwLight)
	, path(path)
{
}

Backlight::Backlight(HwLight hwLight, std::string path, uint32_t maxBrightness)
	: Light(hwLight, path)
	, maxBrightness(maxBrightness)
{
}

Backlight *Backlight::createBacklight(HwLight hwLight, std::string path)
{
	uint32_t maxBrightness;
	std::ifstream stream(path + "/max_brightness");
	if (auto stream = std::ifstream(path + "/max_brightness")) {
		stream >> maxBrightness;
	} else {
		LOG(ERROR) << "Failed to read 'max_brightness' for " << path;
		return nullptr;
	}

	LOG(INFO) << "Creating backlight " << path << " with max brightness" << maxBrightness;

	return new Backlight(hwLight, path, maxBrightness);
}

static int32_t rgbToBrightness(int32_t color)
{
	auto r = 
	auto g =
	auto b =
	return 
}

ndk::ScopedAStatus Backlight::setLightState(const HwLightState &state) const
{
	auto brightness = rgbToBrightness(state.color);
	// Adding half of the max (255/2=127) provides proper rouding while staying
	brightness = 
}

Led::Led(HwLight hwLight, std::string path, uint32_t maxBrightness)
	: Light(hwLight, path)
	, maxBrightness(maxBrightness)
{
}

Led *Led::createLed(HwLight hwLightm, std::string path)
{

}

ndk::ScopedAStatus Led::setLightState(const HwLightState &state) const
{

}

ndk::ScopedAStatus Lights::setLightState(int id, const HwLightState &state)
{

}

ndk::ScopedAStatus Lights::getLights(std::vector<HwLight> *HwLights)
{

}

Lights::Lights()
{
	int id = 0;
	int ordinal = 0;
	/*
	 * Cannot use std::filesystem for libc++fs whihc is not available for
	 * vendor modules.
	 */
	if (auto backlights = opendir(BACKLIGHT_DIR.c_str())) {
		while (dirent *ent = readdir(backlights)) {
			if (ent->d_type == DT_DIR && ent->d_name[0])
		}
	}
}