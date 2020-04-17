/*
 * DataFrame.h
 *
 */

#ifndef DATAFRAME_H_
#define DATAFRAME_H_
#include <stdint.h>
#include <stddef.h>


#define DATA_FRAME_BUFFER 256

class DataFrame {
public:
	DataFrame();
	virtual ~DataFrame();
	void setData(uint8_t CT,uint8_t CMD,uint8_t SMD,uint8_t SN,uint8_t PRIORITY_RET,uint8_t *DATA,uint8_t  DataLen);
	void setFrameData(const uint8_t *Frame,uint8_t FrameLen);
	void setFrameDataNoCheckSum(const uint8_t *Frame,uint8_t FrameLen);
	void setAck(uint8_t CMD,uint8_t SMD,uint8_t SN);
	void printfData();
	uint16_t  checksum( uint8_t *Frame,uint16_t FrameLen);

	uint16_t getCheckSum() const {
		return mCheckSum;
	}

	uint8_t getCmd() const {
		return mCMD;
	}

	uint8_t getCt() const {
		return mCT;
	}

	uint8_t* getData() const {
		return mDATA;
	}

	uint8_t getDataLen() const {
		return mDataLen;
	}

	const uint8_t* getFrame() const {
		return mFrame;
	}

	uint8_t getFrameLen() const {
		return mFrameLen;
	}

	uint8_t getPriorityRet() const {
		return mPRIORITY_RET;
	}

	uint8_t getSmd() const {
		return mSMD;
	}

	uint8_t getSn() const {
		return mSN;
	}
	void clearData();

	void setSn(uint8_t sn);
private:
	uint16_t checkSum();


	uint8_t mCT;//命令类型
	uint8_t mCMD;//命令主ID;
	uint8_t mSMD;//命令子ID;
	uint8_t mSN;//流水号;0-15
	uint8_t mPRIORITY_RET;//优先级
	uint8_t *mDATA;//有效数据
	uint8_t mDataLen;//数据长度
	uint16_t mCheckSum;//CRC校验值
	uint8_t mFrame[DATA_FRAME_BUFFER];//数据
	uint8_t mFrameLen;//数据
};

#endif /* DATAFRAME_H_ */
