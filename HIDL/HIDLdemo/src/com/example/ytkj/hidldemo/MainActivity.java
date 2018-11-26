package com.example.ytkj.hidldemo;

import android.hardware.gunder.V1_0.IGunder;
import android.os.Bundle;
import android.os.RemoteException;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.View;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {
    IGunder iGunderService;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_hidl);
        try {
            iGunderService = IGunder.getService(); //获取服务
        } catch (RemoteException e) {
            e.printStackTrace();
        }
    }

    public void hidlTest(View view){
        if (iGunderService != null){
            Log.d("gunder", "service is connect.");
            String s = null;
            try {
                s = iGunderService.helloWorld("Gunder Lin");//调用HAL层接口
            } catch (RemoteException e) {
                e.printStackTrace();
            }
            Log.d("gunder", s);
            Toast.makeText(this, s, Toast.LENGTH_LONG).show();
        }
    }
}
