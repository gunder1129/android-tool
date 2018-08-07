package com.gunder.tool.fragment;

import java.io.File;
import java.io.FileFilter;

import com.gunder.tool.R;
import com.gunder.tool.utils.Logger;

import android.app.Activity;
import android.content.Context;
import android.os.AsyncTask;
import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.text.TextUtils;
import android.view.LayoutInflater;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

public class DeleteFileFragment extends Fragment implements OnClickListener{

	private static final String DELETE_PART = "/sdcard/";
	private static final String DELETE_FILE = "iflytek";
	
	private TextView mTextView;
	private Button btnDeleteFile;
	private Context mContext;
	private EditText deletePart, deleteFile;
	
	
	@Override
	public View onCreateView(LayoutInflater inflater,
			 ViewGroup container,  Bundle savedInstanceState) {
		Logger.d();
		return inflater.inflate(R.layout.delete_file_fragment, container, false);
	}
	
	@Override
	public void onViewCreated(View view,  Bundle savedInstanceState) {
		super.onViewCreated(view, savedInstanceState);
		Logger.d();
		mContext = getActivity();
		mTextView = (TextView) view.findViewById(R.id.tips);
		btnDeleteFile = (Button) view.findViewById(R.id.delete_file);
		deletePart = (EditText) view.findViewById(R.id.part);
		deleteFile = (EditText) view.findViewById(R.id.file);
		btnDeleteFile.setOnClickListener(this);
		
	}
	
	@Override
	public void onAttach(Activity activity) {
		super.onAttach(activity);
	}
	
	@Override
	public void onDetach() {
		// TODO Auto-generated method stub
		super.onDetach();
	}
	/**
	 * 删除某个目录
	 * @param path 要删除的目录路径
	 * @return
	 */
	private boolean deleteDirs(String path){
		Logger.d("path = " + path);
		File file = new File(path);
		if (!file.exists()){
			return true;
		}
		if (file.isDirectory()){
			File[] childs = file.listFiles();
			if (null == childs){
				return false;
			}
			boolean result = true;
			for (File child : childs){
				result = result && deleteDirs(child.getAbsolutePath());
			}
			Logger.d("file1-------------------" + file.toString());
			try{
				boolean ret = file.delete();
				return result && ret;
			}catch(Exception e){
				e.printStackTrace();
				return false;
			}
			
		}else {
			Logger.d("file2-------------------" + file.toString());
			try {
				boolean ret = file.delete();
				return ret;
			} catch (Exception e) {
				e.printStackTrace();
				return false;
			}
			
		}
	}
	
	/**
	 * 通过异步的方式来执行删除操作
	 * @author ytkj
	 *
	 */
	private class DeleteFileTask extends AsyncTask<String, String, String>{
		
		@Override
		protected void onPreExecute() {
			super.onPreExecute();
			Logger.d();
			mTextView.setVisibility(View.VISIBLE);
//			mTextView.setText("正在删除" + DELETE_PART + DELETE_FILE + "....");
			mTextView.setText(mContext.getResources().getString(R.string.delete_running, DELETE_PART + DELETE_FILE, "...."));
		}
		
		@Override
		protected String doInBackground(String... params) {
			Logger.d();
			String delete_part = params[0];
			final String delete_file = params[1];
			File part = new File(delete_part);
			Logger.d("delete_part = " + delete_part + " ,delete_file = " + delete_file + " ,part = " + part);
			if (!part.exists() || (!part.isDirectory())){
				Logger.d("part = " + part);
				return mContext.getResources().getString(R.string.please_check, part);
			}
			//返回要删除的目录列表
			File[] childFiles = part.listFiles(new FileFilter() {
				
				@Override
				public boolean accept(File pathname) {
					String name = pathname.getName().toLowerCase();
					Logger.d("accept---------------name = " + name);
//					return name.contains(delete_file);
					return name.equals(delete_file);
				}
			});
			
			if (null == childFiles){
				Logger.d("null == childFiles");
				return mContext.getResources().getString(R.string.please_check, delete_part + delete_file);
			}else {
				boolean result = true;
				for (File child : childFiles){
					Logger.d("child = " + child.getAbsolutePath());
					boolean ret = deleteDirs(child.getAbsolutePath());
					result = result && ret;
					if (!ret){
						Logger.d("delete failed : " + child.getAbsolutePath());
					}
				}
				return result ? (mContext.getResources().getString(R.string.delete_success, delete_part + delete_file))
						: (mContext.getResources().getString(R.string.delete_fail, delete_part + delete_file));
			}
			
		}
		
		@Override
		protected void onPostExecute(String result) {
			super.onPostExecute(result);
			Logger.d("result = " + result);
			mTextView.setText(result);
		}
	}

	@Override
	public void onClick(View v) {
		Logger.d();
		String delete_part = deletePart.getText().toString().trim();
		String delete_file = deleteFile.getText().toString().trim();
		if (v.getId() == R.id.delete_file){
			if (!TextUtils.isEmpty(delete_part)){
				if (!TextUtils.isEmpty(delete_file)){
					new DeleteFileTask().execute(delete_part, delete_file);
				}
			}else{
				mTextView.setText( mContext.getResources().getString(R.string.please_check, delete_part));
			}
			
		}
		
	}
}
