#ifndef IEC103NETBAOXIN_H
#define IEC103NETBAOXIN_H

#include "iec103asdu.h"
#include <iec104apci.h>

class IEC103NetBaoXin : public MyBase
{
public:
	IEC103NetBaoXin();
	~IEC103NetBaoXin();
	virtual bool init(const QByteArray& buff);
	virtual QString showToText();
	virtual bool createData(IECDataConfig& config);

public:
	IEC104Apci apci;
	IEC103Asdu asdu;

public:
	QString mLengthType;
};

#endif // IEC103NETBAOXIN_H
