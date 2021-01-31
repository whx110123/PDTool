#ifndef IEC103ASDU221DATA_H
#define IEC103ASDU221DATA_H

#include "iec103asdu.h"

class IEC103Asdu221Data : public IEC103AsduData
{
public:
	IEC103Asdu221Data(const MyConfig& Config);
	~IEC103Asdu221Data();
	virtual bool handle(const QByteArray& buff);

public:
	ushort fnam;
	uchar snam;
	uchar scq;
};

#endif // IEC103ASDU221DATA_H
