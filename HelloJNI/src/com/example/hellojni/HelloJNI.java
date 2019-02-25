package com.example.hellojni;

public class HelloJNI {
	public static native String sayHello(String name); 
	public static native String print(String name); 
	
	static{
    	System.loadLibrary("HelloJNI"); 
    }
}
