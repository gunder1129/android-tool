package com.example.handlerdemo;

import android.app.Activity;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.view.View;
import android.widget.TextView;


public class MainActivity extends Activity {
	private TextView textView;
	private FirstHandler firstHandler;
	private SecondHandler secondHandler;
	private String result;
	
	private Handler handler = new Handler(){
		public void handleMessage(android.os.Message msg) {
			Logger.d("Handler ThreadId = " + Thread.currentThread().getId());
			switch (msg.what) {
			case FirstHandler.ADD_FLAG:
				Logger.d("FirstHandler.ADD_FLAG");
				textView.setText((String) msg.obj); //更新加法运算后的结果
				break;
			case SecondHandler.UI_REFLESH:
				Logger.d("SecondHandler.UI_REFLESH"); 
				textView.setText((String) msg.obj); //更新减法运算后的结果
				break;
			default:
				break;
			}
		};
	};

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        Logger.d("main ThreadId = " + Thread.currentThread().getId());
        setContentView(R.layout.activity_main);
        textView = (TextView) findViewById(R.id.tx_show);
        firstHandler = new FirstHandler();
        secondHandler = new SecondHandler();
    }

    /*
     * handler跟Thread结合使用的测试方法
     */
    public void addCheck(View view){
    	Logger.d();
    	firstHandler.setHandler(handler); //设置Handler对象实例
    	firstHandler.getSum(3000, 4600);  //调用FirstHandler类的getSum方法
    }
    
    /*
     * handler跟HandlerThread结合使用的测试方法
     */
    public void decreaseClick(View view){
    	Logger.d();
    	secondHandler.getSerialThread().post(new Runnable() {
			
			@Override
			public void run() {
				Logger.d("SecondHandler ThreadId = " + Thread.currentThread().getId());
				int sum = decrease(300, 180);
				try {
					Thread.sleep(8 * 1000); //模拟减法运算是一个非常复杂的运算，所以要开线程
				} catch (InterruptedException e) {
					e.printStackTrace();
				}
				result = "result2 = " + sum;
				Message message = new Message();
				message.what = SecondHandler.UI_REFLESH;
				message.obj = result;
				handler.sendMessage(message); //通过主线程更新UI
			}
		});
    }
    
    //减法运算
    private int decrease(int a, int b){
    	return a - b;
    }
    
}
