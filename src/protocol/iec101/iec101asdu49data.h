#ifndef IEC101ASDU49DATA_H
#define IEC101ASDU49DATA_H

#include "iec101asdu.h"



class IEC101Asdu49Data : public IEC101AsduData
{
public:
	IEC101Asdu49Data(const MyConfig& Config);
	~IEC101Asdu49Data();
	virtual bool handle(const QByteArray& buff);
	virtual bool createData(MyData& proData);

public:
	short shortdata;
	uchar qos;
};

#endif // IEC101ASDU49DATA_H
