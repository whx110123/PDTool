#ifndef IEC101ASDU38DATA_H
#define IEC101ASDU38DATA_H

#include "iec101asdu17data.h"



class IEC101Asdu38Data : public IEC101Asdu17Data
{
public:
	IEC101Asdu38Data();
	~IEC101Asdu38Data();
	virtual bool handle(const QByteArray& buff);
	virtual bool createData(IECDataConfig& config);
};

#endif // IEC101ASDU38DATA_H
