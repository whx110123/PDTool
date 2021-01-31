#ifndef IEC101ASDU9DATA_H
#define IEC101ASDU9DATA_H

#include "iec101asdu21data.h"

class IEC101Asdu9Data : public IEC101Asdu21Data
{
public:
	IEC101Asdu9Data(const MyConfig& Config);
	~IEC101Asdu9Data();
	virtual bool handle(const QByteArray& buff);

public:
	uchar qds;
};

#endif // IEC101ASDU9DATA_H
