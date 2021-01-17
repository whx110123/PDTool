#ifndef IEC101ASDU137DATA_H
#define IEC101ASDU137DATA_H

#include "iec101asdu.h"


class IEC101Asdu137Data : public IEC101AsduData
{
public:
	IEC101Asdu137Data();
	~IEC101Asdu137Data();
	virtual bool handle(const QByteArray& buff);
	virtual bool createData(IECDataConfig& config);

public:
	short shortdata;
	uchar qos;
	QDateTime datetime;
};

#endif // IEC101ASDU137DATA_H
