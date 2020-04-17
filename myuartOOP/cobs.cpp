/*
 * Cobs.cpp
 *    本文件用于实现cobs算法，对数据进行编码和解码
 */

#include "cobs.h"
#include <string.h>
#include <log/log.h>
#define FinishBlock(X) (*code_ptr= (X),code_ptr=dst++,code=0x01)

Cobs::Cobs(){
	clearData();
}
/**
 * 清除mCobsData和mData
 * 	 mCobsData为编码之后的缓存数据
 * 	 mData为原始的用户数据
 */
void Cobs::clearData(){
	memset(mCobsData,0,COBS_BUFFER);
	memset(mData,0,COBS_BUFFER);
	mCobsDataLen= 0;
	mDataLen= 0;
}
/**
 * 用于保存一个完整的编码之后的数据到mCobsData中,并对传入的包进行基本的效验
 * @param const uint8_t *ptr 编码的数据指针
 * @param size_t length 编码的数据长度
 * @return size_t 返回完整编码长度,如果数据包符合规则则返回传入的编码数据长度
 * 				0 表示传入的数据编码数据不符合cobs编码规则
 */
size_t Cobs::setCobsData(const uint8_t *ptr,size_t length){
	size_t size = 0;
	int len = length< COBS_BUFFER? length:COBS_BUFFER;
	//效验传包的数据是否正确，即根据规则判断0的位置是否正确
	for(int i=0;i<len;i++){
		if(*(ptr+i) ==0 ){
			size = i+1;
			break;
		}
	}
	memset(mCobsData,0,COBS_BUFFER);
	memcpy(mCobsData,ptr,size);
	mCobsDataLen = size;
	return size;
	}
/**
 * 获取cobs数据的指针
 * @return uint8_t 返回cobs编码数据指针
 */
uint8_t* Cobs::getCobsData(){
	return mCobsData;
}
/**
 * 获取解码之后的原始数据的指针
 * @return uint8_t 返回数据指针
 */
uint8_t* Cobs::getData(){
	return mData;
}
/**
 * 获取cobs数据的长度
 * @return uint8_t 返回cobs数据的长度
 */
size_t Cobs::getCobsDataLength(){
	return mCobsDataLen;
}
/**
 * 获取用户数据的长度
 * @return uint8_t 返回数据的长度
 */
size_t Cobs::getDataLength(){
	return mDataLen;
}

/**
 * 获取用户数据的到缓存
 * const uint8_t *ptr 用户数据指针
 * size_t length 用户数据长度 最大超过 256
 * @return uint8_t 返回数据的长度
 */
size_t Cobs::setData(const uint8_t *ptr,size_t length){
	memset(mData,0,COBS_BUFFER);
	if(length>= COBS_BUFFER){
		mDataLen = 0;
		return 0;
	}

	memcpy(mData,ptr,length);
	mDataLen = length;
	return length;
}

/**
 * 对mData中的用户数据进行编码操作到mCobsData,打包之后的数据最后都是以零结尾
*   数据例子
*   序号   用户数据   			编码数据
*   1			00			 			01 01 00
*   2			00 00    				01 01 01 00
*   3			11 22 00 33 		03 11 22 02 33 00
*   4			11 22 33 44			05 11 22 33 44 00
*   5 		11 00 00 00			02 11 01 01 01 00
*   6			01 02 .... FE			FF 01 02 ......FE 01 00
 * @return uint8_t 返回编码后mCobsData数据的长度
 */

size_t Cobs::stuffData(){
	size_t len = 0;
	uint8_t *dst = mCobsData;
	uint8_t *ptr =mData;
	size_t length = mDataLen;

	memset(mCobsData,0,COBS_BUFFER);
	mCobsDataLen = 0;
	if(mDataLen ==0)
		return mCobsDataLen;

	  const uint8_t *end = ptr + length;
	  uint8_t * dst_org = dst;
	  uint8_t *code_ptr = dst++;
	  uint8_t code = 0x01;

	  while (ptr < end)
	  {
	    if (*ptr == 0)
	      FinishBlock(code);
	    else
	    {
	      *dst++ = *ptr;
	      if (++code == 0xFF)
	        FinishBlock(code);
	    }
	    ptr++;
	  }

	  FinishBlock(code);
	  FinishBlock(0);
	  len = code_ptr -dst_org;
	  mCobsDataLen = len;
	  return len;
}
size_t Cobs::StuffData(uint8_t *ptr, size_t length, uint8_t *dst){
	uint8_t *end      = ptr + length;	
	uint8_t *code_ptr = dst++;	
	uint8_t code      = 0x01;	
	uint8_t len       = 2;	
	
	while (ptr < end){		
		if (*ptr == 0){			
			FinishBlock(code);		
			}		
		else{			
			*dst++ = *ptr;
			if (++code == 0xFF)	{
				FinishBlock(code);
				len++;
				}
			}
		ptr++;
		}
	FinishBlock(code);
	int tmp =length+len;
	printf("cobs len=mCob222sDataLen==%d\n",tmp);
	return length+len;
	}

/**
 * 对mCobsData中的用户数据进行解码操作到mData
 * @return uint8_t 返回编码mData数据的长度
 */
size_t Cobs::unStuffData(){
	size_t len = 0;
		memset(mData,0x00,COBS_BUFFER);
		mDataLen = 0;
		uint8_t *ptr = mCobsData;
		size_t length = mCobsDataLen;
		uint8_t *dst = mData;
	  const uint8_t *end = ptr + length;
	  uint8_t * dst_org = mData;
	  while (ptr < end)
	  {
	    int code = *ptr++;
	    if(ptr+code > end+1){
	    	mDataLen = 0;
	    	return mDataLen;
	    }
	    for (int i = 1; ptr < end&&i < code; i++)
	      *dst++ = *ptr++;
	    if (code != 0)
	      *dst++ = 0;
	  }
	  len = dst-dst_org-1;
	  mDataLen = len;
	return len;

}




