#ifndef IEC101ASDU112DATA_H
#define IEC101ASDU112DATA_H

#include "iec101asdu.h"



class IEC101Asdu112Data : public IEC101AsduData
{
public:
	IEC101Asdu112Data();
	~IEC101Asdu112Data();
	virtual bool handle(const QByteArray& buff);
	virtual bool createData(IECDataConfig& config);

public:
	float floatdata;
	uchar qpm;
};

#endif // IEC101ASDU112DATA_H
