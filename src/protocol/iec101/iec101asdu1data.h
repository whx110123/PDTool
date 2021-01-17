#ifndef IEC101ASDU1DATA_H
#define IEC101ASDU1DATA_H

#include "iec101asdu.h"

class IEC101Asdu1Data : public IEC101AsduData
{
public:
	IEC101Asdu1Data();
	~IEC101Asdu1Data();
	virtual bool handle(const QByteArray& buff);
	virtual bool createData(IECDataConfig& config);

public:
	uchar siq;

};

#endif // IEC101ASDU1DATA_H
