#ifndef IEC103ASDU51DATA_H
#define IEC103ASDU51DATA_H

#include "iec103asdu.h"

class IEC103Asdu51Data : public IEC103AsduData
{
public:
	IEC103Asdu51Data();
	~IEC103Asdu51Data();
	virtual bool handle(const QByteArray& buff);
	virtual bool createData(IECDataConfig& config);

public:
	short shortdata;
	uchar qds;
};

#endif // IEC103ASDU51DATA_H
