#ifndef IEC103ASDU27DATA_H
#define IEC103ASDU27DATA_H

#include "iec103asdu.h"

class IEC103Asdu27Data : public IEC103AsduData
{
public:
	IEC103Asdu27Data(const MyConfig& Config);
	~IEC103Asdu27Data();
	virtual bool handle(const QByteArray& buff);

public:
	uchar datauchar;
	uchar tov;
	ushort fan;
	uchar acc;
	float rpv;
	float rsv;
	float rfa;
};

#endif // IEC103ASDU27DATA_H
