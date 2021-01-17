#ifndef IEC103ASDU35DATA_H
#define IEC103ASDU35DATA_H

#include "iec103asdu32data.h"



class IEC103Asdu35Data : public IEC103Asdu32Data
{
public:
	IEC103Asdu35Data();
	~IEC103Asdu35Data();
	virtual bool handle(const QByteArray& buff);
	virtual bool createData(IECDataConfig& config);
};

#endif // IEC103ASDU35DATA_H
