package com.example.helloworld.util;

import java.lang.reflect.Method;

import android.os.storage.StorageManager;
import android.os.storage.StorageVolume;
import android.text.TextUtils;

/**
 * Created by ryan on 01/03/2018.
 */

public class USBUtil {
    private static final USBUtil mUtil = new USBUtil();
   

    public static USBUtil getInstance() {
        return mUtil;
    }

    public static StorageVolume[] getVolumeList(StorageManager storageManager){
        try {
            Class clz = StorageManager.class;
            Method getVolumeList = clz.getMethod("getVolumeList", null);
            StorageVolume[] result = (StorageVolume[]) getVolumeList.invoke(storageManager, null);
            return result;
        } catch (Exception e) {
            e.printStackTrace();
        }
        return null;
    }
    
    public static String getVolumeState(StorageManager storageManager, String path){
        String result = "";
        if(null == storageManager || TextUtils.isEmpty(path)){
            return result;
        }
        try {
            Class clz = StorageManager.class;
            Method getVolumeList = clz.getMethod("getVolumeState", String.class);
            result = (String) getVolumeList.invoke(storageManager, path);
        } catch (Exception e) {
            e.printStackTrace();
        }
        return result;
    }
    
}
