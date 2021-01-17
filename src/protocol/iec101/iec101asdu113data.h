#ifndef IEC101ASDU113DATA_H
#define IEC101ASDU113DATA_H

#include "iec101asdu.h"



class IEC101Asdu113Data : public IEC101AsduData
{
public:
	IEC101Asdu113Data();
	~IEC101Asdu113Data();
	virtual bool handle(const QByteArray& buff);
	virtual bool createData(IECDataConfig& config);

public:
	uchar qpa;
};

#endif // IEC101ASDU113DATA_H
