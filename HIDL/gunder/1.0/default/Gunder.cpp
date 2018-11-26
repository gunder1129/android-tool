#include "Gunder.h"

namespace android {
namespace hardware {
namespace gunder {
namespace V1_0 {
namespace implementation {

// Methods from IGunder follow.
Return<void> Gunder::helloWorld(const hidl_string& name, helloWorld_cb _hidl_cb) {
    char buf[100];
    ::memset(buf, 0x00, 100);
    ::snprintf(buf, 100, "Hello World, %s", name.c_str());
    hidl_string result(buf);
	_hidl_cb(result);
    return Void();
}


// Methods from ::android::hidl::base::V1_0::IBase follow.

IGunder* HIDL_FETCH_IGunder(const char* /* name */) {
    return new Gunder();
}

}  // namespace implementation
}  // namespace V1_0
}  // namespace gunder
}  // namespace hardware
}  // namespace android
