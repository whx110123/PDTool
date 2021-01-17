#ifndef IEC103ASDU50DATA_H
#define IEC103ASDU50DATA_H

#include "iec103asdu.h"

class IEC103Asdu50Data : public IEC103AsduData
{
public:
	IEC103Asdu50Data();
	~IEC103Asdu50Data();
	virtual bool handle(const QByteArray& buff);
	virtual bool createData(IECDataConfig& config);

public:
	short shortdata;
	uchar qds;
};

#endif // IEC103ASDU50DATA_H
