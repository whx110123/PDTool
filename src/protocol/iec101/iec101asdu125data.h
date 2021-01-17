#ifndef IEC101ASDU125DATA_H
#define IEC101ASDU125DATA_H

#include "iec101asdu.h"



class IEC101Asdu125Data : public IEC101AsduData
{
public:
	IEC101Asdu125Data();
	~IEC101Asdu125Data();
	virtual bool handle(const QByteArray& buff);
	virtual bool createData(IECDataConfig& config);

public:
	ushort nof;
	uchar nos;
	uchar los;
	QString gbkstr;
};

#endif // IEC101ASDU125DATA_H
