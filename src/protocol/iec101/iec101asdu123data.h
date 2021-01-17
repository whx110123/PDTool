#ifndef IEC101ASDU123DATA_H
#define IEC101ASDU123DATA_H

#include "iec101asdu.h"



class IEC101Asdu123Data : public IEC101AsduData
{
public:
	IEC101Asdu123Data();
	~IEC101Asdu123Data();
	virtual bool handle(const QByteArray& buff);
	virtual bool createData(IECDataConfig& config);

public:
	ushort nof;
	uchar nos;
	uchar lsq;
	uchar chs;
};

#endif // IEC101ASDU123DATA_H
