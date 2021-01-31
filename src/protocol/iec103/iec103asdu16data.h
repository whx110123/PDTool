#ifndef IEC103ASDU16DATA_H
#define IEC103ASDU16DATA_H

#include "iec103asdu15data.h"

struct WaveFileInfo
{
	uchar addr;			//录波装置地址文件,南网使用
	QString fileName;
	QDateTime dt;
	uint fileSize;
	uint no;			//在装置中的编号
	QString fileInfo;	//故障概要描述信息
};

class IEC103Asdu16Data : public IEC103Asdu15Data
{
public:
	IEC103Asdu16Data(const MyConfig& Config);
	~IEC103Asdu16Data();
	virtual bool handle(const QByteArray& buff);

public:
	uchar isLast;
	ushort fileNum;
	QVector<WaveFileInfo> files;
	QTextCodec *gbk;
};

#endif // IEC103ASDU16DATA_H
