#ifndef IEC104ASDU43DATA_H
#define IEC104ASDU43DATA_H

#include "iec101asdu.h"


//文件传输(一键顺控扩展功能)
class IEC104Asdu43Data : public IEC101AsduData
{
public:
	IEC104Asdu43Data(const MyConfig& Config);
	~IEC104Asdu43Data();
	virtual bool init(const QByteArray& buff);

public:
	uchar cont;
	uint fileindex;
	QString filedata;
	uchar crc;
private:
	QString contToText();
};

#endif // IEC104ASDU43DATA_H
