package com.china.jar;

import android.os.Parcel;
import android.os.Parcelable;

public class StudentInfo implements Parcelable{
	String name;
	int age;
	
	protected StudentInfo(Parcel in){
		name = in.readString();
		age = in.readInt();
	}
	
	public StudentInfo(String name, int age) {
		this.name = name;
		this.age = age;
	}
	public String getName() {
		return name;
	}
	public void setName(String name) {
		this.name = name;
	}
	public int getAge() {
		return age;
	}
	public void setAge(int age) {
		this.age = age;
	}
	@Override
	public int describeContents() {
		return 0;
	}
	@Override
	public void writeToParcel(Parcel dest, int flags) {
		dest.writeString(name);
		dest.writeInt(age);
	}
	
	public static final Creator<StudentInfo> CREATOR = new Creator<StudentInfo>() {

		@Override
		public StudentInfo createFromParcel(Parcel in) {
			return new StudentInfo(in);
		}

		@Override
		public StudentInfo[] newArray(int size) {
			return new StudentInfo[size];
		}
	};
}
