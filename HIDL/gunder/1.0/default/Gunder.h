#ifndef ANDROID_HARDWARE_GUNDER_V1_0_GUNDER_H
#define ANDROID_HARDWARE_GUNDER_V1_0_GUNDER_H

#include <android/hardware/gunder/1.0/IGunder.h>
#include <hidl/MQDescriptor.h>
#include <hidl/Status.h>

namespace android {
namespace hardware {
namespace gunder {
namespace V1_0 {
namespace implementation {

using ::android::hardware::hidl_array;
using ::android::hardware::hidl_memory;
using ::android::hardware::hidl_string;
using ::android::hardware::hidl_vec;
using ::android::hardware::Return;
using ::android::hardware::Void;
using ::android::sp;

struct Gunder : public IGunder {
    // Methods from IGunder follow.
    Return<void> helloWorld(const hidl_string& name, helloWorld_cb _hidl_cb) override;

    // Methods from ::android::hidl::base::V1_0::IBase follow.

};

// FIXME: most likely delete, this is only for passthrough implementations
 extern "C" IGunder* HIDL_FETCH_IGunder(const char* name);

}  // namespace implementation
}  // namespace V1_0
}  // namespace gunder
}  // namespace hardware
}  // namespace android

#endif  // ANDROID_HARDWARE_GUNDER_V1_0_GUNDER_H
