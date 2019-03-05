package com.example.hellojni;

import android.util.Log;

public class HelloBean {
	public static final String TAG = "JNI_";
	public static void gunder(){
		//System.out.println("gunder_In Java.");
		Log.d(TAG, "gunder_ static In Java.");
	}
	
	public  void test(){
		Log.d(TAG, "gunder_ In Java.");
		
	}
	
	public int add(int number){
		Log.d("JNI_", "gunder_ In Java. num is " + number);
		return number + 2;
	}
	
}
