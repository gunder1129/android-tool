package com.example.hellojni;

import android.app.Activity;
import android.os.Bundle;
import android.widget.TextView;


public class MainActivity extends Activity {
	TextView textView;
	
	

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        textView = (TextView) findViewById(R.id.text);
        String text = HelloJNI.sayHello("JNI"); //3.调用本地函数  
        String text2 = HelloJNI.print("China"); 
        textView.setText(text + "  " + text2);
        
    }
}
