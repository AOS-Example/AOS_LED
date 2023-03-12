#pragma once

#include <aidl/android/hardware/light/BnLights.h>

using namespace aidl::android::hardware::light;

struct Light {
	const HwLight hwLight;
	const std::string path;

	Light(HwLight hwLight, std::string path);
	inline virtual ~Light() {};

	virtual ndk::ScopedAStatus setLightState(const HwLightState &state) const = 0;
};

struct Backlight : public Light {
	const uint32_t maxBrightness;

	Backlight(HwLight hwLight, std::string path, uint32_t maxBrightness);
	static Backlight *createBacklight(HwLight hwLight, std::string path);
	inline virtual ~Backlight() {};

	ndk::ScopedAStatus setLightState(const HwLightState &state) const override;
};

struct Led : public Light {
	const uint32_t maxBrightness;

	Led(HwLight hwLight, std::string path, uint32_t maxBrightness);
	static Led *createLed(HwLight hwLight, std::string path);
	inline virtual ~Led() {};

	ndk::ScopedAStatus setLightState(cont HwLightState &state) const override;
};

class Lights : public BnLights {
	ndk::ScopedAStatus setLightState(int id, const HwLightState &state) override;
	ndk::ScopedAStatus getLights(std::vector<HwLight> *type) override;

	std::vector<std::unique_ptr<Light>> lights;

public:
	Lights();
};