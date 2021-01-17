#ifndef IEC103ASDU36DATA_H
#define IEC103ASDU36DATA_H

#include "iec103asdu.h"

class IEC103Asdu36Data : public IEC103AsduData
{
public:
	IEC103Asdu36Data();
	~IEC103Asdu36Data();
	virtual bool handle(const QByteArray& buff);
	virtual bool createData(IECDataConfig& config);

public:
	int intdata;
	uchar bcr;
};

#endif // IEC103ASDU36DATA_H
