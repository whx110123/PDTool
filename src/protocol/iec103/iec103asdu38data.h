#ifndef IEC103ASDU38DATA_H
#define IEC103ASDU38DATA_H

#include "iec103asdu.h"



class IEC103Asdu38Data : public IEC103AsduData
{
public:
	IEC103Asdu38Data(const MyConfig& Config);
	~IEC103Asdu38Data();
	virtual bool handle(const QByteArray& buff);

public:
	uchar vti;
	uchar qds;
};

#endif // IEC103ASDU38DATA_H
