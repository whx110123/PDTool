#ifndef IEC103ASDU221DATA_H
#define IEC103ASDU221DATA_H

#include "iec103asdu.h"

class IEC103Asdu221Data : public IEC103AsduData
{
public:
	IEC103Asdu221Data();
	~IEC103Asdu221Data();
	virtual bool handle(const QByteArray& buff);
	virtual bool createData(IECDataConfig& config);

public:
	ushort fnam;
	uchar snam;
	uchar scq;
};

#endif // IEC103ASDU221DATA_H
