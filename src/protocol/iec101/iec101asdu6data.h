#ifndef IEC101ASDU6DATA_H
#define IEC101ASDU6DATA_H

#include "iec101asdu5data.h"



class IEC101Asdu6Data : public IEC101Asdu5Data
{
public:
	IEC101Asdu6Data();
	~IEC101Asdu6Data();
	virtual bool handle(const QByteArray& buff);
	virtual bool createData(IECDataConfig& config);

public:
	QDateTime datetime;
};

#endif // IEC101ASDU6DATA_H
