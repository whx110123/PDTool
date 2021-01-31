#ifndef IEC101ASDU21DATA_H
#define IEC101ASDU21DATA_H

#include "iec101asdu.h"


class IEC101Asdu21Data : public IEC101AsduData
{
public:
	IEC101Asdu21Data(const MyConfig& Config);
	~IEC101Asdu21Data();
	virtual bool handle(const QByteArray& buff);

public:
	short shortdata;
};

#endif // IEC101ASDU21DATA_H
