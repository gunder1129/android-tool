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

//字符串的获取创建
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

//获取数组对象
JNIEXPORT jint JNICALL Java_com_example_hellojni_HelloJNI_sumArray
  (JNIEnv *env, jclass cls, jintArray arr)
{
	jint buf[10];
	jint i, sum = 0;
	env->GetIntArrayRegion(arr, 0, 10, buf);
	for (i = 0; i < 9; i++)
	{
		sum += buf[i];
	}
	return sum;

#if 0
	jint *carr;
	jint i, sum = 0;
	carr = env->GetIntArrayElements(arr, NULL);
	if (carr == NULL)
	{
		return 0;
	}
	for (i = 0; i < 10; i++)
	{
		sum += carr[i];
	}
	env->ReleaseIntArrayElements(arr, carr, 0);
	return sum;
#endif

}

//二维数组的操作
JNIEXPORT jobjectArray JNICALL Java_com_example_hellojni_HelloJNI_initInt2DArray
  (JNIEnv *env, jclass cls, jint size)
{
	jobjectArray result;
	int i;
	jclass intArrCls = env->FindClass("[I");
	if (intArrCls == NULL)
	{
		return NULL;
	}
	result = env->NewObjectArray(size, intArrCls, NULL);
	if (result == NULL)
	{
		return NULL;
	}
	for (i = 0; i < size; i++)
	{
		jint tmp[256];
		int j;
		jintArray iarr = env->NewIntArray(size);
		if (iarr == NULL)
		{
			return NULL;
		}
		for (j = 0; j < size; j++)
		{
			tmp[j] = i + j;
		}
		env->SetIntArrayRegion(iarr, 0, size, tmp);
		env->SetObjectArrayElement(result, i, iarr);
		env->DeleteLocalRef(iarr);
	}
	return result;
}

//修改java类中的成员变量（int类型），即java在C++中的回调
JNIEXPORT void JNICALL Java_com_example_hellojni_HelloJNI_changeNum
  (JNIEnv *env, jobject obj)
{

	jclass cls = env->GetObjectClass(obj);
	jfieldID id_number = env->GetFieldID(cls, "number", "I");
	if (id_number == NULL)
	{
		return;
	}
	jint number = env->GetIntField(obj, id_number);
	LOGD("c.height = %d", number);

	env->SetIntField(obj, id_number, 100L);
}

//修改java类中的成员变量（string类型），即java在C++中的回调
JNIEXPORT void JNICALL Java_com_example_hellojni_HelloJNI_accessField
  (JNIEnv *env, jobject obj)
{
	jfieldID fid;
	jstring jstr;
	const char *str;
	/* Get a referece to obj's class */
	jclass cls = env->GetObjectClass(obj);
	/* Look for the instance field height in cls */
	fid = env->GetFieldID(cls, "height", "Ljava/lang/String;");
	if (fid == NULL)
	{
		return;
	}
	/* Read the instance field height */
	jstr = (jstring)(env->GetObjectField(obj, fid));
	str = env->GetStringUTFChars(jstr, NULL);
	if (str == NULL)
	{
		return;
	}
	LOGD("height = %s", str);
	env->ReleaseStringUTFChars(jstr, str);
	/* Create a new string and overwrite the instance field */
	jstr = env->NewStringUTF("12346");
	if (jstr == NULL)
	{
		return;
	}
	env->SetObjectField(obj, fid, jstr);
}

//访问静态字段
JNIEXPORT void JNICALL Java_com_example_hellojni_HelloJNI_staticAccessField
  (JNIEnv *env, jobject obj)
{
	jfieldID fid; //store the field ID;
	jint si;

	jclass cls = env->GetObjectClass(obj);
	fid = env->GetStaticFieldID(cls, "si", "I");
	if (fid == NULL)
	{
		return;
	}
	si = env->GetStaticIntField(cls, fid);
	LOGD("si = %d", si);
	env->SetStaticIntField(cls, fid, 200);
}

//调用java中的方法
JNIEXPORT void JNICALL Java_com_example_hellojni_HelloJNI_nativeMethod
  (JNIEnv *env, jobject obj)
{
	jint num = 20;
	LOGD("In C++ begin");
	jclass clazz = NULL;
		jobject jobj = NULL;
		jmethodID mid_construct = NULL;
		jmethodID mid_instance = NULL;
		jmethodID mid_instance2 = NULL;
		//1.从classpath路径下搜索ClassMethod这个类，并返回该类的Class对象
		clazz =  env->FindClass("com/example/hellojni/HelloBean");
		if (clazz == NULL){
			LOGD("No find com/example/hellojni/HelloBean class");
			return;
		}

		//2.获取类的默认构造方法ID
		mid_construct = env->GetMethodID(clazz, "<init>", "()V");
		if (mid_construct == NULL)
		{
			LOGD("No find defualt construct.");
			return ;
		}

		//3.查找实例方法的ID
		mid_instance = env->GetMethodID(clazz, "test","()V");
		if (mid_instance == NULL){
			LOGD("No find test method");
			return;
		}

		mid_instance2 = env->GetMethodID(clazz, "add","(I)I");
		if (mid_instance == NULL){
			LOGD("No find add method");
			return;
		}

		//4.创建该类的实例
		jobj = env->NewObject(clazz, mid_construct);
		if (jobj == NULL)
		{
			LOGD("No find test in the com/example/hellojni/HelloBean");
		}

		//5.调用对象的实例方法
		env->CallVoidMethod(jobj, mid_instance); //不带参数的方法
		env->CallIntMethod(jobj, mid_instance2, num); //传递参数的方法

		//6.删除局部引用
		env->DeleteLocalRef(clazz);
		env->DeleteLocalRef(jobj);
		LOGD("In C++ end");
}

//调用java中的静态方法
JNIEXPORT void JNICALL Java_com_example_hellojni_HelloJNI_nativeStaticMethod
  (JNIEnv *env, jclass cls)
{
	LOGD("In C++ begin static");
		jclass classTmp =  env->FindClass("com/example/hellojni/HelloBean");
		if (classTmp == NULL){
			LOGD("In C++classTmp == NULL");
			return;
		}
		//jclass clazzTts = env->NewGlobalRef(classTmp);
	//	if (clazzTts != NULL){
			jmethodID gunder  = env->GetStaticMethodID(classTmp,"gunder","()V");
			if (gunder != NULL)
				env->CallStaticVoidMethod(classTmp,gunder);
			else{
				LOGD("stop--- method id error.");
			}
		//}
		LOGD("In C++ end static");
}





