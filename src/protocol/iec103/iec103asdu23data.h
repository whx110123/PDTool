#ifndef IEC103ASDU23DATA_H
#define IEC103ASDU23DATA_H

#include "iec103asdu.h"

class IEC103Asdu23Data : public IEC103AsduData
{
public:
	IEC103Asdu23Data();
	~IEC103Asdu23Data();
	virtual bool handle(const QByteArray& buff);
	virtual bool createData(IECDataConfig& config);

public:
	ushort fan;
	uchar sof;
	QDateTime datetime;
};

#endif // IEC103ASDU23DATA_H
