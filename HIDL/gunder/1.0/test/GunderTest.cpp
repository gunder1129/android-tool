#include <android/hardware/gunder/1.0/IGunder.h>
#include <hidl/Status.h>
#include <hidl/LegacySupport.h> 
#include <utils/misc.h>
#include <hidl/HidlSupport.h>
#include <stdio.h>

using ::android::hardware::hidl_string;
using ::android::sp;
using android::hardware::gunder::V1_0::IGunder;

int main(){
	android::sp<IGunder> service = IGunder::getService();
	if (service == nullptr){
		printf("Failed to get service\n");
		return -1;
	}

	service->helloWorld("Gunder", [&](hidl_string result){
		printf("%s\n", result.c_str());	
   	});
	return 0;
}


