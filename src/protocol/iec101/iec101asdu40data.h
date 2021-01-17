#ifndef IEC101ASDU40DATA_H
#define IEC101ASDU40DATA_H

#include "iec101asdu19data.h"



class IEC101Asdu40Data : public IEC101Asdu19Data
{
public:
	IEC101Asdu40Data();
	~IEC101Asdu40Data();
	virtual bool handle(const QByteArray& buff);
	virtual bool createData(IECDataConfig& config);
};

#endif // IEC101ASDU40DATA_H
