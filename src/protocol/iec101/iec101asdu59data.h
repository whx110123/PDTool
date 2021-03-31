#ifndef IEC101ASDU59DATA_H
#define IEC101ASDU59DATA_H

#include "iec101asdu46data.h"



class IEC101Asdu59Data : public IEC101Asdu46Data
{
public:
	IEC101Asdu59Data(const MyConfig& Config);
	~IEC101Asdu59Data();
	virtual bool handle(const QByteArray& buff);
	virtual bool createData(MyData& proData);

public:
	QDateTime datetime;
};

#endif // IEC101ASDU59DATA_H
