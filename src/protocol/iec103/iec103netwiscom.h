#ifndef IEC103NETWISCOM_H
#define IEC103NETWISCOM_H

#include "iec103asdu.h"
#include "iec103netapciwiscom.h"

class IEC103NetWiscom : public MyBase
{
public:
	IEC103NetWiscom();
	~IEC103NetWiscom();
	virtual bool init(const QByteArray& buff);
	virtual QString showToText();
	virtual bool createData(IECDataConfig& config);

public:
	IEC103NetApciWiscom apci;
	IEC103Asdu asdu;

public:
	QString mLengthType;
};

#endif // IEC103NETWISCOM_H
