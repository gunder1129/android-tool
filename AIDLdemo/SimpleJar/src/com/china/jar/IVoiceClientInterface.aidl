package com.china.jar;
import com.china.jar.IVoiceCallBackInterface;
import com.china.jar.StudentInfo;
interface IVoiceClientInterface{
	void face();
	
	void registerCallBack(IVoiceCallBackInterface callback);
	
	void unRegisterCallBack(IVoiceCallBackInterface callback);
	
	void registerUser(in StudentInfo studentInfo);
}