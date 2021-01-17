#ifndef IEC101ASDU13DATA_H
#define IEC101ASDU13DATA_H

#include "iec101asdu.h"

class IEC101Asdu13Data : public IEC101AsduData
{
public:
	IEC101Asdu13Data();
	~IEC101Asdu13Data();
	virtual bool handle(const QByteArray& buff);
	virtual bool createData(IECDataConfig& config);

public:
	float floatdata;
	uchar qds;
};

#endif // IEC101ASDU13DATA_H
