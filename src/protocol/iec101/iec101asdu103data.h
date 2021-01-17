#ifndef IEC101ASDU103DATA_H
#define IEC101ASDU103DATA_H

#include "iec101asdu.h"


class IEC101Asdu103Data : public IEC101AsduData
{
public:
	IEC101Asdu103Data();
	~IEC101Asdu103Data();
	virtual bool handle(const QByteArray& buff);
	virtual bool createData(IECDataConfig& config);

public:
	QDateTime datetime;
};

#endif // IEC101ASDU103DATA_H
