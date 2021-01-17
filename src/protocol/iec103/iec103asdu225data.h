#ifndef IEC103ASDU225DATA_H
#define IEC103ASDU225DATA_H

#include "iec103asdu.h"

class IEC103Asdu225Data : public IEC103AsduData
{
public:
	IEC103Asdu225Data();
	~IEC103Asdu225Data();
	virtual bool handle(const QByteArray& buff);
	virtual bool createData(IECDataConfig& config);

public:
	ushort fnam;
	uchar snam;
	ushort tmp;
	ushort dlen;
	QString gbkstr;
};

#endif // IEC103ASDU225DATA_H
