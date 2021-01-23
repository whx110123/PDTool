#ifndef IEC103ASDU16DATA_H
#define IEC103ASDU16DATA_H

#include "iec103asdu15data.h"

struct WaveFileInfo
{
	uchar addr;
	QString fileName;
	QDateTime dt;
	uint fileSize;
};

class IEC103Asdu16Data : public IEC103Asdu15Data
{
public:
	IEC103Asdu16Data();
	~IEC103Asdu16Data();
	virtual bool handle(const QByteArray& buff);

public:
	uchar isLast;
	ushort fileNum;
	QVector<WaveFileInfo> files;
	QTextCodec *gbk;
};

#endif // IEC103ASDU16DATA_H
