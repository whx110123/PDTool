#ifndef IEC101ASDU8DATA_H
#define IEC101ASDU8DATA_H

#include "iec101asdu7data.h"



class IEC101Asdu8Data : public IEC101Asdu7Data
{
public:
	IEC101Asdu8Data();
	~IEC101Asdu8Data();
	virtual bool handle(const QByteArray& buff);
	virtual bool createData(IECDataConfig& config);

public:
	QDateTime datetime;
};

#endif // IEC101ASDU8DATA_H
