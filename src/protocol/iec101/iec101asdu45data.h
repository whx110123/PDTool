#ifndef IEC101ASDU45DATA_H
#define IEC101ASDU45DATA_H
#include "iec101asdu.h"


class IEC101Asdu45Data : public IEC101AsduData
{
public:
	IEC101Asdu45Data(const MyConfig& Config);
	~IEC101Asdu45Data();
	virtual bool handle(const QByteArray& buff);
	virtual bool createData(MyData& proData);

public:
	uchar sco;
};

#endif // IEC101ASDU45DATA_H
