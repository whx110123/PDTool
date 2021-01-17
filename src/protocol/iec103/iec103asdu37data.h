#ifndef IEC103ASDU37DATA_H
#define IEC103ASDU37DATA_H

#include "iec103asdu36data.h"



class IEC103Asdu37Data : public IEC103Asdu36Data
{
public:
	IEC103Asdu37Data();
	~IEC103Asdu37Data();
	virtual bool handle(const QByteArray& buff);
	virtual bool createData(IECDataConfig& config);

public:

	QDateTime datetime;
};

#endif // IEC103ASDU37DATA_H
