#ifndef IEC101ASDU104DATA_H
#define IEC101ASDU104DATA_H

#include "iec101asdu.h"



class IEC101Asdu104Data : public IEC101AsduData
{
public:
	IEC101Asdu104Data(const MyConfig& Config);
	~IEC101Asdu104Data();
	virtual bool handle(const QByteArray& buff);

public:
	ushort ushortData;
};

#endif // IEC101ASDU104DATA_H
