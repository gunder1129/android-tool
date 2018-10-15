LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_SRC_FILES := $(call all-java-files-under, src)
LOCAL_PACKAGE_NAME := SimpleService
LOCAL_CERTIFICATE :=platform
LOCAL_STATIC_JAVA_LIBRARIES := simple
include $(BUILD_PACKAGE)
include $(CLEAR_VARS)
LOCAL_MODULE_TAGS := optional 
LOCAL_PREBUILT_STATIC_JAVA_LIBRARIES :=simple:libs/simple.jar 
include $(BUILD_MULTI_PREBUILT)
