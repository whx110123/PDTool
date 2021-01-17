#ifndef IEC103ASDU65DATA_H
#define IEC103ASDU65DATA_H

#include "iec103asdu.h"



class IEC103Asdu65Data : public IEC103AsduData
{
public:
	IEC103Asdu65Data();
	~IEC103Asdu65Data();
	virtual bool handle(const QByteArray& buff);
	virtual bool createData(IECDataConfig& config);

public:
	uchar rcc;
};

#endif // IEC103ASDU65DATA_H
