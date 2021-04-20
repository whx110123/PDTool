#ifndef IEC104ASDU62DATA_H
#define IEC104ASDU62DATA_H

#include "iec101asdu49data.h"


//带CP56Time2a时标的设定值命令, 标度化值
class IEC104Asdu62Data : public IEC101Asdu49Data
{
public:
	IEC104Asdu62Data(const MyConfig& Config);
	~IEC104Asdu62Data();
	virtual bool handle(const QByteArray& buff);

public:
	QDateTime datetime;
};

#endif // IEC104ASDU62DATA_H
