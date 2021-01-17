#ifndef IEC103ASDU20DATA_H
#define IEC103ASDU20DATA_H

#include "iec103asdu.h"



class IEC103Asdu20Data : public IEC103AsduData
{
public:
	IEC103Asdu20Data();
	~IEC103Asdu20Data();
	virtual bool handle(const QByteArray& buff);
	virtual bool createData(IECDataConfig& config);

public:
	uchar dco;
};

#endif // IEC103ASDU20DATA_H
