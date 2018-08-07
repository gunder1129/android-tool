LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_SRC_FILES:= DeleteFile.cpp DeleteFileService.cpp
LOCAL_C_INCLUDES := \
	DeleteFile.h \
	$(JNI_H_INCLUDE)
LOCAL_SHARED_LIBRARIES := \
	liblog \
	libutils \
	libandroid_runtime \
	libbinder \
	libcutils 
LOCAL_LDLIBS := -L$(SYSROOT)/usr/lib -llog
LOCAL_MODULE:= tspautoservice
include $(BUILD_EXECUTABLE)