package com.example.handlerdemo;

import android.os.Handler;
import android.os.HandlerThread;
import android.os.Looper;

public class SecondHandler {
	
	public Handler uiHandler = new Handler(Looper.getMainLooper()); //main主线程，由于更新UI更新
	private HandlerThread mHandlerThread;
	private Handler handler;
	public static final int UI_REFLESH = 0X02;
	
	//设置handler对象关联
	public void setUIhandler(Handler handler){
		uiHandler = handler;
	}
	
	/**
	 *获取获得Looper对象的Handler实例
	 */
	public synchronized Handler getSerialThread(){
		if (null == mHandlerThread){
			HandlerThread thread = new HandlerThread("work_thread");//工作线程，用于耗时的操作，不能用于更新UI
			thread.start();
			handler = new Handler(thread.getLooper()){
			};
		}
		return handler;
	}
}
