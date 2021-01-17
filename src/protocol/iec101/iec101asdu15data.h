#ifndef IEC101ASDU15DATA_H
#define IEC101ASDU15DATA_H

#include "iec101asdu.h"

class IEC101Asdu15Data : public IEC101AsduData
{
public:
	IEC101Asdu15Data();
	~IEC101Asdu15Data();
	virtual bool handle(const QByteArray& buff);
	virtual bool createData(IECDataConfig& config);

public:
	int intdata;
	uchar bcr;
};

#endif // IEC101ASDU15DATA_H
