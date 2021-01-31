#ifndef IEC101ASDU121DATA_H
#define IEC101ASDU121DATA_H

#include "iec101asdu.h"



class IEC101Asdu121Data : public IEC101AsduData
{
public:
	IEC101Asdu121Data(const MyConfig& Config);
	~IEC101Asdu121Data();
	virtual bool handle(const QByteArray& buff);

public:
	ushort nof;
	uchar nos;
	uint lof;
	uchar srq;
};

#endif // IEC101ASDU121DATA_H
