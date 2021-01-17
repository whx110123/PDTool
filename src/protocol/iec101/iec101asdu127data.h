#ifndef IEC101ASDU127DATA_H
#define IEC101ASDU127DATA_H

#include "iec101asdu.h"



class IEC101Asdu127Data : public IEC101AsduData
{
public:
	IEC101Asdu127Data();
	~IEC101Asdu127Data();
	virtual bool handle(const QByteArray& buff);
	virtual bool createData(IECDataConfig& config);

public:
	ushort nof;
	QDateTime datetime1;
	QDateTime datetime2;
};

#endif // IEC101ASDU127DATA_H
