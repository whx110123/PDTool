#ifndef IEC101ASDU116DATA_H
#define IEC101ASDU116DATA_H

#include "iec101asdu.h"



class IEC101Asdu116Data : public IEC101AsduData
{
public:
	IEC101Asdu116Data(const MyConfig& Config);
	~IEC101Asdu116Data();
	virtual bool handle(const QByteArray& buff);

public:
	uchar dataType;
	uchar opFlag;
	uchar result;
	uchar fileNameSize;
	QString fileName;
	uint fileID;
	uint fileSize;
	uint dataIndex;
	uchar isLast;
	QString fileData;
	uchar crc;
	QTextCodec *gbk;
};

#endif // IEC101ASDU116DATA_H
