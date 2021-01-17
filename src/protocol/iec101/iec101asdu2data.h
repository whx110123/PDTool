#ifndef IEC101ASDU2DATA_H
#define IEC101ASDU2DATA_H

#include "iec101asdu1data.h"

class IEC101Asdu2Data : public IEC101Asdu1Data
{
public:
	IEC101Asdu2Data();
	~IEC101Asdu2Data();
	virtual bool handle(const QByteArray& buff);
	virtual bool createData(IECDataConfig& config);

public:
	QDateTime datetime;
};

#endif // IEC101ASDU2DATA_H
