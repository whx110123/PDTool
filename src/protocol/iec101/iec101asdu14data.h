#ifndef IEC101ASDU14DATA_H
#define IEC101ASDU14DATA_H

#include "iec101asdu13data.h"



class IEC101Asdu14Data : public IEC101Asdu13Data
{
public:
	IEC101Asdu14Data();
	~IEC101Asdu14Data();
	virtual bool handle(const QByteArray& buff);
	virtual bool createData(IECDataConfig& config);

public:
	QDateTime datetime;
};

#endif // IEC101ASDU14DATA_H
