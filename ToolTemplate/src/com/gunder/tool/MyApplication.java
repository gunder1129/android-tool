package com.gunder.tool;

import java.util.LinkedList;
import java.util.List;

import android.app.Activity;
import android.app.Application;

import com.gunder.tool.utils.Logger;

public class MyApplication extends Application{
	private List<Activity> mList = new LinkedList<Activity>();	
	/*private MyApplication(){
		
	};*/
	private static MyApplication instance;
	@Override
	public void onCreate() {
		super.onCreate();
		Logger.d();
		instance = this;
	}
	//single intance
	public synchronized static MyApplication getInstance(){
		Logger.d();
		if (null == instance){
			instance = new MyApplication();
		}
		return instance;
	}
	//add activity
	public void addActivity(Activity activity){
		mList.add(activity);
	}
	
	//exit app
	public void exit(){
		try {
			for (Activity activity : mList){
				if (activity != null){
					activity.finish();
				}
			}
		} catch (Exception e) {
			e.printStackTrace();
		}finally{
			System.exit(0);
		}
	}
	
	@Override
	public void onLowMemory() {
		super.onLowMemory();
		System.gc();
	}
}
