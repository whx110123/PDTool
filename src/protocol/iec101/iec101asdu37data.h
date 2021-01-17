#ifndef IEC101ASDU37DATA_H
#define IEC101ASDU37DATA_H

#include "iec101asdu16data.h"



class IEC101Asdu37Data : public IEC101Asdu16Data
{
public:
	IEC101Asdu37Data();
	~IEC101Asdu37Data();
	virtual bool handle(const QByteArray& buff);
	virtual bool createData(IECDataConfig& config);
};

#endif // IEC101ASDU37DATA_H
