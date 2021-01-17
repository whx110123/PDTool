#ifndef IEC101ASDU104DATA_H
#define IEC101ASDU104DATA_H

#include "iec101asdu.h"



class IEC101Asdu104Data : public IEC101AsduData
{
public:
	IEC101Asdu104Data();
	~IEC101Asdu104Data();
	virtual bool handle(const QByteArray& buff);
	virtual bool createData(IECDataConfig& config);

public:
	ushort ushortData;
};

#endif // IEC101ASDU104DATA_H
