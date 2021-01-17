#ifndef IEC101ASDU47DATA_H
#define IEC101ASDU47DATA_H

#include "iec101asdu.h"



class IEC101Asdu47Data : public IEC101AsduData
{
public:
	IEC101Asdu47Data();
	~IEC101Asdu47Data();
	virtual bool handle(const QByteArray& buff);
	virtual bool createData(IECDataConfig& config);

public:
	uchar rco;
};

#endif // IEC101ASDU47DATA_H
