#ifndef IEC101ASDU2DATA_H
#define IEC101ASDU2DATA_H

#include "iec101asdu1data.h"

class IEC101Asdu2Data : public IEC101Asdu1Data
{
public:
	IEC101Asdu2Data(const MyConfig& Config);
	~IEC101Asdu2Data();
	virtual bool handle(const QByteArray& buff);

public:
	QDateTime datetime;
};

#endif // IEC101ASDU2DATA_H
