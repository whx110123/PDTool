#ifndef IEC101APCI_H
#define IEC101APCI_H

#include <mybase.h>

class IEC101Code : public MyBase
{
public:
	IEC101Code();
	~IEC101Code();
	virtual bool init(const QByteArray& buff);
	virtual bool createData(IECDataConfig& config);

public:
	uchar mcode;		//功能码
};

class IEC101Apci : public MyBase
{
public:
	IEC101Apci();
	~IEC101Apci();
	virtual bool init(const QByteArray& buff);
	virtual bool createData(IECDataConfig& config);

public:
	uchar flag;				//启动字符
	ushort length;			//长度域
	IEC101Code code;		//功能码
	ushort addr;			//地址域

public:
	QString mLengthType;			//长度域类型
	int mAddrLen;				//地址域字节数
};

#endif // IEC101APCI_H
