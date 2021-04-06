#ifndef IEC101ASDU51DATA_H
#define IEC101ASDU51DATA_H

#include "iec101asdu.h"

class IEC101Asdu51Data : public IEC101AsduData
{
public:
	IEC101Asdu51Data(const MyConfig& Config);
	~IEC101Asdu51Data();
	virtual bool handle(const QByteArray& buff);

public:
	uint uintdata;
};

#endif // IEC101ASDU51DATA_H
