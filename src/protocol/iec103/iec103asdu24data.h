#ifndef IEC103ASDU24DATA_H
#define IEC103ASDU24DATA_H

#include "iec103asdu.h"

class IEC103Asdu24Data : public IEC103AsduData
{
public:
	IEC103Asdu24Data();
	~IEC103Asdu24Data();
	virtual bool handle(const QByteArray& buff);
	virtual bool createData(IECDataConfig& config);

public:
	uchar too;
	uchar tov;
	ushort fan;
	uchar acc;
};

#endif // IEC103ASDU24DATA_H
