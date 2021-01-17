#ifndef IEC103ASDU223DATA_H
#define IEC103ASDU223DATA_H

#include "iec103asdu.h"

class IEC103Asdu223Data : public IEC103AsduData
{
public:
	IEC103Asdu223Data();
	~IEC103Asdu223Data();
	virtual bool handle(const QByteArray& buff);
	virtual bool createData(IECDataConfig& config);

public:
	ushort fnam;
	uint flen;
	uchar frq;
};

#endif // IEC103ASDU223DATA_H
