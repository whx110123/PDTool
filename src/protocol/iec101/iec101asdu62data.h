#ifndef IEC101ASDU62DATA_H
#define IEC101ASDU62DATA_H

#include "iec101asdu49data.h"



class IEC101Asdu62Data : public IEC101Asdu49Data
{
public:
	IEC101Asdu62Data();
	~IEC101Asdu62Data();
	virtual bool handle(const QByteArray& buff);
	virtual bool createData(IECDataConfig& config);

public:
	QDateTime datetime;
};

#endif // IEC101ASDU62DATA_H
