package com.china.jar;

import java.util.ArrayList;
import java.util.List;

import android.os.Handler;
import android.os.HandlerThread;
import android.os.IBinder.DeathRecipient;
import android.os.Looper;
import android.os.Message;
import android.os.RemoteException;
import android.os.ServiceManager;
import android.util.Log;

public class VoiceManager {
	private static final String TAG = "VoiceManager";
	private static VoiceManager mVoiceManager;
	private static IVoiceClientInterface mService = null;
	public static final String NAME = "simple_jar";
	public static final boolean DEBUG_DATA = true;
	
	private final HandlerThread mWorkThread;
	private final Handler mWorkHander;
	private static final int MSG_INIT_SERVICE = 0x01;
	private CallBack mCallBack;
	private List<VoiceChangedListener> listeners = new ArrayList<VoiceChangedListener>();
	
	//单例模式
	public static synchronized VoiceManager getInstance(){
		if (null == mVoiceManager){
			synchronized (VoiceManager.class) {
				if (null == mVoiceManager){
					mVoiceManager = new VoiceManager();
				}
			}
		}
		return mVoiceManager;
	}
	
	//该构造函数主要调用getService()方法，以便客户端在调用VoiceManager.getInstance()方法时可以跟服务端建立链接
	private VoiceManager(){ 
		Log.d(TAG, "VoiceManager...begin");
		mWorkThread = new HandlerThread("simple_manager");
		mWorkThread.start();
		mWorkHander = new Handler(mWorkThread.getLooper()){
			@Override
			public void handleMessage(Message msg) {
				switch (msg.what) {
				case MSG_INIT_SERVICE:
					removeMessages(MSG_INIT_SERVICE);
					getService();
					break;

				default:
					break;
				}
			}
		};
		mWorkHander.sendEmptyMessage(MSG_INIT_SERVICE);
	}
	//获取服务端注册的NAME服务并跟服务端建立连接
	private synchronized IVoiceClientInterface getService(){
		Log.d(TAG, "getService...begin");
		if (null == mService){
			Log.e(TAG, "IVocieService init");
			mService = IVoiceClientInterface.Stub.asInterface(ServiceManager
                    .getService(NAME));
			if (mService != null){
				try {
					mCallBack = new CallBack(listeners);
					mService.registerCallBack(mCallBack);
					mService.asBinder().linkToDeath(new AidlLinkToDeath(), 0);
				} catch (Exception e) {
					e.printStackTrace();
					mService = null;
				}
			}
		}
		
		if (null == mService){
			Log.e(TAG, "jar service is null");
			mWorkHander.removeMessages(MSG_INIT_SERVICE);
			mWorkHander.sendEmptyMessageDelayed(MSG_INIT_SERVICE, 100);
		}
		return mService;
	}
	
	/**
	 * 监控aidl连接异常，即binder异常
	 */
	private class AidlLinkToDeath implements DeathRecipient{

		@Override
		public void binderDied() {
			Log.e(TAG, "binderDied, aidl connect exception.");
			mService = null;
			mWorkHander.sendEmptyMessage(MSG_INIT_SERVICE);
		}
	}
	
	public void face(){
		Log.d(TAG, "face");
		mService = getService();
		if (null == mService){
			Log.e(TAG, "face mService is null!");
			return ;
		}
		try{
			mService.face();
		}catch(RemoteException e){
			e.printStackTrace();
		}
	}
	
	//注册用户
	public void registerUser(StudentInfo studentInfo){
		Log.d(TAG, "registerUser");
		mService = getService();
		if (null == mService){
			Log.e(TAG, "registerUser mService is null!");
			return ;
		}
		try{
			mService.registerUser(studentInfo);
		}catch(RemoteException e){
			e.printStackTrace();
		}
	}
	
	//注册监听
	public void addVoiceChangedListener(final VoiceChangedListener aListener){
		if (DEBUG_DATA){
			Log.v(TAG, "addVoiceChangedListener..." + aListener + " ,before list size = " + listeners.size());
		}
		
		if (aListener != null && !listeners.contains(aListener)){
			listeners.add(aListener);
			if (DEBUG_DATA){
				Log.v(TAG, "addVoiceChangedListener... after list size = " + listeners.size());
			}
		}
	}
	
	//注销监听
	public void removeVoiceChangedListener(final VoiceChangedListener aListener){
		if (DEBUG_DATA){
			Log.v(TAG, "removeVoiceChangedListener..." + aListener + " ,before list size = " + listeners.size());
		}
		
		if (aListener != null && !listeners.contains(aListener)){
			listeners.add(aListener);
			if (DEBUG_DATA){
				Log.v(TAG, "removeVoiceChangedListener... after list size = " + listeners.size());
			}
		}
	}
	
	//回调接口实现
	private static final class CallBack extends IVoiceCallBackInterface.Stub{
		
		private Handler mHandler = null;
		private List<VoiceChangedListener> mListeners;
		

		public CallBack(List<VoiceChangedListener> listeners) {
			mHandler = new Handler(Looper.getMainLooper());
			this.mListeners = listeners;
		}


		@Override
		public void openAppByVoice(final String packagename) throws RemoteException {
			Log.d(TAG, "packagename = " + packagename);
			this.mHandler.post(new Runnable() {
				
				@Override
				public void run() {
					for (VoiceChangedListener v : mListeners){
						v.openAppByVoice(packagename);
					}
					
				}
			});
		}
	}
	
}
