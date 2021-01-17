#ifndef IEC101ASDU16DATA_H
#define IEC101ASDU16DATA_H

#include "iec101asdu15data.h"



class IEC101Asdu16Data : public IEC101Asdu15Data
{
public:
	IEC101Asdu16Data();
	~IEC101Asdu16Data();
	virtual bool handle(const QByteArray& buff);
	virtual bool createData(IECDataConfig& config);

public:
	QDateTime datetime;
};

#endif // IEC101ASDU16DATA_H
