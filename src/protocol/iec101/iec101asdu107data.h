#ifndef IEC101ASDU107DATA_H
#define IEC101ASDU107DATA_H

#include "iec101asdu.h"



class IEC101Asdu107Data : public IEC101AsduData
{
public:
	IEC101Asdu107Data();
	~IEC101Asdu107Data();
	virtual bool handle(const QByteArray& buff);
	virtual bool createData(IECDataConfig& config);

public:
	ushort ushortData;
	QDateTime datetime;
};

#endif // IEC101ASDU107DATA_H
