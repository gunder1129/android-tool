#include <sys/types.h>
#include <unistd.h>
#include <grp.h>
#include <binder/IPCThreadState.h>
#include <binder/ProcessState.h>
#include <binder/IServiceManager.h>
#include <private/android_filesystem_config.h>
#include "DeleteFile.h"

using namespace android;
int main(int argc, char** argv)
{
	LOGD("main begin.....");
	LOGD("[%s(L:%d)] \n", __FUNCTION__, __LINE__);
	sp<ProcessState> proc(ProcessState::self());
	sp<IServiceManager> sm = defaultServiceManager(); //取得 ServiceManager
	DeleteFile::instantiate();
	ProcessState::self()->startThreadPool(); //启动缓冲池
	IPCThreadState::self()->joinThreadPool(); //这里是把服务添加到 Binder闭合循环进程中
	LOGD("main end.....");
}
