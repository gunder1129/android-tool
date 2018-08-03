package com.gunder.tool.fragment;

import android.os.Bundle;
import android.os.SystemClock;
import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentActivity;
import android.support.v4.app.FragmentManager;
import android.support.v4.app.FragmentTransaction;
import android.view.View;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.ListView;

import com.gunder.tool.MyApplication;
import com.gunder.tool.R;
import com.gunder.tool.adapter.MenuItemsAdapter;
import com.gunder.tool.adapter.MenuItemsAdapter.CallBack;
import com.gunder.tool.utils.Logger;

public class ListFragmentActivity extends FragmentActivity implements CallBack{
	private ListView mListView = null;
	private MenuItemsAdapter mAdapter = null;
	private static final String DELETE_FILE = "删除文件";
	@Override
	protected void onCreate(Bundle arg0) {
		super.onCreate(arg0);
		/*this.requestWindowFeature(Window.FEATURE_NO_TITLE);
        this.getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN, WindowManager.LayoutParams.FLAG_FULLSCREEN);*/
//		this.getActionBar().setDisplayShowHomeEnabled(false);
		
		MyApplication.getInstance().addActivity(this);
		setContentView(R.layout.main_list_activity);
		mListView = (ListView) findViewById(R.id.menu);
		mAdapter = new MenuItemsAdapter(this, this);
		mListView.setAdapter(mAdapter);
		mListView.setOnItemClickListener(new OnItemClickListener() {
			private long mLastTimestamp = 0L;
			@Override
			public void onItemClick(AdapterView<?> parent, View view, int position,
					long id) {
				if (isValidTime()){
					mAdapter.setSelectedIndex(position);
				}
			}
			
			private boolean isValidTime(){
				long c = SystemClock.elapsedRealtime();
				if (c - mLastTimestamp < 500){
					return false;
				}
				mLastTimestamp = c;
				return true;
			}
		});
		mAdapter.setSelectedIndex(-1);
	}
	@Override
	public void onItemClick(String item) {
		
		FragmentManager mFragmentManager = getSupportFragmentManager();
		//开启事务
		FragmentTransaction transaction = mFragmentManager.beginTransaction();
		Logger.d("item = " + item);
		Fragment fragment = getContentView(item);
		if (null == fragment){
			fragment = new TestFragment();
		}
		transaction.replace(R.id.content, fragment);
		transaction.commit();
		
	}
	
	public void onExit(View view){
		MyApplication.getInstance().exit();
	}
	
	@Override
	protected void onDestroy() {
		super.onDestroy();
	}
	
	private Fragment getContentView(String title){
		Logger.d("title = " + title);
		if (DELETE_FILE.equals(title)){
			Logger.d();
			return new DeleteFileFragment();
		}
		return null;
	}
}
