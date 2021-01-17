#ifndef IEC101ASDU126DATA_H
#define IEC101ASDU126DATA_H

#include "iec101asdu.h"



class IEC101Asdu126Data : public IEC101AsduData
{
public:
	IEC101Asdu126Data();
	~IEC101Asdu126Data();
	virtual bool handle(const QByteArray& buff);
	virtual bool createData(IECDataConfig& config);

public:
	ushort nof;
	uint lof;
	uchar sof;
	QDateTime datetime;
};

#endif // IEC101ASDU126DATA_H
