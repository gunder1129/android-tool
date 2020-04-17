#ifndef MCUCONTROLLER_H_
#define MCUCONTROLLER_H_
#include <utils/threads.h>
using namespace android;

class SendThread :public Thread{
public:
    virtual bool threadLoop() ;
    void  block();
    void unblock();
	Condition  mCondition;
	Mutex  mConditionMutex;

};

#endif