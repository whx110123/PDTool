#ifndef IEC103ASDU224DATA_H
#define IEC103ASDU224DATA_H

#include "iec103asdu.h"

class IEC103Asdu224Data : public IEC103AsduData
{
public:
	IEC103Asdu224Data();
	~IEC103Asdu224Data();
	virtual bool handle(const QByteArray& buff);
	virtual bool createData(IECDataConfig& config);

public:
	ushort fnam;
	uint flen;
	uchar srq;
};

#endif // IEC103ASDU224DATA_H
