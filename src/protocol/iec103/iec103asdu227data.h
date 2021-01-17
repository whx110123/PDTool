#ifndef IEC103ASDU227DATA_H
#define IEC103ASDU227DATA_H

#include "iec103asdu.h"

class IEC103Asdu227Data : public IEC103AsduData
{
public:
	IEC103Asdu227Data();
	~IEC103Asdu227Data();
	virtual bool handle(const QByteArray& buff);
	virtual bool createData(IECDataConfig& config);

public:
	ushort fnam;
	uchar snam;
	uchar afq;
};

#endif // IEC103ASDU227DATA_H
