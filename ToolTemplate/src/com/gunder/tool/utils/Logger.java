package com.gunder.tool.utils;

import java.util.Locale;

import android.util.Log;

/**
 * 通过StackTraceElement类获取打印信息
 * Created by Administrator on 2018-3-29.
 * 
 */

public class Logger {
    public static final boolean DEBUG = true;
    public static final String DEFAULT_TAG = "gunder_";

    public Logger(){}
    
    public static void d(){
        if (DEBUG){
            Log.d(DEFAULT_TAG,getPrefix());
        }
    }

    public static void d(String msg){
        if (DEBUG){
            Log.d(DEFAULT_TAG,  getPrefix() + msg);
        }
    }

    public static void d(String msg, Throwable tr){
        if (DEBUG){
            Log.d(DEFAULT_TAG, getPrefix() + msg, tr);
        }
    }

    private static String getPrefix(){
        StackTraceElement stackTraceElement = Thread.currentThread().getStackTrace()[4];
        String className = stackTraceElement.getClassName();
        int classNameStartIndex = className.lastIndexOf(".") + 1;
        className = className.substring(classNameStartIndex);
        String methodName = stackTraceElement.getMethodName();
        int methodLine = stackTraceElement.getLineNumber();
        String format = "%s_%s(L:%d)";
        return String.format(Locale.CANADA, format, className, methodName, methodLine);
    }


}
