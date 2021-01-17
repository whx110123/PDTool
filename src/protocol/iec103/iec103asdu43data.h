#ifndef IEC103ASDU43DATA_H
#define IEC103ASDU43DATA_H

#include "iec103asdu42data.h"

class IEC103Asdu43Data : public IEC103Asdu42Data
{
public:
	IEC103Asdu43Data();
	~IEC103Asdu43Data();
	virtual bool handle(const QByteArray& buff);
	virtual bool createData(IECDataConfig& config);

public:
	QDateTime datetime;
};

#endif // IEC103ASDU43DATA_H
