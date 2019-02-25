#include "Inc/HelloJNI.h"
#include "nativehelper/JNIHelp.h"
#include <stdio.h>
#include <android/log.h>

#define LOG_TAG "DebugJNI"
#define DEBUG
#define ANDROID_PLATFORM

#ifdef DEBUG
	#ifdef ANDROID_PLATFORM
		#define LOGD(...) ((void)__android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__))
	#else
		#define LOGD(fmt, ...) printf(fmt"\n", ##__VA_ARGS__)
	#endif
#else
	#define LOGD(...);
#endif

JNIEXPORT jstring JNICALL Java_com_example_hellojni_HelloJNI_sayHello
  (JNIEnv *env, jclass cls, jstring j_str)
{
	const char *c_str = NULL;
	char buff[128] = { 0 };
	c_str = env->GetStringUTFChars(j_str, NULL);
	if (c_str == NULL)
	{
		LOGD("out of memory.\n");
		return NULL;
	}
	LOGD("Java Str : %s\n", c_str);
	sprintf(buff, "hello %s", c_str);
	env->ReleaseStringUTFChars(j_str, c_str);
	return env->NewStringUTF(buff);
}

JNIEXPORT jstring JNICALL Java_com_example_hellojni_HelloJNI_print
  (JNIEnv *env, jclass cls, jstring j_str)
{
		const char *c_str = NULL;
		char buff[128] = { 0 }, outBuf[128];
		int len = env->GetStringLength(j_str);
		env->GetStringUTFRegion(j_str, 0, len, buff);
		c_str = buff;
		LOGD("Java Str : %s\n", c_str);
		sprintf(outBuf, "welcome %s", c_str);
		return env->NewStringUTF(outBuf);
}
