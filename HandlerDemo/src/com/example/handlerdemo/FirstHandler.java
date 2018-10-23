package com.example.handlerdemo;

import android.os.Handler;
import android.os.Message;

public class FirstHandler {

	private Handler mHandler;
	public static final int ADD_FLAG = 1;
	public void setHandler(Handler handler){
		mHandler = handler;
	}
	
	public synchronized void getSum(final int a, final int b){
		Logger.d("a = " + a + " ,b = " + b);
		class AddRunThread implements Runnable{

			@Override
			public void run() {
				Logger.d("FirstHandler ThreadId = " + Thread.currentThread().getId());
				int sum = add(a, b); 
				try {
					Thread.sleep(6 * 1000); //模拟加法运算是一个非常复杂的运算，所以要开线程
				} catch (InterruptedException e) {
					e.printStackTrace();
				}
				String result = "result = " + sum;
				Message message = mHandler.obtainMessage();
				message.what = ADD_FLAG;
				message.obj = result;
				mHandler.sendMessage(message); //在新的线程中进行发送Message消息
			}
		}
		Thread addRun = new Thread(new AddRunThread());
		addRun.setPriority(Thread.MAX_PRIORITY); //设置线程优先级
		addRun.start();//线程启动
	}
	/**
	 * 实现加法运算
	 */
	private int add(int a, int b){
		return a + b;
	}
}
