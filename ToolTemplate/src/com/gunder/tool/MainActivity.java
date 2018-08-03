package com.gunder.tool;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;

import com.gunder.tool.fragment.ListFragmentActivity;


public class MainActivity extends Activity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        MyApplication.getInstance().addActivity(this);
//        setContentView(R.layout.activity_main);
        Intent intent = new Intent(MainActivity.this, ListFragmentActivity.class);
        intent.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
        startActivity(intent);
    }
}
