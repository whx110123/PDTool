#ifndef IEC101ASDU46DATA_H
#define IEC101ASDU46DATA_H

#include "iec101asdu.h"


class IEC101Asdu46Data : public IEC101AsduData
{
public:
	IEC101Asdu46Data(const MyConfig& Config);
	~IEC101Asdu46Data();
	virtual bool handle(const QByteArray& buff);
	virtual bool createData(MyData& proData);

public:
	uchar dco;
};

#endif // IEC101ASDU46DATA_H
