#ifndef IEC101ASDU122DATA_H
#define IEC101ASDU122DATA_H

#include "iec101asdu.h"



class IEC101Asdu122Data : public IEC101AsduData
{
public:
	IEC101Asdu122Data();
	~IEC101Asdu122Data();
	virtual bool handle(const QByteArray& buff);
	virtual bool createData(IECDataConfig& config);

public:
	ushort nof;
	uchar nos;
	uchar scq;
};

#endif // IEC101ASDU122DATA_H
