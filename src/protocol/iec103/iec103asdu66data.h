#ifndef IEC103ASDU66DATA_H
#define IEC103ASDU66DATA_H

#include "iec103asdu.h"



class IEC103Asdu66Data : public IEC103AsduData
{
public:
	IEC103Asdu66Data();
	~IEC103Asdu66Data();
	virtual bool handle(const QByteArray& buff);
	virtual bool createData(IECDataConfig& config);

public:
	short shortdata;
	uchar qos;
};

#endif // IEC103ASDU66DATA_H
