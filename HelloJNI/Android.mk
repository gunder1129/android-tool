
LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE_TAGS := optional
LOCAL_SRC_FILES := $(call all-java-files-under, src)
LOCAL_PACKAGE_NAME := HelloJNI
LOCAL_CERTIFICATE :=platform
LOCAL_JNI_SHARED_LIBRARIES := libHelloJNI
include $(BUILD_PACKAGE)

include $(CLEAR_VARS)
#LOCAL_PREBUILT_LIBS :=libaisound5:libs/armeabi/libaisound5.so
include $(BUILD_MULTI_PREBUILT)

include $(call all-makefiles-under,$(LOCAL_PATH))
