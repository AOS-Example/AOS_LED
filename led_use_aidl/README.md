# Android Lights AIDL HAL
Provides controls for backlight and led uses AIDL

# Usage

Add the following to your Android device tree:
`$(call inherit-product, the-path-to-lights.mk)`

And set the appropriate user/group in your `ueventd.rc` file for all relevant light, ie:
`
/sys/class/backlight/backlight max_brightness 	0644 root system
/sys/class/backlight/backlight brightness 		0644 system system
`