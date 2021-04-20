#ifndef IEC104ASDU63DATA_H
#define IEC104ASDU63DATA_H

#include "iec101asdu50data.h"


//带CP56Time2a时标的设定值命令, 短浮点数
class IEC104Asdu63Data : public IEC101Asdu50Data
{
public:
	IEC104Asdu63Data(const MyConfig& Config);
	~IEC104Asdu63Data();
	virtual bool handle(const QByteArray& buff);

public:
	QDateTime datetime;
};

#endif // IEC104ASDU63DATA_H
