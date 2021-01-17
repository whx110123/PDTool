#ifndef IEC103ASDU48DATA_H
#define IEC103ASDU48DATA_H

#include "iec103asdu.h"



class IEC103Asdu48Data : public IEC103AsduData
{
public:
	IEC103Asdu48Data();
	~IEC103Asdu48Data();
	virtual bool handle(const QByteArray& buff);
	virtual bool createData(IECDataConfig& config);

public:

	float dataFloat;
	uchar qds;
	QDateTime datetime;
};

#endif // IEC103ASDU48DATA_H
