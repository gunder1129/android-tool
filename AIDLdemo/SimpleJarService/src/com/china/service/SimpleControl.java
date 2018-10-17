package com.china.service;

import com.china.jar.VoiceChangedListener;

public class SimpleControl {
	private static VoiceChangedListener changedListener;
	public SimpleControl(VoiceChangedListener voiceChangedListener){
		changedListener = voiceChangedListener;
	}
	
	//获取初始化后的回调实例
	public static VoiceChangedListener getVoiceCallBack(){
		return changedListener;
	}
}
