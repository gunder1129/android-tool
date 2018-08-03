package com.gunder.tool.adapter;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

import com.gunder.tool.R;

import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.TextView;

/**
 * 菜单适配器
 * @author ytkj
 *
 */
public class MenuItemsAdapter extends BaseAdapter {
	private List<String> mItems = new ArrayList<String>();
	private Context mContext = null;
	private int mIndex = -1;
	private CallBack mCallBack = null;
	public MenuItemsAdapter(Context context, CallBack callBack) {
		mContext = context.getApplicationContext();
		mCallBack = callBack;
		//读取菜单列表
		mItems.addAll(Arrays.asList(mContext.getResources().getStringArray(R.array.res_menu)));
	}
	
	public void setSelectedIndex(int index){
		mIndex = index;
		notifyDataSetChanged();
		String item = ((mIndex < 0 || mIndex >= mItems.size()) ? null : mItems.get(index));
		if (mCallBack != null){
			mCallBack.onItemClick(item);
		}
	}

	public void setSelectedIndex(String item){
		setSelectedIndex((null == item || item.isEmpty()) ? -1 : mItems.indexOf(item));
	}
	
	@Override
	public int getCount() {
		return mItems.size();
	}

	@Override
	public Object getItem(int position) {
		return mItems.get(position);
	}

	@Override
	public long getItemId(int arg0) {
		return 0;
	}

	@Override
	public View getView(int position, View convertView, ViewGroup parent) {
		
		if (null == convertView){
			convertView = createView();
		}
		bindView(convertView, position);
		
		return convertView;
	}
	
	private View createView(){
		ViewHolder holder = new ViewHolder();
		View view = LayoutInflater.from(mContext).inflate(R.layout.layout_item, null);
		holder.mTextView = (TextView) view.findViewById(R.id.item);
		view.setTag(holder);
		return view;
	}
	
	private void bindView(View view, final int position){
		ViewHolder holder = (ViewHolder) view.getTag();
		view.setEnabled(position != mIndex);
		holder.mTextView.setText(mItems.get(position));
	}
	
	class ViewHolder{
		TextView mTextView;
	}
	
	public interface CallBack{
		/**
		 * 选择哪个菜单
		 * @param item 菜单文本，null表示未选中
		 */
		void onItemClick(String item);
	}

}
