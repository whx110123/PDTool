#ifndef IEC103ASDU2DATA_H
#define IEC103ASDU2DATA_H

#include "iec103asdu.h"

class IEC103Asdu2Data : public IEC103AsduData
{
public:
	IEC103Asdu2Data();
	~IEC103Asdu2Data();
	virtual bool handle(const QByteArray& buff);
	virtual bool createData(IECDataConfig& config);

public:
	uchar dpi;
	ushort ret;
	ushort fan;
	QDateTime datetime1;
	QDateTime datetime2;
};

#endif // IEC103ASDU2DATA_H
