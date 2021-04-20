#ifndef IEC104ASDU64DATA_H
#define IEC104ASDU64DATA_H

#include "iec101asdu51data.h"


//带CP56Time2a时标的32比特串
class IEC104Asdu64Data : public IEC101Asdu51Data
{
public:
	IEC104Asdu64Data(const MyConfig& Config);
	~IEC104Asdu64Data();
	virtual bool handle(const QByteArray& buff);

public:
	QDateTime datetime;
};

#endif // IEC104ASDU64DATA_H
