package com.example.helloworld;

import android.app.Activity;
import android.content.Context;
import android.os.Bundle;
import android.os.storage.StorageManager;
import android.os.storage.StorageVolume;
import android.view.View;
import android.widget.TextView;

import com.example.helloworld.util.Logger;
import com.example.helloworld.util.USBUtil;


public class UsbTest extends Activity{
	private StorageManager storageManager;
	Context context;
	TextView mTextView;
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.usb);
		context = UsbTest.this;
		storageManager = (StorageManager) context.getSystemService(Context.STORAGE_SERVICE);
		mTextView = (TextView) findViewById(R.id.show_tv);
		
		
	}
	
	public void startVoice(View view){
		Logger.d();
		if (USBExist(context)){
			mTextView.setText("USB is exist!");
		}else {
			mTextView.setText("USB isn't exist!");
		}
    }
    
    
    public void finishVoice(View view){
    	Logger.d();
    	finish();
    }

    //判断/storage/udisk是否为挂载的路径
    private boolean USBExist(Context context){
    	if (null == storageManager){
    		Logger.d("Invalid reference to StorageManager received.");
    		return false;
    	}
    	String usbPath = getUSBPath(context);
    	if (USBUtil.getVolumeState(storageManager, usbPath).equals(android.os.Environment.MEDIA_MOUNTED)){
    		return true;
    	}
    	
    	return false;
    }
    
    //判断USB路径（/storage/udisk）是否存在
    private String getUSBPath(Context context){
    	Logger.d();
    	String usb = null;
    	StorageVolume[] volumes = USBUtil.getVolumeList(storageManager);
    	for (int i = 0; i < volumes.length; i++){
    		if (volumes[i].isRemovable() && volumes[i].getDescription(context).contains("USB")){
    			usb = volumes[i].getPath();
    			Logger.d("usb = " + usb);
    			if (usb.equals("/storage/udisk")){
    				break;
    			}
    			
    		}
    	}
    	return usb;
    }
	
}
