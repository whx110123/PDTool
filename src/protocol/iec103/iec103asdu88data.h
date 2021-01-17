#ifndef IEC103ASDU88DATA_H
#define IEC103ASDU88DATA_H

#include "iec103asdu.h"

class IEC103Asdu88Data : public IEC103AsduData
{
public:
	IEC103Asdu88Data();
	~IEC103Asdu88Data();
	virtual bool handle(const QByteArray& buff);
	virtual bool createData(IECDataConfig& config);

public:
	uchar qcc;
};

#endif // IEC103ASDU88DATA_H
