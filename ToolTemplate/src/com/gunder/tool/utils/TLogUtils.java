package com.gunder.tool.utils;

import java.io.File;

import android.os.IBinder;
import android.os.Parcel;
import android.os.ServiceManager;
import android.os.SystemProperties;

public class TLogUtils {
	private final static int DELETE_FILES = 0x1;
	public static boolean deleteLog(String src){
		Logger.d("src = " + src);
		if (null == src){
			return false;
		}
		String path = src;
		while ((!path.isEmpty()) && path.charAt(path.length() - 1) == '/')
		{
			path = path.substring(0, path.length() - 1);
		}
		path = path.trim();
		Logger.d("path = " + path);
		if (path.isEmpty()){
			Logger.d("path is empty");
			return true;
		}
		boolean result = false;
		File file = new File(path);
		if (file.exists()){
			result = deleteLogFiles(file);
		}else {
			result = true;
		}
		if (!result){
			Logger.d("delete log failed: " + src);
		}
		return result;
	}

	private static boolean deleteLogFiles(File file) {
		Logger.d();
		if (file != null && file.exists()){
			Logger.d();
			if (file.isDirectory()){
				Logger.d();
				return deleteLogFilesUseRoot(file.getAbsolutePath());
			}
		}else {
			Logger.d();
			return file.delete();
		}
		return true;
	}

	
	private static boolean deleteLogFilesUseRoot(String absolutePath) {
		Logger.d("absolutePath = " + absolutePath);
		Parcel data = Parcel.obtain();
		data.writeString(absolutePath);
		return dealUseRoot(DELETE_FILES, data);
	}

	private static boolean dealUseRoot(int cmd, Parcel data) {
		IBinder binder = null;
		final int MAX_WAIT = 9; //最多获取service 10次
		int index = 0;
		SystemProperties.set("ctl.start", "tsp_auto_service");
		do {
			Logger.d("get service : chinatsp.autoaction");
			binder = ServiceManager.getService("chinatsp.autoaction");
			if (null == binder){
				try {
					Thread.sleep(100);
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		}while ((null == binder) && ((index++) < MAX_WAIT));
		if (null == binder){
			Logger.d("get service of autoaction failed");
			data.recycle();
			SystemProperties.set("ctl.stop", "tsp_auto_service");
			return false;
		}
		Parcel reply = Parcel.obtain();
		int result = -1;
		try {
			Logger.d("cmd = " + cmd);
			binder.transact(cmd, data, reply, 0);
			result = reply.readInt();
		} catch (Exception e) {
			Logger.d("send cmd to autoaction service : error");
		}
		data.recycle();
		reply.recycle();
		SystemProperties.set("ctl.stop", "tsp_auto_service");
		return result == 0;
	}
}
