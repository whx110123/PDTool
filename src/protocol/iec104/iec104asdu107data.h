#ifndef IEC104ASDU107DATA_H
#define IEC104ASDU107DATA_H

#include "iec101asdu.h"


//带CP56Time2a时标的测试命今
class IEC104Asdu107Data : public IEC101AsduData
{
public:
	IEC104Asdu107Data(const MyConfig& Config);
	~IEC104Asdu107Data();
	virtual bool handle(const QByteArray& buff);

public:
	ushort ushortData;
	QDateTime datetime;
};

#endif // IEC104ASDU107DATA_H
