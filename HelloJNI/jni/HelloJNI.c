#include "Inc/HelloJNI.h"
#include "nativehelper/JNIHelp.h"
#include <stdio.h>
#include <android/log.h>

#define LOG_TAG "JNI_"
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



//字符串的获取创建
jstring JNICALL Java_com_example_hellojni_HelloJNI_sayHello
  (JNIEnv *env, jclass cls, jstring j_str)
{
	const char *c_str = NULL;
	char buff[128] = { 0 };
	c_str = (*env)->GetStringUTFChars(env, j_str, NULL);
	if (c_str == NULL)
	{
		LOGD("out of memory.\n");
		return NULL;
	}
	LOGD("Java Str : %s\n", c_str);
	sprintf(buff, "hello %s", c_str);
	(*env)->ReleaseStringUTFChars(env, j_str, c_str);



	return (*env)->NewStringUTF(env, buff);
}

//调用java中的方法
JNIEXPORT void JNICALL Java_com_example_hellojni_HelloJNI_nativeMethod
  (JNIEnv *env, jobject obj)
{
	LOGD("In C begin");
	jclass clazz = NULL;
	jobject jobj = NULL;
	jmethodID mid_construct = NULL;
	jmethodID mid_instance = NULL;
	//1.从classpath路径下搜索ClassMethod这个类，并返回该类的Class对象
	clazz =  (*env)->FindClass(env,"com/example/hellojni/HelloBean");
	if (clazz == NULL){
		LOGD("No find com/example/hellojni/HelloBean class");
		return;
	}

	//2.获取类的默认构造方法ID
	mid_construct = (*env)->GetMethodID(env, clazz, "<init>", "()V");
	if (mid_construct == NULL)
	{
		LOGD("No find defualt construct.");
		return ;
	}

	//3.查找实例方法的ID
	mid_instance  = (*env)->GetMethodID(env, clazz, "test","()V");
	if (mid_instance == NULL){
		LOGD("No find mid instance");
		return;
	}

	//4.创建该类的实例
	jobj = (*env)->NewObject(env, clazz, mid_construct);
	if (jobj == NULL)
	{
		LOGD("No find test in the com/example/hellojni/HelloBean");
	}

	//5.调用对象的实例方法
	(*env)->CallVoidMethod(env, jobj, mid_instance);

	//6.删除局部引用
	(*env)->DeleteLocalRef(env, clazz);
	(*env)->DeleteLocalRef(env, jobj);

	LOGD("In C end");
}


//调用java中的静态方法
JNIEXPORT void JNICALL Java_com_example_hellojni_HelloJNI_nativeStaticMethod
  (JNIEnv *env, jclass cls)
{
	LOGD("In C begin static");
		jclass classTmp =  (*env)->FindClass(env,"com/example/hellojni/HelloBean");
		if (classTmp == NULL){
			LOGD("In C++classTmp == NULL");
			return;
		}
		jclass clazzTts = (*env)->NewGlobalRef(env,classTmp);
		if (clazzTts != NULL){
			jmethodID gunder  = (*env)->GetStaticMethodID(env, clazzTts,"gunder","()V");
			if (gunder != NULL)
				(*env)->CallStaticVoidMethod(env,clazzTts,gunder);
			else{
				LOGD("stop--- method id error.");
			}
		}
		LOGD("In C end static ");
}
