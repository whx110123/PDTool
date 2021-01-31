#ifndef IEC103ASDU222DATA_H
#define IEC103ASDU222DATA_H

#include "iec103asdu.h"

class IEC103Asdu222Data : public IEC103AsduData
{
public:
	IEC103Asdu222Data(const MyConfig& Config);
	~IEC103Asdu222Data();
	virtual bool handle(const QByteArray& buff);

public:
	ushort fnam;
	uint flen;
	uchar sof;
	QDateTime ftim;
};

#endif // IEC103ASDU222DATA_H
