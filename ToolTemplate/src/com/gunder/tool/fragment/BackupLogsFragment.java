package com.gunder.tool.fragment;

import android.os.AsyncTask;
import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.Toast;

import com.gunder.tool.R;
import com.gunder.tool.utils.Logger;
import com.gunder.tool.utils.TLogUtils;

public class BackupLogsFragment extends Fragment implements OnClickListener{
	Button deleteLog;
	@Override
	public View onCreateView(LayoutInflater inflater,
			 ViewGroup container,  Bundle savedInstanceState) {
		return inflater.inflate(R.layout.backup_log_fragment, container, false);
	}
	
	@Override
	public void onViewCreated(View view,  Bundle savedInstanceState) {
		super.onViewCreated(view, savedInstanceState);
		
		initView(view);
		
	}

	private void initView(View root) {
		deleteLog = (Button) root.findViewById(R.id.delelte_log);
		deleteLog.setOnClickListener(this);
	}

	@Override
	public void onClick(View v) {
		switch (v.getId()) {
		case R.id.delelte_log:
			deleteLogs();
			break;

		default:
			break;
		}
	}
	
	//开始删除日志
	private void deleteLogs(){
		 final String delete_path = "/data/media";
		 new DeleteLogsTask().execute(delete_path);
	}
	
	private class DeleteLogsTask extends AsyncTask<String, String, String>{
		
		@Override
		protected void onPreExecute() {
			super.onPreExecute();
			Toast.makeText(getActivity(), "delete file ...", Toast.LENGTH_LONG).show();
		}

		@Override
		protected String doInBackground(String... params) {
			boolean result = true;
			String path = params[0];
			Logger.d("path = " + path);
			boolean ret = deleteLog(path);
			result = result && ret;
			return result ? "success" : "failed";
		}
		protected boolean deleteLog(String path){
			Logger.d();
			return TLogUtils.deleteLog(path);
		}
		
		@Override
		protected void onPostExecute(String result) {
			super.onPostExecute(result);
			Toast.makeText(getActivity(), "delete " + result, Toast.LENGTH_LONG).show();
		}
	}
}
