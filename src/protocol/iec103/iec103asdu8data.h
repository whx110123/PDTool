#ifndef IEC103ASDU8DATA_H
#define IEC103ASDU8DATA_H

#include "iec103asdu.h"

class IEC103Asdu8Data : public IEC103AsduData
{
public:
	IEC103Asdu8Data();
	~IEC103Asdu8Data();
	virtual bool handle(const QByteArray& buff);
	virtual bool createData(IECDataConfig& config);
};

#endif // IEC103ASDU8DATA_H
