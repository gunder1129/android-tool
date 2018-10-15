package com.china.jar;
import com.china.jar.IVoiceCallBackInterface;
interface IVoiceClientInterface{
	void face();
	
	void registerCallBack(IVoiceCallBackInterface callback);
	
	void unRegisterCallBack(IVoiceCallBackInterface callback);
}