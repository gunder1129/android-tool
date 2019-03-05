package com.example.hellojni;


public class HelloJNI {
	public int number = 0;
	private String height;
	public static int si;
	
	public static native String sayHello(String name); 
	public static native String print(String name); 
	public static native int sumArray(int[] arr);
	public static native int[][] initInt2DArray(int size);
	public native void changeNum();
	public native void accessField();
	public native void staticAccessField();
	public native void nativeMethod();
	public static native void nativeStaticMethod();
		
	public String getHeight() {
		return height;
	}
	public void setHeight(String height) {
		this.height = height;
	}	
	
}
