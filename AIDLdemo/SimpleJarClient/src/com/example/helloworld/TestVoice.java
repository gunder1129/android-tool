package com.example.helloworld;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;

import com.china.jar.VoiceChangedListener;
import com.china.jar.VoiceManager;
import com.example.helloworld.util.Logger;


public class TestVoice extends Activity{
	VoiceManager voiceManager;
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.version);
		voiceManager = VoiceManager.getInstance();
		if (voiceManager != null){
			voiceManager.addVoiceChangedListener(new VoiceChangedListener() {//客户端的监听及实现
				
				@Override
				public void openAppByVoice(String arg0) {
					Logger.d("packageName = " + arg0);
					
				}
			});
		}
	}
	
	public void startVoice(View view){
		Logger.d();
		Intent intent = new Intent();
		intent.setClass(TestVoice.this, UsbTest.class);
		intent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
		startActivity(intent);
    }
    
    public void stopVoice(View view){
    	Logger.d();
    	VoiceManager.getInstance().face();
    }
    
    public void finishVoice(View view){
    	Logger.d();
    	finish();
    }

	
	
}
