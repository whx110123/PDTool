#ifndef IEC104ASDU116DATA_H
#define IEC104ASDU116DATA_H

#include "iec101asdu.h"


//源端维护
class IEC104Asdu116Data : public IEC101AsduData
{
public:
	IEC104Asdu116Data(const MyConfig& Config);
	~IEC104Asdu116Data();
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

#endif // IEC104ASDU116DATA_H
