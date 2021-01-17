#ifndef IEC103ASDU41DATA_H
#define IEC103ASDU41DATA_H

#include "iec103asdu40data.h"

class IEC103Asdu41Data : public IEC103Asdu40Data
{
public:
	IEC103Asdu41Data();
	~IEC103Asdu41Data();
	virtual bool handle(const QByteArray& buff);
	virtual bool createData(IECDataConfig& config);

public:
	QDateTime datetime;
};

#endif // IEC103ASDU41DATA_H
