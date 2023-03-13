#!/bin/bash
# Stop execution instantly as a query exits while
# having a non-zero status
set -e

if [ ! -d $ANDROID_BUILD_TOP/AOS_LED/interfaces ] ; then
	echo "Where is AOS_LED/interfaces ?";
	exit 1;
fi

if [ ! -d $ANDROID_BUILD_TOP/system/libhidl/transport ] ; then
	echo "Where is system/libhidl/transport ?";
	exit 1;
fi

PACKAGE=AOS_LED.hardware.led@1.0
LOC=$ANDROID_BUILD_TOP/AOS_LED/interfaces/led/1.0/default/
options="-rAOS_LED.hardware:AOS_LED/interfaces \
		-randroid.hidl:system/libhidl/transport"

#make hidl-gen -j6
hidl-gen -o $LOC -Lc++-impl $options $PACKAGE
hidl-gen -o $LOC -Landroidbp-impl $options $PACKAGE

echo done!