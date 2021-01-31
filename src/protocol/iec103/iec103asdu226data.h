#ifndef IEC103ASDU226DATA_H
#define IEC103ASDU226DATA_H

#include "iec103asdu.h"

class IEC103Asdu226Data : public IEC103AsduData
{
public:
	IEC103Asdu226Data(const MyConfig& Config);
	~IEC103Asdu226Data();
	virtual bool handle(const QByteArray& buff);

public:
	ushort fnam;
	uchar lsq;
};

#endif // IEC103ASDU226DATA_H
