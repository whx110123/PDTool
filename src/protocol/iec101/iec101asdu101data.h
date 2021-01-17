#ifndef IEC101ASDU101DATA_H
#define IEC101ASDU101DATA_H

#include "iec101asdu.h"


class IEC101Asdu101Data : public IEC101AsduData
{
public:
	IEC101Asdu101Data();
	~IEC101Asdu101Data();
	virtual bool handle(const QByteArray& buff);
	virtual bool createData(IECDataConfig& config);

public:
	uchar qcc;
};

#endif // IEC101ASDU101DATA_H
