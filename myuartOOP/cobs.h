#ifndef COBS_H_
#define COBS_H_
#include <stdint.h>
#include <stddef.h>

#define COBS_BUFFER 256
class Cobs {
public:
	Cobs();
		size_t setCobsData(const uint8_t *ptr,size_t length);
		uint8_t* getCobsData();
		size_t getCobsDataLength();
		uint8_t* getData();
		size_t getDataLength();
		size_t setData(const uint8_t *ptr,size_t length);
		size_t unStuffData();
		size_t stuffData();
		size_t StuffData(uint8_t *ptr, size_t length, uint8_t *dst);
		void clearData();
private:
		uint8_t mCobsData[COBS_BUFFER];//cobs打包数据长度
		size_t  mCobsDataLen;//数据长度
		uint8_t mData[COBS_BUFFER];//解包数据长度
		size_t  mDataLen;//数据长度
};

#endif /* COBS_H_ */
