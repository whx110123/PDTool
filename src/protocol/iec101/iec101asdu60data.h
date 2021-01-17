#ifndef IEC101ASDU60DATA_H
#define IEC101ASDU60DATA_H

#include "iec101asdu47data.h"



class IEC101Asdu60Data : public IEC101Asdu47Data
{
public:
	IEC101Asdu60Data();
	~IEC101Asdu60Data();
	virtual bool handle(const QByteArray& buff);
	virtual bool createData(IECDataConfig& config);

public:
	QDateTime datetime;
};

#endif // IEC101ASDU60DATA_H
