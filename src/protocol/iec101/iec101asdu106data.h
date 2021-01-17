#ifndef IEC101ASDU106DATA_H
#define IEC101ASDU106DATA_H

#include "iec101asdu103data.h"



class IEC101Asdu106Data : public IEC101Asdu103Data
{
public:
	IEC101Asdu106Data();
	~IEC101Asdu106Data();
	virtual bool handle(const QByteArray& buff);
	virtual bool createData(IECDataConfig& config);
};

#endif // IEC101ASDU106DATA_H
