#ifndef IEC103ASDU66DATA_H
#define IEC103ASDU66DATA_H

#include "iec103asdu.h"



class IEC103Asdu66Data : public IEC103AsduData
{
public:
	IEC103Asdu66Data(const MyConfig& Config);
	~IEC103Asdu66Data();
	virtual bool handle(const QByteArray& buff);

public:
	short shortdata;
	uchar qos;
};

#endif // IEC103ASDU66DATA_H
