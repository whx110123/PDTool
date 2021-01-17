#ifndef IEC101ASDU124DATA_H
#define IEC101ASDU124DATA_H

#include "iec101asdu.h"



class IEC101Asdu124Data : public IEC101AsduData
{
public:
	IEC101Asdu124Data();
	~IEC101Asdu124Data();
	virtual bool handle(const QByteArray& buff);
	virtual bool createData(IECDataConfig& config);

public:
	ushort nof;
	uchar nos;
	uchar afq;
};

#endif // IEC101ASDU124DATA_H
