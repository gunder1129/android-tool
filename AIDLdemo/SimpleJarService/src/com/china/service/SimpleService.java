package com.china.service;

import com.china.jar.IVoiceCallBackInterface;
import com.china.jar.IVoiceClientInterface;
import com.china.jar.StudentInfo;
import com.china.jar.VoiceChangedListener;
import com.china.jar.VoiceManager;

import android.app.Service;
import android.content.Intent;
import android.os.IBinder;
import android.os.RemoteCallbackList;
import android.os.RemoteException;
import android.os.ServiceManager;

public class SimpleService extends Service{
	private static VoiceClientInterfaceImpl mBinder;
	@Override
	public IBinder onBind(Intent intent) {
		Logger.d();
		return mBinder;//跟客户端绑定
	}
	
	@Override
	public void onCreate() {
		super.onCreate();
		Logger.d();
		if (null == mBinder){
			initService();
		}
	}
	
	@Override
	public int onStartCommand(Intent intent, int flags, int startId) {
		Logger.d();
		if (null == mBinder){
			initService();
		}
		return START_STICKY;
	}
	//实现AIDL的接口
	private class VoiceClientInterfaceImpl extends IVoiceClientInterface.Stub{
		protected RemoteCallbackList<IVoiceCallBackInterface> mRemoteCallbackList = 
				new RemoteCallbackList<IVoiceCallBackInterface>();
		private SimpleControl control;
		
		public VoiceClientInterfaceImpl(){
			control = new SimpleControl(voiceChangedListener);
		}
		
		@Override
		public void face() throws RemoteException {
			Logger.d("face----excute!");//客户端调用face方法时这里会执行，会打印face----excute!
		}
		
		//注册回调
		@Override
		public void registerCallBack(IVoiceCallBackInterface arg0)
				throws RemoteException {
			Logger.d();
			mRemoteCallbackList.register(arg0);
			
		}

		//注销回调
		@Override
		public void unRegisterCallBack(IVoiceCallBackInterface arg0)
				throws RemoteException {
			Logger.d();
			mRemoteCallbackList.unregister(arg0);
		}
		
		//调用回调方法
		private VoiceChangedListener voiceChangedListener = new VoiceChangedListener() {
		
			@Override
			public void openAppByVoice(String arg0) {
				Logger.d("arg0 = " + arg0);
				int len = mRemoteCallbackList.beginBroadcast();
				for (int i = 0; i <len; i++) {
					try {
						mRemoteCallbackList.getBroadcastItem(i).openAppByVoice(arg0);
					} catch (RemoteException e) {
						e.printStackTrace();
					}
				}
				mRemoteCallbackList.finishBroadcast();
			}
		};

		@Override
		public void registerUser(StudentInfo studentInfo) throws RemoteException {
			Logger.d("name = " + studentInfo.getName() + " ,age = " + studentInfo.getAge());
			
		}
	}
	//初始化服务，主要是向系统注册服务
	private void initService(){
		Logger.d();
		if (null == mBinder){
			synchronized (SimpleService.class) {
				if (null == mBinder){
					try {
						mBinder = new VoiceClientInterfaceImpl();
						ServiceManager.addService(VoiceManager.NAME, mBinder);
					} catch (Exception e) {
						e.printStackTrace();
					}
				}
			}
		}
	}
}
