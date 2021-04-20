#ifndef IEC104ASDU61DATA_H
#define IEC104ASDU61DATA_H

#include "iec101asdu48data.h"


//带CP56Time2a时标的设定值命令, 规一化值
class IEC104Asdu61Data : public IEC101Asdu48Data
{
public:
	IEC104Asdu61Data(const MyConfig& Config);
	~IEC104Asdu61Data();
	virtual bool handle(const QByteArray& buff);

public:
	QDateTime datetime;
};

#endif // IEC104ASDU61DATA_H
