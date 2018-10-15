package com.example.helloworld.util;

import android.util.Log;

import java.util.Locale;

public class Logger {
    public static final boolean DEBUG = true;
    public static final String DEFAULT_TAG = "AIOS_";

    public Logger(){}

//    public static void d(String tag, String msg){
//        if (!ENABLE_LOG){
//            return;
//        }
//
//        Log.d(tag +"_" + getClassName(), callMethodAndLine(-1) + ": " +msg);
//    }
//    public static void d(String msg){
//        if (!ENABLE_LOG){
//            return;
//        }
//
//        Log.d(DEFAULT_TAG +"_" + getClassName(), callMethodAndLine(-1) + ": " + msg);
//    }
//    public static void d(){
//        if (!ENABLE_LOG){
//            return;
//        }
//
//        Log.d(DEFAULT_TAG +"_" + getClassName(), callMethodAndLine(-1));
//    }
//
//    private  static String getClassName(){
//        String result;
//        StackTraceElement thisMethodStack = (new Exception()).getStackTrace()[2];
//        result = thisMethodStack.getClassName();
//        int lastIndex = result.lastIndexOf(".");
//        result = result.substring(lastIndex + 1, result.length());
//        return result;
//    }
//
//
//    private static String callMethodAndLine(){
//        String result = "at ";
//        StackTraceElement thisMethodStack = (new Exception()).getStackTrace()[2];
//        result += thisMethodStack.getClassName() + ".";
//        result += thisMethodStack.getMethodName();
//        result += "(" + thisMethodStack.getFileName();
//        result += ":" + thisMethodStack.getLineNumber() + ")";
//
//        return result;
//    }
//    private static String callMethodAndLine(int i){
//        String result = "at ";
//        StackTraceElement thisMethodStack = (new Exception()).getStackTrace()[2];
////        result += thisMethodStack.getClassName() + ".";
//        result += thisMethodStack.getMethodName();
//        result += "(" + thisMethodStack.getFileName();
//        result += ":" + thisMethodStack.getLineNumber() + ")";
//
//        return result;
//    }

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
