#ifndef IEC103ASDU20DATA_H
#define IEC103ASDU20DATA_H

#include "iec103asdu.h"



class IEC103Asdu20Data : public IEC103AsduData
{
public:
	IEC103Asdu20Data(const MyConfig& Config);
	~IEC103Asdu20Data();
	virtual bool handle(const QByteArray& buff);

public:
	uchar dco;
};

#endif // IEC103ASDU20DATA_H
