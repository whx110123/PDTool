#ifndef IEC103ASDU32DATA_H
#define IEC103ASDU32DATA_H

#include "iec103asdu.h"




class IEC103Asdu32Data : public IEC103AsduData
{
public:
	IEC103Asdu32Data();
	~IEC103Asdu32Data();
	virtual bool handle(const QByteArray& buff);
	virtual bool createData(IECDataConfig& config);

public:
	short shortdata;
	uchar qds;
	uint hr;
	QDateTime datetime;
};

#endif // IEC103ASDU32DATA_H
