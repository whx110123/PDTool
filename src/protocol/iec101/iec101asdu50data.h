#ifndef IEC101ASDU50DATA_H
#define IEC101ASDU50DATA_H

#include "iec101asdu.h"


class IEC101Asdu50Data : public IEC101AsduData
{
public:
	IEC101Asdu50Data();
	~IEC101Asdu50Data();
	virtual bool handle(const QByteArray& buff);
	virtual bool createData(IECDataConfig& config);

public:
	float floatdata;
	uchar qos;
};

#endif // IEC101ASDU50DATA_H
