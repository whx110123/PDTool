#ifndef IEC101ASDU35DATA_H
#define IEC101ASDU35DATA_H

#include "iec101asdu12data.h"



class IEC101Asdu35Data : public IEC101Asdu12Data
{
public:
	IEC101Asdu35Data();
	~IEC101Asdu35Data();
	virtual bool handle(const QByteArray& buff);
	virtual bool createData(IECDataConfig& config);
};

#endif // IEC101ASDU35DATA_H
