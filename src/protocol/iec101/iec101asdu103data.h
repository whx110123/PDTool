#ifndef IEC101ASDU103DATA_H
#define IEC101ASDU103DATA_H

#include "iec101asdu.h"


class IEC101Asdu103Data : public IEC101AsduData
{
public:
	IEC101Asdu103Data(const MyConfig& Config);
	~IEC101Asdu103Data();
	virtual bool handle(const QByteArray& buff);
	virtual bool createData(MyData& proData);

public:
	QDateTime datetime;
};

#endif // IEC101ASDU103DATA_H
