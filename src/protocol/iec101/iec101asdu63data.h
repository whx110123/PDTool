#ifndef IEC101ASDU63DATA_H
#define IEC101ASDU63DATA_H

#include "iec101asdu50data.h"



class IEC101Asdu63Data : public IEC101Asdu50Data
{
public:
	IEC101Asdu63Data();
	~IEC101Asdu63Data();
	virtual bool handle(const QByteArray& buff);
	virtual bool createData(IECDataConfig& config);

public:
	QDateTime datetime;
};

#endif // IEC101ASDU63DATA_H
