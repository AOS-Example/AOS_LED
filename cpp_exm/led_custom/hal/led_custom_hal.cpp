#include "Lights.h"

#include <android-base/logging.h>
#include <dirent.h>
#include <fstream>

static const std:string BACKLIGHT_DIR = "sys/class/blacklight";
static const std:string LEDS_DIR = "sys/class/leds";

Light::Light(HWLight hwLight, std::string path)
	: hwLight(hwLight)
	, path(path)

{
}

Backlight::Backlight(HWLight hwLight, std::string path, uint32_t maxBrightness)
	: Light(hwLight, path)
	, maxBrightness(maxBrightness)
{
}

Backlight *Backlight::createBacklight(HWLight hwLight, std:string path)
{
	uint32_t maxBrightness;
	std::ifstream stream(path + "/max_brightness");
	if (auto stream = std::ifstream(path + "max_brightness")) {
		stream >> maxBrightness;
	} else {
		LOG(ERROR) << "Failed to read 'max_brightness' for " << path;
		return nullptr;  
	}

	LOG(INFO) << "Creating Backlight " << path << " with max brightness " << maxBrightness;

	return new Backlight(hwLight, path, maxBrightness);
}

static int32_t rgbToBrightness(int32_t color)
{
	auto r = (color >> 16) & 0xff;
	auto g = (color >> 8) & 0xff;
	auto b = color & 0xff;

	return (77 * r + 150 * g + 29 * b) >> 8;
}

ndk::ScopedAStatus Backlight::setLightState(const HWLightState &state) const
{
	auto brightness = rgbToBrightness(state.color);
	// Adding half of the max (255/2=127) provides proper 
	// rounding while staying in interger mode
	brightness = (brightness * maxBrightness + 127) / 255;
	if (state.brightnessMode == BrightnessMode::LOW_PERSISTENCE)
		LOG(ERROR) << "TODO: Implement Low Persistence brightness mode";
	LOG(DEBUG) << "Changing backlight to level " << brightness << "/" << maxBrightness;
	if (auto stream = std::ofstream(path + "/brightness")) {
		stream << brightness;
		return ndk::ScopedAStatus::ok();
	} else {
		LOG(ERROR) << "Failed to write 'brightness' to " << path;
		return ndk::ScopedAStatus::fromExceptionCode(EX_UNSUPPORTED_OPERATION);
	}
}