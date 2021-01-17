#ifndef IEC101ASDU48DATA_H
#define IEC101ASDU48DATA_H

#include "iec101asdu.h"



class IEC101Asdu48Data : public IEC101AsduData
{
public:
	IEC101Asdu48Data();
	~IEC101Asdu48Data();
	virtual bool handle(const QByteArray& buff);
	virtual bool createData(IECDataConfig& config);

public:
	short shortdata;
	uchar qos;
};

#endif // IEC101ASDU48DATA_H
