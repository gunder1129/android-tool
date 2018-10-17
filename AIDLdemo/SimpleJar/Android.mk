LOCAL_PATH:=$(call my-dir)
include $(CLEAR_VARS)
#LOCAL_SRC_FILES := $(call all-java-files-under, src)
LOCAL_SRC_FILES := $(call all-subdir-java-files) 
LOCAL_SRC_FILES += \
    src/com/china/jar/IVoiceClientInterface.aidl \
	src/com/china/jar/IVoiceCallBackInterface.aidl 

LOCAL_MODULE_TAGS := optional
LOCAL_MODULE := simple
LOCAL_CERTIFICATE := platform
#include $(BUILD_JAVA_LIBRARY)
include $(BUILD_STATIC_JAVA_LIBRARY)
