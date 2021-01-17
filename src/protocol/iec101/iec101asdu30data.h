#ifndef IEC101ASDU30DATA_H
#define IEC101ASDU30DATA_H

#include "iec101asdu2data.h"

class IEC101Asdu30Data : public IEC101Asdu2Data
{
public:
	IEC101Asdu30Data();
	~IEC101Asdu30Data();
	virtual bool handle(const QByteArray& buff);
	virtual bool createData(IECDataConfig& config);

};

#endif // IEC101ASDU30DATA_H
