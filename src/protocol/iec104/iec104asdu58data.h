#ifndef IEC104ASDU58DATA_H
#define IEC104ASDU58DATA_H

#include "iec101asdu45data.h"


//带CP56Time2a时标的单点命令
class IEC104Asdu58Data : public IEC101Asdu45Data
{
public:
	IEC104Asdu58Data(const MyConfig& Config);
	~IEC104Asdu58Data();
	virtual bool handle(const QByteArray& buff);
	virtual bool createData(MyData& proData);

public:
	QDateTime datetime;
};

#endif // IEC104ASDU58DATA_H
