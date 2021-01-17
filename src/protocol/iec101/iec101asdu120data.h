#ifndef IEC101ASDU120DATA_H
#define IEC101ASDU120DATA_H

#include "iec101asdu.h"



class IEC101Asdu120Data : public IEC101AsduData
{
public:
	IEC101Asdu120Data();
	~IEC101Asdu120Data();
	virtual bool handle(const QByteArray& buff);
	virtual bool createData(IECDataConfig& config);

public:
	uchar frq;
};

#endif // IEC101ASDU120DATA_H
