package com.china.service;

import android.content.Context;
import android.view.Gravity;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.view.WindowManager;
import android.widget.LinearLayout;
import android.widget.TextView;
import android.widget.Toast;

import com.china.jar.VoiceChangedListener;
import com.chinatsp.service.R;

public class SimpleControl {
	private static VoiceChangedListener changedListener;
	private static Context mContext;
	public SimpleControl(VoiceChangedListener voiceChangedListener, Context context){
		changedListener = voiceChangedListener;
		mContext = context;
	}
	
	//获取初始化后的回调实例
	public static VoiceChangedListener getVoiceCallBack(){
		return changedListener;
	}
	
	static long lastshowToastTime = 0;
	public static void showToast(String s) {
		if(Math.abs(System.currentTimeMillis() - lastshowToastTime)<3000){
			return;
		}
		Logger.d("show Toast");
		View view = LayoutInflater.from(mContext.getApplicationContext())
				.inflate(R.layout.common_toast_custom,
						null);
		WindowManager wm = (WindowManager) mContext.getApplicationContext()
				.getSystemService(Context.WINDOW_SERVICE);
		int width = wm.getDefaultDisplay().getWidth();
		LinearLayout.LayoutParams layoutParams = new LinearLayout.LayoutParams(
				width / 2, ViewGroup.LayoutParams.WRAP_CONTENT);

		TextView txt = (TextView) view
				.findViewById(R.id.textViewToastMsg);
		txt.setText(s);
		txt.setLayoutParams(layoutParams);
		Toast toast = new Toast(mContext.getApplicationContext());
		toast.setView(view);
		toast.setGravity(Gravity.CENTER, 0, 0);
		toast.setDuration(3000);
		toast.show();
		lastshowToastTime = System.currentTimeMillis();
	}
}
