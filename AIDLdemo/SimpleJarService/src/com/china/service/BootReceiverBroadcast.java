package com.china.service;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;

public class BootReceiverBroadcast extends BroadcastReceiver{
    @Override
    public void onReceive(Context context, Intent intent) {
        Logger.d();
        Intent service = new Intent(context, SimpleService.class);//开机启动会拉起服务SimpleService
        context.startService(service);
        if(intent.getAction().equals("android.intent.gunder.SimpleJar")){
        	//android.intent.gunder.SimpleJar属于自定义action
        	Logger.d(intent.getAction());
        	SimpleControl.getVoiceCallBack().openAppByVoice("nihao");//这里模拟调用penAppByVoice方法
        }
    }
}
