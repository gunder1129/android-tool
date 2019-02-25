LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE    := libHelloJNI
LOCAL_SHARED_LIBRARIES := liblog libutils
LOCAL_LDLIBS := -L$(SYSROOT)/usr/lib -llog
LOCAL_SRC_FILES := HelloJNI.cpp
TARGET_CFLAGS += -g
include $(BUILD_SHARED_LIBRARY)
