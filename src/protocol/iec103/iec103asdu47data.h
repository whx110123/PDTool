#ifndef IEC103ASDU47DATA_H
#define IEC103ASDU47DATA_H

#include "iec103asdu46data.h"

class IEC103Asdu47Data : public IEC103Asdu46Data
{
public:
	IEC103Asdu47Data();
	~IEC103Asdu47Data();
	virtual bool handle(const QByteArray& buff);
	virtual bool createData(IECDataConfig& config);

public:

	QDateTime datetime;
};

#endif // IEC103ASDU47DATA_H
