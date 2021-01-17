#ifndef IEC103ASDU7DATA_H
#define IEC103ASDU7DATA_H

#include "iec103asdu.h"

class IEC103Asdu7Data : public IEC103AsduData
{
public:
	IEC103Asdu7Data();
	~IEC103Asdu7Data();
	virtual bool handle(const QByteArray& buff);
	virtual bool createData(IECDataConfig& config);
};

#endif // IEC103ASDU7DATA_H
