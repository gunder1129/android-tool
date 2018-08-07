#include "DeleteFile.h"
#include <binder/IServiceManager.h>
#include <binder/IPCThreadState.h>
#include <cutils/log.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define DELETE_FILE 0x01
#define SERVICE_NAME "chinatsp.autoaction"

int dealDeleteFiles(const char* path){
	char* cmd = (char*) malloc(16 + strlen(path));
	memset(cmd, 0, sizeof(cmd));
	sprintf(cmd, "rm -rf %s", path);
	int result = system(cmd);
	free(cmd);
	return result;
}

namespace android{
DeleteFile::DeleteFile(){
}
DeleteFile::~DeleteFile(){

}
int DeleteFile::instantiate(){
	int r = defaultServiceManager()->addService(String16(SERVICE_NAME), new DeleteFile());
	return r;
}

status_t DeleteFile::onTransact(uint32_t code, const Parcel& data, Parcel* reply,
		uint32_t flags) {
	switch (code) {
	case DELETE_FILE:{
//		int keep = data.readInt32();
		String16 path = data.readString16();
		LOGD("[%s(L:%d)] path = %s\n", __FUNCTION__, __LINE__, String8(path).string());
		int result = dealDeleteFiles(String8(path).string());
		reply->writeInt32(result);
		system("sync");
		return 0;
	}
	break;
	default: {
			return BBinder::onTransact(code, data, reply, flags);
		}
			break;
	}
}

}//namespace
