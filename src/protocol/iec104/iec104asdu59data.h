#ifndef IEC104ASDU59DATA_H
#define IEC104ASDU59DATA_H

#include "iec101asdu46data.h"


//带CP56Time2a时标的双点命令
class IEC104Asdu59Data : public IEC101Asdu46Data
{
public:
	IEC104Asdu59Data(const MyConfig& Config);
	~IEC104Asdu59Data();
	virtual bool handle(const QByteArray& buff);
	virtual bool createData(MyData& proData);

public:
	QDateTime datetime;
};

#endif // IEC104ASDU59DATA_H
