#ifndef IEC104ASDU127DATA_H
#define IEC104ASDU127DATA_H

#include "iec101asdu.h"


//查询日志
class IEC104Asdu127Data : public IEC101AsduData
{
public:
	IEC104Asdu127Data(const MyConfig& Config);
	~IEC104Asdu127Data();
	virtual bool handle(const QByteArray& buff);

public:
	ushort nof;
	QDateTime datetime1;
	QDateTime datetime2;
};

#endif // IEC104ASDU127DATA_H
