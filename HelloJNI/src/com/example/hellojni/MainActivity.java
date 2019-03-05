package com.example.hellojni;

import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.widget.TextView;


public class MainActivity extends Activity {
	TextView textView;
	
	

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        textView = (TextView) findViewById(R.id.text);
        /*
        String text = HelloJNI.sayHello("JNI"); //3.调用本地函数  
        String text2 = HelloJNI.print("China"); 
        int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        int text3 = HelloJNI.sumArray(arr);
        textView.setText(text + "  " + text2 + "  " + text3);
        //数组测试
        StringBuffer sb = new StringBuffer();
        int[][] i2arr = HelloJNI.initInt2DArray(3);
        for (int i = 0; i < 3; i++){
        	for (int j = 0; j < 3; j++){
        		sb.append(" " + i2arr[i][j]);
        	}
        }
        textView.setText("  " + sb.toString());
        
        //方法回调，修改java中成员变量
        HelloJNI helloJNI = new HelloJNI();
        helloJNI.changeNum();
        textView.setText("" + helloJNI.number);
        
        helloJNI.setHeight("168");
        helloJNI.accessField();
        textView.setText(helloJNI.getHeight());
       
        HelloJNI.si = 100;
        helloJNI.staticAccessField();
        textView.setText("" + HelloJNI.si);
        */
        
       // HelloJNI.sayHello("hello");
        
        
        
    }
    
    public void jniTest(View v){
//    	HelloJNI.nativeStaticMethod();
//    	HelloJNI.sayHello("hello");
    	HelloJNI helloJNI = new HelloJNI();
    	helloJNI.nativeMethod();
    }
}
