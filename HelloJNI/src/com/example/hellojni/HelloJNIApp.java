package com.example.hellojni;

import android.app.Application;
import android.util.Log;

public class HelloJNIApp extends Application{
	
	static{
    	System.loadLibrary("HelloJNI"); 
    }
	
	@Override
	public void onCreate() {
		super.onCreate();
		Log.d("JNI_", "Application---");
		
	}
}
