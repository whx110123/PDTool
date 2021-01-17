#ifndef IEC101ASDU5DATA_H
#define IEC101ASDU5DATA_H

#include "iec101asdu.h"



class IEC101Asdu5Data : public IEC101AsduData
{
public:
	IEC101Asdu5Data();
	~IEC101Asdu5Data();
	virtual bool handle(const QByteArray& buff);
	virtual bool createData(IECDataConfig& config);

public:
	uchar vti;
	uchar qds;
};

#endif // IEC101ASDU5DATA_H
