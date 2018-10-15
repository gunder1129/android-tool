package com.china.service;

import com.china.jar.VoiceChangedListener;

public class SimpleControl {
	private static VoiceChangedListener changedListener;
	public SimpleControl(VoiceChangedListener voiceChangedListener){
		changedListener = voiceChangedListener;
	}
	
	public static VoiceChangedListener getVoiceCallBack(){
		return changedListener;
	}
}
