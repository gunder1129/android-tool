#define LOG_TAG "android.hardware.gunder@1.0-service"
#include <android/hardware/gunder/1.0/IGunder.h>
#include <hidl/LegacySupport.h>
using android::hardware::gunder::V1_0::IGunder;
using android::hardware::defaultPassthroughServiceImplementation;

int main(){
	return defaultPassthroughServiceImplementation<IGunder>();

}
