#ifndef IEC101ASDU102DATA_H
#define IEC101ASDU102DATA_H

#include "iec101asdu.h"



class IEC101Asdu102Data : public IEC101AsduData
{
public:
	IEC101Asdu102Data();
	~IEC101Asdu102Data();
	virtual bool handle(const QByteArray& buff);
	virtual bool createData(IECDataConfig& config);
};

#endif // IEC101ASDU102DATA_H
