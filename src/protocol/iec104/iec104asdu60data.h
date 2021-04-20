#ifndef IEC104ASDU60DATA_H
#define IEC104ASDU60DATA_H

#include "iec101asdu47data.h"


//带CP56Time2a时标的步调节命令
class IEC104Asdu60Data : public IEC101Asdu47Data
{
public:
	IEC104Asdu60Data(const MyConfig& Config);
	~IEC104Asdu60Data();
	virtual bool handle(const QByteArray& buff);

public:
	QDateTime datetime;
};

#endif // IEC104ASDU60DATA_H
