#ifndef IEC103ASDU40DATA_H
#define IEC103ASDU40DATA_H

#include "iec103asdu.h"

class IEC103Asdu40Data : public IEC103AsduData
{
public:
	IEC103Asdu40Data();
	~IEC103Asdu40Data();
	virtual bool handle(const QByteArray& buff);
	virtual bool createData(IECDataConfig& config);

public:
	uchar siq;
};

#endif // IEC103ASDU40DATA_H
