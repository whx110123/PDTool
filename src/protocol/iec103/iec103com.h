#ifndef IEC103COM_H
#define IEC103COM_H

#include "iec103asdu.h"
#include <iec101apci.h>

class IEC103COM : public MyBase
{
public:
	IEC103COM();
	~IEC103COM();
	virtual bool init(const QByteArray& buff);
	virtual QString showToText();
	virtual bool createData(IECDataConfig& config);

public:
	IEC101Apci apci;
	IEC103Asdu asdu;
	uchar crc;
	uchar end;

public:
	QString mLengthType;		//长度域类型
	int mAddrLen;				//地址域字节数
};

#endif // IEC103COM_H
