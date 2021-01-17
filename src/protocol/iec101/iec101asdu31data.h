#ifndef IEC101ASDU31DATA_H
#define IEC101ASDU31DATA_H
#include "iec101asdu4data.h"


class IEC101Asdu31Data : public IEC101Asdu4Data
{
public:
	IEC101Asdu31Data();
	~IEC101Asdu31Data();
	virtual bool handle(const QByteArray& buff);
	virtual bool createData(IECDataConfig& config);

};

#endif // IEC101ASDU31DATA_H
